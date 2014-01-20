// пример работы с mutex

#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

using namespace std;

mutex m_mutex;

void increment(int * pk){
   	lock_guard<mutex> guard(m_mutex);
    cout << "-----------------\nbefore inc = " << *pk << endl;
    for (int i = 0; i < 100000; ++i) {
     	(*pk)++;
     } 
    cout << "after inc = "<< *pk << endl;
}

void decrement(int * pk){
	lock_guard<mutex> guard(m_mutex);
    cout << "-----------------\nbefore dec = " << *pk << endl;
    for (int i = 0; i < 100000; ++i)
     {
     	(*pk)--;
     } 
    cout << "after dec = "<< *pk << endl;
}

int main() {
	int k = 9;
	
	vector<std::thread> threads;
	for(int i = 0; i < 100; ++i)
        threads.push_back(thread(increment, &k));
	for(int i = 0; i < 100; ++i)
        threads.push_back(thread(decrement, &k));
   	for(auto& thread : threads) 
		thread.join(); 
	
	return 0;
}	
