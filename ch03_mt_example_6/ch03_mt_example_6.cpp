#include "poco/Thread.h"
#include <iostream>

using namespace Poco;


class HelloRunnable:public Runnable{
    virtual void run(){
        std::cout<<"Hello, world"<<std::endl;
    }
};

int main(int argc,char** argv){
    HelloRunnable runnable;
    Thread thread;

    thread.start(runnable);
    thread.join();
    return 0;
}