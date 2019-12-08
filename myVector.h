#pragma once
#include <iostream>
#define EXTRA_SIZE 16
#define MAX_SIZE 153391689

using namespace std;

template <typename T>
class myVector
{
private:
	unsigned int myVector_size;
	unsigned int myVector_capacity;
	T* myVector_buffer;

public:

	/**** Итератор ****/
	class myIterator
	{
	public:
		using value_type = T;
		using reference = value_type&;
		using pointer = value_type*;
		using difference_type = ptrdiff_t;
		using iterator_category = random_access_iterator_tag;

	private:
		T* myIterator_current_value;
		T* myIterator_buffer;
		unsigned int myIterator_index;

	public:
		myIterator()
		{
			myIterator_current_value = nullptr;
			myIterator_buffer = nullptr;
			myIterator_index = 0;
		}

		myIterator(T* _value, T* _buffer, unsigned int _index)
		{
			myIterator_current_value = _value;
			myIterator_buffer = _buffer;
			myIterator_index = _index;
		}

		~myIterator()
		{
			myIterator_buffer = nullptr;
			myIterator_current_value = nullptr;
		}

		bool operator == (myIterator _iterator) const
		{
			return (myIterator_current_value == _iterator.myIterator_current_value) && (myIterator_index == _iterator.myIterator_index);
		}

		bool operator != (myIterator _iterator) const
		{
			return (myIterator_current_value != _iterator.myIterator_current_value) && (myIterator_index != _iterator.myIterator_index);
		}

		bool operator < (myIterator _iterator) const
		{
			return (myIterator_current_value < _iterator.myIterator_current_value) && (myIterator_index < _iterator.myIterator_index);
		}

		difference_type operator-(myIterator _iterator) const
		{
			return this->myIterator_current_value - _iterator.myIterator_current_value;
		}

		bool operator <= (myIterator _iterator) const
		{
			return (myIterator_current_value <= _iterator.myIterator_current_value) && (myIterator_index <= _iterator.myIterator_index);
		}

		bool operator > (myIterator _iterator) const
		{
			return (myIterator_current_value > _iterator.myIterator_current_value) && (myIterator_index > _iterator.myIterator_index);
		}

		bool operator >= (myIterator _iterator) const
		{
			return (myIterator_current_value >= _iterator.myIterator_current_value) && (myIterator_index >= _iterator.myIterator_index);
		}

		T& operator *()
		{
			return *myIterator_current_value;
		}

		myIterator& operator++()
		{
			myIterator_index++;
			myIterator_current_value = myIterator_buffer + myIterator_index;
			return *this;
		}

		myIterator operator++(int)
		{
			myIterator ret = *this;
			myIterator_index++;
			myIterator_current_value = myIterator_buffer + myIterator_index;
			return ret;
		}

		myIterator& operator--()
		{
			myIterator_index--;
			myIterator_current_value = myIterator_buffer + myIterator_index;
			return *this;
		}

		myIterator operator--(int)
		{
			myIterator ret = *this;
			myIterator_index--;
			myIterator_current_value = myIterator_buffer + myIterator_index;
			return ret;
		}

		myIterator& operator += (unsigned int _value)
		{
			myIterator_index += _value;
			myIterator_current_value = myIterator_buffer + myIterator_index;
			return *this;
		}

		myIterator& operator + (unsigned int _value)
		{
			myIterator_index += _value;
			myIterator_current_value = myIterator_buffer + myIterator_index;
			return *this;
		}

		myIterator& operator -= (unsigned int _value)
		{
			myIterator_index -= _value;
			myIterator_current_value = myIterator_buffer + myIterator_index;
			return *this;
		}

		myIterator& operator - (unsigned int _value)
		{
			myIterator_index -= _value;
			myIterator_current_value = myIterator_buffer + myIterator_index;
			return *this;
		}

		unsigned int get_index()
		{
			return myIterator_index;
		}
	};


	/**** Функции-члены ****/
	/****  Основные ****/

	myVector()//работает
	{
		myVector_size = 0;
		myVector_capacity = 0;
		myVector_buffer = NULL;
	}

	myVector(unsigned int _size)//работает
	{
		myVector_size = _size;
		myVector_capacity = _size + EXTRA_SIZE;
		myVector_buffer = new T[myVector_capacity];
	}

	myVector(unsigned int _size, T _value)//работает
	{
		myVector_size = _size;
		myVector_capacity = _size + EXTRA_SIZE;
		myVector_buffer = new T[myVector_capacity];
		for (unsigned int i = 0; i < myVector_capacity; i++)
		{
			myVector_buffer[i] = _value;
		}
	}

	myVector<T>& operator = (myVector<T>& _vector)//работает
	{
		delete[] myVector_buffer;
		myVector_size = _vector.myVector_size;
		myVector_capacity = _vector.myVector_capacity;

		myVector_buffer = new T[myVector_capacity];
		memcpy(myVector_buffer, _vector.myVector_buffer, (myVector_size * sizeof(T)));
		return *this;
	}

	void assign(unsigned int _size, T _value)//работает
	{
		if (_size > MAX_SIZE + EXTRA_SIZE)
		{
			return;
		}
			
		delete[] myVector_buffer;
		myVector_size = _size;
		myVector_capacity = _size + EXTRA_SIZE;

		myVector_buffer = new T[myVector_capacity];
		for (int i = 0; i < myVector_size; i++)
		{
			myVector_buffer[i] = _value;
		}
	}

	/**** Доступ к элементам ****/

	T& at(unsigned int _index)//работает
	{
		return myVector_buffer[_index];
	}

	T& operator[](unsigned int _index)//работает
	{

		return myVector_buffer[_index];
	}

	T& front()//работает
	{
		return myVector_buffer[0];
	}

	T& back()//работает
	{
		return myVector_buffer[myVector_size - 1];
	}

	/**** Итераторы ****/

	myIterator begin() const//работает
	{
		myIterator ret(&myVector_buffer[0], myVector_buffer, 0);
		return ret;
	}

	myIterator end() const//работает
	{
		myIterator ret(&myVector_buffer[myVector_size], myVector_buffer, myVector_size);
		return ret;
	}

	/**** Вместимость ****/

	bool empty()//работает
	{
		return (!myVector_size);
	}

	unsigned int size()//работает
	{
		return myVector_size;
	}

	unsigned int max_size()//работает
	{
		return MAX_SIZE;
	}

	void reserve(unsigned int _size)//работает
	{
		if (_size > MAX_SIZE + EXTRA_SIZE)
		{
			return;
		}
			
		T* temp_myVector_buffer = new T[_size + EXTRA_SIZE];
		memcpy(temp_myVector_buffer, myVector_buffer, (_size * sizeof(T)));

		delete[] myVector_buffer;
		myVector_buffer = temp_myVector_buffer;
		temp_myVector_buffer = NULL;

		myVector_size = _size;
		myVector_capacity = _size + EXTRA_SIZE;
	}

	unsigned int capacity()//работает
	{
		return myVector_capacity;
	}

	void shrink_to_fit()//работает
	{
		T* temp_myVector_buffer = new T[myVector_size];
		memcpy(temp_myVector_buffer, myVector_buffer, (myVector_size * sizeof(T)));

		delete[] myVector_buffer;
		myVector_buffer = temp_myVector_buffer;
		temp_myVector_buffer = nullptr;
		myVector_capacity = myVector_size;
	}

	/**** Модификаторы ****/

	void clear()//работает
	{
		while (myVector_size)
		{
			pop_back();
		}
	}

	void destroy(T* _item)//работает
	{ 
		_item->~T();
	};

	myIterator insert(myIterator _position, T _value)//работает
	{
		if (myVector_size == myVector_capacity)
		{
			reserve(myVector_capacity);
		}
		if (_position.get_index() < myVector_capacity) 
		{
			for (unsigned int i = myVector_size - 1; i >= _position.get_index(); i--)
			{
				myVector_buffer[i + 1] = myVector_buffer[i];
				if (i == 0)
				{
					break;
				}
			}
			myVector_buffer[_position.get_index()] = _value;
			myVector_size++;
			return begin() + _position.get_index();
		}
	}

	myIterator erase(myIterator _position)//работает
	{
		if (myVector_size != 0)
		{
			if (_position.get_index() < myVector_capacity && _position.get_index() >= 0)
			{
				if (_position.get_index() == myVector_size - 1)
				{
					destroy(myVector_buffer + myVector_size - 1);
				}
				for (unsigned int i = _position.get_index(); i < myVector_size - 1; i++)
				{
					myVector_buffer[i] = myVector_buffer[i + 1];
					if (i == 0)
					{
						break;
					}
				}
				myVector_size--;
				return begin() + _position.get_index();
			}
		}
	}

	void push_back(T _value)//работает
	{
		if (myVector_size >= myVector_capacity)
		{
			reserve(myVector_capacity);
		}

		myVector_buffer[myVector_size] = _value;
		myVector_size++;
	}

	void pop_back()//работает
	{
		erase(end());
	}

	void resize(unsigned int _size)//работает
	{
		if (_size <= MAX_SIZE + EXTRA_SIZE) 
		{
			T* Newbuffer = new T[_size];
			unsigned int size_t = _size < myVector_size ? _size : myVector_size;
			for (unsigned int i = 0; i < size_t; i++)
			{
				Newbuffer[i] = myVector_buffer[i];
			}
			if (_size > myVector_capacity)
			{
				myVector_capacity = _size;
			}
			if (_size < myVector_size)
			{
				myVector_size = _size;
			}
			delete[] myVector_buffer;
			myVector_buffer = Newbuffer;
			if (_size > myVector_size) 
			{
				while (myVector_size != _size)
				{
					destroy(myVector_buffer + myVector_size);
					if (_size > myVector_size)
					{
						myVector_size++;
					}
				}
			}
		}
	}

	void swap(myVector<T>& _vector)//работает
	{
		std::swap(_vector.myVector_size, myVector_size);
		std::swap(_vector.myVector_capacity, myVector_capacity);
		std::swap(_vector.myVector_buffer, myVector_buffer);
	}
};