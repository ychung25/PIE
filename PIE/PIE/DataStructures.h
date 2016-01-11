#pragma once

namespace DataStructures
{
	template <class T>
	struct Node
	{
		Node* r;
		Node* l;
		T data;
	};

	template <class T>
	class Stack
	{
	public:
		Stack() : h(nullptr), t(nullptr) {}
		virtual ~Stack() {}

		void Push(T data)
		{
			Node<T>* n = new Node<T>();
			n->data = data;
			n->r = 0;
			n->l = 0;

			if (!h)
			{
				h = n;
				t = n;
			}
			else
			{
				t->r = n;
				n->l = t;
				t = n;
			}
		}

		T Pop()
		{
			if (!h)
				return 0;

			T data = t->data;
			Node<T>* prev = t->l;
			if(prev)
				prev->r = nullptr;
			delete t;
			t = prev;

			if (!prev)
				h = nullptr;

			return data;
		}

		bool IsEmpty()
		{
			return h ? false : true;
		}

	private:
		Node<T>* h;
		Node<T>* t;
	};

	template <class T>
	class Queue
	{
	public:
		Queue() : h(nullptr), t(nullptr) {}
		virtual ~Queue() {}

		void Enqueue(T data)
		{
			Node<T>* n = new Node<T>();
			n->l = nullptr;
			n->r = nullptr;
			n->data = data;

			if (!h)
			{
				h = n;
				t = n;
			}
			else
			{
				t->r = n;
				n->l = t;
				t = n;
			}
		}

		T Dequeue()
		{
			if (!h)
				return 0;

			T data = h->data;
			Node<T>* afterHead = h->r;
			if(afterHead)
				afterHead->l = nullptr;
			delete h;
			
			h = afterHead;

			if (!afterHead)
				t = nullptr;

			return data;
		}

		bool IsEmpty()
		{
			return h ? false : true;
		}

	private:
		Node<T>* h;
		Node<T>* t;
	};
}
