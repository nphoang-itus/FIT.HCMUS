## Câu promt đã sử dụng:
```
Đóng vai trò là reviewer giáo viên khó tính, hãy nhận xét đoạn mã nguồn bên dưới:
using System;
using System.Text;
using System.Collections.Generic;

namespace EmailPuzzleGame
{
    public class EmailPuzzle
    {
        // Email bị ẩn
        private char[] hiddenEmail = "_phuchoang__tus@gmail.com".ToCharArray();

        // Danh sách câu hỏi + vị trí ký tự cần lấy (0-based index)
        private List<(string question, int charIndex)> questions = new List<(string, int)>
        {
            (
                "Câu 1: Trong OOP, tính chất nào cho phép một lớp mới có thể tái sử dụng thuộc tính và phương thức của lớp cũ?\n" +
                "Trả lời đáp án bằng tiếng Anh",
                1
            ),
            (
                "Câu 2: Trong C#, ký tự nào được dùng để truy cập thành viên (property, method) của một đối tượng hoặc namespace?",
                0
            ),
            (
                "Câu 3: Kết quả in ra màn hình của đoạn code sau là gì?\n" +
                "using System;\n\n" +
                "class Program\n{\n" +
                "    static string BuildString(int n)\n" +
                "    {\n" +
                "        if (n <= 0) return \"\";\n" +
                "        if (n % 2 == 0)\n" +
                "            return \"h\" + BuildString(n - 1);\n" +
                "        else\n" +
                "            return BuildString(n - 1) + \"i\";\n" +
                "    }\n\n" +
                "    static void Main()\n" +
                "    {\n" +
                "        Console.WriteLine(BuildString(4));\n" +
                "    }\n" +
                "}",
                2
            )

        };

        public void Run()
        {
            ShowIntro();

            var extractedChars = new List<char>();

            foreach (var (question, charIndex) in questions)
            {
                string answer = AskForAnswer(question);
                char extracted = ExtractCharacter(answer, charIndex);
                extractedChars.Add(extracted);
            }

            string finalEmail = BuildEmail(extractedChars);

            ShowResult(finalEmail);
        }

        private void ShowIntro()
        {
            Console.WriteLine("============================================================");
            Console.WriteLine("        THỬ THÁCH KHÔI PHỤC EMAIL BỊ ẨN");
            Console.WriteLine("============================================================");
            Console.WriteLine("Ba ký tự trong email đã bị xóa. Hãy trả lời 3 câu hỏi dưới đây.");
            Console.WriteLine($"Email bị ẩn: {new string(hiddenEmail)}\n");
        }

        private string AskForAnswer(string question)
        {
            Console.WriteLine("------------------------------------------------------------");
            Console.WriteLine(question);
            Console.Write("Đáp án của bạn: ");
            return Console.ReadLine()?.Trim() ?? string.Empty;
        }

        private char ExtractCharacter(string answer, int index)
        {
            if (string.IsNullOrEmpty(answer) || index >= answer.Length)
                return '_'; // nếu trả lời sai hoặc quá ngắn thì ghép ký tự rỗng

            return answer[index];
        }

        private string BuildEmail(List<char> chars)
        {
            char[] emailCopy = (char[])hiddenEmail.Clone();
            int idx = 0;

            for (int i = 0; i < emailCopy.Length && idx < chars.Count; i++)
            {
                if (emailCopy[i] == '_')
                {
                    emailCopy[i] = chars[idx];
                    idx++;
                }
            }

            return new string(emailCopy);
        }

        private void ShowResult(string email)
        {
            Console.WriteLine("\n============================================================");
            Console.WriteLine("                        KẾT QUẢ");
            Console.WriteLine("============================================================");
            Console.ForegroundColor = ConsoleColor.Green;
            Console.WriteLine($"Hãy gửi lời mời tới: {email}");
            Console.ResetColor();
            Console.WriteLine("------------------------------------------------------------");
        }
    }

    class Program
    {
        static void Main()
        {
            Console.OutputEncoding = Encoding.UTF8;
            Console.InputEncoding = Encoding.UTF8;

            var game = new EmailPuzzle();
            game.Run();

            Console.WriteLine("\nNhấn Enter để thoát...");
            Console.ReadLine();
        }
    }
}
```
## Nội dung thô từ chatgpt (copy dán vào):

Dưới góc nhìn của một giáo viên khó tính, tôi sẽ đánh giá đoạn mã này theo các khía cạnh: **chất lượng code**, **cấu trúc**, **quy ước đặt tên**, **tính mở rộng**, **tính an toàn**, và **trải nghiệm người dùng**.

---

## 1. **Chất lượng code & Quy ước**

✅ **Điểm tốt:**

* Sử dụng `namespace` hợp lý, tách biệt logic vào class `EmailPuzzle`.
* Đặt tên phương thức khá rõ ràng: `Run()`, `ShowIntro()`, `AskForAnswer()`…
* Sử dụng `var` hợp lý để giảm lặp kiểu dữ liệu.
* Áp dụng `ToCharArray()` và `Clone()` để tránh thay đổi trực tiếp mảng gốc – đây là thói quen tốt.

❌ **Điểm trừ:**

* **Tên biến `hiddenEmail` chưa đủ rõ nghĩa**: nó là "email có ký tự bị ẩn", có thể đổi thành `maskedEmail` hoặc `obfuscatedEmail` để rõ ý hơn.
* **Sử dụng tuple `(string question, int charIndex)`** là tiện, nhưng có thể gây khó đọc khi dự án phức tạp hơn. Nên định nghĩa một **class Question** với thuộc tính `QuestionText` và `CharIndex` → dễ mở rộng hơn trong tương lai.
* Thiếu comment giải thích vì sao `charIndex` lại là **index của câu trả lời**, điều này có thể gây nhầm lẫn cho người đọc code lần đầu.

---

## 2. **Cấu trúc & Tính mở rộng**

✅ **Điểm tốt:**

* Chia nhỏ phương thức tương đối tốt, mỗi hàm đảm nhiệm 1 trách nhiệm (SRP).
* `BuildEmail()` được thiết kế khá sạch, dễ đọc, dễ kiểm thử.

❌ **Điểm trừ:**

* Dữ liệu `questions` đang **hard-code** trong code. Nếu số lượng câu hỏi tăng, phải biên dịch lại chương trình. Có thể cải thiện bằng cách đọc từ **file JSON** hoặc **cơ sở dữ liệu**.
* `ExtractCharacter()` chỉ đơn thuần lấy ký tự theo index, không kiểm tra tính đúng/sai của đáp án. Nghĩa là dù người dùng trả lời sai, vẫn có thể lấy ký tự bất kỳ miễn là chuỗi dài. Điều này khiến "trò chơi" mất ý nghĩa kiểm tra kiến thức.

---

## 3. **Tính an toàn & Xử lý lỗi**

❌ **Điểm yếu:**

* Không có xử lý ngoại lệ (`try/catch`). Nếu người dùng nhập dữ liệu null, hoặc nhấn Ctrl+Z (EOF), `Console.ReadLine()` có thể trả về null → hiện có check `?? string.Empty` nhưng chưa xử lý log lỗi hay thông báo người dùng nhập lại.
* `charIndex` được hard-code, nhưng không có kiểm tra xem có nằm trong phạm vi của `answer` (chỉ check `index >= answer.Length`, không kiểm tra giá trị âm). Nếu `charIndex` bị cấu hình âm sẽ gây `IndexOutOfRangeException`.

---

## 4. **Trải nghiệm người dùng**

✅ **Điểm tốt:**

* Hiển thị intro rõ ràng, gợi ý cho người chơi biết email đang ở trạng thái nào.
* Dùng màu xanh lá (`Console.ForegroundColor = ConsoleColor.Green`) để hiển thị kết quả, tạo cảm giác "thành công".

❌ **Điểm cần cải thiện:**

* Không có thông báo khi trả lời sai → người chơi không biết mình sai ở đâu.
* Không có cơ chế nhập lại khi câu trả lời quá ngắn hoặc sai → trải nghiệm game giảm hứng thú.
* Sau khi điền hết 3 ký tự, không xác minh email có hợp lệ hay không (ví dụ có dấu `@`, có phần domain hợp lệ…).

---

## 5. **Hiệu suất**

Không có vấn đề lớn vì bài toán nhỏ. Tuy nhiên:

* Với danh sách câu hỏi lớn, có thể cân nhắc dùng `StringBuilder` để nối chuỗi trong `ShowIntro()` hoặc `AskForAnswer()` để tối ưu.

---

## 6. **Đề xuất cải tiến**

* Định nghĩa class `Question` thay vì tuple để dễ mở rộng.
* Thêm lớp `GameEngine` tách biệt logic hỏi đáp với logic hiển thị (theo hướng MVC hoặc tách UI/Logic).
* Bổ sung cơ chế kiểm tra đáp án đúng/sai, yêu cầu người chơi nhập lại khi sai.
* Đọc câu hỏi từ file JSON để dễ thay đổi dữ liệu mà không phải sửa code.
* Thêm xử lý ngoại lệ, validate input chặt chẽ hơn.
* Cho phép chơi lại nếu người chơi muốn thử nhiều lần.

---

Bạn có muốn tôi **viết lại một phiên bản cải tiến** của đoạn code này theo hướng chuyên nghiệp hơn (có kiểm tra đáp án, đọc dữ liệu từ file JSON, tách UI/Logic rõ ràng)? Điều đó sẽ giúp bạn thấy cách áp dụng Clean Code và SOLID vào bài tập này.


## Các điểm cảm thấy hợp lí và các thay đổi trong mã nguồn tương ứng (tóm tắt ý chính là được không cần copy hết):
### 1. Đặt tên biến rõ nghĩa hơn (`hiddenEmail → maskedEmail`)

**Giải thích:**
Trước đây biến `hiddenEmail` chỉ ra “email bị ẩn” nhưng tên chưa rõ ràng. Đổi thành `maskedEmail` giúp người đọc hiểu ngay rằng đây là email đang được “mask” bằng ký tự `*`.

**Code:**

```csharp
private char[] maskedEmail = "_phuchoang__tus@gmail.com".ToCharArray();
```

### 2. Tách tuple ra thành class `Question`

**Giải thích:**
Trước đây danh sách câu hỏi dùng tuple `(string question, int charIndex)`. Điều này khó đọc và khó mở rộng (không thể thêm nhiều thuộc tính khác như đáp án chuẩn, điểm số...).
Giờ tạo riêng một class `Question` giúp code rõ ràng, dễ mở rộng về sau.

**Code:**

```csharp
class Question
{
    public string QuestionText { get; set; }

    // charIndex: vị trí ký tự trong câu trả lời được dùng để giải mã email
    public int CharIndex { get; set; }

    public Question(string questionText, int charIndex)
    {
        QuestionText = questionText;
        CharIndex = charIndex;
    }
}

// Danh sách câu hỏi sau khi chỉnh:
List<Question> questions = new List<Question>
{
    //... Các câu hỏi
```

### 3. Bổ sung comment giải thích `charIndex`

**Giải thích:**
Trước đây người đọc khó hiểu `charIndex` dùng để làm gì.
Tôi đã thêm comment ngay trong class để giải thích mục đích: “lấy ký tự tại vị trí `charIndex` trong câu trả lời để giải mã email, kể cả khi trả lời sai.”

**Code:**

```csharp
/// <summary>
/// Vị trí ký tự cần lấy từ câu trả lời (0-based index).
/// Nếu trả lời sai, vẫn lấy ký tự ở vị trí này để tạo email bị sai.
/// </summary>
public int CharIndex { get; set; }
```

### 4. Vẫn cho phép lấy ký tự dù trả lời sai

**Giải thích:**
Theo yêu cầu đề bài, ngay cả khi người dùng trả lời sai, vẫn phải lấy ký tự tại `charIndex`.
Điều này giữ nguyên tính thử thách (email sẽ “bị sai” theo đáp án người chơi).

**Code:**

```csharp
for (int i = 0; i < emailCopy.Length && idx < chars.Count; i++)
{
    if (emailCopy[i] == '_')
    {
        emailCopy[i] = chars[idx];
        idx++;
    }
}
```

### 5. Thêm xử lý `try/catch`

**Giải thích:**
Trước đây nếu nhập dữ liệu bất thường (như Ctrl+Z) hoặc xảy ra lỗi runtime, chương trình sẽ crash.
Giờ tôi bọc toàn bộ logic trong `try/catch` để hiển thị thông báo lỗi thay vì kết thúc bất ngờ.

**Code:**

```csharp
try
{
    // Toàn bộ logic chương trình nằm trong đây
}
catch (Exception ex)
{
    Console.WriteLine($"Đã xảy ra lỗi: {ex.Message}");
}
```

### 6. Kiểm tra giới hạn index

**Giải thích:**
Trước đây chỉ kiểm tra `index < answer.Length`, nhưng chưa kiểm tra giá trị âm → có nguy cơ `IndexOutOfRangeException`.
Giờ tôi bổ sung điều kiện `index >= 0` để tránh lỗi.

**Code:**

```csharp
if (string.IsNullOrEmpty(answer) || index < 0 || index >= answer.Length)
    return '_'; // nếu trả lời sai hoặc quá ngắn thì ghép ký tự rỗng
```

##  Các điểm cảm thấy không hợp lí nên đã không làm theo kèm lí do:
1. Đọc câu hỏi từ JSON / DB
Lý do: Đề bài chỉ yêu cầu một bài tập nhỏ 3 câu hỏi, không cần phức tạp hóa bằng file ngoài. Hard-code đủ dùng và dễ hiểu.
2. Thông báo khi trả lời sai
Lý do: Đề bài muốn email bị sai nếu người chơi trả lời sai, nên không có thông báo là hợp lý. Nếu cảnh báo thì sẽ giúp họ sửa → trái yêu cầu đề bài.
3. Cho nhập lại khi sai
Lý do: Giống trên, đề bài không yêu cầu nhập lại, mục tiêu là tạo email sai để nhận ra.
4. Kiểm tra email hợp lệ sau khi hoàn thành
Lý do: Không cần, vì mục tiêu là minh họa sự thay đổi ký tự trong email chứ không phải kiểm tra cú pháp email chuẩn.
5. Tối ưu StringBuilder
Lý do: Chỉ có 3-4 dòng in ra, hiệu năng không phải vấn đề.