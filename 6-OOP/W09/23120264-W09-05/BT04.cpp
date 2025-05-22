#include <vector>
#include <iostream>
#include <string>
#include <sstream>

class ChiTietMay;
class ChiTietDon;
class ChiTietPhuc;
class CoMay;

class ChiTietMay {
protected:
    std::string _ten;

    virtual void Print(std::ostream& os) const = 0;

public:
    virtual ~ChiTietMay() = default;
    ChiTietMay(const std::string& ten) : _ten(ten) {};

    virtual int TrongLuongCT() const = 0;
    virtual int GiaThanhCT() const = 0;

    friend std::ostream& operator<<(std::ostream& os, const ChiTietMay& ctMay) {
        ctMay.Print(os);
        return os;
    }
};

class ChiTietPhuc : public ChiTietMay {
private:
    std::vector<ChiTietMay*> _dsChiTietMay;
    void Print(std::ostream& os) const override {
        os << "Chi Tiet Phuc (" << _ten << ")" << "\n";
        for (const auto& x : _dsChiTietMay) {
            std::string output;
            std::stringstream ss;
            ss << *x;
            while (std::getline(ss, output)) {
                os << "  " << output << "\n";
            }
        }
    }

public:
    ChiTietPhuc(const std::string& ten) : ChiTietMay(ten) {}

    ~ChiTietPhuc() {
        for (auto x : _dsChiTietMay) {
            delete x;
        }
    }

    void ThemChiTiet(ChiTietMay* ctMay) {
        _dsChiTietMay.push_back(ctMay);
    }

    int TrongLuongCT() const override {
        int result = 0;

        for (const auto& x : _dsChiTietMay) {
            result += x->TrongLuongCT();
        }

        // Như trong đề ko nói rõ trọng lượng phụ kiện kết nối là gì nên em mặc định là 10% tổng trọng lượng các chi tiết con.
        result += 0.1 * result;

        return result;
    }

    int GiaThanhCT() const override {
        int result = 0;

        for (const auto& x : _dsChiTietMay) {
            result += x->GiaThanhCT();
        }

        // Như trong đề ko nói rõ giá thành phụ kiện kết nối là gì nên em mặc định là 10% tổng giá thành các chi tiết con.
        result += 0.2 * result;

        return result;
    }
};

class ChiTietDon : public ChiTietMay {
private:
    int _trongLuong;
    int _giaThanh;

    void Print(std::ostream& os) const override {
        os << "Chi Tiet Don (" << _ten << ": " << _trongLuong << ", " << _giaThanh << ")\n";
    }
public:
    ChiTietDon(const std::string& ten, const int& trongLuong, const int& giaThanh) : ChiTietMay(ten), _trongLuong(trongLuong), _giaThanh(giaThanh) {}

    int TrongLuongCT() const override {
        return _trongLuong;
    }

    int GiaThanhCT() const override {
        return _giaThanh;
    }
};

class CoMay {
private:
    std::vector<ChiTietMay*> _dsChiTietMay;
    void Print(std::ostream& os) const {
        for (const auto& x : _dsChiTietMay) {
            os << *x;
        }
    }

public:
    ~CoMay() {
        for (auto x : _dsChiTietMay) {
            delete x;
        }
    }

    void ThemChiTietMay(ChiTietMay* ctMay) {
        _dsChiTietMay.push_back(ctMay);
    }

    int TrongLuong() const {
        int result = 0;

        for (const auto& x : _dsChiTietMay) {
            result += x->TrongLuongCT();
        }

        return result;
    }

    int GiaThanh() const {
        int result = 0;

        for (const auto& x : _dsChiTietMay) {
            result += x->GiaThanhCT();
        }

        return result;
    }

    friend std::ostream& operator<<(std::ostream& os, const CoMay& coMay) {
        coMay.Print(os);
        return os;
    }
};

int main() {
    CoMay* pcm = new CoMay();
    pcm->ThemChiTietMay(new ChiTietDon("CTD001", 120, 350000));
    
    ChiTietMay* pctm = new ChiTietPhuc("CTP001");
    ((ChiTietPhuc*)pctm)->ThemChiTiet(new ChiTietDon("CTD002", 50, 1280000));
    ((ChiTietPhuc*)pctm)->ThemChiTiet(new ChiTietDon("CTD003", 20, 10000));

    ChiTietMay* pctm1 = new ChiTietPhuc("CTP002");
    ((ChiTietPhuc*)pctm1)->ThemChiTiet(new ChiTietDon("CTD004", 80, 170000));

    ((ChiTietPhuc*)pctm)->ThemChiTiet(pctm1);

    pcm->ThemChiTietMay(pctm);
    pcm->ThemChiTietMay(new ChiTietDon("CTD005", 210, 2350000));
    pcm->ThemChiTietMay(new ChiTietDon("CTD006", 40, 50000));

    std::cout << "Thong tin co may\n" << *pcm << "\n";
    std::cout << "Trong luong: " << pcm->TrongLuong() << "\n";
    std::cout << "Gia thanh: " << pcm->GiaThanh() << "\n";

    std::cout << "\n\n";
    return 0;
}