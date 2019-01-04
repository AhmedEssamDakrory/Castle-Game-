#pragma once
#include "Node.h"
template <class T>

class priorityList
{
	Node<T>* head;
	Node<T>* tail;
	int count;

public:
	priorityList()
	{
		tail = head = NULL;
		count = 0;
	}

	
	priorityList(const priorityList<T>& l)
	{
	count = l.count;
	if(l.head == NULL)
	head = tail = NULL;
	else
	{
	head = new Node<T>(l.head->get_data());
	Node<T>* temp1 = l.head->get_next();
	Node<T>* temp2 = head;
	while(temp1)
	{
	Node<T>* ptr = new Node<T>(temp1->get_data());
	temp2->set_next(ptr);
	temp2 = temp2->get_next();
	temp1 = temp1->get_next();
	}

	tail = temp2 ;
	}
	}
	


	T getEntry(int ind)
	{
		if(ind >= count)
			return tail->get_data();

		Node<T>* temp = head;
		for(int i=0;i<ind;i++)
			temp = temp->get_next();

		return temp->get_data(); 

	}

	bool Isempty()
	{
		return (count == 0;)
	}

	int size()
	{
		return count;
	}

	void add(const T& val)
	{
		Node<T>* ptr = new Node<T>(val);

		if(count == 0)
		{
			head = tail = ptr;
		}

		else if(val <= tail->get_data())
		{
			tail->set_next(ptr);
			tail = ptr;
		}

		else if(val > head->get_data() )
		{
			ptr->set_next(head);
			head = ptr;

		}

		else
		{
			Node<T>* temp = head;

			while(temp->get_next())
			{
				if(val > temp->get_next()->get_data())
				{
					ptr->set_next(temp->get_next());
					temp->set_next(ptr);
					break;
				}

				temp = temp->get_next();
			}
		}

		count++;
	}

	bool remove(const T& val)
	{
		Node<T>* ptr ; 
		ptr = head;
		if(!head) return false;
		if(val == head->get_data())
		{
			if(head->get_next() == NULL)
				tail =NULL;
			head = ptr->get_next();
			ptr->set_next(NULL);
			delete ptr;
			ptr = NULL;
			count--;
			return true;
		}

		while(ptr->get_next())
		{

			if(val == ptr->get_next()->get_data() )
			{
				Node<T>* del = ptr->get_next();
				ptr->set_next(ptr->get_next()->get_next());
				if(del == tail)
					tail = ptr;
				del->set_next(NULL);
				delete del;
				del = NULL;
				count--;
				return true;

			}

			ptr = ptr->get_next();

		}

		return false;

	}

	T* ToArr(int m)
	{
		m=(m<0?0:m);
		m=(m>count?count:m);
		T* arr = new T[m];
		Node<T>* temp = head;
		int n = 0;
		while(temp && n<m)
		{
			arr[n] = temp->get_data();
			temp= temp->get_next();
			n++;
		}
		return arr;
	}

	
	void clear()
	{
		tail = NULL ;

		while(head)
		{
			Node<T>* del = head;
			head= head->get_next();
			del->set_next(NULL);
			delete del;
		}

	}

	~priorityList()
	{
		clear();
	}
	


};
