#include "TimeWatch.hpp"

#include <iostream>
#include <thread>

int main(void) {

	wlib::TimeWatch watch("Hoge Table");

	bool is_continue = true;
	while(is_continue){

		watch.start();
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		watch.stamp("10 ms");
		std::this_thread::sleep_for(std::chrono::milliseconds(15));
		watch.stamp("more 15 ms");

		std::cout << "exit (y, else) ? ";
		std::string is_exit;
		std::cin >> is_exit;
		if (is_exit == "y") is_continue = false;

		watch.stop();

		std::cout << "CSV Headers ===" << std::endl;
		watch.printCSVHeader(std::cout);
		std::cout << std::endl << "CSV Data ===" << std::endl;
		watch.printCSVResult(std::cout);
		std::cout << std::endl << "Decorated ===" << std::endl;
		watch.printDecoratedResult(std::cout);

		std::cout << std::endl;
	}

	return 0;
}