#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <format>
#include <sstream>

struct DataEntry{
    std::string key;
    double value;
    long timestamp;
};

class DataPacket {
public:
    std::vector<DataEntry> entries;
    std::string sourceId;
    
    DataPacket(std::vector<DataEntry> e, std::string s) : entries(e), sourceId(s) {}

    void addEntry(std::string key, double value, long timestamp) {
        entries.push_back({key, value, timestamp});
    }
};

class IDataProcessor {
public:
    virtual ~IDataProcessor() = default;
    virtual void processData(const DataPacket& dataPacket) = 0;
};

class LegacyAnalyticsLibrary {
public:
    void analyzeXMLData(const std::string& xmlData) {
        std::cout << "LegacyAnalyticsLibrary: Analyzing XML data: \"" << xmlData << "\"" << std::endl;
        // Logic phân tích XML phức tạp ở đây...
        std::cout << "LegacyAnalyticsLibrary: Analysis complete." << std::endl;
    }
};

class ModernDataAnalyzer {
public:
    void runAnalysis(IDataProcessor& processor, const DataPacket& packet) {
        std::cout << "ModernDataAnalyzer: Analyzing data packet: \"" << packet.sourceId << "\"" << std::endl;
        processor.processData(packet);
        std::cout << "ModernDataAnalyzer: Analysis complete." << std::endl;
    }
};

class AnalyticsAdapter : public IDataProcessor {
private:
    std::unique_ptr<LegacyAnalyticsLibrary> _legacy;

public:
    AnalyticsAdapter(std::unique_ptr<LegacyAnalyticsLibrary> legacy) : _legacy(std::move(legacy)) {}

    void processData(const DataPacket& dataPacket) override {
        /* xml:
        <packet source_id="some_id">
            <entry key="temp" value="25.5" timestamp="1678886400" />
            <entry key="humidity" value="60.1" timestamp="1678886400" />
            ...
        </packet>
        */
        
        std::string xmlData = "";
        
        // get sourceId:
        xmlData = "<packet source_id=\"" + dataPacket.sourceId + "\"> ";

        // get data:
        for (const auto& entry : dataPacket.entries) { // Dùng range-based for
            xmlData += "<entry key=\"" + entry.key + "\"" // Thêm dấu nháy kép
                    + " value=\"" + std::to_string(entry.value) + "\""
                    + " timestamp=\"" + std::to_string(entry.timestamp) + "\""
                    + " />"; // Thêm newline cho dễ đọc
        }

        // end xml
        xmlData += "</packet>";

        _legacy->analyzeXMLData(xmlData);
    }
};

int main() {
    DataPacket packet(
        {{"data1", 12.3, 11},
        {"data2", 12.3, 12},
        {"data3", 12.3, 13}},
        "id1"
    );

    AnalyticsAdapter adapter(std::make_unique<LegacyAnalyticsLibrary>());
    ModernDataAnalyzer client;
    client.runAnalysis(adapter, packet);

    return 0;
}