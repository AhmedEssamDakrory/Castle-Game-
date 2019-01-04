#pragma once
#include "Node.h"

template <class T>
class queue{

	Node<T>* head;
	Node<T>* rear;

public:

	queue()
	{
		head = rear = NULL;
	}

	void enqueue(const T& val)
	{
		Node<T>* temp = new Node<T>(val);
		if(head == NULL)
			head = rear = temp;
		else
		{
			rear->set_next(temp);
			rear = temp ;
		}

	}

	bool dequeue()
	{
		if(head == NULL)
			return false ;

		else if(head->get_next() == NULL)
		{
			Node<T>* del = head;
			head = head->get_next();
			rear->set_next(NULL);
			del->set_next(NULL);
			delete del;

		}

		else
		{
			Node<T>* del = head;
	        head = head->get_next();
		    del->set_next(NULL);
		    delete del;
		}

		return true;

	}

	T queuefront()
	{
		return (head->get_data());

	}

	~queue()
	{

		bool f = true;

		while(f)
		{

			f = dequeue();

		}
	}


};