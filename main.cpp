/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 01:24:09 by fcavillo          #+#    #+#             */
/*   Updated: 2022/02/18 18:46:43 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"
#include "stack.hpp"
#include <vector>
#include <list>
#include <map>
#include "map.hpp"






int		main()
{
	// ft::map<int, char>	mp1;
	// ft::map<int, char>	mp2;


	// mp1['a'] = 2; mp1['b'] = 3; mp1['c'] = 4; mp1['d'] = 5;
	// mp2['a'] = 2; mp2['b'] = 3; mp2['c'] = 4; mp2['d'] = 5;
	
	// if (mp1 == mp2)
	// 	std::cout << "equal" << std::endl;
	// else
	// 	std::cout << "not equal" << std::endl;
	// 
//	ft::map<int, char>	map;

	ft::map<int, char>  map2;

	for (int i = 0; i < 10; i++)
		map2[i] = i + 97;

	// ft::map<int, char> const	map(map2);
	// ft::map<int, char>  map3;


	// ft::map<int, char>::const_iterator	it = map.begin();
	// ft::map<int, char>::const_iterator	ite = map.end();
	ft::map<int, char>::iterator	it2 = map2.begin();
	ft::map<int, char>::iterator	ite2 = map2.end();
	// ft::map<int, char>::reverse_iterator	rit2 = map2.rbegin();
	// ft::map<int, char>::reverse_iterator	rite2 = map2.rend();

	// rite2--;
	// std::cout << rit2->first << rite2->first << std::endl;
	// map3.insert(map2.begin(), map2.end());
	
	// ft::map<int, char>::iterator	it2 = map.begin();
	// ft::map<int, char>::iterator	ite2 = map.end();

	// ft::pair<int, char> pair = ft::make_pair<int, char>(2, 'u');
	
	// map.insert(it2, pair);
	for (; it2 != ite2; it2++)
		std::cout << "[" << it2->first << "] " << it2->second << std::endl;
	// for (; rit2 != rite2; rit2++)
	// 	std::cout << "[" << rit2->first << "] " << rit2->second << std::endl;	
	// it = map.begin();
	// map.erase(it2);
	// map.erase(--(--(--map.end())), --map.end());

	// ft::map<int, char>::iterator	it2 = map.begin();
	// ft::map<int, char>::iterator	ite2 = map.end();

	// map.erase(--(--(--map.end())), --map.end());
	
	// for (int i = 0; i < 15; i++)
	// {
	// 	std::cout << "[" << it2->first << "] " << it2->second << std::endl;
	// 	it2++;
	// }
	// // map.debug_print_btree_structure_(map.begin()._node, 1);
	// // ft::map<int, char>::const_iterator	const_ite;
	// // const_ite  = map.begin();
	
	// std::map<int, char>	map2;

	// for (int i = 0; i < 10; i++)
	// 	map[i] = i + 97;
	// std::map<int, char>::const_iterator	it3(map2.begin());
	// it3 = map2.begin();

	// ft::map<int, char>	map3;

	// for (int i = 0; i < 10; i++)
	// 	map[i] = i + 97;

	// std::cout << "hey" << std::endl;
	// ft::map<int, char>::const_iterator	it3a(map3.begin());
	// it3a = map3.begin();
	// std::cout << "hoy" << std::endl;
	
	// for (; it != ite; it++)
	// 	std::cout << "[" << it->first << "] " << it->second << std::endl;

	// ft::map<int, char>	map2(map.begin(), map.end());

	// ft::map<int, char>::iterator	it2 = map2.begin();
	// ft::map<int, char>::iterator	ite2 = map2.end();
	
	// map2.erase(map2.begin());
	// it2 = map2.begin();
	// for (; it2 != ite2; it2++)
	// 	std::cout << "[" << it2->first << "] " << it2->second << std::endl;

	// map[4] = 'd';
	// std::cout << "test" << std::endl;

	// map[1] = 'b';
	// // std::cout << map[0] << std::endl;
	// // std::cout << map[1] << std::endl;

	// map[2] = (map.begin())->second;
	// // std::cout << map[0] << std::endl;
	// map[1] = 'a';

	// ft::map<int, char>::iterator it;
	// it = map.begin();
	// std::cout << "1[" << it->first << "] " << it->second << std::endl;
	// ++it;
	// std::cout << "2[" << it->first << "] " << it->second << std::endl;
	// ++it;	
	// std::cout << "3[" << it->first << "] " << it->second << std::endl;
	// --it;
	// std::cout << "2[" << it->first << "] " << it->second << std::endl;
	// --it;	
	// std::cout << "1[" << it->first << "] " << it->second << std::endl;
	// it++;
	// std::cout << "2[" << it->first << "] " << it->second << std::endl;
	// it++;	
	// std::cout << "3[" << it->first << "] " << it->second << std::endl;
	// it--;
	// std::cout << "2[" << it->first << "] " << it->second << std::endl;
	// it--;	
	// std::cout << "1[" << it->first << "] " << it->second << std::endl;

	// ft::map<int, char>::iterator ite;
	// it = map.end();
	// std::cout << "end[" << it->first << "] " << it->second << std::endl;
	// --it;
	// std::cout << "3[" << it->first << "] " << it->second << std::endl;
	// --it;	
	// std::cout << "2[" << it->first << "] " << it->second << std::endl;
	// std::cout << "size = " << map.size() << "\tempty = " << map.empty() << "\tmax-size = " << map.max_size() << std::endl;

	// it = map.upper_bound(2);
	// std::cout << "[" << it->first << "] " << it->second << std::endl;
	
	// ft::map_iterator<int, char, ft::less<int>, ft::map<int, char, ft::less<int>, std::__1::allocator<ft::pair<const int, char> > >::Node, false> it;
	// std::list<int> lst;
	// unsigned int lst_size = 7;
	// for (unsigned int i = 0; i < lst_size; ++i)
	// 	lst.push_back('a' + i);

	// std::cout << *(lst.begin()) << std::endl;
	// ft::map<int, int> mp(lst.begin(), lst.end());

/*	 ft::vector<std::string>	vect(5);
	//  std::vector<int>	vect;
	// ft::vector<int>	vect2(5, 3);
	// std::vector<int>		rvect;
	std::cout << "1" << std::endl;
	//  vect.push_back(2);
	//  vect.push_back(3);
	//  vect.push_back(4);
	for (unsigned long int i = 0; i < vect.size(); ++i)
		vect[i] = std::string((vect.size() - i), i + 65);
	for (size_t i = 0; i < vect.size(); i++)
		std::cout << vect[i] << std::endl;	
//	vect.assign(2, 5);
	 std::cout << "2" << std::endl;
	// for (size_t i = 0; i < vect.size(); i++)
	// 	std::cout << vect[i] << std::endl;
	// vect.erase(vect.begin());
	// for (size_t i = 0; i < vect.size(); i++)
	// 	std::cout << vect[i] << std::endl;
	static int i = 0;
	vect.erase(vect.begin());
	 std::cout << "2.3" << std::endl;
	vect.erase(vect.begin() + 2);
	 std::cout << "2.5" << std::endl;
	std::cout << "[" << i++ << "] " << "erase: " << (vect.erase(vect.begin() + 2)) - vect.begin() << std::endl;
	for (size_t i = 0; i < vect.size(); i++)
		std::cout << vect[i] << std::endl;	
	std::cout << "2" << std::endl;
	std::cout << "size: " << vect.size() << std::endl;
	std::cout << "capacity: " << vect.capacity() << std::endl;
	std::cout << "max_size: " << vect.max_size() << std::endl;

	ft::stack<int>	st;
	ft::stack<int>	st2(st);

	if (st == st2)
		std::cout << "sameeeee" << std::endl;*/
	// ft::vector<int>		vect2(vect);
	// std::cout << "vct[0] = " << vect2[0] << std::endl;
	// std::cout << "3" << std::endl;
	// std::cout << "f = ";
	// std::cout << vect2.front() << std::endl;
	// std::cout << "e = ";
	// std::cout << vect2.end() << std::endl;
	

// 	for (size_t i = 0; i < vect2.size(); i++)
// 		std::cout << vect2[i] << std::endl;
// 	for (size_t i = 0; i < vect.size(); i++)
// 		std::cout << vect[i] << std::endl;
// // 	ft::vector<int> vct(7);
// //	std::cout << vct << std::endl;
// //	std::vector<int>		vct(5);
// 	for (unsigned long int i = 0; i < vct.size(); ++i)
// 	{
// //		std::cout << "i = " << i << " size = " << vct.size() << "* = " << (vct.size() - i) * 3 << std::endl;
// 		vct.at(i) = (vct.size() - i) * 3;
// 		std::cout << "vct.at(): " << vct.at(i) << " | ";
// 		std::cout << "vct[]: " << vct[i] << std::endl;
// 	}
// 	std::cout << "size: " << vct.size() << std::endl;
// 	std::cout << "capacity: " << vct.capacity() << std::endl;
// 	std::cout << "max_size: " << vct.max_size() << std::endl;

//	ft::vector<int> vct2;

	// const int cut = 3;

	// for (unsigned long int i = 0; i < vct.size(); ++i)
	// 	vct[i] = (vct.size() - i) * 7;
 	// std::cout << vct << " " << vct.size() << "/" << vct.capacity() << std::endl;
	// vct2.insert(vct2.begin(), vct.begin(), vct.begin() + cut);
 	// std::cout << vct2 << " " << vct2.size() << "/" << vct2.capacity() << std::endl;


// 	std::cout << vect2 << " " << vect2.size() << "/" << vect2.capacity() << std::endl;
// 	ft::vector<int>::iterator	it = vect2.begin();
// 	vect2.insert(it, 42);
// 	std::cout << vect2 << " " << vect2.size() << "/" << vect2.capacity() << std::endl;
// 	it++;
// 	std::cout << "insert done" << std::endl;
// 	vect2.erase(it);
// 	std::cout << "erase done" << std::endl;
// 	// std::cout << vect2 << " " << vect2.size() << "/" << vect2.capacity() << std::endl;

// 	try
// 	{
// 		rvect.pop_back();
// 	}
// 	catch(const std::exception& e)
// 	{
// 		std::cerr << "broken soul : " << e.what() << '\n';
// 	}
	
// 	std::cout << rvect.capacity() << " " << rvect.size() << " " << rvect.max_size() << std::endl;
// 	std::cout << vect << vect.size() << "/" << vect.capacity() << std::endl;
// 	std::cout << vect2 << vect.size() << "/" << vect.capacity() << std::endl;
	
// 	for (int i = 0; i < 20; i++)
// 	{
// 		vect.push_back(i);
// 		std::cout << vect << vect.size() << "/" << vect.capacity() << std::endl;
		
// 	}
// 	std::cout << "front : " << vect.front() << " back = " << vect.back() << " [3] = " << vect[3] << std::endl;	
// 	std::cout << "begin : " << *vect.begin() << " end = " << vect.back() << " [3] = " << vect[3] << std::endl;	
// 	ft::vector<int>	vect3 = vect;
// 	std::cout << "front : " << vect3.front() << " back = " << vect3.back() << " [3] = " << vect3[3] << std::endl;	
// //	vect3.erase(3);
// 		std::cout << vect << vect3.size() << "/" << vect.capacity() << std::endl;
// 	std::cout << "erased front : " << vect3.front() << " back = " << vect3.back() << " [3] = " << vect3[3] << std::endl;	
// //	vect3.insert()
// 		std::cout << vect << vect3.size() << "/" << vect.capacity() << std::endl;
// 	std::cout << "inserted front : " << vect3.front() << " back = " << vect3.back() << " [3] = " << vect3[3] << std::endl;	
// 	// while (!vect.empty())
// 	// {
// 	// 	vect.pop_back();
// 	// 	std::cout << vect << vect.size() << "/" << vect.capacity() << std::endl;
// 	// }

	return (0);
}
