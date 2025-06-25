### Bài tập về Chain of Responsibility Pattern (C++)

**Mục tiêu chung:** Hiểu rõ cách xây dựng chuỗi các đối tượng xử lý, cách mỗi handler quyết định xử lý hoặc chuyển tiếp yêu cầu, và cách client tương tác với chuỗi.

---

#### Bài tập 1: Hệ thống Lọc Email Đơn giản

**Bối cảnh:**
Bạn cần xây dựng một hệ thống lọc email cơ bản. Các email đến cần được xử lý qua một chuỗi các bộ lọc:
1.  **SpamFilter:** Kiểm tra xem email có chứa các từ khóa spam hay không. Nếu có, đánh dấu là spam và có thể dừng xử lý.
2.  **LengthFilter:** Kiểm tra độ dài của nội dung email. Nếu quá ngắn hoặc quá dài, có thể đánh dấu là "cần xem xét" (review).
3.  **AttachmentFilter:** Kiểm tra xem email có tệp đính kèm nguy hiểm không (ví dụ: dựa trên phần mở rộng .exe, .bat). Nếu có, đánh dấu là "nguy hiểm" và dừng xử lý.
4.  **FinalCategorizer:** Nếu email vượt qua các bộ lọc trên, phân loại nó vào các thư mục như "Inbox", "Promotions", "Social" dựa trên người gửi hoặc tiêu đề.

**Yêu cầu:**

1.  Định nghĩa struct `Email` chứa các thông tin: `std::string sender`, `std::string subject`, `std::string body`, `std::vector<std::string> attachments` (tên file đính kèm), `std::string status` (ví dụ: "Inbox", "Spam", "Review", "Dangerous").
2.  Định nghĩa interface `IEmailHandler` với:
    *   `setNext(IEmailHandler* handler)`
    *   `process(Email* email)` (có thể trả về `void` hoặc `bool` để chỉ ra có tiếp tục hay không).
3.  Tạo lớp cơ sở `BaseEmailHandler` (tùy chọn) để quản lý `nextHandler` và cung cấp logic chuyển tiếp mặc định.
4.  Tạo các lớp handler cụ thể: `SpamFilterHandler`, `LengthFilterHandler`, `AttachmentFilterHandler`, `FinalCategorizerHandler`.
    *   Mỗi handler thực hiện logic kiểm tra/phân loại của mình.
    *   Quyết định xem có cập nhật `email->status` không.
    *   Quyết định xem có gọi handler tiếp theo trong chuỗi không, hay dừng lại.
5.  Trong `main()`:
    *   Tạo các đối tượng handler.
    *   Xây dựng chuỗi các handler theo thứ tự hợp lý.
    *   Tạo một vài đối tượng `Email` với các đặc điểm khác nhau (spam, quá ngắn, có file .exe, email bình thường).
    *   Cho mỗi email đi qua chuỗi handler.
    *   In ra `status` cuối cùng của mỗi email.

**Gợi ý:**
*   `SpamFilterHandler` có thể dừng chuỗi nếu phát hiện spam.
*   `AttachmentFilterHandler` có thể dừng chuỗi nếu phát hiện tệp nguy hiểm.
*   `LengthFilterHandler` có thể chỉ cập nhật status và luôn chuyển tiếp.
*   `FinalCategorizerHandler` là handler cuối cùng nếu email "sạch".

---

#### Bài tập 2: Hệ thống Xử lý Giao dịch Ngân hàng

**Bối cảnh:**
Một ngân hàng cần xử lý các yêu cầu giao dịch (ví dụ: rút tiền, chuyển tiền, kiểm tra số dư). Mỗi yêu cầu cần được xử lý qua nhiều bước:
1.  **AuthenticationStep:** Xác thực thông tin khách hàng (ví dụ: mã PIN, thông tin đăng nhập). Nếu thất bại, từ chối giao dịch.
2.  **BalanceCheckStep:** Kiểm tra số dư đủ để thực hiện giao dịch (đối với rút tiền, chuyển tiền). Nếu không đủ, từ chối.
3.  **FraudDetectionStep:** Kiểm tra các dấu hiệu gian lận (ví dụ: giao dịch số tiền lớn bất thường, nhiều giao dịch nhỏ liên tiếp). Nếu nghi ngờ, có thể tạm giữ giao dịch hoặc yêu cầu xác minh thêm.
4.  **TransactionLoggingStep:** Ghi log lại mọi thông tin giao dịch (thành công hay thất bại và lý do). Bước này luôn được thực hiện.
5.  **ExecutionStep:** Nếu mọi thứ ổn, thực hiện giao dịch (trừ tiền, cộng tiền).

**Yêu cầu:**

1.  Định nghĩa struct `TransactionRequest` chứa: `std::string accountNumber`, `std::string transactionType` ("withdraw", "transfer", "balance"), `double amount`, `std::string credentials`, `bool isAuthenticated`, `bool isSufficientBalance`, `bool isFraudSuspected`, `bool isExecuted`, `std::string statusMessage`.
2.  Định nghĩa interface `ITransactionHandler` và lớp cơ sở `BaseTransactionHandler` tương tự bài 1.
3.  Tạo các lớp handler cụ thể: `AuthenticationHandler`, `BalanceCheckHandler`, `FraudDetectionHandler`, `TransactionLoggingHandler`, `ExecutionHandler`.
    *   `AuthenticationHandler` và `BalanceCheckHandler` có thể dừng chuỗi nếu điều kiện không đáp ứng.
    *   `FraudDetectionHandler` có thể cập nhật `isFraudSuspected` và `statusMessage`, sau đó có thể quyết định dừng (nếu gian lận rõ ràng) hoặc chuyển tiếp (nếu chỉ nghi ngờ và cần các bước sau xử lý).
    *   `TransactionLoggingHandler` luôn ghi log và luôn chuyển tiếp (nếu có handler tiếp theo).
    *   `ExecutionHandler` chỉ thực hiện nếu các bước trước đó không có vấn đề nghiêm trọng.
4.  Trong `main()`:
    *   Tạo chuỗi handler. Lưu ý rằng `TransactionLoggingHandler` có thể được đặt ở nhiều vị trí trong chuỗi (ví dụ, log trước khi thực thi và log sau khi thực thi, hoặc chỉ log ở cuối). Hãy thử nghiệm với việc đặt nó ở cuối.
    *   Tạo các `TransactionRequest` khác nhau (rút tiền thành công, rút tiền không đủ số dư, giao dịch bị nghi ngờ gian lận, kiểm tra số dư).
    *   Cho mỗi request đi qua chuỗi.
    *   In ra `statusMessage` và các cờ trạng thái của `TransactionRequest`.

**Thử thách thêm:**
*   Làm thế nào để `TransactionLoggingHandler` có thể ghi log cả trạng thái *trước* và *sau* khi một handler khác xử lý? (Gợi ý: một handler có thể gọi `nextHandler->handle()` và sau đó thực hiện hành động của mình).
*   Nếu `FraudDetectionStep` quyết định giao dịch cần "xác minh thêm" thay vì dừng hẳn, làm thế nào để chuỗi thể hiện điều này? (Có thể có một nhánh xử lý khác hoặc một trạng thái đặc biệt).

---

#### Bài tập 3: Bộ điều phối Sự kiện Giao diện Người dùng (GUI)

**Bối cảnh:**
Trong một ứng dụng GUI, các sự kiện (click chuột, nhấn phím) được gửi đến thành phần GUI đang có focus. Nếu thành phần đó không xử lý được sự kiện, nó sẽ chuyển sự kiện lên cho thành phần cha (container) của nó, và cứ thế tiếp tục lên đến cửa sổ chính của ứng dụng. Đây là một ví dụ kinh điển của Chain of Responsibility.

**Yêu cầu:**

1.  Định nghĩa struct `GUIEvent` chứa: `std::string eventType` ("click", "keypress"), `int x`, `int y` (tọa độ cho click), `char key` (cho keypress).
2.  Định nghĩa interface `IGUIComponent` (đây sẽ là Handler):
    *   `void setParent(IGUIComponent* parent)` (thay vì `setNext`, vì "next" ở đây là "parent").
    *   `bool handleEvent(GUIEvent* event)` (trả về `true` nếu sự kiện đã được xử lý, `false` nếu không và nên được chuyển lên).
    *   `std::string getName() const` (để dễ debug).
3.  Tạo lớp cơ sở `BaseGUIComponent` lưu trữ `parentComponent`. Phương thức `handleEvent` mặc định của nó sẽ kiểm tra `parentComponent` và gọi `parentComponent->handleEvent(event)` nếu có.
4.  Tạo các lớp component cụ thể:
    *   `Button`: Chỉ xử lý sự kiện "click" nếu tọa độ `(x, y)` nằm trong vùng của button.
    *   `TextField`: Chỉ xử lý sự kiện "keypress".
    *   `Panel`: Là một container, có thể chứa các component khác. Nó không tự xử lý sự kiện nào mà chỉ chuyển lên cho parent của nó (sau khi các con của nó không xử lý được - điều này hơi khác với CoR truyền thống, bạn có thể chọn cách triển khai: Panel cố xử lý trước, hoặc Panel chỉ làm nhiệm vụ chuyển tiếp). Cho bài này, giả sử Panel không xử lý mà chỉ chuyển.
    *   `Window`: Là container cấp cao nhất. Có thể xử lý một số sự kiện chung (ví dụ: "keypress" với phím ESC để đóng cửa sổ).
5.  Trong `main()`:
    *   Tạo một cấu trúc GUI đơn giản: một `Window` chứa một `Panel`, `Panel` đó chứa một `Button` và một `TextField`.
    *   Thiết lập mối quan hệ cha-con (ví dụ: `button->setParent(panel)`, `panel->setParent(window)`).
    *   Tạo các `GUIEvent` khác nhau (click vào button, click ra ngoài button nhưng trong panel, nhấn phím khi focus vào textfield, nhấn phím ESC).
    *   Gửi sự kiện đến component "lá" nhất (ví dụ: `button->handleEvent(&clickEvent)`).
    *   In ra component nào đã xử lý sự kiện (hoặc nếu không ai xử lý).

**Gợi ý:**
*   Mỗi component cần biết "vùng" của nó để xử lý sự kiện click.
*   Cấu trúc ở đây là một cây, và chuỗi trách nhiệm đi ngược từ lá lên gốc.
*   Phương thức `handleEvent` của `Button` và `TextField` sẽ trả về `true` nếu chúng xử lý sự kiện, ngược lại trả về kết quả của `BaseGUIComponent::handleEvent(event)` (tức là chuyển cho cha).

---

**Lời khuyên chung:**

*   **Tập trung vào logic `handle`:** Phần cốt lõi là quyết định của mỗi handler: "Tôi có xử lý cái này không? Nếu có, tôi có dừng chuỗi không? Nếu không, tôi chuyển tiếp như thế nào?"
*   **Thiết kế đối tượng Request:** Đối tượng yêu cầu (Email, TransactionRequest, GUIEvent) nên chứa đủ thông tin cho các handler làm việc và cũng có thể chứa các trường để handler cập nhật trạng thái.
*   **Thứ tự chuỗi:** Suy nghĩ về thứ tự các handler trong chuỗi vì nó ảnh hưởng lớn đến kết quả.