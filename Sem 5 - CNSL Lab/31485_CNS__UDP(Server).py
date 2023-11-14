import socket

def receive_file(filename, sender_ip, sender_port):
    # Create a UDP socket
    udp_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    udp_socket.bind(('0.0.0.0', sender_port))

    try:
        with open(filename, 'wb') as file:
            while True:
                data, addr = udp_socket.recvfrom(1024)
                if not data:
                    break
                file.write(data)
        print(f"File '{filename}' received successfully. from {sender_ip}")
    except Exception as e:
        print(f"An error occurred: {e}")
    finally:
        udp_socket.close()

if __name__ == "__main__":
    sender_ip = 'sender_machine_ip'  # Replace with the actual IP of the sender machine
    sender_port = 12345  # Use the same port as the sender
    file_to_receive = 'received_audio.mp3'  # Name for the received audio file

    receive_file(file_to_receive, sender_ip, sender_port)



