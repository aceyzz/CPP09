/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 10:01:23 by cedmulle          #+#    #+#             */
/*   Updated: 2024/03/10 11:52:10 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include <list>
#include <string>
#include <iostream>
#include <algorithm>
#include <sys/time.h>
#include <set>
#include "colors.hpp"

class	PmergeMe
{
	public:
		PmergeMe();
		PmergeMe(const PmergeMe& src);
		PmergeMe& operator=(const PmergeMe& src);
		~PmergeMe();

		void	pmerge(int argc, char **argv);// MAIN FUNCTION FOR SORTING

		bool	isSortedVector() const;
		bool	isSortedList() const;
	
		class	EmptyListException : public std::exception
		{
			public:
				virtual const char* what() const throw() { return (REDD "List is empty!" RST); }
		};
		class	EmptyVectorException : public std::exception
		{
			public:
				virtual const char* what() const throw() { return (REDD "Vector is empty!" RST); }
		};
		class	DuplicateException : public std::exception
		{
			public:
				virtual const char* what() const throw() { return (REDD "Duplicate detected!" RST); }
		};
		class	InvalidValueException : public std::exception
		{
			public:
				virtual const char* what() const throw() { return (REDD "Invalid value!" RST); }
		};

	private:
		std::vector<int>		_vec;
		std::list<int>			_list;

		int		convertToInt(const std::string &str);
		void	parseNumbers(int argc, char **argv);
		void	fordJohnson();

		std::vector<int>	mergeVector(std::vector<int> &left, std::vector<int> &right);
		std::list<int>		mergeList(std::list<int> &left, std::list<int> &right);

		void	myMergeSortVector(std::vector<int> &vec);
		void	myMergeSortList(std::list<int> &list);
		
		void	printer(const std::string &message);
};
