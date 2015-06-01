#ifndef FASTA_H_
#define FASTA_H_
#include <string>

class FASTA
{
  public :
	FASTA(std::string fileName);
	const std::string &getDescription(void);
	const std::string &getContent(void);
  private :
	std::string description;
	std::string content;
};

#endif
