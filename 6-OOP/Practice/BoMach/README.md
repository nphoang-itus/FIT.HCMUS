**Đề bài: Hệ Thống Quản Lý Bo Mạch Điện Tử**

Bạn được yêu cầu xây dựng một hệ thống quản lý các thành phần mạch điện trên một bo mạch chính. Bo mạch này chứa nhiều loại mạch điện khác nhau, bao gồm các mạch đơn lẻ và các mạch phức hợp (mạch nối tiếp, mạch song song) được cấu thành từ các mạch đơn hoặc các mạch phức khác.

**1. Các Loại Mạch Điện:**

*   **`IMachDien` (Interface/Lớp cơ sở trừu tượng):**
    *   **Thuộc tính chung (protected):** `maSo` (string), `triGia` (long - giá trị/chi phí của mạch).
    *   **Phương thức (thuần ảo/ảo):**
        *   `virtual ~IMachDien() {}`
        *   `virtual double tinhDienTro() const = 0;` (Tính tổng điện trở của mạch).
        *   `virtual long layTriGia() const;` (Trả về `triGia`).
        *   `virtual void hienThiThongTin(std::ostream& os, int indentLevel = 0) const = 0;` (Hiển thị thông tin chi tiết của mạch, `indentLevel` để thụt lề).
        *   `virtual std::string layMaSo() const;`
        *   `virtual std::string layLoaiMach() const = 0;` (Trả về "MachDon", "MachNoiTiep", "MachSongSong").
        *   `virtual void themMachCon(IMachDien* machCon)` (Mặc định ném ngoại lệ, chỉ `MachPhuc` mới override).
        *   `virtual int demSoLuongMachCon() const { return 0; }` (Mặc định trả về 0, `MachPhuc` sẽ override để đếm đệ quy).
    *   `friend std::ostream& operator<<(std::ostream& os, const IMachDien& md);` (Gọi `md.hienThiThongTin(os, 0)`).

*   **`MachDon` (Mạch Đơn - Kế thừa từ `IMachDien`):**
    *   **Thuộc tính (private):** `dienTroRieng` (double).
    *   **Phương thức:**
        *   Constructor nhận `maSo`, `triGia`, `dienTroRieng`.
        *   Override các phương thức cần thiết từ `IMachDien`.
            *   `tinhDienTro()`: Trả về `dienTroRieng`.
            *   `hienThiThongTin()`: Hiển thị mã số, trị giá, điện trở riêng.
            *   `layLoaiMach()`: Trả về "MachDon".

*   **`MachPhuc` (Mạch Phức - Lớp cơ sở trừu tượng cho Mạch Nối Tiếp và Song Song, kế thừa từ `IMachDien`):**
    *   **Thuộc tính (protected):** `std::vector<IMachDien*> danhSachMachCon;`
    *   **Phương thức:**
        *   Constructor nhận `maSo`, `triGia`.
        *   `~MachPhuc()`: Giải phóng bộ nhớ cho các `danhSachMachCon`.
        *   Override `themMachCon(IMachDien* machCon)`: Thêm một mạch vào `danhSachMachCon`.
        *   Override `demSoLuongMachCon() const`: Đếm tổng số mạch con bên trong (bao gồm cả các mạch con của mạch con, tức là đếm đệ quy tất cả các `MachDon`).
        *   Override `hienThiThongTin()`: Hiển thị thông tin của mạch phức, sau đó duyệt và hiển thị thông tin của từng `danhSachMachCon` với `indentLevel + 1`.
        *   Phương thức `tinhDienTro()` sẽ là thuần ảo ở đây, vì cách tính khác nhau cho nối tiếp và song song.

*   **`MachNoiTiep` (Kế thừa từ `MachPhuc`):**
    *   **Phương thức:**
        *   Constructor.
        *   Override `tinhDienTro() const`: Tổng điện trở của các mạch con cộng lại.
        *   Override `layLoaiMach()`: Trả về "MachNoiTiep".

*   **`MachSongSong` (Kế thừa từ `MachPhuc`):**
    *   **Phương thức:**
        *   Constructor.
        *   Override `tinhDienTro() const`: Tính theo công thức 1/R_td = 1/R1 + 1/R2 + ... (Cẩn thận trường hợp mạch con có điện trở bằng 0 nếu có).
        *   Override `layLoaiMach()`: Trả về "MachSongSong".

**2. `QuanLyBoMach` (Lớp Quản lý Chính):**

*   **Thuộc tính (private):**
    *   `std::vector<IMachDien*> danhSachTatCaMach;` (Lưu trữ tất cả các mạch, bao gồm cả mạch đơn và mạch phức, để dễ dàng quản lý và tìm kiếm theo mã).
    *   `std::vector<IMachDien*> danhSachMachGoc;` (Lưu trữ các mạch phức không nằm trong mạch phức nào khác, hoặc các mạch đơn không nằm trong mạch phức nào – các mạch "cấp cao nhất" trên bo mạch).
*   **Phương thức:**
    *   `~QuanLyBoMach()`: Giải phóng bộ nhớ cho tất cả các mạch trong `danhSachTatCaMach`. (Lưu ý: Nếu một mạch nằm trong `danhSachMachCon` của một `MachPhuc`, và `MachPhuc` đó cũng nằm trong `danhSachTatCaMach`, cần cẩn thận để không `delete` hai lần. Một cách là `danhSachTatCaMach` chỉ lưu con trỏ, và việc `delete` chính sẽ do `MachPhuc` (cho con của nó) và `QuanLyBoMach` (cho các mạch gốc trong `danhSachMachGoc`) đảm nhiệm. Hoặc, đơn giản hơn, nếu tất cả mạch đều được thêm vào `danhSachTatCaMach` một lần duy nhất, thì chỉ `~QuanLyBoMach` cần dọn dẹp `danhSachTatCaMach`).
    *   `void themMach(IMachDien* mach);` (Thêm vào `danhSachTatCaMach`. Có thể có logic để xác định mạch gốc và thêm vào `danhSachMachGoc`).
    *   `IMachDien* timMachTheoMaSo(const std::string& maSo) const;`
    *   `void napDuLieuTuFile(const std::string& tenFile);`
        *   Đọc file `data.txt`.
        *   Phân tích từng dòng để xác định loại mạch (MachDon, MachNoiTiep, MachSongSong).
        *   Tạo đối tượng mạch tương ứng.
        *   Xử lý dòng chứa mã mạch phức (ví dụ: `MNT002` dưới một `MachDon`) để thêm mạch đơn đó vào đúng mạch phức chứa nó.
        *   Lưu trữ tất cả các mạch vào `danhSachTatCaMach`. Các mạch không được chỉ định là con của mạch nào khác sẽ được coi là mạch gốc và thêm vào `danhSachMachGoc`.
    *   `void hienThiToanBoBoMach() const;` (Hiển thị thông tin của các mạch trong `danhSachMachGoc`).
    *   `double tinhTongDienTroBoMach() const;` (Tính tổng điện trở của bo mạch, có thể là tổng điện trở của các `danhSachMachGoc` theo một quy tắc nào đó, ví dụ coi chúng mắc nối tiếp, hoặc chỉ tính cho một mạch gốc cụ thể).
    *   `long tinhTongTriGiaBoMach() const;` (Tính tổng trị giá của tất cả các mạch trên bo mạch, không tính trùng).
    *   `IMachDien* timMachPhucChuaNhieuMachDonNhat() const;` (Tìm và trả về con trỏ đến mạch phức (Nối tiếp hoặc Song song) chứa số lượng `MachDon` nhiều nhất bên trong nó - đếm đệ quy).
    *   `void lietKeMachDonTrongMachPhuc(const std::string& maMachPhuc) const;`

**3. Định dạng file `data.txt` và cách xử lý:**
Ví dụ:
```
MachNoiTiep - MNT002
172500 276.445
MachSongSong - MSS001
159500 96.4451
MachDon - MD012
50000 325
MD012
MachDon - MD006
70000 320
MD006
MachDon - MD008
25000 240
MD008
MSS001
MachDon - MD001
3000 50
MD001
MachDon - MD004
10000 130
MD004
MNT002
```
Tức:
MNT002 chứa MSS001 (MSS001 chứa MD012, MD006, MD008), MD001, MD004
Từng dòng:
Dòng 1: Loại mạch - Mã mạch
Dòng 2: Trị giá Điện trở
Dòng 3 trở đi: Thông tin các mạch con nếu có (mạch đơn thì tất nhiên ko có mạch con)
Dòng cuối: Mã mạch đánh dấu kết thúc