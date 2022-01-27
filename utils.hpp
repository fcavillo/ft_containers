/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 11:52:07 by fcavillo          #+#    #+#             */
/*   Updated: 2022/01/27 12:19:14 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
#define UTILS_HPP

namespace   ft
{

	/*	ENABLE_IF	*/
	//B is the condition, if true there is a member given to the function, preventing bad choices from the compiler
	template< bool B, class T = void >
	struct enable_if
	{};

	template<class T> 
	struct enable_if<true, T> 
	{ typedef T type; };

	/*	IS_INTEGRAL	*/
	
	//this struct is assigned a type and a result
	template <bool is_int, typename T>
	struct is_integral_res
	{
		typedef T			type;
		static const bool 	value = is_int;
	};
	
	//for this reconstruction of is_integral, same types will be handled as in C++98 and accepted as ints
	//for each one, I give the type and the result I want from the is_integral_res struct
	
	//I expect a false if nothing is sent to the function
	template <typename>
		struct is_integral_type : public is_integral_res<false, bool> {};

	//for example, I expect a true from a bool
	template <>
		struct is_integral_type<bool> : public is_integral_res<true, bool> {};

	template <>
		struct is_integral_type<char> : public is_integral_res<true, char> {};

	template <>
		struct is_integral_type<signed char> : public is_integral_res<true, signed char> {};

	template <>
		struct is_integral_type<short int> : public is_integral_res<true, short int> {};
	
	template <>
		struct is_integral_type<int> : public is_integral_res<true, int> {};

	template <>
		struct is_integral_type<long int> : public is_integral_res<true, long int> {};

	template <>
		struct is_integral_type<long long int> : public is_integral_res<true, long long int> {};

	template <>
		struct is_integral_type<unsigned char> : public is_integral_res<true, unsigned char> {};

	template <>
		struct is_integral_type<unsigned short int> : public is_integral_res<true, unsigned short int> {};

	template <>
		struct is_integral_type<unsigned int> : public is_integral_res<true, unsigned int> {};

	template <>
		struct is_integral_type<unsigned long int> : public is_integral_res<true, unsigned long int> {};
	
	template <>
		struct is_integral_type<unsigned long long int> : public is_integral_res<true, unsigned long long int> {};

	//general ft being called each time, going through is_integral_type, then is_integral_res
	template <typename T>
		struct is_integral : public is_integral_type<T> { };
	
}

#endif