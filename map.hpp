/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 18:56:46 by fcavillo          #+#    #+#             */
/*   Updated: 2022/02/09 17:11:35 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include <memory>
#include "pair.hpp"
#include "utils.hpp"
#include "map_iterator.hpp"

//https://www.cplusplus.com/reference/map/map/

//start doing empty, begin, end, size..

namespace   ft
{

template < class Key,											// map::key_type
		   class T,												// map::mapped_type
		   class Compare = ft::less<Key>,						// map::key_compare
		   class Alloc = std::allocator<pair<const Key,T> >		// map::allocator_type
		   > 
class map
{

	private :

	/*	NODE	*/

		struct	Node
		{
			ft::pair<const Key, T>	data;
			Node*					parent;
			Node*					left;
			Node*					right;
		};

	
	public :
	
	/*	ALIASES	*/
	
		typedef Key					key_type;
		typedef T					mapped_type;
		typedef	Compare				key_compare;
		typedef Alloc				allocator_type;
		typedef size_t				size_type;
		typedef std::ptrdiff_t		difference_type;
		typedef ft::pair<const key_type, mapped_type>			value_type;
		typedef typename allocator_type::reference				reference;
		typedef typename allocator_type::const_reference		const_reference;
		typedef typename allocator_type::pointer				pointer;
		typedef typename allocator_type::const_pointer			const_pointer;
		typedef ft::map_iterator<Key, T, Compare, Node, false>	iterator;
		typedef ft::map_iterator<Key, T, Compare, Node, true>	const_iterator;
		typedef ft::reverse_iterator<iterator>					reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;		


	private :
	
	/*	VARS	*/

		Node*					_root;		//pointer to first tree element
		Node*					_last;		//pointer to last tree element
		size_type				_size;		//number of nodes
		allocator_type			_allocPair;	//pair-size memory handling
		std::allocator<Node>	_allocNode;	//pair + pointers to relatives -size memory handling
		key_compare				_comp;		//used way of comparing keys to sort the map
		


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

		//enable_if only lets the last parameter exist as long as it is not an int
		//it checks if the type of the value InputIterator is an int
		template <class InputIterator>
		map (InputIterator first, InputIterator last,
			const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type(),
			typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type* = 0) :
		_size(0),
		_allocPair(alloc),
		_comp(comp)
		{
			_last = createNode(ft::pair<const key_type, mapped_type>());
			_root = _last;
			_last->left = _last;
			_last->right = _last;
	//++f or f++
			std::cout << *first << std::endl;
			for (; first != last; first++)
		 		insert(*first);
		// insert(first, last);
			(void)last;
			return ;
		}

	map (const map& x);


	/*	ITERATORS	*/


	/*	CAPACITY	*/

		
	/*	ELEMENT ACCESS	*/

		//access an element : if exists, returns the content
		//if doesn't exist, inserts a node at this key and returns the available content space reference
		mapped_type& operator[] (const key_type& k)
		{
			Node*	tmp = searchNode(_root, k);

			if (tmp)
				return (tmp->data.second);

			value_type	newPair = make_pair<key_type, mapped_type>(k, mapped_type()); //type != fct
			return (insertNode(_root, newPair)->data.second);
		}



	/*	MODIFIERS	*/

		//inserts val and returns a pair, 
		//with p::first being an iterator to the node,
		//pair::second is true if val inserted, false if already there
		ft::pair<iterator,bool>	insert(/*const*/ value_type& val)
		{
			Node*	isKeyDouble = searchNode(_root, val.first);
std::cout << "insert 1" << std::endl;
			if (isKeyDouble)
				return (ft::pair<iterator, bool>(iterator(isKeyDouble, _last, _comp), false));
	//look for key, if exists, return that iterator with false bool
			_size++;
return (ft::pair<iterator, bool>(iterator(isKeyDouble, _last, _comp), false)); //badddd
		}

		//inserts val at position,
		//returns iterator to new node or already existing similar one
		iterator insert (iterator position, const value_type& val)
		{
std::cout << "insert 2" << std::endl;
			(void)val;
			return (position);
		}

		template <class InputIterator>
		void insert (InputIterator first, InputIterator last,
		typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type* = 0)
		{
std::cout << "insert 3" << std::endl;
			(void)first;
			(void)last;
			return ;
		}


	/*	OBSERVERS	*/


	/*	OPERATIONS	*/


	/*	ALLOCATOR	*/

	private :
	
	/*	PRIVATE MEMBER FUNCTIONS	*/
		/*	AVL tree handling	*/
	
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

		//recursive comparison of the key with every key in the tree nodes (key = node->data.first)
		//returns the found node, or 0
		Node*	searchNode(Node* root, key_type key)
		{
			//empty tree or leaf
			if (!root || root == _last)
				return (0);
			
			//found key : key !< root.key and key !> root.key
			if (_comp(root->data.first, key) == 0 && _comp(key, root->data.first) == 0)
				return (root);

			//recursive loop until key is found : if the node is higher, I go left
			if (root->data.first > key && root->left && root->left != _last)
				return (searchNode(root->left, key));
			else if (root->data.first < key && root->right && root->right != _last)
				return (searchNode(root->right, key));

//case where it would reach the end ?			
			return (0); 
		}
	
		//returns 0 if key exists already
		Node*	insertNode(Node* position, const value_type& pair)
		{
			//first node creation
			if (_root == _last)
			{
				_root = createNode(pair);

				_root->left = _last;
				_root->right = _last;
				_last->left = _root;
				_last->right = _root;

				return (_root);
			}

			//key already exists
			if (position->data.first == pair.first)
				return (0);

			//recursion until reaching a leaf or a _last : if pair.key < node.key, go left
			if (position->data.first > pair.first && position->left && position->left != _last)
				return (insertNode(position->left, pair));
			else if (position->data.first < pair.first && position->right && position->right != _last)
				return (insertNode(position->right, pair));

			/*reaching a leaf or max/min node wich are parents to _last*/
			Node*	newNode = createNode(pair);
			
			//if reached a regular leaf with space on the needed side
			if (position->data.first > newNode->data.first && !position->left)
				position->left = newNode;
			else if (position->data.first < newNode->data.first && !position->right)
				position->right = newNode;
			//if reached max/min, node has to be inserted between max/min and _last
			else if (position->left && position->data.first > newNode->data.first)
			{
				newNode->left = _last;				//setting left child as last
				_last->right = newNode;				//setting last's right child to new
				position->left = newNode;			//putting new in position's left
			}		
			else if (position->right && position->data.first < newNode->data.first)
			{
				newNode->right = _last;				//setting right child as last
				_last->left = newNode;				//setting last's left child to new
				position->right = newNode;			//putting new in position's right
			}

			newNode->parent = position;
			
//equilibrage mdr

			return (newNode);
		}
	
};

	
}; //namespace end

#endif