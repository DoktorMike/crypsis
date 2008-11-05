#ifndef _Individual_h_
#define _Individual_h_

#include <vector>

class Individual
{
	public:

		Individual();
		~Individual();
		double getFitness(){ return fitness; }
		void setFitness(double fitness){ this->fitness = fitness; }

		std::vector<double>& getGenome() { return genome; }

		static const uint genomeSize = 8; /** The number of genes in the genome */
		static const uint maxGenomeVal = 4; /** The maximum value a gene can have */
	private:
		double fitness; /** The fitness of the individual */
		std::vector<double> genome; /** The genome of the individual */

};

#endif
