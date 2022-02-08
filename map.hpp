/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 18:56:46 by fcavillo          #+#    #+#             */
/*   Updated: 2022/02/08 12:40:53 by fcavillo         ###   ########.fr       */
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
		typedef Alloc				allocator_type;
		typedef size_t				size_type;
		typedef std::ptrdiff_t		difference_type;
		typedef pair<const key_type, mapped_type>			value_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef typename allocator_type::pointer			iterator;
		typedef typename allocator_type::const_pointer		const_iterator;
		typedef ft::reverse_iterator<iterator>				reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;		

	private :

		/*	NODE	*/

		struct	Node
		{
			ft::pair<const Key, T>	data;
			Node*					parent;
			Node*					left;
			Node*					right;
		};

		/*	VARS	*/

		Node*					_root;		//pointer to first tree element
		Node*					_last;		//pointer to last tree element
		size_type				_size;		//number of nodes
		allocator_type			_allocPair;	//pair-size memory handling
		std::allocator<Node>	_allocNode;	//pair + pointers to relatives -size memory handling
		key_compare				_comp;		//used way of comparing keys
		


	public :
	
	/*	CONSTRUCTORS, DESTRUCTOR, OPERATOR=	*/

	explicit map (const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type()) :
	_size(0),
	_allocPair(alloc),
	_comp(comp)
	{
		_last = createNode(ft::pair<const key_type, mapped_type>());	//the only node is empty, but allocated
		_root = _last;													
		_last->left = _last;
		_last->right = _last;
//or null ?		
		return ;
	}

	template <class InputIterator>
	map (InputIterator first, InputIterator last,
		const key_compare& comp = key_compare(),
		const allocator_type& alloc = allocator_type())
	_allocPair(alloc),
	_comp(comp)
	{
		
		return ;
	}

map (const map& x);

	private :
	
	/*	PRIVATE MEMBER FUNCTIONS	*/
	
	//create a new node, construct content, set relatives to 0
	Node*	createNode(const value_type & pair)
	{
		Node*	newNode = _allocNode.allocate(1); 

		_allocPair.construct(&newNode->data, pair);
		newNode->parent = 0;
		newNode->left = 0;
		newNode->right = 0;
		return (newNode);
	}
	
};

	
}; //namespace end

#endif