#include "Account.h"
#include "User.h"
#include <iostream>

int main() {
    NormalUser* user1 = new NormalUser;
    std::vector<Account*> acc = {
        new BankAccount("Bank1", 1),
        new StockAccount("Stock1", 1, 1),
        new CryptoAccount("Crypto1", 1, 1.1),
        new BankAccount("Bank2", 1),
        new StockAccount("Stock2", 1, 1),
        new CryptoAccount("Crypto2", 1, 1.2)
    };

    for (auto& a : acc) {
        user1->addAccount(a);
    }

    user1->reportAccounts();
    user1->reportTotalValue();

    VipUser* user2 = new VipUser;
    std::vector<Account*> acc2 = {
        new BankAccount("Bank1", 1),
        new StockAccount("Stock1", 1, 1),
        new CryptoAccount("Crypto1", 1, 1.1),
        new BankAccount("Bank2", 1),
        new StockAccount("Stock2", 1, 1),
        new CryptoAccount("Crypto2", 1, 1.2)
    };

    for (auto& a : acc2) {
        user2->addAccount(a);
    }

    user2->reportTotalValueByTypes();

    delete user2;
    delete user1;
    return 0;
}