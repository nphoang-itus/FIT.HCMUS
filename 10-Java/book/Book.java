package book;
public class Book {
  private String _title;
  private String _author;
  private double _price;

  public Book(String title, String author, double price) {
    _title = title;
    _author = author;
    _price = price;
  }

  public void printInfo() {
    System.out.println("Title: " + _title + ", Author: " + _author + ", Price: " + _price);
  }
}