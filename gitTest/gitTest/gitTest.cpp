#include <sstream>
#include <iostream>
using namespace std;

#pragma pack(4)

class Parent {

public:

	Parent() = default;

	virtual ~Parent() = default;



	virtual void run() {

		std::cout << "Parent:run" << std::endl;

	}

private:

	char a;

};



class Child : public Parent {

public:

	Child() = default;

	~Child() = default;



public:

	virtual void run() {

		std::cout << "Child:run" << std::endl;

	}

private:

	int b;

};



int main(int argc, char** argv) {

	Parent* a = new Child;

	Parent* b = new Parent;

	Child* c = new Child;





	a->run();

	b->run();

	c->run();
	cout << sizeof(Parent);

	delete c;

	delete b;

	delete a;

	return 0;

}