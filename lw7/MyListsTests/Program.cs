using System;
using Xunit;
namespace MyLIst
{
    public class CMyListTests
    {
        [Fact]
        public void Add_AddsItemToList()
        {
            // Arrange
            var list = new CMyList<int>();

            // Act
            list.Add(1);

            // Assert
            Assert.Equal(1, list.Count);
            Assert.Equal(1, list[0].Count);
        }

        [Fact]
        public void InsertFirst_InsertsItemAtBeginning()
        {
            // Arrange
            var list = new CMyList<int> { 2, 3 };

            // Act
            list.InsertFirst(1);

            // Assert
            Assert.Equal(3, list.Count);
            Assert.Equal(1, list[0].Count);
            Assert.Equal(2, list[1].Count);
            Assert.Equal(3, list[2].Count);
        }

        [Fact]
        public void GetEnumerator_ReturnsItemsInOrder()
        {
            // Arrange
            var list = new CMyList<int> { 1, 2, 3 };

            // Act
            var enumerator = list.GetEnumerator();

            // Assert
            Assert.True(enumerator.MoveNext());
            Assert.Equal(1, enumerator.Current);
            Assert.True(enumerator.MoveNext());
            Assert.Equal(2, enumerator.Current);
            Assert.True(enumerator.MoveNext());
            Assert.Equal(3, enumerator.Current);
            Assert.False(enumerator.MoveNext());
        }

        [Fact]
        public void GetReverseEnumerator_ReturnsItemsInReverseOrder()
        {
            // Arrange
            var list = new CMyList<int> { 1, 2, 3 };

            // Act
            var enumerator = list.GetReverseEnumerator();

            // Assert
            Assert.True(enumerator.MoveNext());
            Assert.Equal(3, enumerator.Current);
            Assert.True(enumerator.MoveNext());
            Assert.Equal(2, enumerator.Current);
            Assert.True(enumerator.MoveNext());
            Assert.Equal(1, enumerator.Current);
            Assert.False(enumerator.MoveNext());
        }
        // get tests for empty list
        [Fact]
        public void DeepCopy_CreatesCopyWithSameValues()
        {
            // Arrange
            var originalList = new CMyList<int> { 1, 2, 3 };

            // Act
            var copyList = originalList.DeepCopy();

            // Assert
            Assert.NotSame(originalList, copyList);
            Assert.Equal(originalList.Count, copyList.Count);

            for (int i = 0; i < originalList.Count; i++)
            {
                Assert.NotSame(originalList[i], copyList[i]);
                Assert.Equal(originalList[i].Count, copyList[i].Count);
                Assert.Equal(originalList[i][0], copyList[i][0]);
            }
        }

        [Fact]
        public void Clone_CreatesCopyWithSameValues()
        {
            // Arrange
            var originalList = new CMyList<int> { 1, 2, 3 };

            // Act
            var copyList = originalList.Clone();

            // Assert
            Assert.NotSame(originalList, copyList);
            Assert.Equal(originalList.Count, copyList.Count);

            for (int i = 0; i < originalList.Count; i++)
            {
                Assert.NotSame(originalList[i], copyList[i]);
                Assert.Equal(originalList[i].Count, copyList[i].Count);
                Assert.Equal(originalList[i][0], copyList[i][0]);
            }
        }
    }
}
