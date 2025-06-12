#ifndef USER_H
#define USER_H

#include "Account.h"
#include <vector>
#include <map>

class NormalUser {
protected:
    std::vector<Account*> _accounts;
public:
    virtual ~NormalUser() {
        for (auto& a : _accounts) {
            delete a;
        }
    }

    virtual void addAccount(Account* info) {
        if (_accounts.size() <= 10) {
            _accounts.push_back(info);
        } else {
            std::cout << "Quá 10 tài khoản rồi, nạp tiền đi rồi cho thêm.\n";
        }
    }

    void reportAccounts() const {
        for (const auto a : _accounts) {
            std::cout << *a << "\n";
        }
    }

    void reportTotalValue() const {
        std::cout << "Total accounts:" << _accounts.size() << "\n";

        for(int i = 0; i < _accounts.size(); i++) {
            std::cout << _accounts[i]->name() << ": " << _accounts[i]->value() << "\n";
        }
    }
};

class VipUser : public NormalUser {
public:
    void addAccount(Account* info) override {
        _accounts.push_back(info);
    }

    void reportTotalValueByTypes() {
        // // Cách 1: Logic đơn giản
        // std::vector<Account*> prototypes = {
        //     new BankAccount(),
        //     new StockAccount(),
        //     new CryptoAccount()
        // };

        // std::vector<int> sums = {0, 0, 0};

        // for (int i = 0; i < _accounts.size(); ++i) {
        //     for (int j = 0; j < prototypes.size(); ++j) {
        //         if (_accounts[i]->name() == prototypes[j]->name()) {
        //             sums[j] += _accounts[i]->value();
        //         }
        //     }
        // }

        // std::cout << "Bank Account Value: " << sums[0] << "\n";
        // std::cout << "Stock Account Value: " << sums[1] << "\n";
        // std::cout << "Crypto Account Value: " << sums[2] << "\n";

        // // Cách 2: Dùng dynamic_cast
        // std::vector<int> sums = {0, 0, 0};

        // for (int i = 0; i < _accounts.size(); ++i) {
        //     int index = -1;
        //     if (dynamic_cast<BankAccount*>(_accounts[i])) {
        //         index = 0;
        //     } else if (dynamic_cast<StockAccount*>(_accounts[i])) {
        //         index = 1;
        //     } else if (dynamic_cast<CryptoAccount*>(_accounts[i])) {
        //         index = 2;
        //     }

        //     sums[index] += _accounts[i]->value();
        // }

        // std::cout << "Bank Account Value: " << sums[0] << "\n";
        // std::cout << "Stock Account Value: " << sums[1] << "\n";
        // std::cout << "Crypto Account Value: " << sums[2] << "\n";

        // Cách 3: dùng map
        std::map<std::string, int> typeSum;

        for (const auto& acc : _accounts) {
            typeSum[acc->name()] += acc->value();
        }

        std::cout << "Bank Account Value: " << typeSum["Bank Account"] << "\n";
        std::cout << "Stock Account Value: " << typeSum["Stock Account"] << "\n";
        std::cout << "Crypto Account Value: " << typeSum["Crypto Account"] << "\n";
    }
};

#endif