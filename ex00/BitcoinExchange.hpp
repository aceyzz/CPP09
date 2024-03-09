/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 13:23:02 by cedmulle          #+#    #+#             */
/*   Updated: 2024/03/09 17:11:57 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "colors.hpp"
#include <iostream>
#include <string>
#include <map>
#include <exception>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <utility>

#define DATAPATH "./db/data.csv"

class	BitcoinExchange
{
	public:
		BitcoinExchange(std::string dataBase);
		BitcoinExchange(const BitcoinExchange &src);
		BitcoinExchange& operator=(const BitcoinExchange &src);
		~BitcoinExchange();

		bool	isValidDate(const std::string &date);
		std::pair<std::string, double>	getExchangeRateForDate(const std::string &date);

		class	FileOpenException : public std::exception
		{
			public:
				virtual const char *what() const throw() { return (REDD "Impossible d'ouvrir le fichier!" RST); }
		};
		class	InvalidFormatException : public std::exception
		{
			public:
				virtual const char *what() const throw() { return (REDD "Format de fichier invalide!" RST); }
		};
		class	OutOfRangeException : public std::exception
		{
			public:
				virtual const char *what() const throw() { return (REDD "Valeur Out of Range!" RST); }
		};
		class	DateNotFoundException : public std::exception
		{
			public:
				virtual const char *what() const throw() { return (REDD "Date antérieure introuvable!" RST); }
		};
		class	InvalidDateFormatException : public std::exception
		{
			public:
				virtual const char *what() const throw() { return (REDD "Format de date invalide!" RST); }
		};
		class	LargeNumberException : public std::exception
		{
			public:
				virtual const char *what() const throw() { return (REDD "Nombre trop grand!" RST); }
		};
		class	EmptyFileException : public std::exception
		{
			public:
				virtual const char *what() const throw() { return (REDD "Fichier vide!" RST); }
		};
		class	ParsingErrorException : public std::exception
		{
			public:
				virtual const char *what() const throw() { return (REDD "Erreur de parsing!" RST); }
		};

	private:
		BitcoinExchange();

		void	parseData();

		std::string						_filename;
		std::map<std::string, double>	_rates;
};
