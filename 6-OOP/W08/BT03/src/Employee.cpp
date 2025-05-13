#include "Employee.h"

#include <sstream>

// ==== Implement Employee Class ====
Employee::Employee() : _name(""), _location("") {}

Employee::Employee(const std::string& name, const std::string& location) : _name(name), _location(location) {}

std::string Employee::getName() const {
    return _name;
}

std::string Employee::getLocation() const {
    return _location;
}

void Employee::setName(const std::string& name) {
    _name = name;
}

void Employee::setLocation(const std::string& location) {
    _location = location;
}

void Employee::print(std::ostream& os) const {
    os << _name << "(" << _location << ")";
}

// Tran Van A (Tp Ho Chi Minh)
void Employee::read(std::istream& is) {
    std::string token = "";
    
    std::getline(is, token, '(');
    token.erase(token.find_last_not_of(" ") + 1);
    setName(token);

    std::getline(is, token, ')');
    setLocation(token);
}

std::ostream& operator<<(std::ostream& os, const Employee& emp) {
    emp.print(os);
    return os;
}

// Tran Van A (Tp Ho Chi Minh)
std::istream& operator>>(std::istream& is, Employee& emp) {
    emp.read(is);
    return is;
}

// ==== Implement Secretary Class ====
Secretary::Secretary() : _foreignLanguageCertificate(""), _numberOfReports(0) {}

Secretary::Secretary(const std::string& name, const std::string& location, const std::string& foreignLanguageCertificate, const int& numberOfReports)
    : Employee(name, location), _foreignLanguageCertificate(foreignLanguageCertificate), _numberOfReports(numberOfReports) {}


std::string Secretary::getCertificate() const {
    return _foreignLanguageCertificate;
}

int Secretary::getNumberOfReports() const {
    return _numberOfReports;
}

void Secretary::setForeignLanguageCertificate(const std::string& foreignLanguageCertificate) {
    _foreignLanguageCertificate = foreignLanguageCertificate;
}

void Secretary::setNumberOfReports(const int& numberOfReports) {
    _numberOfReports = numberOfReports;
}

bool Secretary::checkOutstandingEmployee() const {
    bool isOutstandingEmployee = _numberOfReports > 12 ? true : false;
    return isOutstandingEmployee;
}

std::string Secretary::getEmployeeType() const {
    return "nvtk";
}

void Secretary::print(std::ostream& os) const {
    os << "nvtk: ";
    Employee::print(os);
    os << " [" << _foreignLanguageCertificate << "] <" << _numberOfReports << ">";
}

void Secretary::read(std::istream& is) {
    std::string employeeInfo = "";
    std::getline(is, employeeInfo, ')');
    employeeInfo += ')';
    std::istringstream iss(employeeInfo);
    Employee::read(iss);
    
    std::string token = "";
    
    std::getline(is, token, '[');
    std::getline(is, token, ']');
    setForeignLanguageCertificate(token);

    std::getline(is, token, '<');
    std::getline(is, token, '>');
    setNumberOfReports(std::stoi(token));
}

// Nguyen Thi B (Tp Ho Chi Minh) [Anh] <11>
std::ostream& operator<<(std::ostream& os, const Secretary& sec) {
    sec.print(os);
    return os;
}

// Nguyen Thi B (Tp Ho Chi Minh) | [Anh] <11>
std::istream& operator>>(std::istream& is, Secretary& sec) {
    sec.read(is);
    return is;
}

// ==== Implement Technician Class ====
Technician::Technician() : _professionalCertificate(""), _numberOfInitiatives(0) {}

Technician::Technician(const std::string& name, const std::string& location, const std::string& professionalCertificate, const int& numberOfInitiatives)
    : Employee(name, location), _professionalCertificate(professionalCertificate), _numberOfInitiatives(numberOfInitiatives) {}


std::string Technician::getCertificate() const {
    return _professionalCertificate;
}

int Technician::getNumberOfInitiatives() const {
    return _numberOfInitiatives;
}

void Technician::setProfessionalCertificate(const std::string& professionalCertificate) {
    _professionalCertificate = professionalCertificate;
}

void Technician::setNumberOfInitiatives(const int& numberOfInitiatives) {
    _numberOfInitiatives = numberOfInitiatives;
}

bool Technician::checkOutstandingEmployee() const {
    bool isOutstandingEmployee = _numberOfInitiatives > 6 ? true : false;
    return isOutstandingEmployee;
}

std::string Technician::getEmployeeType() const {
    return "nvkt";
}

void Technician::print(std::ostream& os) const {
    os << "nvkt: ";
    Employee::print(os);
    os << " [" << _professionalCertificate << "] <" << _numberOfInitiatives << ">";
}

void Technician::read(std::istream& is) {
    std::string employeeInfo = "";
    std::getline(is, employeeInfo, ')');
    employeeInfo += ')';
    std::istringstream iss(employeeInfo);
    Employee::read(iss);
    
    std::string token = "";
    
    std::getline(is, token, '[');
    std::getline(is, token, ']');
    setProfessionalCertificate(token);

    std::getline(is, token, '<');
    std::getline(is, token, '>');
    setNumberOfInitiatives(std::stoi(token));
}

std::ostream& operator<<(std::ostream& os, const Technician& tech) {
    tech.print(os);
    return os;
}

std::istream& operator>>(std::istream& is, Technician& tech) {
    tech.read(is);
    return is;
}