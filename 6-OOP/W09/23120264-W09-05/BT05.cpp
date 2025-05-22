#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <vector>
#include <sstream>
#include <filesystem>

namespace fs = std::filesystem;

class Node {
protected:
    std::string _name;

public:
    Node(const std::string& name) : _name(name) {}
    virtual ~Node() {}

    std::string getName() { return _name; };

    virtual void print(int indent = 0) const = 0;
    virtual int countFiles() const = 0;
    virtual int countDirectories() const = 0;
    virtual double getSize() const = 0;
    virtual double getDiskSize(const std::string& basePath) const = 0;
    virtual Node* findDirectory(const std::string& dirName) { return nullptr; }

    virtual void saveToFile(std::ofstream& outFile, int indent = 0) const = 0;

    virtual bool createOnDisk(const std::string& basePath) const = 0;
};

class File : public Node {
private:
    double _size;

public:
    File(const std::string& name, const double& size) : Node(name), _size(size) {}

    void print(int indent = 0) const override {
        std::cout << std::string(indent, ' ') << _name << " (" << std::fixed << std::setprecision(3) << _size << " B)\n";
    }

    int countFiles() const override { return 1; }
    int countDirectories() const override { return 0; }
    double getSize() const override { return _size; }

    void saveToFile(std::ofstream& outFile, int indent = 0) const override {
        outFile << std::string(indent, ' ') << _name << " " << _size << "\n";
    }

    bool createOnDisk(const std::string& basePath) const override {
        std::string fullPath = basePath + "/" + _name;
        std::ofstream file(fullPath);
        if (!file) {
            std::cout << "Error creating file: " << fullPath << "\n";
            return false;
        }
        
        file << std::string(static_cast<int>(_size), '0');
        std::cout << "Created file: " << fullPath << std::endl;
        return true;
    }
    
    double getDiskSize(const std::string& basePath) const override {
        std::string fullPath = basePath + "/" + _name;
        try {
            if (fs::exists(fullPath) && fs::is_regular_file(fullPath)) {
                return static_cast<double>(fs::file_size(fullPath));
            } else {
                std::cout << "File not found on disk: " << fullPath << std::endl;
                return 0.0;
            }
        } catch (const fs::filesystem_error& e) {
            std::cout << "Error getting file size: " << e.what() << std::endl;
            return 0.0;
        }
    }
};

class Directory : public Node {
    std::vector<Node*> _children;

public:
    Directory(const std::string& name) : Node(name) {}

    ~Directory() {
        for (Node* child : _children) {
            delete child;
        }
    }

    void add(Node* node) {
        _children.push_back(node);
    }

    void print(int indent = 0) const override {
        std::cout << std::string(indent, ' ') << "[" << _name << "]" << "\n";
        for (Node* child : _children) {
            child->print(indent + 2);
        }
    }

    int countFiles() const override {
        int count = 0;
        for (Node* child : _children) {
            count += child->countFiles();
        }
        return count;
    }

    int countDirectories() const override {
        int count = 0;
        for (Node* child : _children) {
            count += child->countDirectories();
            if (dynamic_cast<Directory*>(child)) count++;
        }
        return count;
    }

    double getSize() const override {
        double total = 0;
        for (Node* child : _children) {
            total += child->getSize();
        }
        return total;
    }

    Node* findDirectory(const std::string& dirName) override {
        if (_name == dirName)
            return this;

        for (Node* child : _children) {
            Directory* dir = dynamic_cast<Directory*>(child);
            if (dir) {
                Node* found = dir->findDirectory(dirName);
                if (found) return found;
            }
        }
        return nullptr;
    }
    
    void saveToFile(std::ofstream& outFile, int indent = 0) const override {
        outFile << std::string(indent, ' ') << "D " << _name << "\n";
        for (Node* child : _children) {
            child->saveToFile(outFile, indent + 2);
        }
    }
    
    bool createOnDisk(const std::string& basePath) const override {
        std::string fullPath = basePath + "/" + _name;
        
        // Create directory
        try {
            if (!fs::create_directory(fullPath)) {
                if (!fs::exists(fullPath)) {
                    std::cout << "Error creating directory: " << fullPath << "\n";
                    return false;
                }
            } else {
                std::cout << "Created directory: " << fullPath << "\n";
            }
            
            // Create all children inside this directory
            for (Node* child : _children) {
                if (!child->createOnDisk(fullPath)) {
                    return false;
                }
            }
            
            return true;
        } catch (const fs::filesystem_error& e) {
            std::cout << "Filesystem error: " << e.what() << "\n";
            return false;
        }
    }
    
    static Directory* loadFromFile(const std::string& filename) {
        std::ifstream inFile(filename);
        if (!inFile) {
            std::cout << "Error opening file: " << filename << "\n";
            return nullptr;
        }
        
        Directory* root = nullptr;
        std::vector<Directory*> dirStack;
        std::string line;
        
        while (getline(inFile, line)) {
            if (line.empty()) continue;
        
            int indent = 0;
            while (indent < line.length() && line[indent] == ' ') indent++;
            int level = indent / 2;
            
            line = line.substr(indent);
            
            char type = line[0];
            std::string name, sizeStr;
            std::stringstream ss(line.substr(2));
            
            if (type == 'D') {
                std::getline(ss, name);
                Directory* dir = new Directory(name);
                
                if (level == 0) {
                    root = dir;
                    dirStack.clear();
                    dirStack.push_back(dir);
                } else {
                    // Adjust dirStack to the correct level
                    while (dirStack.size() > level) {
                        dirStack.pop_back();
                    }
                    
                    dirStack.back()->add(dir);
                    dirStack.push_back(dir);
                }
            } else if (type == 'F') {
                double size;
                // ss >> name >> size;
                // if (!dirStack.empty()) {
                //     dirStack.back()->add(new File(name, size));
                // }
                std::string fullText = line.substr(2);
                size_t lastSpace = fullText.find_last_of(' ');
                if (lastSpace != std::string::npos) {
                    name = fullText.substr(0, lastSpace);
                    size = std::stod(fullText.substr(lastSpace + 1));
                    if (!dirStack.empty()) {
                        dirStack.back()->add(new File(name, size));
                    }
                }
            }
        }
        
        return root;
    }
    
    double getDiskSize(const std::string& basePath) const override {
        std::string fullPath = basePath + "/" + _name;
        try {
            if (!fs::exists(fullPath) || !fs::is_directory(fullPath)) {
                std::cout << "Directory not found on disk: " << fullPath << std::endl;
                return 0.0;
            }
            
            double totalSize = 0.0;
            
            for (Node* child : _children) {
                totalSize += child->getDiskSize(fullPath);
            }
            
            
            return totalSize;
        } catch (const fs::filesystem_error& e) {
            std::cout << "Error calculating directory size: " << e.what() << std::endl;
            return 0.0;
        }
    }
    
    static double calculateDirectorySize(const std::string& dirPath) {
        try {
            if (!fs::exists(dirPath) || !fs::is_directory(dirPath)) {
                std::cout << "Path does not exist or is not a directory: " << dirPath << std::endl;
                return 0.0;
            }
            
            double totalSize = 0.0;
            for (const auto& entry : fs::recursive_directory_iterator(dirPath)) {
                if (fs::is_regular_file(entry)) {
                    totalSize += static_cast<double>(fs::file_size(entry));
                }
            }
            
            return totalSize;
        } catch (const fs::filesystem_error& e) {
            std::cout << "Error calculating directory size: " << e.what() << std::endl;
            return 0.0;
        }
    }
};

int main() {
    std::string structureFile = "directory_structure.txt";
    
    std::cout << "=== Loading directory structure from file ===" << std::endl;
    Directory* root = Directory::loadFromFile(structureFile);
    
    if (!root) {
        std::cout << "Failed to load directory structure. Exiting..." << std::endl;
        return 1;
    }
    
    std::cout << "\n=== Loaded Directory Structure ===" << std::endl;
    root->print();
    
    std::string basePath = "created_filesystem";
    std::cout << "\n=== Creating directory structure on disk at " << basePath << " ===" << std::endl;

    if (fs::exists(basePath)) {
        try {
            for (const auto& entry : fs::directory_iterator(basePath)) {
                fs::remove_all(entry.path());
            }
            std::cout << "Existing directory cleaned." << std::endl;
        } catch (const fs::filesystem_error& e) {
            std::cout << "Error cleaning directory: " << e.what() << std::endl;
            delete root;
            return 1;
        }
    } else {
        // Create new directory
        try {
            fs::create_directory(basePath);
            std::cout << "Created base directory: " << basePath << std::endl;
        } catch (const fs::filesystem_error& e) {
            std::cout << "Error creating directory: " << e.what() << std::endl;
            delete root;
            return 1;
        }
    }
    
    // Create the loaded structure on disk
    if (!root->createOnDisk(basePath)) {
        std::cout << "Failed to create directory structure on disk." << std::endl;
        delete root;
        return 1;
    }
    
    std::string targetDir = "Bai tap";
    std::cout << "\nFinding information about directory \"" << targetDir << "\"" << std::endl;
    Node* found = root->findDirectory(targetDir);
    if (found) {
        std::cout << "Directory found!" << std::endl;
        std::cout << "Number of files: " << found->countFiles() << std::endl;
        std::cout << "Number of subdirectories: " << found->countDirectories() << std::endl;
        std::cout << "Total size (from virtual structure): " << std::fixed << std::setprecision(3) << found->getSize() << " B" << std::endl;
    } else {
        std::cout << "Directory not found!" << std::endl;
    }
    
    delete root;
    
    return 0;
}