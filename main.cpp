#include <iostream>
#include <cstdlib>
#include "DNAArg.h"
#include "FASTA.h"
#include "Hairpin.h"

int main(int argc, char **argv)
{
	using namespace std;

	DNAArg args(argc, argv);

	if (!args.isValid())
	{
		args.usage();
		exit(1);
	}

	FASTA dna_single_strand(args.getFileName());

	HairpinTable table(dna_single_strand.getContent(),
					   args.getLoopLength(),
					   args.getMissmatchNumber());

	HairpinResult result(false);

	cout << "-----------------OUTPUT-----------------" << endl;

	while ((result = table.printResult(args.getMinimumLength(), false)).isValid())
	{
		 cout << result;
	}

	cout << "--------------END OF RESULT------------" << endl;

	return 0;
}
