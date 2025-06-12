#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cmath>

// Custom exception classes
class BanhException : public std::exception {
protected:
    int errorCode;
    std::string description;
    std::string message;

public:
    BanhException(int code, const std::string& desc) 
        : errorCode(code), description(desc) {
        message = "Loi " + std::to_string(code) + ": " + desc;
    }
    
    virtual const char* what() const noexcept override {
        return message.c_str();
    }
    
    int getErrorCode() const { return errorCode; }
    const std::string& getDescription() const { return description; }
};

class NullReferenceException : public BanhException {
public:
    NullReferenceException(const std::string& desc) : BanhException(1001, desc) {};
};

class IndexOutOfRangeException : public BanhException {
public:
    IndexOutOfRangeException(const std::string& desc) : BanhException(2001, desc) {};
};

class FileNotFoundException : public BanhException {
public:
    FileNotFoundException(const std::string& desc) : BanhException(3001, desc) {};
};

class InvalidDataException : public BanhException {
public:
    InvalidDataException(const std::string& desc) : BanhException(4001, desc) {};
};

class INguyenLieu {
protected:
    std::string tenNguyenLieu;

public:
    INguyenLieu(const std::string& ten) : tenNguyenLieu(ten) {}
    virtual ~INguyenLieu() {}
    
    virtual double tinhKhoiLuong() const = 0;
    virtual double tinhHamLuongBeo() const = 0;
    virtual double tinhLuongDuong() const = 0;
    virtual void hienThiThongTin(std::ostream& os, int indentLevel = 0) const = 0;
    virtual std::string layTen() const { return tenNguyenLieu; }
    virtual std::string layLoaiNguyenLieu() const = 0;
    virtual void themNguyenLieuCon(INguyenLieu* nguyenLieuCon) { 
        throw InvalidDataException("Cannot add sub-ingredient to this type of ingredient"); 
    }
    virtual int demSoLuongNguyenLieuDon() const { return 0; }
    
    friend std::ostream& operator<<(std::ostream& os, const INguyenLieu& nl) {
        nl.hienThiThongTin(os, 0);
        return os;
    }
};

class NguyenLieuDon : public INguyenLieu {
private:
    double khoiLuong;
    double hamLuongBeo;
    double luongDuong;

public:
    NguyenLieuDon(const std::string& ten, double kl, double hlb, double ld) 
        : INguyenLieu(ten), khoiLuong(kl), hamLuongBeo(hlb), luongDuong(ld) {}
    
    double tinhKhoiLuong() const override {
        return khoiLuong;
    }
    
    double tinhHamLuongBeo() const override {
        return hamLuongBeo;
    }
    
    double tinhLuongDuong() const override {
        return luongDuong;
    }
    
    void hienThiThongTin(std::ostream& os, int indentLevel = 0) const override {
        std::string indent(indentLevel * 2, ' ');
        os << indent << "NguyenLieuDon - " << tenNguyenLieu << std::endl;
        os << indent << "Khoi luong: " << std::fixed << std::setprecision(3) << khoiLuong 
           << ", Ham luong beo: " << hamLuongBeo 
           << ", Luong duong: " << luongDuong << std::endl;
    }
    
    std::string layLoaiNguyenLieu() const override {
        return "NguyenLieuDon";
    }
};

class NguyenLieuHonHop : public INguyenLieu {
protected:
    std::vector<INguyenLieu*> danhSachNguyenLieuCon;

public:
    NguyenLieuHonHop(const std::string& ten) : INguyenLieu(ten) {}
    
    virtual ~NguyenLieuHonHop() {
        // Memory management handled by QuanLyBanh
    }
    
    void themNguyenLieuCon(INguyenLieu* nguyenLieuCon) override {
        if (nguyenLieuCon) {
            danhSachNguyenLieuCon.push_back(nguyenLieuCon);
        }
    }
    
    int demSoLuongNguyenLieuDon() const override {
        int count = 0;
        for (const INguyenLieu* nl : danhSachNguyenLieuCon) {
            if (nl->layLoaiNguyenLieu() == "NguyenLieuDon") {
                count++;
            } else {
                count += nl->demSoLuongNguyenLieuDon();
            }
        }
        return count;
    }
    
    void hienThiThongTin(std::ostream& os, int indentLevel = 0) const override {
        std::string indent(indentLevel * 2, ' ');
        os << indent << layLoaiNguyenLieu() << " - " << tenNguyenLieu << std::endl;
        os << indent << "Khoi luong: " << std::fixed << std::setprecision(3) << tinhKhoiLuong() 
           << ", Ham luong beo: " << tinhHamLuongBeo() 
           << ", Luong duong: " << tinhLuongDuong() << std::endl;
        for (const INguyenLieu* nl : danhSachNguyenLieuCon) {
            nl->hienThiThongTin(os, indentLevel + 1);
        }
    }
    
    const std::vector<INguyenLieu*>& layDanhSachNguyenLieuCon() const {
        return danhSachNguyenLieuCon;
    }
};

class NguyenLieuHonHopDac : public NguyenLieuHonHop {
public:
    NguyenLieuHonHopDac(const std::string& ten) : NguyenLieuHonHop(ten) {}
    
    double tinhKhoiLuong() const override {
        double tongKhoiLuong = 0;
        for (const INguyenLieu* nl : danhSachNguyenLieuCon) {
            tongKhoiLuong += nl->tinhKhoiLuong();
        }
        return tongKhoiLuong;
    }
    
    double tinhHamLuongBeo() const override {
        double tongBeo = 0;
        for (const INguyenLieu* nl : danhSachNguyenLieuCon) {
            tongBeo += nl->tinhHamLuongBeo();
        }
        return tongBeo * 0.4; // 40% dissolution rate
    }
    
    double tinhLuongDuong() const override {
        double tongDuong = 0;
        for (const INguyenLieu* nl : danhSachNguyenLieuCon) {
            tongDuong += nl->tinhLuongDuong();
        }
        return tongDuong * 0.4; // 40% dissolution rate
    }
    
    std::string layLoaiNguyenLieu() const override {
        return "NguyenLieuHonHopDac";
    }
};

class NguyenLieuHonHopLong : public NguyenLieuHonHop {
public:
    NguyenLieuHonHopLong(const std::string& ten) : NguyenLieuHonHop(ten) {}
    
    double tinhKhoiLuong() const override {
        double tongKhoiLuong = 0;
        for (const INguyenLieu* nl : danhSachNguyenLieuCon) {
            tongKhoiLuong += nl->tinhKhoiLuong();
        }
        return tongKhoiLuong * 1.25; // Increase by 25% due to liquidity
    }
    
    double tinhHamLuongBeo() const override {
        double tongBeo = 0;
        for (const INguyenLieu* nl : danhSachNguyenLieuCon) {
            tongBeo += nl->tinhHamLuongBeo();
        }
        return tongBeo;
    }
    
    double tinhLuongDuong() const override {
        double tongDuong = 0;
        for (const INguyenLieu* nl : danhSachNguyenLieuCon) {
            tongDuong += nl->tinhLuongDuong();
        }
        return tongDuong;
    }
    
    std::string layLoaiNguyenLieu() const override {
        return "NguyenLieuHonHopLong";
    }
};

class QuanLyBanh {
private:
    std::string tenBanh;
    std::vector<INguyenLieu*> danhSachTatCaNguyenLieu;
    std::vector<INguyenLieu*> danhSachNguyenLieuGoc;

public:
    ~QuanLyBanh() {
        for (INguyenLieu* nl : danhSachTatCaNguyenLieu) {
            delete nl;
        }
    }
    
    void themNguyenLieu(INguyenLieu* nguyenLieu) {
        if (nguyenLieu) {
            danhSachTatCaNguyenLieu.push_back(nguyenLieu);
        }
    }
    
    INguyenLieu* timNguyenLieuTheoTen(const std::string& ten) const {
        for (INguyenLieu* nl : danhSachTatCaNguyenLieu) {
            if (nl->layTen() == ten) {
                return nl;
            }
        }
        return nullptr;
    }
    
    void napDuLieuTuFile(const std::string& tenFile) {
        std::ifstream file(tenFile);
        if (!file.is_open()) {
            throw FileNotFoundException("Cannot open file: " + tenFile);
        }
        
        std::string line;
        std::vector<std::string> usedIngredients;
        std::vector<INguyenLieu*> complexIngredientStack;
        
        // Read cake name
        if (std::getline(file, line)) {
            tenBanh = line;
        }
        
        while (std::getline(file, line)) {
            if (line.empty()) continue;
            
            if (line.find(" (") == std::string::npos) {
                // This is either an end marker or a reference to existing ingredient
                bool isEndMarker = false;
                
                for (int i = complexIngredientStack.size() - 1; i >= 0; i--) {
                    if (line == complexIngredientStack[i]->layTen()) {
                        INguyenLieu* completedIngredient = complexIngredientStack[i];
                        complexIngredientStack.erase(complexIngredientStack.begin() + i);
                        
                        if (!complexIngredientStack.empty()) {
                            complexIngredientStack.back()->themNguyenLieuCon(completedIngredient);
                            usedIngredients.push_back(line);
                        }
                        
                        isEndMarker = true;
                        break;
                    }
                }
                
                if (!isEndMarker) {
                    if (!complexIngredientStack.empty()) {
                        INguyenLieu* subIngredient = timNguyenLieuTheoTen(line);
                        if (subIngredient) {
                            complexIngredientStack.back()->themNguyenLieuCon(subIngredient);
                            usedIngredients.push_back(line);
                        } else {
                            throw IndexOutOfRangeException("Ingredient not found: " + line);
                        }
                    }
                }
                continue;
            }
            
            // Parse ingredient definition
            size_t openParen = line.find(" (");
            size_t closeParen = line.find(")");
            
            if (openParen == std::string::npos || closeParen == std::string::npos) {
                throw InvalidDataException("Cannot parse line: " + line);
            }
            
            std::string loaiNguyenLieu = line.substr(0, openParen);
            std::string tenNguyenLieu = line.substr(openParen + 2, closeParen - openParen - 2);
            
            if (loaiNguyenLieu == "NguyenLieuDon" || 
                loaiNguyenLieu == "NguyenLieuHonHopDac" || 
                loaiNguyenLieu == "NguyenLieuHonHopLong") {
                
                // Read the three value lines that follow every ingredient definition
                std::string khoiLuongLine, hamLuongBeoLine, luongDuongLine;
                if (!std::getline(file, khoiLuongLine) || 
                    !std::getline(file, hamLuongBeoLine) || 
                    !std::getline(file, luongDuongLine)) {
                    throw InvalidDataException("Missing value lines after ingredient definition");
                }
                
                INguyenLieu* nguyenLieu = nullptr;
                if (loaiNguyenLieu == "NguyenLieuDon") {
                    // For simple ingredients, parse and use the values
                    double khoiLuong = std::stod(khoiLuongLine);
                    double hamLuongBeo = std::stod(hamLuongBeoLine);
                    double luongDuong = std::stod(luongDuongLine);
                    nguyenLieu = new NguyenLieuDon(tenNguyenLieu, khoiLuong, hamLuongBeo, luongDuong);
                } else if (loaiNguyenLieu == "NguyenLieuHonHopDac") {
                    // For complex ingredients, ignore the values as they are calculated
                    nguyenLieu = new NguyenLieuHonHopDac(tenNguyenLieu);
                    complexIngredientStack.push_back(nguyenLieu);
                } else if (loaiNguyenLieu == "NguyenLieuHonHopLong") {
                    // For complex ingredients, ignore the values as they are calculated
                    nguyenLieu = new NguyenLieuHonHopLong(tenNguyenLieu);
                    complexIngredientStack.push_back(nguyenLieu);
                }
                
                themNguyenLieu(nguyenLieu);
            } else {
                throw InvalidDataException("Cannot parse line: " + line);
            }
        }
        
        // Determine root ingredients
        for (INguyenLieu* nl : danhSachTatCaNguyenLieu) {
            if (std::find(usedIngredients.begin(), usedIngredients.end(), nl->layTen()) == usedIngredients.end()) {
                danhSachNguyenLieuGoc.push_back(nl);
            }
        }
        
        file.close();
    }
    
    void hienThiThongTinBanh() const {
        std::cout << "=== THONG TIN BANH: " << tenBanh << " ===" << std::endl;
        for (const INguyenLieu* nl : danhSachNguyenLieuGoc) {
            std::cout << *nl << std::endl;
        }
    }
    
    double tinhTongKhoiLuong() const {
        double tong = 0;
        for (const INguyenLieu* nl : danhSachNguyenLieuGoc) {
            tong += nl->tinhKhoiLuong();
        }
        return tong;
    }
    
    double tinhTongHamLuongBeo() const {
        double tong = 0;
        for (const INguyenLieu* nl : danhSachNguyenLieuGoc) {
            tong += nl->tinhHamLuongBeo();
        }
        return tong;
    }
    
    double tinhTongLuongDuong() const {
        double tong = 0;
        for (const INguyenLieu* nl : danhSachNguyenLieuGoc) {
            tong += nl->tinhLuongDuong();
        }
        return tong;
    }
    
    INguyenLieu* timNguyenLieuHonHopChuaNhieuNguyenLieuDonNhat() const {
        INguyenLieu* ketQua = nullptr;
        int maxSoLuong = 0;
        
        for (INguyenLieu* nl : danhSachTatCaNguyenLieu) {
            if (nl->layLoaiNguyenLieu() != "NguyenLieuDon") {
                int soLuong = nl->demSoLuongNguyenLieuDon();
                if (soLuong > maxSoLuong) {
                    maxSoLuong = soLuong;
                    ketQua = nl;
                }
            }
        }
        return ketQua;
    }
    
    void lietKeNguyenLieuDonTrongNguyenLieuHonHop(const std::string& tenNguyenLieuHonHop) const {
        INguyenLieu* nguyenLieuHonHop = timNguyenLieuTheoTen(tenNguyenLieuHonHop);
        if (!nguyenLieuHonHop) {
            throw IndexOutOfRangeException("Ingredient not found: " + tenNguyenLieuHonHop);
        }
        if (nguyenLieuHonHop->layLoaiNguyenLieu() == "NguyenLieuDon") {
            throw InvalidDataException("Ingredient " + tenNguyenLieuHonHop + " is not a complex ingredient");
        }
        
        std::cout << "Cac nguyen lieu don trong " << tenNguyenLieuHonHop << ":" << std::endl;
        lietKeNguyenLieuDonRecursive(nguyenLieuHonHop, 1);
    }

private:
    void lietKeNguyenLieuDonRecursive(const INguyenLieu* nl, int level) const {
        if (nl->layLoaiNguyenLieu() == "NguyenLieuDon") {
            std::string indent(level * 2, ' ');
            std::cout << indent << "- " << nl->layTen() 
                     << " (KL: " << std::fixed << std::setprecision(3) << nl->tinhKhoiLuong()
                     << ", Beo: " << nl->tinhHamLuongBeo()
                     << ", Duong: " << nl->tinhLuongDuong() << ")" << std::endl;
        } else {
            const NguyenLieuHonHop* nlHonHop = dynamic_cast<const NguyenLieuHonHop*>(nl);
            if (nlHonHop) {
                const std::vector<INguyenLieu*>& subIngredients = nlHonHop->layDanhSachNguyenLieuCon();
                for (const INguyenLieu* subNl : subIngredients) {
                    lietKeNguyenLieuDonRecursive(subNl, level);
                }
            }
        }
    }
};

int main() {
    try {
        QuanLyBanh quanLy;
        
        quanLy.napDuLieuTuFile("banhData.txt");
        
        quanLy.hienThiThongTinBanh();
        
        std::cout << "\n=== THONG KE ===" << std::endl;
        std::cout << "Tong khoi luong: " << std::fixed << std::setprecision(3) 
                 << quanLy.tinhTongKhoiLuong() << " g" << std::endl;
        std::cout << "Tong ham luong beo: " << std::fixed << std::setprecision(3) 
                 << quanLy.tinhTongHamLuongBeo() << " g" << std::endl;
        std::cout << "Tong luong duong: " << std::fixed << std::setprecision(3) 
                 << quanLy.tinhTongLuongDuong() << " g" << std::endl;
        
        INguyenLieu* nlNhieuNhat = quanLy.timNguyenLieuHonHopChuaNhieuNguyenLieuDonNhat();
        if (nlNhieuNhat) {
            std::cout << "Nguyen lieu hon hop chua nhieu nguyen lieu don nhat: " << nlNhieuNhat->layTen() 
                     << " (" << nlNhieuNhat->demSoLuongNguyenLieuDon() << " nguyen lieu don)" << std::endl;
        }
        
        std::cout << "\n=== LIET KE NGUYEN LIEU DON ===" << std::endl;
        quanLy.lietKeNguyenLieuDonTrongNguyenLieuHonHop("NLHHL0200");
        quanLy.lietKeNguyenLieuDonTrongNguyenLieuHonHop("NLHHD0002");
        
    } catch (const BanhException& e) {
        std::cerr << "Banh Error [" << e.getErrorCode() << "]: " << e.getDescription() << std::endl;
        return e.getErrorCode();
    } catch (const std::exception& e) {
        std::cerr << "General Error: " << e.what() << std::endl;
        return 9999;
    }
    
    return 0;
}
