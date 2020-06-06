#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include <string>
using namespace std;

class StrBlodPtr;

class StrBlod
{
public:
	friend class StrBlodPtr;
	StrBlodPtr begin();
	StrBlodPtr end();
	/*StrBlodPtr begin() { return StrBlodPtr(*this); }
	StrBlodPtr end() {
		auto ret = StrBlodPtr(*this, data->size());
		return ret;
	}*/
	// ���캯��
	typedef vector<string>::size_type size_type;

	StrBlod();
	StrBlod(initializer_list<string> il);
	~StrBlod();

	size_type size() const { return data->size(); }
	bool empty() const { return data->empty(); }

	// add delete
	void push_back(const string &t) { data->push_back(t); }
	void pop_back();

	string& front();
	string& back();

private:
	shared_ptr<vector<string>> data;
	void check(size_type i, const string &msg) const;
};

StrBlod::StrBlod() :data(make_shared<vector<string>>())
{
}
StrBlod::StrBlod(initializer_list<string> il) : data(make_shared<vector<string>>(il))
{
}
StrBlod::~StrBlod()
{
}


void StrBlod::pop_back()
{
	check(0, "pop_back on empty");
	data->pop_back();
}

string & StrBlod::front()
{
	// TODO: �ڴ˴����� return ���
	check(0, "front on empty");
	return data->front();
}

string & StrBlod::back()
{
	// TODO: �ڴ˴����� return ���
	check(0, "back on empyt");
	return data->back();
}

void StrBlod::check(size_type i, const string & msg) const
{
	if (i >= data->size())
	{
		throw out_of_range(msg);
	}
}

// ================weak_ptr ��������ָ������������� ====================
class StrBlodPtr
{
public:
	StrBlodPtr() :curr(0) {}
	//StrBlodPtr::StrBlodPtr();
	StrBlodPtr(StrBlod &a, size_t sz = 0) :wptr(a.data), curr(sz) {}
	~StrBlodPtr();

	string& deref() const;
	StrBlodPtr& incr();

private:
	size_t curr;
	weak_ptr<vector<string>> wptr;
	shared_ptr<vector<string>> check(size_t, const string&) const;
};


StrBlodPtr::~StrBlodPtr()
{
}

string & StrBlodPtr::deref() const
{
	// TODO: �ڴ˴����� return ���
	auto p = check(curr, "������ʧ��");
	return (*p)[curr];
}

StrBlodPtr & StrBlodPtr::incr()
{
	// TODO: �ڴ˴����� return ���
	check(curr, "�Ѿ�ָ������β�����ܵ�����");
	++curr;
	return *this;
}

shared_ptr<vector<string>> StrBlodPtr::check(size_t i, const string & msg) const
{
	auto ret = wptr.lock();		// vector����ô�� �ڷ���һ����ָ���shareptr
	if (!ret)
		throw runtime_error("unbound StrBordptr");
	if (i >= ret->size())
		throw out_of_range(msg);
	return ret;
}

// ���ﶨ�� begin��end������ ====================================
StrBlodPtr StrBlod::begin() { return StrBlodPtr(*this); }
StrBlodPtr StrBlod::end() {
	auto ret = StrBlodPtr(*this, data->size());
	return ret;
}
