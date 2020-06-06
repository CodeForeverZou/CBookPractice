// CPPBook11.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
using namespace std;

// 文本转换： where r y
map<string, string> buildMap(ifstream &iFile) {
	map<string, string> m;
	string key, value;
	while (iFile >> key && getline(iFile, value))	// 读取很有技巧啊
	{
		m[key] = value.substr(1);
	}
	return m;
}

void transform(ifstream &iFile, ifstream &oFile) {
	map<string, string> textMap;
	textMap = buildMap(iFile);
	string text, res, word;
	while (getline(oFile, text))
	{	
		res = "";
		istringstream ss(text);
		bool firstWord = true;
		while (ss >> word)
		{
			if (firstWord) {
				firstWord = false;
			}
			else
			{
				res += " ";
			}
			auto iter = textMap.find(word);
			if (iter != textMap.cend()) {
				res += iter->second;
			}
			else
			{
				res += word;
			}
		}

		std::cout << res << endl;
	}
}

int main()
{
	ifstream iFile("inputfile.txt"), OFile("outputfile.txt");
	transform(iFile, OFile);

	vector<int> nums = { 1 };
	nums.pop_back();

	
}

