### Bài tập về Visitor Pattern (C++)

**Mục tiêu chung:** Hiểu rõ cách tách rời thuật toán khỏi cấu trúc đối tượng, cách triển khai double dispatch, và cách quản lý trạng thái bên trong một visitor.

---

#### Bài tập 1: Hệ thống Tính toán Thuế cho các loại Tài sản

**Bối cảnh:**
Một công ty tài chính cần tính thuế cho các loại tài sản khác nhau mà khách hàng sở hữu. Mỗi loại tài sản có một cách tính thuế riêng. Hệ thống đã có các lớp `Asset` (Tài sản) như `BankAccount`, `RealEstate` (Bất động sản), và `Stock` (Cổ phiếu). Bạn cần thêm chức năng tính thuế mà không được sửa đổi các lớp `Asset` này (ngoài việc thêm phương thức `accept`).

**Yêu cầu:**

1.  Định nghĩa một interface `IAsset` (Element) với phương thức ảo thuần túy `accept(IVisitor* visitor)`.
2.  Tạo các lớp `ConcreteElement`:
    *   `BankAccount`: có thuộc tính `double balance`.
    *   `RealEstate`: có thuộc tính `double estimatedValue` và `std::string location`.
    *   `Stock`: có thuộc tính `int numberOfShares` và `double sharePrice`.
    *   Mỗi lớp này kế thừa từ `IAsset` và triển khai phương thức `accept`.
3.  Định nghĩa interface `IVisitor` với các phương thức `visit`:
    *   `visitBankAccount(BankAccount* account)`.
    *   `visitRealEstate(RealEstate* property)`.
    *   `visitStock(Stock* stock)`.
4.  Tạo một lớp `ConcreteVisitor` là `TaxCalculatorVisitor`:
    *   Lớp này có một thuộc tính `double totalTax` để tích lũy tổng số thuế.
    *   Triển khai các phương thức `visit`:
        *   `visitBankAccount`: Thuế là 5% trên số dư.
        *   `visitRealEstate`: Thuế là 10% trên giá trị ước tính.
        *   `visitStock`: Thuế là 7% trên tổng giá trị cổ phiếu (`numberOfShares * sharePrice`).
    *   Mỗi phương thức `visit` sẽ tính toán thuế cho tài sản tương ứng và cộng vào `totalTax`.
    *   Thêm một phương thức `getTotalTax()` để lấy kết quả cuối cùng.
5.  Trong `main()`:
    *   Tạo một `std::vector` chứa các con trỏ (tốt nhất là smart pointer) đến các đối tượng `IAsset` khác nhau.
    *   Tạo một đối tượng `TaxCalculatorVisitor`.
    *   Duyệt qua vector tài sản, gọi `asset->accept(&taxVisitor)` trên mỗi tài sản.
    *   Sau khi duyệt xong, gọi `taxVisitor.getTotalTax()` và in ra tổng số thuế.

**Thử thách thêm:**
*   Tạo một visitor thứ hai, ví dụ `NetWorthVisitor`, để tính tổng giá trị tài sản ròng của khách hàng. Visitor này sẽ cộng dồn giá trị của từng tài sản thay vì thuế. Điều này cho thấy sự linh hoạt của pattern khi thêm một hoạt động hoàn toàn mới.

---

#### Bài tập 2: Tối ưu hóa và Phân tích Cây Cú pháp Trừu tượng (AST)

**Bối cảnh:**
Bạn đang xây dựng một trình biên dịch đơn giản. Sau khi phân tích cú pháp (parsing), bạn có một Cây Cú pháp Trừu tượng (Abstract Syntax Tree - AST) đại diện cho mã nguồn. Cây này được xây dựng từ các nút (nodes) khác nhau như `NumberNode`, `VariableNode`, `BinaryOperationNode` (ví dụ: phép cộng, trừ), `AssignmentNode`. Bạn cần thực hiện các hoạt động trên cây này như:
1.  **PrettyPrint:** In ra biểu thức dưới dạng chuỗi có thể đọc được (ví dụ: `(5 + x)`).
2.  **Evaluate:** Tính toán giá trị của biểu thức (nếu có thể).

**Yêu cầu:**

1.  Định nghĩa một interface `IAstNode` (Element) với `accept(IVisitor* visitor)`.
2.  Tạo các lớp `ConcreteElement` (Node) kế thừa từ `IAstNode`:
    *   `NumberNode`: chứa một giá trị `double`.
    *   `VariableNode`: chứa một `std::string` tên biến.
    *   `BinaryOperationNode`: chứa `char operation` (`+`, `-`, `*`, `/`) và hai con trỏ (`std::unique_ptr<IAstNode>`) đến toán hạng trái (`left`) và phải (`right`). Đây là một ví dụ về pattern **Composite**.
    *   `AssignmentNode`: chứa `std::unique_ptr<VariableNode>` và `std::unique_ptr<IAstNode>` cho biểu thức được gán.
    *   Triển khai `accept` cho mỗi lớp. `BinaryOperationNode` và `AssignmentNode` cần phải gọi `accept` trên các nút con của chúng.
3.  Định nghĩa `IVisitor` với các phương thức `visit` cho từng loại nút.
4.  Tạo `ConcreteVisitor` thứ nhất: `PrettyPrintVisitor`.
    *   `visitBinaryOperationNode`: sẽ gọi `accept` trên `left`, sau đó in ra `operation`, rồi gọi `accept` trên `right`. Có thể cần in thêm dấu ngoặc đơn.
    *   Các phương thức `visit` khác chỉ cần in ra giá trị hoặc tên của nút.
    *   Visitor này có thể có một `std::stringstream` để xây dựng chuỗi output.
5.  Tạo `ConcreteVisitor` thứ hai: `EvaluationVisitor`.
    *   Visitor này cần một cách để lưu trữ giá trị của các biến (ví dụ: `std::map<std::string, double> context`).
    *   Nó cũng cần một cách để lưu trữ kết quả của các biểu thức con đã được tính toán (ví dụ: một `std::stack<double>`).
    *   `visitNumberNode`: đẩy giá trị của nó vào stack.
    *   `visitVariableNode`: lấy giá trị từ `context` và đẩy vào stack.
    *   `visitBinaryOperationNode`: gọi `accept` trên `left` và `right` (sẽ đẩy 2 giá trị vào stack), sau đó lấy 2 giá trị này ra, thực hiện phép toán, và đẩy kết quả trở lại stack.
6.  Trong `main()`:
    *   Xây dựng một cây AST đơn giản, ví dụ cho biểu thức `a = (5 + b) * 2`.
    *   Tạo một `PrettyPrintVisitor` và cho nó duyệt cây để in ra biểu thức.
    *   Tạo một `EvaluationVisitor`, cung cấp cho nó một `context` (ví dụ: `b = 10`), và cho nó duyệt cây để tính giá trị của `a`. In kết quả cuối cùng.

**Gợi ý:**
*   Bài tập này kết hợp **Visitor** và **Composite**. Cách `accept` được gọi đệ quy trong các nút composite là một kỹ thuật phổ biến.
*   `EvaluationVisitor` là một ví dụ về visitor có trạng thái phức tạp (cần context và stack).

---

#### Bài tập 3: Cấu hình Hệ thống cho các loại Server khác nhau

**Bối cảnh:**
Bạn là một quản trị viên hệ thống cần tự động hóa việc cấu hình cho một cụm server gồm nhiều loại khác nhau: `WebServer`, `DatabaseServer`, và `MailServer`. Mỗi server có các thành phần phần cứng khác nhau (CPU, RAM, Disk). Bạn muốn thực hiện các hoạt động như:
1.  **GenerateReport:** Tạo một báo cáo chi tiết về cấu hình của toàn bộ cụm.
2.  **RunDiagnostics:** Chạy các bài kiểm tra chẩn đoán khác nhau cho từng loại server.

**Yêu cầu:**

1.  Định nghĩa các lớp `HardwareComponent` như `CPU`, `RAM`, `Disk`. Chúng không cần phải là element trong pattern này.
2.  Định nghĩa interface `IServer` (Element) với `accept(IVisitor* visitor)`.
3.  Tạo các lớp `ConcreteElement`:
    *   `WebServer`: có `std::vector<CPU>`, `RAM`, `Disk` và thuộc tính riêng như `std::string httpSoftware` (e.g., "Nginx").
    *   `DatabaseServer`: tương tự, có thêm `std::string databaseSoftware` (e.g., "PostgreSQL").
    *   `MailServer`: tương tự, có thêm `std::string mailSoftware` (e.g., "Postfix").
    *   Triển khai `accept` cho mỗi lớp.
4.  Định nghĩa `IVisitor` với các phương thức `visitWebServer`, `visitDatabaseServer`, `visitMailServer`.
5.  Tạo `ConcreteVisitor` thứ nhất: `ReportVisitor`.
    *   Visitor này sẽ xây dựng một báo cáo dạng chuỗi.
    *   `visitWebServer`: thêm thông tin về phần cứng và phần mềm web server vào báo cáo.
    *   Tương tự cho các loại server khác.
6.  Tạo `ConcreteVisitor` thứ hai: `DiagnosticsVisitor`.
    *   `visitWebServer`: In ra "Running HTTP connection tests on Nginx..."
    *   `visitDatabaseServer`: In ra "Checking database integrity for PostgreSQL..."
    *   `visitMailServer`: In ra "Testing SMTP and IMAP ports on Postfix..."
7.  Trong `main()`:
    *   Tạo một `std::vector<std::unique_ptr<IServer>>` đại diện cho cụm server của bạn.
    *   Tạo một `ReportVisitor`, duyệt cụm server và in ra báo cáo tổng hợp.
    *   Tạo một `DiagnosticsVisitor` và duyệt cụm server để "chạy" các bài kiểm tra.

**Thử thách thêm (Vấn đề truy cập private):**
*   Giả sử các thuộc tính của các lớp Server là `private`. Làm thế nào để Visitor có thể truy cập chúng?
    *   **Cách 1:** Thêm các phương thức getter public vào các lớp Server.
    *   **Cách 2 (C++):** Khai báo `class ReportVisitor;` và `class DiagnosticsVisitor;` trước định nghĩa lớp `IServer`, sau đó trong mỗi lớp server cụ thể, thêm `friend class ReportVisitor;` và `friend class DiagnosticsVisitor;`. Thảo luận ưu và nhược điểm của cách này so với việc dùng getter.

---

**Lời khuyên chung:**

*   **Forward Declaration:** Khi `IVisitor` cần tham chiếu đến các lớp `ConcreteElement` và ngược lại, bạn sẽ cần sử dụng forward declaration để tránh lỗi circular dependency trong file header.
*   **Double Dispatch là cốt lõi:** Luôn tự hỏi "Cuộc gọi đầu tiên đi đâu? Cuộc gọi thứ hai đi đâu?". Điều này giúp bạn hiểu rõ cơ chế hoạt động.
*   **Visitor không chỉ để đọc:** Visitor có thể sửa đổi trạng thái của các element mà nó "thăm", mặc dù các ví dụ trên chủ yếu tập trung vào việc đọc và tích lũy thông tin.