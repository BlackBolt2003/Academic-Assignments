# -----------------------------------------------------------------
# Write a Python program to compute following operations on STRING :
# (a) To display word with the longest length
# (b) To determine the frequency of occurrence of particular character in the string
# (c) To check whether given string is palindrome or not
# (d) To display index of first appearance of the substring
# (e) To count the occurrences of each word in a given string
# (Do not use string built-in functions)
# -----------------------------------------------------------------

class String:

    def __init__(self):                 # constructor to get value for string
        self.charList = []              # stores characters in string object
        self.strLen = 0                 # length of string
        self.wordList = []              # list to store words in string
        self.wordCount = 0              # number of words in string

    def get_string(self):               # get string attributes
        temp = input("Enter string = ")
        for i in range(len(temp)):
            self.charList.append(temp[i])
            self.strLen += 1
        self.word_list()

    def word_list(self):
        word = ""                       # create word list
        for i in range(self.strLen):
            if self.charList[i] != " ":
                word += self.charList[i]
            else:
                self.wordList.append(word)
                self.wordCount += 1
                word = ""
        self.wordList.append(word)       # last word
        self.wordCount += 1

    def display_string(self):       # display attributes of string
        print("String =", end=" ")
        for i in range(self.strLen):
            print(self.charList[i], end="")

        print("\nLength of string =", self.strLen)

        print("Word List =", self.wordList)

        print("No of words =", self.wordCount, end="\n")

    def longest_word(self):            # method to return longest word in given string
        curr_len = 0
        curr_str = ""
        max_len = 0
        max_str = ""

        for i in range(self.wordCount):
            curr_str = self.wordList[i]
            for char in curr_str:
                curr_len += 1

            if curr_len > max_len:     # compare current word with the longest word yet
                max_len = curr_len
                max_str = curr_str
                curr_len = 0

            else:
                curr_len = 0
        return max_str

    def freq_of(self, key):                     # return frequency of occurrence of a character in string
        freq = 0
        for i in range(self.strLen):
            if self.charList[i] == key:
                freq += 1
        return freq

    def check_palindrome(self):                 # check if string is a palindrome or not
        for i in range(int(self.strLen/2)):
            if self.charList[i] != self.charList[self.strLen - i - 1]:
                return "String is not a palindrome"
        return "String is a palindrome"

    def substr_occurence(self, substr):         # display index of first occurrence of given substring in string
        k = 0                                   # Index at substr for traversal
        for i in range(self.strLen):            # traverse string
            if self.charList[i] == substr.charList[k]:
                k += 1                          # increment in substring if character matches
            else:
                k = 0                           # restart in substring
            if k == substr.strLen:            # complete substring found
                return i - substr.strLen + 1
        return -1

    def word_count(self):               # return frequency of each word in string
        word_dic = {}
        for word in self.wordList:
            if word not in word_dic:
                word_dic[word] = 1
            else:
                word_dic[word] += 1

        for word in word_dic:
            print(word, " =", word_dic[word])

    def concat(self, s2):           # concatenate another string to old string
        ans = String()
        for i in range(self.strLen):
            ans.charList.append(self.charList[i])
            ans.strLen += 1
        for i in range(s2.strLen):
            ans.charList.append(s2.charList[i])
            ans.strLen += 1

        ans.word_list()
        return ans

    def all_occ(self, substr):      # Find all occurrences of a substring in string
        indices = []                            # store all occurrences
        k = 0                                   # Index at substr for traversal
        for i in range(self.strLen):            # traverse string
            if self.charList[i] == substr.charList[k]:
                k += 1                          # increment in substring if character matches
            else:
                k = 0                           # restart in substring
            if k == substr.strLen:            # complete substring found
                indices.append(i - substr.strLen + 1)       # append index to list
                k = 0
        return indices

    def get_substr(self, st, en):           # Find substring in given range
        ans = String()
        for i in range(st, en+1):
            ans.charList.append(self.charList[i])
            ans.strLen += 1
        ans.word_list()
        return ans


while True:
    print("\n-------- Menu --------")
    print("1. Enter a new String")
    print("2. Display word with the longest length")
    print("3. Frequency of occurrence of a character in the string")
    print("4. Check if string is palindrome")
    print("5. Find index of first occurrence of substring")
    print("6. Occurrence of each word in string")
    print("7. Concatenate another string to old string")
    print("8. Find all occurrences of a substring in string")
    print("9. Find substring in given range")
    print("-1. Exit")
    print("----------------------")

    choice = int(input("\nEnter your choice = "))

    if choice == 1:     # Enter a new String
        objStr = String()
        objStr.get_string()
        objStr.display_string()

    elif choice == 2:       # Display word with the longest length
        print("Longest word in string =", objStr.longest_word())

    elif choice == 3:       # Frequency of occurrence of a character in the string
        key = input("\nEnter character to find its no of occurrences = ")
        print("Frequency of occurrence of", key, " =", objStr.freq_of(key))

    elif choice == 4:       # Check if string is palindrome
        print("\n" + objStr.check_palindrome() + "\n")

    elif choice == 5:       # Find index of first occurrence of substring
        objSubStr = String()
        objSubStr.get_string()
        msg = objStr.substr_occurence(objSubStr)
        if msg == -1:
            print("Substring not found\n")
        else:
            print("Substring found first at index =", msg, "\n")

    elif choice == 6:       # Occurrence of each word in string
        print("\nWord count in given string :")
        objStr.word_count()

    elif choice == 7:       # Concatenate another string to old string
        print("\nTo concatenate in existing string:")
        S2 = String()
        S2.get_string()
        Ans = objStr.concat(S2)
        Ans.display_string()

    elif choice == 8:       # Find all occurrences of a substring in string
        objSubStr = String()
        print("\nTo find a substring in given string:")
        objSubStr.get_string()
        Idx = objStr.all_occ(objSubStr)
        if not Idx:
            print("Substring not found")
        else:
            print("Substring occurs at indices =", objStr.all_occ(objSubStr))

    elif choice == 9:       # Find substring in given range
        St = int(input("Enter start index of substring = "))
        En = int(input("Enter end index of substring (inclusive) = "))
        if St < 0 or En < 0 or St > objStr.strLen or En > objStr.strLen:    # exception for out of range
            print("Indices out of range!")
        else:
            print("Substring in given range:")
            Ans = objStr.get_substr(St, En)
            Ans.display_string()

    else:       # Exit
        print("\nExit . . .")
        break
