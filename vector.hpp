/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 00:42:45 by fcavillo          #+#    #+#             */
/*   Updated: 2022/01/21 06:02:30 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <memory>

/*
**  vectors allocate the size for a multi-element array.
**  when the number of elements equalizes the number of allocated elements,
**  vector reallocate a  bigger array elsewhere
*/
namespace ft {

template<typename T>
class vector
{
	public:
	
	
		vector() : _size(0), _capacity(1), _array(new T[_capacity])		
		{																//constructs empty container
			return ;
		}
	
		vector(size_t n, const T& val)	: _size(n), _capacity(n * 2), _array(new T[_capacity])						
		{																//constructs a container with n elements = val
			for (size_t i = 0; i < n; i++)
				_array[i] = val;
			return ;
		}
	
//		vector(InputIterator first, InputIterator last);	
	
	
		vector(const vector& rhs) : _size(rhs.size()), _capacity(rhs.capacity()), _array(new T[_capacity])
		{
			for (size_t i = 0; i < rhs.size(); i++)
				_array[i] = rhs._array[i];
		}

		~vector()
		{
			delete [] _array;
			return ;
		}


		bool empty() const
		{
			return (_size == 0);
		}
		size_t size() const 
		{
			return (_size);
		}
		size_t capacity() const
		{
			return (_capacity);
		}

		vector & operator=(const vector & rhs)
		{
			if (rhs.size() > size())
			{
				delete _array;
				_capacity = rhs.size();
				_array = new T[capacity()];
			}
			for (size_t i = 0; i < rhs.size(); i++)
				_array[i] = rhs._array[i];
			_size = rhs.size();
			return *this;
		}
		
		T & operator[](size_t index)
		{
			// if (index >= size())
			// 	return (NULL);
			return (_array[index]);
		}
		T & at(size_t index)
		{
			if (index < 0 || index >= size())
				throw std::out_of_range("Out of range error");
			return (_array[index]);			
		}
		T & front()
		{
			return (_array[0]);
		}
		T & back()
		{
			return (_array[size() - 1]);
		}

		bool	operator==(const vector& rhs) const
		{
			if (size() != rhs.size())
				return (false);
			for (int i = 0; i < size(); i++)
				if (_array[i] != rhs._array[i])
					return (false);
		}
		bool	operator!=(const vector& rhs) const
		{
			return !(*this == rhs);
		}
		bool	operator<(const vector& rhs) const
		{
			for (size_t i; i < size(); i++)
			{
				if (_array[i] < rhs._array[i])
					return (true);
			}
			return (false);
		}
		bool	operator<=(const vector& rhs) const
		{
			return !(*this > rhs);
		}
		bool	operator>(const vector& rhs) const
		{
			for (size_t i; i < size(); i++)
			{
				if (_array[i] > rhs._array[i])
					return (true);
			}
			return (false);
		}
		bool	operator>=(const vector& rhs) const
		{
			return !(*this < rhs);
		}
		
		
		void push_back(const T& val)
		{
			if (_size < _capacity)
			{
				_array[_size] = val;
				_size++;			
			}
			else
			{
				_capacity *= 2;
				T* newarray = new T[_capacity];
				for (size_t i = 0; i < size(); i++)
					newarray[i] = _array[i];
				newarray[_size] = val;
				_size++;				
				delete [] _array;
				_array = newarray;
				
			}	
		}
	
		void pop_back()
		{
			if (size() == 0)
				return ;
			_size--;
		}

		void insert(size_t position, const T & val)
		{
			if (position < 0 || position >= size())
				return ;
			push_back(_array[size() - 1]);
			for (size_t i = size() - 1; i > position ; i--)
				_array[i] = _array[i - 1]; 		
			_array[position] = val;	
		}
		void erase(size_t position)
		{
			if (position < 0 || position >= size())
				return ;
			for (size_t i = position; i < size() - 1; i++)
				_array[i] = _array[i + 1];
			_size--; 
		}
		void clear()
		{
			_size = 0;
		}

//	private:

		size_t	_size;
		size_t	_capacity;
		T*		_array;
		
};



}

template<typename T>
std::ostream & operator<<(std::ostream &o, ft::vector<T> const & rhs)
{
	for (size_t i = 0; i < rhs.size(); i++)
	{
		o << rhs._array[i] << " ";
	}
	o << " || ";
	for (size_t i = rhs.size(); i < rhs.capacity(); i++)
	{
		o << rhs._array[i] << " ";
	}
	o << std::endl;
	return (o);
}

#endif