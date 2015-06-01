#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include "Hairpin.h"

using std::string;


static int minNum(int a, int b, int c)
{
	if (b < a)
		if (c < b) return 2;
		else return 1;
	else
		if (c < a) return 2;
		else return 0;
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

static string stringtoupper(string str)
{
	using std::toupper;

	for (string::iterator it = str.begin(); it != str.end(); it++)
		*it = toupper(*it);
	return str;
}




int TableControl::geti(int ind)
{
	return ind/tableSize;
}

int TableControl::getj(int ind)
{
	return ind%tableSize;
}

int TableControl::makeIndex(int i, int j)
{
	return  i*tableSize + j;
}




void HairpinTable::fillTables(const std::string &dna_sequence)
{
	using std::cerr;
	using std::exit;

	for (int i = 0; i < tableSize - loopLength; i++)
	{
		valueTable[makeIndex(i,i+loopLength-1)] = 0;
		directionTable[makeIndex(i,i+loopLength-1)] = HOLD;
	}

	for (int diff = loopLength; diff < tableSize; diff++)
	{
		for (int i = 0; i < tableSize-diff; i++)
		{
			int j = i + diff;
			int ind = makeIndex(i,j);
			if (isBasePair(dna_sequence[i],dna_sequence[j]))
			{
				valueTable[ind] = valueTable[makeIndex(i+1,j-1)];
				directionTable[ind] = LEFTDOWNG;
			}
			else
			{
				int vt_i1j0 = valueTable[makeIndex(i+1,j)] + 1;
				int vt_i0j1 = valueTable[makeIndex(i,j-1)] + 1;
				int vt_i1j1;
				if (i+1 > j-1)
					vt_i1j1 = tableSize;
				else
					vt_i1j1 = valueTable[makeIndex(i+1,j-1)] + 1;

				switch (minNum(vt_i1j1, vt_i0j1, vt_i1j0))
				{
					case 2 :
							 valueTable[ind] = vt_i1j0;
							 directionTable[ind] = DOWN;
							 break;
					case 1 :
							 valueTable[ind] = vt_i0j1;
							 directionTable[ind] = LEFT;
							 break;
					case 0 :
							 valueTable[ind] = vt_i1j1;
							 directionTable[ind] = LEFTDOWNB;
							 break;
					default :
							 cerr << "Impossible!!\n";
							 exit(2);
				}
			}
		}
	}
}

HairpinTable::HairpinTable(const std::string &dna_sequence, int loopLength, int mismatchNumber)
		: dna_sequence(dna_sequence)
{
	tableSize = dna_sequence.length();
	valueTable = new int[tableSize*tableSize];
	directionTable = new Direction[tableSize*tableSize];
	this->loopLength = loopLength;
	this->mismatchNumber = mismatchNumber;

	fillTables(dna_sequence);
}

HairpinTable::~HairpinTable()
{
	delete [] valueTable;
	delete [] directionTable;
}

HairpinResult HairpinTable::printResult(int minimumLength, bool reset)
{
	static int diff = tableSize-3;
	static int i = 1;
	int j = i + diff;

	if (!(valueTable[makeIndex(0,tableSize-1)] < mismatchNumber))
	{

		while (diff >= minimumLength)
		{
			while (i < tableSize - diff - 1)
			{
				j = i + diff;
				if (valueTable[makeIndex(i,j)] == mismatchNumber &&
					valueTable[makeIndex(i-1,j)] > mismatchNumber &&
					valueTable[makeIndex(i,j+1)] > mismatchNumber &&
					valueTable[makeIndex(i-1,j+1)] == mismatchNumber + 1)
				{
					goto ret;
				}
				i++;
			}
			diff--;
			i = 1;
		}
	}
	else
	{
		i = 0;
		j = tableSize-1;
	}

//  	while (ind < (tableSize*(tableSize+1))/2 &&
//		   !(valueTable[ind] == mismatchNumber &&
//			 i > 0 && j+1 < (tableSize*(tableSize+1))/2 &&
//			 valueTable[makeIndex(i-1,j+1)] == mismatchNumber+1 &&
//			 j-i+2 > minimumLength))
//	{
//		ind++;
//		i = geti(ind);
//		j = getj(ind);
//		std::cout << ind << " / " << (tableSize*(tableSize+1))/2 << "\n";
//	}

  ret:
	if (diff < minimumLength)
	{
		return HairpinResult(false);
	}
	else
	{
		i++;

		return HairpinResult(true, i, j, loopLength, mismatchNumber,
							 &dna_sequence, directionTable,
							 tableSize);
	}
}










void HairpinResult::backtracking(int i, int j, const string *dna_sequence, Direction *directionTable)
{
	using std::toupper;

	int len = j-i+1;

	while (j-i+1 > loopLength)
	{
		switch(directionTable[makeIndex(i,j)])
		{
			case HOLD :
					 realLoopLength = len -
						 sequence1.length() - sequence3.length();
					 sequence1 += "  " + stringtoupper((*dna_sequence).substr(i,(j-i+1)));
					 return;
			case DOWN :
					 sequence1 += toupper((*dna_sequence)[i]);
					 sequence2 += " ";
					 sequence3 += "-";
					 i++;
					 len++;
					 break;
			case LEFT :
					 sequence1 += "-";
					 sequence2 += " ";
					 sequence3 += toupper((*dna_sequence)[j]);
					 j--;
					 len++;
					 break;
			case LEFTDOWNB :
					 sequence1 += toupper((*dna_sequence)[i]);
					 sequence2 += " ";
					 sequence3 += toupper((*dna_sequence)[j]);
					 i++;
					 j--;
					 break;
			case LEFTDOWNG :
					 sequence1 += toupper((*dna_sequence)[i]);
					 sequence2 += "|";
					 sequence3 += toupper((*dna_sequence)[j]);
					 i++;
					 j--;
					 break;
			default :
					 valid = false;
					 return;
		}

	}

	realLoopLength = len -
		sequence1.length() - sequence3.length();
	sequence1 += "  " + stringtoupper((*dna_sequence).substr(i,(j-i+1)));
}

HairpinResult::HairpinResult(bool valid,
							 int i, int j,
							 int loopLength, int mismatchNumber,
							 const string *dna_sequence, Direction *directionTable,
							 int tableSize)
{
	this->valid = valid;
	this->i = i;
	this->j = j;
	this->loopLength = loopLength;
	this->tableSize = tableSize;
	this->mismatchNumber = mismatchNumber;
	this->sequence1 = "";
	this->sequence2 = "";
	this->sequence3 = "";

	if (valid)
	{
		backtracking(i, j, dna_sequence, directionTable);
	}
}

bool HairpinResult::isValid() const
{
	return valid;
}

std::ostream &operator<<(std::ostream &os, const HairpinResult hr)
{
	int max3 = hr.sequence3.length();
	int max1 = hr.sequence1.length();
	int counter = 0;

	os << "||  ============================================================\n||\n";

	os << "\n||  i = " << hr.i << ", j = " << hr.j
	   << ", length = " << hr.j-hr.i+1
	   << ", loop_length = " << hr.realLoopLength
	   << ", miss = " << hr.mismatchNumber << "\n||\n";

	while (counter + 60 < max3)
	{
		os << "||  " << hr.sequence1.substr(counter,60) << "\n";
		os << "||  " <<hr.sequence2.substr(counter,60) << "\n";
		os << "||  " <<hr.sequence3.substr(counter,60) << "\n||\n";
		counter += 60;
	}

	if (counter + 60 < max1)
	{
		os << "||  " << hr.sequence1.substr(counter,60) << "\n";
		os << "||  " << hr.sequence2.substr(counter) << "\n";
		os << "||  " << hr.sequence3.substr(counter) << "\n||\n";
		counter += 60;
		while (counter + 60 < max1)
		{
			os << "||  " << hr.sequence1.substr(counter,60) << "\n||\n||\n";
			counter += 60;
		}
		os << "||  " << hr.sequence1.substr(counter) << "\n||\n";
	}
	else
	{
		os << "||  " << hr.sequence1.substr(counter) << "\n";
		os << "||  " << hr.sequence2.substr(counter) << "\n";
		os << "||  " << hr.sequence3.substr(counter) << "\n||\n";
	}
	os << "||  ============================================================\n\n\n";

	return os;
}
