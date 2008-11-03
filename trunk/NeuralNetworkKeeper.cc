#include "NeuralNetworkKeeper.hh"
#include "PopulationGenerator.hh"

#include <neuralnethack/Config.hh>
#include <neuralnethack/mlp/Mlp.hh>
#include <neuralnethack/mlp/CrossEntropy.hh>
#include <neuralnethack/mlp/QuasiNewton.hh>
#include <neuralnethack/datatools/DataSet.hh>

#include <vector>
#include <string>

using namespace NeuralNetHack;
using namespace MultiLayerPerceptron;

using std::vector;
using std::string;

NeuralNetworkKeeper::NeuralNetworkKeeper():mlp(0), trainer(0), dataSet(0)
{
	vector<uint> arch; arch.push_back(8); arch.push_back(1); arch.push_back(1);
	vector<string> types; types.push_back("tansig"); types.push_back("logsig");
	mlp = new Mlp(arch, types, false);
	dataSet = dataGenerator.createInitialDataSet();
	CrossEntropy* cee = new CrossEntropy(*mlp, *dataSet);
	trainer = new QuasiNewton(*mlp, *dataSet, *cee, 1e-5, 1e5);
}

NeuralNetworkKeeper::~NeuralNetworkKeeper()
{
	if(mlp != 0) delete mlp;
	if(trainer->error() != 0) delete trainer->error();
	if(trainer != 0) delete trainer;
	if(dataSet != 0) delete dataSet;
}

void NeuralNetworkKeeper::train()
{
}

