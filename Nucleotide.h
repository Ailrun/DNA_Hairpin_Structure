#ifndef NUCLEOTIDE_H_
#define NUCLEOTIDE_H_
#include <cctype>
#include <stdexcept>

typedef enum Nucleobase {A, C, G, T} Nucleobase;

class Nucleotide
{
  private :
	Nucleobase base;
  public :
	Nucleotide(const char base);
	Nucleotide(const Nucleobase base);
	Nucleotide(const Nucleotide &src);
	bool isBasePair(const Nucleotide &counterpart) const;
};

#endif
