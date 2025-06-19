### Bài tập: Xây dựng Giao diện Người dùng Đa Nền tảng (Cross-Platform UI Toolkit)

**Bối cảnh:**
Bạn đang phát triển một framework UI cho phép các nhà phát triển tạo ra các ứng dụng desktop có thể chạy trên nhiều hệ điều hành khác nhau (ví dụ: Windows, macOS, Linux). Mỗi hệ điều hành có phong cách và cảm nhận riêng cho các thành phần UI (nút bấm, hộp kiểm, thanh trượt, v.v.).

Mục tiêu là cung cấp một cách để tạo ra các bộ thành phần UI sao cho tất cả các thành phần trong một bộ đều nhất quán với một hệ điều hành cụ thể. Ví dụ, nếu ứng dụng đang chạy trên Windows, tất cả các nút bấm, hộp kiểm phải có giao diện của Windows. Tương tự với macOS.

**Yêu cầu:**
Sử dụng **Abstract Factory Pattern** để thiết kế và triển khai một hệ thống cho phép tạo ra các họ thành phần UI (ví dụ: một họ cho Windows, một họ cho macOS).

**Các bước thực hiện:**

1.  **Định nghĩa Abstract Products (Giao diện Thành phần UI):**
    *   Tạo các interface (lớp trừu tượng thuần túy trong C++) cho từng loại thành phần UI cơ bản. Ví dụ:
        *   `IButton`:
            *   `virtual void paint() const = 0;` (để "vẽ" nút)
            *   `virtual void onClick(std::function<void()>) = 0;` (để gán hành động khi click)
        *   `ICheckbox`:
            *   `virtual void paint() const = 0;`
            *   `virtual void setChecked(bool checked) = 0;`
            *   `virtual bool isChecked() const = 0;`
        *   `ITextBox`: (Nếu bạn muốn thêm)
            *   `virtual void paint() const = 0;`
            *   `virtual void setText(const std::string& text) = 0;`
            *   `virtual std::string getText() const = 0;`
    *   Nhớ virtual destructor cho mỗi interface.

2.  **Định nghĩa Concrete Products (Thành phần UI Cụ thể cho mỗi Nền tảng):**
    *   Tạo các lớp cụ thể triển khai các interface trên cho từng hệ điều hành bạn muốn hỗ trợ (ít nhất là 2, ví dụ: Windows và macOS).
    *   **Họ Windows:**
        *   `WindowsButton`: Triển khai `IButton` (ví dụ, `paint()` in ra "Rendering a Windows-style button.").
        *   `WindowsCheckbox`: Triển khai `ICheckbox`.
        *   `WindowsTextBox` (nếu có).
    *   **Họ macOS:**
        *   `MacOSButton`: Triển khai `IButton`.
        *   `MacOSCheckbox`: Triển khai `ICheckbox`.
        *   `MacOSTextBox` (nếu có).

3.  **Định nghĩa Abstract Factory (`IGUIFactory`):**
    *   Tạo một interface `IGUIFactory`.
    *   Interface này sẽ khai báo các phương thức tạo cho mỗi loại Abstract Product:
        *   `virtual std::unique_ptr<IButton> createButton() const = 0;`
        *   `virtual std::unique_ptr<ICheckbox> createCheckbox() const = 0;`
        *   `virtual std::unique_ptr<ITextBox> createTextBox() const = 0;` (nếu có)
    *   Nhớ virtual destructor.

4.  **Định nghĩa Concrete Factories (`WindowsFactory`, `MacOSFactory`):**
    *   Tạo các lớp con của `IGUIFactory`:
        *   `WindowsFactory`: Ghi đè các phương thức `create...()` để trả về các đối tượng `WindowsButton`, `WindowsCheckbox`, v.v.
        *   `MacOSFactory`: Ghi đè các phương thức `create...()` để trả về các đối tượng `MacOSButton`, `MacOSCheckbox`, v.v.

5.  **Viết Client Code (ví dụ lớp `Application`):**
    *   Tạo một lớp `Application` (hoặc một hàm client) nhận một `IGUIFactory` trong constructor của nó.
    *   Lớp `Application` sẽ sử dụng factory được cung cấp để tạo ra các thành phần UI mà nó cần.
        ```cpp
        class Application {
        private:
            std::unique_ptr<IGUIFactory> factory_;
            std::unique_ptr<IButton> loginButton_;
            std::unique_ptr<ICheckbox> rememberMeCheckbox_;
        public:
            Application(std::unique_ptr<IGUIFactory> factory) : factory_(std::move(factory)) {}

            void createUI() {
                if (!factory_) return;
                std::cout << "Application: Creating UI elements...\n";
                loginButton_ = factory_->createButton();
                rememberMeCheckbox_ = factory_->createCheckbox();

                if (loginButton_) {
                    loginButton_->onClick([]() {
                        std::cout << "Login button clicked!\n";
                    });
                }
            }

            void renderUI() const {
                if (loginButton_) loginButton_->paint();
                if (rememberMeCheckbox_) rememberMeCheckbox_->paint();
            }
        };
        ```
    *   Trong `main()`, bạn sẽ quyết định tạo `WindowsFactory` hay `MacOSFactory` dựa trên một số cấu hình (ví dụ: một biến môi trường, một file config, hoặc đơn giản là input từ người dùng cho bài tập này). Sau đó, truyền factory đã chọn vào `Application`.

**Sơ đồ lớp (Mermaid):**
Hãy tự vẽ sơ đồ lớp bằng Mermaid dựa trên mô tả này. Nó sẽ giúp bạn hình dung rõ ràng hơn cấu trúc của pattern.

**Gợi ý:**
*   Sử dụng `std::unique_ptr` để quản lý bộ nhớ.
*   Các phương thức `paint()` có thể chỉ cần `std::cout` ra một thông báo mô tả thành phần đang được "vẽ".
*   Trong `main()`, bạn có thể mô phỏng việc chọn hệ điều hành:
    ```cpp
    std::string os_type;
    std::cout << "Enter OS type (Windows/MacOS): ";
    std::cin >> os_type;
    std::unique_ptr<IGUIFactory> factory;
    if (os_type == "Windows") {
        factory = std::make_unique<WindowsFactory>();
    } else if (os_type == "MacOS") {
        factory = std::make_unique<MacOSFactory>();
    } else {
        std::cerr << "Unknown OS type. Exiting.\n";
        return 1;
    }
    Application app(std::move(factory));
    app.createUI();
    app.renderUI();
    // Thử gọi onClick của button nếu bạn đã triển khai nó
    ```

**Câu hỏi nâng cao (Bonus):**

1.  **Thêm sản phẩm mới:**
    Làm thế nào để thêm một loại thành phần UI mới (ví dụ: `ISlider` với các biến thể `WindowsSlider`, `MacSlider`) vào hệ thống? Bạn cần thay đổi những gì?
2.  **Thêm biến thể mới:**
    Làm thế nào để thêm hỗ trợ cho một hệ điều hành mới (ví dụ: Linux với `LinuxFactory`, `LinuxButton`, `LinuxCheckbox`)?
3.  **Tương tác giữa các sản phẩm:**
    Trong ví dụ pseudocode gốc, có đề cập "Products of one family are usually able to collaborate among themselves". Hãy nghĩ về một ví dụ đơn giản về sự hợp tác này. Ví dụ, một `IDialog` có thể chứa một `IButton`. Làm thế nào Abstract Factory có thể giúp đảm bảo rằng một `WindowsDialog` chỉ chứa `WindowsButton`? (Bạn có thể không cần triển khai đầy đủ, chỉ cần mô tả ý tưởng).

**Mục tiêu của bài tập:**
*   Hiểu rõ cách Abstract Factory giúp tạo ra các *họ* đối tượng liên quan.
*   Thực hành cách đảm bảo tính nhất quán giữa các sản phẩm được tạo ra bởi cùng một factory.
*   Thấy được lợi ích của việc tách biệt client code khỏi các lớp cụ thể của sản phẩm và factory, cho phép dễ dàng thay đổi "theme" hoặc "style" của toàn bộ họ sản phẩm.