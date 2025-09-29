using System;

namespace DateCheckApp
{
  class Program
  {
    static void Main()
    {
      // int day = 10;
      // int month = 12;
      // int year = 1999;
      findNextDateUseCase(31, 12, 1999);
    }

    public static bool isValidDate(int day, int month, int year)
    {
      if (day < 1 || (month < 1 || month > 12) || year < 1900)
      {
        return false;
      }

      int[] daysInMonth = {
        31,
        (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0) ? 29 : 28,
        31, 30, 31, 30,
        31, 31, 30, 31, 30, 31
      };

      return day <= daysInMonth[month - 1];
    }

    static public (int, int, int) getNextDay(int day, int month, int year)
    {
      int[] daysInMonth = {
        31,
        (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0) ? 29 : 28,
        31, 30, 31, 30,
        31, 31, 30, 31, 30, 31
      };

      // day++;
      // if (day > daysInMonth[month - 1])
      // {
      //   day = 1;
      //   month++;
      //   if (month > 12)
      //   {
      //     month = 1;
      //     year++;
      //   }
      // }

      return (nextDay, nextMonth, nextYear);
    }

    static void findNextDateUseCase(int day, int month, int year)
    {
      if (isValidDate(day, month, year))
      {
        var (nextDay, nextMonth, nextYear) = getNextDay(day, month, year);
        Console.WriteLine($"Next date is: {nextDay}/{nextMonth}/{nextYear}");
      }
      else
      {
        Console.WriteLine("Invalid Date");
      }
    }
  }
}