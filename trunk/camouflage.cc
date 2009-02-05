#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <numeric>
#include <cstdlib>

#include <neuralnethack/Config.hh>
#include <neuralnethack/mlp/Mlp.hh>
#include <neuralnethack/datatools/Pattern.hh>

#include "Predator.hh"
#include "Habitat.hh"
#include "NeuralNetworkKeeper.hh"

using std::string;
using std::vector;
using std::cout;
using std::accumulate;
using std::endl;

using namespace NeuralNetHack;
using namespace MultiLayerPerceptron;
using DataTools::Pattern;

bool cleanup(Mlp* mlp)
{
	if(mlp != 0) delete mlp;
	return true;
}

void scoreIndividuals()
{
}

void meanValues()
{
	PopulationGenerator pg;
	//double mean1 = 0;
	//double mean2 = 0;
	std::ofstream tmp("habitatmeans.txt");

	for(uint i=0; i<1000; ++i){
		vector<double> p1 = pg.createBackground1().input();
		vector<double> p2 = pg.createBackground2().input();
		/*
		mean1 += accumulate(p1.begin(), p1.end(), 0);
		mean2 += accumulate(p2.begin(), p2.end(), 0);
		*/
		double m1 = accumulate(p1.begin(), p1.end(), 0);
		double m2 = accumulate(p2.begin(), p2.end(), 0);
		tmp<<m1<<"\t"<<m2<<endl;

	}
	//cout<<"Mean 1: "<<mean1<<"\tMean 2: "<<mean2<<endl;
	tmp.close();
}

int main(int argc, char* argv[])
{
	srand48(time(0));
	/*
	NeuralNetworkKeeper nnk;
	nnk.train();
	std::ofstream os("generated_data.dat");
	nnk.printCurrentDataSet(os);
	os.close();

	meanValues();
	*/

	Habitat h1(H1);

	while(true){
		h1.scoreIndividuals();
		cout<<"Average Fitness: "<<h1.getAverageFitness()<<endl;
		sleep(1);
		/*
		   h1.replicate();
		   scoreIndividuals();
		   killOffPrey();
		   migrate();
		   replicate();
		   */
	}
	return EXIT_SUCCESS;
}
