# 21451 - DSL - Assignment 01 - Implement SET using LIST in python

# Function to create a set
def create_set():
    n = int(input("Enter No. of Elements for Set :"))
    list1 = []
    print("List Elements : ")
    for i in range(n):
        list1.append(int(input()))
    set1 = []
    for element in list1:
        if element not in set1:
            set1.append(element)
    return set1


# Function to display set
def display_set(set1):
    if len(set1) == 0:
        print("{}")
        return
    print("{ ", end="")
    i=0
    while i < len(set1)-1:
        print(set1[i], ", ", end="")
        i += 1
    print(set1[i],"}")


# Function to return intersection of 2 sets
def intersection_set(set1, set2):
    set3 = []
    for element in set1:
        if element in set2:
            set3.append(element)
    return set3


# Function to return symmetric difference of 2 sets
def sym_diff_set(set1, set2):
    set3 = []
    for element in set1:
        if element not in set2:
            set3.append(element)
    for element in set2:
        if element not in set1:
            set3.append(element)

    return set3


# Function to return union of 2 sets
def union_set(set1, set2):
    set3 = []
    for element in set1:
        set3.append(element)
    for element in set2:
        if element not in set3:
            set3.append(element)
    return set3


# Function to return union of 2 sets
def universal_set(set1, set2, set3):
    u = []
    for element in set1:
        u.append(element)
    for element in set2:
        if element not in u:
            u.append(element)
    for element in set3:
        if element not in u:
            u.append(element)
    return u


# Function to return union complement of 2 sets
def union_c_set(set1, set2, u):
    union = union_set(set1, set2)
    union_c = []
    for element in u:
        if element not in union:
            union_c.append(element)
    return union_c


# function to return cardinality of set
def cardinality_set(set1):
    count = 0
    for i in set1:
        count += 1
    return count


# function to return intersection of 2 sets and complement of 3rd set
def custom_operation (set1, set2, set3):
    ans = []
    for element in set1:
        if (element in set2) and (element not in set3) :
            ans.append(element)
    return ans


# function to return students not playing any game
def union_compliment(set1, set2, set3, u):
    ans = []
    for element in u:
        if (element not in set1) and (element not in set2) and (element not in set3):
            ans.append(element)
    return ans

# Create Set By Taking Input
print("Set of Students - ")
U = create_set()
print("\nUniversal Set of Students = ", end="")
display_set(U)

print("Set of Students that play Cricket - ")
C = create_set()
print("\nCricket = ", end="")
display_set(C)

print("Set of Students that play Badminton - ")
B = create_set()
print("Badminton = ", end="")
display_set(B)

print("Set of Students that play Football - ")
F = create_set()
print("Football = ", end="")
display_set(F)


# Menu Driven Program :
while True:
    print("\nFunction Menu : ")
    print("1 - Students who play both Cricket and Badminton")
    print("2 - Students who play either Cricket or Badminton but not Both")
    print("3 - Students who play neither cricket nor badminton")
    print("4 - Students who play cricket and football but not badminton")
    print("5 - Students who do not play any game")
    print("6 - Students who play at least one game")
    print("7 - Exit")

    choice = int(input("Enter your choice of function : "))

    if choice == 1:
        # Set Intersection of sets C and B
        intCB = intersection_set(C, B)
        print("\nStudents playing both Cricket and Badminton -")
        display_set(intCB)
        num = cardinality_set(intCB)
        print("Size of set for this choice = ", num)
        continue

    if choice == 2:
        # Symmetric Difference of sets C and B
        symDiffCB = sym_diff_set(C, B)
        print("\nStudents who play either Cricket or Badminton but not Both -")
        display_set(symDiffCB)
        num = cardinality_set(symDiffCB)
        print("Size of set for this choice = ", num)
        continue

    if choice == 3:
        # Union compliment of C and B
        union_c_CB = union_c_set(C, B, U)
        print("\nStudents who play neither cricket nor badminton - ")
        display_set(union_c_CB)
        num = cardinality_set(union_c_CB)
        print("Size of set for this choice = ", num)
        continue

    if choice == 4:
        # Students who play cricket and Football but not badminton i.e C.F.B'
        custom_set = custom_operation(C, F, B)
        num = cardinality_set(custom_set)
        print("\nStudents who play cricket and football but not badminton - ")
        display_set(custom_set)
        print("Size of set for this choice = ", num)
        continue

    if choice == 5:
        # Students who do not play any game
        no_game = union_compliment(C, B, F, U)
        num = cardinality_set(no_game)
        print("\nStudents who do not play any game - ")
        display_set(no_game)
        print("Size of set for this choice = ", num)
        continue

    if choice == 6:
        # Students who play at least one game
        unionCB = union_set(C, B)
        unionCBF = union_set(unionCB, F)
        num = cardinality_set(unionCBF)
        print("\nStudents who play at least one game - ")
        display_set(unionCBF)
        print("Size of set for this choice = ", num)
        continue

    if choice == 7:
        print("\nHave a Great Day !")
        break
