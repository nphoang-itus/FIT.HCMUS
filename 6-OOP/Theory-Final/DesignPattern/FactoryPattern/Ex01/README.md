**Yêu cầu:**

Dựa trên mô tả bài toán về "Hệ Thống Giao Hàng Đa Phương Thức" đã được đưa ra, hãy triển khai đầy đủ chương trình bằng ngôn ngữ lập trình C++ để minh họa cho Factory Method Pattern. Bài làm của bạn cần đáp ứng các yêu cầu sau:

**Phần 1: Định nghĩa các lớp Product**

1.  **Lớp trừu tượng `Delivery`:**
    * Định nghĩa một lớp trừu tượng có tên `Delivery`.
    * Thêm phương thức ảo thuần túy `virtual void deliver(const std::string& address) = 0;` để mô tả việc giao hàng đến một địa chỉ.
    * Thêm phương thức ảo thuần túy `virtual double calculateCost(double distance) const = 0;` để tính toán chi phí giao hàng dựa trên khoảng cách (đơn vị: km). Phương thức này trả về một giá trị `double` là chi phí.
    * Đảm bảo có destructor ảo `virtual ~Delivery() {}` để xử lý việc giải phóng bộ nhớ đúng cách trong trường hợp kế thừa.

2.  **Các lớp sản phẩm cụ thể:**
    * **`RoadDelivery`:** Kế thừa từ `Delivery`.
        * Triển khai phương thức `deliver` để in ra thông báo về việc giao hàng bằng đường bộ đến địa chỉ được cung cấp.
        * Triển khai phương thức `calculateCost` theo công thức: `5.0 + 0.5 * distance`.
    * **`AirDelivery`:** Kế thừa từ `Delivery`.
        * Triển khai phương thức `deliver` để in ra thông báo về việc giao hàng bằng đường hàng không đến địa chỉ được cung cấp.
        * Triển khai phương thức `calculateCost` theo công thức: `50.0 + 2.0 * distance`.
    * **`SeaDelivery`:** Kế thừa từ `Delivery`.
        * Triển khai phương thức `deliver` để in ra thông báo về việc giao hàng bằng đường biển đến địa chỉ được cung cấp.
        * Triển khai phương thức `calculateCost` theo công thức: `10.0 + 0.1 * distance`.

**Phần 2: Định nghĩa các lớp Creator**

1.  **Lớp trừu tượng `Logistics`:**
    * Định nghĩa một lớp trừu tượng có tên `Logistics`.
    * Thêm phương thức ảo thuần túy `virtual Delivery* createDeliveryMethod() = 0;` để tạo đối tượng `Delivery`.
    * Thêm phương thức `void planDelivery(const std::string& address, double distance)` không ảo (non-virtual). Phương thức này thực hiện các bước sau:
        * Gọi phương thức `createDeliveryMethod()` để nhận một đối tượng `Delivery`.
        * Gọi phương thức `deliver()` của đối tượng `Delivery` để thực hiện giao hàng đến địa chỉ đã cho.
        * Gọi phương thức `calculateCost()` của đối tượng `Delivery` để tính toán chi phí giao hàng cho khoảng cách đã cho.
        * In ra thông báo về chi phí giao hàng.
        * Đảm bảo giải phóng bộ nhớ của đối tượng `Delivery` sau khi sử dụng (sử dụng `delete` vì chúng ta đang trả về con trỏ thô từ factory method).
    * Đảm bảo có destructor ảo `virtual ~Logistics() {}`.

2.  **Các lớp Creator cụ thể:**
    * **`RoadLogistics`:** Kế thừa từ `Logistics`.
        * Ghi đè phương thức `createDeliveryMethod()` để trả về một đối tượng `RoadDelivery` được cấp phát động bằng `new`.
    * **`AirLogistics`:** Kế thừa từ `Logistics`.
        * Ghi đè phương thức `createDeliveryMethod()` để trả về một đối tượng `AirDelivery` được cấp phát động bằng `new`.
    * **`SeaLogistics`:** Kế thừa từ `Logistics`.
        * Ghi đè phương thức `createDeliveryMethod()` để trả về một đối tượng `SeaDelivery` được cấp phát động bằng `new`.

**Phần 3: Mã máy khách (trong hàm `main`)**

1.  Tạo ít nhất ba đối tượng `Logistics` khác nhau: một `RoadLogistics`, một `AirLogistics`, và một `SeaLogistics`.
2.  Gọi phương thức `planDelivery()` trên mỗi đối tượng `Logistics` với các địa chỉ và khoảng cách khác nhau để mô phỏng các kịch bản giao hàng khác nhau. Ví dụ:
    * Giao hàng bằng đường bộ đến "123 Đường ABC, Thành phố XYZ" với khoảng cách 100 km.
    * Giao hàng bằng đường hàng không đến "Sân bay Quốc tế DEF, Thành phố UVW" với khoảng cách 1500 km.
    * Giao hàng bằng đường biển đến "Cảng GHI, Thành phố RST" với khoảng cách 5000 km.

**Yêu cầu về mặt trình bày:**

* Code của bạn phải được tổ chức rõ ràng, dễ đọc và tuân theo các quy tắc cơ bản về định dạng code (ví dụ: thụt lề nhất quán, đặt tên biến/lớp có ý nghĩa).
* Sử dụng các thư viện iostream để in ra thông tin cần thiết.
* Đảm bảo không có rò rỉ bộ nhớ trong chương trình của bạn.

**Lưu ý:**

* Bạn được phép sử dụng các tính năng cơ bản của C++ như lớp, kế thừa, phương thức ảo, con trỏ, và toán tử `new`/`delete`.
* Mục tiêu chính của bài tập này là để bạn hiểu và có thể triển khai Factory Method Pattern.