#ifndef _Population_hh_
#define _Population_hh_

#include <neuralnethack/mlp/Mlp.hh>

#include <vector>

class Population
{
	public:
		Population();
		~Population();
		void updateFitness(MultiLayerPerceptron::Mlp& mlp);
	private:
		std::vector<double> fitness; /** The individuals' fitness */
};
#endif
