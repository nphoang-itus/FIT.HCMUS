#ifndef HINH_H
#define HINH_H

#include <iostream>
#include <cmath>

class Hinh {
protected:
    virtual void _in(std::ostream& os) const = 0;
public:
    virtual ~Hinh() = default;

    friend std::ostream& operator<<(std::ostream& os, const Hinh& hinh) {
        hinh._in(os);
        return os;
    }
};

class Hinh2D : public Hinh {
protected:
    virtual void _in(std::ostream& os) const override = 0;
public:
    virtual double tinhChuVi() const = 0;
    virtual double tinhDienTich() const = 0;
};

class HinhTron : public Hinh2D {
private:
    double _banKinh;
    
public:
    static const double PI;

    HinhTron(const float& banKinh) : _banKinh(banKinh) {}

    double tinhChuVi() const override { return 2 * PI * _banKinh; };
    double tinhDienTich() const override { return PI * _banKinh * _banKinh; };
    
    void _in(std::ostream& os) const override {
        os << "Hinh Tron [P = " << tinhChuVi() << ", S = " << tinhDienTich() << "]";
    }
};

const double HinhTron::PI = 3.1414;

class HinhTamGiacDeu : public Hinh2D {
private:
    double _canh;

public:
    HinhTamGiacDeu(const float& canh) : _canh(canh) {}

    double tinhChuVi() const override { return 3 * _canh; };
    double tinhDienTich() const override { return (std::sqrt(3)/4) * _canh * _canh; };
    
    void _in(std::ostream& os) const override {
        os << "Hinh Tam Giac Deu [P = " << tinhChuVi() << ", S = " << tinhDienTich() << "]";
    }
};

class HinhChuNhat : public Hinh2D {
private:
    double _chieuDai;
    double _chieuRong;

public:
    HinhChuNhat(const float& chieuDai, const float& chieuRong) : _chieuDai(chieuDai), _chieuRong(chieuRong) {}

    double tinhChuVi() const override { return 2 * (_chieuDai + _chieuRong); };
    double tinhDienTich() const override { return _chieuDai * _chieuRong; };
    
    void _in(std::ostream& os) const override {
        os << "Hinh Chu Nhat [P = " << tinhChuVi() << ", S = " << tinhDienTich() << "]";
    }
};

class HinhVuong : public Hinh2D {
private:
    double _canh;

public:
    HinhVuong(const float& canh) : _canh(canh) {}

    double tinhChuVi() const override { return 4 * _canh; };
    double tinhDienTich() const override { return _canh * _canh; };
    
    void _in(std::ostream& os) const override {
        os << "Hinh Vuong [P = " << tinhChuVi() << ", S = " << tinhDienTich() << "]";
    }
};

class Hinh3D : public Hinh {
protected:
    virtual void _in(std::ostream& os) const override = 0;
public:
    virtual double tinhSXungQuanh() const = 0;
    virtual double tinhTheTich() const = 0;
};

class HinhCau : public Hinh3D {
private:
    double _banKinh;

public:
    HinhCau(const float& banKinh) : _banKinh(banKinh) {}

    double tinhSXungQuanh() const override { return 4 * HinhTron::PI * _banKinh * _banKinh; };
    double tinhTheTich() const override { return (4.0 / 3) * HinhTron::PI * std::pow(_banKinh, 3); };
    
    void _in(std::ostream& os) const override {
        os << "Hinh Cau [Sxq = " << tinhSXungQuanh() << ", V = " << tinhTheTich() << "]";
    }
};

class HinhLapPhuong : public Hinh3D {
private:
    double _canh;

public:
    HinhLapPhuong(const float& canh) : _canh(canh) {}

    double tinhSXungQuanh() const override { return 4 * _canh * _canh; };
    double tinhTheTich() const override { return _canh * _canh * _canh; };
    
    void _in(std::ostream& os) const override {
        os << "Hinh Lap Phuong [Sxq = " << tinhSXungQuanh() << ", V = " << tinhTheTich() << "]";
    }
};

class HinhHop : public Hinh3D {
private:
    double _chieuDai;
    double _chieuRong;
    double _chieuCao;

public:
    HinhHop(const float& chieuDai, const float& chieuRong, const float& chieuCao) : _chieuDai(chieuDai), _chieuRong(chieuRong), _chieuCao(chieuCao) {}

    double tinhSXungQuanh() const override { return 2 * (_chieuDai + _chieuRong) * _chieuCao; };
    double tinhTheTich() const override { return _chieuDai * _chieuRong * _chieuCao; };
    
    void _in(std::ostream& os) const override {
        os << "Hinh Hop [Sxq = " << tinhSXungQuanh() << ", V = " << tinhTheTich() << "]";
    }
};

class HinhTru : public Hinh3D {
private:
    double _banKinhDay;
    double _chieuRong;

public:
    HinhTru(const float& banKinhDay, const float& chieuRong) : _banKinhDay(banKinhDay), _chieuRong(chieuRong) {}

    double tinhSXungQuanh() const override { return 2 * HinhTron::PI * _banKinhDay * _chieuRong; };
    double tinhTheTich() const override { return _chieuRong * HinhTron::PI * _banKinhDay * _banKinhDay; };
    
    void _in(std::ostream& os) const override {
        os << "Hinh Tru [Sxq = " << tinhSXungQuanh() << ", V = " << tinhTheTich() << "]";
    }
};

class HinhNon : public Hinh3D {
private:
    double _duongSinh;
    double _banKinhDay;

public:
    HinhNon(const float& duongSinh, const float& banKinhDay) : _duongSinh(duongSinh), _banKinhDay(banKinhDay) {}

    double tinhSXungQuanh() const override { return HinhTron::PI * _banKinhDay * _duongSinh; };
    double tinhTheTich() const override { return (1.0/3) * HinhTron::PI * _banKinhDay * _banKinhDay * (std::sqrt(_duongSinh * _duongSinh - _banKinhDay * _banKinhDay)); };
    
    void _in(std::ostream& os) const override {
        os << "Hinh Non [Sxq = " << tinhSXungQuanh() << ", V = " << tinhTheTich() << "]";
    }
};

#endif
