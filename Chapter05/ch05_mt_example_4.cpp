#include <iostream>
#include <chrono>
#include <thread>

using namespace std::chrono_literals;

// 슬립(sleep)

typedef std::chrono::time_point<std::chrono::high_resolution_clock> timepoint;

int main(){
    std::cout<<"Starting sleep.\n";

    timepoint start=std::chrono::high_resolution_clock::now(); //시작

    std::this_thread::sleep_for(2s);

    timepoint end=std::chrono::high_resolution_clock::now(); // 끝

    std::chrono::duration<double,std::milli> elapsed=end-start;

    std::cout<<"slept for:"<<elapsed.count()<<"ms\n";


}