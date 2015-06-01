#include <iostream>
#include <cctype>
#include <cstdlib>
#include "Hairpin.h"

static int minNum(int a, int b, int c)
{
	if (b < a)
	{
		if (c < b)
		{
			return 2;
		}
		else
		{
			return 1;
		}
	}
	else
	{
		if (c < a)
		{
			return 2;
		}
		else
		{
			return 0;
		}
	}
}

static bool isBasePair(char fst, char scd)
{
	using std::cerr;
	using std::exit;

	switch (toupper(fst))
	{
		case 'A' :
				 return (toupper(scd) == 'T');
		case 'C' :
				 return (toupper(scd) == 'G');
		case 'G' :
				 return (toupper(scd) == 'C');
		case 'T' :
				 return (toupper(scd) == 'A');
		default :
				 cerr << "this FASTA file is not a dna FASTA!\n";
				 exit(1);
	}
}

int HairpinTable::makeIndex(int i, int j)
{
	return ((j-loopLen+1)*(j-loopLen+2))/2 + i;
}

void HairpinTable::fillTables(const std::string &dna_sequence)
{
	using std::cerr;
	using std::exit;

	for (int i = 0; i < tableSize; i++)
	{
		for (int j = i; (j < tableSize + loopLen - 1 &&
						 j < i + loopLen); j++)
		{
			valueTable[makeIndex(i,j)] = 0;
			directionTable[makeIndex(i,j)] = HOLD;
		}
	}

	for (int i = 0; i < tableSize; i++)
	{
		for (int j = i+loopLen; j < tableSize + loopLen - 1; j++)
		{
			int ind = makeIndex(i,j);
			if (isBasePair(dna_sequence[i],dna_sequence[j]))
			{
				valueTable[ind] = valueTable[makeIndex(i+1,j-1)];
				directionTable[ind] = LEFTDOWN;
			}
			else
			{
				int vt_i1j0 = valueTable[makeIndex(i+1,j)] + 1;
				int vt_i0j1 = valueTable[makeIndex(i,j-1)] + 1;
				int vt_i1j1 = valueTable[makeIndex(i+1,j-1)] + 1;
				switch (minNum(vt_i1j0, vt_i0j1, vt_i1j1))
				{
					case 0 :
							 valueTable[ind] = vt_i1j0;
							 directionTable[ind] = DOWN;
							 break;
					case 1 :
							 valueTable[ind] = vt_i0j1;
							 directionTable[ind] = LEFT;
							 break;
					case 2 :
							 valueTable[ind] = vt_i1j1;
							 directionTable[ind] = LEFTDOWN;
							 break;
					default :
							 cerr << "Impossible!!\n";
							 exit(2);
				}
			}
		}
	}
}

HairpinTable::HairpinTable(const std::string &dna_sequence, int loopLength, int missmatchNumber)
{
	tableSize = dna_sequence.length() - loopLength + 1;
	valueTable = new int[(tableSize*(tableSize+1))/2];
	directionTable = new Direction[(tableSize*(tableSize+1))/2];
	loopLen = loopLength;
	missNum = missmatchNumber;

	fillTables(dna_sequence);
}

HairpinTable::~HairpinTable()
{
	delete [] valueTable;
	delete [] directionTable;
}

HairpinResult HairpinTable::printResult(int minimumLength)
{
	return HairpinResult();
}

HairpinResult::HairpinResult()
{}

bool HairpinResult::isValid() const
{
	return true;
}

std::ostream &operator<<(std::ostream &os, const HairpinResult hr)
{
	return os;
}
