import xmlrpc.client
proxy = xmlrpc.client.ServerProxy('http://localhost:3000/')
while(True):
    c=int(input("1.FACTORIAL\n2.SQUARE\n3.EXIT\n"))
    if(c==1):
        a=int(input("ENTER THE NUMBER TO FIND FACTORIAL OF-"))
        print("factorial of ",a," is : %s" % str(proxy.factorial_rpc(a)))
    if(c==2):
        b=int(input("ENTER THE NUMBER TO FIND SQUARE OF-"))
        print("square of ", b," is : %s" % str(proxy.square_rpc(b)))
    if(c==3):
        break
    if(c>3 or c<0):
        print("ENTER CORRECT OPTION")