/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 00:42:45 by fcavillo          #+#    #+#             */
/*   Updated: 2022/02/01 14:10:22 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <memory>
#include <stdexcept>
#include <algorithm>

#include "reverse_iterator.hpp"
#include "utils.hpp"
//#include <vector>

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
		typedef ft::reverse_iterator<iterator>				reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;

	/*	CONSTRUCTOR, DESTRUCTOR, OPERATOR=	*/

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
			_array = _alloc.allocate(n);
			_capacity = n;
			while (n--)
			{
				_alloc.construct(_array + _size, val);
				_size++;
			}
		}


		//enable_if only lets the last parameter exist as long as it is not an int, to counter the previous constructor
		template <class InputIterator>
		vector (InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type(),
		typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0) :
		_alloc(alloc),
		_size(0)
		{
			size_t	s = 0;
			
			for (InputIterator tmp = first; tmp != last; tmp++)
				s++;
			_array = _alloc.allocate(s);
			_capacity = s;

			while (s--)
			{
				_alloc.construct(_array + _size, *first++);
				_size++;
			}
		}
	
		vector(const vector& x) :
		_alloc(x._alloc),
		_size(0),
		_capacity(0), 
		_array(NULL)
		{
			insert(begin(), x.begin(), x.end());
		}

		~vector()
		{
			if (_array)
			{
				// std::cout << "destroy bitch1" << std::endl;
				for (iterator it = begin(); it != end(); it++)
					_alloc.destroy(it);
				// std::cout << "destroy bitch2 : going to dealloc" << std::endl;
				_alloc.deallocate(_array, _capacity);
				// std::cout << "destroy bitch3" << std::endl;
			}
			return ;
		}

		vector & operator= (const vector & x)
		{
			if (x == *this)
				return *this;
			clear();
			insert(begin(), x.begin(), x.end());
			return *this;
		}


	/*	ITERATORS	*/

		iterator begin()
		{
			iterator	beg = &_array[0];
			return (beg);
		}

		const_iterator begin() const
		{
			const_iterator	beg = &_array[0];
			return (beg);
		}

		iterator end()
		{
			iterator	end = &_array[_size];
			return (end);
		}

		const_iterator end() const
		{
			const_iterator	end = &_array[_size];
			return (end);
		}

		reverse_iterator rbegin()
		{
			reverse_iterator	rbeg = &_array[_size - 1];
			return (rbeg);
		}
		
		const_reverse_iterator rbegin() const
		{
			const_reverse_iterator	rbeg = &_array[_size - 1];
			return (rbeg);
		}			

		reverse_iterator rend()
		{
			reverse_iterator	rend = &_array[0];
			rend--;
			return (rend);
		}
		
		const_reverse_iterator rend() const
		{
			const_reverse_iterator	rend = &_array[0];
			rend--;
			return (rend);
		}	

	/*	CAPACITY	*/
    
		size_type size() const 
		{
			return (_size);
		}

		size_type max_size() const
		{
			size_type	max = 0;
			try
			{
				max = _alloc.max_size();
			}
			catch (std::exception &e)
			{
				std::cout << "Error :\t vector::max_size : " << e.what() << std::endl;
			}
			return (max);
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

			if (n > max_size())
				throw std::length_error("Error:\t vector::reserve : n > max_size");
			//make sure the new_cap is at least 2x > than actual size
			if (n <= _size * 2)
				new_capacity = _size * 2;
			else
				new_capacity = n;
			if ((n > _capacity))
			{
				if (_capacity == 0) //first alloc
				{
					_array = _alloc.allocate(new_capacity);
// std::cout << "first alloc" << std::endl;
					_capacity = new_capacity;
				}
				else				//realloc 
				{
	// std::cout << "realloc, meaning the size to reserve (" << n << ") is bigger than capacity (" << this->capacity() << ")" << std::endl;
					value_type	*new_array;
					new_array = _alloc.allocate(new_capacity);
					for (size_t i = 0; i < _size; i++)	//copies array into new_array by constructing on allocated slots
						_alloc.construct(new_array + i, _array[i]);
					// _alloc.deallocate(_array, _capacity);
					// _alloc.destroy(_array);
					for (iterator it = begin(); it != end(); it++)
						_alloc.destroy(it);
	// std::cout << "dealloc" << std::endl;
					_alloc.deallocate(_array, _capacity);				
//wow wow wow this is nonsense 
					_array = new_array;
					_capacity = new_capacity;
				}
			}
		}


	/*	ELEMENT ACCESS	*/
		
		reference operator[] (size_type n)
		{
			return (*(_array + n));
		}

		const_reference operator[] (size_type n) const
		{
			return (*(_array + n));
		}

		//same as [] but with out_of_range exception
		reference at (size_type n)
		{
			if (n >= _size || n < 0)
				throw std::out_of_range("Error :\t vector::at : Out of range error");
			return (_array[n]);			
		}

		const_reference at (size_type n) const
		{
			if (n >= _size || n < 0)
				throw std::out_of_range("Error :\t vector::at : Out of range error");
			return (_array[n]);			
		}

		//first element in container
		reference front()
		{
			return (*_array);
		}

		const_reference front() const
		{
			return (*_array);
		}

		//last element in container
		reference back()
		{
			return (*(_array + size() - 1));
		}

		const_reference back() const
		{
			return (*(_array + size() - 1));
		}

	/*	MODIFIERS	*/

		template <class InputIterator>
		void assign (InputIterator first, InputIterator last,
		typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0)
		{
			clear();
			insert(begin(), first, last);
		}

		void assign (size_type n, const value_type& val)
		{
			clear();
			resize(n, val);			
		}

		//add a value to the vector, realloc x2 if already full
		void push_back (const value_type& val)
		{
//  std::cout << "pushing_back " << val << " size = " << size() << "/" << capacity() << std::endl;
			if (_size == _capacity)
			{
				size_t	new_cap;
				
				if (size() > 0)
					new_cap = size() * 2;
				else
					new_cap = 1;
				reserve(new_cap);
			}
			//no need to allocate, done in reserve
			_alloc.construct(_array + _size, val);
			_size++;
// std::cout << "pushed_back " << val << " size = " << size() << "/" << capacity() << "[i] = " << _array[_size-1] <<std::endl;
		}

		//remove last vector value
		void pop_back ()
		{
			if (size() == 0)
				return ;
			_alloc.destroy(_array + _size - 1);
			_size--;
		}

		//inserts val at position, returning iterator to the position
		iterator insert (iterator position, const value_type& val)
		{
			size_t	pos = position - begin();	//convert position to a size_t
			size_t	n = 1;

			insert(position, n, val);
			return (&_array[pos]);
		}

		//inserts n * val from position
		void insert (iterator position, size_type n, const value_type& val)
		{
			vector		tmp;
			iterator	it = begin();
// std::cout << "inserts n * val from position" << std::endl;
			if (n <= 0)
				return ;
			//reserve might change the overall capacity
			tmp.reserve(_size + n); 
			for (; it != position; it++)
				tmp.push_back(*it);
			for (; n > 0; n--)
				tmp.push_back(val);
			for (; it != end(); it++)
				tmp.push_back(*it);
				
			swap(tmp);
		}

		//insert an array from first to last from position
		//only use this insert if the InputIterators sent are indeed pointers
		template <class InputIterator>
		void insert (iterator position, InputIterator first, InputIterator last,
		typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type* = 0)
		{
			vector		tmp;
			iterator	it = begin();
// std::cout << "insert an array from first to last from position" << std::endl;
// std::cout << "1 size = " << size() << "/" << capacity() <<std::endl;

			// if (it != NULL)
			// {
				for (; it != position; it++)
				{
					tmp.push_back(*it);
// std::cout << "pb old" << std::endl;				
				}
			// }
			for (; first != last; first++)
			{
				tmp.push_back(*first);
// std::cout << "pb new" << std::endl;				
			}
			for (; it != end(); it++)
			{
				tmp.push_back(*it);
// std::cout << "pb end old" << std::endl;				
			}

// std::cout << " size = " << size() << "/" << capacity() <<std::endl;
// std::cout << "tmp.[0] = " << tmp._array[0] <<std::endl;			
			swap(tmp);
// std::cout << "[0] = " << _array[0] <<std::endl;			
// std::cout << "finished insert" << std::endl;				

		}		

		//erase val from position
		iterator erase (iterator position)
		{
			iterator	it = position;
// std::cout << "in erase" << std::endl;
			_alloc.destroy(position);
// std::cout << "destroyed" << std::endl;
			for (iterator tmp = position; tmp != end() - 1; tmp++)
			{
// std::cout << "constructin'" << std::endl;
				_alloc.construct(tmp, *(tmp + 1));
//necessary ?	// if (tmp + 1 != end())
				// 	_alloc.destroy(tmp + 1);
// std::cout << "constructed'" << std::endl;
			}
			_size--;
// std::cout << "erase done" << std::endl;
			return (it);
		}
				
		//erase vals from first to last
		iterator erase (iterator first, iterator last)
		{
			for (; first != last; --last)
				first = erase(first);
			return (last);
		}		
		//exchange this' content with x's
		void swap (vector& x)
		{
			if (x == *this)
				return;
			
			allocator_type	tmp_alloc 	= x._alloc;
			size_type		tmp_size 	= x._size;
			size_type		tmp_capacity = x._capacity;
			value_type*		tmp_array 	= x._array;

			x._alloc 	= this->_alloc;
			x._size 	= this->_size;
			x._capacity = this->_capacity;
			x._array 	= this->_array;

			this->_array 	= tmp_array;
			this->_size 	= tmp_size;
			this-> _capacity = tmp_capacity;
			this->_alloc	 = tmp_alloc;
			return;
		}

		//empty vector
		void clear()
		{
			for (size_type i = 0; i < _size; i++)
				_alloc.destroy(&_array[i]);
			_size = 0;
		}
			


		
		
	/*	ALLOCATOR	*/

		allocator_type get_allocator() const
		{
			return (_alloc);
		}

//	private:

		allocator_type	_alloc;
		size_type		_size;
		size_type		_capacity;
		value_type*		_array;
		
};

	/*	NON-MEMBER FUNCTION OPERATORS	*/

	template <class T, class Alloc>
	bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		for (size_t i = 0; i < lhs.size(); i++)
			if (lhs[i] != rhs[i])
				return (false);
		return (true);
	}
	
	template <class T, class Alloc>
	bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)	
	{
		return !(lhs == rhs);
	}
	
	//using the lexicographical comparaison wich returns true if vect1 is < to vect2
	template <class T, class Alloc>
	bool operator< (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)	
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}
	
	//is v1 >= v2, then !v1 < v2
	template <class T, class Alloc>
	bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)	
	{
		return !(lhs < rhs);
	}
	
	template <class T, class Alloc>
	bool operator> (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)	
	{
		return (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));
	}
	
	//is v1 <= v2, then !v1 > v2
	template <class T, class Alloc>
	bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)	
	{
		return !(lhs > rhs);
	}

}	//namespace end


//to delete
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