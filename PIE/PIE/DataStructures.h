#pragma once

namespace DataStructures
{
	template <class T>
	class Stack
	{
	public:
		Stack() : h(nullptr), t(nullptr), size(0) {}
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
			size++;
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

			size--;
			return data;
		}

		T Peek()
		{
			return t->data;
		}

		bool IsEmpty()
		{
			return h ? false : true;
		}

		int Size()
		{
			return size;
		}

	private:
		template <class T>
		struct Node
		{
			Node* r;
			Node* l;
			T data;
		};

		Node<T>* h;
		Node<T>* t;
		int size;
	};

	template <class T>
	class Queue
	{
	public:
		Queue() : h(nullptr), t(nullptr), size(0) {}
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
			size++;
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

			size--;
			return data;
		}

		T Peek()
		{
			return h->data;
		}

		bool IsEmpty()
		{
			return h ? false : true;
		}

	private:
		template <class T>
		struct Node
		{
			Node* r;
			Node* l;
			T data;
		};

		Node<T>* h;
		Node<T>* t;
		int size;
	};

	// It doesn't do delete and dynamic resize for simplicity
	template<class K, class V>
	class Hash
	{
	public:
		Hash() : size(100)
		{
			hashItems = new HashItem<K, V>*[size]();
		}
		virtual ~Hash()
		{
			delete[] hashItems;
		}

		void Insert(K key, V value)
		{
			HashItem<K, V>* newHashItem = new HashItem<K, V>();
			newHashItem->key = key;
			newHashItem->value = value;
			newHashItem->next = nullptr;

			int index = HashFunction(key) % size;
			HashItem<K, V>* hashItem = hashItems[index];
			if (hashItem)
			{
				_InsertInEnd(hashItem, newHashItem);
			}
			else
			{
				hashItems[index] = newHashItem;
			}

		}

		bool Find(K key, V* pV)
		{
			int index = HashFunction(key) % size;
			HashItem<K, V>* hashItem = hashItems[index];
			if (hashItem)
			{
				*pV = hashItem->value;
				return true;
			}
			else
			{
				return false;
			}
		}

	private:
		template <class K, class V>
		struct HashItem
		{
			K key;
			V value;
			HashItem* next;
		};

		int HashFunction(K key)
		{
			int converted = (int)key;
			return converted % size;
		}
		void _InsertInEnd(HashItem<K, V>* h, HashItem<K, V>* toInsert)
		{
			while (h->next)
			{
				h = h->next;
			}

			h->next = toInsert;
		}

		int size;
		HashItem<K,V>** hashItems;
	};
}
