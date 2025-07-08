### Bài tập về Strategy Pattern (C++)

**Mục tiêu chung:** Hiểu cách định nghĩa một họ thuật toán, đóng gói từng thuật toán và làm cho chúng có thể hoán đổi cho nhau. Luyện tập với việc tách rời hành vi khỏi đối tượng sử dụng nó.

---

#### Bài tập 1: Hệ thống Nén File

**Bối cảnh:**
Bạn đang viết một ứng dụng cần nén các thư mục. Có nhiều thuật toán nén khác nhau như ZIP, RAR, hoặc 7z. Bạn muốn cho phép người dùng chọn thuật toán nén mà họ muốn sử dụng tại thời gian chạy.

**Yêu cầu:**

1.  Định nghĩa một interface `ICompressionStrategy` với một phương thức:
    *   `void compress(const std::string& folderPath)`
2.  Tạo các lớp `ConcreteStrategy`:
    *   `ZipCompressionStrategy`: Triển khai `compress`, in ra một thông báo như "Compressing folder '[folderPath]' using ZIP algorithm."
    *   `RarCompressionStrategy`: Triển khai `compress`, in ra "Compressing folder '[folderPath]' using RAR algorithm."
    *   `SevenZCompressionStrategy`: Triển khai `compress`, in ra "Compressing folder '[folderPath]' using 7z algorithm."
3.  Định nghĩa một lớp `CompressionContext` (Context):
    *   Lớp này có một trường để giữ một con trỏ (tốt nhất là smart pointer) đến `ICompressionStrategy`.
    *   Có một hàm tạo hoặc một phương thức `setStrategy(std::unique_ptr<ICompressionStrategy> strategy)` để client có thể thiết lập strategy.
    *   Có một phương thức `createArchive(const std::string& folderPath)`: phương thức này sẽ gọi phương thức `compress` trên đối tượng strategy hiện tại.
4.  Trong `main()` (Client):
    *   Tạo một đối tượng `CompressionContext`.
    *   Giả lập việc người dùng chọn các thuật toán khác nhau:
        *   Thiết lập strategy là `ZipCompressionStrategy` và gọi `createArchive`.
        *   Thay đổi strategy thành `RarCompressionStrategy` và gọi lại `createArchive` trên cùng một đối tượng context.
        *   Làm tương tự với `SevenZCompressionStrategy`.

**Thử thách thêm:**
*   Sửa đổi phương thức `compress` để trả về một `std::string` là tên file nén đã tạo (ví dụ: `folderPath + ".zip"`). Phương thức `createArchive` của context sẽ nhận và in ra tên file này.

---

#### Bài tập 2: Hệ thống Sắp xếp Dữ liệu

**Bối cảnh:**
Bạn có một tập hợp dữ liệu (ví dụ: một `std::vector<int>`) và bạn muốn có thể sắp xếp nó bằng các thuật toán khác nhau (ví dụ: Bubble Sort, Quick Sort, Merge Sort) mà không cần thay đổi lớp chứa dữ liệu đó.

**Yêu cầu:**

1.  Định nghĩa một interface `ISortStrategy` với một phương thức:
    *   `void sort(std::vector<int>& data)`
2.  Tạo các lớp `ConcreteStrategy`:
    *   `BubbleSortStrategy`: Triển khai thuật toán Bubble Sort.
    *   `QuickSortStrategy`: Triển khai thuật toán Quick Sort.
    *   `MergeSortStrategy`: Triển khai thuật toán Merge Sort.
    *   *Mẹo:* Bạn không cần phải triển khai các thuật toán này từ đầu một cách hoàn hảo. Mục tiêu là cấu trúc của pattern, vì vậy bạn có thể chỉ cần in ra thông báo "Sorting using [Algorithm Name] sort..." và sau đó gọi `std::sort` để thực sự sắp xếp dữ liệu (trong một ứng dụng thực tế, mỗi lớp sẽ có logic riêng).
3.  Định nghĩa lớp `DataSorter` (Context):
    *   Lớp này chứa một `std::vector<int>`.
    *   Có một trường để giữ strategy sắp xếp.
    *   Có phương thức `setSortStrategy(...)` để thay đổi thuật toán.
    *   Có phương thức `sortData()`: phương thức này sẽ gọi `sort()` trên đối tượng strategy hiện tại, truyền vào vector dữ liệu của chính `DataSorter`.
    *   Có phương thức `printData()` để hiển thị dữ liệu.
4.  Trong `main()` (Client):
    *   Tạo một đối tượng `DataSorter` với một vector dữ liệu chưa được sắp xếp.
    *   In dữ liệu ban đầu.
    *   Thiết lập `BubbleSortStrategy`, gọi `sortData()`, và in kết quả.
    *   Thiết lập lại dữ liệu về trạng thái chưa sắp xếp.
    *   Thiết lập `QuickSortStrategy`, gọi `sortData()`, và in kết quả.

**Thử thách thêm:**
*   Làm thế nào để client có thể truyền một hàm lambda (hoặc `std::function`) làm strategy thay vì một đối tượng lớp? (Gợi ý: Lớp context có thể lưu trữ một `std::function<void(std::vector<int>&)>` thay vì `std::unique_ptr<ISortStrategy>`).

---

#### Bài tập 3: Hệ thống Thanh toán Đa dạng

**Bối cảnh:**
Một trang web thương mại điện tử cần hỗ trợ nhiều phương thức thanh toán khác nhau: Thẻ tín dụng, PayPal, và Tiền mã hóa (Crypto). Mỗi phương thức có một quy trình xử lý thanh toán khác nhau.

**Yêu cầu:**

1.  Định nghĩa interface `IPaymentStrategy` với một phương thức:
    *   `bool pay(double amount)` (trả về `true` nếu thanh toán thành công).
2.  Tạo các lớp `ConcreteStrategy`:
    *   `CreditCardPaymentStrategy`:
        *   Trong hàm tạo, nhận vào các thông tin như tên chủ thẻ, số thẻ, mã CVV.
        *   Phương thức `pay` sẽ in ra "Paying $[amount] using Credit Card [card number]." và trả về `true`.
    *   `PayPalPaymentStrategy`:
        *   Trong hàm tạo, nhận vào email và mật khẩu (dĩ nhiên đây chỉ là giả lập).
        *   Phương thức `pay` sẽ in ra "Paying $[amount] using PayPal account [email]." và trả về `true`.
    *   `CryptoPaymentStrategy`:
        *   Trong hàm tạo, nhận vào địa chỉ ví (wallet address).
        *   Phương thức `pay` sẽ in ra "Paying $[amount] in crypto to wallet [wallet address]." và trả về `true`.
3.  Định nghĩa lớp `PaymentProcessor` (Context):
    *   Có một trường để giữ strategy thanh toán.
    *   Có phương thức `setPaymentStrategy(...)`.
    *   Có phương thức `processPayment(double amount)`: phương thức này sẽ gọi `pay(amount)` trên strategy hiện tại và in ra thông báo thành công hoặc thất bại dựa trên kết quả trả về.
4.  Trong `main()` (Client):
    *   Giả lập một giỏ hàng có tổng số tiền là 250.50.
    *   Tạo một đối tượng `PaymentProcessor`.
    *   **Lựa chọn 1 (Thẻ tín dụng):** Tạo một `CreditCardPaymentStrategy` với thông tin giả, đặt nó làm strategy cho `PaymentProcessor`, và thực hiện thanh toán.
    *   **Lựa chọn 2 (PayPal):** Tạo một `PayPalPaymentStrategy`, đặt nó làm strategy, và thực hiện thanh toán.
    *   **Lựa chọn 3 (Crypto):** Làm tương tự với `CryptoPaymentStrategy`.

**Gợi ý:**
*   Bài tập này cho thấy cách các strategy có thể có trạng thái nội tại riêng (thông tin thẻ, tài khoản PayPal) được khởi tạo khi tạo đối tượng strategy.

---

**Lời khuyên chung:**

*   **Tập trung vào Interface:** Interface của Strategy là phần quan trọng nhất. Nó định nghĩa hợp đồng chung mà tất cả các thuật toán phải tuân theo.
*   **Context không biết chi tiết:** Hãy nhớ rằng Context không nên biết bất cứ điều gì về lớp cụ thể của strategy. Nó chỉ làm việc thông qua interface.
*   **Client là người quyết định:** Client có trách nhiệm chọn strategy phù hợp và cung cấp nó cho Context.