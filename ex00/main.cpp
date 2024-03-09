/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmulle <cedmulle@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 15:03:15 by cedmulle          #+#    #+#             */
/*   Updated: 2024/03/09 17:47:34 by cedmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

/*

	Container used : std::map< std::string, double >
	
	- If 0 argument, goes into interactive mode
	- If 1 argument, goes into file mode
	- If more, error

*/

void fileMode(const std::string &filename, BitcoinExchange &btc)
{
    std::ifstream inputFile(filename.c_str());
    if (!inputFile.is_open())
	{
        std::cout << REDD "Fichier d'input non valide!" RST << std::endl;
        return;
    }

    std::string line;
    getline(inputFile, line);

    while (getline(inputFile, line))
	{
        std::istringstream lineStream(line);
        std::string date, valueStr;
        std::getline(lineStream, date, '|');
        std::getline(lineStream, valueStr);

        // Nettoyage des entrées
        date.erase(0, date.find_first_not_of(" \t"));
        date.erase(date.find_last_not_of(" \t") + 1);
        valueStr.erase(0, valueStr.find_first_not_of(" \t"));
        valueStr.erase(valueStr.find_last_not_of(" \t") + 1);

        if (!btc.isValidDate(date))
		{
            std::cout << ORNG "Erreur: Format de date invalide => " RST << date << std::endl;
            continue;
        }

        double value;
        try
		{
            value = std::stod(valueStr);
        }
		catch (...)
		{
            std::cout << REDD "Erreur: Format de valeur invalide => " RST << valueStr << std::endl;
            continue;
        }

        if (value < 0.0 || value > 100000.0)
		{
            std::cout << ORNG "Erreur: Valeur hors plage => " RST << value << std::endl;
            continue;
        }

        try
		{
            std::pair<std::string, double> rateInfo = btc.getExchangeRateForDate(date);
            std::string closestDate = rateInfo.first; // La date la plus proche utilisée.
            double rate = rateInfo.second;
            double convertedValue = value * rate;

            std::cout << std::fixed << std::setprecision(2);
            std::cout << CYAN << closestDate << " | " << value << " * " << rate << " = " << convertedValue << RST << std::endl;
        }
		catch (const BitcoinExchange::DateNotFoundException& e)
		{
            std::cout << REDD "Erreur: " RST << e.what() << " pour la date " << date << std::endl;
        }
    }
    inputFile.close();
}


void	processSingleLine(const std::string &line, BitcoinExchange &btc)
{
	std::istringstream lineStream(line);
	std::string date, valueStr;
	std::getline(lineStream, date, '|');
	std::getline(lineStream, valueStr);

	// Clean input
	date.erase(0, date.find_first_not_of(" \t"));
	date.erase(date.find_last_not_of(" \t") + 1);
	valueStr.erase(0, valueStr.find_first_not_of(" \t"));
	valueStr.erase(valueStr.find_last_not_of(" \t") + 1);

	// Validation du format de la date
	if (!btc.isValidDate(date))
	{
		std::cout << ORNG "Erreur: Format de date invalide => " RST << date << std::endl;
		return;
	}

	double value;
	// Validation du format de la valeur
	try
	{
		value = std::stod(valueStr);
	}
	catch (...)
	{
		std::cout << REDD "Erreur: Format de valeur invalide => " RST << valueStr << std::endl;
		return;
	}

	// Validation de la plage de la valeur
	if (value < 0.0 || value > 100000.0)
	{
		std::cout << ORNG "Erreur: Valeur hors plage => " RST << value << std::endl;
		return;
	}

	// Recherche du taux de change et calcul de la valeur convertie
	try
	{
        // La fonction retourne maintenant un pair avec la date et le taux
        std::pair<std::string, double> rateInfo = btc.getExchangeRateForDate(date);
        std::string closestDate = rateInfo.first; // Date la plus proche
        double rate = rateInfo.second; // Taux de change
        double convertedValue = value * rate;

        std::cout << std::fixed << std::setprecision(2);
        // Utiliser la date la plus proche retournée au lieu de celle entrée par l'utilisateur
        std::cout << LIME << closestDate << " | " << value << " * " << rate << " = " << convertedValue << RST << std::endl;
    }
	catch (const BitcoinExchange::DateNotFoundException& e)
	{
        std::cout << REDD "Erreur: " RST << e.what() << " pour la date " << date << std::endl;
    }
}

// Fonction pour gérer l'interruption CTRL+C
void signalHandler(int signum) { exit(signum); }

void interactiveMode(BitcoinExchange &btc)
{
	// Configuration signal CTRL+C
	signal(SIGINT, signalHandler);

	std::string line;
	while (1)
	{
		std::cout << GRY1 "Veuillez entrez votre la transaction:" << std::endl;
		std::cout << "Format: [YYYY-MM-DD | AMOUNT]" RST << std::endl;
		std::getline(std::cin, line);

		// Fin de fichier (EOF / Ctrl+D) ou "EXIT"
		if (std::cin.eof() || line == "EXIT" || line == "exit")
		{
			std::cout << PURP "\n\nBye bye ❤️\n\n" RST;
			break;
		}

		if (!line.empty())
		{
			processSingleLine(line, btc);
			std::cout << std::endl;
		}
	}
}

int	main(int argc, char **argv)
{
	std::cout << CLRALL;

	BitcoinExchange	btc(DATAPATH);

	if (argc == 1)
		interactiveMode(btc);
	else if (argc == 2)
		fileMode(argv[1], btc);
	else
	{
		std::cout << REDD << YLLW "\nUsage:\n";
		std::cout << ORNG "./btc <input_file>\t" GRY1 << "// For normal mode\n";
		std::cout << ORNG "./btc " << GRY1 << "\t\t\t// For interactive mode\n\n";
	}

	std::cout << std::endl;

	return (0);
}
