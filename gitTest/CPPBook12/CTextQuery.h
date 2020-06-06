#pragma once

#include <sstream>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <set>

using namespace std;
// 文本、单词处理程序
// 统计每个单词出现次数，以及该单词所在行号，打印该行句子
// 需要dic存单词，set存行号，vector存句子
// 有count、print方法、read方法


class QueryResult;

class TextQuery
{
public:
	TextQuery(ifstream&);
	~TextQuery();
	QueryResult query(string) const;
private:
	// set是share_ptr，句子vector是共享的
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
		sentence->push_back(line);	// 这里竟然用 ->

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
	// 必须要声明友元才能 访问private成员！！！
	friend ostream& print(ostream&, const QueryResult&);
	// 构造函数 ！！！
	QueryResult(string s, shared_ptr<set<int>> p, \
		shared_ptr<vector<string>> f) :word(s), lines(p), ss(f) {};
	~QueryResult();

private:
	// 结果：行号、单词、句子内容
	string word;
	shared_ptr<set<int>> lines;
	shared_ptr<vector<string>> ss;
};



QueryResult::~QueryResult()
{
}

// ====================================
QueryResult TextQuery::query(string word) const {
	// 如果没找到，返回nodata指针
	
	static shared_ptr<set<int>> nodata(new set<int>);
	auto loc = dic.find(word);
	if (loc == dic.end()) {
		return QueryResult(word, nodata, sentence);
	}
	else
	{	// 漏写一个->second ，真恐怖
		//cout << "query" << loc->second->size() << endl;
		return QueryResult(word, loc->second, sentence);
	}
	
}

ostream &print(ostream &os, const QueryResult &qr) {
	
	//cout << " print " << endl;
	os << qr.word << " occurs " << qr.lines->size() << " " << endl;
	for (auto num : *qr.lines)
	{	// 万万没想到 解引用(qr.ss->begin() + num)来得到vector内容
		os << "\t(line " << num  << ")"  << *(qr.ss->begin() + num - 1) << endl;

	}
	return os;
}

