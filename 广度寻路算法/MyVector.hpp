#pragma once
#include <iostream>
using namespace std;
template<class T>
class MyVector
{
private:
	T* arr;
	size_t len;
	size_t capacity;
	bool _isCapacity();
public:
	MyVector();
	~MyVector();
	void push_front(const T& data);
	void push_back(const T& data);
	void pop_front();
	void pop_back();
	void pop_pos(size_t pos);//下标pos
	void travel();
	size_t get_capacity();
	size_t size();
	T operator[](const int i);
	void clear();
};

template<class T>
inline bool MyVector<T>::_isCapacity()
{
	if (len >= capacity)//需要申请
	{
		capacity = ((int)(capacity * 1.5) == capacity) ? (capacity + 1) : (int)(capacity * 1.5);
		return true;
	}
	return false;
}
template<class T>
MyVector<T>::MyVector()
{
	arr = NULL;
	capacity = len = 0;
}

template<class T>
MyVector<T>::~MyVector()
{
	if (arr != NULL)
	{
		delete[] arr;
		arr = NULL;
		len = 0;
		capacity = 0;
	}
}

template<class T>
void MyVector<T>::push_front(const T& data)
{
	if (_isCapacity())
	{
		auto pnew = new T[len + 1];
		if (arr != NULL)
			memcpy(pnew + 1, arr, sizeof(T) * len);
		if (arr != NULL)
			delete[] arr;
		arr = pnew;
	}
	arr[0] = data;
	len++;
}

template<class T>
void MyVector<T>::push_back(const T& data)
{
	if (_isCapacity())
	{
		auto pnew = new T[capacity];
		if (arr != NULL)
			memcpy(pnew, arr, sizeof(T) * len);
		if (arr != NULL)
			delete[] arr;
		arr = pnew;
	}
	arr[len++] = data;
}

template<class T>
void MyVector<T>::pop_front()
{
	if (arr == NULL)
		return;
	if (len == 1)
	{
		delete[] arr;
		arr = NULL;
		len--;
		return;
	}
	auto pnew = new T[len - 1];
	memcpy(pnew, arr + 1, sizeof(T) * (len - 1));
	delete[] arr;
	arr = pnew;
	len--;
}

template<class T>
void MyVector<T>::pop_back()
{
	if (NULL == arr)
		return;
	if (len == 1)
	{
		delete[] arr;
		arr = NULL;
		len--;
		return;
	}
	auto pnew = new T[len - 1];
	memcpy(pnew, arr, sizeof(T) * (len - 1));
	delete[] arr;
	arr = pnew;
	len--;
}

template<class T>
void MyVector<T>::pop_pos(size_t pos)
{
	if (pos < 0 || pos >= len)
		return;
	if (pos == 0)
	{
		pop_front();
		return;
	}
	if (pos == len - 1)
	{
		pop_back();
		return;
	}
	auto pnew = new T[len - 1];
	memcpy(pnew, arr, sizeof(T) * pos);
	memcpy(pnew + pos, arr + pos + 1, sizeof(T) * (len - pos - 1));
	delete[] arr;
	arr = pnew;
	len--;
}

template<class T>
void MyVector<T>::travel()
{
	cout << "SeqList:";
	for (size_t i = 0; i < len; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}

template<class T>
size_t MyVector<T>::get_capacity()
{
	return this->capacity;
}

template<class T>
size_t MyVector<T>::size()
{
	return len;
}

template<class T>
T MyVector<T>::operator[](const int i)
{
	return this->arr[i];
}

template<class T>
void MyVector<T>::clear()
{
	arr = nullptr;
	len = 0;
	capacity = 0;
}
