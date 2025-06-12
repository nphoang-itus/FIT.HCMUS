#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <iostream>

class Account {
private:
    virtual void _printAccount(std::ostream& os) const = 0;

public:
    virtual ~Account() = default;
    virtual int value() = 0;
    virtual std::string name() const = 0;

    friend std::ostream& operator<<(std::ostream& os, const Account& acc) {
        acc._printAccount(os);
        return os;
    }
};

class BankAccount : public Account {
private:
    std::string _bankName;
    int _balance;

    void _printAccount(std::ostream& os) const override {
        os << "Bank Name: " << _bankName << ", Balance: " << _balance;
    }
public:
    BankAccount() = default;
    BankAccount(std::string bankName, int balance) : _bankName(bankName), _balance(balance) {}

    int value() override {
        return _balance;
    };

    std::string name() const override {
        return "Bank Account";
    }
};

class StockAccount : public Account {
private:
    std::string _stockSymbol;
    int _amount;
    int _price;

    void _printAccount(std::ostream& os) const override {
        os << "Stock Symbol: " << _stockSymbol << ", Amount: " << _amount << ", Price: " << _price;
    }
public:
    StockAccount() = default;
    StockAccount(std::string stockSymbol, int amount, int price) : _stockSymbol(stockSymbol),  _amount(amount), _price(price) {}

    int value() override {
        return _amount * _price;
    };

    std::string name() const override {
        return "Stock Account";
    }
};

class CryptoAccount : public Account {
private:
    std::string _tokenName;
    int _amount;
    double _exchangeRate;

    void _printAccount(std::ostream& os) const override {
        os << "Token Name: " << _tokenName << ", Amount: " << _amount << ", Exchange Rate: " << _exchangeRate;
    }
public:
    CryptoAccount() = default;
    CryptoAccount (std::string tokenName, int amount, double exchangeRate) : _tokenName(tokenName), _amount(amount), _exchangeRate(exchangeRate) {}

    int value() override {
        return _amount * _exchangeRate;
    };

    std::string name() const override {
        return "Crypto Account";
    }
};

#endif