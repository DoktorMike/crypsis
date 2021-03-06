#include "Predator.hh"
#include "Individual.hh"

#include <vector>
#include <iostream>

using DataTools::DataSet;
using std::vector;
using std::ostream;

Predator::Predator() {}
Predator::~Predator() {}

void Predator::reset() { nnh.getMlp().regenerateWeights(); }

/**FIXME This function should return true if training was successful!*/
bool Predator::train(DataSet& dataset) 
{
	nnh.train(dataset);
	return true;
}

double Predator::predate(vector<double>& genome)
{
	return nnh.propagate(genome);
}

void Predator::predate(Individual& individual)
{
	individual.setFitness(1-nnh.propagate(individual.getGenome()));
}

void Predator::printCurrentDataSet(ostream& os)
{
	nnh.printCurrentDataSet(os);
}

