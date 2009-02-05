#include "NeuralNetworkKeeper.hh"
#include "PopulationGenerator.hh"

#include <neuralnethack/Config.hh>
#include <neuralnethack/mlp/Mlp.hh>
#include <neuralnethack/mlp/CrossEntropy.hh>
#include <neuralnethack/mlp/QuasiNewton.hh>
#include <neuralnethack/mlp/GradientDescent.hh>
#include <neuralnethack/datatools/DataSet.hh>

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <iterator>

using namespace NeuralNetHack;
using namespace MultiLayerPerceptron;

using std::vector;
using std::string;
using std::cout;
using std::ostream;
using std::copy;
using std::ostream_iterator;
using DataTools::DataSet;

/** TODO: Make sure this initial dataset is handled in a better way! */
NeuralNetworkKeeper::NeuralNetworkKeeper(uint numVar):mlp(0), trainer(0), dataSet(0)
{
	vector<uint> arch; arch.push_back(numVar); arch.push_back(1); arch.push_back(1);
	vector<string> types; types.push_back("tansig"); types.push_back("logsig");
	mlp = new Mlp(arch, types, false);
	dataSet = dataGenerator.createInitialDataSet(100);
	CrossEntropy* cee = new CrossEntropy(*mlp, *dataSet);
	trainer = new QuasiNewton(*mlp, *dataSet, *cee, 1e-15, 1000);
	//trainer = new GradientDescent(*mlp, *dataSet, *cee, 1e-15, 10, 0.02, 0.9, 0.8);
	trainer->numEpochs(1000);
}

NeuralNetworkKeeper::~NeuralNetworkKeeper()
{
	if(mlp != 0) delete mlp;
	if(trainer->error() != 0) delete trainer->error();
	if(trainer != 0) delete trainer;
	if(dataSet != 0) delete dataSet;
}

void NeuralNetworkKeeper::train(DataSet& dataset)
{
	trainer->train(*mlp, dataset, cout);
}

double NeuralNetworkKeeper::propagate(vector<double>& genome)
{
	return mlp->propagate(genome).front();
}

/*void convertDataToPopulation(Population& population)
{
	for(uint i=0; i<dataSet.size(); ++i){
		Pattern& p = dataSet.pattern(i);

		if(){
		}
	}
}
*/
/*
void NeuralNetworkKeeper::refreshDataSet()
{
	if(dataSet != 0) delete dataSet;
	dataSet = dataGenerator.createInitialDataSet(100);
}
*/
void NeuralNetworkKeeper::printCurrentDataSet(ostream& os)
{
	for(uint i=0; i<dataSet->size(); ++i){
		vector<double>& input = dataSet->pattern(i).input();
		vector<double>& output = dataSet->pattern(i).output();
		copy(input.begin(), input.end(), ostream_iterator<double>(os, " ")); os<<"\t";
		copy(output.begin(), output.end(), ostream_iterator<double>(os, " ")); os<<std::endl;
	}
}

