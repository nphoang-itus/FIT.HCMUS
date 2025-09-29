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