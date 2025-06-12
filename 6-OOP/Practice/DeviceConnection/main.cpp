#include <iostream>
#include <vector>
#include <string>
#include <memory> // Để sử dụng smart pointers nếu muốn

// --- KHAI BÁO CÁC LỚP VÀ INTERFACE Ở ĐÂY ---
// (IConnectable, IDisplayable, Device, SmartPhone, Television, SmartTV, NetworkRouter)
class IConnectable {
public:
    virtual void connect(const std::string& networkName) = 0;
    virtual void disconnect() = 0;
    virtual bool isConnected() const = 0;
    virtual std::string getNetworkName() const = 0;
    virtual ~IConnectable() {};
};

class IDisplayable {
public:
    virtual void displayContent(const std::string& content) = 0;
    virtual void turnOnDisplay() = 0;
    virtual void turnOffDisplay() = 0;
    virtual bool isDisplayOn() const = 0;
    virtual ~IDisplayable() {}
};

class Device {
protected:
    std::string _deviceID;
    std::string _modelName;
    bool _isPoweredOn;

public:
    Device(const std::string& deviceID, const std::string& modelName) : _deviceID(deviceID), _modelName(modelName), _isPoweredOn(false) {}
    virtual ~Device() {}
    
    void powerOn() {
        _isPoweredOn = true;
    }

    void powerOff() {
        _isPoweredOn = false;
    }

    bool getPowerStatus() const {
        return _isPoweredOn;
    }

    virtual void printDeviceInfo(std::ostream& os) const {
        os << "ID: " << _deviceID << ", Name: " << _modelName << ", ";
        os << "ACTIVE: " << (_isPoweredOn ? "TRUE" : "FALSE");
    }

    friend std::ostream& operator<<(std::ostream& os, const Device& device) {
        device.printDeviceInfo(os);
        return os;
    }
};

class SmartPhone : public IConnectable, IDisplayable, Device {
private:
    std::string _operatingSystem;
    std::string _currentNetwork;
    bool _displayStatus;


};

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