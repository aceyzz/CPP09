/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 08:51:55 by cedmulle          #+#    #+#             */
/*   Updated: 2024/03/10 09:24:19 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN() : _result(0) {}
RPN::~RPN() {}

RPN::RPN(const RPN &src)
{
	*this = src;
}

RPN& RPN::operator=(const RPN &src)
{
	if (this != &src)
	{
		_result = src._result;
		_stack = src._stack;
	}
	return (*this);
}

void RPN::rpn(const std::string formula)
{
	for (size_t i = 0; i < formula.length(); i++)
	{
		if (std::isdigit(formula[i]))
			_stack.push(formula[i] - '0');
		else if (_isOperator(formula[i]))
		{
			if (_stack.size() < 2)
				throw NotEnoughOperandsException();

			int b = _stack.top(); _stack.pop();
			int a = _stack.top(); _stack.pop();

			_doOperation(a, b, formula[i]);
			_stack.push(_result);
		}
		else if (formula[i] != ' ')
			throw InvalidValueException();
	}

	if (_stack.size() != 1 || formula.empty())
		throw TooManyOperandsException();

	_result = _stack.top(); _stack.pop();
}

bool	RPN::_isOperator(char c)
{
	return (c == '+' || c == '-' || c == '/' || c == '*');
}

void	RPN::_doOperation(int a, int b, char op)
{
	switch (op)
	{
		case '+':
			_result = a + b;
			break;
		case '-':
			_result = a - b;
			break;
		case '*':
			_result = a * b;
			break;
		case '/':
			if (a == 0 || b == 0)
				throw DivisionByZeroException();
			_result = (a / b);
			break;
		default:
			throw InvalidValueException();
	}
}

int	RPN::getResult() const
{
	return (_result);
}
