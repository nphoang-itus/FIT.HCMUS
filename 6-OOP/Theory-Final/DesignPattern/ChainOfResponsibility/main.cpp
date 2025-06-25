#include <iostream>
#include <string>
#include <vector>
#include <format>

struct Email {
    std::string sender;
    std::string subject;
    std::string body;
    std::vector<std::string> attachments;
    std::string status;

    Email(
        const std::string& send,
        const std::string& sbj,
        const std::string& bd,
        const std::vector<std::string>& attach
    ) : 
        sender(send),
        subject(sbj),
        body(bd),
        attachments(attach),
        status("Inbox")
    {}

    void printStatus() const {
        std::cout << std::format(
            "Email for {} with subject=\"{}\", body=\"{}\", attachments=\"{}\", status=\"{}\"\n",
            sender, subject, body, (attachments.empty() ? "no" : "yes"), status
        );
    }
};

class IEmailHandler {
public:
    virtual ~IEmailHandler() = default;
    virtual IEmailHandler* setNextHandler(IEmailHandler* handler) = 0;
    virtual bool process(Email* email) = 0;
};

class BaseEmailHandler : public IEmailHandler {
protected:
    IEmailHandler* _nextHandler = nullptr;
public:
    IEmailHandler* setNextHandler(IEmailHandler* handler) override {
        this->_nextHandler = handler;
        return handler;
    }

    bool process(Email* email) override {
        if (this->_nextHandler) {
            return this->_nextHandler->process(email);
        }
        return true;
    }
};

class SpamFilterHandler : public BaseEmailHandler {
public:
    bool process(Email* email) override {
        std::cout << "SpamFilterHandler: Checking spam for email " << email->sender << "\n";
        if (email->subject == "spam") {
            email->status = "Spam";
            std::cout << "SpamFilterHandler: email " << email->sender << "has been spam.\n";
            return false;
        } else {
            std::cout << "SpamFilterHandler: email " << email->sender << "hasn't been spam.\n";
        }
        return BaseEmailHandler::process(email);
    }
};

class LengthFilterHandler : public BaseEmailHandler {
public:
    bool process(Email* email) override {
        std::cout << "LengthFilterHandler: Checking length for email " << email->sender << "\n";
        if (email->body.size() < 5 || email->body.size() > 30) {
            email->status = "Review";
            std::cout << "LengthFilterHandler: email " << email->sender << " too long or short.\n";
        } else {
            std::cout << "LengthFilterHandler: email " << email->sender << "has good length.\n";
        }
        return BaseEmailHandler::process(email);
    }
};

class AttachmentFilterHandler : public BaseEmailHandler {
public:
    bool process(Email* email) override {
        std::cout << "AttachmentFilterHandler: Checking attachments for email " << email->sender << "\n";
        for (const auto& attachment : email->attachments) {
            // Kiểm tra file extension nguy hiểm
            if (attachment.find(".exe") != std::string::npos || 
                attachment.find(".bat") != std::string::npos ||
                attachment.find(".scr") != std::string::npos) {
                email->status = "Dangerous";
                std::cout << "AttachmentFilterHandler: email " << email->sender << " has suspicious attachment.\n";
                return false;
            }
        }
        std::cout << "AttachmentFilterHandler: email " << email->sender << " has safe attachments.\n";
        return BaseEmailHandler::process(email);
    }
};

class FinalCategorizerHandler : public BaseEmailHandler {
public:
    bool process(Email* email) override {
        std::cout << "FinalCategorizerHandler: Checking email " << email->sender << "\n";
        if (email->status == "Inbox") {
            std::cout << "FinalCategorizerHandler: Checking email " << email->sender << " processed successfully!" << std::endl;
            return true;
        } else {
            std::cout << "FinalCategorizerHandler: Checking email " << email->sender << " failed!" << std::endl;
            return false;
        }
    }
};

void processOrderRequest(IEmailHandler* chain, Email* email) {
    std::cout << "\n--- Processing new order request ---" << std::endl;
    email->printStatus();
    bool success = chain->process(email);
    if (success) {
        std::cout << "Email request chain completed." << std::endl;
    } else {
        std::cout << "Email request chain stopped due to an issue." << std::endl;
    }
    email->printStatus(); // In trạng thái cuối cùng
    std::cout << "------------------------------------" << std::endl;
    std::cout << "\n";
}


int main() {
    SpamFilterHandler spamHandler;
    LengthFilterHandler lengthHandler;
    AttachmentFilterHandler attachHandler;
    FinalCategorizerHandler finalHandler;

    spamHandler.setNextHandler(&lengthHandler)->setNextHandler(&attachHandler)->setNextHandler(&finalHandler);

    Email email1("nphoang@gm.com", "test1", "xin chao cac ban", {});
    Email email2("nphoang@gm.com", "spam", "xin chao cac ban", {}); // spam
    Email email3("nphoang@gm.com", "test3", "xi", {}); // length
    Email email4("nphoang@gm.com", "test1", "xin chao cac ban", {"blabla.exe", "temp.cpp"}); // attachments

    processOrderRequest(&spamHandler, &email1);
    processOrderRequest(&spamHandler, &email2);
    processOrderRequest(&spamHandler, &email3);
    processOrderRequest(&spamHandler, &email4);

    return 0;
}