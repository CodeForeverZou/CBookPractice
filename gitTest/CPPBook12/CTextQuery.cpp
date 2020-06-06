#include "CTextQuery.h"

extern void runQueries(ifstream &inFile);

void runQueries(ifstream &inFile) {

	TextQuery tx(inFile);
	cout << "�����������ĵ��ʣ�" << endl;
	string word;
	while (true)
	{
		if (!(cin >> word) || word == "q") break;
		// ʹ�����ش�ӡ���� print
		print(cout, tx.query(word));
	} 
	cout << "����";
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