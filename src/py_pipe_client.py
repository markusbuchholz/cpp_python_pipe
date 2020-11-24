#
# Hello World client in Python
# Connects REQ socket to tcp://localhost:5555
# Sends "Hello" to server, expects "World" back
#
# INSTALLED VIA EASY_INSTALL
# pip install zmq
# https://opensource.com/article/20/3/zeromq-c-python
import zmq
import time

context = zmq.Context()

# Socket to talk to server
print ("Connecting to hello world server...")
socket = context.socket(zmq.REQ)
socket.connect("tcp://localhost:5555")

# Do 10 requests, waiting each time for a response
for request in range(10):
    print ("Sending request ", request, "...")
    socket.send_string(str(29) +"/" + str(30))
    
    #a = [10,20,30,40] #numpy.random.rand(array_size, array_size)
    #socket.send_pyobj(a)

    # Get the reply.
    message = socket.recv()
    print ("Received reply ", request, "[", message, "]")