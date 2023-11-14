import sys
import socket


print("1. Search by url")
print("2. Search by IP address")
choice = int(input("\nEnter the choice: "))

if choice == 1:
    name = input("Enter url: ")
    print(socket.gethostbyname(name))
elif choice == 2:
    address = input("Enter address: ")
    print(socket.gethostbyaddr(address))
else:
    print("please enter valid choice!")