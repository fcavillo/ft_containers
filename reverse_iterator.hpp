/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 17:24:33 by fcavillo          #+#    #+#             */
/*   Updated: 2022/02/01 17:06:11 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "iterator_traits.hpp"

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

	/*	CONSTRUCTORS	*/
	
		reverse_iterator() : _base()
		{
			return ;
		}
		
		explicit reverse_iterator (iterator_type it) : _base(it)
		{
			return ;
		}
		
		template <class Iter>
		reverse_iterator (const reverse_iterator<Iter>& rev_it) : _base(rev_it.base())
		{
			return ;
		}

	/*	MEMBER FUNCTIONS	*/
	
		iterator_type base() const
		{
			return (_base);
		}

		reference operator*() const
		{
			iterator_type	tmp = _base;
			
			tmp--;
			return (*tmp);
		}

		//returns an iterator pointing at +n member
		reverse_iterator operator+ (difference_type n) const
		{
			return (reverse_iterator(_base - n));
		}

		//pre-increment
		reverse_iterator& operator++()
		{
			this->_base--;
			return (*this);
		}

		//post-increment
		reverse_iterator  operator++(int)
		{
			reverse_iterator	tmp = *this;
			
			this->_base--;
			return (tmp);			
		}
		
		reverse_iterator& operator+= (difference_type n)
		{
			this->_base = _base - n;
			return (*this);
		}

		reverse_iterator operator- (difference_type n) const
		{
			return (reverse_iterator(_base + n));
		}

		//pre-increment
		reverse_iterator& operator--()
		{
			this->_base++;
			return (*this);
		}

		//post-increment
		reverse_iterator  operator--(int)
		{
			reverse_iterator	tmp = *this;
			
			this->_base++;
			return (tmp);			
		}
		
		reverse_iterator& operator-= (difference_type n)
		{
			this->_base = _base + n;
			return (*this);
		}

		pointer operator->() const 
		{
  			return &(operator*());
		}

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
		return (lhs.base() - rhs.base());
	}

	template <class Iterator_L, class Iterator_R>
	bool operator- (const reverse_iterator<Iterator_L>& lhs,
					const reverse_iterator<Iterator_R>& rhs) 
	{ 
		return (lhs.base() - rhs.base()); 
	}
	
};

#endif