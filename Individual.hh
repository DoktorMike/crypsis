#ifndef _Individual_h_
#define _Individual_h_

#include <vector>

class Individual
{
	public:

		double getFitness(){ return fitness; }
		void setFitness(double fitness){ this->fitness = fitness; }

		std::vector<double>& getGenome() { return genome; }

	private:
		double fitness;
		std::vector<double> genome;
};

#endif
