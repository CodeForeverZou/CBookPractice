#pragma once

#include <sstream>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <set>

using namespace std;
// �ı������ʴ������
// ͳ��ÿ�����ʳ��ִ������Լ��õ��������кţ���ӡ���о���
// ��Ҫdic�浥�ʣ�set���кţ�vector�����
// ��count��print������read����


class QueryResult;

class TextQuery
{
public:
	TextQuery(ifstream&);
	~TextQuery();
	QueryResult query(string) const;
private:
	// set��share_ptr������vector�ǹ����
	shared_ptr<vector<string>> sentence;
	map<string, shared_ptr<set<int>>> dic;
};

TextQuery::TextQuery(ifstream& inFile): sentence(new vector<string>)
{
	string line, word;
	int countLine = 0;
	while (getline(inFile, line))
	{
		istringstream ss(line);
		countLine++;
		sentence->push_back(line);	// ���ﾹȻ�� ->

		while (ss >> word)
		{
			auto &lines = dic[word];
			if (!lines)
				lines.reset(new set<int>);
			lines->insert(countLine);
		}
	}
	cout << "init Text " << dic.size() << endl;
	/*for (auto v : dic)
	{
		cout << v.second->size() << endl;
	}*/
}

TextQuery::~TextQuery()
{
}

// ====================================
class QueryResult
{
public:
	// ����Ҫ������Ԫ���� ����private��Ա������
	friend ostream& print(ostream&, const QueryResult&);
	// ���캯�� ������
	QueryResult(string s, shared_ptr<set<int>> p, \
		shared_ptr<vector<string>> f) :word(s), lines(p), ss(f) {};
	~QueryResult();

private:
	// ������кš����ʡ���������
	string word;
	shared_ptr<set<int>> lines;
	shared_ptr<vector<string>> ss;
};



QueryResult::~QueryResult()
{
}

// ====================================
QueryResult TextQuery::query(string word) const {
	// ���û�ҵ�������nodataָ��
	
	static shared_ptr<set<int>> nodata(new set<int>);
	auto loc = dic.find(word);
	if (loc == dic.end()) {
		return QueryResult(word, nodata, sentence);
	}
	else
	{	// ©дһ��->second ����ֲ�
		//cout << "query" << loc->second->size() << endl;
		return QueryResult(word, loc->second, sentence);
	}
	
}

ostream &print(ostream &os, const QueryResult &qr) {
	
	//cout << " print " << endl;
	os << qr.word << " occurs " << qr.lines->size() << " " << endl;
	for (auto num : *qr.lines)
	{	// ����û�뵽 ������(qr.ss->begin() + num)���õ�vector����
		os << "\t(line " << num  << ")"  << *(qr.ss->begin() + num - 1) << endl;

	}
	return os;
}

