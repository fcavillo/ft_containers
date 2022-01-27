/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 01:24:09 by fcavillo          #+#    #+#             */
/*   Updated: 2022/01/27 17:01:48 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"
#include <vector>

// when inserting then deleting, double free

int		main()
{
	 ft::vector<std::string>	vect(5);
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