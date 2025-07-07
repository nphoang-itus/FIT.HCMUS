#include <iostream>
#include <string>
#include <vector>

class IAsset;
class BankAccount;
class RealEstate;
class Stock;
class TaxCalculatorVisitor;

class IVisitor {
public:
    virtual ~IVisitor() = default;
};

class IAsset {
public:
    virtual ~IAsset() = default;
    virtual void accept(IVisitor* visitor) = 0;
};

class BankAccount : public IAsset {
private:
    double _balance;
public:
    BankAccount(double balance) : _balance(balance) {}

    void accept(IVisitor* visitor) override;

    friend class TaxCalculatorVisitor;
};

class RealEstate : public IAsset {
private:
    double _estimatedValue;
    std::string _location;
public:
    RealEstate(double estimatedValue, std::string location) : _estimatedValue(estimatedValue) , _location(location) {}

    void accept(IVisitor* visitor) override;

    friend class TaxCalculatorVisitor;
};

class Stock : public IAsset {
private:
    int _numberOfShares;
    double _sharePrice;
public:
    Stock(int numberOfShares, double sharePrice) : _numberOfShares(numberOfShares) , _sharePrice(sharePrice) {}

    void accept(IVisitor* visitor) override;

    friend class TaxCalculatorVisitor;
};

class TaxCalculatorVisitor : public IVisitor {
private:
    double _totalTax;
public:
    TaxCalculatorVisitor() : _totalTax(0) {}

    void calcTax(BankAccount* account) {
        _totalTax += account->_balance * 0.05;
    }

    void calcTax(RealEstate* property) {
        _totalTax += property->_estimatedValue * 0.1;
    }

    void calcTax(Stock* stock) {
        _totalTax += stock->_numberOfShares * stock->_sharePrice * 0.07;
    }

    double getTotalTax() const {
        return _totalTax;
    }
};

void BankAccount::accept(IVisitor* visitor) {
    dynamic_cast<TaxCalculatorVisitor*>(visitor)->calcTax(this);
}

void RealEstate::accept(IVisitor* visitor) {
    dynamic_cast<TaxCalculatorVisitor*>(visitor)->calcTax(this);
}

void Stock::accept(IVisitor* visitor) {
    dynamic_cast<TaxCalculatorVisitor*>(visitor)->calcTax(this);
}

int main() {
    std::vector<IAsset*> assets = {
        new BankAccount(12000.0),
        new BankAccount(5000.0),
        new BankAccount(3123123.2),
        new RealEstate(30000, "123/12 Linh Chieu, Thu Duc, TP.HCM"),
        new Stock(153, 12.000),
    };

    TaxCalculatorVisitor calcTax;
    // tính toán
    for (auto a : assets) {
        a->accept(&calcTax);
        delete a;
    }

    std::cout << "Total tax: " << calcTax.getTotalTax() << "\n";

    return 0;
}