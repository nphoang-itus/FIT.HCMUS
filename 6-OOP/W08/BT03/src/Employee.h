#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
#include <iostream>

class Employee {
protected:
    std::string _name;
    std::string _location;

public:
    virtual ~Employee() = default;
    Employee();
    Employee(const std::string& name, const std::string& location);

    std::string getName() const;
    std::string getLocation() const;

    void setName(const std::string& name);
    void setLocation(const std::string& location);

    virtual bool checkOutstandingEmployee() const = 0;
    virtual std::string getEmployeeType() const = 0;
    virtual void print(std::ostream& os) const = 0;
    virtual void read(std::istream& is) = 0;

    friend std::ostream& operator<<(std::ostream& os, const Employee& emp);
    friend std::istream& operator>>(std::istream& is, Employee& emp);
};

class Secretary : public Employee {
private:
    std::string _foreignLanguageCertificate;
    int _numberOfReports;
public:
    Secretary();
    Secretary(const std::string& name, const std::string& location, const std::string& foreignLanguageCertificate, const int& numberOfReports);

    std::string getCertificate() const;
    int getNumberOfReports() const;

    void setForeignLanguageCertificate(const std::string& foreignLanguageCertificate);
    void setNumberOfReports(const int& numberOfReports);

    bool checkOutstandingEmployee() const override;
    std::string getEmployeeType() const override;
    void print(std::ostream& os) const override;
    void read(std::istream& is) override;

    friend std::ostream& operator<<(std::ostream& os, const Secretary& sec);
    friend std::istream& operator>>(std::istream& is, Secretary& sec);
};

class Technician : public Employee {
private:
    std::string _professionalCertificate;
    int _numberOfInitiatives;
public:
    Technician();
    Technician(const std::string& name, const std::string& location, const std::string& professionalCertificate, const int& numberOfInitiatives);

    std::string getCertificate() const;
    int getNumberOfInitiatives() const;

    bool checkOutstandingEmployee() const override;
    std::string getEmployeeType() const override;
    void print(std::ostream& os) const override;
    void read(std::istream& is) override;

    void setProfessionalCertificate(const std::string& professionalCertificate);
    void setNumberOfInitiatives(const int& numberOfInitiatives);

    friend std::ostream& operator<<(std::ostream& os, const Technician& tech);
    friend std::istream& operator>>(std::istream& is, Technician& tech);
};

#endif