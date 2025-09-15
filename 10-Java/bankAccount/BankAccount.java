public class BankAccount {
  private String accountNumber;
  private double balance;

  public BankAccount(String accountNumber, double balance) {
    this.accountNumber = accountNumber;
    this.balance = (balance < 0) ? 0 : balance;
  }

  public double getBalance() {
    return balance;
  }

  public void deposit(double amount) {
    balance += amount;
  }

  public void withdraw(double amount) {
    if (amount > balance) {
      System.out.println("ko the rut tien");
      return;
    }

    balance -= amount;
  }

  public String toString() {
    return "Account Number: " + accountNumber + ", Balance: " + balance;
  }
}