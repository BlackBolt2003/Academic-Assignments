import socket
from _thread import *

HOST = '127.0.0.1'
PORT = 2003
threadCount = 0

ServerSideSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

try:
    ServerSideSocket.bind((HOST, PORT))
except socket.error as err:
    print(str(err))

print("Socket is listening...")
ServerSideSocket.listen(5)  #argument = backlog connections

def multi_threaded_client(connection):
    connection.send(str.encode('Server is working:'))
    while True:
        data = connection.recv(1024)
        response = "Server message: " + data.decode()
        
        if not data:
            break
        
        connection.sendall(str.encode(response))
        
        if data.decode() == 'exit':
            break

    print(f"Closed connection: {client}")
    connection.close()

while True:
    client, address = ServerSideSocket.accept()
    print(f"Connected to: {address[0]} : {str(address[1])}")
    start_new_thread(multi_threaded_client, (client, ))
    threadCount += 1
    print(f"Thread Number : {str(threadCount)}")

    command = input()
    if command == "exit":
        print("Server process terminated...")
        ServerSideSocket.close()
