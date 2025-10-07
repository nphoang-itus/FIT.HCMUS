using System;
using System.Data;
using System.Globalization;

namespace MyCode
{
    class Program
    {
        static void Main()
        {
            CultureInfo culture = new CultureInfo("vi-VN");
            double money = 100000.29;

            culture.NumberFormat.NumberGroupSeparator = ".";  
            culture.NumberFormat.NumberDecimalSeparator = ","; 

            string formatted = money.ToString("#,##0.00 đ", culture.NumberFormat);
            Console.WriteLine(formatted);

            formatted = string.Format(culture, "{0:c}", money);
            Console.WriteLine(formatted);
        }
    }
}