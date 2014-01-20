/*
О спящем парикмахере
В тихом городке есть парикмахерская с двумя дверями и несколькими креслами. Посетители
входят через одну дверь и выходят через другую. Салон парикмахерской мал, и ходить по нему
может только парикмахер и один посетитель. Парикмахер всю жизнь обслуживает посетителей.
Когда в салоне никого нет, он спит в своем кресле. Когда посетитель приходит и видит спящего
парикмахера, он будит его, садится в кресло и спит, пока тот занят стрижкой. Если парикмахер
занят, когда приходит посетитель, тот садится в одно из свободных кресел и засыпает. После
стрижки парикмахер открывает посетителю выходную дверь и закрывает её за ним. Если есть
ожидающие посетители, парикмахер будит одного из них и ждет, пока тот сядет в кресло
парикмахера. Если никого нет, он снова идет спать до прихода следующего посетителя.
*/


#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <vector>

using namespace std;

queue<int> visitors;
mutex m;
condition_variable c_v;
bool all_cut = false;
bool visitor_came = false;

void vFunc() {
	int i = 0;
	while(i < 10) {
		this_thread::sleep_for(chrono::milliseconds(1));
		unique_lock<mutex> lock(m);
		cout << "came visitor "<< i  << endl;
		visitors.push(i);
		i++;
		visitor_came = true;
		c_v.notify_one();
	}
	all_cut = true;
	c_v.notify_one();
}

void sFunc() {
	
	unique_lock<mutex> lock(m);
	while(!all_cut) {
		while(!visitor_came) {
			c_v.wait(lock);
			//cout<<"Ready"<<endl;
		}
		while(!visitors.empty()) {
			cout << "visitor " << visitors.front() << " cut\n";
			this_thread::sleep_for(chrono::seconds(5));
			visitors.pop();
		}
		visitor_came = false;
	}
}

int main() {
	thread stylist(sFunc);
	thread visitor(vFunc);
   	stylist.join();
	visitor.join();
	return 0;
}
