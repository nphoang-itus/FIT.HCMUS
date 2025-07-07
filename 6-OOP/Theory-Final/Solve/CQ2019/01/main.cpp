#include <iostream>
#include <string>

class ArmstrongNum {
private:
    int n;
    int format(const int& n) {
        int res = n;
        do {
            if (isArmstrongNum(res))
                break;
        } while (res++);
        return res;
    }
    bool isArmstrongNum(const int& val) const {
        std::string strNum = std::to_string(val);
        int exp = strNum.size();
        int sum = 0;
        for (int i = 0; i < exp; ++i) {
            sum += std::pow(strNum[i] - '0', exp);
        }
        return val == sum;
    }
public:
    ArmstrongNum() : n(1) {}
    ArmstrongNum(const int& val) : n(format(val)) { }
    friend std::ostream& operator<<(std::ostream& os, const ArmstrongNum& other) {
        return os << other.n;
    }
    friend std::istream& operator>>(std::istream& is, ArmstrongNum& other) {
        int val = 0;
        is >> val;
        other.n = other.format(val);
        return is;
    }
    ArmstrongNum& operator=(const ArmstrongNum& other) {
        if (this != &other) {
            this->n = other.n;
        }
        return *this;
    }
    ArmstrongNum& operator++() {
        this->n = this->format(this->n + 1);
        return *this;
    }
    ArmstrongNum operator++(int) {
        ArmstrongNum temp = *this;
        ++(*this);
        return temp;
    }
    bool operator==(const ArmstrongNum& other) const {
        return this->n == other.n;
    }
};

int main() {
	ArmstrongNum a;	//Khởi tạo mặc định số Armstrong nhỏ nhất.
	std::cin >> a;	//Nhập giá trị a từ bàn phím, nếu không phải số //Armstrong thì chuyển a về số Armstrong lớn hơn //gần nhất.
	std::cout << a;	//In số Armstrong a ra màn hình.
	
	ArmstrongNum b = a;
	++b;	//tăng b lên số Armstrong gần nhất.
	a = b++;
	
	if(a == b)
	   std::cout << a << " bang " << b << std::endl;
    else
	   std::cout << a << " khac " << b << std::endl;

    return 0;
}