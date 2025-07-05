#include <iostream>
#include <vector>
#include <string>
#include <format>

class Object {
public:
    virtual std::string toString() = 0;
};

class KhachHang : public Object {
private:
    std::string _ten;
    std::string _CMND;
    std::string _diaChi;
public:
    KhachHang(std::string ten, std::string CMND, std::string diaChi) : _ten(ten), _CMND(CMND), _diaChi(diaChi) {}
    std::string toString() override {
        return std::format(
            "ten=\"{}\",CMND=\"{}\",diaChi=\"{}\"",
            _ten, _CMND, _diaChi
        );
    }
};

class IGoiCuocLe : public Object {
public:
    virtual ~IGoiCuocLe() = default;
    virtual float tinhTien() = 0;
};

class CuocDienThoai : public IGoiCuocLe {
private:
    float _thoiGianGoi;
    const int DON_GIA_GOI = 1000;
public:
    std::string toString() override {
        return std::format(
            "thoiGianGoi=\"{}\",DON_GIA_GOI=\"{}\"",
            _thoiGianGoi, DON_GIA_GOI
        );
    }
};

class CuocInternet : public IGoiCuocLe {
private:
    float _luuLuongTruyCap;
    const int DON_GIA_TRUY_CAP = 200;
public:
    std::string toString() override {
        return std::format(
            "luuLuongTruyCap=\"{}\",DON_GIA_TRUY_CAP=\"{}\"",
            _luuLuongTruyCap, DON_GIA_TRUY_CAP
        );
    }
};

class IGoiCuoc{
protected:
    CuocDienThoai* cdt;
    CuocInternet* ci;
public:
    virtual float tinhCuocDienThoai() = 0;
    virtual float tinhCuocInternet() = 0;
    virtual float tinhTongCuoc() = 0;
};

class Basic : public IGoiCuoc {};

class DataFree : public IGoiCuoc {};
class DataFix : public IGoiCuoc {};

int main() {

    return 0;
}