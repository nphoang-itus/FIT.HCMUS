using System;
using System.Text;
using System.Collections.Generic;

namespace EmailPuzzleGame
{
    /// <summary>
    /// Lớp đại diện cho một câu hỏi và thông tin vị trí ký tự cần lấy
    /// </summary>
    public class Question
    {
        public string QuestionText { get; set; }
        /// <summary>
        /// Vị trí ký tự cần lấy từ câu trả lời (0-based index).
        /// Nếu trả lời sai, vẫn lấy ký tự ở vị trí này để tạo email bị sai.
        /// </summary>
        public int CharIndex { get; set; }

        public Question(string questionText, int charIndex)
        {
            QuestionText = questionText;
            CharIndex = charIndex;
        }
    }

    public class EmailPuzzle
    {
        // Email có ký tự bị ẩn (masked email)
        private char[] maskedEmail = "_phuchoang__tus@gmail.com".ToCharArray();

        // Danh sách câu hỏi, mỗi câu hỏi xác định vị trí ký tự cần lấy
        private List<Question> questions = new List<Question>
        {
            new Question(
                "Câu 1: Trong OOP, tính chất nào cho phép một lớp mới có thể tái sử dụng thuộc tính và phương thức của lớp cũ?\n" +
                "Trả lời đáp án bằng tiếng Anh",
                1
            ),
            new Question(
                "Câu 2: Trong C#, ký tự nào được dùng để truy cập thành viên (property, method) của một đối tượng hoặc namespace?",
                0
            ),
            new Question(
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
            try
            {
                ShowIntro();

                var extractedChars = new List<char>();

                foreach (var q in questions)
                {
                    string answer = AskForAnswer(q.QuestionText);
                    char extracted = ExtractCharacter(answer, q.CharIndex);
                    extractedChars.Add(extracted);
                }

                string finalEmail = BuildEmail(extractedChars);

                ShowResult(finalEmail);
            }
            catch (Exception ex)
            {
                Console.ForegroundColor = ConsoleColor.Red;
                Console.WriteLine("\nĐã xảy ra lỗi không mong muốn:");
                Console.WriteLine(ex.Message);
                Console.ResetColor();
            }
        }

        private void ShowIntro()
        {
            Console.WriteLine("============================================================");
            Console.WriteLine("        THỬ THÁCH KHÔI PHỤC EMAIL BỊ ẨN");
            Console.WriteLine("============================================================");
            Console.WriteLine("Ba ký tự trong email đã bị xóa. Hãy trả lời 3 câu hỏi dưới đây.");
            Console.WriteLine($"Email bị ẩn: {new string(maskedEmail)}\n");
        }

        private string AskForAnswer(string question)
        {
            try
            {
                Console.WriteLine("------------------------------------------------------------");
                Console.WriteLine(question);
                Console.Write("Đáp án của bạn: ");

                string? input = Console.ReadLine();

                // Xử lý trường hợp null hoặc chỉ nhập khoảng trắng
                return string.IsNullOrWhiteSpace(input) ? string.Empty : input.Trim();
            }
            catch (Exception ex)
            {
                Console.ForegroundColor = ConsoleColor.Yellow;
                Console.WriteLine($"Lỗi khi nhập dữ liệu: {ex.Message}");
                Console.ResetColor();
                return string.Empty;
            }
        }

        private char ExtractCharacter(string answer, int index)
        {
            try
            {
                // Kiểm tra an toàn: index phải >= 0 và nhỏ hơn độ dài chuỗi mới lấy được ký tự
                if (string.IsNullOrEmpty(answer) || index < 0 || index >= answer.Length)
                    return '_'; // nếu trả lời sai hoặc quá ngắn thì ghép ký tự rỗng

                return answer[index];
            }
            catch (Exception ex)
            {
                Console.ForegroundColor = ConsoleColor.Yellow;
                Console.WriteLine($"Lỗi khi trích xuất ký tự: {ex.Message}");
                Console.ResetColor();
                return '_';
            }
        }

        private string BuildEmail(List<char> chars)
        {
            char[] emailCopy = (char[])maskedEmail.Clone();
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
