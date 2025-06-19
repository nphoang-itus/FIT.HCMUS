#include <iostream>
#include <string>

class IMessageSender {
public:
    virtual ~IMessageSender() = default;
    virtual void sendMessage(std::string recipient, std::string message) = 0;
};

class EmailSender : public IMessageSender {
public:
    void sendMessage(std::string recipient, std::string message) override {
        std::cout << "Sending EMAIL to '" << recipient << "': \"" << message << "\"" << std::endl;
    }
};

class SMSSender : public IMessageSender {
public:
    void sendMessage(std::string recipient, std::string message) override {
        std::cout << "Sending SMS to '" << recipient << "': \"" << message << "\"" << std::endl;
    }
};

class PushNotificationSender : public IMessageSender {
public:
    void sendMessage(std::string recipient, std::string message) override {
        std::cout << "Sending PUSH NOTIFICATION to '" << recipient << "': \"" << message << "\"" << std::endl;
    }
};

class Notification {
protected:
    IMessageSender& _sender;
public:
    virtual ~Notification() = default;
    Notification(IMessageSender& sender) : _sender(sender) {}
    virtual void notify(std::string recipient, std::string message) {
        std::cout << "Notification: Preparing to send message." << std::endl;
        _sender.sendMessage(recipient, message);
    }
};

class NormalNotification : public Notification {
public:
    NormalNotification(IMessageSender& sender) : Notification(sender) {}
    void notify(std::string recipient, std::string message) override {
        std::cout << "NormalNotification: Preparing to send message." << std::endl;
        _sender.sendMessage(recipient, message);
    }
};

class UrgentNotification : public Notification {
public:
    UrgentNotification(IMessageSender& sender) : Notification(sender) {}
    void notify(std::string recipient, std::string message) override {
        std::cout << "UrgentNotification: Preparing to send message." << std::endl;
        std::string urgentMessage = "[URGENT!!!] " + message + " [!!!URGENT]";
        _sender.sendMessage(recipient, urgentMessage);
    }
};

int main() {
    EmailSender email;
    SMSSender sms;
    PushNotificationSender pushNotif;

    std::cout << "--- Using Email Sender ---" << std::endl;
    NormalNotification normalEmail(email);
    normalEmail.notify("john.doe@example.com", "Your weekly report is ready.");

    UrgentNotification urgentEmail(email);
    urgentEmail.notify("jane.doe@example.com", "System critical alert! Please check immediately.");

    std::cout << "\n--- Using SMS Sender ---" << std::endl;
    NormalNotification normalSms(sms);
    normalSms.notify("+1234567890", "Friendly reminder: Appointment tomorrow.");

    std::cout << "\n--- Using Push Notification Sender ---" << std::endl;

    // Tạo một UrgentNotification sử dụng PushNotificationSender
    UrgentNotification urgentPush(pushNotif);
    urgentPush.notify("admin_device_token_xyz", "Server overload! Action required.");

    return 0;
}