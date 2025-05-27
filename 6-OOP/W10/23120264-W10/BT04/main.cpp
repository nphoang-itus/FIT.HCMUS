#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <exception>
#include <sstream>
#include <iomanip>

enum class ErrorCode {
    UnknownError = 1000,
    ArgumentNull = 1001,
    InvalidSize = 1002,
    FileNotFound = 1003,
    FolderNotFound = 1004,
    DuplicateName = 1005,
    InvalidAttributeChange = 1006,
    ArgumentEmpty = 1007
};

class MyException : public std::runtime_error {
private:
    std::string _errorDescription;
    ErrorCode _errorCode;
    std::string _errorMessage;

    static std::string BuildErrorMessage(const ErrorCode& errCode, const std::string& errDes) {
        std::ostringstream oss;
        oss << errDes << " (Code: "<< static_cast<int>(errCode) << ")" ;
        return oss.str();
    }

public:
    MyException(const ErrorCode& errCode, const std::string& errDes)
        : std::runtime_error(BuildErrorMessage(errCode, errDes)),
          _errorCode(errCode),
          _errorDescription(errDes),
          _errorMessage(BuildErrorMessage(errCode, errDes)) {}

    const std::string& GetErrorDescription() const { return _errorDescription; }
    const ErrorCode& GetErrorCode() const { return _errorCode; }
    const char* what() const noexcept override { return _errorMessage.c_str(); }
};

enum class Attribute {
    READ_ONLY,
    HIDDEN,
};

class CItem {
protected:
    std::string _name;
    Attribute _attribute;

public:
    virtual ~CItem() = default;
    CItem(const std::string& name) : _attribute(Attribute::READ_ONLY) {
        if (name.empty()) {
            throw MyException(ErrorCode::ArgumentEmpty, "Item name cannot be empty");
        }
        _name = name;
    }

    virtual float Size() const = 0;
    std::string Name() const { return _name; }

    Attribute Attribute() const { return _attribute; }

    virtual void SetHidden(const bool& isHidden, const bool& isAlsoApplyToChildren) {
        _attribute = isHidden ? Attribute::HIDDEN : Attribute::READ_ONLY;
    }

    virtual void Print(const bool& isPrintHiddenItems, int indent = 0) const = 0;
};

class CFolder : public CItem {
private:
    std::vector<CItem*> _children;

public:
    CFolder(const std::string& name) : CItem(name) {}

    void Print(const bool& isPrintHiddenItems, int indent = 0) const override {
        if (!isPrintHiddenItems && _attribute == Attribute::HIDDEN) {
            return;
        }
        
        std::cout << std::string(indent, ' ') << "[" << _name << "]" << " (" << std::fixed << std::setprecision(3) << Size() << " B)\n";
        for (CItem* child : _children) {
            child->Print(isPrintHiddenItems, indent + 2);
        }
    }

    void Add(CItem* item) {
        if (item == nullptr) {
            throw MyException(ErrorCode::ArgumentNull, "Argument must not be null");
        }
        
        // Kiểm tra duplicate name
        for (const CItem* existingItem : _children) {
            if (existingItem->Name() == item->Name()) {
                throw MyException(ErrorCode::DuplicateName, 
                    "Item with name '" + item->Name() + "' already exists");
            }
        }

        _children.push_back(item);
    }

    float Size() const override  {
        float total = 0;
        for (const CItem* item: _children) {
            total += item->Size();
        }
        return total;
    }

    CItem* FindByName(const std::string& name) {
        // Tìm trong cấp con trực tiếp trước
        for (CItem* item : _children) {
            if (item->Name() == name) {
                return item;
            }
        }

        for (CItem* item : _children) {
            CFolder* folder = dynamic_cast<CFolder*>(item);
            if (folder != nullptr) {
                CItem* found = folder->FindByName(name);
                if (found != nullptr) {
                    return found;
                }
            }
        }

        return nullptr;
    }

    CItem* RemoveByName(const std::string& name) {
        for (auto it = _children.begin(); it != _children.end(); ++it) {
            if ((*it)->Name() == name) {
                CItem* itemForRemove = *it;
                _children.erase(it);
                return itemForRemove;
            }
        }

        for (CItem* item : _children) {
            CFolder* folder = dynamic_cast<CFolder*>(item);
            if (folder != nullptr) {
                CItem* removed = folder->RemoveByName(name);
                if (removed != nullptr) {
                    return removed;
                }
            }
        }

        return nullptr;
    }

    void SetHidden(const bool& isHidden, const bool& isAlsoApplyToChildren) override {
        CItem::SetHidden(isHidden, isAlsoApplyToChildren);

        if (isAlsoApplyToChildren) {
            for (CItem* item: _children) {
                CFolder* folder = dynamic_cast<CFolder*>(item);
                if (folder) {
                    folder->SetHidden(isHidden, isAlsoApplyToChildren);
                }
            }
        }
    }
};

class CFile : public CItem {
private:
    float _size;

public:
    CFile(const std::string& name, const float& size) : CItem(name) {
        if (size < 0) {
            throw MyException(ErrorCode::InvalidSize, "File size cannot be negative");
        }

        _size = size;
    }

    void Print(const bool& isPrintHiddenItems, int indent = 0) const override {
        if (!isPrintHiddenItems && _attribute == Attribute::HIDDEN) {
            return;
        }
        
        std::cout << std::string(indent, ' ') << _name << " (" << std::fixed << std::setprecision(3) << _size << " B)\n";
    }

    float Size() const override{ return _size; }
};

int main() {
    try {
        CFolder C("C");
        CFolder System("System");
        CFolder Windows("Windows");
        CFile a_txt("a.txt", 123);
        CFile b_doc("b.doc", 456);

        System.Add(&a_txt);
        Windows.Add(&b_doc);
        C.Add(&System);
        C.Add(&Windows);

        std::cout << "\nContent of folder C ->\n";
        bool isPrintHiddenItems = false;
        C.Print(isPrintHiddenItems);

        CItem* p = C.RemoveByName("System");
        std::cout << "\n\nContent of folder C after removing folder System ->\n";
        C.Print(isPrintHiddenItems);

        std::cout << "\n\n";
        std::string itemToFind = "b.doc";
        p = C.FindByName(itemToFind);
        if (p) {
            std::cout << itemToFind << " is found in folder C\n";
        } else {
            std::cout << itemToFind << " isn't found\n";
        }

        itemToFind = "a.txt";
        p = C.FindByName(itemToFind);
        if (p) {
            std::cout << itemToFind << " is found in folder C\n\n";
        } else {
            std::cout << itemToFind << " isn't found\n\n";
        }

        itemToFind = "Windows";
        p = C.FindByName(itemToFind);
        bool isHidden = false;
        bool isAlsoApplyToChildren = false;

        if (p) {
            std::cout << itemToFind << " is found in folder C\n";
            std::cout << "Content of folder " << itemToFind << "->\n";
            
            isHidden = true, isAlsoApplyToChildren = false;
            p->SetHidden(isHidden, isAlsoApplyToChildren);
            p->Print(false); // Vì Windows đã được set là hidden nên sẽ ko in ra gì

            isHidden = true, isAlsoApplyToChildren = true;
            p->SetHidden(isHidden, isAlsoApplyToChildren);
            p->Print(false); // vì p đang là Windows mà đang ở chế độ hidden nên sẽ ko in ra gì
        } else {
            std::cout << itemToFind << " isn't found\n";
        }
    } catch (const MyException& e) {
        std::cout << "Custom Error: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Standard Error: " << e.what() << std::endl;
    }

    return 0;
}