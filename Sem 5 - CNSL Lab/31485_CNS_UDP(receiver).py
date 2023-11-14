import socket

def send_file(filename, receiver_ip, receiver_port):
    # Create a UDP socket
    udp_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    try:
        with open(filename, 'rb') as file:
            data = file.read(1024)
            while data:
                udp_socket.sendto(data, (receiver_ip, receiver_port))
                data = file.read(1024)
        print(f"File '{filename}' sent successfully.")
    except FileNotFoundError:
        print(f"File '{filename}' not found.")
    finally:
        udp_socket.close()

if __name__ == "__main__":
    receiver_ip = '192.168.1.6'
    receiver_port = 12345
    file_to_send = '31478_test_audio.mp3'

    send_file(file_to_send, receiver_ip, receiver_port)

