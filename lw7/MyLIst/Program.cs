using MyLIst;
using System;
class Program
{
    static void Main(string[] args)
    {
        CMyList<int> myList = new CMyList<int>();

        myList.Add(1);
        myList.Add(2);
        myList.Add(3);
        myList.Insert(1, 4);

        Console.WriteLine("Список:");
        foreach (int item in myList)
        {
            Console.WriteLine(item);
        }

        Console.WriteLine("Перебор элементов в прямом направлении:");
        var iterator = myList.GetEnumerator();
        while (iterator.MoveNext())
        {
            int item = iterator.Current;
            Console.WriteLine(item);
        }

        Console.WriteLine("Перебор элементов в обратном направлении:");
        var reverseIterator = myList.GetReverseEnumerator();
        while (reverseIterator.MoveNext())
        {
            int item = reverseIterator.Current;
            Console.WriteLine(item);
        }

        myList.RemoveAt(2);

        Console.WriteLine("Обновленный список:");
        foreach (int item in myList)
        {
            Console.WriteLine(item);
        }

        Console.WriteLine("Количество элементов: " + myList.Count);

        CMyList<int> copyList = new CMyList<int>(myList);

        Console.WriteLine("Копия списка:");
        foreach (int item in copyList)
        {
            Console.WriteLine(item);
        }

        CMyList<string> strings = new CMyList<string>();

        strings.InsertFirst("Hello");
        strings.InsertLast(" world!");
        strings.Add("faceit.com");
        var it = strings.GetEnumerator();


        Console.WriteLine("Список строк: ");

        Console.WriteLine("Перебор элементов в прямом направлении:");
        while (it.MoveNext())
        {
            string item = it.Current;
            Console.WriteLine(item);
        }

        Console.WriteLine("Перебор элементов в обратном направлении:");
        var revIT = strings.GetReverseEnumerator();
        while (revIT.MoveNext())
        {
            string item = revIT.Current;
            Console.WriteLine(item);
        }
    }
}
