# -----------------------------------------------------------------------
# Write a python program to compute following computation on matrix:
# (a) Addition of two matrices
# (b) Subtraction of two matrices
# (c) Multiplication of two matrices
# (d) Transpose of a matrix
# -----------------------------------------------------------------------

class Matrix:

    # ------------- REQUIRED IN ASSIGNMENT  -------------
    def __init__(self):     # default constructor
        self.row = 0        # max number of rows
        self.col = 0        # max number of columns
        self.value = []     # elements in matrix

    def get_matrix(self):   # accept elements of matrix from user
        self.row = int(input("Enter no of rows: "))
        self.col = int(input("Enter no of columns: "))
        print("Enter", self.row*self.col, "elements: ")

        for i in range(self.row):    # i = traverse in row
            r = []          # store row elements for current row
            for j in range(self.col):   # j = traverse in column
                r.append(int(input()))      # store column elements
            self.value.append(r)

    def display_matrix(self):       # display the elements of matrix
        for i in range(self.row):
            for j in range(self.col):
                print(self.value[i][j], end=" ")
            print("")

    def add(self, m):       # A + B
        ans = Matrix()
        ans.row = self.row
        ans.col = self.col

        for i in range(self.row):    # i = traverse in row
            r = []          # store row elements for current row
            for j in range(self.col):   # j = traverse in column
                r.append(self.value[i][j] + m.value[i][j])      # store column elements
            ans.value.append(r)
        return ans

    def subtract(self, m):      # A - B
        ans = Matrix()
        ans.row = self.row
        ans.col = self.col
        for i in range(self.row):    # i = traverse in row
            r = []          # store row elements for current row
            for j in range(self.col):   # j = traverse in column
                r.append(self.value[i][j] - m.value[i][j])      # store column elements
            ans.value.append(r)
        return ans

    def transpose(self):    # find transpose of A
        trans = Matrix()
        trans.row = self.row
        trans.col = self.col
        for i in range(self.row):
            r = []
            for j in range(self.col):
                r.append(self.value[j][i])
            trans.value.append(r)
        return trans

    def multiply_matrix(self, m):       # A x B
        ans = Matrix()
        ans.row = self.row
        ans.col = m.col
        for i in range(ans.row):
            r = []
            for j in range(ans.col):
                ele = 0
                for k in range(self.col):
                    ele += self.value[i][k] * m.value[k][j]
                r.append(ele)
            ans.value.append(r)
        return ans

    # ------------- OPERATOR OVERLOADING  -------------
    def __add__(self, m):       # A + B
        ans = Matrix()
        ans.row = self.row
        ans.col = self.col

        for i in range(self.row):    # i = traverse in row
            r = []          # store row elements for current row
            for j in range(self.col):   # j = traverse in column
                r.append(self.value[i][j] + m.value[i][j])      # store column elements
            ans.value.append(r)
        return ans

    def __sub__(self, m):      # A - B
        ans = Matrix()
        ans.row = self.row
        ans.col = self.col
        for i in range(self.row):    # i = traverse in row
            r = []          # store row elements for current row
            for j in range(self.col):   # j = traverse in column
                r.append(self.value[i][j] - m.value[i][j])      # store column elements
            ans.value.append(r)
        return ans

    def __mul__(self, m):       # A x B
        ans = Matrix()
        ans.row = self.row
        ans.col = m.col
        for i in range(ans.row):
            r = []
            for j in range(ans.col):
                ele = 0
                for k in range(self.col):
                    ele += self.value[i][k] * m.value[k][j]
                r.append(ele)
            ans.value.append(r)
        return ans

    # ------------- EXTRA OPERATIONS -------------
    def det(self):      # determinant of matrix
        order = self.row
        if order == 1:
            return self.value[0][0]

        elif order == 2:
            d = self.value[0][0]*self.value[1][1]
            d -= self.value[0][1]*self.value[1][0]
            return d

        elif order == 3:
            d = self.value[0][0] * (self.value[1][1] * self.value[2][2] - self.value[1][2] * self.value[2][1])
            d -= self.value[0][1] * (self.value[1][0] * self.value[2][2] - self.value[1][2] * self.value[2][0])
            d += self.value[0][2] * (self.value[1][0] * self.value[2][1] - self.value[1][1] * self.value[2][0])
            return d

    def inverse_2d(self):  # inverse of 2x2 matrix
        inv = Matrix()
        inv.row = self.row
        inv.col = self.col
        d = self.det()
        r1 = [d*self.value[1][1], d*(-self.value[0][1])]
        inv.value.append(r1)
        r2 = [d*(-self.value[1][0]), d*self.value[0][0]]
        inv.value.append(r2)

        return inv

    def check_magic(self):  # check if matrix is magic matrix
        # sum of each row, column and diagonal is same
        curr_sum = 0
        for i in range(self.col):
            curr_sum += self.value[0][i]
        magic_sum = curr_sum

        for i in range(1, self.row):
            curr_sum = 0
            for j in range(self.col):
                curr_sum += self.value[i][j]
            if curr_sum != magic_sum:
                print("Matrix is not a Magic Matrix")
                return

        for i in range(self.col):
            curr_sum = 0
            for j in range(self.row):
                curr_sum += self.value[j][i]
            if curr_sum != magic_sum:
                print("Matrix is not a Magic Matrix")
                return

        curr_sum = 0
        j = 0
        for i in range(self.col):
            curr_sum += self.value[i][j]
            j += 1
        if curr_sum != magic_sum:
            print("Matrix is not a Magic Matrix")
            return

        curr_sum = 0
        i = self.row-1
        j = 0
        while j < self.col:
            curr_sum += self.value[i][j]
            j += 1
            i -= 1
        if curr_sum != magic_sum:
            print("Matrix is not a Magic Matrix")
            return

        print("Matrix is a Magic Matrix")
        return

# ------------- END OF CLASS DEFINITION -------------


# menu driven program
while True:
    print("---------- MENU ----------")
    print("1. Enter a New Matrix")
    print("2. Add Matrix")
    print("3. Subtract Matrix")
    print("4. Multiply Matrix")
    print("5. Transpose of Matrix")
    print("6. Add matrix (operator overloading)")
    print("7. Determinant of matrix")
    print("8. Inverse of 2x2 matrix")
    print("9. Check if matrix is magic matrix")
    print("-1. Exit")
    print("--------------------------")

    choice = int(input("\nEnter your choice = "))

    if choice == 1:    # Enter new matrix
        M1 = Matrix()
        M1.get_matrix()
        M1.display_matrix()
        print('')

    elif choice == 2:   # Add Matrix
        print("For addition to previous matrix:")
        M2 = Matrix()
        M2.get_matrix()
        M2.display_matrix()
        print('')

        if M1.col != M2.col or M1.row != M2.row:
            print("Dimensions of matrices must be same!")
            continue

        Sum = M1.add(M2)
        print("Addition of two matrices:")
        Sum.display_matrix()
        print('')

    elif choice == 3:   # Subtract matrix
        print("For subtraction from previous matrix:")
        M2 = Matrix()
        M2.get_matrix()
        M2.display_matrix()
        print('')

        if M1.col != M2.col or M1.row != M2.row:
            print("Dimensions of matrices must be same!")
            continue

        Diff = M1.subtract(M2)
        print("Subtraction of two matrices:")
        Diff.display_matrix()
        print('')

    elif choice == 4:   # Multiply matrix
        print("For Multiplication with previous matrix:")
        M2 = Matrix()
        M2.get_matrix()
        M2.display_matrix()
        print('')

        if M1.col != M2.row:
            print("Invalid dimensions of matrices!")
            print("Condition: Columns in A = Rows in B ")
            continue

        Product = M1.multiply_matrix(M2)
        print("Product of two matrices:")
        Product.display_matrix()
        print('')

    elif choice == 5:   # transpose of matrix
        Transpose = M1.transpose()
        print("Transpose of given matrix:")
        Transpose.display_matrix()
        print('')

    elif choice == 6:   # Add Matrix with operator overloading
        print("For addition to previous matrix:")
        M2 = Matrix()
        M2.get_matrix()
        M2.display_matrix()
        print('')

        if M1.col != M2.col or M1.row != M2.row:
            print("Dimensions of matrices must be same!")
            continue

        Sum = M1 + M2
        print("Addition of two matrices:")
        Sum.display_matrix()
        print('')

    elif choice == 7:   # Determinant of matrix
        if M1.row != M1.col:
            print("Matrix must be square matrix!")
            continue
        print("Determinant of matrix is = ", M1.det())

    elif choice == 8:   # inverse of 2x2 matrix
        if M1.row != 2 or M1.col != 2:
            print("Only 2x2 matrix allowed!")
            continue

        Inv = M1.inverse_2d()
        Inv.display_matrix()
        print('')

    elif choice == 9:   # Check if matrix is magic matrix
        if M1.row != M1.col:
            print("Matrix must be square matrix!")
            continue

        M1.check_magic()
        print('')

    else:       # exit
        print("Exit...\n")
        break
