using System;

class Program
{
    static void Main()
    {
        int[] nums = { -1, 0, 1, 2, -1, -4 };
        int count = CountPairs(nums, 0);
        Console.WriteLine(count);
    }

    static int CountPairs(int[] nums, int target)
    {
        Array.Sort(nums); // [-4, -1, -1, 0, 1, 2]
        int left = 0, right = nums.Length - 1, result = 0;

        while (left < right)
        {
            int sum = nums[left] + nums[right];
            if (sum == target)
            {
                result++;
                left++;
                right--;
            }
            else if (sum < target)
                left++;
            else
                right--;
        }
        return result;
    }
}