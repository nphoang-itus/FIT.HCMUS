```mermaid
classDiagram
    Account <|.. BankAccount
    Account <|.. StockAccount
    Account <|.. CryptoAccount

    class Account {
        + virtual value(): int = 0
    }
    class BankAccount {
        - bankName: string
        - balance: int
        + override value(): int
    }
    class StockAccount {
        - stockSymbol: string
        - amount: int
        - price: int
        + override value(): int
    }
    class CryptoAccount {
        - tokenName: string
        - amount: int
        - exchangeRate: double
        + override value(): int
    }

    NormalUser <|.. VipUser
    class NormalUser {
        # account: vector~Vector*~
        + virtual addAccount(Account* info): void
        + reportAccounts(): void
        + reportTotalValue(): void
    }

    class VipUser {
        + override addAccount(Account* info): void
        + reportTotalValueByTypes(Account* type): void
    }
```