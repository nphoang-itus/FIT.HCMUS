// main.cpp
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip> // For std::fixed and std::setprecision
#include <algorithm> // For std::remove if needed for TaskManager::deleteTask
#include <exception>

// --- BẠN CẦN TRIỂN KHAI CÁC LỚP VÀ PHƯƠNG THỨC DƯỚI ĐÂY ---
// Forward declarations (Khai báo trước các lớp)
class Task;
class SimpleTask;
class ProjectTask;
class TaskManager;
class Logger; // Lớp Logger sử dụng Singleton Pattern

// Custom Exception (Ngoại lệ tùy chỉnh)
class TaskOperationException : public std::exception {
public:
    TaskOperationException(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
private:
    std::string message;
};


// class Logger
class Logger {
private:
    std::ostream* _outputStream;

    Logger() : _outputStream(&std::cout) {}

    ~Logger() {}
public:
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    static Logger& getInstance() {
        static Logger instance;
        return instance;
    }

    void log(const std::string& message) {
        if (_outputStream) {
            try {
                *_outputStream << "[LOG] " << message << "\n";
            }
            catch(const std::ios_base::failure& log_ex) {
                if (_outputStream != &std::cerr) {
                    std::cerr << "!!! Logger stream failed: " << log_ex.what() << std::endl;
                }
            }
        }
    }
};

class Task {
protected:
    std::string _id;
    std::string _description;

public:
    virtual void display(std::ostream& os, int indent = 0) const {
        os << "ID: " << _id << ", Desc: " << _description;
    }

    Task(const std::string& id, const std::string& description) : _id(id), _description(description) {}
    virtual ~Task() = default;

    // pure virtual
    virtual float getEstimatedHours() const = 0;
    virtual void saveTasksToFile(const std::string& fileName) const = 0;
    virtual void addSubTask(Task* subTask) = 0;
    
    friend std::ostream& operator<<(std::ostream& os, const Task& task) {
        task.display(os);
        return os;
    }
};

class SimpleTask : public Task {
private:
    float _estimatedHours;

public:
    void display(std::ostream& os, int indent = 0) const override {
        os << std::string(indent, ' ');
        os << "[Task] ";
        Task::display(os);
        os << ", Hours " << _estimatedHours << "\n";
    }

    SimpleTask(const std::string& id, const std::string& description, const float& estimatedHours) : Task(id, description), _estimatedHours(estimatedHours) {}

    float getEstimatedHours() const override {
        return _estimatedHours;
    }
    
    void saveTasksToFile(const std::string& fileName) const override {
        try {
            std::ofstream ofs(fileName);

            if (!ofs.good() || ofs.fail()) {
                throw TaskOperationException("Failed to open file " + fileName);
            }

            display(ofs);
        } catch (const std::exception& e) {
            std::cerr << "common error: " << e.what() << "\n";
        }
    }

    void addSubTask(Task* subTask) override {
        throw TaskOperationException("Simple task can't be add sub task");
    }
};


class ProjectTask : public Task {
private:
    std::vector<Task*> _subTasks;

public:
    void display(std::ostream& os, int indent = 0) const override {
        os << std::string(indent, ' ') << "[Project] ";
        Task::display(os, indent);
        os << " Total Hours: " << getEstimatedHours() << "\n";

        for (Task* task : _subTasks) {
            task->display(os, indent + 2);
        }
    }

    ProjectTask(const std::string& id, const std::string& description) : Task(id, description) {}
    
    ~ProjectTask() {
        for (Task* task : _subTasks) {
            if (task) {
                delete task;
            }
        }
    }

    float getEstimatedHours() const override {
        float result = 0.0;
        for (const Task* task : _subTasks) {
            result += task->getEstimatedHours();
        }
        return result;
    }
    
    void saveTasksToFile(const std::string& fileName) const override {
        try {
            std::ofstream ofs(fileName);

            if (!ofs.good() || ofs.fail()) {
                throw TaskOperationException("Failed to open file " + fileName);
            }

            display(ofs);
        } catch (const std::exception& e) {
            std::cerr << "common error: " << e.what() << "\n";
        }
    }

    void addSubTask(Task* subTask) override {
        if (subTask == nullptr) {
            throw TaskOperationException("Sub task can't be nullptr");
        }

        _subTasks.push_back(subTask);
    }
};

class TaskManager {
private:
    std::vector<Task*> _taskList;

public:
    ~TaskManager() {
        for (Task* task : _taskList) {
            if (task) {
                delete task;
            }
        }
    }

    void addTask(Task* task) {
        if (task == nullptr) {
            throw TaskOperationException("Sub task can't be nullptr");
        }

        _taskList.push_back(task);
    }

    void displayAllTasks() const {
        for (const Task* task : _taskList) {
            std::cout << *task;
        }
    }

    float getTotalEstimatedHours() const {
        float total = 0.0;
        for (const Task* task : _taskList) {
            total += task->getEstimatedHours();
        }
        return total;
    }

    void saveTasksToFile(const std::string& fileName) {
        try {
            std::ofstream ofs(fileName);

            if (!ofs.good() || ofs.fail()) {
                throw TaskOperationException("Failed to open file " + fileName);
            }

            for (const Task* task : _taskList) {
                task->saveTasksToFile(fileName);
            }
        } catch (const std::exception& e) {
            std::cerr << "common error: " << e.what() << "\n";
        }
    }

    // std::vector<Task*> loadTasksFromFile(const std::string& fileName) const {
    //     try {
    //         std::ofstream ofs(fileName);

    //         if (ofs.good() || ofs.fail()) {
    //             throw TaskOperationException("Failed to open file " + fileName);
    //         }

    //         for (const Task* task : _taskList) {
    //             task->saveTasksToFile(fileName);
    //         }
    //     } catch (const std::exception& e) {
    //         std::cerr << "common error: " << e.what() << "\n";
    //     }
    // }
};

// --- HẾT PHẦN KHAI BÁO CẦN TRIỂN KHAI ---

int main() {
    // Sử dụng std::fixed và std::setprecision cho output của số thực
    std::cout << std::fixed << std::setprecision(2);

    // Lấy instance của Logger (Singleton)
    Logger& logger = Logger::getInstance();
    logger.log("Program started.");

    TaskManager manager;

    // 1. Thêm công việc thủ công
    std::cout << "--- Adding tasks manually ---" << std::endl;
    manager.addTask(new SimpleTask("T001", "Design UI Mockups", 8.0));
    manager.addTask(new SimpleTask("T002", "Develop Login Module", 12.5));

    ProjectTask* backendProject = new ProjectTask("P001", "Backend Development");
    backendProject->addSubTask(new SimpleTask("T003", "Setup Database", 4.0));
    backendProject->addSubTask(new SimpleTask("T004", "Implement API Endpoints", 16.0));

    ProjectTask* paymentSubProject = new ProjectTask("P002", "Payment Gateway Integration");
    paymentSubProject->addSubTask(new SimpleTask("T005", "Research Payment APIs", 3.0));
    paymentSubProject->addSubTask(new SimpleTask("T006", "Implement Stripe Integration", 10.0));
    backendProject->addSubTask(paymentSubProject);

    manager.addTask(backendProject);
    logger.log("Manual tasks added.");

    // 2. Hiển thị tất cả công việc
    std::cout << "\n--- Displaying all tasks ---" << std::endl;
    manager.displayAllTasks();

    // 3. Lấy tổng số giờ dự kiến
    std::cout << "\n--- Total estimated hours for all tasks ---" << std::endl;
    std::cout << "Total hours: " << manager.getTotalEstimatedHours() << "h" << std::endl;

    // 4. Lưu công việc ra file
    std::cout << "\n--- Saving tasks to tasks.txt ---" << std::endl;
    try {
        manager.saveTasksToFile("tasks.txt");
        std::cout << "Tasks saved successfully." << std::endl;
        logger.log("Tasks saved to tasks.txt.");
    } catch (const std::ios_base::failure& e) { // Bắt ngoại lệ chung cho stream I/O
        std::cerr << "Error saving tasks: " << e.what() << std::endl;
        logger.log("Error saving tasks: " + std::string(e.what()));
    }

    // // 5. Xóa các công việc hiện tại và tải từ file
    // std::cout << "\n--- Clearing tasks and loading from tasks.txt ---" << std::endl;
    // TaskManager newManager; // Tạo một TaskManager mới để nạp dữ liệu
    // try {
    //     newManager.loadTasksFromFile("tasks.txt");
    //     std::cout << "Tasks loaded successfully." << std::endl;
    //     logger.log("Tasks loaded from tasks.txt.");
    //     std::cout << "\n--- Displaying loaded tasks ---" << std::endl;
    //     newManager.displayAllTasks();
    //     std::cout << "\n--- Total estimated hours for loaded tasks ---" << std::endl;
    //     std::cout << "Total hours: " << newManager.getTotalEstimatedHours() << "h" << std::endl;
    // } catch (const std::ios_base::failure& e) { // Bắt ngoại lệ chung cho stream I/O
    //     std::cerr << "Error loading tasks: " << e.what() << std::endl;
    //     logger.log("Error loading tasks: " + std::string(e.what()));
    // } catch (const TaskOperationException& e) {
    //     std::cerr << "Error during task operation while loading: " << e.what() << std::endl;
    //     logger.log("Error during task operation while loading: " + std::string(e.what()));
    // }

    // 6. Thử thực hiện thao tác không hợp lệ (thêm subtask vào SimpleTask)
    std::cout << "\n--- Attempting invalid operation ---" << std::endl;
    Task* anotherSimpleTask = new SimpleTask("T007", "A very simple task", 2.0);
    // Thêm vào manager để đảm bảo nó được giải phóng bộ nhớ (nếu không được delete trong try-catch)
    // Tuy nhiên, trong trường hợp này, chúng ta sẽ không thêm vào manager để test việc ném ngoại lệ
    // mà không làm ảnh hưởng đến manager. Chúng ta sẽ tự delete nó.

    try {
        std::cout << "Attempting to add subtask to SimpleTask T007..." << std::endl;
        Task* illegalSubtask = new SimpleTask("T008", "Illegal Subtask", 1.0);
        anotherSimpleTask->addSubTask(illegalSubtask); // Dòng này nên ném ngoại lệ
        std::cout << "This line should NOT be reached if exception is thrown correctly." << std::endl;
        // Nếu không ném ngoại lệ, phải delete illegalSubtask ở đây
        // delete illegalSubtask; // Không cần nếu addSubTask ném ngoại lệ và subtask chưa được quản lý
    } catch (const TaskOperationException& e) {
        std::cerr << "Caught expected exception: " << e.what() << std::endl;
        logger.log("Caught expected exception for T007: " + std::string(e.what()));
        // illegalSubtask chưa được thêm vào đâu cả và cũng không được delete nếu addSubTask ném ngoại lệ
        // Để đơn giản, ta bỏ qua việc delete nó ở đây, hoặc bạn có thể delete nó trong catch.
        // Trong một ứng dụng thực tế, bạn nên xử lý bộ nhớ cẩn thận hơn.
    }
    delete anotherSimpleTask; // Xóa task đã tạo cho thử nghiệm này

    logger.log("Program finished.");
    return 0;
}