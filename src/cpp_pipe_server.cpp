//
//  Hello World server in C++
//  Binds REP socket to tcp://*:5555
//  Expects "Hello" from client, replies with "World"
//

// TO GET IT TO WORK:
// Copy the zm.hpp from https://github.com/zeromq/cppzmq into the include folder of zmq (3.2.4 at the time)
// VS needs to specify .lib files of platform! e.g. 

// g++ cpp_pipe_server.cpp -lzmq -o server

//https://github.com/zeromq/zmqpp/blob/develop/examples/simple_server.cpp

/*
markus@markus:~/sw_dev/cpp_dev/cpp_python_pipe/src$ pip3 install zmq

*/


#include <zmq.hpp>
#include <string>
#include <iostream>
#ifndef _WIN32
#include <unistd.h>
#else
#include <windows.h>
#endif

int main () {
    //  Prepare our context and socket
    zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_REP);
    socket.bind ("tcp://*:5555");

    while (true) {
        zmq::message_t request;
        //zmq::message data;

        //  Wait for next request from client
        socket.recv (&request);
        std::cout << "Received Hello :::" << std::endl;
        std::string replyMessage = std::string(static_cast<char *>(request.data()), request.size());
        std::cout << "Received from client: " + replyMessage << std::endl;

        //  Do some 'work'
#ifndef _WIN32
    	sleep(0.1);
#else
	Sleep (0.1);
#endif

        //  Send reply back to client
        zmq::message_t reply (5);
        memcpy ((void *) reply.data (), "World", 5);
        socket.send (reply);
    }
    return 0;
}