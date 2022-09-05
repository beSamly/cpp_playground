#include "main.h"
#include <iostream>
#include <vector>

class MemberVar {
public:
	MemberVar() {

	};
};

class Test {
public:
	MemberVar* ptr = nullptr;
public:
	Test() {
		std::cout << "Normal constructor" << std::endl;
		ptr = new MemberVar();
	}

	void GetAddress() {
		std::cout << "Address is " << ptr << std::endl;
	}

	Test(Test& other) {
		std::cout << "LValue constructor" << std::endl;
		ptr = new MemberVar();
	}

	//Test(Test&& other) {
	//	std::cout << "RValue constructor" << std::endl;
	//}

	//void operator=(Test& other) {
	//	std::cout << "operator = constructor" << std::endl;
	//}
};



int main() {
	std::vector<Test> myVector;
	Test t1;
	Test t2 = t1;
	t1.GetAddress();
	t2.GetAddress();
	t1 = t2;
	t1.GetAddress();
	t2.GetAddress();

	return 0;
}