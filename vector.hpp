/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 00:42:45 by fcavillo          #+#    #+#             */
/*   Updated: 2022/01/24 12:23:43 by fcavillo         ###   ########.fr       */
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

namespace ft 
{

template<typename T, class Alloc = std::allocator<T> >
class vector
{
	public:

		typedef T					value_type;
		typedef Alloc				allocator_type;
		typedef size_t				size_type;
		typedef ptrdiff_t			difference_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef typename allocator_type::pointer			iterator;
		typedef typename allocator_type::const_pointer		const_iterator;
//reverse_iterator ? + const

	/*	constructor, destructor, operator	*/

		//default constructor
		explicit vector (const allocator_type& alloc = allocator_type()) : 
		_alloc(alloc),
		_size(0),
		_capacity(0), 
		_array(NULL)		
		{
			return ;
		}

		//constructs a container with n elements = val
		explicit vector (size_type n, const value_type& val = value_type(), 
							const allocator_type& alloc = allocator_type()) :
		_alloc(alloc),
		_size(0), 
		_capacity(0), 
		_array(NULL)						
		{							
			assign(n, val);
			return ;
		}
	
//vector(InputIterator first, InputIterator last);	
	
	
		vector(const vector& rhs) : _size(rhs.size()), _capacity(rhs.capacity()), _array(new T[_capacity])
		{
			for (size_type i = 0; i < rhs.size(); i++)
				_array[i] = rhs._array[i];
		}

		~vector()
		{
			delete [] _array;
			return ;
		}

		vector & operator=(const vector & rhs)
		{
			if (rhs.size() > size())
			{
				delete _array;
				_capacity = rhs.size();
				_array = new T[capacity()];
			}
			for (size_type i = 0; i < rhs.size(); i++)
				_array[i] = rhs._array[i];
			_size = rhs.size();
			return *this;
		}


	/*	capacity	*/

		bool empty() const
		{
			return (_size == 0);
		}
		size_type size() const 
		{
			return (_size);
		}
		// size_type max_size() const
		// {
		// 	return ((size_t)(-1) / sizeof(ft::vector));
		// }

		//resizes the container so that it contains n elements
		void resize (size_type n, value_type val = value_type())
		{
			
		}
		
		size_type capacity() const
		{
			return (_capacity);
		}
		// void resize (size_type n, T val) //TODO
		// {
		// 	if (n < size())
		// 	{
		// 		_size = n;
		// 		return ;
		// 	}
		// 	else if ()
		// }
		// void reserve(size_type n)
		// {
		// 	//TODO	
		// }


	/*	element access	*/
		
		T & operator[](size_type index)
		{
			// if (index >= size())
			// 	return (NULL);
			return (_array[index]);
		}
		T & at(size_type index)
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


	/*	modifiers	*/

		template <class InputIterator>
		void assign (InputIterator first, InputIterator last)
		{
			//todo
		}

		void assign (size_type n, const value_type& val)
		{
			clear();
			resize(n, val);			
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
				for (size_type i = 0; i < size(); i++)
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

		void insert(size_type position, const T & val)
		{
			if (position < 0 || position >= size())
				return ;
			push_back(_array[size() - 1]);
			for (size_type i = size() - 1; i > position ; i--)
				_array[i] = _array[i - 1]; 		
			_array[position] = val;	
		}
		void erase(size_type position)
		{
			if (position < 0 || position >= size())
				return ;
			for (size_type i = position; i < size() - 1; i++)
				_array[i] = _array[i + 1];
			_size--; 
		}
		
		//empty vector
		void clear()
		{
			for (size_type i = 0; i < _size; i++)
				alloc.destroy(&_array[i]);
			_size = 0;
		}
			

	/*	non-member function operators	*/
//GET OUT BITCH

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
			for (size_type i; i < size(); i++)
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
			for (size_type i; i < size(); i++)
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
		
		
		// allocator_type get_allocator() const
		// {
		// 	return (Alloc.)
		// }

//	private:

		size_type		_size;
		size_type		_capacity;
		value_type*		_array;
		allocator_type	_alloc;
		
};

}	//namespace end

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