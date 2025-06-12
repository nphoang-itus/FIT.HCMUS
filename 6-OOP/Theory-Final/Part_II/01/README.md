**Yêu cầu:**

Bạn được yêu cầu xây dựng một hệ thống nhỏ để quản lý các loại ấn phẩm khác nhau trong một thư viện. Các ấn phẩm bao gồm **Sách (Book)** và **Tạp chí (Magazine)**.

**Phần 1: Thiết kế Interface và Lớp cơ sở (1.0 điểm)**

a)  **(0.5 điểm)** Hãy khai báo một lớp trừu tượng (abstract class) có tên là `AnPham` (Publication) đóng vai trò như một interface chung cho các loại ấn phẩm. Lớp `AnPham` cần có các thông tin và hành vi sau:
    *   Thuộc tính (protected):
        *   `string maSo`: Mã số duy nhất của ấn phẩm.
        *   `string tenNhanDe`: Tên nhan đề của ấn phẩm.
        *   `string nhaXuatBan`: Nhà xuất bản.
        *   `int namXuatBan`: Năm xuất bản.
    *   Hàm tạo (constructor) để khởi tạo các thuộc tính trên.
    *   Phương thức thuần ảo (pure virtual function):
        *   `virtual void hienThiThongTin() const = 0;`: Hiển thị đầy đủ thông tin chi tiết của ấn phẩm.
        *   `virtual string getType() const = 0;`: Trả về loại của ấn phẩm (ví dụ: "Sach", "TapChi").
    *   Hàm hủy ảo (virtual destructor).

b)  **(0.5 điểm)** Viết một hàm không phải thành viên (non-member function) có tên `void themAnPhamVaoThuVien(vector<AnPham*>& danhSach, AnPham* ap)` để thêm một ấn phẩm mới vào danh sách quản lý của thư viện (sử dụng `std::vector<AnPham*>`).

**Phần 2: Cài đặt các Lớp Con (1.5 điểm)**

a)  **(0.75 điểm)** Hãy khai báo và cài đặt lớp `Sach` (Book) kế thừa từ lớp `AnPham`. Lớp `Sach` có thêm các thuộc tính riêng:
    *   `string tenTacGia`: Tên tác giả.
    *   `int soTrang`: Số trang.
    *   Cài đặt hàm tạo cho lớp `Sach` để khởi tạo tất cả các thuộc tính (bao gồm cả các thuộc tính kế thừa từ `AnPham`).
    *   Ghi đè (override) phương thức `hienThiThongTin()` để hiển thị thông tin của sách, bao gồm tất cả các thuộc tính của `AnPham` và các thuộc tính riêng của `Sach`.
    *   Ghi đè (override) phương thức `getType()` để trả về chuỗi "Sach".

b)  **(0.75 điểm)** Hãy khai báo và cài đặt lớp `TapChi` (Magazine) kế thừa từ lớp `AnPham`. Lớp `TapChi` có thêm các thuộc tính riêng:
    *   `int soPhatHanh`: Số phát hành của tạp chí.
    *   `int thangPhatHanh`: Tháng phát hành.
    *   Cài đặt hàm tạo cho lớp `TapChi` để khởi tạo tất cả các thuộc tính.
    *   Ghi đè (override) phương thức `hienThiThongTin()` để hiển thị thông tin của tạp chí.
    *   Ghi đè (override) phương thức `getType()` để trả về chuỗi "TapChi".

**Phần 3: Quản lý và Xử lý (1.5 điểm)**

a)  **(0.5 điểm)** Viết một hàm không phải thành viên `void hienThiDanhSachAnPham(const vector<AnPham*>& danhSach)` để duyệt qua danh sách các ấn phẩm trong thư viện và gọi phương thức `hienThiThongTin()` của từng ấn phẩm (thể hiện tính đa hình).

b)  **(0.5 điểm)** Trong hàm `main()`, hãy tạo ít nhất 2 đối tượng `Sach` và 2 đối tượng `TapChi` với thông tin tự chọn. Thêm các đối tượng này vào một `std::vector<AnPham*>`. Sau đó, gọi hàm `hienThiDanhSachAnPham()` để hiển thị thông tin của tất cả ấn phẩm.

c)  **(0.5 điểm)** Giả sử việc tìm kiếm một ấn phẩm dựa trên `maSo` có thể không thành công. Hãy viết một hàm `AnPham* timAnPhamTheoMa(const vector<AnPham*>& danhSach, const string& maSoTimKiem)` để tìm kiếm một ấn phẩm.
    *   Nếu tìm thấy, trả về con trỏ đến ấn phẩm đó.
    *   Nếu không tìm thấy, hàm này phải **ném (throw)** một ngoại lệ kiểu `std::runtime_error` với thông báo "Khong tim thay an pham voi ma so: [maSoTimKiem]".
    *   Trong hàm `main()`, hãy viết đoạn code để gọi hàm `timAnPhamTheoMa` và sử dụng khối `try-catch` để xử lý trường hợp tìm thấy và không tìm thấy (in ra thông báo phù hợp).

**Lưu ý chung:**

*   Tất cả cài đặt phải sử dụng ngôn ngữ lập trình C++.
*   Sử dụng `std::string`, `std::vector`, `std::iostream`, `std::runtime_error`.
*   Chú ý đến việc quản lý bộ nhớ (sử dụng `new` để tạo đối tượng và `delete` để giải phóng khi cần thiết, đặc biệt là khi kết thúc chương trình hoặc khi vector không còn cần thiết).

---

**Gợi ý cách tiếp cận và các điểm cần lưu ý:**

1.  **Lớp `AnPham`:**
    *   Khai báo các thuộc tính là `protected` để lớp con có thể truy cập.
    *   Constructor của `AnPham` sẽ nhận các tham số tương ứng để khởi tạo.
    *   `hienThiThongTin()` và `getType()` là `virtual ... = 0;`.
    *   Đừng quên `virtual ~AnPham() {}` (hoặc có thể in ra thông báo nếu muốn theo dõi).

2.  **Lớp `Sach` và `TapChi`:**
    *   Trong constructor của lớp con, gọi constructor của lớp cha `AnPham` bằng member initializer list.
    *   Khi override `hienThiThongTin()`, bạn có thể gọi lại một phần hiển thị chung từ lớp cha (nếu có) hoặc tự hiển thị tất cả.
    *   Đảm bảo từ khóa `override` được sử dụng khi ghi đè hàm ảo.

3.  **Hàm `main()` và các hàm tiện ích:**
    *   Khởi tạo các đối tượng sách và tạp chí bằng `new`.
    *   Lưu trữ con trỏ `AnPham*` vào vector.
    *   Khi duyệt vector để hiển thị hoặc dọn dẹp, sử dụng range-based for loop hoặc iterator.
    *   **Quản lý bộ nhớ:** Sau khi sử dụng xong vector, đừng quên `delete` từng con trỏ trong vector để tránh rò rỉ bộ nhớ.
        ```cpp
        // Trong main, sau khi không cần danhSachAnPham nữa:
        for (AnPham* ap : danhSachAnPham) {
            delete ap;
        }
        danhSachAnPham.clear();
        ```

4.  **Xử lý ngoại lệ:**
    *   Trong `timAnPhamTheoMa`, sau vòng lặp, nếu không tìm thấy, `throw std::runtime_error("...")`.
    *   Trong `main`, bọc lời gọi `timAnPhamTheoMa` trong `try` và bắt `const std::runtime_error& e` trong `catch`.