#ifndef HAIRPIN_H_
#define HAIRPIN_H_
#include <iostream>
#include <string>

class HairpinResult;

enum Direction{HOLD, LEFT, DOWN, LEFTDOWN};

class HairpinTable
{
  public :
	HairpinTable(const std::string &dna_sequence, int loopLength, int missmatchNumber);
	~HairpinTable();
 	HairpinResult printResult(int minimumLength);
  private:
	int tableSize;
	int loopLen;
	int missNum;
	int *valueTable;
	Direction *directionTable;
	int makeIndex(int i, int j);
	void fillTables(const std::string &dna_sequence);
};

class HairpinResult
{
	friend std::ostream &operator<<(std::ostream &os, const HairpinResult hr);
	friend HairpinResult HairpinTable::printResult(int minimumLength);

  public :
	HairpinResult();
	bool isValid() const;
  private :
	int i, j;
	int length;
	int loopLength;
	int missmatchNumber;
	std::string sequence1;
	std::string sequence2;
	std::string sequence3;
};

#endif
