#ifndef HAIRPIN_H_
#define HAIRPIN_H_
#include <iostream>
#include <string>

class TableControl
{
  public :
	int tableSize;
	int loopLength;

	int makeIndex(int i, int j);
	int geti(int ind);
	int getj(int ind);
};

class HairpinResult;

enum Direction{HOLD, LEFT, DOWN, LEFTDOWNB, LEFTDOWNG};

class HairpinTable : private TableControl
{
  public :
	HairpinTable(const std::string &dna_sequence, int loopLength, int mismatchNumber);
	~HairpinTable();
 	HairpinResult printResult(int minimumLength, bool reset);
  private:
	const std::string &dna_sequence;
	int mismatchNumber;
	int *valueTable;
	Direction *directionTable;
	void fillTables(const std::string &dna_sequence);
};

class HairpinResult : private TableControl
{
	friend std::ostream &operator<<(std::ostream &os, const HairpinResult hr);
	friend HairpinResult HairpinTable::printResult(int minimumLength, bool reset);

  public :
	HairpinResult(bool valid,
				  int i=0, int j=0,
				  int loopLength=0, int mismatchNumber=0,
				  const std::string *dna_sequence=nullptr,
				  Direction *directionTable=nullptr,
				  int tableSize=0);
	bool isValid() const;
  private :
	bool valid;
	int i, j;
	int mismatchNumber;
	int realLoopLength;
	std::string sequence1;
	std::string sequence2;
	std::string sequence3;
	void backtracking(int i, int j, const std::string *dna_sequence, Direction *directionTable);
};

#endif
