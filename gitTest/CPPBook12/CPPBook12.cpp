// CPPBook12.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <fstream>
using namespace std;
extern void test();
extern void runQueries(ifstream &inFile);

int main()
{
	//test();

	ifstream inFile("stroy.txt");
	runQueries(inFile);


	/*vector<int> vInt;
	set<int> sInt;*/
	//copy(vInt.begin(), vInt.end(), sInt.begin()); 错
	//sInt.insert(vInt.begin(),vInt.end());
	//cout << sInt.erase(15);

	return 0;
	
}

