# -------------------------------------------------------------------------------
# Write a Python program for sparse matrix realization and operations on it-
# (a) Transpose, (b) Fast Transpose and (c) addition of two matrices
# -------------------------------------------------------------------------------

class Triplet:

    # Triplet = <row, column, value>
    def __init__(self, r, c, val):
        self.r = r
        self.c = c
        self.val = val


class SparseMatrix:
    def __init__(self):
        self.row = 0
        self.col = 0
        self.totalValues = 0
        self.terms = []

    def getData(self):
        self.row = int(input("Enter Number of Rows in matrix = "))
        self.col = int(input("Enter Number of Columns in matrix = "))
        print("Enter Values for 2D Matrix:")
        for i in range(self.row):
            for j in range(self.col):
                temp = int(input())
                if temp != 0:
                    t = Triplet(i, j, temp)
                    self.terms.append(t)
                    self.totalValues += 1

    def display(self):
        print(self.row, "\t", self.col, "\t", self.totalValues)
        print("----------")
        for i in range(self.totalValues):
            print(self.terms[i].r, "\t", self.terms[i].c, "\t", self.terms[i].val)
        print("----------")

    def transpose(self):
        ans = SparseMatrix()
        ans.row = self.col
        ans.col = self.row
        ans.totalValues = self.totalValues

        for i in range(self.col):
            for j in range(self.totalValues):
                if self.terms[j].c == i:
                    t = Triplet(self.terms[j].c, self.terms[j].r, self.terms[j].val)
                    ans.terms.append(t)
        return ans
    # Time Complexity = O(columns * no. of elements)

    def fastTranspose(self):
        ans = SparseMatrix()
        ans.row = self.col
        ans.col = self.row
        ans.totalValues = self.totalValues

        rowcount = [0] * self.col
        pos = [0] * self.col

        for i in range(self.totalValues):
            t = Triplet(0, 0, 0)
            ans.terms.append(t)

        for i in range(self.totalValues):
            rowcount[self.terms[i].c] += 1

        pos[0] = 0
        for i in range(1, self.col):
            pos[i] += pos[i-1] + rowcount[i-1]

        for i in range(self.totalValues):
            t = Triplet(self.terms[i].c, self.terms[i].r, self.terms[i].val)
            ans.terms[pos[self.terms[i].c]] = t
            pos[self.terms[i].c] += 1
        return ans
    # Time Complexity = O(columns + no. of elements)

    def __add__(self, m):
        if (self.row != m.row) or (self.col != m.col):
            print("Dimensions must be same, returning matrix 1")
            return self

        ans = SparseMatrix()
        ans.row = self.row
        ans.col = self.col

        a = 0
        b = 0
        while (a != self.totalValues) or (b != m.totalValues):
            if self.terms[a].r == m.terms[b].r:
                if self.terms[a].c == m.terms[b].c:
                    if (self.terms[a].val + m.terms[b].val) == 0:
                        a += 1
                        b += 1
                    else:
                        ans.terms.append(Triplet(self.terms[a].r, self.terms[a].c, self.terms[a].val + m.terms[b].val))
                        ans.totalValues += 1
                        a += 1
                        b += 1
                elif self.terms[a].c < m.terms[b].c:
                    ans.terms.append(Triplet(self.terms[a].r, self.terms[a].c, self.terms[a].val))
                    ans.totalValues += 1
                    a += 1
                else:
                    ans.terms.append(Triplet(m.terms[b].r, m.terms[b].c, m.terms[b].val))
                    ans.totalValues += 1
                    b += 1
            elif self.terms[a].r < m.terms[b].r:
                ans.terms.append(Triplet(self.terms[a].r, self.terms[a].c, self.terms[a].val))
                ans.totalValues += 1
                a += 1
            else:
                ans.terms.append(Triplet(m.terms[b].r, m.terms[b].c, m.terms[b].val))
                ans.totalValues += 1
                b += 1

        while a != self.totalValues:
            ans.terms.append(Triplet(self.terms[a].r, self.terms[a].c, self.terms[a].val))
            ans.totalValues += 1
            a += 1

        while b != m.totalValues:
            ans.terms.append(Triplet(m.terms[b].r, m.terms[b].c, m.terms[b].val))
            ans.totalValues += 1
            b += 1

        return ans


print("Matrix 1")
sm = SparseMatrix()
sm.getData()

print("\nSparse Matrix: ")
sm.display()

print("\nTranspose: ")
tr = sm.fastTranspose()
tr.display()

print("Matrix 2")
sm2 = SparseMatrix()
sm2.getData()

Sum = sm + sm2
print("\nSum of two matrices:")
Sum.display()


# m1
# 0
# 7
# 9
# 0
# 0
# -1
# 3
# 1
# 0
# 0
# 0
# 2

# m2
# 0
# 1
# 0
# 0
# 2
# 1
# 0
# 0
# 5
# 0
# 0
# 4

