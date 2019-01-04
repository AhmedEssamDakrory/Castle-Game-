#pragma once
#include <iostream>
using namespace std;

template <class T>
class Node{

	T data;
	Node<T>* next;

public:
	Node(const T& d)
	{
		set_data(d);
		set_next(NULL);
	}


	void set_next(Node<T>* n)
	{
		next = n;
	}

	void set_data(const T& d)
	{
		data = d;
	}

	Node<T>* get_next() 
	{
		return next;
	}

	T get_data()
	{
		return data;
	}
};