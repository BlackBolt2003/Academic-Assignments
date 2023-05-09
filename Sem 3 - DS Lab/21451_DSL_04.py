# ---------------------------------------------------------------------------
# (a) Write a Python program to store roll numbers of students in
# array who attended training program in random order. Write
# function for searching whether particular student attended
# training program or not, using Linear search and Sentinel
# search.
# (b) Write a Python program to store roll numbers of student
# array who attended training program in sorted order. Write
# function for searching whether particular student attended
# training program or not, using Binary search and Fibonacci search.
# ---------------------------------------------------------------------------

class SearchTech:
    def __init__(self):  # default constructor
        self.array = []
        self.size = 0
        self.comparisons = 0
        self.sortedArray = []

    def getArray(self):  # get array elements
        self.size = int(input("Enter size of Array:"))
        print("Enter array elements:")
        for i in range(self.size):
            temp = int(input())
            self.array.append(temp)
        self.sortedArray = self.array.copy()
        self.sortedArray.sort()

    def linearSearch(self, key):  # linear search - iterative method
        self.comparisons = 0
        for i in range(self.size):
            if self.array[i] == key:
                self.comparisons += 1
                return [i, self.comparisons]
            else:
                self.comparisons += 1
        return [-1, self.comparisons]

    def linearSearchRecursive(self, currIdx, key):  # linear search - recursive method
        if currIdx == self.size:
            self.comparisons = currIdx
            return [-1, self.comparisons]
        if self.array[currIdx] == key:
            self.comparisons = currIdx + 1
            return [currIdx, self.comparisons]
        return self.linearSearchRecursive(currIdx + 1, key)

    def binarySearch(self, key):  # binary search - iterative method
        self.comparisons = 0
        low = 0
        high = self.size - 1
        while low <= high:
            mid = (low + high) // 2
            self.comparisons += 1
            if self.sortedArray[mid] == key:
                return [mid, self.comparisons]
            elif key < self.sortedArray[mid]:
                high = mid - 1
            else:
                low = mid + 1
        return [-1, self.comparisons]

    def binarySearchRecursive(self, low, high, key, comparisons):  # binary search - recursive method
        if low == high:
            if key == self.sortedArray[low]:
                return [low, comparisons]
            else:
                return [-1, comparisons]
        else:
            mid = (low + high) // 2
            if self.sortedArray[mid] == key:
                return [mid, comparisons]
            elif key < self.sortedArray[mid]:
                return self.binarySearchRecursive(low, mid - 1, key, comparisons + 1)
            else:
                return self.binarySearchRecursive(mid + 1, high, key, comparisons + 1)

    def sentinelSearch(self, key):  # sentinel search
        last = self.array[self.size - 1]  # store last element
        self.array[self.size - 1] = key  # set last element as key to search
        i = 0
        while self.array[i] != key:
            i += 1
        self.array[self.size - 1] = last  # put last element back
        if (i < self.size - 1) or (key == self.array[self.size - 1]):
            self.comparisons = i + 1
            return [i, self.comparisons]
        else:
            self.comparisons = i + 1
            return [-1, self.comparisons]

    def fiboSearch(self, key):
        st = 0
        n = self.size
        en = n - 1
        flag = False
        self.comparisons = 0
        while (flag is False) and (st <= en):
            m = 0
            idx = fibo(m)
            while idx < n:
                m += 1
                idx = fibo(m)
            if idx >= n:
                idx = fibo(m-1)
            self.comparisons += 1
            if self.sortedArray[st + idx] == key:
                flag = True
                return [st + idx, self.comparisons]
            elif self.sortedArray[st + idx] < key:
                st = st + idx + 1
            else:
                en = st + idx - 1
            n = en - st + 1
        return [-1, self.comparisons]

    def fiboSearchRecursive(self, key, st, en, n):
        # st = 0
        # n = self.size
        # en = n - 1
        if st <= en:
            m = 0
            idx = fibo(m)
            while idx < n:
                m += 1
                idx = fibo(m)
            if idx >= n:
                idx = fibo(m - 1)
            self.comparisons += 1
            if self.sortedArray[st + idx] == key:
                return [st + idx, self.comparisons]
            elif self.sortedArray[st + idx] < key:
                st = st + idx + 1
            else:
                en = st + idx - 1
            n = en - st + 1
            self.fiboSearchRecursive(key, st, en, n)
        return [-1, self.comparisons]


def fibo(m):
    # 0 1 1 2 3 5 8 13 21
    if m == 0 or m == 1:
        return m
    fib1 = 0
    fib2 = 1
    fib = fib1 + fib2
    for i in range(m - 2):
        fib1 = fib2
        fib2 = fib
        fib = fib1 + fib2
    return fib


# driver code
while True:
    print("-----Menu-----")
    print("1. Enter Array of Roll Numbers")
    print("2. Linear Search")
    print("3. Binary Search")
    print("4. Sentinel Search")
    print("5. Fibonacci Search")
    print("-1. Exit")
    print("--------------")
    choice = int(input("Enter your choice:"))

    if choice == 1:  # Enter Array of Roll Numbers

        obj = SearchTech()
        obj.getArray()

    elif choice == 2:  # Linear Search

        print("Array =", obj.array)
        Key = int(input("Enter element to search:"))
        print("Result of Iterative Linear Search:")
        searchResult = obj.linearSearch(Key)
        if searchResult[0] == -1:
            print("Element not found in", searchResult[1], "comparisons")
        else:
            print("Element found at index", searchResult[0], "in", searchResult[1], "comparisons")

        print("Result of Recursive Linear Search:")
        searchResult = obj.linearSearchRecursive(0, Key)
        if searchResult[0] == -1:
            print("Element not found in", searchResult[1], "comparisons")
        else:
            print("Element found at index", searchResult[0], "in", searchResult[1], "comparisons")

    elif choice == 3:  # Binary Search

        print("Sorted Array =", obj.sortedArray)
        Key = int(input("Enter element to search:"))
        print("Result of Iterative Binary Search:")
        searchResult = obj.binarySearch(Key)
        if searchResult[0] == -1:
            print("Element not found in", searchResult[1], "comparisons")
        else:
            print("Element found at index", searchResult[0], "in", searchResult[1], "comparisons")

        print("Result of Recursive Binary Search:")
        searchResult = obj.binarySearchRecursive(0, obj.size - 1, Key, 1)
        if searchResult[0] == -1:
            print("Element not found in", searchResult[1], "comparisons")
        else:
            print("Element found at index", searchResult[0], "in", searchResult[1], "comparisons")

    elif choice == 4:  # sentinel search
        print("Array =", obj.array)
        Key = int(input("Enter element to search:"))
        print("Result of Sentinel Search:")
        searchResult = obj.sentinelSearch(Key)
        if searchResult[0] == -1:
            print("Element not found in", searchResult[1], "comparisons")
        else:
            print("Element found at index", searchResult[0], "in", searchResult[1], "comparisons")

    elif choice == 5:  # fibonacci search
        print("Sorted Array =", obj.sortedArray)
        Key = int(input("Enter element to search:"))
        print("Result of Fibonacci Search:")
        # searchResult = obj.fiboSearch(Key)
        searchResult = obj.fiboSearchRecursive(Key, 0, obj.size-1, obj.size)
        if searchResult[0] == -1:
            print("Element not found in", searchResult[1], "comparisons")
        else:
            print("Element found at index", searchResult[0], "in", searchResult[1], "comparisons")

    else:
        print("----Exit from Program----")
        break

# end of code
