#include "PopulationGenerator.hh"
#include "Individual.hh"
#include "Constants.hh"

#include <neuralnethack/datatools/CoreDataSet.hh>
#include <neuralnethack/datatools/DataSet.hh>
#include <neuralnethack/datatools/Normaliser.hh>

#include <cmath>
#include <algorithm>

using DataTools::DataSet;
using DataTools::Pattern;
using DataTools::CoreDataSet;
using DataTools::Normaliser;

using std::vector;

PopulationGenerator::PopulationGenerator()
{ 
	gsl_rng_env_setup(); 
	T = gsl_rng_default; 
	r = gsl_rng_alloc (T);  
}

PopulationGenerator::~PopulationGenerator()
{ 
	gsl_rng_free (r);
}

DataSet* PopulationGenerator::createInitialDataSet(uint n)
{
	CoreDataSet* coreDataSet = new CoreDataSet();
	for(uint i=0; i<n; ++i){
		coreDataSet->addPattern(createIndividual());
		coreDataSet->addPattern(createBackground1());
	}
	DataSet* dataSet = new DataSet();
	dataSet->coreDataSet(*coreDataSet);

	//Normaliser norm;
	//norm.calcAndNormalise(*dataSet, true);
	return dataSet;
}

Pattern PopulationGenerator::createIndividual()
{
	vector<double> genome;
	vector<double> target(1,1);
	Individual individual(*this);

	for(uint i=0; i<genomeSize; ++i)
		genome.push_back(round(drawRandomNumber()*maxGenomeVal));

	Pattern pattern("", genome, target);
	return pattern;
}

Pattern PopulationGenerator::createBackground1()
{
	vector<double> genome; 
	vector<double> target(1,0);
	Individual individual(*this);

	/* Background 1 contains 2 1's and 1 3's */
	genome.push_back(1); genome.push_back(1); genome.push_back(3);

	/* Fill up with numbers != 1 and 3 */
	while(genome.size() < genomeSize){
		uint value = round(drawRandomNumber()*maxGenomeVal);
		if(value != 1 and value != 3) genome.push_back(value);
	}
	random_shuffle(genome.begin(), genome.end());

	Pattern pattern("", genome, target);
	return pattern;
}

Pattern PopulationGenerator::createBackground2()
{
	vector<double> genome; 
	vector<double> target(1,0);
	Individual individual(*this);

	/* Background 1 contains 2 2's and 1 4's */
	genome.push_back(2); genome.push_back(2); genome.push_back(4);

	/* Fill up with numbers != 2 and 4 */
	while(genome.size() < genomeSize){
		uint value = round(drawRandomNumber()*maxGenomeVal);
		if(value != 2 and value != 4) genome.push_back(value);
	}
	random_shuffle(genome.begin(), genome.end());

	Pattern pattern("", genome, target);
	return pattern;
}
