/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 09:09:18 by cedmulle          #+#    #+#             */
/*   Updated: 2024/03/10 09:44:51 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

inline void cleanInput(std::string& input)
{
	size_t startPos = input.find_first_not_of(" \t");
	size_t endPos = input.find_last_not_of(" \t");

	if (startPos == std::string::npos)
		input.clear();
	else
		input = input.substr(startPos, endPos - startPos + 1);
}

void	signalHandler(int signum)
{
	std::cout << PURP "\n ❤️ Goodbye ❤️ \n" RST << std::endl;
	exit(signum);
}

void normalMode(RPN &rpn, std::string input)
{
	int result;

	try
	{
		rpn.rpn(input);
		result = rpn.getResult();
		std::cout << YLLW "Result of { "<< input << " } is: " LIME << result << RST << std::endl;
	}
	catch (RPN::TooManyOperandsException &e) { std::cout << e.what() << std::endl; }
	catch (RPN::NotEnoughOperandsException &e) { std::cout << e.what() << std::endl; }
	catch (RPN::DivisionByZeroException &e) { std::cout << e.what() << std::endl; }
	catch (RPN::InvalidValueException &e) { std::cout << e.what() << std::endl; }

	return;
}

void	interactiveMode(RPN &rpn)
{
	std::string	input;

	signal(SIGINT, signalHandler);

	while (true)
	{
		std::cout << GRY2 "Enter an RPN expression or 'exit' to quit: " RST << std::endl;
		std::getline(std::cin, input);
		cleanInput(input);

		if (input == "exit" || input == "EXIT" || std::cin.eof())
		{
			std::cout << PURP "\n ❤️ Goodbye ❤️ \n" RST << std::endl;
			break ;
		}
		else if (!input.empty())
		{
			normalMode(rpn, input);
			std::cout << std::endl;
		}
		else
			std::cout << ORNG "Invalid input!" RST << std::endl;
	}
}

int	main(int argc, char **argv)
{
	std::cout << CLRALL << std::endl;

	RPN	rpn;
	
	if (argc == 1)
		interactiveMode(rpn);
	else if (argc == 2)
		normalMode(rpn, argv[1]);
	else
	{
		std::cout << YLLW "Usage error:\n";
		std::cout << ORNG "./rpn\t\t\t" << GRY1 "// For interactive mode\n" RST;
		std::cout << ORNG "./rpn <rpn_expression>\t" << GRY1 "// For normal mode\n\n" RST;
		return (1);
	}

	std::cout << std::endl;

	return (0);
}
