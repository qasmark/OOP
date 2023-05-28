using MyLIst;
using System;
class Program
{
    static void Main(string[] args)
    {
        CMyList<int> myList = new CMyList<int>();

        // Добавление элементов в список
        myList.Add(1);
        myList.Add(2);
        myList.Add(3);

        // Вставка элемента в позицию
        myList.Insert(1, 4);

        // Вывод содержимого списка
        Console.WriteLine("Список:");
        foreach (int item in myList)
        {
            Console.WriteLine(item);
        }

        // Использование итераторов для перебора элементов
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

        // Удаление элемента из списка
        myList.RemoveAt(2);

        // Вывод обновленного списка
        Console.WriteLine("Обновленный список:");
        foreach (int item in myList)
        {
            Console.WriteLine(item);
        }

        // Количество элементов списка
        Console.WriteLine("Количество элементов: " + myList.Count);

        // Копирование списка
        CMyList<int> copyList = new CMyList<int>(myList);

        // Вывод копии списка
        Console.WriteLine("Копия списка:");
        foreach (int item in copyList)
        {
            Console.WriteLine(item);
        }

        CMyList<string> strings = new CMyList<string>();


    }
}
