# Write a python program to store first year percentage of students in array. Write function for
# sorting array of floating point numbers in ascending order using "quick sort" and display top
# five scores.

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

    # low -> starting index of partition
    # high -> ending index of partition

    def partition(self, low, high):
        # pivot -> element to be placed at correct position
        pivot = self.arr[high]
        # correct position of pivot so far
        idx = low - 1

        for k in range(low, high):
            if self.arr[k] < pivot:
                idx += 1
                # swap
                temp = self.arr[idx]
                self.arr[idx] = self.arr[k]
                self.arr[k] = temp
        # swap
        temp = self.arr[idx+1]
        self.arr[idx+1] = self.arr[high]
        self.arr[high] = temp
        return idx+1

    def quickSort(self, low, high):
        if low < high:
            # pi -> partitioning index
            # arr[pi] -> element currently at its correct position
            pi = self.partition(low, high)

            # sort left partition
            self.quickSort(low, pi-1)

            # sort right partition
            self.quickSort(pi+1, high)
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


# driver code
while True:
    print("-----Menu-----")
    print("1. Enter Array of Percentage Scores of Students")
    print("2. Quick Sort")
    print("3. Get Top 5 Scores")
    print("-1. Exit")
    choice = int(input("Enter your choice:"))

    if choice == 1:     # Enter Array of Percentage Scores of Students
        obj = SortTech()
        obj.getArray()

    elif choice == 2:   # Quick Sort
        obj.quickSort(0, obj.size-1)
        obj.setTopScores()
        print("Sorted Array =", obj.arr)

    elif choice == 3:   # Get Top 5 Scores
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
