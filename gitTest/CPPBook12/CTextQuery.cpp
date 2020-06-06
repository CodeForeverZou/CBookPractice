#include "CTextQuery.h"

extern void runQueries(ifstream &inFile);

void runQueries(ifstream &inFile) {

	TextQuery tx(inFile);
	cout << "请输入你想查的单词：" << endl;
	string word;
	while (true)
	{
		if (!(cin >> word) || word == "q") break;
		// 使用重载打印函数 print
		print(cout, tx.query(word));
	} 
	cout << "结束";
}

void process(ifstream &iFile) {
	map<string, set<int>> dic;
	string text, word;
	int countLine = 0;
	set<int> tmpSet;
	vector<string> fullText;
	while (getline(iFile, text))
	{
		istringstream line(text);
		fullText.push_back(text);
		countLine++;
		while (line >> word)
		{
			if (dic.find(word) == dic.end()) {
				tmpSet = { countLine };
				dic[word] = tmpSet;
			}
			else
			{
				dic[word].insert(countLine);
			}
		}
	}
	for (auto k : dic)
	{
		cout << k.first << " ";
		for (auto v : k.second) {
			cout << v << " ";
		}
		cout << endl;
	}
}
//ifstream inFile("stroy.txt");
//process(inFile);