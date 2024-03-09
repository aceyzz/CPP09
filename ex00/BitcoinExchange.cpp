/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 13:34:19 by cedmulle          #+#    #+#             */
/*   Updated: 2024/03/09 17:11:31 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(std::string dataBase)
: _filename(dataBase)
{
	try
	{
        parseData();
    }
	catch (const FileOpenException& e) {
        std::cerr << e.what() << std::endl;
    } catch (const InvalidDateFormatException& e) {
        std::cerr << e.what() << std::endl;
    } catch (const InvalidFormatException& e) {
        std::cerr << e.what() << std::endl;
    } catch (const LargeNumberException& e) {
        std::cerr << e.what() << std::endl;
    } catch (const OutOfRangeException& e) {
        std::cerr << e.what() << std::endl;
    } catch (const EmptyFileException& e) {
        std::cerr << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Erreur inattendue: " << e.what() << std::endl;// Au cas ou
    }
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &src)
{
	*this = src;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange &src)
{
	if (this != &src)
	{
		_filename = src._filename;
		_rates = src._rates;
	}
	return (*this);
}

BitcoinExchange::~BitcoinExchange() {}

bool	BitcoinExchange::isValidDate(const std::string &date)
{
	if (date.size() != 10) return (false);

	for (size_t i = 0; i < date.size(); i++)
	{
		if (i == 4 || i == 7)
		{
			if (date[i] != '-')
				return (false);
		}
		else
		{
			if (!isdigit(date[i]))
				return (false);
		}
	}

	int	year = std::atoi(date.substr(0, 4).c_str());
	int	month = std::atoi(date.substr(5, 2).c_str());
	int	day = std::atoi(date.substr(8, 2).c_str());

	if (year < 1900 || year > 2100) return (false);
	if (month < 1 || month > 12) return (false);
	if (day < 1 || day > 31) return (false);

	return (true);
}

void	BitcoinExchange::parseData()
{
	std::ifstream	file(_filename);
	if (!file.is_open())
		throw FileOpenException();
	
	std::string	line;
	getline(file, line);

	while (getline(file, line))
	{
		std::istringstream	iss(line);
		std::string			date;
		double				exchangeRate;

		std::getline(iss, date, ',');
		std::string		exchangeRateStr;
		std::getline(iss, exchangeRateStr);

		if (!isValidDate(date))
			throw InvalidDateFormatException();

		try {
			exchangeRate = std::stof(exchangeRateStr);
		} catch (const std::invalid_argument &e) {
			throw InvalidFormatException();
		} catch (const std::out_of_range &e) {
			throw LargeNumberException();
		}

		if (exchangeRate < 0.0f)
			throw OutOfRangeException();

		_rates[date] = exchangeRate;
	}
	file.close();

	if (_rates.empty())
		throw EmptyFileException();
}

std::pair<std::string, double>	BitcoinExchange::getExchangeRateForDate(const std::string &date)
{
	if (!isValidDate(date))
		throw InvalidDateFormatException();

	std::map<std::string, double>::const_iterator it = _rates.lower_bound(date);
	// pour etre sur de ne rien edit, const_iterator

	if (it == _rates.begin() && date < it->first)// Si pas de date antérieure
		throw DateNotFoundException();
	
	if (it == _rates.end() || it->first > date)// Si on a depassé la date
		--it;// on recule pour avoir la date antérieure
	
	return (std::make_pair(it->first, it->second));
}
