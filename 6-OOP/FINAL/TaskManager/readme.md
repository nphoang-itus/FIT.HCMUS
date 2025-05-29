
**Hàm `main()`:**

```cpp
// main.cpp
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip> // For std::fixed and std::setprecision
#include <algorithm> // For std::remove if needed for TaskManager::deleteTask

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

    // 5. Xóa các công việc hiện tại và tải từ file
    std::cout << "\n--- Clearing tasks and loading from tasks.txt ---" << std::endl;
    TaskManager newManager; // Tạo một TaskManager mới để nạp dữ liệu
    try {
        newManager.loadTasksFromFile("tasks.txt");
        std::cout << "Tasks loaded successfully." << std::endl;
        logger.log("Tasks loaded from tasks.txt.");
        std::cout << "\n--- Displaying loaded tasks ---" << std::endl;
        newManager.displayAllTasks();
        std::cout << "\n--- Total estimated hours for loaded tasks ---" << std::endl;
        std::cout << "Total hours: " << newManager.getTotalEstimatedHours() << "h" << std::endl;
    } catch (const std::ios_base::failure& e) { // Bắt ngoại lệ chung cho stream I/O
        std::cerr << "Error loading tasks: " << e.what() << std::endl;
        logger.log("Error loading tasks: " + std::string(e.what()));
    } catch (const TaskOperationException& e) {
        std::cerr << "Error during task operation while loading: " << e.what() << std::endl;
        logger.log("Error during task operation while loading: " + std::string(e.what()));
    }

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
```

**Output Mẫu Mong Muốn (có thể có thay đổi nhỏ về định dạng không đáng kể):**

```
[LOG] Program started.
--- Adding tasks manually ---
[LOG] Manual tasks added.

--- Displaying all tasks ---
[Task] ID: T001, Desc: Design UI Mockups, Hours: 8.00
[Task] ID: T002, Desc: Develop Login Module, Hours: 12.50
[Project] ID: P001, Desc: Backend Development, Total Hours: 33.00
  [Task] ID: T003, Desc: Setup Database, Hours: 4.00
  [Task] ID: T004, Desc: Implement API Endpoints, Hours: 16.00
  [Project] ID: P002, Desc: Payment Gateway Integration, Total Hours: 13.00
    [Task] ID: T005, Desc: Research Payment APIs, Hours: 3.00
    [Task] ID: T006, Desc: Implement Stripe Integration, Hours: 10.00

--- Total estimated hours for all tasks ---
Total hours: 53.50h

--- Saving tasks to tasks.txt ---
Tasks saved successfully.
[LOG] Tasks saved to tasks.txt.

--- Clearing tasks and loading from tasks.txt ---
Tasks loaded successfully.
[LOG] Tasks loaded from tasks.txt.

--- Displaying loaded tasks ---
[Task] ID: T001, Desc: Design UI Mockups, Hours: 8.00
[Task] ID: T002, Desc: Develop Login Module, Hours: 12.50
[Project] ID: P001, Desc: Backend Development, Total Hours: 33.00
  [Task] ID: T003, Desc: Setup Database, Hours: 4.00
  [Task] ID: T004, Desc: Implement API Endpoints, Hours: 16.00
  [Project] ID: P002, Desc: Payment Gateway Integration, Total Hours: 13.00
    [Task] ID: T005, Desc: Research Payment APIs, Hours: 3.00
    [Task] ID: T006, Desc: Implement Stripe Integration, Hours: 10.00

--- Total estimated hours for loaded tasks ---
Total hours: 53.50h

--- Attempting invalid operation ---
Attempting to add subtask to SimpleTask T007...
Caught expected exception: Cannot add subtask to a SimpleTask.
[LOG] Caught expected exception for T007: Cannot add subtask to a SimpleTask.
[LOG] Program finished.
```

**Yêu cầu cụ thể cho việc triển khai các lớp:**
<!-- 
1.  **`Task` (Lớp cơ sở trừu tượng):**
    *   Thuộc tính (protected): `id` (string), `description` (string).
    *   Phương thức:
        *   Constructor nhận `id`, `description`.
        *   `virtual ~Task() {}` (Hàm hủy ảo).
        *   `virtual double getEstimatedHours() const = 0;` (Thuần ảo).
        *   `virtual void display(std::ostream& os, int indentLevel = 0) const = 0;` (Thuần ảo, `indentLevel` dùng để thụt lề khi hiển thị).
        *   `virtual void save(std::ofstream& ofs) const = 0;` (Thuần ảo, lưu thông tin task ra file).
        *   `virtual void addSubTask(Task* subTask)` (Ném `TaskOperationException("Operation not supported for this task type")` theo mặc định. `ProjectTask` sẽ override).
        *   Getters cho `id`, `description`.
        *   `friend std::ostream& operator<<(std::ostream& os, const Task& task);` (Sẽ gọi `task.display(os, 0)`).

2.  **`SimpleTask` (Kế thừa từ `Task`):**
    *   Thuộc tính (private): `estimatedHours` (double).
    *   Phương thức:
        *   Constructor nhận `id`, `description`, `estimatedHours`.
        *   Override `getEstimatedHours() const`.
        *   Override `display(std::ostream& os, int indentLevel) const` (Hiển thị `[Task] ID: ..., Desc: ..., Hours: ...`).
        *   Override `save(std::ofstream& ofs) const` (Lưu loại task là `SIMPLE`, sau đó là `id`, `description`, `estimatedHours`).
        *   Override `addSubTask(Task* subTask)` (Ném `TaskOperationException("Cannot add subtask to a SimpleTask")`).

3.  **`ProjectTask` (Kế thừa từ `Task` - Áp dụng Composite Pattern):**
    *   Thuộc tính (private): `std::vector<Task*> subTasks;`
    *   Phương thức:
        *   Constructor nhận `id`, `description`.
        *   `~ProjectTask()` (Quan trọng: giải phóng bộ nhớ cho tất cả `subTasks`).
        *   Override `getEstimatedHours() const` (Tính tổng giờ của tất cả `subTasks`).
        *   Override `display(std::ostream& os, int indentLevel) const` (Hiển thị `[Project] ID: ..., Desc: ..., Total Hours: ...`, sau đó duyệt và hiển thị từng `subTask` với `indentLevel + 1`).
        *   Override `save(std::ofstream& ofs) const` (Lưu loại task là `PROJECT`, sau đó là `id`, `description`. Tiếp theo, lưu số lượng subtask, rồi duyệt và gọi `save` cho từng `subTask`).
        *   Override `addSubTask(Task* subTask)` (Thêm `subTask` vào `subTasks`).

4.  **`TaskManager`:**
    *   Thuộc tính (private): `std::vector<Task*> tasks;`
    *   Phương thức:
        *   `~TaskManager()` (Quan trọng: giải phóng bộ nhớ cho tất cả `tasks`).
        *   `void addTask(Task* task);`
        *   `void displayAllTasks() const;` (Duyệt và xuất từng task bằng `operator<<`).
        *   `double getTotalEstimatedHours() const;` (Tổng giờ của tất cả task cấp cao nhất).
        *   `void saveTasksToFile(const std::string& filename) const;` (Mở file, ghi số lượng task cấp cao nhất, sau đó duyệt qua `tasks` và gọi `task->save(ofs)`. Ném `std::ios_base::failure` nếu có lỗi file).
        *   `void loadTasksFromFile(const std::string& filename);` (Đây là phần thử thách nhất. Mở file, đọc số lượng task. Với mỗi task, đọc loại (`SIMPLE` hay `PROJECT`) để tạo đối tượng tương ứng. Nếu là `PROJECT`, cần đọc đệ quy các `subTasks` của nó. Ném `std::ios_base::failure` nếu lỗi file, hoặc `TaskOperationException` nếu định dạng file sai hoặc gặp loại task không xác định).
            *   **Gợi ý định dạng file `tasks.txt`:**
                ```
                // Dòng đầu tiên: số lượng task cấp cao nhất
                // Tiếp theo là thông tin của từng task:
                // TYPE:[SIMPLE|PROJECT]
                // ID:<id>
                // DESC:<description>
                // Nếu SIMPLE:
                // HOURS:<hours>
                // Nếu PROJECT:
                // SUBTASK_COUNT:<count>
                //   (Lặp lại cấu trúc task cho từng subtask)
                ```
                Ví dụ:
                ```
                2
                TYPE:SIMPLE
                ID:T001
                DESC:Design UI Mockups
                HOURS:8.00
                TYPE:PROJECT
                ID:P001
                DESC:Backend Development
                SUBTASK_COUNT:1 
                TYPE:SIMPLE
                ID:T003
                DESC:Setup Database
                HOURS:4.00
                ```

5.  **`Logger` (Singleton Pattern):**
    *   Phương thức:
        *   `static Logger& getInstance();`
        *   `void log(const std::string& message);` (In ra console với định dạng `[LOG] <message>`, có thể thêm timestamp nếu muốn).
    *   Đảm bảo chỉ có một instance của `Logger` được tạo (ví dụ: sử dụng Meyers' Singleton).
    *   Constructor private, copy constructor và assignment operator bị delete hoặc private. -->

1.  **`Task` (Lớp Cơ sở Trừu tượng):**
    *   **Chức năng:** Đại diện cho một công việc chung nhất trong hệ thống. Nó là "khuôn mẫu" cho tất cả các loại công việc cụ thể.
    *   **Đặc điểm chính:**
        *   Lưu trữ thông tin cơ bản như `id` và `description` của công việc.
        *   Định nghĩa giao diện (interface) chung mà tất cả các loại công việc phải tuân theo, bao gồm:
            *   Cách tính toán số giờ dự kiến hoàn thành (`getEstimatedHours`).
            *   Cách hiển thị thông tin của công việc (`display`).
            *   Cách lưu thông tin công việc ra file (`save`).
            *   Cách thêm một công việc con (mặc định là không hỗ trợ, nhưng cho phép các lớp con như `ProjectTask` định nghĩa lại).
        *   Phải có hàm hủy ảo (`virtual destructor`) để đảm bảo việc giải phóng bộ nhớ đúng cách khi làm việc với con trỏ lớp cơ sở.
        *   Cung cấp toán tử `<<` để dễ dàng xuất thông tin Task ra stream.

2.  **`SimpleTask` (Lớp Con của `Task`):**
    *   **Chức năng:** Đại diện cho một công việc đơn lẻ, không thể chia nhỏ thành các công việc con.
    *   **Đặc điểm chính:**
        *   Ngoài thông tin kế thừa từ `Task`, nó có thêm thuộc tính riêng là `estimatedHours` (số giờ dự kiến để hoàn thành công việc này).
        *   Triển khai cụ thể các phương thức trừu tượng từ `Task`:
            *   `getEstimatedHours()`: Trả về giá trị `estimatedHours` của chính nó.
            *   `display()`: Hiển thị thông tin `id`, `description`, và `estimatedHours` của công việc này.
            *   `save()`: Lưu thông tin (bao gồm cả loại "SIMPLE") và các thuộc tính của `SimpleTask` ra file.
        *   Khi cố gắng `addSubTask`, nó sẽ báo lỗi (ném ngoại lệ) vì `SimpleTask` không hỗ trợ công việc con.

3.  **`ProjectTask` (Lớp Con của `Task` - Composite):**
    *   **Chức năng:** Đại diện cho một dự án hoặc một công việc lớn, bao gồm nhiều công việc con (có thể là `SimpleTask` hoặc thậm chí là `ProjectTask` khác). Đây là nơi áp dụng **Composite Pattern**.
    *   **Đặc điểm chính:**
        *   Lưu trữ một danh sách các công việc con (`subTasks`).
        *   Triển khai cụ thể các phương thức trừu tượng từ `Task`:
            *   `getEstimatedHours()`: Tính tổng số giờ dự kiến của tất cả các `subTasks` bên trong nó.
            *   `display()`: Hiển thị thông tin của dự án, sau đó hiển thị thông tin của từng `subTask` (có thụt lề để thể hiện cấu trúc cây).
            *   `save()`: Lưu thông tin (bao gồm cả loại "PROJECT") và các thuộc tính của `ProjectTask`. Quan trọng là sau đó nó phải lưu lần lượt thông tin của từng `subTask`.
        *   Override phương thức `addSubTask` để cho phép thêm công việc con vào danh sách `subTasks` của nó.
        *   Hàm hủy của `ProjectTask` phải chịu trách nhiệm giải phóng bộ nhớ cho tất cả các `subTasks` mà nó quản lý.

4.  **`TaskManager` (Lớp Quản lý):**
    *   **Chức năng:** Quản lý một danh sách các công việc cấp cao nhất (có thể là `SimpleTask` hoặc `ProjectTask`).
    *   **Đặc điểm chính:**
        *   Lưu trữ một danh sách các `Task` (các công việc gốc).
        *   Cung cấp các chức năng:
            *   `addTask()`: Thêm một công việc mới vào danh sách quản lý.
            *   `displayAllTasks()`: Hiển thị thông tin của tất cả các công việc đang quản lý.
            *   `getTotalEstimatedHours()`: Tính tổng số giờ dự kiến của tất cả các công việc cấp cao nhất mà nó quản lý.
            *   `saveTasksToFile()`: Lưu toàn bộ danh sách công việc (bao gồm cả cấu trúc lồng nhau của `ProjectTask`) ra một file text.
            *   `loadTasksFromFile()`: Đọc dữ liệu công việc từ một file text và tái tạo lại danh sách các công việc (bao gồm cả cấu trúc lồng nhau). Đây là phần phức tạp, đòi hỏi phải nhận diện được loại Task và đọc đệ quy nếu là `ProjectTask`.
        *   Hàm hủy của `TaskManager` phải chịu trách nhiệm giải phóng bộ nhớ cho tất cả các `Task` mà nó quản lý.

5.  **`Logger` (Lớp Tiện ích - Singleton):**
    *   **Chức năng:** Cung cấp một cơ chế ghi log tập trung cho toàn bộ ứng dụng. Sử dụng **Singleton Pattern** để đảm bảo chỉ có một đối tượng `Logger` duy nhất trong suốt quá trình chạy chương trình.
    *   **Đặc điểm chính:**
        *   `getInstance()`: Phương thức tĩnh để truy cập vào đối tượng `Logger` duy nhất.
        *   `log()`: Phương thức để ghi một thông điệp log (ví dụ: ra console, hoặc sau này có thể mở rộng ra file).
        *   Constructor, copy constructor, và assignment operator được thiết kế để ngăn chặn việc tạo nhiều instance.

6.  **`TaskOperationException` (Lớp Ngoại lệ Tùy chỉnh):**
    *   **Chức năng:** Định nghĩa một loại ngoại lệ cụ thể cho các lỗi liên quan đến thao tác trên `Task` (ví dụ: cố gắng thêm subtask vào `SimpleTask`, hoặc định dạng file không hợp lệ khi load).
    *   **Đặc điểm chính:**
        *   Kế thừa từ `std::exception`.
        *   Cho phép truyền một thông điệp lỗi cụ thể khi ném ngoại lệ.
        *   Override phương thức `what()` để trả về thông điệp lỗi.

**Lưu ý quan trọng:**

*   **Quản lý bộ nhớ:** Vì `main()` sử dụng con trỏ thô (`new`), bạn cần cực kỳ cẩn thận với việc giải phóng bộ nhớ (`delete`) trong các hàm hủy của `ProjectTask` và `TaskManager` để tránh rò rỉ bộ nhớ.
*   **Thứ tự include và forward declaration:** Đảm bảo các file header (nếu bạn chia ra nhiều file) và forward declaration được sắp xếp hợp lý.
*   **Xử lý file:** Khi đọc/ghi file, hãy đảm bảo bạn kiểm tra trạng thái của stream (ví dụ `ofs.good()`, `ifs.fail()`) và xử lý các trường hợp file không mở được hoặc định dạng không đúng. Hàm `saveTasksToFile` và `loadTasksFromFile` cần bật cờ ngoại lệ cho stream (ví dụ `ofs.exceptions(std::ofstream::failbit | std::ofstream::badbit);`).
*   **`operator<<`:** Triển khai `operator<<` cho lớp `Task` để có thể `cout << *task_pointer;`.
*   **Đệ quy khi load `ProjectTask`:** Phần `loadTasksFromFile` cho `ProjectTask` sẽ cần một hàm trợ giúp đệ quy để đọc các `subTasks`.