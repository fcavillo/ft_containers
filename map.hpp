/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 18:56:46 by fcavillo          #+#    #+#             */
/*   Updated: 2022/02/16 12:45:24 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include <memory>
#include "pair.hpp"
#include "utils.hpp"
#include "map_iterator.hpp"

//https://www.cplusplus.com/reference/map/map/

//start doing empty, size..

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
//privatize it again bitch
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
		typedef typename allocator_type::template rebind<Node>::other 	node_allocator;		//rebind is a class in wich member "other" can be used to allocate other types
		typedef ft::pair<const key_type, mapped_type>					value_type;
		typedef typename allocator_type::reference						reference;
		typedef typename allocator_type::const_reference				const_reference;
		typedef typename allocator_type::pointer						pointer;
		typedef typename allocator_type::const_pointer					const_pointer;
		typedef ft::map_iterator<Key, T, Compare, Node>					iterator;
		typedef ft::map_iterator<Key, T, Compare, Node>			const_iterator;
		// typedef ft::reverse_iterator<iterator>					reverse_iterator;
		// typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;		


	private :
	
	/*	VARS	*/

		Node*					_root;		//pointer to first tree element
		Node*					_last;		//pointer to last tree element (before begin and rbegin)
		size_type				_size;		//number of nodes
		allocator_type			_allocPair;	//pair-size memory handling
		node_allocator			_allocNode;	//pair + pointers to relatives -size memory handling
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
			// std::cout << *first << std::endl;
			for (; first != last; first++)
		 		insert(*first);
		// insert(first, last);
			return ;
		}

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
		}

		map& operator= (const map& x)
		{
			map	tmp(x);
			
			this->swap(tmp);
			
			return *this;		
		}

	/*	ITERATORS	*/

		//sending node, last, comp function
		iterator begin()
		{
			iterator		beg = iterator(_last->right, _last, _comp);
// std::cout << "wsh maggle t pa un const" << std::endl;
			return (beg);
		}

		const_iterator begin() const
		{
			const_iterator	beg = const_iterator(_last->right, _last, _comp);
// std::cout << "wsh maggle t un const" << std::endl;
			return (beg);
		}

		iterator end()
		{
			iterator		end = iterator(_last, _last, _comp);
			return (end);
		}

		const_iterator end() const
		{
			const_iterator		end = const_iterator(_last, _last, _comp);
			return (end);		}
		
	/*	CAPACITY	*/

		bool empty() const
		{
			return (_size == 0);
		}

		size_type size() const
		{
			return (_size);
		}
		
		size_type max_size() const throw()
		{
			size_type	max = 0;
			try
			{
				max = _allocNode.max_size();
			}
			catch (std::exception &e)
			{
				std::cout << "Error :\t map::max_size : " << e.what() << std::endl;
			}
			return (max);
		}
		
	/*	ELEMENT ACCESS	*/

		//access an element : if exists, returns the content
		//if doesn't exist, inserts a node at this key and returns the available content space reference
		mapped_type& operator[] (const key_type& k)
		{
			Node*	tmp = searchNode(_root, k);

			if (tmp)
				return (tmp->data.second);

			value_type	newPair = ft::make_pair<key_type, mapped_type>(k, mapped_type()); //type != fct
			return (insertNode(_root, newPair)->data.second);
		}



	/*	MODIFIERS	*/

		//inserts val and returns a pair, 
		//with p::first being an iterator to the node,
		//p::second is true if val inserted, false if already there
		ft::pair<iterator,bool>	insert(/*const*/ value_type& val)
		{
			Node*	tmp = searchNode(_root, val.first);
			//look for key, if exists, return that iterator with false bool
			if (tmp)
				return (ft::pair<iterator, bool>(iterator(tmp, _last, _comp), false));
			tmp = insertNode(_root, val);
			return (ft::pair<iterator, bool>(iterator(tmp, _last, _comp), true));
		}

		//inserts val by starting looking for a spot at position,
		//optimizing insertion process
		//returns iterator to new node or already existing similar one
		iterator insert (iterator position, const value_type& val)
		{
			//if val.key < position.key, we decrease position until finding closest higher key
			if (val.first < position->first)
			{
				iterator	tooHigh(position);
				//tooHigh is always position - 1, so when we get to the first lower val, position is on the first higher one
				--tooHigh;
				while (tooHigh != end() && tooHigh->first >= val.first)
				{
					position--;
					tooHigh--;
				}
			}
			//if val.key > position.key, we increase position until finding closest lower key
			else if (val.first > position->first)
			{
				iterator	tooLow(position);
				//tooLow is always position + 1, so when we get to the first higher val, position is on the first lower one
				++tooLow;
				while (tooLow != end() && tooLow->first <= val.first)
				{
					position++;
					tooLow++;
				}
			}
			//if the key is aleady in the tree
			if (position != end() && val.first == position->first)
				return (position);

			// _size++
			return (iterator(insertNode(position.getNode(), val), _last, _comp));
					
		}

		template <class InputIterator>
		void insert (InputIterator first, InputIterator last,
		typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type* = 0)
		{
			while (first != last)
				insert(*first++);
			return ;
		}

		void erase (iterator position)
		{
			deleteNode(position.getNode(), position->first);
			return ;
		}

		size_type erase (const key_type& k)	//returns number of elem deleted (1 or 0)
		{
			if (deleteNode(_root, k))		//returns 1 if key not found
				return (0);
			return (1);
		}

		void erase (iterator first, iterator last)
		{
			while (first != last)
// 			{
// std::cout << "erasing [" << first->first << "] with parent " << first._node->parent->data.first << std::endl;
				erase(first++);
// std::cout << "_last left and right keys = " << _last->right->data.first << " / " << _last->left->data.first << std::endl;
// 			}
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

		void clear()
		{
			erase(begin(), end());
		}

	/*	OBSERVERS	*/

		//returns the used way of comparing keys (ft::less by default)
		key_compare key_comp() const
		{
			return (_comp);
		}
		
		//value compare is a nested class type (function object) map::value_compare 
		//the () operator is overloaded in it to allow a comparison of the keys of 2 pairs
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
			iterator	it = this->find(k);
			
			if (it != this->end())
				return (1);
			return (0);
		}

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

		void	deallocNode(Node* target)
		{
			_allocPair.destroy(&target->data);
			_allocNode.deallocate(target, 1);
		}

		//recursive comparison of the key with every key in the tree nodes (key = node->data.first)
		//returns the found node, or 0
		Node*	searchNode(Node* root, key_type key) const
		{
			//empty tree or leaf's child
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
	
		//returns 0 if key exists already, else inserts a node of value pair on best free space from position
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
//temp ????
				_size++;
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
//temp ????
			_size++;
			return (newNode);
		}
	
		//returns 1	if key is not found, else deletes node with a matching key found from position and returns 0
		bool	deleteNode(Node* position, key_type key)
		{
			Node*	target = searchNode(position, key);
			
			if (!target)
				return (1);
			
			//confusedNode is the node to balance from once the target is deleted
			//this is usually the parent, unless we delete _root then it is a child
			Node*	confusedNode = 0;
			
			/* DELETING THE PARENTLESS ROOT	*/
			if (!target->parent)
			{
				//case 1 : only node in the tree
				if (target->right == _last && target->left == _last)
				{
					_root = _last;
					_last->right = _last;
					_last->left = _last;
				}
				//case 2 : root only has one left or right child
				else if (target->left && target->right == _last)
				{
					// confusedNode = target->parent;
//makes no sense
					_root = target->left;		//root becomes left child
					target->left->parent = 0;	//cuts the link between target and new root
					_root->right = _last;
					_last->left = _root;		//setting the right side of the one node tree _last elem
				}
				else if (target->right && target->left == _last)
				{
					// confusedNode = target->parent;
//makes no sense
					_root = target->right;		//root becomes right child
					target->right->parent = 0;	//cuts the link between target and new root
					_root->left = _last;
					_last->right = _root;		//setting the left side of the one node tree _last elem
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
//who r u 		

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
			
//balance tree
			(void)confusedNode;

			deallocNode(target);

			_size--;
			return (0);
		}

		/*	AVL tree specifics	*/




};

	template< class Key, class T, class Compare, class Alloc >
	bool operator==( const ft::map<Key,T,Compare,Alloc>& lhs,
					const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		if (lhs.size() != rhs.size())
			return (false);
		ft::map<Key,T,Compare,Alloc>::iterator	itl = lhs.begin();
		ft::map<Key,T,Compare,Alloc>::iterator	itr = rhs.begin();
		
		while (itl != lhs.end())
		{
			if (itl != itr)
				return (false);
			itl++;
			itr++;
		}
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
		ft::map<Key,T,Compare,Alloc>::iterator	itl = lhs.begin();
		ft::map<Key,T,Compare,Alloc>::iterator	itr = rhs.begin();

		while (itl != lhs.end() && itr != rhs.end())
		{
			if (itl->first < itr->first)
				return (true);
			else if (itl->first > itr->first)
				return (false);
			else
			{
				if (itl->second < itr->second)
					return (true);
				else (itl->second > itr->second)
					return (false);
			}
			itl++;
			itr++;
		}
//	to finish
				
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