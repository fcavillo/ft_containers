/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 17:53:20 by fcavillo          #+#    #+#             */
/*   Updated: 2022/03/02 16:14:17 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"
#include <deque>

/*
**	stacks are container adaptors, operating in LIFO mode,
**	that use an encapsulated container class as it's underlying container,
**	as long as the container can support the few stack base operations :
**	empty, size, back, push_back, pop_back
**	
**	more : https://www.cplusplus.com/reference/stack/stack/
*/



namespace   ft
{

template <class T, class Container = ft::vector<T> >
class stack
{
	public:

		typedef T			value_type;
		typedef Container	container_type;
		typedef size_t		size_type;

	/*	CONSTRUCTOR	*/

		explicit stack (const container_type& ctnr = container_type()) :
		c(ctnr)
		{
			return ;
		}

		stack( const stack& other )
		{
			this->c = other.c;
		}
		
		~stack()
		{
			return ;
		}

		stack& operator=( const stack& other )
		{
			this->c = other.c;
			return (*this);
		}

	/*	MEMBER FUNCTIONS	*/

		bool empty() const
		{
			return(c.empty());
		}
		
		size_type size() const
		{
			return(c.size());
		}

		//stack.top is equivalent to others.back
		value_type& top()
		{
			return(c.back());
		}
		
		const value_type& top() const
		{
			return(c.back());
		}

		void push (const value_type& val)
		{
			return(c.push_back(val));
		}

		void pop()
		{
			return(c.pop_back());
		}

	/*	NON-MEMBER FUNCTION OVERLOAD	*/
	
	//these operators need access to the protected container_type variable,
	//friend declaration grants access to private or protected members of the class declaring friendship
	template <class T_, class Container_>
	friend bool operator== (const stack<T_,Container_>& lhs, const stack<T_,Container_>& rhs);

	template <class T_, class Container_>
	friend bool operator<  (const stack<T_,Container_>& lhs, const stack<T_,Container_>& rhs);

	protected:

		container_type		c;
};

	template <class T, class Container>
	bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs.c == rhs.c);
	}
	
	template <class T, class Container>
	bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return !(lhs == rhs);		
	}

	template <class T, class Container>
	bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs.c < rhs.c);
	}

	// l >= r == l !< r
	template <class T, class Container>
	bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return !(lhs < rhs);
	}

	// l > r == l !<= r
	template <class T, class Container>
	bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return !(lhs <= rhs);
	}
	
	// l <= r == r !< l
	template <class T, class Container>
	bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return !(rhs < lhs);
	}

};	//namespace end;

#endif