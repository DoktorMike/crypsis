#ifndef _NeuralNetworkKeeper_hh_
#define _NeuralNetworkKeeper_hh_

#include "PopulationGenerator.hh"

#include <neuralnethack/Config.hh>
#include <neuralnethack/mlp/Mlp.hh>
#include <neuralnethack/mlp/QuasiNewton.hh>
#include <neuralnethack/mlp/GradientDescent.hh>
#include <neuralnethack/datatools/DataSet.hh>

#include <iostream>

class NeuralNetworkKeeper
{
	public:
		NeuralNetworkKeeper();
		virtual ~NeuralNetworkKeeper();

		void train(void);
		MultiLayerPerceptron::Mlp& getMlp() { return *mlp; }
		void printCurrentDataSet(std::ostream& os);

	private:
		MultiLayerPerceptron::Mlp* mlp;
		//MultiLayerPerceptron::QuasiNewton* trainer;
		MultiLayerPerceptron::GradientDescent* trainer;
		DataTools::DataSet* dataSet;
		PopulationGenerator dataGenerator;
		//const uint sampleSize;
};

#endif
