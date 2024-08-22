#include <thread>
#include <iostream>
#include <mutex>
#include <vector>
#include <random>

using namespace std;

mutex values_mutex;
mutex cout_mutex;
vector<int> values;

int randGen(const int& min, const int& max) {
	static thread_local mt19937

		generator(hash<thread::id>() (this_thread::get_id()));
	uniform_int_distribution<int> distribution(min, max);
	return distribution(generator);
}


void threadFnc(int tid) {
	cout_mutex.lock();
	cout << "Starting thread" << tid << ".\n";
	cout_mutex.unlock();

    values_mutex.lock();
    int val=values[0];
    values_mutex.unlock();

    int rval = randGen(0, 10);
val += rval;

	cout_mutex.lock();
	cout << "Thread" << tid << " adding" << rval << ". New value: " << val
		<<"." << endl;

	cout_mutex.unlock();

	values_mutex.lock();
	values.push_back(val);
	values_mutex.unlock();
}

int main(){
    values.push_back(42);
    thread tr1(threadFnc, 1);
	thread tr2(threadFnc, 2);
	thread tr3(threadFnc, 3);
	thread tr4(threadFnc, 4);

	tr1.join();
	tr2.join();
	tr3.join();
	tr4.join();

    cout << "Input: " << values[0] << ", Result 1:" << values[1] << ", Result 2:" << values[2] << ", Result 3:" << values[3] << ", Result 4:" << values[4] << endl;

	return 1;
}