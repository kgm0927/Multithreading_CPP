#include <iostream>
#include <future>

using namespace std;

bool is_prime(int x){
    cout<<"Calculating prime ..."<<endl;
    for (int i = 2; i < x; ++i)
    {
        if(x%i==0){
            return false;
        }
    }
    return true;
}

int main(){
    future<bool> pFuture=std::async(is_prime,343321);
    cout<<"Checking whether 343321 is a prime number. \n";

    // wait for future object to be ready.

    bool result=pFuture.get();
    if (result)
    {
        cout<<"Prime found."<<endl;
    }else
    {
        cout<<"No prime found."<<endl;
    }

    return 0;
    
    
}