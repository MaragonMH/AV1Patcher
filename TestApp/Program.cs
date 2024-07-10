using System.Threading;
using System;


namespace TestApp
{
    internal class Program
    {
        private static void Main()
        {
            int i = 0;
            while (i < 30)
            {
                F(i++);
                Thread.Sleep(1000);
            }
        }

        private static void F(int i)
        {
            Console.WriteLine($"TestApp: {i}");
        }
    }
}
