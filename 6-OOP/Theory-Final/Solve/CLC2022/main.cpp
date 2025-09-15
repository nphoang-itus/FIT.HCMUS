#include <iostream>
#include <cstring>

struct Base {
  Base(const char *s) { m_str = strdup(s); }
  Base(const Base &b) { m_str = strdup(b.m_str); }
  ~Base() { 
    std::cout << "~" << m_str << "\n"; 
    delete []m_str; 
  }
  Base & operator =(const Base &b) {
    std::cout << m_str << " = " << b.m_str << "\n";
    Base tmp(b);
    std::swap(m_str, tmp.m_str);
    return *this;
  }
private:
  char *m_str;
};

struct Derive: public Base {
  Derive(const char *s): Base(s) {}
};
int main() {
  Derive d1("hello");
  Derive d2("world");
  d1 = d1;			// Assign to itself.
  d2 = d1;
}
