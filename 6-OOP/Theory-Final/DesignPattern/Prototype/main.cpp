#include <iostream>
#include <string>
#include <vector>
#include <memory>

class Document {
protected:
    std::string _title;
    std::string _author;
public:
    Document(const std::string& title, const std::string& author) : _title(title), _author(author) {}
    Document(const Document& other) : _title(other._title), _author(other._author) {}
    virtual ~Document() = default;
    virtual std::unique_ptr<Document> clone() const = 0;
    virtual void displayInfo() const {
        std::cout << "title: " << _title << "; " << "author: " << _author;
    }
};

class Letter : public Document {
private:
    std::string _recipientAddress;
public:
    Letter(const std::string& title, const std::string& author, const std::string& recipientAddress) : Document(title, author), _recipientAddress(recipientAddress) {}
    Letter(const Letter& other) : Document(other), _recipientAddress(other._recipientAddress) {}
    std::unique_ptr<Document> clone() const override {
        return std::make_unique<Letter>(*this);
    }
    void displayInfo() const override {
        Document::displayInfo();
        std::cout << " recipient address: " << _recipientAddress << "\n";
    }
};

class Report : public Document {
private:
    std::string _summary;
public:
    Report(const std::string& title, const std::string& author, const std::string& summary) : Document(title, author), _summary(summary) {}
    Report(const Report& other) : Document(other), _summary(other._summary) {}
    std::unique_ptr<Document> clone() const override {
        return std::make_unique<Report>(*this);
    }
    void displayInfo() const override {
        Document::displayInfo();
        std::cout << " summary: " << _summary << "\n";
    }
};

class Resume : public Document {
private:
    std::vector<std::string> _skills;
public:
    Resume(const std::string& title, const std::string& author, const std::vector<std::string>& skills) : Document(title, author), _skills(skills) {}
    Resume(const Resume& other) : Document(other), _skills(other._skills) {}
    std::unique_ptr<Document> clone() const override {
        return std::make_unique<Resume>(*this);
    }
    void displayInfo() const override {
        Document::displayInfo();
        std::cout << "; skills: ";
        for (const auto& skill : _skills) {
            std::cout << skill << ", ";
        }
        std::cout << "\n";
    }
};

int main() {
    std::vector<std::unique_ptr<Document>> docs;
    
    docs.push_back(std::make_unique<Letter>("Chuong 1", "Nguyen Phuc Hoang", "Ho Chi Minh"));
    docs.push_back(std::make_unique<Report>("Chuong 1", "Nguyen Phuc Hoang", "Hong biec"));
    std::vector<std::string> skills = {"skill 1", "skill 2"};
    docs.push_back(std::make_unique<Resume>("Chuong 1", "Nguyen Phuc Hoang", skills));

    std::vector<std::unique_ptr<Document>> cloneDocs;
    for (const auto& doc : docs) {
        cloneDocs.push_back(doc->clone());
    }

    std::cout << "Clone document:\n";
    for (const auto& doc : cloneDocs) {
        doc->displayInfo();
    }

    return 0;
}