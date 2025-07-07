#include <iostream>
#include <vector>

class TaiKhoan;
class GiaoDich;

class GiaoDich {
protected:
    int maGiaoDich;
    std::string ngayGiaoDich;
    float soTien;
    std::string trangThai;
public:
    virtual ~GiaoDich() = default;
    GiaoDich(int a, std::string b, float c) : maGiaoDich(a), ngayGiaoDich(b), soTien(c), trangThai("Chờ thực hiện") {}
    virtual void hoanTat(TaiKhoan* tk) = 0;
    virtual std::string getTrangThai() {
        return trangThai;
    }
};

class TaiKhoan {
private:
    int maTaiKhoan;
    int maKhachHang;
    std::string ngayMoTaiKhoan;
    float soDu;
public:
    std::vector<GiaoDich*> dsGiaoDich;
    ~TaiKhoan() {
        for (auto& x : dsGiaoDich)
            if (x) delete x;
    }

    TaiKhoan(int mtk, int mkh, std::string ngay, float sd) : maTaiKhoan(mtk), maKhachHang(mkh), ngayMoTaiKhoan(ngay), soDu(sd) {}

    void themGiaoDich(GiaoDich* gd) {
        // todo: check giao dich co hop ly ko (so du < so tien gd)
        dsGiaoDich.push_back(gd);
    }

    void setSoDu(float sd) {
        soDu = sd;
    }

    float getSoDu() {
        return soDu;
    }

    void khopLenh() {
        for (auto& x : dsGiaoDich) {
            if (x->getTrangThai() == "Chờ thực hiện") {
                x->hoanTat(this);
            }
        }
    }
};

class RutTienMat : public GiaoDich {
private:
    const float lePhi = 1000;
public:
    RutTienMat(int a, std::string b, float c) : GiaoDich(a, b, c) {}
    void hoanTat(TaiKhoan* tk) override {
        tk->setSoDu(tk->getSoDu() - soTien - lePhi);
        trangThai = "Thành công";
    }
};

class NapTienMat : public GiaoDich {
public:
    NapTienMat(int a, std::string b, float c) : GiaoDich(a, b, c) {}

    void hoanTat(TaiKhoan* tk) override {
        tk->setSoDu(tk->getSoDu() + soTien);
        trangThai = "Thành công";
    }
};

class ChuyenKhoan : public GiaoDich {
private:
    TaiKhoan* taiKhoanHuongThu;
public:
    ChuyenKhoan(int a, std::string b, float c, TaiKhoan* tkht) : GiaoDich(a, b, c), taiKhoanHuongThu(tkht) {}

    void hoanTat(TaiKhoan* tk) override {
        // tru tai khoan chuyen
        tk->setSoDu(tk->getSoDu() - soTien);
        // cong tai khoan huong
        taiKhoanHuongThu->setSoDu(taiKhoanHuongThu->getSoDu() + soTien);
        trangThai = "Thành công";
    }
};

class NganHang {
private:
    std::vector<TaiKhoan*> dsTaiKhoan;
public:

    ~NganHang() {
        for (auto& x : dsTaiKhoan)
            if (x) delete x;
    }

    void themTaiKhoan(TaiKhoan* tk) {
        dsTaiKhoan.push_back(tk);
    }

    void khopLenhToanBo() {
        for (auto& x : dsTaiKhoan) {
            x->khopLenh();
        }
    }
};

int main() {
    NganHang nh;
    TaiKhoan* tk = new TaiKhoan(1, 1, "07/07/2025", 12000);
    TaiKhoan* tkht = new TaiKhoan(2, 2, "07/07/2025", 19000);
    nh.themTaiKhoan(tk);
    nh.themTaiKhoan(tkht);

    tk->dsGiaoDich = {
        new RutTienMat(1, "07/07/2025", 8000),
        new NapTienMat(2, "07/07/2025", 80000),
        new ChuyenKhoan(1, "07/07/2025", 17000, tkht)
    };

    std::cout << tk->getSoDu() << "\n";
    std::cout << tkht->getSoDu() << "\n";

    nh.khopLenhToanBo();

    std::cout << tk->getSoDu() << "\n";
    std::cout << tkht->getSoDu() << "\n";

    return 0;
}