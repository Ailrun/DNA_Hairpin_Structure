#ifndef DNAARG_H_
#define DNAARG_H_
#include <string>

class DNAArg
{
  public :
	DNAArg(int argc, char **argv);

	const std::string &getFileName(void);
	int getMinimumLength(void);
	int getLoopLength(void);
	int getMissmatchNumber(void);
	bool isValid(void);

	void usage(void);

  private:
	std::string fileName;
	int minimumLength;
	int loopLength;
	int mismatchNumber;

	bool valid;

	void invalidSetting(void);
	int validSetting(char* optionk, char* optionv);
};

#endif
