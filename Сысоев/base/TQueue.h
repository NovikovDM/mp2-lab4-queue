#pragma once
#ifndef __TQueue_H__
#define __TQueue_H__

const int MaxQueueSize = 100;

template <class T>
class TQueue
{
	T *pMem;
	int size;
	int top;
public:
	TQueue(int _size)
	{
		if ((_size < 1) || (_size > MaxQueueSize))
			throw "Error";
		size = _size;
		top = -1;
		pMem = new T[size];
	}
	~TQueue()
	{
		delete[] pMem;
	}
	void Push(T elem);                             
	T Pop();                                       
	bool IsEmpty() { return top == -1; }           
	bool IsFull() { return top == size - 1; }      
	T GetTop() { return pMem[0]; }                
	int GetLenght() { return top + 1; }
};

template <class T>
void TQueue<T>::Push(T elem)
{
	if (IsFull())
		throw "Is full";
	top++;
	pMem[top] = elem;
}

template <class T>
T TQueue<T>::Pop()
{
	if (IsEmpty())
		throw "Is empty";
	T Top = pMem[0];
	for (int i = 0; i < top; i++)
	{
		pMem[i] = pMem[i + 1];
	}
	top--;
	return Top;
}

#endif
