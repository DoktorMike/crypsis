#ifndef _Predator_h_
#define _Predator_h_

#include "NeuralNetworkKeeper.hh"
#include "Individual.hh"

#include <neuralnethack/datatools/DataSet.hh>

#include <vector>

class Predator
{
	public:
		Predator();
		~Predator();

		bool train(DataTools::DataSet& dataset);
		void reset();
		double predate(std::vector<double>& genome);
		void predate(Individual& individual);

	private:
		NeuralNetworkKeeper nnh;
};

#endif
