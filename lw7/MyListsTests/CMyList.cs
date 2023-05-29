 using System;
using System.Collections;
using System.Collections.Generic;



namespace MyLIst
{

    public class CMyList<T> : IEnumerable<T>
    {
        private class Node
        {
            public T Data { get; set; }
            public Node Prev { get; set; }
            public Node Next { get; set; }

            public Node(T data, Node prev = null, Node next = null)
            {
                Data = data;
                Prev = prev;
                Next = next;
            }
        }

        private Node _head;
        private Node _tail;
        private int _count;

        public int Count => _count;

        public CMyList()
        {
            _head = null;
            _tail = null;
            _count = 0;
        }

        public CMyList(CMyList<T> other)
        {
            _head = null;
            _tail = null;
            _count = 0;

            foreach (T item in other)
            {
                Add(item);
            }
        }
        // сделать за константное время
        public void Add(T item)
        {
            Node newNode = new Node(item);

            if (_head == null)
            {
                _head = newNode;
                _tail = newNode;
            }
            else
            {
                newNode.Prev = _tail;
                _tail.Next = newNode;
                _tail = newNode;
            }

            _count++;
        }
        // передача T в начало, в конец, в произвольну позицию
        public void Insert(int index, T item)
        {
            if (index < 0 || index > _count)
            {
                throw new ArgumentOutOfRangeException(nameof(index));
            }

            if (index == _count)
            {
                Add(item);
                return;
            }

            Node newNode = new Node(item);

            if (index == 0)
            {
                newNode.Next = _head;
                _head.Prev = newNode;
                _head = newNode;
            }
            else
            {
                Node current = _head;
                for (int i = 0; i < index; i++)
                {
                    current = current.Next;
                }

                newNode.Prev = current.Prev;
                newNode.Next = current;
                current.Prev.Next = newNode;
                current.Prev = newNode;
            }

            _count++;
        }

        public void InsertFirst(T item)
        {
            Node newNode = new Node(item);

            if (_head == null)
            {
                _head = newNode;
                _tail = newNode;
            }
            else
            {
                newNode.Next = _head;
                _head.Prev = newNode;
                _head = newNode;
            }

            _count++;
        }

        public void InsertLast(T item)
        {
            Add(item);
        }
        // передача T в начало, в конец, в произвольну позицию
        public void RemoveAt(int index)
        {
            if (index < 0 || index >= _count)
            {
                throw new ArgumentOutOfRangeException(nameof(index));
            }

            if (index == 0)
            {
                _head = _head.Next;
                if (_head != null)
                {
                    _head.Prev = null;
                }
            }
            else if (index == _count - 1)
            {
                _tail = _tail.Prev;
                _tail.Next = null;
            }
            else
            {
                Node current = _head;
                for (int i = 0; i < index; i++)
                {
                    current = current.Next;
                }

                current.Prev.Next = current.Next;
                current.Next.Prev = current.Prev;
            }

            _count--;
        }

        public IEnumerator<T> GetEnumerator()
        {
            Node current = _head;
            while (current != null)
            {
                yield return current.Data;
                current = current.Next;
            }
        }
        // тест: во время итерации по списки можно удалить/добавлять элементы
        IEnumerator IEnumerable.GetEnumerator()
        {
            return GetEnumerator();
        }

        public IEnumerator<T> GetReverseEnumerator()
        {
            Node current = _tail;
            while (current != null)
            {
                yield return current.Data;
                current = current.Prev;
            }
        }
        // DeepCopy || Clone?
        public CMyList<T> DeepCopy()
        {
            return new CMyList<T>(this);
        }
        // написать тест
        public CMyList<T> Clone()
        {
            CMyList<T> newList = new CMyList<T>();
            foreach (T item in this)
            {
                newList.Add(item);
            }
            return newList;
        }
        // написать тесты
        public CMyList<T> this[int index]
        {
            get
            {
                if (index < 0 || index >= _count)
                {
                    throw new ArgumentOutOfRangeException(nameof(index));
                }

                CMyList<T> newList = new CMyList<T>();
                Node current = _head;
                for (int i = 0; i <= index; i++)
                {
                    newList.Add(current.Data);
                    current = current.Next;
                }
                return newList;
            }
        }

    }
}