#pragma once
#include<iostream>
using namespace std;

template<class T>
class MyStack
{
public:
	MyStack();
	~MyStack();
	void push_stack(const T& val);
	bool pop_stack();
	bool empty();
	T stack_top();
	int stack_capacity();
private:
	bool is_capacity();
	T* p;
	int len;
	int capacity;
};

template<class T>
MyStack<T>::MyStack()
{
	len = 0;
	capacity = 0;
	p =nullptr;
}

template<class T>
MyStack<T>::~MyStack()
{
	if (p)
	{
		delete[] p;
		p = nullptr;
	}
}

template<class T>
void MyStack<T>::push_stack(const T& val)
{
	if (is_capacity())
	{
		capacity = ((int)(capacity * 1.5) == capacity) ? capacity + 1 : (int)capacity * 1.5;
		T* pnew = new T[capacity];
		if (p)
			memcpy(pnew, p, sizeof(T) * capacity);
		p = pnew;
	}
	p[len++] = val;
}

template<class T>
bool MyStack<T>::pop_stack()
{
	if (len > 0)
	{
		p[len--] = { 0 };
		return true;
	}
	exit(-1);
}

template<class T>
bool MyStack<T>::empty()
{
	return len == 0;
}

template<class T>
T MyStack<T>::stack_top()
{
	return p[len - 1];
}

template<class T>
int MyStack<T>::stack_capacity()
{
	return this->capacity;
}

template<class T>
bool MyStack<T>::is_capacity()
{
	return (len >= capacity);
}

