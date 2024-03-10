/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 08:49:35 by cedmulle          #+#    #+#             */
/*   Updated: 2024/03/10 09:06:49 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <iostream>
#include <stack>
#include <limits>
#include <exception>
#include "colors.hpp"

class	RPN
{
	public:
		RPN();
		RPN(const RPN &src);
		RPN& operator=(const RPN &src);
		~RPN();

		void	rpn(const std::string formula);
		int		getResult() const;
	
		class	TooManyOperandsException : std::exception
		{
			public:
				const char*	what() const throw() { return (REDD "Too many operands!" RST);}	
		};
		class	NotEnoughOperandsException : std::exception
		{
			public:
				const char*	what() const throw() { return (REDD "Not enough operands!" RST);}	
		};
		class	DivisionByZeroException : std::exception
		{
			public:
				const char*	what() const throw() { return (REDD "Division by zero!" RST);}	
		};
		class	InvalidValueException : std::exception
		{
			public:
				const char*	what() const throw() { return (REDD "Invalid value detected!" RST);}	
		};

	private:
		std::stack<int>	_stack;
		int				_result;

		bool	_isOperator(char c);
		void	_doOperation(int a, int b, char op);
};
