#include "StrBlod.h"

extern void test();
void test() {
	//std::cout << "Hello World!\n";
	StrBlod b1;
	{
		StrBlod b2 = { "a", "an" };
		b1 = b2;							// b1��b2��С����һ��������
		b2.push_back("the");
		// string s = b2.front();			// û��string ͷ�ļ���cout����
		cout << b1.size() << " " << b2.size() << " " << b1.back() << endl;
	}
	StrBlodPtr wp = b1.begin();

	cout << wp.deref() << endl;
	wp.incr();
	cout << wp.deref();
}