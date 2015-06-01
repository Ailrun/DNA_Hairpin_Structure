#include <iostream>
#include <stdexcept>
#include <string>
#include <cstring>
#include "DNAArg.h"

using std::string;

void DNAArg::invalidSetting(void)
{
	fileName = "";
	minimumLength = -1;
	loopLength = -1;
	mismatchNumber = -1;
}

int DNAArg::validSetting(char *optionk, char *optionv)
{
	using std::strlen;
	using std::strncmp;
	using std::stoi;
	using std::exception;

	if ((strlen(optionk) != 2 && strlen(optionk) != 6) || optionk[0] != '-')
	{
		return -1;
	}

	if (strlen(optionk) == 6)
	{
		fileName = optionv;
		return (strncmp((optionk+1), "input", 5)==0?0:-1);
	}

	try
	{
		switch (optionk[1])
		{
			case 'l' :
					 minimumLength = stoi(optionv);
					 return 1;
			case 'm' :
					 mismatchNumber = stoi(optionv);
					 return 2;
			case 'h' :
					 loopLength = stoi(optionv);
					 return 3;
			default :
					 return -1;
		}
	}
	catch (const exception e)
	{
		return -1;
	}
}

DNAArg::DNAArg(int argc, char **argv)
{
	if (argc != 9)
	{
		invalidSetting();
	}
	else
	{
		int optind;
		bool optionsExist[4] = {false, false, false, false};
		/* as sequencially,
		 * 0 : index for -input option
		 * 1 : index for -l option
		 * 2 : index for -m option
		 * 3 : index for -h option
		 */
		for (int ind = 0; ind < 4; ind++)
		{
			optind = validSetting(argv[2*ind+1],argv[2*ind+2]);
			if (optind > -1 && optind < 5)
				optionsExist[optind] = true;
		}
		valid = optionsExist[0] & optionsExist[1] &
			optionsExist[2] & optionsExist[3];
	}
}
const string &DNAArg::getFileName(void)
{
	return fileName;
}

int DNAArg::getMinimumLength(void)
{
	return minimumLength;
}

int DNAArg::getMissmatchNumber(void)
{
	return mismatchNumber;
}

int DNAArg::getLoopLength(void)
{
	return loopLength;
}

bool DNAArg::isValid(void)
{
	return valid;
}

void DNAArg::usage(void)
{
	using std::cout;
	using std::endl;

	cout << "usage: ./DNA_Hairpin OPTIONS" << endl
		 << "OPTIONS:" << endl
		 << "  -l <number>       print hairpin structures" << endl
		 << "                    which is longer than <number>"
		 << endl
		 << "  -m <number>       print hairpin structures" << endl
		 << "                    which have missmatch fewer than <number>"
		 << endl
		 << "  -h <number>       print hairpin structures" << endl
		 << "                    which have looplength is shorter than <number>"
		 << endl
		 << "  -input <filename> print hairpin structures of" << endl
		 << "                    <filename> file." << endl
		 << "                    THE FILE MUST BE FASTA FORMAT"
		 << endl
		 << "EXAMPLE:" << endl
		 << "  ./DNA_Hairpin -input soybean.fa -l 200 -m 5 -h 20" << endl;
}
