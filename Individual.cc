#include "Individual.hh"

#include "PopulationGenerator.hh"

#include <neuralnethack/datatools/Pattern.hh>

#include <cmath>

using std::vector;
using DataTools::Pattern;

Individual::Individual(PopulationGenerator& pg):fitness(0), genome(0)
{
	for(uint i=0; i<genomeSize; ++i)
		genome.push_back(pg.drawRandomNumber(maxGenomeVal+1));
}

Individual::~Individual()
{
}

Pattern Individual::getPattern()
{
	vector<double> target(1,1);
	Pattern pattern("", genome, target);
	return pattern;
}
