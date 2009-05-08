#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <numeric>
#include <cstdlib>
#include <utility>

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
using std::pair;

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

	std::ofstream population1("population1.txt");
	std::ofstream population2("population2.txt");

	Habitat h1(H1);
	Habitat h2(H2); h2.exterminate();

	uint generationCounter = 0;
	while(true){
		cout<<"Generation: "<<++generationCounter<<endl;
		// Score Individuals
		h1.scoreIndividuals();
		h2.scoreIndividuals();
		// Print it
		h1.printIndividuals(population1);
		h2.printIndividuals(population2);
		cout<<"Average Fitness: H1 = "<<h1.getAverageFitness()<<" H2 = "<<h2.getAverageFitness()<<endl;
		cout<<"Average Background Fitness: H1 = "<<h1.getAverageBackgroundFitness()<<" H2 = "<<h2.getAverageBackgroundFitness()<<endl;
		//cout<<"Average Sum: H1 = "<<h1.getAverageSum()<<" H2 = "<<h2.getAverageSum()<<endl;
		cout<<"Number of individuals: H1 = "<<h1.getNumIndividuals()<<" H2 = "<<h2.getNumIndividuals()<<endl;
		sleep(1);
		// Train the predator
		h1.trainPredator(false);
		h2.trainPredator(false);
		// Kill less fit individuals
		uint n1Killed = h1.killOffPrey();
		uint n2Killed = h2.killOffPrey();
		cout<<"Killed off: H1 = "<<n1Killed<<" H2 = "<<n2Killed<<" individuals"<<endl;
		// Migration between the habitats
		pair<uint, uint> nMigrated = h1.migrate(h2);
		cout<<"Migrated from: H1 = "<<nMigrated.first<<" H2 = "<<nMigrated.second<<" individuals"<<endl;
		// Replication
		h1.replicate();
		h2.replicate();
	}

	population1.close();
	population2.close();

	return EXIT_SUCCESS;
}
