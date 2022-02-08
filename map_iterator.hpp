/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 15:23:19 by fcavillo          #+#    #+#             */
/*   Updated: 2022/02/08 18:01:52 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_ITERATOR_HPP
#define MAP_ITERATOR_HPP

//https://www.cplusplus.com/reference/iterator/iterator/

namespace   ft
{

template < class Key,											// map::key_type
		   class T,												// map::mapped_type
		   class Compare,										// map::key_compare
		   typename Node,										// node struct
		   bool C > 											// 1 for const, 0 for regular
class map_iterator
{
	public :
	
		typedef Key					key_type;
		typedef T					mapped_type;
		typedef	Compare				key_compare;
		typedef size_t				size_type;
		typedef std::ptrdiff_t		difference_type;
		// typedef	Node*				nodePtr;
		typedef ft::pair<const key_type, mapped_type>				value_type;
		typedef typename std::bidirectional_iterator_tag			iterator_category;;
		typedef value_type				*pointer;
		typedef value_type				&reference;

	private :

		Node*		_node;		//curent node pointed by iterator
		Node*		_last;		//pointer to NULL pointer Type Nil : non-existant leaves
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
			return (&_node->content);	
		}

		//++ operator goes from one key to the immediate superior one
		map_iterator&	operator++()
		{
			Node*	prevNode = _node;

			// iterator is starting on last, go back to root
			// if (_node == _last)
			// {
			// 	_node == _last->right;
			// 	return (*this);
			// }

			//until reaching last and while prev >= node, we ++ (see ft::less in utils)
			while (_node != _last && !_comp(prevNode->data.first, _node->data.first))
			{
				//right child is last
				if (_node->right && _node->right == _last)
				{
					_node = _node->right;
				}
//cut some stuff				
				//right child is higher
				else if (_node->right && _comp(prevNode->data.first, _node->data.first))
				{
					_node = _node->right;

					Node* 	tmp = 0;
					if ((tmp = searchMin(_node)))
						_node = tmp;
				}
				//no right child, try again with parent
				else
					_node = _node->parent;
			}
			return (*this);

				
		}
			
		
	
};


};   //namespace end

#endif