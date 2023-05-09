# Write a python program to store second year percentage of students in array. Write function
# for sorting array of floating-point numbers in ascending order using
# (a) Insertion sort
# (b) Shell Sort, and display top five scores

class SortTech:
    def __init__(self):
        self.size = 0   # size of array
        self.arr = []   # array to store percentage scores of students
        self.top = []   # array to store top five students
        self.sortFlag = False   # whether array is sorted or not

    def getArray(self):
        self.size = int(input("Enter Size of Array: "))
        print("Enter Percentage scores: ")
        for i in range(self.size):
            temp = float(input())
            self.arr.append(temp)

    def insertionSort(self):
        for i in range(1, self.size):
            # select value to insert
            value = self.arr[i]
            pos = i-1
            # locate position 'pos' to insert 'value'
            while (pos >= 0) and (self.arr[pos] > value):    # while inside array and prev element greater than value
                self.arr[pos+1] = self.arr[pos]                 # swap elements
                pos -= 1                                    # decrement position
            # insert 'value' at final position 'pos'
            self.arr[pos+1] = value
        self.sortFlag = True

    def bubbleSort(self):
        for k in range(self.size):
            for i in range(self.size - 1 - k):
                if self.arr[i] > self.arr[i+1]:
                    temp = self.arr[i]
                    self.arr[i] = self.arr[i+1]
                    self.arr[i+1] = temp
            print("pass", k, "=", self.arr)
        self.sortFlag = True

    def selectionSort(self):
        for st in range(self.size):
            minNo = self.arr[st]
            idx = st
            for i in range(st, self.size):
                if self.arr[i] < minNo:
                    minNo = self.arr[i]
                    idx = i
            temp = self.arr[st]
            self.arr[st] = self.arr[idx]
            self.arr[idx] = temp
            print("pass", st, "=", self.arr)
        self.sortFlag = True

    def shellSort(self):
        # Knuth's Formula for interval
        interval = 0
        passes = 0
        while interval < self.size/3:
            interval = int(interval * 3 + 1)

        while interval > 0:
            for outer in range(interval, self.size):
                # select value to insert
                value = self.arr[outer]
                inner = outer

                # shift element to right
                while (inner > interval - 1) and (self.arr[inner - interval] >= value):
                    self.arr[inner] = self.arr[inner - interval]
                    inner = inner - interval

                # insert number at hole position
                self.arr[inner] = value
                print("pass", passes, "=", self.arr)

            # calculate interval
            interval = int((interval - 1) / 3)
        self.sortFlag = True

    def setTopScores(self):
        if self.size > 5:
            for i in range(5):
                temp = self.arr[self.size - i - 1]
                self.top.append(temp)

        else:
            for i in range(self.size):
                temp = self.arr[self.size - i - 1]
                self.top.append(temp)

# 21.34
# 98.76
# 56.78
# 67.43
# 23.33
# 89.76
# 76.54


# driver code
while True:
    print("-----Menu-----")
    print("1. Enter Array of Percentage Scores of Students")
    print("2. Insertion Sort")
    print("3. Shell Sort")
    print("4. Bubble Sort")
    print("5. Selection Sort")
    print("6. Get Top 5 Scores")
    print("-1. Exit")
    print("--------------")
    choice = int(input("Enter your choice:"))

    if choice == 1:     # Enter Array of Percentage Scores of Students
        obj = SortTech()
        obj.getArray()

    elif choice == 2:   # Insertion Sort
        obj.insertionSort()
        obj.setTopScores()
        print("Sorted Array =", obj.arr)

    elif choice == 3:   # Shell Sort
        obj.shellSort()
        obj.setTopScores()
        print("Sorted Array =", obj.arr)

    elif choice == 4:   # Bubble Sort
        obj.bubbleSort()
        obj.setTopScores()
        print("Sorted Array =", obj.arr)

    elif choice == 5:   # Selection Sort
        obj.selectionSort()
        obj.setTopScores()
        print("Sorted Array =", obj.arr)

    elif choice == 6:   # Get Top 5 Scores
        if not obj.sortFlag:
            print("Array Not Sorted Yet!")
            continue
        elif obj.size > 5:
            print("Top 5 Scores:", obj.top)
        else:
            print("Top", obj.size, "Scores:", obj.top)

    else:   # Exit
        print("---- Exit from Program ----")
        break
