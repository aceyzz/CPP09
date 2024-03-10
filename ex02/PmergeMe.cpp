/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 10:14:05 by cedmulle          #+#    #+#             */
/*   Updated: 2024/03/10 12:06:50 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}
PmergeMe::~PmergeMe() {}
PmergeMe::PmergeMe(const PmergeMe& src) { *this = src;}
PmergeMe& PmergeMe::operator=(const PmergeMe& src)
{
	if (this != &src)
	{
		_vec = src._vec;
		_list = src._list;
	}
	return *this;
}

int	PmergeMe::convertToInt(const std::string &str)
{
	try { return std::stoi(str); }
	catch (std::invalid_argument &e) { throw InvalidValueException(); }
	catch (std::out_of_range &e) { throw InvalidValueException(); }
}

void PmergeMe::parseNumbers(int argc, char **argv)
{
	int num;
	std::set<int> uniqueNumbers;

	argv++;

	for (int i = 0; i < argc - 1; i++)
	{
		try
		{
			num = convertToInt(argv[i]);

			if (uniqueNumbers.find(num) != uniqueNumbers.end())
				throw DuplicateException();

			uniqueNumbers.insert(num);
			_vec.push_back(num);
			_list.push_back(num);
		}
		catch (std::exception &e) { std::cerr << e.what() << std::endl; }
	}
	if (_vec.empty()) throw EmptyVectorException();
	if (_list.empty()) throw EmptyListException();
}

void	PmergeMe::printer(const std::string &message)
{
	std::cout << GRY1 "############# " ORNG << message << GRY1 " #############" RST << std::endl;
	
	std::vector<int>::iterator itv = _vec.begin();
	std::cout << GRY2 "Vector: (" GOLD << _vec.size() << GRY2 " elements)\n[ " MAGN;
	while (itv != _vec.end())
	{
		std::cout << *itv << " ";
		itv++;
	}
	std::cout << GRY2 "]" RST << std::endl;

	std::list<int>::iterator itl = _list.begin();
	std::cout << GRY2 "List: (" GOLD << _vec.size() << GRY2 " elements)\n[ " CYAN;
	while (itl != _list.end())
	{
		std::cout << *itl << " ";
		itl++;
	}
	std::cout << GRY2 "]" RST << std::endl << std::endl;
}

void	PmergeMe::myMergeSortVector(std::vector<int> &vec)
{
	std::vector<int>	left;
	std::vector<int>	right;
	size_t				middle;

	if (vec.size() <= 1)
		return;

	middle = vec.size() / 2;

	for (size_t i = 0; i < middle; i++)
		left.push_back(vec[i]);

	for (size_t i = middle; i < vec.size(); i++)
		right.push_back(vec[i]);

	myMergeSortVector(left);
	myMergeSortVector(right);
	vec = mergeVector(left, right);
}

std::vector<int>	PmergeMe::mergeVector(std::vector<int> &left, std::vector<int> &right)
{
	std::vector<int> result;

	while (left.size() > 0 || right.size() > 0)
	{
		if (left.size() > 0 && right.size() > 0)
		{
			if (left.front() <= right.front())
			{
				result.push_back(left.front());
				left.erase(left.begin());
			}
			else
			{
				result.push_back(right.front());
				right.erase(right.begin());
			}
		}
		else if (left.size() > 0)
		{
			for (size_t i = 0; i < left.size(); i++)
				result.push_back(left[i]);
			break;
		}
		else if (right.size() > 0)
		{
			for (size_t i = 0; i < right.size(); i++)
				result.push_back(right[i]);
			break;
		}
	}
	return (result);
}

void	PmergeMe::myMergeSortList(std::list<int> &list)
{
    if (list.size() <= 1)
        return;

    std::list<int> left, right;
    size_t middle = list.size() / 2;
    std::list<int>::iterator it = list.begin();

    // Divisez la liste en deux moitiés : left et right
    for (size_t i = 0; i < middle; ++i) {
        left.push_back(*it++);
    }
    for (size_t i = middle; i < list.size(); ++i) {
        right.push_back(*it++);
    }

    // Tri récursif des deux moitiés
    myMergeSortList(left);
    myMergeSortList(right);

    // Fusion des deux moitiés triées
    list = mergeList(left, right);
}

std::list<int> PmergeMe::mergeList(std::list<int>& left, std::list<int>& right)
{
	std::list<int> result;

	while (!left.empty() && !right.empty())
	{
		if (left.front() <= right.front())
		{
			result.push_back(left.front());
			left.pop_front();
		}
		else
		{
			result.push_back(right.front());
			right.pop_front();
		}
	}

	// Append the remaining elements from the non-empty list
	while (!left.empty())
	{
		result.push_back(left.front());
		left.pop_front();
	}

	while (!right.empty())
	{
		result.push_back(right.front());
		right.pop_front();
	}

	return (result);
}

void	PmergeMe::fordJohnson()
{
	struct timeval start, end;
	std::vector<int> vec;
	std::list<int> list;

	double seconds;

	vec = _vec;
	list = _list;

	gettimeofday(&start, NULL);
	myMergeSortVector(vec);
	_vec = vec;
	gettimeofday(&end, NULL);
	seconds = (end.tv_usec - start.tv_usec) / 1000000.0;
	std::cout << GRY2 "Vector sorted in " GOLD << (end.tv_usec - start.tv_usec) << GRY2 " microseconds " RST;
	std::cout << GRY2 "(" GOLD << seconds << GRY2 " seconds)\n" RST;
	std::cout << GRY2 "Started at : " ORNG << start.tv_usec << std::endl;
	std::cout << GRY2 "Ended at :   " ORNG << end.tv_usec << std::endl;

	std::cout << std::endl;

	gettimeofday(&start, NULL);
	myMergeSortList(list);
	_list = list;
	gettimeofday(&end, NULL);
	seconds = (end.tv_usec - start.tv_usec) / 1000000.0;
	std::cout << GRY2 "List sorted in " GOLD << (end.tv_usec - start.tv_usec) << GRY2 " microseconds " RST;
	std::cout << GRY2 "(" GOLD << seconds << GRY2 " seconds)\n" RST;
	std::cout << GRY2 "Started at : " ORNG << start.tv_usec << std::endl;
	std::cout << GRY2 "Ended at :   " ORNG << end.tv_usec << std::endl;
	
	std::cout << std::endl;
}

bool PmergeMe::isSortedList() const
{
	std::list<int>::const_iterator it = _list.begin();
	std::list<int>::const_iterator it2 = _list.begin();

	it2++;

	while (it2 != _list.end())
	{
		if (*it > *it2)
			return false;
		it++;
		it2++;
	}
	return true;
}

bool PmergeMe::isSortedVector() const
{
	std::vector<int>::const_iterator it = _vec.begin();
	std::vector<int>::const_iterator it2 = _vec.begin();

	it2++;

	while (it2 != _vec.end())
	{
		if (*it > *it2)
			return false;
		it++;
		it2++;
	}
	return true;
}

// Fonction orchestrale entree du programme
void	PmergeMe::pmerge(int argc, char **argv)
{
	parseNumbers(argc, argv);
	printer("BEFORE");
	fordJohnson();
	printer("AFTER");
}
