#include <thread>
#include <string>
#include <utility>

// 스레드 이동하기
//

void worker(int n,std::string t){
    // Business logic.
}


int main(){
    std::string s="Test";
    std::thread t0(worker,1,s);

    std::thread t1(std::move(t0));
    t1.join();
    return 0;
}