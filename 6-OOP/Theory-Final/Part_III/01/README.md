**CÂU 3: XÂY DỰNG HỆ THỐNG ĐẶT VÀ THANH TOÁN ĐƠN HÀNG TRỰC TUYẾN**

**Bối cảnh:**

Một cửa hàng trực tuyến cần một hệ thống để quản lý sản phẩm, giỏ hàng của khách hàng, và quy trình thanh toán cho các đơn hàng.

*   **Sản phẩm (Product):** Mỗi sản phẩm có mã sản phẩm, tên, mô tả, và giá bán.
*   **Mục trong giỏ hàng (CartItem):** Đại diện cho một loại sản phẩm cụ thể được thêm vào giỏ hàng, bao gồm thông tin sản phẩm và số lượng.
*   **Giỏ hàng (ShoppingCart):** Chứa một danh sách các `CartItem`. Có thể tính tổng giá trị các mặt hàng trong giỏ.
*   **Đơn hàng (Order):** Được tạo từ một `ShoppingCart` khi khách hàng quyết định thanh toán. Đơn hàng sẽ có tổng giá trị, và trạng thái (ví dụ: "Đang chờ xử lý", "Đã thanh toán", "Đã hủy").

**Yêu cầu:**

**a) (2.0 điểm) Thiết kế Sơ đồ Lớp (Class Diagram)**

Hãy áp dụng các tính chất hướng đối tượng đã học để **vẽ sơ đồ lớp (class diagram)** thể hiện các lớp cần thiết cho hệ thống (ví dụ: `Product`, `CartItem`, `ShoppingCart`, `Order`).
*   Ghi rõ các **thuộc tính (attributes)** quan trọng cho mỗi lớp.
*   Ghi rõ các **phương thức (methods)** chính mà mỗi lớp cần có (ví dụ: thêm sản phẩm vào giỏ, xóa sản phẩm khỏi giỏ, tính tổng giỏ hàng, đặt hàng, cập nhật trạng thái đơn hàng).
*   Thể hiện rõ các **mối quan hệ (relationships)** giữa các lớp.

**b) (2.0 điểm) Cài đặt các Lớp và Chức năng Chính**

Dựa trên thiết kế ở câu a, hãy cài đặt chi tiết bằng ngôn ngữ C++:
1.  **Lớp `Product`**:
    *   Cài đặt đầy đủ các thuộc tính và hàm tạo.
    *   Phương thức `void displayProductInfo() const`.
2.  **Lớp `CartItem`**:
    *   Thuộc tính: `Product* product`, `int quantity`.
    *   Hàm tạo.
    *   Phương thức `double getItemTotal() const` để tính tổng giá trị của mục này (giá sản phẩm * số lượng).
    *   Phương thức `void displayItemInfo() const`.
3.  **Lớp `ShoppingCart`**:
    *   Thuộc tính: `vector<CartItem> items`.
    *   Phương thức `void addItem(const Product& product, int quantity)`: Thêm một sản phẩm với số lượng nhất định vào giỏ. Nếu sản phẩm đã có, tăng số lượng.
    *   Phương thức `void removeItem(const string& productId)`: Xóa một sản phẩm khỏi giỏ dựa trên mã sản phẩm.
    *   Phương thức `double getTotalValue() const`: Tính tổng giá trị của tất cả các mặt hàng trong giỏ.
    *   Phương thức `void displayCart() const`.
4.  **Lớp `Order`**:
    *   Thuộc tính: `vector<CartItem> orderedItems`, `double totalAmount`, `string status`.
    *   Hàm tạo nhận vào một đối tượng `ShoppingCart` để khởi tạo đơn hàng.
    *   Phương thức `void displayOrderDetails() const`.
5.  Trong hàm `main()`:
    *   Tạo ít nhất 3 đối tượng `Product`.
    *   Tạo một đối tượng `ShoppingCart`.
    *   Thêm các sản phẩm vào giỏ hàng. Hiển thị giỏ hàng và tổng giá trị.
    *   Tạo một đối tượng `Order` từ giỏ hàng. Hiển thị chi tiết đơn hàng.

*Lưu ý: Quản lý bộ nhớ cho `Product*` trong `CartItem` cần được cân nhắc. Trong bài này, có thể giả định các đối tượng `Product` tồn tại suốt chương trình và `CartItem` chỉ lưu con trỏ.*

**c) (1.0 điểm) Mở rộng: Thông báo Trạng thái Đơn hàng cho Khách hàng (Observer Pattern)**

Hiện tại, khi trạng thái của một đơn hàng (`Order`) thay đổi (ví dụ: từ "Đang chờ xử lý" thành "Đã thanh toán", rồi thành "Đang giao hàng", "Đã giao"), khách hàng không được tự động thông báo. Chúng ta muốn triển khai một cơ chế để khi trạng thái đơn hàng thay đổi, các "người quan sát" (ví dụ: hệ thống gửi email, hệ thống gửi SMS, một module hiển thị trên dashboard của khách hàng) có thể được thông báo và thực hiện hành động tương ứng.

Bạn sẽ **thay đổi hay bổ sung thêm cho các lớp đối tượng** (đã thiết kế ở câu a, đặc biệt là lớp `Order`) như thế nào để hỗ trợ cơ chế thông báo này?
*   Hãy giải thích những thay đổi hoặc bổ sung cần thiết.
*   Mô tả (không cần vẽ lại toàn bộ sơ đồ lớp, chỉ cần mô tả các lớp/interface mới và mối quan hệ chính) cách bạn sẽ áp dụng **Observer Design Pattern** để giải quyết yêu cầu này.
*   Nêu rõ vai trò của các thành phần trong Observer Pattern (Subject, Observer, ConcreteSubject, ConcreteObserver) trong bối cảnh bài toán này.

*(Trong đề gốc câu 3c yêu cầu về Composite Pattern cho cấu trúc cây. Ở đây, chúng ta đổi sang Observer Pattern để xử lý việc thông báo sự kiện thay đổi trạng thái).*

---

**Gợi ý cho câu 3c (Observer Pattern):**

1.  **Subject (Chủ thể):**
    *   Interface `OrderSubject` (hoặc `Subject`) định nghĩa các phương thức để đăng ký (`attach`), hủy đăng ký (`detach`), và thông báo (`notify`) cho các observers.
    *   Lớp `Order` sẽ là một **ConcreteSubject**. Nó sẽ kế thừa từ `OrderSubject` (hoặc triển khai interface nếu bạn định nghĩa nó là interface thuần túy).
    *   `Order` sẽ có một danh sách các `OrderObserver*` (hoặc `Observer*`).
    *   Khi trạng thái của `Order` thay đổi (ví dụ, trong một phương thức `setStatus(newStatus)`), nó sẽ gọi phương thức `notify()` của mình.

2.  **Observer (Người quan sát):**
    *   Interface `OrderObserver` (hoặc `Observer`) định nghĩa một phương thức `update(const Order& order)` (hoặc tương tự) mà Subject sẽ gọi khi có thay đổi.
    *   Bạn sẽ tạo các lớp **ConcreteObserver** (ví dụ: `EmailNotifier`, `SMSNotifier`, `DashboardDisplay`) kế thừa từ `OrderObserver` và triển khai phương thức `update()`. Bên trong `update()`, mỗi ConcreteObserver sẽ thực hiện hành động cụ thể của nó (gửi email, gửi SMS, cập nhật dashboard).

3.  **Cách hoạt động:**
    *   Các đối tượng ConcreteObserver (ví dụ: một `EmailNotifier`) sẽ được tạo và đăng ký với một đối tượng `Order` (ConcreteSubject).
    *   Khi phương thức `Order::setStatus()` được gọi và trạng thái thay đổi, `Order` sẽ duyệt qua danh sách các Observer đã đăng ký và gọi phương thức `update()` của từng Observer, truyền thông tin về đơn hàng (hoặc chỉ trạng thái mới).
    *   Mỗi Observer sẽ phản ứng theo cách riêng của nó.

Bằng cách này, lớp `Order` không cần biết chi tiết về cách các hệ thống khác nhau muốn được thông báo. Nó chỉ cần biết về interface `OrderObserver`. Điều này giúp giảm sự phụ thuộc và tăng tính linh hoạt, dễ dàng thêm hoặc bớt các loại thông báo mới mà không cần sửa đổi lớp `Order`.