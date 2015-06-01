#include "Nucleotide.h"

using namespace std;

Nucleotide::Nucleotide(const char base)
{
	switch (toupper(base))
	{
		case 'A' :
				 this->base = A;
				 break;
		case 'C' :
				 this->base = C;
				 break;
		case 'G' :
				 this->base = G;
				 break;
		case 'T' :
				 this->base = T;
				 break;
		default :
				 throw invalid_argument("Nucleobases are A, C, G, T");
				 break;
	}
}

Nucleotide::Nucleotide(const Nucleobase base)
{
	this->base = base;
}

Nucleotide::Nucleotide(const Nucleotide &src)
{
	this->base = src.base;
}

bool Nucleotide::isBasePair(const Nucleotide &counterpart) const
{
	switch(this->base)
	{
		case A :
				 return counterpart.base == T;
		case C :
				 return counterpart.base == G;
		case G :
				 return counterpart.base == C;
		case T :
				 return counterpart.base == A;
		default :
				 throw invalid_argument("Construction Error in first argument"
										"of isBasePair");
				 return false;
	}
}
