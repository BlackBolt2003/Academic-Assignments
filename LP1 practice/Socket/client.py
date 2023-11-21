import socket

HOST = '127.0.0.1'
PORT = 2003
ClientMultiSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

print("Waiting for connection response...")

try:
    ClientMultiSocket.connect((HOST, PORT))
except socket.error as err:
    print(str(err))

while True:
    msg = input("=> ")
    ClientMultiSocket.send(str.encode(msg))
    res = ClientMultiSocket.recv(1024)
    print(res.decode())

    if msg == 'exit':
        ClientMultiSocket.close()
        print("Socket closed...")
        break

