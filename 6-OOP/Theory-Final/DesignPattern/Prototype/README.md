---

### Bài tập về Prototype Pattern (C++)

**Mục tiêu chung:** Hiểu và áp dụng Prototype Pattern để tạo bản sao của các đối tượng mà không cần phụ thuộc vào lớp cụ thể của chúng, đồng thời luyện tập với các khái niệm như kế thừa, đa hình, hàm tạo sao chép và quản lý bộ nhớ (sử dụng smart pointers).

---

#### Bài tập 1: Hệ thống quản lý tài liệu cơ bản

**Bối cảnh:**
Bạn đang xây dựng một hệ thống quản lý tài liệu đơn giản. Hệ thống cần có khả năng tạo các bản sao (template) của các loại tài liệu khác nhau như `Letter` (Thư), `Report` (Báo cáo), và `Resume` (Sơ yếu lý lịch). Mỗi loại tài liệu có các thuộc tính chung (như `title`, `author`) và các thuộc tính riêng.

**Yêu cầu:**

1.  Định nghĩa một lớp cơ sở trừu tượng `Document` với:
    *   Các thuộc tính chung: `std::string title`, `std::string author`.
    *   Một hàm tạo để khởi tạo các thuộc tính này.
    *   Một hàm tạo sao chép cho lớp `Document`.
    *   Một phương thức ảo thuần túy `std::unique_ptr<Document> clone() const`.
    *   Một phương thức ảo `void displayInfo() const` để hiển thị thông tin tài liệu.
    *   Hàm hủy ảo.
2.  Tạo các lớp cụ thể `Letter`, `Report`, `Resume` kế thừa từ `Document`:
    *   `Letter` có thêm thuộc tính `std::string recipientAddress`.
    *   `Report` có thêm thuộc tính `std::string summary`.
    *   `Resume` có thêm thuộc tính `std::vector<std::string> skills`.
    *   Mỗi lớp cụ thể phải:
        *   Có hàm tạo riêng để khởi tạo tất cả các thuộc tính của nó (bao gồm cả thuộc tính từ lớp cha).
        *   Triển khai hàm tạo sao chép, gọi hàm tạo sao chép của lớp cha.
        *   Triển khai phương thức `clone()` để trả về một bản sao của chính nó.
        *   Override phương thức `displayInfo()` để hiển thị tất cả thông tin (cả chung và riêng).
3.  Trong hàm `main()`:
    *   Tạo một vài đối tượng prototype ban đầu (ví dụ: một `Letter` mẫu, một `Report` mẫu).
    *   Tạo một `std::vector<std::unique_ptr<Document>>` để lưu trữ các tài liệu.
    *   Sử dụng phương thức `clone()` để tạo các bản sao của các prototype và thêm vào vector.
    *   Thay đổi một vài thuộc tính của các bản sao để chứng tỏ chúng là các đối tượng độc lập.
    *   Duyệt qua vector và gọi `displayInfo()` cho mỗi tài liệu.

**Gợi ý:**
*   Sử dụng `std::unique_ptr` để quản lý bộ nhớ.
*   Hãy chắc chắn rằng hàm tạo sao chép của các lớp con gọi hàm tạo sao chép của lớp cha.

---

#### Bài tập 2: Cấu hình nhân vật trong Game

**Bối cảnh:**
Trong một trò chơi, bạn cần tạo ra nhiều kẻ thù (Enemy) hoặc NPC (Non-Player Character). Mỗi loại nhân vật (ví dụ: `Warrior`, `Mage`, `Archer`) có các thuộc tính cơ bản giống nhau (như `health`, `attackPower`) nhưng cũng có các kỹ năng hoặc trang bị đặc thù. Việc tạo mới và cấu hình từng nhân vật từ đầu rất tốn công.

**Yêu cầu:**

1.  Định nghĩa lớp cơ sở trừu tượng `GameCharacter` với:
    *   Thuộc tính: `int health`, `int attackPower`, `std::string name`.
    *   Hàm tạo, hàm tạo sao chép.
    *   Phương thức ảo thuần túy `std::shared_ptr<GameCharacter> clone() const`.
    *   Phương thức ảo `void describe() const`.
    *   Hàm hủy ảo.
2.  Tạo các lớp cụ thể `Warrior`, `Mage`, `Archer` kế thừa từ `GameCharacter`:
    *   `Warrior`: thêm `std::string weaponType` (e.g., "Sword", "Axe").
    *   `Mage`: thêm `std::vector<std::string> spells` (e.g., {"Fireball", "Heal"}).
    *   `Archer`: thêm `int arrowCount`.
    *   Triển khai hàm tạo, hàm tạo sao chép, `clone()`, và `describe()` cho mỗi lớp.
3.  Tạo một lớp `CharacterRegistry` (Prototype Registry):
    *   Sử dụng `std::map<std::string, std::shared_ptr<GameCharacter>>` để lưu trữ các prototype nhân vật.
    *   Phương thức `void addPrototype(const std::string& key, std::shared_ptr<GameCharacter> prototype)`.
    *   Phương thức `std::shared_ptr<GameCharacter> createCharacter(const std::string& key)`: phương thức này sẽ tìm prototype trong map và trả về một bản sao (clone) của nó.
4.  Trong hàm `main()`:
    *   Tạo các đối tượng prototype cho `Warrior`, `Mage`, `Archer` với các cấu hình ban đầu (ví dụ: "Elite Warrior", "Novice Mage").
    *   Đăng ký các prototype này vào `CharacterRegistry`.
    *   Sử dụng `CharacterRegistry` để tạo nhiều instance của các nhân vật (ví dụ: một đội quân gồm 3 "Elite Warrior" và 2 "Novice Mage").
    *   Thay đổi một vài thuộc tính của các nhân vật được tạo ra từ registry (ví dụ: giảm `health` của một Warrior sau khi chiến đấu) để chứng tỏ chúng độc lập.
    *   Hiển thị thông tin của tất cả các nhân vật đã tạo.

**Gợi ý:**
*   Sử dụng `std::shared_ptr` vì các prototype trong registry có thể được chia sẻ và nhân bản nhiều lần.
*   Khi `createCharacter` từ registry, hãy nhớ gọi `clone()` trên prototype lấy từ map.

---

#### Bài tập 3: Sao chép sâu (Deep Copy) với đối tượng phức tạp

**Bối cảnh:**
Bạn đang làm việc với các đối tượng `UserProfile` chứa thông tin người dùng. Mỗi `UserProfile` có một đối tượng `Address` (địa chỉ) và một danh sách các `Hobby` (sở thích). Khi bạn nhân bản một `UserProfile`, bạn muốn rằng đối tượng `Address` và danh sách các `Hobby` cũng được nhân bản (sao chép sâu), chứ không phải chỉ là tham chiếu đến cùng một đối tượng `Address` hoặc cùng một danh sách `Hobby`.

**Yêu cầu:**

1.  Định nghĩa lớp `Hobby`:
    *   Thuộc tính: `std::string name`.
    *   Hàm tạo, hàm tạo sao chép.
    *   (Tùy chọn) Phương thức `clone()` nếu bạn muốn `Hobby` cũng là một prototype.
2.  Định nghĩa lớp `Address`:
    *   Thuộc tính: `std::string street`, `std::string city`.
    *   Hàm tạo, hàm tạo sao chép.
    *   (Tùy chọn) Phương thức `clone()`.
3.  Định nghĩa lớp `UserProfile` (Prototype):
    *   Thuộc tính: `std::string username`, `int age`.
    *   Thuộc tính là đối tượng: `Address* userAddress` (hoặc `std::unique_ptr<Address>`).
    *   Thuộc tính là danh sách đối tượng: `std::vector<Hobby*> userHobbies` (hoặc `std::vector<std::unique_ptr<Hobby>>`).
    *   Hàm tạo để khởi tạo `UserProfile`, bao gồm cả việc tạo đối tượng `Address` và thêm `Hobby`.
    *   **Hàm tạo sao chép (quan trọng):** Phải thực hiện **sao chép sâu** cho `userAddress` và `userHobbies`. Tức là, tạo các đối tượng `Address` và `Hobby` mới cho bản sao, không dùng chung với bản gốc.
    *   Hàm hủy: Phải giải phóng bộ nhớ cho `userAddress` và các `Hobby` trong `userHobbies` nếu bạn dùng con trỏ thô. (Sử dụng smart pointer sẽ đơn giản hóa việc này).
    *   Phương thức `std::unique_ptr<UserProfile> clone() const`.
    *   Phương thức `void displayProfile() const`.
4.  Trong hàm `main()`:
    *   Tạo một `UserProfile` gốc, thiết lập địa chỉ và một vài sở thích.
    *   Sử dụng `clone()` để tạo một bản sao của `UserProfile`.
    *   Thay đổi địa chỉ (`street`, `city`) của bản sao.
    *   Thêm/xóa một sở thích khỏi danh sách sở thích của bản sao.
    *   Hiển thị thông tin của cả profile gốc và profile bản sao. Kiểm tra xem các thay đổi trên bản sao có ảnh hưởng đến bản gốc không (chúng không nên ảnh hưởng nếu sao chép sâu được thực hiện đúng).

**Gợi ý:**
*   Đây là bài tập tập trung vào việc triển khai đúng hàm tạo sao chép để thực hiện deep copy.
*   Nếu `userAddress` là `Address*`, trong hàm tạo sao chép của `UserProfile`, bạn cần `new Address(*(source.userAddress))` (nếu `source.userAddress` không null).
*   Tương tự, với `userHobbies`, bạn cần duyệt qua vector `source.userHobbies` và `new Hobby(*(originalHobby))` cho mỗi hobby trong đó.
*   Sử dụng `std::unique_ptr` cho `userAddress` và `std::vector<std::unique_ptr<Hobby>>` cho `userHobbies` sẽ giúp quản lý bộ nhớ tự động và việc sao chép sâu cũng có thể được thực hiện bằng cách clone từng `unique_ptr`.
    *   Ví dụ, trong hàm tạo sao chép của `UserProfile`:
        ```cpp
        // For unique_ptr<Address>
        if (source.userAddress) {
            userAddress = std::make_unique<Address>(*source.userAddress); // Hoặc source.userAddress->clone() nếu Address là prototype
        }
        // For vector<unique_ptr<Hobby>>
        for (const auto& hobby_ptr : source.userHobbies) {
            if (hobby_ptr) {
                userHobbies.push_back(std::make_unique<Hobby>(*hobby_ptr)); // Hoặc hobby_ptr->clone()
            }
        }
        ```

---

**Lời khuyên chung khi làm bài:**

*   **Chia nhỏ vấn đề:** Xây dựng từng lớp một và kiểm tra kỹ lưỡng.
*   **Debug:** Sử dụng `std::cout` hoặc trình gỡ lỗi để theo dõi quá trình tạo và sao chép đối tượng.
*   **Quản lý bộ nhớ:** Ưu tiên sử dụng smart pointers (`std::unique_ptr`, `std::shared_ptr`) để tránh rò rỉ bộ nhớ và đơn giản hóa code.
*   **Const correctness:** Sử dụng `const` một cách hợp lý cho các phương thức không thay đổi trạng thái đối tượng (như `clone()` và các hàm getter).