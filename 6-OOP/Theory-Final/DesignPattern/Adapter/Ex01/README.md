### Bài tập: Tích hợp Thư viện Phân tích Dữ liệu Cũ

**Bối cảnh:**
Bạn đang làm việc trên một hệ thống phân tích dữ liệu hiện đại. Hệ thống của bạn (`ModernDataAnalyzer`) nhận dữ liệu dưới dạng một đối tượng `DataPacket` có cấu trúc như sau:

```cpp
// Dữ liệu mà hệ thống hiện đại của bạn hiểu
struct DataEntry {
    std::string key;
    double value;
    long timestamp;
};

class DataPacket {
public:
    std::vector<DataEntry> entries;
    std::string source_id;

    void addEntry(const std::string& key, double value, long timestamp) {
        entries.push_back({key, value, timestamp});
    }
    // ... các phương thức khác
};
```

Hệ thống của bạn có một interface chuẩn để xử lý dữ liệu:
```cpp
// Interface mà hệ thống hiện đại của bạn mong đợi
class IDataProcessor {
public:
    virtual ~IDataProcessor() = default;
    virtual void processData(const DataPacket& data) = 0;
};
```

Bây giờ, bạn cần tích hợp một thư viện phân tích dữ liệu cũ (`LegacyAnalyticsLibrary`). Thư viện này rất mạnh mẽ nhưng có một giao diện hoàn toàn khác và xử lý dữ liệu dưới dạng một chuỗi XML đơn giản.

```cpp
// Thư viện cũ bạn cần tích hợp (Adaptee)
class LegacyAnalyticsLibrary {
public:
    // Nhận dữ liệu dưới dạng chuỗi XML
    void analyzeXMLData(const std::string& xmlData) {
        std::cout << "LegacyAnalyticsLibrary: Analyzing XML data: \"" << xmlData << "\"" << std::endl;
        // Logic phân tích XML phức tạp ở đây...
        std::cout << "LegacyAnalyticsLibrary: Analysis complete." << std::endl;
    }
};
```

**Yêu cầu:**
Sử dụng **Adapter Pattern** (cụ thể là **Object Adapter**) để cho phép `ModernDataAnalyzer` (Client) sử dụng `LegacyAnalyticsLibrary` (Adaptee) thông qua interface `IDataProcessor` (Target).

**Các bước thực hiện:**

1.  **Xác định các thành phần:**
    *   **Client:** Một lớp (ví dụ: `ModernDataAnalyzer`) sử dụng `IDataProcessor`.
    *   **Target Interface:** `IDataProcessor`.
    *   **Adaptee:** `LegacyAnalyticsLibrary`.

2.  **Thiết kế Adapter (`AnalyticsAdapter`):**
    *   Tạo một lớp `AnalyticsAdapter` triển khai interface `IDataProcessor`.
    *   Lớp `AnalyticsAdapter` sẽ chứa một tham chiếu (hoặc con trỏ/`std::unique_ptr`) đến một đối tượng `LegacyAnalyticsLibrary`.
    *   Triển khai phương thức `processData(const DataPacket& data)` trong `AnalyticsAdapter`. Bên trong phương thức này:
        *   Bạn cần **chuyển đổi (convert)** đối tượng `DataPacket` thành một chuỗi XML mà `LegacyAnalyticsLibrary` có thể hiểu.
            *   Đây là phần "logic" chính của Adapter. Bạn không cần phải tạo một trình phân tích cú pháp XML hoàn chỉnh. Một biểu diễn XML đơn giản là đủ. Ví dụ:
                ```xml
                <packet source_id="some_id">
                    <entry key="temp" value="25.5" timestamp="1678886400" />
                    <entry key="humidity" value="60.1" timestamp="1678886400" />
                    ...
                </packet>
                ```
        *   Sau khi chuyển đổi, gọi phương thức `analyzeXMLData()` của đối tượng `LegacyAnalyticsLibrary` với chuỗi XML đã tạo.

3.  **Viết Client Code:**
    *   Tạo một lớp `ModernDataAnalyzer` có một phương thức, ví dụ `runAnalysis(IDataProcessor& processor, const DataPacket& dataPacket)`, nhận vào một `IDataProcessor` và một `DataPacket`.
    *   Trong `main()`:
        *   Tạo một đối tượng `DataPacket` với một số dữ liệu mẫu.
        *   Tạo một đối tượng `LegacyAnalyticsLibrary`.
        *   Tạo một đối tượng `AnalyticsAdapter`, truyền đối tượng `LegacyAnalyticsLibrary` vào constructor của nó.
        *   Tạo một đối tượng `ModernDataAnalyzer`.
        *   Gọi phương thức `runAnalysis` của `ModernDataAnalyzer`, truyền `AnalyticsAdapter` (dưới dạng `IDataProcessor&`) và `DataPacket` vào.

**Sơ đồ lớp (Mermaid):**
Bạn hãy tự vẽ sơ đồ lớp bằng Mermaid dựa trên mô tả này. Nó sẽ giúp bạn hình dung cấu trúc trước khi code.

**Gợi ý:**
*   Để chuyển đổi `DataPacket` sang XML trong `AnalyticsAdapter`, bạn có thể sử dụng `std::stringstream` để xây dựng chuỗi XML.
*   Hãy đảm bảo rằng `LegacyAnalyticsLibrary` được quản lý vòng đời một cách hợp lý. Nếu `AnalyticsAdapter` sở hữu nó, hãy dùng `std::unique_ptr`. Nếu không, hãy đảm bảo đối tượng `LegacyAnalyticsLibrary` tồn tại trong suốt thời gian `AnalyticsAdapter` sử dụng nó. Trong bài tập này, bạn có thể tạo `LegacyAnalyticsLibrary` trên stack trong `main` và truyền tham chiếu của nó cho Adapter.

**Mã nguồn khởi đầu (bạn cần hoàn thiện):**

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <sstream> // For std::stringstream
#include <memory>  // For std::unique_ptr if needed

// --- Target Interface and Data Structures ---
struct DataEntry {
    std::string key;
    double value;
    long timestamp;
};

class DataPacket {
public:
    std::vector<DataEntry> entries;
    std::string source_id;

    void addEntry(const std::string& key, double value, long timestamp) {
        entries.push_back({key, value, timestamp});
    }
    // Giả sử có thêm các phương thức getter nếu cần
    const std::vector<DataEntry>& getEntries() const { return entries; }
    const std::string& getSourceId() const { return source_id; }
};

class IDataProcessor {
public:
    virtual ~IDataProcessor() = default;
    virtual void processData(const DataPacket& data) = 0;
};

// --- Adaptee ---
class LegacyAnalyticsLibrary {
public:
    void analyzeXMLData(const std::string& xmlData) {
        std::cout << "LegacyAnalyticsLibrary: Analyzing XML data: \"" << xmlData << "\"" << std::endl;
        // ... (logic phân tích)
        std::cout << "LegacyAnalyticsLibrary: Analysis complete." << std::endl;
    }
};

// --- Adapter (CẦN BẠN HOÀN THIỆN) ---
class AnalyticsAdapter : public IDataProcessor {
private:
    LegacyAnalyticsLibrary& m_legacyLibrary; // Hoặc con trỏ, hoặc unique_ptr

public:
    AnalyticsAdapter(LegacyAnalyticsLibrary& legacyLib) : m_legacyLibrary(legacyLib) {}

    void processData(const DataPacket& data) override {
        std::cout << "AnalyticsAdapter: Converting DataPacket to XML..." << std::endl;

        // TODO: Chuyển đổi 'data' (DataPacket) thành chuỗi XML
        std::stringstream xmlStream;
        xmlStream << "<packet source_id=\"" << data.getSourceId() << "\">\n";
        for (const auto& entry : data.getEntries()) {
            xmlStream << "  <entry key=\"" << entry.key
                      << "\" value=\"" << entry.value
                      << "\" timestamp=\"" << entry.timestamp << "\" />\n";
        }
        xmlStream << "</packet>";
        std::string xmlData = xmlStream.str();

        std::cout << "AnalyticsAdapter: XML data created: \n" << xmlData << std::endl;

        // TODO: Gọi phương thức của LegacyAnalyticsLibrary
        m_legacyLibrary.analyzeXMLData(xmlData);

        std::cout << "AnalyticsAdapter: Data sent to LegacyAnalyticsLibrary." << std::endl;
    }
};

// --- Client ---
class ModernDataAnalyzer {
public:
    void runAnalysis(IDataProcessor& processor, const DataPacket& dataPacket) {
        std::cout << "ModernDataAnalyzer: Starting analysis..." << std::endl;
        processor.processData(dataPacket);
        std::cout << "ModernDataAnalyzer: Analysis run complete." << std::endl;
    }
};


int main() {
    // 1. Tạo dữ liệu mẫu
    DataPacket packet;
    packet.source_id = "sensor_001";
    packet.addEntry("temperature", 25.5, 1678886400L);
    packet.addEntry("humidity", 60.2, 1678886401L);
    packet.addEntry("pressure", 1012.5, 1678886402L);

    // 2. Tạo Adaptee
    LegacyAnalyticsLibrary legacyLibInstance;

    // 3. Tạo Adapter, truyền Adaptee vào
    AnalyticsAdapter adapter(legacyLibInstance);

    // 4. Tạo Client
    ModernDataAnalyzer analyzer;

    // 5. Client sử dụng Adapter thông qua Target Interface
    analyzer.runAnalysis(adapter, packet);

    std::cout << "\n--- Demonstrating with a different (hypothetical) processor ---" << std::endl;
    // Giả sử có một processor tương thích trực tiếp khác để so sánh
    class DirectModernProcessor : public IDataProcessor {
    public:
        void processData(const DataPacket& data) override {
            std::cout << "DirectModernProcessor: Processing DataPacket directly for source: " << data.source_id << std::endl;
            for(const auto& entry : data.entries) {
                std::cout << " - Key: " << entry.key << ", Value: " << entry.value << std::endl;
            }
        }
    };
    DirectModernProcessor directProcessor;
    analyzer.runAnalysis(directProcessor, packet);


    return 0;
}
```

**Mục tiêu của bài tập:**
*   Hiểu rõ cách Adapter kết nối các interface không tương thích.
*   Thực hành việc chuyển đổi dữ liệu hoặc lời gọi phương thức bên trong Adapter.
*   Thấy được cách Client có thể làm việc với các hệ thống khác nhau (cũ và mới) một cách thống nhất thông qua một interface chung.