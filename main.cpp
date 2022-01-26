/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 01:24:09 by fcavillo          #+#    #+#             */
/*   Updated: 2022/01/21 05:14:50 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"
#include <vector>

// when inserting then deleting, double free

int		main()
{
	ft::vector<int>	vect;
	ft::vector<int>	vect2(5, 3);
	std::vector<int>		rvect;

	ft::vector<int> vct(5);
	ft::vector<int> vct2;

	const int cut = 3;

	for (unsigned long int i = 0; i < vct.size(); ++i)
		vct[i] = (vct.size() - i) * 7;
 	std::cout << vct << " " << vct.size() << "/" << vct.capacity() << std::endl;
	vct2.insert(vct2.begin(), vct.begin(), vct.begin() + cut);
 	std::cout << vct2 << " " << vct2.size() << "/" << vct2.capacity() << std::endl;


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