/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 18:56:46 by fcavillo          #+#    #+#             */
/*   Updated: 2022/01/29 19:04:58 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include <memory>

namespace   ft
{

template < class Key,											// map::key_type
           class T,												// map::mapped_type
           class Compare = less<Key>,							// map::key_compare
           class Alloc = std::allocator<pair<const Key,T> >		// map::allocator_type
           > 
class map
{
	public :
		typedef Key		key_type;
		typedef T		mapped_type;
		
};

	
};

#endif