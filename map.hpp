/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 18:56:46 by fcavillo          #+#    #+#             */
/*   Updated: 2022/02/23 19:16:19 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP
#include <unistd.h> //for sleep

#include <memory>
#include "pair.hpp"
#include "utils.hpp"
#include "map_iterator.hpp"
#include "reverse_iterator.hpp"

//https://www.cplusplus.com/reference/map/map/
//https://en.cppreference.com/w/cpp/container/map

/*
*	std::map is a sorted associative container that contains key-value pairs with unique keys. 
*	Keys are sorted by using the comparison function Compare.
*	List of implementations :
		-	Member classes :
			*	value_compare
		-	Member functions :
			*	constructors
			*	destructor
			*	operator=
			*	get_allocator
			*	operator[]
			*	begin
			*	end
			*	rbegin
			*	rend
			*	empty
			*	size
			*	max_size
			*	clear
			*	insert
			*	erase
			*	swap
			*	count
			*	find
			*	equal_range
			*	lower_bound
			*	upper_bound
			*	key_comp
			*	value_comp
		-	Non-member functions :
			*	comparison operators9
			*	std::swap
*
*/


namespace   ft
{

template < class Key,											// map::key_type
		   class T,												// map::mapped_type
		   class Compare = ft::less<Key>,						// map::key_compare
		   class Alloc = std::allocator<pair<const Key,T> > >	// map::allocator_type
class map
{

	private :

	/*	NODE	*/

		/*	This is one the stored element
		*	data is of type value_type,
		*	pointers are directed to relatives
		*
		*				Parent
		*				  |
		*				data
		*				/	\
		*			left	right
		*										*/
		struct	Node
		{
			ft::pair<const Key, T>	data;
			Node*					parent;
			Node*					left;
			Node*					right;
		};

	
	public :
	
	/*	ALIASES	*/
	
		/*	The map is composed of several nodes, each node has pointers to it's relatives
		*	and a data made of a pair of <const Key, T>
		*	Key being the key at which the node is spatially,
		*	T being the type of data actually stored in the map	
		*	value_type represents a pair	*/
		typedef Key										key_type;
		typedef T										mapped_type;
		typedef ft::pair<const key_type, mapped_type>	value_type;

		/*	key_compare is the used way of comparing keys, which sets the order of the nodes in the map */
		typedef	Compare				key_compare;

		/*	By default, std::allocator is used, here for a pair-sized allocation
		*	to alloc for nodes, I am using rebind, a class in std::allocator 
		*	in wich member "other" can be used to allocate other types	*/
		typedef Alloc														allocator_type;
		typedef typename allocator_type::template rebind<Node>::other 		node_allocator;		

		/*	To respect the naming norms, size_t and std::ptrdiff_t are renamed	*/
		typedef size_t				size_type;
		typedef std::ptrdiff_t		difference_type;

		/*	Pointers and references are based on the std::allocator pointers and references	*/
		typedef typename allocator_type::reference							reference;
		typedef typename allocator_type::const_reference					const_reference;
		typedef typename allocator_type::pointer							pointer;
		typedef typename allocator_type::const_pointer						const_pointer;

		/*	iterators and const_iterators work similarly, but
		*	the references and pointers are constant for const iterators	
		*	reverse_iterators are based on those but have the same functions no matter the container	*/
		typedef typename ft::map_iterator<Key, T, Compare, Node, false>     iterator;
		typedef typename ft::map_iterator<Key, T, Compare, Node, true>      const_iterator;
		typedef ft::reverse_iterator<iterator>								reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>						const_reverse_iterator;		


	private :

	/*	VARS	*/

		Node*				_root;			//pointer to first tree element
		Node*				_last;			//pointer to link tree element (before begin and rbegin)
		size_type			_size;			//number of nodes
		allocator_type		_allocPair;		//pair-size memory handling
		node_allocator		_allocNode;		//pair + pointers to relatives -size memory handling
		key_compare			_comp;			//used way of comparing keys to sort the map
		


	public :
	
	/*	CONSTRUCTORS, DESTRUCTOR, OPERATOR=	*/


		/*	Default constructor, constructs an empty container.
		*	An empty node is allocated for _last, _last is set as the root in a self-centered loop.
		*	Node is initialised with an empty type of data	*/
		explicit map (const key_compare& comp = key_compare(),
					const allocator_type& alloc = allocator_type()) :
		_size(0),
		_allocPair(alloc),
		_comp(comp)
		{
			_last = createNode(ft::pair<const key_type, mapped_type>());
			_root = _last;													
			_last->left = _last;
			_last->right = _last;

			return ;
		}

		/*	Constructs the container with the value_type contents of the range [first, last)
		*	_last is allocated as an empty node, each value_type is then inserted one by one */
		template <class InputIterator>
		map (InputIterator first, InputIterator last,
			const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type()) :
		_size(0),
		_allocPair(alloc),
		_comp(comp)
		{
			_last = createNode(ft::pair<const key_type, mapped_type>());
			_root = _last;
			_last->left = _last;
			_last->right = _last;

			for (; first != last; first++)
		 		insert(*first);
			return ;
		}

		/*	Copy constructor : constructs the container with the copy of the contents of other	*/
		map (const map& x) :
		_size(0),
		_allocPair(x._allocPair),
		_allocNode(x._allocNode),
		_comp(x._comp)
		{
			_last = createNode(ft::pair<const key_type, mapped_type>());
			_root = _last;
			_last->left = _last;
			_last->right = _last;
			insert(x.begin(), x.end());
			return ;
		}

		/*	Destructors of the elements are called and the used storage is deallocated	*/
		~map ()
		{
			clear();
			deallocNode(_root);
			return ;
		}

		/*	Replaces the contents with a copy of the contents of other
		*	by creating a copy of x, then swaping with current instance	 */
		map& operator= (const map& x)
		{
			map	tmp(x);
			
			this->swap(tmp);
//leaks ?			
			return *this;		
		}

	/*	ITERATORS	*/

		/*	Returns an iterator to the first element,
		*	here to the right of _last : sending node, _last and _comp to the iterator constructor	*/
		iterator begin()
		{
			iterator		beg = iterator(_last->right, _last, _comp);
			return (beg);
		}

		/*	Returns a const iterator to the first element,
		*	here to the right of _last : sending node, _last and _comp to the const_iterator constructor	*/		const_iterator begin() const
		{
			const_iterator	beg = const_iterator(_last->right, _last, _comp);
			return (beg);
		}

		/*	Returns an iterator to the _last element :
		*	sending node (here _last), _last and _comp to the iterator constructor	*/
		iterator end()
		{
			iterator		end = iterator(_last, _last, _comp);
			return (end);
		}

		/*	Returns a const_iterator to the _last element :
		*	sending node (here _last), _last and _comp to the const_iterator constructor	*/		
		const_iterator end() const
		{
			const_iterator		end = const_iterator(_last, _last, _comp);
			return (end);		
		}

		/*	Returns a reverse_iterator to rbegin = end() - 1
		*	here to the left of _last : sending node, _last and _comp to the rev_iterator constructor	*/
		reverse_iterator rbegin()
		{
			return (reverse_iterator(end()));
		}
		/*	Returns a const_reverse_iterator to rbegin = end() - 1
		*	here to the left of _last : sending node, _last and _comp to the const_rev_iterator constructor	*/
		const_reverse_iterator rbegin() const
		{
			return (const_reverse_iterator(end()));
		}

		/*	Returns a rev_iterator to rend = _last or begin() - 1:
		*	sending node (here _last), _last and _comp to the rev_iterator constructor	*/
		reverse_iterator rend()
		{
			return (reverse_iterator(begin()));
		}

		/*	Returns an const_rev_iterator to rend = _last or begin() - 1:
		*	sending node (here _last), _last and _comp to the const_rev_iterator constructor	*/
		const_reverse_iterator rend() const
		{
			return (const_reverse_iterator(begin()));
		}

	/*	CAPACITY	*/

		bool empty() const
		{
			return (_size == 0);
		}

		size_type size() const
		{
			return (_size);
		}
		
		/*	Returns the maximum number of elements the container is able to hold,
		*	calculated from the max_size function from std::allocator, for a size of Node
		*	https://www.cplusplus.com/reference/memory/allocator/max_size/	*/
		size_type max_size() const
		{
			size_type	max = 0;

			max = _allocNode.max_size();
			
			return (max);
		}
		
	/*	ELEMENT ACCESS	*/

		/*	Returns a reference to the value that is mapped to a key equivalent to k, 
		*	performing an insertion if such key does not already exist :
		*	creating a pair from k and empty mapped_type(),
		*	inserting node with data = newPair,
		*	returning reference to mapped_type value	*/
		mapped_type& operator[] (const key_type& k)
		{
			Node*	tmp = searchNode(_root, k);

			if (tmp)
				return (tmp->data.second);


			value_type	newPair = ft::make_pair<key_type, mapped_type>(k, mapped_type());
			tmp = insertNode(_root, newPair);

			return (tmp->data.second);
		}

		// https://www.cplusplus.com/reference/map/map/at/ (at) was not implemented in c++98


	/*	MODIFIERS	*/

		/*	Inserts a value_type val in the map. 
		*	A pair is returned, with p->first being an iterator to the new node (or same-key node if existant),
		*	and p->second being a bool : true if inserted, false if key already exists	*/
		ft::pair<iterator,bool>	insert(const value_type& val)
		{
			//look for key, if exists, return the iterator to the node with false bool
			Node*		tmp = searchNode(_root, val.first);
			if (tmp)
			{
				iterator it = iterator(tmp, _last, _comp);
				return (ft::pair<iterator, bool>(it, false));
			}

			//else, insert new value into map by creating a new node and return the iterator to the node with true bool 
			tmp = insertNode(_root, val);
			iterator it = iterator(tmp, _last, _comp);
			return (ft::pair<iterator, bool>(it, true));
		}

		/*	Inserts a value_type val in the map, starting to look for the closest spot from position 
		*	(search and insertion optimization). 
		*	This is done by going down until we find the closest existant higher key (for low keys)
		*	or closest existant lower key (for high keys),
		*	since this is a good point where to start looking for the correct node spot with insert.
		*	Returns an iterator to the new node (or same-key node if existant) 	*/
		iterator insert (iterator position, const value_type& val)
		{ 
			//if the key is aleady in the tree
			if (count(val.first))
				return (position);
			//if val.key < position.key, we decrease position until finding closest higher key
			else if (_comp(val.first, position->first))
			{
				while (position != end() && _comp(val.first, position->first))
					position--;
				position++;
					
			}
			//if val.key > position.key, we increase position until finding closest lower key
			else if (_comp(position->first, val.first))
			{
				while (position != end() && _comp(position->first, val.first))
					position++;
				position--;
			}
			//if key is already in the tree
			if (position != end() && val.first == position->first)
				return (position);

			Node*	newNode = insertNode(position.getNode(), val);
			return (iterator(newNode, _last, _comp));
					
		}

		/*	Inserts elements from range [first, last[.		
		*	enable_if is an additional function argument : (Substitution Failure Is Not An Error)
		*	this insert takes 2 parameters but it has to be differentiated from the previous insert at compilation
		*	To do this, we check that the parameters sent is not an integral_type :
		*	is_integral<InputIterator> has to be false */
		template <class InputIterator>
		void insert (InputIterator first, InputIterator last,
		typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type* = 0)
		{
			while (first != last)
				insert(*first++);
			return ;
		}

		/*	Erases a specific node at position	*/
		void erase (iterator position)
		{
			deleteNode(position.getNode(), position->first);
			return ;
		}

		/*	Erases a specific node with key k,
		*	returns the number of deleted nodes (0 or 1)	*/
		size_type erase (const key_type& k)
		{
			if (deleteNode(_root, k))			//returns 1 if key not found
				return (0);
			return (1);
		}

		/*	Erases every node from [first to last[	*/
		void erase (iterator first, iterator last)
		{
			while (first != last)
				erase(first++);
			return ;
		}

		void swap (map& x)
		{

			Node*					tmp_root 		= x._root;		
			Node*					tmp_last 		= x._last;
			size_type				tmp_size 		= x._size;		
			allocator_type			tmp_allocPair 	= x._allocPair;	
			std::allocator<Node>	tmp_allocNode 	= x._allocNode;	
			key_compare				tmp_comp 		= x._comp;	
			
			x._root 		= this->_root;		
			x._last 		= this->_last;	
			x._size 		= this->_size;			
			x._allocPair	= this->_allocPair;		
			x._allocNode 	= this->_allocNode;		
			x._comp 		= this->_comp;		

			this->_root 		= tmp_root;
			this->_last 		= tmp_last;
			this->_size 		= tmp_size;
			this->_allocPair 	= tmp_allocPair;
			this->_allocNode 	= tmp_allocNode;
			this->_comp 		= tmp_comp;

			return;		
		}

		/*	Erases all elements from the container	*/
		void clear()
		{
			erase(begin(), end());
		}

	/*	OBSERVERS	*/

		/* Returns the used way of comparing keys (ft::less by default)	*/
		key_compare key_comp() const
		{
			return (_comp);
		}
		
		/*	Value compare is a nested class type (function object) map::value_compare 
		*	the () operator is overloaded in it to allow a comparison of the keys of 2 pairs	*/
		class	value_compare
		{
			//friend class can access private and protected members of class in which it is declared as friend
			friend class map;

			public :

				typedef bool		result_type;
				typedef value_type	first_argument_type;
				typedef value_type	second_argument_type;
				
				bool operator()( const value_type& lhs, const value_type& rhs ) const
				{
					return (_val_comp(lhs.first, rhs.first));
				}

			protected :
			
				value_compare(Compare c) : _val_comp(c)
				{
					return;
				}
				
				Compare	_val_comp;
				
		};

		value_compare	value_comp() const
		{
			return (value_compare(_comp));
		}

	/*	OPERATIONS	*/

		iterator find (const key_type& k)
		{
			Node*	target = searchNode(_root, k);

			if (target)
				return (iterator(target, _last, _comp));
			
			return (end());
		}
		
		const_iterator find (const key_type& k) const
		{
			Node*	target = searchNode(_root, k);

			if (target)
				return (const_iterator(target, _last, _comp));
			
			return (end());		
		}

		size_type count (const key_type& k) const
		{
			const_iterator	it = this->find(k);
			
			if (it != this->end())
				return (1);
			return (0);
		}

		/* Returns an iterator pointing to the first element that is not less than (i.e. greater or equal to) key */
		iterator lower_bound (const key_type& k)
		{
			iterator	it = this->begin();
			iterator	ite = this->end();
			
			for (; it != ite && (key_comp())(it->first, k) == true && it != ite; it++);
			return (it);
		}
		
		const_iterator lower_bound (const key_type& k) const
		{
			const_iterator	it = this->begin();
			const_iterator	ite = this->end();
			
			for (; it != ite && (key_comp())(it->first, k) == true; it++);
			return (it);		
		}

		/* Returns an iterator pointing to the first element that is greater than key */
		iterator upper_bound (const key_type& k)
		{
			iterator	it = this->begin();
			iterator	ite = this->end();
			
			for (; it != ite && (key_comp())(k, it->first) == false; it++);
			return (it);
		}

		const_iterator upper_bound (const key_type& k) const
		{
			const_iterator	it = this->begin();
			const_iterator	ite = this->end();
			
			for (; it != ite && (key_comp())(k, it->first) == false; it++);
			return (it);		
		}

		pair<const_iterator,const_iterator> equal_range (const key_type& k) const
		{
			ft::pair<const_iterator, const_iterator>	pair(lower_bound(k), upper_bound(k));

			return (pair);
		}
		
		pair<iterator,iterator>             equal_range (const key_type& k)
		{
			ft::pair<iterator, iterator>	pair(lower_bound(k), upper_bound(k));

			return (pair);		
		}

	/*	ALLOCATOR	*/

		allocator_type get_allocator() const
		{
			return(_allocPair);
		}


	private :
	
	/*	PRIVATE MEMBER FUNCTIONS	*/
		/*	BST tree handling	*/
	
		/*	Creates a new node, allocates for it, 
		*	constructs a pair, sets relatives to 0	*/
		Node*	createNode(const value_type & pair)
		{
			Node*	newNode = _allocNode.allocate(1); 

			_allocPair.construct(&newNode->data, pair);
			newNode->parent = 0;
			newNode->left = 0;
			newNode->right = 0;

			return (newNode);
		}

		void	deallocNode(Node* target)
		{
			_allocPair.destroy(&target->data);
			_allocNode.deallocate(target, 1);
		}

		/*	lisa <3	*/
		/*	Recursive comparison of the wanted key with every key in the tree (node->data.first).
		*	Returns the found node or 0 if not found	*/
		Node*	searchNode(Node* root, key_type key) const
		{
			//reached _last or leaf child : no key found
			if (!root || root == _last)
				return (0);

			//found key : key !< root.key and key !> root.key
			if (_comp(root->data.first, key) == 0 && _comp(key, root->data.first) == 0)
				return (root);

			//recursive loop until key is found : if the node key is higher, I go left
			if (_comp(key, root->data.first) && root->left && root->left != _last)
				return (searchNode(root->left, key));
			else if (_comp(root->data.first, key) && root->right && root->right != _last)
				return (searchNode(root->right, key));

			return (0); 
		}

		Node*	searchMaxNode(Node* root) const
		{
			if (root->right && root->right != _last)
				return (searchMaxNode(root->right));
			return (root);
		}

		Node*	searchMinNode(Node* root) const
		{
			if (root->left && root->left != _last)
				return (searchMinNode(root->left));
			return (root);
		}
	
		/*	Makes a new node with data = pair, searching recursively for it's spot from position.
		*	Returns 0 if key already exists, 	*/
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

				_size++;
				return (_root);
			}

			//key already exists
			if (position->data.first == pair.first)
				return (0);

			//recursion until reaching a leaf or a _last : if pair.key < node.key, go left
			if (_comp(pair.first, position->data.first) && position->left && position->left != _last)
				return (insertNode(position->left, pair));
			else if (_comp(position->data.first, pair.first) && position->right && position->right != _last)
				return (insertNode(position->right, pair));

			//reaching a leaf or max/min node wich are parents to _last
			Node*	newNode = createNode(pair);
			
			//if reached a regular leaf with space on the needed side
			if (_comp(newNode->data.first, position->data.first) && !position->left)
				position->left = newNode;
			else if (_comp(position->data.first, newNode->data.first) && !position->right)
				position->right = newNode;
			//if reached max/min, node has to be inserted between max/min and _last
			else if (position->left && _comp(newNode->data.first, position->data.first))
			{
				newNode->left = _last;				//setting left child as last
				_last->right = newNode;				//setting last's right child to new as the new min
				position->left = newNode;			//putting new in position's left
			}		
			else if (position->right && _comp(position->data.first, newNode->data.first))
			{
				newNode->right = _last;				//setting right child as last
				_last->left = newNode;				//setting last's left child to new as the new max
				position->right = newNode;			//putting new in position's right
			}

			newNode->parent = position;
			
			balanceTree(&_root, newNode);

			_size++;
			return (newNode);
		}
	
		/*	Deletes the node with the matching key, returns 0 if done, 1 if not found	*/
		bool	deleteNode(Node* position, key_type key)
		{
			Node*	target = searchNode(position, key);
			
			if (!target)
				return (1);
			
			//confusedNode is the node to balance from once the target is deleted
			//this is usually the parent, unless we delete _root then it is 0 to make balanceTree useless
			Node*	confusedNode = 0;
			
			/* DELETING THE PARENTLESS ROOT	*/
			if (!target->parent)
			{
				//case 1 : only one node in the tree
				if (target->right == _last && target->left == _last)
				{
					_root = _last;
					_last->right = _last;
					_last->left = _last;
				}
				//case 2 : root only has one left or right child
				else if (target->left && target->right == _last)
				{
					confusedNode = target->parent;	//set as 0
					_root = target->left;			//root becomes left child
					target->left->parent = 0;		//cuts the link between target and new root
					_root->right = _last;
					_last->left = _root;			//setting the right side of the one node tree _last elem
				}
				else if (target->right && target->left == _last)
				{
					confusedNode = target->parent;	//set as 0
					_root = target->right;			//root becomes right child
					target->right->parent = 0;		//cuts the link between target and new root
					_root->left = _last;
					_last->right = _root;			//setting the left side of the one node tree _last elem
				}
				//case 3 : root has 2 children -> set the 'inorder predecessor' one as root
				else
				{
					Node*	leftSubtreeHighest = searchMaxNode(target->left);

					_allocPair.destroy(&target->data);
					_allocPair.construct(&target->data, leftSubtreeHighest->data);	//copy highestNode to root
//make a graph
					//in the left subtree, delete the highest that was moved to root
					return (deleteNode(target->left, leftSubtreeHighest->data.first));	
				}
			}
			/*	DELETING A NODE	*/
			//case 1 : target is a leaf
			else if ((!target->left || target->left == _last) && (!target->right || target->right == _last))
			{
				confusedNode = target->parent;

				if (target->left == _last)									//min leaf node (left)
				{
					_last->right = target->parent;
					target->parent->left = _last;
				}
				else if (target->right == _last)							//max leaf node (right)
				{
					_last->left = target->parent;
					target->parent->right = _last;
				}
				else if (target->data.first <= target->parent->data.first)	//regular leaf	(left)
				{
					target->parent->left = 0;
				}
				else														//regular leaf	(right)
				{
					target->parent->right = 0;
				}
			}
			//case 2 : target has a child
			else if ((target->left && target->left != _last) && (!target->right || target->right == _last))	//has a left child
			{
				confusedNode = target->parent;
	
				if (target->data.first <= target->parent->data.first)		//target is a left child
					target->parent->left = target->left;
				else														//target is a right child
					target->parent->right = target->left;
				target->left->parent = target->parent;
				
				if (target->right == _last)									//target is max node
				{
					target->left->right = _last;
					_last->left = target->left;
				}
			}
			else if ((target->right && target->right != _last) && (!target->left || target->left == _last))	//has a right child
			{
				confusedNode = target->parent;

				if (target->data.first <= target->parent->data.first)		//target is a left child
					target->parent->left = target->right;
				else														//target is a right child
					target->parent->right = target->right;
				target->right->parent = target->parent;
				
				if (target->left == _last)									//target is max node
				{
					target->right->left = _last;
					_last->right = target->right;
				}
			}
			//case 3 : target has 2 children : same logic as root -> set the 'inorder predecessor' one as root
			else
			{
				Node*	leftSubtreeHighest = searchMaxNode(target->left);

				_allocPair.destroy(&target->data);
				_allocPair.construct(&target->data, leftSubtreeHighest->data);	//copy highestNode to root
//make a graph
				//in the left subtree, delete the highest that was moved to root
				return (deleteNode(target->left, leftSubtreeHighest->data.first));					
			}
			
			balanceTree(&_root, confusedNode);

			deallocNode(target);

			_size--;
			return (0);
		}

		/*	AVL tree specifics	*/

		int	treeHeight(Node* root, int height)
		{
			//reached leaf + 1
			if (!root || root == _last)
				return (height - 1);

			int	leftHeight = treeHeight(root->left, height + 1);
			int rightHeight = treeHeight(root->right, height + 1);

			if (leftHeight > rightHeight)
				return (leftHeight);
			else
				return (rightHeight);
		}

		int		balanceFactor(Node* node)
		{
			return (treeHeight(node->left, 1) - treeHeight(node->right, 1));
		}

		//checks from node to root if each one is balanced (bf should be -1, 0 or 1)
		//https://www.programiz.com/dsa/avl-tree
		void	balanceTree(Node** root, Node* node)
		{
			// return ;
			while (node)
			{
				int	bf;
				bf = balanceFactor(node);
				if (bf > 1 && balanceFactor(node->left) > 0)		//ll
				{
					rotateRight(root, node);
				}
				else if (bf > 1 && balanceFactor(node->left) <= 0)	//lr
				{
					rotateLeft(root, node->left);
					rotateRight(root, node);
				}
				else if (bf < -1 && balanceFactor(node->right) >= 0)	//rl
				{
					rotateRight(root, node->right);
					rotateLeft(root, node);
				}
				else if (bf < -1 && balanceFactor(node->right) < 0)	//rr
				{
					rotateLeft(root, node);
				}
				node = node->parent;
			}
			return ;
		}

		void	rotateLeft(Node** root, Node* nodeDown)
		{
			Node*	nodeUp = nodeDown->right;
// std::cout << "rotate left" << std::endl;				

			// nodeDown->right = nodeUp->left;

			// if (nodeUp->left)
			// 	nodeUp->left->parent = nodeDown;

			// if (!(nodeDown->parent))
			// {
			// 	_root = nodeUp;
			// 	nodeUp->parent = 0;
			// }
			// else if (nodeDown->parent->left == nodeDown)	//down is a left child
			// 	nodeDown->parent->left = nodeUp;
			// else											//down is a right child
			// 	nodeDown->parent->right = nodeUp;
			
			// nodeDown->parent = nodeUp;
			
			  nodeDown->right = nodeUp->left;

				if (nodeUp->left)
					nodeUp->left->parent = nodeDown;
				
				nodeUp->left = nodeDown;
				
				nodeUp->parent = nodeDown->parent;

				if (nodeDown->parent && nodeDown->parent->left == nodeDown)
					nodeDown->parent->left = nodeUp;
				else if (nodeDown->parent)
					nodeDown->parent->right = nodeUp;

				nodeDown->parent = nodeUp;

				if (!nodeUp->parent)
				   *root = nodeUp;
				   
			return ;
		}

		void	rotateRight(Node** root, Node* nodeDown)
		{
			Node*	nodeUp = nodeDown->left;
// std::cout << "rotate right" << std::endl;				

			// nodeDown->left = nodeUp->right;

			// if (nodeUp->right)
			// 	nodeUp->right->parent = nodeDown;

			// if (!(nodeDown->parent))
			// {
			// 	_root = nodeUp;
			// 	nodeUp->parent = 0;
			// }
			// else if (nodeDown->parent->right == nodeDown)	//down is a right child
			// 	nodeDown->parent->right = nodeUp;
			// else											//down is a left child
			// 	nodeDown->parent->left = nodeUp;

			// nodeDown->parent = nodeUp;
			
			//
			  nodeDown->left = nodeUp->right;

				if (nodeUp->right)
					nodeUp->right->parent = nodeDown;
				
				nodeUp->right = nodeDown;
				
				nodeUp->parent = nodeDown->parent;

				if (nodeDown->parent && nodeDown->parent->left == nodeDown)
					nodeDown->parent->left = nodeUp;
				else if (nodeDown->parent)
					nodeDown->parent->right = nodeUp;

				nodeDown->parent = nodeUp;

				if (!nodeUp->parent)
				   *root = nodeUp;
			
			return ;
		}
/* 	This is a public member function, created for the correction.
	It is based on the answer from @Adrian Schneider :
	https://stackoverflow.com/questions/36802354/print-binary-tree-in-a-pretty-way-using-c
	This has to be a public member function since it needs access to the private _root
	
	It is a great way to visualize the tree and it's balanced structure.
	It works best for perfectly balanced trees, 
	with a node total number of 3, 15, 63, 255, 511... ((powers of 2) - 1) */

public :
void printBT(const std::string& prefix, const Node* node, bool isLeft)
{
	if( node && node != _last )
	{
		usleep(125000);
		std::cout << prefix;

		std::cout << (isLeft ? "├──" : "└──" );

		// print the value of the node
		std::cout << node->data.first << std::endl;

		// enter the next tree level - left and right branch
		printBT( prefix + (isLeft ? "│   " : "    "), node->left, true);
		printBT( prefix + (isLeft ? "│   " : "    "), node->right, false);
	}
}

void printBT()
{
	printBT("", _root, false);    
}

/*	testos fin	*/

};

	template< class Key, class T, class Compare, class Alloc >
	bool operator==( const ft::map<Key,T,Compare,Alloc>& lhs,
					const ft::map<Key,T,Compare,Alloc>& rhs )
	{
// std::cout << "1" << std::endl;
		if (lhs.size() != rhs.size())
			return (false);
// std::cout << "2" << std::endl;

		typename ft::map<Key,T>::const_iterator	itl = lhs.begin();
		typename ft::map<Key,T>::const_iterator	itr = rhs.begin();
// int i = 0;		
		while (itl != lhs.end())
		{
// std::cout << i++ << std::endl;	
			if (*itl != *itr)
				return (false);
			itl++;
			itr++;
		}
// std::cout << "3" << std::endl;
		return (true);		
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator!=( const ft::map<Key,T,Compare,Alloc>& lhs,
					const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		return (!(lhs == rhs));
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator<( const ft::map<Key,T,Compare,Alloc>& lhs,
					const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		typename ft::map<Key,T>::const_iterator	itl = lhs.begin();
		typename ft::map<Key,T>::const_iterator	itr = rhs.begin();		
		typename ft::map<Key,T>::const_iterator	itle = lhs.end();
		typename ft::map<Key,T>::const_iterator	itre = rhs.end();

		while (itl != itle)
		{
			if (*itl < *itr)				//left is lesser
				return (true);
			else if (*itl > *itr)			//right is lesser
				return (false);
			else if (itr == itre)			//right is shorter == lesser
				return (false);
			itl++;
			itr++;
		}
		if (itr == itre && itl == itle)	//both sides are equal
			return (false);
		return (true);					//left is shorter == lesser				
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator<=( const ft::map<Key,T,Compare,Alloc>& lhs,
					const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		return (!(rhs < lhs));
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator>( const ft::map<Key,T,Compare,Alloc>& lhs,
					const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		return (!(lhs <= rhs));
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator>=( const ft::map<Key,T,Compare,Alloc>& lhs,
					const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		return (!(lhs < rhs));
	}
  




}; //namespace end

#endif