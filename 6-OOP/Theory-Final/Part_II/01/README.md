**CÂU 2: CÀI ĐẶT HÀNG ĐỢI (QUEUE) SỬ DỤNG INTERFACE VÀ DANH SÁCH LIÊN KẾT**

Hàng đợi (Queue) là một cấu trúc dữ liệu rất quen thuộc, hoạt động theo nguyên tắc **FIFO (First In, First Out)**, nghĩa là phần tử nào được thêm vào trước sẽ được lấy ra trước.

*Lưu ý: Sinh viên không được sử dụng các lớp `std::queue`, `std::list` hay các cấu trúc dữ liệu hàng đợi/danh sách có sẵn khác trong thư viện chuẩn C++ để cài đặt các yêu cầu cốt lõi của bài toán này. Sinh viên phải tự xây dựng dựa trên danh sách liên kết đơn.*

**a) (0.5 điểm) Khai báo Interface `IQueue`**

Hãy khai báo một lớp trừu tượng (abstract class) đóng vai trò như một interface, đặt tên là `IQueue`, để quản lý một hàng đợi (queue) chứa các số nguyên. `IQueue` cần có các hàm thuần ảo (pure virtual functions) sau:
i.  `virtual void enqueue(int value) = 0;` : Thêm một phần tử `value` vào cuối hàng đợi.
ii. `virtual int dequeue() = 0;` : Lấy và xóa phần tử ở đầu hàng đợi, đồng thời trả về giá trị của phần tử được xóa.
iii. `virtual int peek() const = 0;` : Trả về giá trị của phần tử ở đầu hàng đợi mà không xóa nó.
iv. `virtual bool isEmpty() const = 0;` : Kiểm tra xem hàng đợi có rỗng không.
v.  `virtual int getSize() const = 0;`: Trả về số lượng phần tử hiện tại đang có trong hàng đợi.
vi. `virtual void clear() = 0;`: Xóa tất cả các phần tử ra khỏi hàng đợi, làm cho hàng đợi trở nên rỗng.

**b) (0.5 điểm) Khai báo lớp `LinkedQueue`**

Hãy khai báo một lớp `LinkedQueue`, kế thừa từ interface `IQueue` đã định nghĩa ở trên. Lớp `LinkedQueue` sẽ cài đặt các chức năng của hàng đợi bằng cách sử dụng một **danh sách liên kết đơn (singly linked list)** bên trong để lưu trữ các phần tử.
*   Lớp `LinkedQueue` cần định nghĩa một cấu trúc (struct) hoặc lớp lồng (nested class) tên là `Node` để biểu diễn một nút trong danh sách liên kết. Mỗi `Node` chứa một giá trị số nguyên (`data`) và một con trỏ (`next`) đến nút kế tiếp.
*   Lớp `LinkedQueue` cần có các con trỏ thành viên phù hợp để quản lý đầu (`frontNode` hoặc `head`) và cuối (`rearNode` hoặc `tail`) của danh sách liên kết, cũng như một biến thành viên để theo dõi số lượng phần tử (`currentSize`).

**c) (1.5 điểm) Cài đặt các phương thức cho lớp `LinkedQueue`**

Hãy cài đặt chi tiết các phương thức đã được khai báo trong interface `IQueue` cho lớp `LinkedQueue` mà bạn vừa định nghĩa ở câu b. Cụ thể:
*   `void enqueue(int value)`
*   `int dequeue()` (phiên bản chưa xử lý ngoại lệ ở bước này)
*   `int peek() const` (phiên bản chưa xử lý ngoại lệ ở bước này)
*   `bool isEmpty() const`
*   `int getSize() const`
*   `void clear()`
*   Đồng thời, cài đặt **hàm tạo (constructor)** cho lớp `LinkedQueue` để khởi tạo một hàng đợi rỗng, và **hàm hủy (destructor)** để giải phóng tất cả các nút trong danh sách liên kết khi đối tượng `LinkedQueue` bị hủy, tránh rò rỉ bộ nhớ.

**d) (0.5 điểm) Xử lý ngoại lệ cho `dequeue()` và `peek()` và minh họa**

Thao tác `dequeue()` và `peek()` có thể bị lỗi khi hàng đợi hiện tại đang rỗng (không có phần tử nào để lấy ra hoặc xem).
*   Hãy **chỉnh sửa lại** việc cài đặt hai hàm `int dequeue()` và `int peek() const` trong lớp `LinkedQueue` bằng cách áp dụng cơ chế xử lý ngoại lệ (exception handling) đơn giản. Cụ thể, nếu hàng đợi rỗng khi các hàm này được gọi, chúng phải **ném (throw)** một ngoại lệ kiểu `std::runtime_error` với thông báo là "Error: Queue is empty."
*   Viết một đoạn code trong hàm `main()` để minh họa việc sử dụng hàm `dequeue()` (hoặc `peek()`) trong trường hợp hàng đợi có phần tử (hoạt động bình thường) và trong trường hợp hàng đợi rỗng gây ra lỗi. Sử dụng khối `try-catch` để bắt và xử lý ngoại lệ được ném ra, in thông báo lỗi ra màn hình.