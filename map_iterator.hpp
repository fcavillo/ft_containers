/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 15:23:19 by fcavillo          #+#    #+#             */
/*   Updated: 2022/02/10 11:21:37 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_ITERATOR_HPP
#define MAP_ITERATOR_HPP

//https://www.cplusplus.com/reference/iterator/iterator/

/*	
*	implementation list for the map_iterator :
*	-	constructor, copy constructor, destructor
*	-	operator=
*	-	pointer and reference
*	-	operator++ pre and post-increment
*	-	operator-- pre and post-decrement
*	-	operator== amd operator !=
*/


//Const iterators to do
namespace   ft
{

template < class Key,											// map::key_type
		   class T,												// map::mapped_type
		   class Compare,										// map::key_compare
		   typename Node,										// node struct
		   bool C > 											// 1 for const, 0 for regular ??
class map_iterator
{
	public :
	
		typedef Key					key_type;
		typedef T					mapped_type;
		typedef	Compare				key_compare;
		typedef size_t				size_type;
		typedef std::ptrdiff_t		difference_type;
		typedef ft::pair<const key_type, mapped_type>				value_type;
		typedef typename std::bidirectional_iterator_tag			iterator_category;;
		typedef value_type				*pointer;
		typedef value_type				&reference;

	private :

		Node*		_node;		//curent node pointed by iterator
		Node*		_last;		//pointer to NULL pointer Type Nil : non-existant leaves, past-the-end element
		key_compare	_comp;		//used way of comparing keys to sort the map, needed to know wich way to iterate

	public :

	/*	CONSTRUCTORS, DESTRUCTOR, OPERATOR=	*/

		//default constructor, creates an iterator to the parameter node
		//if the parameters are not sent, defult set to 0
		map_iterator(Node* node = 0, Node* last = 0, const key_compare& comp = key_compare()) :
		_node(node),
		_last(last),
		_comp(comp)
		{
			return ;
		}

		//copy const
		map_iterator(const map_iterator<Key, T, Compare, Node, false>& copy)
		{
			_node = copy.getNode();
			_last = copy.getLast();
			_comp = copy.getComp();
			return ;
		}

		//nothing is ever allocated inside an iterator, it acts like a pointer
		~map_iterator()
		{
			return ;
		}

		map_iterator& operator=(const map_iterator& rhs)
		{
			if (this != rhs)
			{
				_node = rhs.getNode();
				_last = rhs.getLast();
				_comp = rhs.getComp();		
			}
		}
	
	/*	GETTERS	*/

		Node*	getNode() const
		{
			return (_node);
		}

		Node*	getLast() const
		{
			return (_last);
		}

		key_compare	getComp() const
		{
			return (_comp);
		}
	
	/*	MEMBER FUNCTION : OPERATORS	*/

		reference	operator*() const
		{
			return (_node->data);
		}
		
		pointer		operator->() const
		{
			return (&_node->data);	
		}

		//++ pre-increment operator goes from one key to the immediate superior one
		map_iterator&	operator++()
		{
			Node*	prevNode = _node;

			//iterator is starting on _last (rend() or end()), go back to min
			if (_node == _last)
			{
				_node == _last->right;
				return (*this);
			}
			
			//until reaching last and while prev >= node, we ++ (see ft::less in utils)
			while (_node != _last && !_comp(prevNode->data.first, _node->data.first))
			{
				//right child is last
				if (_node->right && _node->right == _last)
				{
					_node = _node->right;
				}
//cut some stuff
				//there is a right child : immediate higher node is right subtree's min
				else if (_node->right && _comp(prevNode->data.first, _node->data.first))
				{
					_node = _node->right;

					Node* 	tmp = 0;
//~~maybe _node can directly be set to lowest, no need for tmp
					if ((tmp = lowestNode(_node)))
						_node = tmp;
				}
				//no right child, try again from parent
//or go up until I am a left child
				else
					_node = _node->parent;
			}
			return (*this);
		}

		//++ post-increment operator goes from one key to the immediate superior one
		map_iterator	operator++(int)
		{
			map_iterator	ret(*this);

			//iterator is starting on last, go back to min
			if (_node == _last)
			{
				_node == _last->right;
				return (ret);
			}
			
			//until reaching last and while prev >= node, we ++ (see ft::less in utils)
			while (_node != _last && !_comp(ret->first, _node->data.first))
			{
				//right child is _last
				if (_node->right && _node->right == _last)
				{
					_node = _node->right;
				}
//cut some stuff
				//there is a right child : immediate higher node is right subtree's min
				else if (_node->right && _comp(ret->first, _node->data.first))
				{
					_node = _node->right;

					Node* 	tmp = 0;
					if ((tmp = lowestNode(_node)))
						_node = tmp;
				}
				//no right child, try again from parent
				else
					_node = _node->parent;
			}
			return (ret);	
		}

		//-- pre-decrement operator goes from one key to the immediate inferior one
		map_iterator&	operator--()
		{
			Node*	prevNode = _node;

			//iterator is starting on _last (rend() or end()), go back to max
			if (_node == _last)
			{
				_node == _last->left;
				return (*this);
			}
			
			//until reaching last and while prev <= node, we -- (see ft::less in utils)
			while (_node != _last && !_comp(_node->data.first, prevNode->data.first))
			{
				//left child is _last
				if (_node->left && _node->left == _last)
				{
					_node = _node->left;
				}
//cut some stuff
				//there is a left child : immediate lower node is left subtree's max
				else if (_node->left && _comp(_node->data.first, prevNode->data.first))
				{
					_node = _node->left;

					Node* 	tmp = 0;
					if ((tmp = highestNode(_node)))
						_node = tmp;
				}
				//no right child, try again from parent
//or go up until I a; a right child
				else
					_node = _node->parent;
			}
			return (*this);
		}

		//-- post-decrement operator goes from one key to the immediate inferior one
		map_iterator	operator--(int)
		{
			map_iterator	ret(*this);

			// iterator is starting on last, go back to root
			if (_node == _last)
			{
				_node == _last->left;
				return (ret);
			}
			
			//until reaching last and while prev <= node, we -- (see ft::less in utils)
			while (_node != _last && !_comp(_node->data.first, ret->first))
			{
				//left child is _last
				if (_node->left && _node->left == _last)
				{
					_node = _node->left;
				}
//cut some stuff
				//there is a left child : immediate lower node is left subtree's max
				else if (_node->left && _comp(_node->data.first, ret->first))
				{
					_node = _node->left;

					Node* 	tmp = 0;
					if ((tmp = highestNode(_node)))
						_node = tmp;
				}
				//no right child, try again from parent
				else
					_node = _node->parent;
			}
			return (ret);
		}

		bool	operator==(const map_iterator& rhs) const
		{
			return (rhs._node == _node);
		}

		bool	operator!=(const map_iterator& rhs) const
		{
			return (rhs._node != _node);
		}

	/*	PRIVATE MEMBER FUNCTIONS	*/
	
	private :

		//returns the lowest key node from the root after recursive search
		Node*	lowestNode(Node* root)
		{
			if (root && root != _last && root->left && root->left != _last)
				return (lowestNode(root->left));
			return (root);
		}
	
		//returns the highest key node from the root after recursive search
		Node*	highestNode(Node* root)
		{
			if (root && root != _last && root->right && root->right != _last)
				return (highestNode(root->left));
			return (root);
		}
	
};


};   //namespace end

#endif