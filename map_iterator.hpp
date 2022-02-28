/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 15:23:19 by fcavillo          #+#    #+#             */
/*   Updated: 2022/02/24 19:39:09 by fcavillo         ###   ########.fr       */
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
*	-	operator== and operator !=
*/


//Const iterators to do
namespace   ft
{

	//boolean is true is const
	template <bool isConst, typename falseConst, typename trueConst>
	struct chooseConst {};

	//sets 2nd parameter as ref and pointer
	template <typename falseConst, typename trueConst>
	struct chooseConst<false, falseConst, trueConst>
	{
		typedef falseConst type;
	};

	//sets 3rd parameter as (const) ref and pointer
	template <typename falseConst, typename trueConst>
	struct chooseConst<true, falseConst, trueConst>
	{
		typedef trueConst type;
	};

template < class Key,											// map::key_type
		   class T,												// map::mapped_type
		   class Compare,										// map::key_compare
		   typename Node, 										// node struct
		   bool Con>											//1 if const
class map_iterator
{
	public :
	
		typedef Key					key_type;
		typedef T					mapped_type;
		typedef	Compare				key_compare;
		typedef size_t				size_type;
		typedef std::ptrdiff_t		difference_type;
		typedef ft::pair<const key_type, mapped_type>								value_type;
		typedef typename std::bidirectional_iterator_tag							iterator_category;;
  		typedef typename chooseConst<Con, value_type&, const value_type&>::type		reference;
		typedef typename chooseConst<Con, value_type*, const value_type*>::type		pointer;
			
			
	private :
	
		Node*		_node;		//curent node pointed by iterator
		Node*		_last;		//pointer to NULL pointer Type Nil : non-existant leaves, past-the-end element
		key_compare	_comp;		//used way of comparing keys to sort the map, needed to know wich way to iterate

	public :

	/*	CONSTRUCTORS, DESTRUCTOR, OPERATOR=	*/

		//default constructor, creates an iterator to the parameter node
		//if the parameters are not sent, default set to 0
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
			if (this != &rhs)
			{
				_node = rhs.getNode();
				_last = rhs.getLast();
				_comp = rhs.getComp();		
			}
			return (*this);
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
// std::cout << "preincrement boii" << std::endl;
			//iterator is starting on _last (rend() or end()), go back to min
			if (_node == _last)
			{
				_node = _last->right;
				return (*this);
			}
// std::cout << "1" << std::endl;
			//until reaching last and while prev >= node, we ++ (see ft::less in utils)
			while (_node != _last && !_comp(prevNode->data.first, _node->data.first))
			{
// std::cout << "2" << std::endl;
				//right child is last
				if (_node->right && _node->right == _last)
				{
// std::cout << "3" << std::endl;
					_node = _node->right;
				}
//cut some stuff
				//there is a right child : immediate higher node is right subtree's min
				else if (_node->right && _comp(prevNode->data.first, _node->right->data.first))
				{
// std::cout << "4" << std::endl;
					_node = _node->right;

					Node* 	tmp = 0;
//~~maybe _node can directly be set to lowest, no need for tmp
					if ((tmp = lowestNode(_node)))
						_node = tmp;
				}
				//no right child, try again from parent
//or go up until I am a left child
				else
				{
					Node*	parentNode = _node->parent;
					while (_node != parentNode->left)
					{
						_node = parentNode;
						parentNode = parentNode->parent;
					}
					_node = parentNode;
					return (*this);
					// std::cout << "5" << std::endl;
					// _node = _node->parent : old way
				}
			}
// std::cout << "9" << std::endl;
			return (*this);
		}

		//++ post-increment operator goes from one key to the immediate superior one
		map_iterator	operator++(int)
		{
// std::cout << "0" << std::endl;
			map_iterator	ret(*this);
// std::cout << "1" << std::endl;
			//iterator is starting on last, go back to min
			if (_node == _last)
			{
				_node = _last->right;
// std::cout << "++ to key " << _node->data.first << " wich is after last : " << (_node == _last) << std::endl;
				return (ret);
			}
// std::cout << "2" << std::endl;
			
			//until reaching last and while prev >= node, we ++ (see ft::less in utils)
			while (_node != _last && !_comp(ret->first, _node->data.first))
			{
// std::cout << "3" << std::endl;
				//right child is _last
				if (_node->right && _node->right == _last)
				{
// std::cout << "6" << std::endl;
					_node = _node->right;
				}
//cut some stuff
				//there is a right child : immediate higher node is right subtree's min
				else if (_node->right && _comp(ret->first, _node->right->data.first))
				{
// std::cout << "7" << std::endl;
					_node = _node->right;

					Node* 	tmp = 0;
					if ((tmp = lowestNode(_node)))
						_node = tmp;
				}
				//no right child, try again from parent
				else
				{
					Node*	parentNode = _node->parent;
					while (_node != parentNode->left)
					{
						_node = parentNode;
						parentNode = parentNode->parent;
					}
					_node = parentNode;
					return (ret);
// std::cout << "5" << std::endl;
					// _node = _node->parent : old way
				}
			}
// std::cout << "++ to key " << _node->data.first << " node is last : " << (_node == _last) << std::endl;
			return (ret);	
		}

		//-- pre-decrement operator goes from one key to the immediate inferior one
		map_iterator&	operator--()
		{
			Node*	prevNode = _node;

			//iterator is starting on _last (rend() or end()), go back to max
			if (_node == _last)
			{
				_node = _last->left;
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
				else if (_node->left && _comp(_node->left->data.first, prevNode->data.first))
				{
					_node = _node->left;

					Node* 	tmp = 0;
					if ((tmp = highestNode(_node)))
						_node = tmp;
				}
				//no right child, try again from parent
//or go up until I am a right child
				else
				{
					Node*	parentNode = _node->parent;
					while (_node != parentNode->right)
					{
						_node = parentNode;
						parentNode = parentNode->parent;
					}
					_node = parentNode;
					return (*this);
// std::cout << "5" << std::endl;
					// _node = _node->parent : old way
				}
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
				_node = _last->left;
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
				else if (_node->left && _comp(_node->left->data.first, ret->first))
				{
					_node = _node->left;

					Node* 	tmp = 0;
					if ((tmp = highestNode(_node)))
						_node = tmp;
				}
				//no right child, try again from parent
				else
				{
					Node*	parentNode = _node->parent;
					while (_node != parentNode->right)
					{
						_node = parentNode;
						parentNode = parentNode->parent;
					}
					_node = parentNode;
					return (ret);
// std::cout << "5" << std::endl;
					// _node = _node->parent : old way
				}
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
				return (highestNode(root->right));
			return (root);
		}
	
};

// template < class Key,											// map::key_type
// 		   class T,												// map::mapped_type
// 		   class Compare,										// map::key_compare
// 		   typename Node >										// node struct
// class map_const_iterator
// {
// 	public :
	
// 		typedef Key					key_type;
// 		typedef T					mapped_type;
// 		typedef	Compare				key_compare;
// 		typedef size_t				size_type;
// 		typedef std::ptrdiff_t		difference_type;
// 		typedef ft::pair<const key_type, mapped_type>				value_type;
// 		typedef typename std::bidirectional_iterator_tag			iterator_category;;
// 		typedef const value_type				*pointer;
// 		typedef const value_type				&reference;

// //	private :
// //set back quick boiiiii
// 		Node*		_node;		//curent node pointed by iterator
// 		Node*		_last;		//pointer to NULL pointer Type Nil : non-existant leaves, past-the-end element
// 		key_compare	_comp;		//used way of comparing keys to sort the map, needed to know wich way to iterate

// 	public :

// 	/*	CONSTRUCTORS, DESTRUCTOR, OPERATOR=	*/

// 		//default constructor, creates an iterator to the parameter node
// 		//if the parameters are not sent, defult set to 0
// 		map_const_iterator(Node* node = 0, Node* last = 0, const key_compare& comp = key_compare()) :
// 		_node(node),
// 		_last(last),
// 		_comp(comp)
// 		{
// 			return ;
// 		}

// 		//copy const
// 		map_const_iterator(const map_const_iterator<Key, T, Compare, Node>& copy)
// 		{
// 			_node = copy.getNode();
// 			_last = copy.getLast();
// 			_comp = copy.getComp();
// 			return ;
// 		}
// //nonononono this may be very bad an forbidden \/
// 		// map_const_iterator(const map_iterator<Key, T, Compare, Node>& copy)
// 		// {
// 		// 	_node = copy.getNode();
// 		// 	_last = copy.getLast();
// 		// 	_comp = copy.getComp();
// 		// 	return ;
// 		// }
		
// 		//nothing is ever allocated inside an iterator, it acts like a pointer
// 		~map_const_iterator()
// 		{
// 			return ;
// 		}

// 		map_const_iterator& operator=(const map_const_iterator& rhs)
// 		{
// 			if (this != &rhs)
// 			{
// 				_node = rhs.getNode();
// 				_last = rhs.getLast();
// 				_comp = rhs.getComp();		
// 			}
// 			return (*this);
// 		}

// 	/*	GETTERS	*/

// 		Node*	getNode() const
// 		{
// 			return (_node);
// 		}

// 		Node*	getLast() const
// 		{
// 			return (_last);
// 		}

// 		key_compare	getComp() const
// 		{
// 			return (_comp);
// 		}
	
// 	/*	MEMBER FUNCTION : OPERATORS	*/

// 		reference	operator*() const
// 		{
// 			return (_node->data);
// 		}
		
// 		pointer		operator->() const
// 		{
// 			return (&_node->data);	
// 		}

// 		//++ pre-increment operator goes from one key to the immediate superior one
// 		map_const_iterator&	operator++()
// 		{
// 			Node*	prevNode = _node;
// // std::cout << "preincrement boii" << std::endl;
// 			//iterator is starting on _last (rend() or end()), go back to min
// 			if (_node == _last)
// 			{
// 				_node = _last->right;
// 				return (*this);
// 			}
// // std::cout << "1" << std::endl;
// 			//until reaching last and while prev >= node, we ++ (see ft::less in utils)
// 			while (_node != _last && !_comp(prevNode->data.first, _node->data.first))
// 			{
// // std::cout << "2" << std::endl;
// 				//right child is last
// 				if (_node->right && _node->right == _last)
// 				{
// // std::cout << "3" << std::endl;
// 					_node = _node->right;
// 				}
// //cut some stuff
// 				//there is a right child : immediate higher node is right subtree's min
// 				else if (_node->right && _comp(prevNode->data.first, _node->right->data.first))
// 				{
// // std::cout << "4" << std::endl;
// 					_node = _node->right;

// 					Node* 	tmp = 0;
// //~~maybe _node can directly be set to lowest, no need for tmp
// 					if ((tmp = lowestNode(_node)))
// 						_node = tmp;
// 				}
// 				//no right child, try again from parent
// //or go up until I am a left child
// 				else
// 				{
// 					Node*	parentNode = _node->parent;
// 					while (_node != parentNode->left)
// 					{
// 						_node = parentNode;
// 						parentNode = parentNode->parent;
// 					}
// 					_node = parentNode;
// 					return (*this);
// 					// std::cout << "5" << std::endl;
// 					// _node = _node->parent : old way
// 				}
// 			}
// // std::cout << "9" << std::endl;
// 			return (*this);
// 		}

// 		//++ post-increment operator goes from one key to the immediate superior one
// 		map_const_iterator	operator++(int)
// 		{
// // std::cout << "0" << std::endl;
// 			map_const_iterator	ret(*this);
// // std::cout << "1" << std::endl;
// 			//iterator is starting on last, go back to min
// 			if (_node == _last)
// 			{
// 				_node = _last->right;
// // std::cout << "++ to key " << _node->data.first << " wich is after last : " << (_node == _last) << std::endl;
// 				return (ret);
// 			}
// // std::cout << "2" << std::endl;
			
// 			//until reaching last and while prev >= node, we ++ (see ft::less in utils)
// 			while (_node != _last && !_comp(ret->first, _node->data.first))
// 			{
// // std::cout << "3" << std::endl;
// 				//right child is _last
// 				if (_node->right && _node->right == _last)
// 				{
// // std::cout << "6" << std::endl;
// 					_node = _node->right;
// 				}
// //cut some stuff
// 				//there is a right child : immediate higher node is right subtree's min
// 				else if (_node->right && _comp(ret->first, _node->right->data.first))
// 				{
// // std::cout << "7" << std::endl;
// 					_node = _node->right;

// 					Node* 	tmp = 0;
// 					if ((tmp = lowestNode(_node)))
// 						_node = tmp;
// 				}
// 				//no right child, try again from parent
// 				else
// 				{
// 					Node*	parentNode = _node->parent;
// 					while (_node != parentNode->left)
// 					{
// 						_node = parentNode;
// 						parentNode = parentNode->parent;
// 					}
// 					_node = parentNode;
// 					return (ret);
// // std::cout << "5" << std::endl;
// 					// _node = _node->parent : old way
// 				}
// 			}
// // std::cout << "++ to key " << _node->data.first << " node is last : " << (_node == _last) << std::endl;
// 			return (ret);	
// 		}

// 		//-- pre-decrement operator goes from one key to the immediate inferior one
// 		map_const_iterator&	operator--()
// 		{
// 			Node*	prevNode = _node;

// 			//iterator is starting on _last (rend() or end()), go back to max
// 			if (_node == _last)
// 			{
// 				_node = _last->left;
// 				return (*this);
// 			}
			
// 			//until reaching last and while prev <= node, we -- (see ft::less in utils)
// 			while (_node != _last && !_comp(_node->data.first, prevNode->data.first))
// 			{
// 				//left child is _last
// 				if (_node->left && _node->left == _last)
// 				{
// 					_node = _node->left;
// 				}
// //cut some stuff
// 				//there is a left child : immediate lower node is left subtree's max
// 				else if (_node->left && _comp(_node->left->data.first, prevNode->data.first))
// 				{
// 					_node = _node->left;

// 					Node* 	tmp = 0;
// 					if ((tmp = highestNode(_node)))
// 						_node = tmp;
// 				}
// 				//no right child, try again from parent
// //or go up until I a; a right child
// 				else
// 				{
// 					Node*	parentNode = _node->parent;
// 					while (_node != parentNode->right)
// 					{
// 						_node = parentNode;
// 						parentNode = parentNode->parent;
// 					}
// 					_node = parentNode;
// 					return (*this);
// // std::cout << "5" << std::endl;
// 					// _node = _node->parent : old way
// 				}
// 			}
// 			return (*this);
// 		}

// 		//-- post-decrement operator goes from one key to the immediate inferior one
// 		map_const_iterator	operator--(int)
// 		{
// 			map_const_iterator	ret(*this);

// 			// iterator is starting on last, go back to root
// 			if (_node == _last)
// 			{
// 				_node = _last->left;
// 				return (ret);
// 			}
			
// 			//until reaching last and while prev <= node, we -- (see ft::less in utils)
// 			while (_node != _last && !_comp(_node->data.first, ret->first))
// 			{
// 				//left child is _last
// 				if (_node->left && _node->left == _last)
// 				{
// 					_node = _node->left;
// 				}
// //cut some stuff
// 				//there is a left child : immediate lower node is left subtree's max
// 				else if (_node->left && _comp(_node->left->data.first, ret->first))
// 				{
// 					_node = _node->left;

// 					Node* 	tmp = 0;
// 					if ((tmp = highestNode(_node)))
// 						_node = tmp;
// 				}
// 				//no right child, try again from parent
// 				else
// 				{
// 					Node*	parentNode = _node->parent;
// 					while (_node != parentNode->right)
// 					{
// 						_node = parentNode;
// 						parentNode = parentNode->parent;
// 					}
// 					_node = parentNode;
// 					return (ret);
// // std::cout << "5" << std::endl;
// 					// _node = _node->parent : old way
// 				}
// 			}
// 			return (ret);
// 		}

// 		bool	operator==(const map_const_iterator& rhs) const
// 		{
// 			return (rhs._node == _node);
// 		}

// 		bool	operator!=(const map_const_iterator& rhs) const
// 		{
// 			return (rhs._node != _node);
// 		}

// 	/*	IS_CONST_IT	*/
// /*	
// 		//this struct is assigned a type and a result
// 		template <bool is_const_it, typename T>
// 		struct is_const_it_res
// 		{
// 			typedef T			type;
// 			static const bool 	value = is_const_it;
// 		};
		
// 		//I expect a false if nothing is sent to the function
// 		template <typename>
// 			struct is_const_it_type : public is_const_it_res<false, bool> {};

// 		//for example, I expect a true from a bool
// 		template <>
// 			struct is_const_it_type<bool> : public is_const_it_res<true, bool> {};

// 		template <>
// 			struct is_const_it_type<char> : public is_const_it_res<true, char> {};


// 		//general ft being called each time, going through is_const_it_type, then is_const_it_res
// 		template <typename T>
// 			struct is_const_it : public is_const_it_type<T> { };
// */
// 	/*	PRIVATE MEMBER FUNCTIONS	*/
	
// 	private :

// 		//returns the lowest key node from the root after recursive search
// 		Node*	lowestNode(Node* root)
// 		{
// 			if (root && root != _last && root->left && root->left != _last)
// 				return (lowestNode(root->left));
// 			return (root);
// 		}
	
// 		//returns the highest key node from the root after recursive search
// 		Node*	highestNode(Node* root)
// 		{
// 			if (root && root != _last && root->right && root->right != _last)
// 				return (highestNode(root->right));
// 			return (root);
// 		}
	
// };



};   //namespace end

#endif