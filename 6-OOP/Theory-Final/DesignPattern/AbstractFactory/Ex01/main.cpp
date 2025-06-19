#include <iostream>

class IButton {
public:
    virtual ~IButton() = default;
    virtual void paint() const = 0;
    virtual void onClick() const = 0;
};

class ICheckbox {
protected:
    bool _checked;
public:
    virtual ~ICheckbox() = default;
    virtual void paint() const = 0;
    virtual void setChecked(const bool& checked) = 0;
    virtual bool isChecked() const = 0;
};

class WindowsButton : public IButton {
public:
    void paint() const override {
        std::cout << "Windows painting button\n";
    }

    void onClick() const override {
        std::cout << "Window on click\n";
    }
};

class MacOSButton : public IButton {
public:
    void paint() const override {
        std::cout << "MacOS painting button\n";
    }

    void onClick() const override {
        std::cout << "MacOS on click\n";
    }
};

class WindowsCheckbox : public ICheckbox {
public:
    void paint() const override {
        std::cout << "Windows painting checkbox\n";
    }

    void setChecked(const bool& checked) override {
        _checked = checked;
    }

    bool isChecked() const override {
        return _checked;
    }
};

class MacOSCheckbox : public ICheckbox {
public:
    void paint() const override {
        std::cout << "MacOS painting checkbox\n";
    }

    void setChecked(const bool& checked) override {
        _checked = checked;
    }

    bool isChecked() const override {
        return _checked;
    }
};

class IGUIFactory {
public:
    virtual ~IGUIFactory() = default;
    virtual IButton* createButton() const = 0;
    virtual ICheckbox* createCheckbox() const = 0;
};

class WindowsFactory : public IGUIFactory {
public:
    IButton* createButton() const override {
        return new WindowsButton;
    }

    ICheckbox* createCheckbox() const override {
        return new WindowsCheckbox;
    }
};

class MacOSFactory : public IGUIFactory {
public:
    IButton* createButton() const override {
        return new MacOSButton;
    }

    ICheckbox* createCheckbox() const override {
        return new MacOSCheckbox;
    }
};

class Application {
private:
    IGUIFactory* _factory;
    IButton* _loginButton;
    ICheckbox* _rememberMeCheckbox;
public:
    Application() {
        _factory = nullptr;
        _loginButton = nullptr;
        _rememberMeCheckbox = nullptr;
    }
    Application(IGUIFactory* factory) : _factory(factory) {
        _loginButton = nullptr;
        _rememberMeCheckbox = nullptr;
    }
    ~Application() {
        if (_factory) delete _factory;
        if (_loginButton) delete _loginButton;
        if (_rememberMeCheckbox) delete _rememberMeCheckbox;
    }

    void createUI() {
        if (!_factory) return;

        std::cout << "Application: Creating UI element...\n";
        _loginButton = _factory->createButton();
        _rememberMeCheckbox = _factory->createCheckbox();

        if (_loginButton) {
            _loginButton->onClick();
        }
    }

    void renderUI() const {
        if (_loginButton) _loginButton->paint();
        if (_rememberMeCheckbox) _rememberMeCheckbox->paint();
    }
};

int main() {
    std::string type = "";
    std::cin >> type;

    IGUIFactory* factory = nullptr;

    if (type == "win") {
        factory = new WindowsFactory;
    } else if (type == "mac") {
        factory = new MacOSFactory;
    }

    Application app(factory);
    
    app.createUI();
    app.renderUI();

    return 0;
}