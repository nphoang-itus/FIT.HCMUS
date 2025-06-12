**Bài tập: Hệ thống Quản lý Thiết bị Điện tử Đa năng**

Bạn cần xây dựng một hệ thống để quản lý các thiết bị điện tử. Một số thiết bị có thể có nhiều chức năng (ví dụ: một Smart TV vừa là TV, vừa có thể kết nối Internet).

**Yêu cầu các Lớp:**

1.  **`IConnectable` (Interface - Lớp trừu tượng hoàn toàn):**
    *   **Chức năng:** Định nghĩa giao diện cho các thiết bị có khả năng kết nối mạng.
    *   **Phương thức (thuần ảo):**
        *   `virtual void connect(const std::string& networkName) = 0;`
        *   `virtual void disconnect() = 0;`
        *   `virtual bool isConnected() const = 0;`
        *   `virtual std::string getNetworkName() const = 0;` (Trả về tên mạng đang kết nối, hoặc chuỗi rỗng nếu không kết nối).
        *   `virtual ~IConnectable() {}` (Hàm hủy ảo cho interface).

2.  **`IDisplayable` (Interface - Lớp trừu tượng hoàn toàn):**
    *   **Chức năng:** Định nghĩa giao diện cho các thiết bị có khả năng hiển thị nội dung.
    *   **Phương thức (thuần ảo):**
        *   `virtual void displayContent(const std::string& content) = 0;`
        *   `virtual void turnOnDisplay() = 0;`
        *   `virtual void turnOffDisplay() = 0;`
        *   `virtual bool isDisplayOn() const = 0;`
        *   `virtual ~IDisplayable() {}`

3.  **`Device` (Lớp cơ sở):**
    *   **Thuộc tính (protected):** `deviceID` (string), `modelName` (string), `isPoweredOn` (bool, mặc định `false`).
    *   **Phương thức (public):**
        *   Constructor nhận `deviceID`, `modelName`.
        *   `virtual ~Device() {}` (Hàm hủy ảo).
        *   `void powerOn();`
        *   `void powerOff();`
        *   `bool getPowerStatus() const;`
        *   `virtual void printDeviceInfo(std::ostream& os) const;` (Hiển thị thông tin cơ bản của thiết bị).
        *   `friend std::ostream& operator<<(std::ostream& os, const Device& device);` (Gọi `device.printDeviceInfo(os)`).

4.  **`SmartPhone` (Kế thừa từ `Device`, `IConnectable`, `IDisplayable`):**
    *   **Thuộc tính (private):** `operatingSystem` (string), `currentNetwork` (string), `displayStatus` (bool).
    *   **Phương thức:**
        *   Constructor.
        *   Override các phương thức từ `IConnectable` và `IDisplayable`.
        *   Override `printDeviceInfo(std::ostream& os) const` để hiển thị thêm thông tin về OS, trạng thái kết nối, trạng thái màn hình.
        *   `void makeCall(const std::string& phoneNumber);` (Phương thức riêng của Smartphone).

5.  **`Television` (Kế thừa từ `Device`, `IDisplayable`):**
    *   **Thuộc tính (private):** `currentChannel` (int), `displayStatus` (bool).
    *   **Phương thức:**
        *   Constructor.
        *   Override các phương thức từ `IDisplayable`.
        *   Override `printDeviceInfo(std::ostream& os) const` để hiển thị thêm thông tin về kênh hiện tại, trạng thái màn hình.
        *   `void changeChannel(int channel);`

6.  **`SmartTV` (Kế thừa từ `Television`, `IConnectable`):**
    *   *Lưu ý: `Television` đã kế thừa `IDisplayable`, `SmartTV` không cần kế thừa lại trực tiếp `IDisplayable` nữa nếu `Television` đã cung cấp đủ.*
    *   **Thuộc tính (private):** `currentNetwork` (string).
    *   **Phương thức:**
        *   Constructor.
        *   Override các phương thức từ `IConnectable`.
        *   Override `printDeviceInfo(std::ostream& os) const` để hiển thị thông tin từ `Television` và thêm trạng thái kết nối.
        *   `void browseInternet(const std::string& url);`

7.  **`NetworkRouter` (Kế thừa từ `Device`, `IConnectable`):**
    *   **Thuộc tính (private):** `currentNetwork` (string), `maxConnectedDevices` (int).
    *   **Phương thức:**
        *   Constructor.
        *   Override các phương thức từ `IConnectable`.
        *   Override `printDeviceInfo(std::ostream& os) const` để hiển thị thêm thông tin về số thiết bị tối đa có thể kết nối, trạng thái kết nối.

**Hàm `main()` gợi ý:**

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <memory> // Để sử dụng smart pointers nếu muốn

// --- KHAI BÁO CÁC LỚP VÀ INTERFACE Ở ĐÂY ---
// (IConnectable, IDisplayable, Device, SmartPhone, Television, SmartTV, NetworkRouter)
// --- HẾT PHẦN KHAI BÁO ---

// Hàm helper để thao tác với các thiết bị có khả năng kết nối
void testConnection(IConnectable* device, const std::string& network) {
    if (!device) return;
    std::cout << "\n--- Testing Connection ---" << std::endl;
    if (device->isConnected()) {
        std::cout << "Device is already connected to " << device->getNetworkName() << std::endl;
        device->disconnect();
        std::cout << "Disconnected." << std::endl;
    }
    std::cout << "Connecting to " << network << "..." << std::endl;
    device->connect(network);
    if (device->isConnected()) {
        std::cout << "Successfully connected to " << device->getNetworkName() << std::endl;
    } else {
        std::cout << "Failed to connect." << std::endl;
    }
}

// Hàm helper để thao tác với các thiết bị có khả năng hiển thị
void testDisplay(IDisplayable* device, const std::string& message) {
    if (!device) return;
    std::cout << "\n--- Testing Display ---" << std::endl;
    if (!device->isDisplayOn()) {
        std::cout << "Turning display ON." << std::endl;
        device->turnOnDisplay();
    }
    device->displayContent(message);
    std::cout << "Turning display OFF." << std::endl;
    device->turnOffDisplay();
}


int main() {
    std::vector<Device*> allDevices; // Hoặc std::vector<std::unique_ptr<Device>>

    SmartPhone* myPhone = new SmartPhone("SP001", "Galaxy S24", "Android 14");
    Television* livingRoomTV = new Television("TV001", "Sony Bravia X90K", 5);
    SmartTV* kitchenSmartTV = new SmartTV("STV001", "LG C3 OLED", 1);
    NetworkRouter* homeRouter = new NetworkRouter("RTR001", "ASUS RT-AX88U", 50);

    allDevices.push_back(myPhone);
    allDevices.push_back(livingRoomTV);
    allDevices.push_back(kitchenSmartTV);
    allDevices.push_back(homeRouter);

    std::cout << "--- Initial Device States ---" << std::endl;
    for (const auto* device : allDevices) {
        if (device) {
            device->powerOn(); // Bật nguồn tất cả thiết bị
            std::cout << *device << std::endl;
        }
    }

    // Sử dụng dynamic_cast để kiểm tra và sử dụng các interface
    std::cout << "\n\n--- INTERFACE INTERACTIONS ---" << std::endl;

    // Thao tác với myPhone
    std::cout << "\n== Interacting with SmartPhone ==" << std::endl;
    IConnectable* phoneConnect = dynamic_cast<IConnectable*>(myPhone);
    IDisplayable* phoneDisplay = dynamic_cast<IDisplayable*>(myPhone);
    testConnection(phoneConnect, "MyHomeWiFi");
    testDisplay(phoneDisplay, "Hello from my Galaxy S24!");
    myPhone->makeCall("123-456-7890");

    // Thao tác với livingRoomTV (không có IConnectable)
    std::cout << "\n== Interacting with Television ==" << std::endl;
    IDisplayable* tvDisplay = dynamic_cast<IDisplayable*>(livingRoomTV);
    testDisplay(tvDisplay, "Watching News Channel.");
    livingRoomTV->changeChannel(7);
    std::cout << *livingRoomTV << std::endl; // Xem kênh mới

    IConnectable* tvConnectTest = dynamic_cast<IConnectable*>(livingRoomTV);
    if (tvConnectTest) {
        std::cout << "This TV can connect (This should not happen for basic TV)." << std::endl;
    } else {
        std::cout << "This Television cannot connect to the internet directly." << std::endl;
    }


    // Thao tác với kitchenSmartTV
    std::cout << "\n== Interacting with SmartTV ==" << std::endl;
    IConnectable* smartTVConnect = dynamic_cast<IConnectable*>(kitchenSmartTV);
    IDisplayable* smartTVDisplay = dynamic_cast<IDisplayable*>(kitchenSmartTV); // Vẫn có thể cast vì Television đã kế thừa
    testConnection(smartTVConnect, "KitchenNet");
    testDisplay(smartTVDisplay, "Streaming YouTube on SmartTV.");
    kitchenSmartTV->browseInternet("www.google.com");
    kitchenSmartTV->changeChannel(101); // SmartTV vẫn là TV
    std::cout << *kitchenSmartTV << std::endl;


    // Thao tác với homeRouter
    std::cout << "\n== Interacting with NetworkRouter ==" << std::endl;
    IConnectable* routerConnect = dynamic_cast<IConnectable*>(homeRouter);
    testConnection(routerConnect, "ISP_PrimaryLink");
    // NetworkRouter không có IDisplayable
    IDisplayable* routerDisplayTest = dynamic_cast<IDisplayable*>(homeRouter);
     if (routerDisplayTest) {
        std::cout << "This Router can display (This should not happen)." << std::endl;
    } else {
        std::cout << "This Router does not have display capabilities." << std::endl;
    }
    std::cout << *homeRouter << std::endl;


    std::cout << "\n--- Powering Off Devices ---" << std::endl;
    for (auto* device : allDevices) {
        if (device) {
            device->powerOff();
            std::cout << device->modelName << " is "
                      << (device->getPowerStatus() ? "ON" : "OFF") << std::endl;
            delete device; // Dọn dẹp bộ nhớ
        }
    }
    allDevices.clear();

    return 0;
}

```

**Yêu cầu chính bạn cần tập trung triển khai:**

1.  **Định nghĩa các Interface:** `IConnectable`, `IDisplayable` với các phương thức thuần ảo.
2.  **Lớp cơ sở `Device`:** Với các thuộc tính và phương thức chung.
3.  **Các lớp con kế thừa:**
    *   `SmartPhone`: Kế thừa từ `Device`, `IConnectable`, `IDisplayable`.
    *   `Television`: Kế thừa từ `Device`, `IDisplayable`.
    *   `SmartTV`: Kế thừa từ `Television` (đã có `IDisplayable`) và `IConnectable`. Đây là ví dụ về việc một lớp con (SmartTV) có được interface (IDisplayable) thông qua một lớp cha trực tiếp (Television) chứ không cần khai báo lại.
    *   `NetworkRouter`: Kế thừa từ `Device`, `IConnectable`.
4.  **Override các phương thức:** Đảm bảo các lớp con override đúng các phương thức từ interface và lớp cơ sở `Device` (đặc biệt là `printDeviceInfo`).
5.  **Quản lý trạng thái:** Các thiết bị cần quản lý trạng thái của mình (bật/tắt, kết nối/không kết nối, màn hình bật/tắt).
6.  **Hàm hủy ảo:** Đảm bảo sử dụng hàm hủy ảo ở tất cả các lớp cơ sở và interface để tránh rò rỉ bộ nhớ khi xóa qua con trỏ lớp cơ sở/interface.
7.  **Sử dụng `dynamic_cast`:** Trong `main`, `dynamic_cast` được sử dụng để kiểm tra xem một đối tượng `Device*` có thực sự triển khai một interface cụ thể hay không trước khi gọi các phương thức của interface đó. Đây là một phần quan trọng để hiểu cách làm việc với đa hình và interface.
8.  **Quản lý bộ nhớ:** Dọn dẹp bộ nhớ cẩn thận (sử dụng `delete` cho các đối tượng được tạo bằng `new`). Cân nhắc sử dụng `std::unique_ptr` hoặc `std::shared_ptr` nếu bạn muốn thực hành với smart pointers.

**Thử thách thêm (Tùy chọn):**

*   **Xử lý ngoại lệ:** Ném ngoại lệ trong các trường hợp không hợp lệ (ví dụ: cố gắng `disconnect` khi chưa `connect`, hoặc `displayContent` khi màn hình đang tắt và thiết bị không tự động bật).
*   **File I/O:** Thêm chức năng lưu và tải danh sách thiết bị từ file, bao gồm cả trạng thái hiện tại của chúng (kết nối mạng nào, kênh TV nào, v.v.).