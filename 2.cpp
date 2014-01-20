/*
Поиск образца в файле
Взять любой большой текстовый файл. Необходимо найти в текстовом файле заданную
строку. Главный поток управления запускает N дочерних потоков, каждый из которых имеет
номер k и ищет образец в строке k­1, k­1 + N, k­1 + 2N и т.д. до конца файла.
*/

#include <iostream>
#include <fstream>
#include <thread>
#include <vector>
#include <cstring>

using namespace std;

void fs(char *ref, string target, int count) { 
	string line(ref, ref + count);
	//cout << line << endl;
	size_t found = line.find(target);
	if (found != std::string::npos) 
		cout << "found word <" << target << ">\n";
}

int main() {
	vector<string> lines;
	ifstream file("file.txt");
	string line, all = "";
	while(getline(file, line)) {
		all += line;
	}
	file.close();
	string target = "again";
	
	vector<thread> threads;
	for(int i = 0; i < all.length(); i += all.length()/100) 
		threads.push_back(thread(fs, &all[i], target, all.length()/100));
	for(auto& thread : threads) 
		thread.join(); 	
	/*  threads
		real	0m0.017s
		user	0m0.000s
		sys	0m0.012s
	*/
	// for(int i = 0; i < all.length(); i += all.length()/100) {
	// 	fs(&all[i], target, all.length()/100);
	// }
	/* 
		real	0m0.008s
		user	0m0.004s
		sys	0m0.000s
	*/
	return 0;
}
