#include <iostream>
#include <string>
#include <memory>

class Computer {
public:
    std::string cpu;
    int ramGB;
    std::string storageType;
    std::string storageCapacityGB;
    std::string gpuModel;
    int psuWattage;
    std::string caseType;
public:
    void displayConfiguration() {
        std::cout << "--- Computer Configuration ---" << std::endl;
        if (!cpu.empty()) std::cout << "CPU: " << cpu << std::endl;
        if (ramGB > 0) std::cout << "RAM: " << ramGB << "GB" << std::endl;
        if (!storageType.empty()) std::cout << "Storage: " << storageCapacityGB << "GB " << storageType << std::endl;
        if (!gpuModel.empty()) std::cout << "GPU: " << gpuModel << std::endl;
        else std::cout << "GPU: Integrated Graphics" << std::endl;
        if (psuWattage > 0) std::cout << "PSU: " << psuWattage << "W" << std::endl;
        if (!caseType.empty()) std::cout << "Case: " << caseType << std::endl;
        std::cout << "----------------------------" << std::endl;
    }
};

class IComputerBuilder {
public:
    virtual ~IComputerBuilder() = default;
    virtual void reset() = 0;
    virtual void buildCPU(const std::string& cpuModel) = 0;
    virtual void buildRAM(int ramSizeGB) = 0;
    virtual void buildStorage(const std::string& type, int capacityGB) = 0;
    virtual void buildGPU(const std::string& gpuModel) = 0;
    virtual void buildPSU(int wattage) = 0;
    virtual void buildCase(const std::string& caseType) = 0;
    virtual std::unique_ptr<Computer> getComputer() = 0;
};

class DesktopComputerBuilder : public IComputerBuilder {
private:
    std::unique_ptr<Computer> _desktop;
public:
    DesktopComputerBuilder() {
        this->reset();
    }

    void reset() {
        _desktop = std::make_unique<Computer>();
    }

    void buildCPU(const std::string& cpuModel) {
        _desktop->cpu = cpuModel;
    }

    void buildRAM(int ramSizeGB) {
        _desktop->ramGB = ramSizeGB;
    }

    void buildStorage(const std::string& type, int capacityGB) {
        _desktop->storageType = type;
        _desktop->storageCapacityGB = capacityGB;
    }

    void buildGPU(const std::string& gpuModel) {
        _desktop->gpuModel = gpuModel;
    }

    void buildPSU(int wattage) {
        _desktop->psuWattage = wattage;
    }

    void buildCase(const std::string& caseType) {
        _desktop->caseType = caseType;
    }

    std::unique_ptr<Computer> getComputer() {
        std::unique_ptr<Computer> result = std::move(_desktop);
        this->reset();
        return result;
    }
};

class ComputerAssembler {
private:
    IComputerBuilder* _builder = nullptr;
public:
    void setBuilder(IComputerBuilder* builder) {
        _builder = builder;
    }

    void assembleGamingPC() {
        std::cout << "Director: Assembling a Gaming PC." << std::endl;
        _builder->reset();
        _builder->buildCPU("Intel Core i9 Extreme");
        _builder->buildRAM(32); // 32GB RAM
        _builder->buildStorage("SSD", 2048); // 2TB SSD
        _builder->buildGPU("NVIDIA GeForce RTX 4090");
        _builder->buildPSU(1000); // 1000W PSU
        _builder->buildCase("Full Tower RGB");
    }

    void assembleOfficePC() {
        std::cout << "Director: Assembling an Office PC." << std::endl;
        _builder->reset();
        _builder->buildCPU("Intel Core i5");
        _builder->buildRAM(16); // 16GB RAM
        _builder->buildStorage("SSD", 512); // 512GB SSD
        // Không build GPU rời, sẽ dùng integrated
        _builder->buildPSU(550); // 550W PSU
        _builder->buildCase("Mid Tower Office");
    }
};

int main() {
    DesktopComputerBuilder builder;
    ComputerAssembler director;
    director.setBuilder(&builder);
    director.assembleGamingPC();
    auto desktopGaming = builder.getComputer();

    desktopGaming->displayConfiguration();
    return 0;
}