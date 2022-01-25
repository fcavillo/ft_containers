/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 00:42:45 by fcavillo          #+#    #+#             */
/*   Updated: 2022/01/24 17:30:06 by fcavillo         ###   ########.fr       */
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
		typedef std::ptrdiff_t			difference_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef typename allocator_type::pointer			iterator;
		typedef typename allocator_type::const_pointer		const_iterator;
//reverse_iterator ? + const

	/*	CONSTRUCTOR, DESTRUCTOR, OPERATOR	*/

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
			_alloc.deallocate(_array, _capacity);
			_alloc.destroy(_array);						
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


	/*	CAPACITY	*/

		size_type size() const 
		{
			return (_size);
		}

		size_type max_size() const
		{
			return ((size_t)(-1) / sizeof(ft::vector));
		}

		//resizes the container so that it contains n elements
		void resize (size_type n, value_type val = value_type())
		{
			while (n > _size)
				push_back(val);
			while (n < _size)
				pop_back();
			return ;
		}
		
		size_type capacity() const
		{
			return (_capacity);
		}
		
		bool empty() const
		{
			return (_size == 0);
		}

		//requests that the vector capacity be at least enough to contain n elements
		void reserve(size_type n)
		{
			size_t	new_capacity;
			//make sure the new_cap is at least 2x > than actual capacity
			if (n <= _capacity * 2)
				new_capacity = _capacity * 2;
			else
				new_capacity = n + 1;
//max_size error with a throw
			if ((n > _capacity))
			{
				if (_capacity == 0) //first alloc
				{
					_array = _alloc.allocate(new_capacity);
					_capacity = new_capacity;
				}
				else				//realloc 
				{
					value_type	*new_array;
					new_array = _alloc.allocate(new_capacity);
					for (size_t i = 0; i < _size; i++)	//copies array into new_rray by constructing on allocated slots
						_alloc.construct(new_array + i, _array[i]);
					_alloc.deallocate(_array, _capacity);
					_alloc.destroy(_array);
					_array = new_array;
					_capacity = new_capacity;
				}
			}
		}


	/*	ELEMENT ACCESS	*/
		
		reference operator[] (size_type n)
		{
			return (_array[n]);
		}

		//same as [] but with out_of_range exception
		reference at (size_type n)
		{
			if (n >= _size || n < 0)
				throw std::out_of_range("Error :\t vector::at :\t Out of range error");
			return (_array[n]);			
		}

		const_reference at (size_type n) const
		{
			if (n >= _size || n < 0)
				throw std::out_of_range("Error :\t vector::at :\t Out of range error");
			return (_array[n]);			
		}

		//first element in container
		reference front()
		{
			return (_array[0]);
		}

		const_reference front() const
		{
			return (_array[0]);
		}

		//last element in container
		reference back()
		{
			return (_array[_size - 1]);
		}

		const_reference back() const
		{
			return (_array[_size - 1]);
		}

	/*	MODIFIERS	*/

		template <class InputIterator>
		void assign (InputIterator first, InputIterator last)
		{
			(void)first;
			(void)last;
			clear();
//todo
		}

		void assign (size_type n, const value_type& val)
		{
			clear();
			resize(n, val);			
		}

		//add a value to the vector, realloc x2 if already full
		void push_back (const value_type& val)
		{
			if (_size == _capacity)
				reserve(_size + 1);
			//no need to allocate, done in reserve
			_alloc.construct(_array + _size, val);
			_size++;
		}

		//remove last vector value
		void pop_back ()
		{
			if (size() == 0)
				return ;
			_alloc.destroy(_array + _size - 1);
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
				_alloc.destroy(&_array[i]);
			_size = 0;
		}
			

	/*	NON-MEMBER FUNCTION OPERATORS	*/
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

		allocator_type	_alloc;
		size_type		_size;
		size_type		_capacity;
		value_type*		_array;
		
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