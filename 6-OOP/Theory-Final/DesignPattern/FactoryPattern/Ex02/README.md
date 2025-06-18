### Bài tập: Hệ thống Tạo Hình học (Geometry Factory)

**Bối cảnh:**
Bạn đang xây dựng một ứng dụng vẽ đồ họa đơn giản. Ứng dụng này cần có khả năng tạo ra nhiều loại hình học khác nhau (ví dụ: Hình tròn, Hình chữ nhật, Hình tam giác). Ban đầu, bạn có thể chỉ hỗ trợ một vài loại, nhưng bạn muốn hệ thống dễ dàng mở rộng để thêm các loại hình mới trong tương lai mà không cần sửa đổi nhiều code hiện có, đặc biệt là code client (phần code sử dụng các hình học này để vẽ).

**Yêu cầu:**
Sử dụng **Factory Method Pattern** để thiết kế và triển khai một hệ thống cho phép tạo ra các đối tượng hình học.

**Các bước thực hiện:**

1.  **Định nghĩa Product Interface (`Shape`):**
    *   Tạo một interface (lớp trừu tượng thuần túy trong C++) tên là `Shape`.
    *   Interface này nên có ít nhất một phương thức trừu tượng, ví dụ:
        *   `virtual void draw() const = 0;` (để vẽ hình)
        *   `virtual double getArea() const = 0;` (để tính diện tích)
    *   Đừng quên virtual destructor!

2.  **Định nghĩa Concrete Products (`Circle`, `Rectangle`, `Triangle`):**
    *   Tạo các lớp cụ thể triển khai interface `Shape`:
        *   `Circle`: Cần có bán kính. Triển khai `draw()` (ví dụ: in ra "Drawing a Circle with radius X") và `getArea()`.
        *   `Rectangle`: Cần có chiều dài và chiều rộng. Triển khai `draw()` và `getArea()`.
        *   `Triangle`: Cần có 3 cạnh (hoặc đáy và chiều cao, tùy bạn chọn cách đơn giản). Triển khai `draw()` và `getArea()`.

3.  **Định nghĩa Creator (`ShapeFactory`):**
    *   Tạo một lớp trừu tượng (hoặc một lớp cơ sở với triển khai mặc định) tên là `ShapeFactory`.
    *   Lớp này sẽ chứa **Factory Method** trừu tượng (hoặc virtual):
        *   `virtual std::unique_ptr<Shape> createShape() const = 0;`
    *   `ShapeFactory` cũng có thể có một số logic nghiệp vụ sử dụng `Shape`. Ví dụ:
        *   `void describeShape() const { std::cout << "Creating a shape: "; auto shape = createShape(); if (shape) shape->draw(); }`

4.  **Định nghĩa Concrete Creators (`CircleFactory`, `RectangleFactory`, `TriangleFactory`):**
    *   Tạo các lớp con của `ShapeFactory`:
        *   `CircleFactory`: Ghi đè `createShape()` để trả về một `std::unique_ptr<Circle>`.
        *   `RectangleFactory`: Ghi đè `createShape()` để trả về một `std::unique_ptr<Rectangle>`.
        *   `TriangleFactory`: Ghi đè `createShape()` để trả về một `std::unique_ptr<Triangle>`.
    *   Trong phương thức `createShape()` của các Concrete Creator này, bạn có thể quyết định các thuộc tính mặc định cho hình học (ví dụ: bán kính mặc định cho Circle) hoặc chúng có thể nhận tham số trong constructor của Factory (ví dụ `CircleFactory(double defaultRadius)`). Tuy nhiên, để đơn giản cho bài tập này, bạn có thể hardcode giá trị trong phương thức `createShape()`.

5.  **Viết Client Code (ví dụ trong `main()`):**
    *   Trong hàm `main()`, tạo ra các đối tượng `ConcreteCreator` khác nhau.
    *   Gọi phương thức `describeShape()` (hoặc trực tiếp `createShape()` rồi gọi `draw()` và `getArea()`) trên các đối tượng factory này để thấy các loại hình khác nhau được tạo ra.
    *   Client code chỉ nên làm việc với interface `ShapeFactory` và `Shape`, không nên biết về các lớp cụ thể như `Circle` hay `CircleFactory` (trừ lúc khởi tạo factory ban đầu).

**Sơ đồ lớp (Mermaid):**
Bạn hãy tự vẽ sơ đồ lớp bằng Mermaid dựa trên mô tả trên. Nó sẽ tương tự như ví dụ Logistics nhưng với các tên lớp khác.

**Gợi ý:**
*   Sử dụng `std::unique_ptr` để quản lý bộ nhớ cho các đối tượng `Shape` được tạo ra.
*   In ra các thông điệp đơn giản trong các phương thức `draw()` và `getArea()` để kiểm tra.

**Câu hỏi nâng cao (Bonus):**

1.  **Factory Method với tham số:**
    Thay vì có nhiều `ConcreteCreator` (như `CircleFactory`, `RectangleFactory`), hãy thử sửa đổi `ShapeFactory` sao cho `createShape()` nhận một tham số (ví dụ: một `enum ShapeType { CIRCLE, RECTANGLE, TRIANGLE }` hoặc một `std::string typeName`).
    Khi đó, bạn chỉ cần một `ConcreteCreator` (hoặc `ShapeFactory` không còn là abstract nữa) và nó sẽ quyết định tạo `Shape` nào dựa trên tham số này. So sánh ưu nhược điểm của cách này so với việc có nhiều `ConcreteCreator`.

2.  **Cấu hình Factory:**
    Làm thế nào để client code có thể quyết định sử dụng `CircleFactory` hay `RectangleFactory` mà không cần hardcode tên lớp trong `main()`? (Ví dụ: đọc từ một file config đơn giản, hoặc nhận input từ người dùng).

**Mục tiêu của bài tập:**
*   Hiểu rõ vai trò của từng thành phần trong Factory Method Pattern.
*   Thực hành cách tách biệt việc tạo đối tượng khỏi việc sử dụng đối tượng.
*   Thấy được lợi ích của việc dễ dàng mở rộng hệ thống khi thêm các "Product" mới.