#pragma once
#include "Node.h"
template <class T>

class LinkedList
{
	Node<T>* head;
	Node<T>* tail;
	int count;

public:
	LinkedList()
	{
		tail = head = NULL;
		count = 0;
	}



	LinkedList(const LinkedList<T>& l)
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

			tail = temp2;
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

	void append(const T& val)
	{
		Node<T>* temp = new Node<T>(val);
		if(count == 0)
		{
			head = tail = temp;
			count++;
		}  

		else
		{
			tail->set_next(temp);
			tail = temp;
			count++;
		}

	}

	bool Insert(int ind , const T&val)
	{
		if(ind >= count)
			return false;

		Node<T>* temp =new Node<T>(val);
		Node<T>* ptr ;
		ptr = head;

		if(ind == 0)
		{
			temp->set_next(head);
			head = temp;
			count++;
		}

		else
		{

			for(int i=0;i<ind-1 ; i++)
			{
				ptr = ptr->next; 
			}

			temp ->set_next(ptr->get_next());
			ptr->set_next(temp);
			count++;
		}

		return true;
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

		while(ptr->get_next() != NULL)
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

	T* ToArr(int n)
	{
		n=(n<0?0:n);
		n=(n>count?count:n);
		T* arr = new T[n];
		Node<T>* temp = head;
		int m = 0;
		while(temp && m < n)
		{
			arr[m] = temp->get_data();
			temp= temp->get_next();
			m++;
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

	
	~LinkedList()
	{
		clear();
	
	}
	




};

