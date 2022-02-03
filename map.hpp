/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 18:56:46 by fcavillo          #+#    #+#             */
/*   Updated: 2022/02/02 16:55:55 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include <memory>
#include "pair.hpp"
#include "utils.hpp"
#include "reverse_iterator.hpp"

namespace   ft
{

template < class Key,											// map::key_type
		   class T,												// map::mapped_type
		   class Compare = ft::less<Key>,						// map::key_compare
		   class Alloc = std::allocator<pair<const Key,T> >		// map::allocator_type
		   > 
class map
{
	public :
		typedef Key					key_type;
		typedef T					mapped_type;
		typedef	Compare				key_compare;
		//value_compare ?
		typedef Alloc				allocator_type;
		typedef size_t				size_type;
		typedef std::ptrdiff_t		difference_type;
		typedef typename pair<const key_type, mapped_type>	value_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef typename allocator_type::pointer			iterator;
		typedef typename allocator_type::const_pointer		const_iterator;
		typedef ft::reverse_iterator<iterator>				reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;		

	/*	CONSTRUCTORS, DESTRUCTOR, OPERATOR=	*/

explicit map (const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type());

template <class InputIterator>
	map (InputIterator first, InputIterator last,
		const key_compare& comp = key_compare(),
		const allocator_type& alloc = allocator_type());

map (const map& x);


};

	
}; //namespace end

#endif