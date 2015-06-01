#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "FASTA.h"

using std::string;

FASTA::FASTA(std::string fileName)
{
	using std::ifstream;
	using std::cerr;
	using std::endl;

	ifstream inputFile(fileName);
	if (!inputFile.good())
	{
		cerr << "Error opening '" << fileName << "'." << endl;
		exit(1);
	}

	description.clear();
	content.clear();

	string line;
	while (std::getline(inputFile, line).good())
	{
		if (line[0] == '>')
		{
			description = line.substr(1);
		}
		else if (!description.empty())
		{
			if (line.find(' ') != string::npos)
			{
				cerr << "This file is not a FASTA format!\n"
					 << "There is ' ' in the file\n";
				exit(1);
			}
			content += line;
		}
	}
}


const string &FASTA::getDescription(void)
{
	return description;
}

const string &FASTA::getContent(void)
{
	return content;
}
