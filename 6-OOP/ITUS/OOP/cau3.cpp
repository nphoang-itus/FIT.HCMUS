#include <iostream>
#include <string>
#include <vector>

class IRule {
public:
    virtual std::string setRule(std::string name) = 0;
};

class RenameCVFileUseCase {
private:
    std::vector<IRule*> rules;

public:
    std::string rename(std::string oriName) {
        std::string resultName = oriName;
        for (auto r : rules) {
            resultName = r->setRule(resultName);
        }
        return resultName;
    }

    void addRule(IRule* r) { rules.push_back(r); }
};

int main() {
    RenameCVFileUseCase cvFileRename;

    // Tao ra 3 cai luat
    IRule* rule1 = new NormalizeCasing(); cvFileRename.addRule(rule1);
    IRule* rule2 = new RemoveSpecialCharacters(); cvFileRename.addRule(rule2);
    IRule* rule3 = new AddDatePrefix(); cvFileRename.addRule(rule3);

    std::string oriName = "nguyen van A";
    std::string formatName = cvFileRename.rename(oriName);

    return 0;
}

// VIET TRONG THI
std::string RenameCVFileUseCase::rename(std::string oriName) {
    std::string resultName = oriName;
    for (auto r : rules) {
        resultName = r->setRule(resultName);
    }
    return resultName;
}