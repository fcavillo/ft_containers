/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 19:10:25 by fcavillo          #+#    #+#             */
/*   Updated: 2022/02/08 11:58:10 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
#define PAIR_HPP

/*
**	This class couples together a pair of values,
**	which may be of different types (T1 and T2)
*/

namespace   ft
{

template <class T1, class T2>
struct pair
{
	typedef	T1	first_type;
	typedef T2	second_type;
	
	first_type	first;
	second_type	second;
	
	/*	CONSTRUCTOR	*/

		pair() :
		first(),
		second()
		{
			return ;
		}
		
		template<class U, class V> 
		pair (const pair<U,V>& pr) :
		first(pr.first),
		second(pr.second)
		{
			return ;
		}
		
		pair( const T1& x, const T2& y ) :
		first(x),
		second(y)
		{
			return ;
		}

	/* MEMBER FUNCTIONS	*/
		
		pair& operator= (const pair& pr)
		{
			first = pr.first;
			second = pr.second;
			return (*this);
		}
	
};

	/*	NON-MEMBER FUNCTION OVERLOADS	*/

	template <class T1, class T2>
	bool operator== (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
	{ 
		return (lhs.first == rhs.first && lhs.second == rhs.second);
	}

	template <class T1, class T2>
	bool operator!= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
	{ 
		return !(lhs == rhs); 
	}

	template <class T1, class T2>
	bool operator<  (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
	{ 
		return (lhs.first < rhs.first || (!(rhs.first < lhs.first) 
					&& lhs.second < rhs.second));
	}

	template <class T1, class T2>
	bool operator<= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
	{ 
		return !(rhs < lhs); 
	}

	template <class T1, class T2>
	bool operator>  (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
	{ 
		return (rhs < lhs);
	}

	template <class T1, class T2>
	bool operator>= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
	{
		return !(lhs < rhs);
	}	

	template <class T1, class T2>
	pair<T1,T2> make_pair (T1 x, T2 y)
	{
		return (ft::pair<T1, T2>(x, y));
	}

};

#endif