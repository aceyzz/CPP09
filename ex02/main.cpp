/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 11:04:25 by cedmulle          #+#    #+#             */
/*   Updated: 2024/03/10 12:07:18 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

/*

	Containers used :	std::list< int >
						std::vector< int >
						(aussi std::set< int > pour check duplicates)

*/

int	main(int argc, char **argv)
{
	std::cout << CLRALL;

	try
	{
        PmergeMe pmerge;
        pmerge.pmerge(argc, argv);

		if (pmerge.isSortedList())
			std::cout << GRNN "List is sorted!\n" RST;
		else
			std::cout << REDD "List is not sorted!\n" RST;

		if (pmerge.isSortedVector())
			std::cout << GRNN "Vector is sorted!\n\n" RST;
		else
			std::cout << REDD "Vector is not sorted!\n\n" RST;
    }
	catch (const std::exception& e)
	{
        std::cerr << std::endl << e.what() << std::endl << std::endl;
        return (1);
    }
    return (0);
}
