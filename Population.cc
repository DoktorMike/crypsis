#include "Population.hh"
#include "Individual.hh"

#include <vector>

using std::vector;

void Population::updateFitness(MultiLayerPerceptron::Mlp& mlp)
{
	for(vector<Individual>::iterator it=individuals.begin(); it!=individuals.end(); ++it){
		it->setFitness(mlp.propagate(it->getGenome()).front());
	}
}
