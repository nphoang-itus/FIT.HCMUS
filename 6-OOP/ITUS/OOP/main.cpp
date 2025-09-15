#include <iostream>
#include <string>
#include <vector>

class ICustomer {
public:
    virtual void update(std::string message) = 0;
};

class ConcreteCustomer : public ICustomer {
public:
    void update(std::string message) override {
        std::cout << message << "\n";
    }
};

class IStore {
public:
    virtual void addCustomer(ICustomer* cust) = 0;
    virtual void removeCustomer(ICustomer* cust) = 0;
    virtual void notifyCustomer(std::string message) = 0;
};

class ConcreteStore : public IStore {
protected:
    std::vector<ICustomer*> customers;
public:
    void addCustomer(ICustomer* cust) override {
        customers.push_back(cust);
    }

    void removeCustomer(ICustomer* cust) override {
        // Em ko nho ham remove trong vector nhung y tuong la duyet iterator de xoa
        for (auto i = customers.begin(); i != customers.end(); ++i) {
            if (*i == cust) {
                customers.erase(i);
            }
        }
    }

    void notifyCustomer(std::string message) override {
        for (ICustomer* i : customers) { // for each
            i->update(message);
        }
    }
};