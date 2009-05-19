#ifndef _NeuralNetworkKeeper_hh_
#define _NeuralNetworkKeeper_hh_

#include "PopulationGenerator.hh"

#include <neuralnethack/Config.hh>
#include <neuralnethack/mlp/Mlp.hh>
#include <neuralnethack/mlp/QuasiNewton.hh>
#include <neuralnethack/mlp/Trainer.hh>
#include <neuralnethack/mlp/GradientDescent.hh>
#include <neuralnethack/datatools/DataSet.hh>

#include <iostream>
#include <fstream>
#include <string>

class NeuralNetworkKeeper
{
	public:
		NeuralNetworkKeeper(uint numVar=8);
		virtual ~NeuralNetworkKeeper();

		MultiLayerPerceptron::Mlp& getMlp() { return *mlp; }

		void train(DataTools::DataSet& dataset);

		double propagate(std::vector<double>& genome);

		void printCurrentDataSet(std::ostream& os);

	private:
		MultiLayerPerceptron::Mlp* mlp;
		//MultiLayerPerceptron::QuasiNewton* trainer;
		//MultiLayerPerceptron::GradientDescent* trainer;
		MultiLayerPerceptron::Trainer* trainer;
		DataTools::DataSet* dataSet;
		PopulationGenerator dataGenerator;
		//const uint sampleSize;
		std::ofstream os;

};

#endif
