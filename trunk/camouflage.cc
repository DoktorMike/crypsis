#include <vector>
#include <string>
#include <iostream>

#include <neuralnethack/Config.hh>
#include <neuralnethack/mlp/Mlp.hh>

#include "NeuralNetworkKeeper.hh"

using std::string;
using std::vector;
using std::cout;

using namespace NeuralNetHack;
using namespace MultiLayerPerceptron;

bool cleanup(Mlp* mlp)
{
	if(mlp != 0) delete mlp;
	return true;
}

int main(int argc, char* argv[])
{
	NeuralNetworkKeeper nnk;
	nnk.train();
	nnk.printCurrentDataSet(cout);

	/*while(){
		scoreIndividuals();
		killOffPrey();
		migrate();
		replicate();
	}*/
	return EXIT_SUCCESS;
}
