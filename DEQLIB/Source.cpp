#include <iostream>
#include "myDeque.cpp"

int main() {
	DEQ <int> d;
	//d.push_back(10);
	/*for (int i = 0; i < 100; ++i)
		d.push_back(i);*/
	for(int i = 0; i < 10; ++i)
		d.push_front(i);
	for (int i = 0; i < 20; ++i)
		d.push_back(i);
	//for (int i = 0; i < 110; ++i)
		//d.pop_back();
	d.push_back(1);
	//d.pop_back();
	//for (int i = 0; i < d.size(); ++i) {
	//	std::cout << d[i] << std::endl;
	//}
	//std::cout << '\n';
	for (auto it = d.begin(); it != d.end(); ++it) {
		std::cout << *it << std::endl;
	}
	std::cout << std::endl;
	std::cout << *d.begin() << std::endl;
	std::cout << *(--d.end()) << std::endl;
}
