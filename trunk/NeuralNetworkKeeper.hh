#ifndef _NeuralNetworkKeeper_hh_
#define _NeuralNetworkKeeper_hh_

#include "PopulationGenerator.hh"

#include <neuralnethack/Config.hh>
#include <neuralnethack/mlp/Mlp.hh>
#include <neuralnethack/mlp/QuasiNewton.hh>
#include <neuralnethack/datatools/DataSet.hh>

class NeuralNetworkKeeper
{
	public:
		NeuralNetworkKeeper();
		virtual ~NeuralNetworkKeeper();

		void train(void);

	private:
		MultiLayerPerceptron::Mlp* mlp;
		MultiLayerPerceptron::QuasiNewton* trainer;
		DataTools::DataSet* dataSet;
		PopulationGenerator dataGenerator;
};

#endif
