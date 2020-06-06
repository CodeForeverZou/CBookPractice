#include "StrBlod.h"

extern void test();
void test() {
	//std::cout << "Hello World!\n";
	StrBlod b1;
	{
		StrBlod b2 = { "a", "an" };
		b1 = b2;							// b1、b2大小内容一样！！！
		b2.push_back("the");
		// string s = b2.front();			// 没有string 头文件，cout不了
		cout << b1.size() << " " << b2.size() << " " << b1.back() << endl;
	}
	StrBlodPtr wp = b1.begin();

	cout << wp.deref() << endl;
	wp.incr();
	cout << wp.deref();
}