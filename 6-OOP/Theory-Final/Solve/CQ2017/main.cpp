#include <iostream>
#include <string>
#include <vector>
#include <format>
#include <sstream>
#include <fstream>

class Employee {
protected:
    std::string _id;
    std::string _name;
    std::string _dateOfBirth;
    std::string _location;
    float _salaryCoefficient;
    std::string _startingWorkDate;
    
    std::string _type;

    virtual void input(std::istream& is, Employee& e) {
        // Không cần getline ở đây vì stream đã chứa line
        std::string token;
        
        // Đọc các field chung
        std::getline(is, _type, ',');
        std::getline(is, _id, ',');
        std::getline(is, _name, ',');
        std::getline(is, _dateOfBirth, ',');
        std::getline(is, _location, ',');
        
        std::getline(is, token, ',');
        _salaryCoefficient = std::stof(token);
        
        std::getline(is, _startingWorkDate, ',');
    }
public:
    // Thêm default constructor
    Employee() : _salaryCoefficient(0.0f) {}
    
    Employee(
        std::string id,
        std::string name,
        std::string dateOfBirth,
        std::string location,
        float salaryCoefficient,
        std::string startingWorkDate
    ) :
        _id(id),
        _name(name),
        _dateOfBirth(dateOfBirth),
        _location(location),
        _salaryCoefficient(salaryCoefficient),
        _startingWorkDate(startingWorkDate) 
    {}

    virtual ~Employee() = default;
    virtual float calcSalary() const = 0;
    virtual std::string type() const {
        return _type;
    }

    virtual std::string toString() const {
        return std::format(
            "type=\"{}\",id=\"{}\",name=\"{}\",dateOfBirth=\"{}\",location=\"{}\",salaryCoefficient=\"{}\",statingWorkDate=\"{}\"",
            _type, _id, _name, _dateOfBirth, _location, _salaryCoefficient, _startingWorkDate
        );
    }

    friend std::ostream& operator<<(std::ostream& os, const Employee& e) {
        os << e.toString();
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Employee& e) {
        e.input(is, e);
        return is;
    }
};

class Manager : public Employee {
private:
    float _baseSalary = 0.0f;

    void input(std::istream& is, Employee& e) override {
        Employee::input(is, e);
        
        // Đọc baseSalary từ stream hiện tại
        std::string token;
        std::getline(is, token, ',');
        if (!token.empty()) {
            _baseSalary = std::stof(token);
        }
    }
public:
    Manager() { _type = "manager"; }
    
    Manager(std::string id,
        std::string name,
        std::string dateOfBirth,
        std::string location,
        float salaryCoefficient,
        std::string startingWorkDate,
        float baseSalary
    ) :
        Employee(id, name, dateOfBirth, location, salaryCoefficient, startingWorkDate),
        _baseSalary(baseSalary)
    {
        _type = "manager";
    }

    float calcSalary() const override {
        return _baseSalary * _salaryCoefficient;
    }

    std::string toString() const override {
        return std::format(
            "{},baseSalary=\"{}\"",
            _type, Employee::toString(), _baseSalary
        );
    }
};

class Programmer : public Employee {
private:
    float _baseSalary = 0.0f;
    float _overtime = 0.0f;

    void input(std::istream& is, Employee& e) override {
        Employee::input(is, e);
        
        std::string line;
        is.clear();
        is.seekg(0);
        if (std::getline(is, line)) {
            std::stringstream ss(line);
            std::string token;
            
            // Skip 7 fields đầu
            for (int i = 0; i < 7; i++) {
                std::getline(ss, token, ',');
            }
            
            // Đọc baseSalary và overtime
            std::getline(ss, token, ',');
            _baseSalary = std::stof(token);
            
            std::getline(ss, token, ',');
            _overtime = std::stof(token);
        }
    }
public:
    Programmer() { _type = "programmer"; }
    
    Programmer(std::string id,
        std::string name,
        std::string dateOfBirth,
        std::string location,
        float salaryCoefficient,
        std::string startingWorkDate,
        float baseSalary,
        float overtime
    ) :
        Employee(id, name, dateOfBirth, location, salaryCoefficient, startingWorkDate),
        _baseSalary(baseSalary),
        _overtime(overtime)
    {
        _type = "programmer";
    }

    float calcSalary() const override {
        return _baseSalary * _salaryCoefficient + _overtime;
    }

    std::string toString() const override {
        return std::format(
            "{},baseSalary=\"{}\",overtime=\"{}\"",
            Employee::toString(), _baseSalary, _overtime
        );
    }
};

class Designer : public Employee {
private:
    float _baseSalary = 0.0f;
    float _bonus = 0.0f;

    void input(std::istream& is, Employee& e) override {
        Employee::input(is, e);
        
        std::string line;
        is.clear();
        is.seekg(0);
        if (std::getline(is, line)) {
            std::stringstream ss(line);
            std::string token;
            
            // Skip 7 fields đầu
            for (int i = 0; i < 7; i++) {
                std::getline(ss, token, ',');
            }
            
            // Đọc baseSalary và bonus
            std::getline(ss, token, ',');
            _baseSalary = std::stof(token);
            
            std::getline(ss, token, ',');
            _bonus = std::stof(token);
        }
    }
public:
    Designer() { _type = "designer"; }
    
    Designer(std::string id,
        std::string name,
        std::string dateOfBirth,
        std::string location,
        float salaryCoefficient,
        std::string startingWorkDate,
        float baseSalary,
        float bonus
    ) :
        Employee(id, name, dateOfBirth, location, salaryCoefficient, startingWorkDate),
        _baseSalary(baseSalary),
        _bonus(bonus)
    {
        _type = "designer";
    }

    float calcSalary() const override {
        return _baseSalary * _salaryCoefficient + _bonus;
    }

    std::string toString() const override {
        return std::format(
            "{},baseSalary=\"{}\",bonus=\"{}\"",
            Employee::toString(), _baseSalary, _bonus
        );
    }
};

class Tester : public Employee {
private:
    float _baseSalary = 0.0f;
    int _error = 0;

    void input(std::istream& is, Employee& e) override {
        Employee::input(is, e);
        
        std::string line;
        is.clear();
        is.seekg(0);
        if (std::getline(is, line)) {
            std::stringstream ss(line);
            std::string token;
            
            // Skip 7 fields đầu
            for (int i = 0; i < 7; i++) {
                std::getline(ss, token, ',');
            }
            
            // Đọc baseSalary và error
            std::getline(ss, token, ',');
            _baseSalary = std::stof(token);
            
            std::getline(ss, token, ',');
            _error = std::stoi(token);
        }
    }
public:
    Tester() { _type = "tester"; }
    
    Tester(std::string id,
        std::string name,
        std::string dateOfBirth,
        std::string location,
        float salaryCoefficient,
        std::string startingWorkDate,
        float baseSalary,
        int error
    ) :
        Employee(id, name, dateOfBirth, location, salaryCoefficient, startingWorkDate),
        _baseSalary(baseSalary),
        _error(error)
    {
        _type = "tester";
    }

    float calcSalary() const override {
        return _baseSalary * _salaryCoefficient + _error * 200000;
    }

    std::string toString() const override {
        return std::format(
            "{},baseSalary=\"{}\",error=\"{}\"",
            Employee::toString(), _baseSalary, _error
        );
    }
};

// class EmployeeFactory {
// public:
//     virtual ~EmployeeFactory() = default;
//     virtual Employee* create(const std::string& type) const {
//         if (type == "")
//     }
// };

// class ManagerFactory : public EmployeeFactory {
// public:
//     Employee* create(const std::string& type) const override {
//         return new Manager;
//     }
// }

class EmployeesRepository {
private:
    std::string _fileName;
    
public:
    std::vector<Employee*> _list;

    EmployeesRepository(const std::string& fileName) : _fileName(fileName) {}

    ~EmployeesRepository() {
        for (auto& l : _list) {
            delete l;
        }
    }

    void getAll() {
        std::ifstream ifs(_fileName);
        if (!ifs) {
            std::cerr << "can't open file " << _fileName << "\n";
            return;
        }

        std::string line = "";

        while (std::getline(ifs, line)) {
            // lấy type
            int idx = line.find(',');
            std::string type = line.substr(0, idx);
            
            Employee* e = nullptr;
            if (type == "manager") {
                e = new Manager();
            } else if (type == "programmer") {
                e = new Programmer();
            } else if (type == "designer") {
                e = new Designer();
            } else if (type == "tester") {
                e = new Tester();
            }

            std::istringstream iss(line);
            iss >> *e;
            _list.push_back(e);
        }

        ifs.close();
    }

    float calculatorTotalSalary() {
        double total = 0;
        for (const auto& e : _list) {
            total += e->calcSalary();
        }
        return total;
    }
};

int main() {
    std::string fileName = "data.txt";
    EmployeesRepository repo(fileName);
    repo.getAll();

    for (const auto& e : repo._list) {
        std::cout << *e << "\n";
    }

    std::cout << "\n\nTotal salary: " << repo.calculatorTotalSalary() << "\n";
    
    return 0;
}