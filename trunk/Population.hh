#ifndef _Population_hh_
#define _Population_hh_

#include <neuralnethack/mlp/Mlp.hh>

#include <vector>

#include "Individual.hh"

class Population
{
	public:
		Population();
		~Population();
		void updateFitness(MultiLayerPerceptron::Mlp& mlp);

	private:
		std::vector<Individual> individuals; /** The individuals */
};
#endif
