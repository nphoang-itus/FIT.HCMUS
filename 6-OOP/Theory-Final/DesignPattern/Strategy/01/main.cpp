#include <iostream>
#include <string>
#include <memory>

class ICompressionStrategy {
public:
    virtual ~ICompressionStrategy() = default;
    virtual void compress(const std::string& filePath) const = 0;
};

class ZipCompressionStrategy : public ICompressionStrategy {
public:
    void compress(const std::string& filePath) const override {
        std::cout << "compress zip file: " << filePath << "\n";
    }
};

class RarCompressionStrategy : public ICompressionStrategy {
public:
    void compress(const std::string& filePath) const override {
        std::cout << "compress rar file: " << filePath << "\n";
    }
};

class SevenZCompressionStrategy : public ICompressionStrategy {
public:
    void compress(const std::string& filePath) const override {
        std::cout << "compress sZ file: " << filePath << "\n";
    }
};

class CompressionContext {
private:
    std::unique_ptr<ICompressionStrategy> _strategy;
public:
    void setStrategy(std::unique_ptr<ICompressionStrategy> strategy) {
        _strategy = std::move(strategy);
    }

    void createArchive(const std::string& filePath) const {
        _strategy->compress(filePath);
    }
};

int main() {
    std::string filePath = "C://System/";
    // Nén file
    CompressionContext context;
    context.setStrategy(std::make_unique<RarCompressionStrategy>());
    context.createArchive(filePath);

    return 0;
}