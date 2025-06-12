#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cmath>

// Custom exception classes
class BoMachException : public std::exception {
protected:
    int errorCode;
    std::string description;
    std::string message;

public:
    BoMachException(int code, const std::string& desc) 
        : errorCode(code), description(desc) {
        message = "Error " + std::to_string(code) + ": " + desc;
    }
    
    virtual const char* what() const noexcept override {
        return message.c_str();
    }
    
    int getErrorCode() const { return errorCode; }
    const std::string& getDescription() const { return description; }
};

class FileException : public BoMachException {
public:
    FileException(const std::string& filename) 
        : BoMachException(1001, "Cannot open file: " + filename) {}
};

class InvalidCircuitException : public BoMachException {
public:
    InvalidCircuitException(const std::string& circuitId) 
        : BoMachException(2001, "Invalid circuit operation for: " + circuitId) {}
};

class CircuitNotFoundException : public BoMachException {
public:
    CircuitNotFoundException(const std::string& circuitId) 
        : BoMachException(2002, "Circuit not found: " + circuitId) {}
};

class ParseException : public BoMachException {
public:
    ParseException(const std::string& line) 
        : BoMachException(3001, "Cannot parse line: " + line) {}
};

class DivisionByZeroException : public BoMachException {
public:
    DivisionByZeroException() 
        : BoMachException(4001, "Division by zero in parallel resistance calculation") {}
};

class IMachDien {
protected:
    std::string maSo;
    long triGia;

public:
    IMachDien(const std::string& maSo, long triGia) : maSo(maSo), triGia(triGia) {}
    virtual ~IMachDien() {}
    
    virtual double tinhDienTro() const = 0;
    virtual long layTriGia() const { return triGia; }
    virtual void hienThiThongTin(std::ostream& os, int indentLevel = 0) const = 0;
    virtual std::string layMaSo() const { return maSo; }
    virtual std::string layLoaiMach() const = 0;
    virtual void themMachCon(IMachDien* machCon) { 
        throw InvalidCircuitException("Cannot add sub-circuit to this type of circuit"); 
    }
    virtual int demSoLuongMachCon() const { return 0; }
    
    friend std::ostream& operator<<(std::ostream& os, const IMachDien& md) {
        md.hienThiThongTin(os, 0);
        return os;
    }
};

class MachDon : public IMachDien {
private:
    double dienTroRieng;

public:
    MachDon(const std::string& maSo, long triGia, double dienTroRieng) 
        : IMachDien(maSo, triGia), dienTroRieng(dienTroRieng) {}
    
    double tinhDienTro() const override {
        return dienTroRieng;
    }
    
    void hienThiThongTin(std::ostream& os, int indentLevel = 0) const override {
        std::string indent(indentLevel * 2, ' ');
        os << indent << "MachDon - " << maSo << std::endl;
        os << indent << "Tri gia: " << triGia << ", Dien tro: " << std::fixed << std::setprecision(3) << dienTroRieng << std::endl;
    }
    
    std::string layLoaiMach() const override {
        return "MachDon";
    }
};

class MachPhuc : public IMachDien {
protected:
    std::vector<IMachDien*> danhSachMachCon;

public:
    MachPhuc(const std::string& maSo, long triGia) : IMachDien(maSo, triGia) {}
    
    virtual ~MachPhuc() {
        // for (IMachDien* mach : danhSachMachCon) {
        //     delete mach;
        // }
    }
    
    void themMachCon(IMachDien* machCon) override {
        if (machCon) {
            danhSachMachCon.push_back(machCon);
        }
    }
    
    int demSoLuongMachCon() const override {
        int count = 0;
        for (const IMachDien* mach : danhSachMachCon) {
            if (mach->layLoaiMach() == "MachDon") {
                count++;
            } else {
                count += mach->demSoLuongMachCon();
            }
        }
        return count;
    }
    
    void hienThiThongTin(std::ostream& os, int indentLevel = 0) const override {
        std::string indent(indentLevel * 2, ' ');
        os << indent << layLoaiMach() << " - " << maSo << std::endl;
        os << indent << "Tri gia: " << triGia << ", Dien tro: " << std::fixed << std::setprecision(3) << tinhDienTro() << std::endl;
        for (const IMachDien* mach : danhSachMachCon) {
            mach->hienThiThongTin(os, indentLevel + 1);
        }
    }
    
    const std::vector<IMachDien*>& layDanhSachMachCon() const {
        return danhSachMachCon;
    }
};


class MachNoiTiep : public MachPhuc {
public:
    MachNoiTiep(const std::string& maSo, long triGia) : MachPhuc(maSo, triGia) {}
    
    double tinhDienTro() const override {
        double tongDienTro = 0;
        for (const IMachDien* mach : danhSachMachCon) {
            tongDienTro += mach->tinhDienTro();
        }
        return tongDienTro;
    }
    
    std::string layLoaiMach() const override {
        return "MachNoiTiep";
    }
};


class MachSongSong : public MachPhuc {
public:
    MachSongSong(const std::string& maSo, long triGia) : MachPhuc(maSo, triGia) {}
    
    double tinhDienTro() const override {
        if (danhSachMachCon.empty()) return 0;
        
        double nghichDaoTong = 0;
        for (const IMachDien* mach : danhSachMachCon) {
            double dienTro = mach->tinhDienTro();
            if (dienTro > 0) {
                nghichDaoTong += 1.0 / dienTro;
            } else if (dienTro == 0) {
                throw DivisionByZeroException();
            }
        }
        if (nghichDaoTong == 0) {
            throw DivisionByZeroException();
        }
        return 1.0 / nghichDaoTong;
    }
    
    std::string layLoaiMach() const override {
        return "MachSongSong";
    }
};


class QuanLyBoMach {
private:
    std::vector<IMachDien*> danhSachTatCaMach;
    std::vector<IMachDien*> danhSachMachGoc;

public:
    ~QuanLyBoMach() {
        for (IMachDien* mach : danhSachTatCaMach) {
            delete mach;
        }
    }
    
    void themMach(IMachDien* mach) {
        if (mach) {
            danhSachTatCaMach.push_back(mach);
        }
    }
    
    IMachDien* timMachTheoMaSo(const std::string& maSo) const {
        for (IMachDien* mach : danhSachTatCaMach) {
            if (mach->layMaSo() == maSo) {
                return mach;
            }
        }
        return nullptr;
    }
    
    void napDuLieuTuFile(const std::string& tenFile) {
        std::ifstream file(tenFile);
        if (!file.is_open()) {
            throw FileException(tenFile);
        }
        
        std::string line;
        std::vector<std::string> usedCircuits;
        std::vector<IMachDien*> complexCircuitStack; 
        
        while (std::getline(file, line)) {
            if (line.empty()) continue;
            
            if (line.find(" - ") == std::string::npos) {
                
                bool isEndMarker = false;
                
                for (int i = complexCircuitStack.size() - 1; i >= 0; i--) {
                    if (line == complexCircuitStack[i]->layMaSo()) {
                        
                        IMachDien* completedCircuit = complexCircuitStack[i];
                        complexCircuitStack.erase(complexCircuitStack.begin() + i);
                        
                        
                        if (!complexCircuitStack.empty()) {
                            complexCircuitStack.back()->themMachCon(completedCircuit);
                            usedCircuits.push_back(line);
                        }
                        
                        isEndMarker = true;
                        break;
                    }
                }
                
                if (!isEndMarker) {
                    if (!complexCircuitStack.empty()) {
                        IMachDien* subMach = timMachTheoMaSo(line);
                        if (subMach) {
                            complexCircuitStack.back()->themMachCon(subMach);
                            usedCircuits.push_back(line);
                        } else {
                            throw CircuitNotFoundException(line);
                        }
                    }
                }
                continue;
            }
            
            std::istringstream iss(line);
            std::string loaiMach, dash, maSo;
            iss >> loaiMach >> dash >> maSo;
            
            if (loaiMach == "MachDon" || loaiMach == "MachNoiTiep" || loaiMach == "MachSongSong") {
                if (!std::getline(file, line)) {
                    throw ParseException("Missing value line after circuit definition");
                }
                
                std::istringstream valueIss(line);
                long triGia;
                double dienTro;
                if (!(valueIss >> triGia >> dienTro)) {
                    throw ParseException(line);
                }
                
                IMachDien* mach = nullptr;
                if (loaiMach == "MachDon") {
                    mach = new MachDon(maSo, triGia, dienTro);
                } else if (loaiMach == "MachNoiTiep") {
                    mach = new MachNoiTiep(maSo, triGia);
                    complexCircuitStack.push_back(mach); 
                } else if (loaiMach == "MachSongSong") {
                    mach = new MachSongSong(maSo, triGia);
                    complexCircuitStack.push_back(mach); 
                }
                
                themMach(mach);
            } else {
                throw ParseException(line);
            }
        }
        
        for (IMachDien* mach : danhSachTatCaMach) {
            if (std::find(usedCircuits.begin(), usedCircuits.end(), mach->layMaSo()) == usedCircuits.end()) {
                danhSachMachGoc.push_back(mach);
            }
        }
        
        file.close();
    }
    
    void hienThiToanBoBoMach() const {
        std::cout << "=== THONG TIN TOAN BO BO MACH ===" << std::endl;
        for (const IMachDien* mach : danhSachMachGoc) {
            std::cout << *mach << std::endl;
        }
    }
    
    double tinhTongDienTroBoMach() const {
        double tong = 0;
        for (const IMachDien* mach : danhSachMachGoc) {
            tong += mach->tinhDienTro();
        }
        return tong;
    }
    
    long tinhTongTriGiaBoMach() const {
        long tong = 0;
        for (const IMachDien* mach : danhSachTatCaMach) {
            tong += mach->layTriGia();
        }
        return tong;
    }
    
    IMachDien* timMachPhucChuaNhieuMachDonNhat() const {
        IMachDien* ketQua = nullptr;
        int maxSoLuong = 0;
        
        for (IMachDien* mach : danhSachTatCaMach) {
            if (mach->layLoaiMach() != "MachDon") {
                int soLuong = mach->demSoLuongMachCon();
                if (soLuong > maxSoLuong) {
                    maxSoLuong = soLuong;
                    ketQua = mach;
                }
            }
        }
        return ketQua;
    }
    
    void lietKeMachDonTrongMachPhuc(const std::string& maMachPhuc) const {
        IMachDien* machPhuc = timMachTheoMaSo(maMachPhuc);
        if (!machPhuc) {
            throw CircuitNotFoundException(maMachPhuc);
        }
        if (machPhuc->layLoaiMach() == "MachDon") {
            throw InvalidCircuitException("Circuit " + maMachPhuc + " is not a complex circuit");
        }
        
        std::cout << "Cac mach don trong " << maMachPhuc << ":" << std::endl;
        lietKeMachDonRecursive(machPhuc, 1);
    }

private:
    void lietKeMachDonRecursive(const IMachDien* mach, int level) const {
        if (mach->layLoaiMach() == "MachDon") {
            std::string indent(level * 2, ' ');
            std::cout << indent << "- " << mach->layMaSo() << " (Dien tro: " 
                     << std::fixed << std::setprecision(3) << mach->tinhDienTro() << ")" << std::endl;
        } else {
            const MachPhuc* machPhuc = dynamic_cast<const MachPhuc*>(mach);
            if (machPhuc) {
                const std::vector<IMachDien*>& subCircuits = machPhuc->layDanhSachMachCon();
                for (const IMachDien* subMach : subCircuits) {
                    lietKeMachDonRecursive(subMach, level);
                }
            }
        }
    }
};

int main() {
    try {
        QuanLyBoMach quanLy;
        
        quanLy.napDuLieuTuFile("data.txt");
        
        quanLy.hienThiToanBoBoMach();
        
        std::cout << "\n=== THONG KE ===" << std::endl;
        std::cout << "Tong dien tro bo mach: " << std::fixed << std::setprecision(3) 
                 << quanLy.tinhTongDienTroBoMach() << " Ohm" << std::endl;
        std::cout << "Tong tri gia bo mach: " << quanLy.tinhTongTriGiaBoMach() << " VND" << std::endl;
        
        
        IMachDien* machNhieuNhat = quanLy.timMachPhucChuaNhieuMachDonNhat();
        if (machNhieuNhat) {
            std::cout << "Mach phuc chua nhieu mach don nhat: " << machNhieuNhat->layMaSo() 
                     << " (" << machNhieuNhat->demSoLuongMachCon() << " mach don)" << std::endl;
        }
        
        std::cout << "\n=== LIET KE MACH DON ===" << std::endl;
        quanLy.lietKeMachDonTrongMachPhuc("MNT002");
        quanLy.lietKeMachDonTrongMachPhuc("MSS004");
        
    } catch (const BoMachException& e) {
        std::cerr << "BoMach Error [" << e.getErrorCode() << "]: " << e.getDescription() << std::endl;
        return e.getErrorCode();
    } catch (const std::exception& e) {
        std::cerr << "General Error: " << e.what() << std::endl;
        return 9999;
    }
    
    return 0;
}