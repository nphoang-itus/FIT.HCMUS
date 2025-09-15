public class Main {
  public static void main(String[] args) {
    BankAccount myAcc = new BankAccount("067202528", 1000000);
    myAcc.deposit(120000);
    System.out.println(myAcc);
    myAcc.withdraw(120000);
    System.out.println(myAcc);
  }
}
