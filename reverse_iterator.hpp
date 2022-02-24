/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 17:24:33 by fcavillo          #+#    #+#             */
/*   Updated: 2022/02/24 18:57:50 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "iterator_traits.hpp"

//https://en.cppreference.com/w/cpp/iterator/reverse_iterator
//http://www.cplusplus.com/reference/iterator/reverse_iterator/

/*	Using the iterator aliases from iterator traits,
*	This class reverses the direction in which a bidirectional iterator iterates through a range.
*	It keeps a copy of the original iterator as _base :
*	For most actions done on a current instance, the opposite will be applied to _base.
*	when an iterator is reversed, the reversed version does not point to the same element in the range, 
*	but to the one preceding it. 
*	List of implementations :
	-	Member functions :
		*	constructor
		*	base
		*	operator*
		*	operator+
		*	operator++
		*	operator+=
		*	operator-
		*	operator--
		*	operator-=
		*	operator->
		*	operator[]
	-	Non-member functions :
		*	relational operators
		*	operator+
		*	operator-		
*/

namespace ft
{

template <typename Iterator>
class   reverse_iterator
{
	public :

		typedef Iterator		                        					iterator_type;
		typedef typename ft::iterator_traits<Iterator>::value_type			value_type;;
		typedef typename ft::iterator_traits<Iterator>::difference_type		difference_type;;
		typedef typename ft::iterator_traits<Iterator>::iterator_category	iterator_category;;
		typedef typename ft::iterator_traits<Iterator>::pointer				pointer;
		typedef typename ft::iterator_traits<Iterator>::reference			reference;

	/*	CONSTRUCTORS, OPERATOR=	*/
	
		reverse_iterator() : _base()
		{
			return ;
		}
		
		explicit reverse_iterator (iterator_type it) : _base(it)
		{
			return ;
		}
		
		/*	Copy constructor	*/
		template <class Iter>
		reverse_iterator (const reverse_iterator<Iter>& rev_it) : _base(rev_it.base())
		{
			return ;
		}

	
		template< class U >
		reverse_iterator& operator=( const reverse_iterator<U>& other )
		{
			_base = other.base();
			return *this;
		}
		
	/*	MEMBER FUNCTIONS	*/
	
		iterator_type base() const
		{
			return (_base);
		}

		/*	Returns a reference to the element pointed to by the iterator	*/
		reference operator*() const
		{
			iterator_type	tmp = _base;
			
			tmp--;
			return (*tmp);
		}

		/*	Returns a reverse iterator pointing to the element located 
		*	n positions away from the element the iterator currently points to	*/
		reverse_iterator operator+ (difference_type n) const
		{
			return (reverse_iterator(_base - n));
		}

		/*	The pre-increment version returns *this	*/
		reverse_iterator& operator++()
		{
			this->_base--;
			return (*this);
		}

		/*	The post-increment version returns the value *this had before the call	*/
		reverse_iterator  operator++(int)
		{
			reverse_iterator	tmp(*this);
			
			++(*this);
			return (tmp);			
		}
		
		/*	Advances the reverse_iterator by n element positions	*/
		reverse_iterator& operator+= (difference_type n)
		{
			this->_base = _base - n;
			return (*this);
		}

		/*	Returns a reverse iterator pointing to the element located 
		*	n positions away from the element the iterator currently points to	*/
		reverse_iterator operator- (difference_type n) const
		{
			return (reverse_iterator(_base + n));
		}

		/*	The pre-decrement version returns *this	*/
		reverse_iterator& operator--()
		{
			this->_base++;
			return (*this);
		}

		/*	The post-decrement version returns the value *this had before the call	*/
		reverse_iterator  operator--(int)
		{
			reverse_iterator	tmp = *this;
			
			--(*this);
			return (tmp);			
		}
		
		/*	Descreases the reverse_iterator by n element positions	*/
		reverse_iterator& operator-= (difference_type n)
		{
			this->_base = _base + n;
			return (*this);
		}

		/*	Returns a pointer to the element pointed to by the iterator,
		*	referenced so it can be modified	*/
		pointer operator->() const 
		{
  			return &(operator*());
		}

		/*	Accesses the element located n positions away 
		*	from the element currently pointed to by the iterator	*/
		reference operator[] (difference_type n) const
		{
			return (base()[-n - 1]);
		}

	private :

		iterator_type	_base;
	
};

	/*	NON-MEMBER FUNCTION OVERLOADS	*/

	template <class Iterator1, class Iterator2>
	bool operator== (const reverse_iterator<Iterator1>& lhs,
                   const reverse_iterator<Iterator2>& rhs)
	{	
		return (lhs.base() == rhs.base());
	}
	
	template <class Iterator1, class Iterator2>
	bool operator!= (const reverse_iterator<Iterator1>& lhs,
                   const reverse_iterator<Iterator2>& rhs)
	{	
		return (lhs.base() != rhs.base());
	}

	//comparison operators are inverted
	template <class Iterator1, class Iterator2>
	bool operator<  (const reverse_iterator<Iterator1>& lhs,
                   const reverse_iterator<Iterator2>& rhs)
	{	
		return (lhs.base() > rhs.base());
	}

	template <class Iterator1, class Iterator2>
	bool operator<= (const reverse_iterator<Iterator1>& lhs,
                   const reverse_iterator<Iterator2>& rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template <class Iterator1, class Iterator2>
	bool operator>  (const reverse_iterator<Iterator1>& lhs,
                   const reverse_iterator<Iterator2>& rhs)
	{	
		return (lhs.base() < rhs.base());
	}

	template <class Iterator1, class Iterator2>
	bool operator>= (const reverse_iterator<Iterator1>& lhs,
                   const reverse_iterator<Iterator2>& rhs)
	{	
		return (lhs.base() <= rhs.base());
	}

	template <class Iterator>
	reverse_iterator<Iterator> operator+ (typename reverse_iterator<Iterator>::difference_type n,
             								const reverse_iterator<Iterator>& rev_it)
	{
		return (rev_it + n);
	}

	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator- (const reverse_iterator<Iterator>& lhs,
																	const reverse_iterator<Iterator>& rhs)
	{
		return (rhs.base() - lhs.base());
	}

	template <class Iterator_L, class Iterator_R>
	std::ptrdiff_t operator- (const reverse_iterator<Iterator_L>& lhs,
								const reverse_iterator<Iterator_R>& rhs) 
	{ 
		return (rhs.base() - lhs.base()); 
	}
	
};

#endif