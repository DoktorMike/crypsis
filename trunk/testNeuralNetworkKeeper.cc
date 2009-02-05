#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <numeric>
#include <cmath>

#include <neuralnethack/Config.hh>
#include <neuralnethack/mlp/Mlp.hh>
#include <neuralnethack/datatools/Pattern.hh>
#include <neuralnethack/datatools/DataSet.hh>
#include <neuralnethack/datatools/CoreDataSet.hh>

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
using DataTools::DataSet;
using DataTools::CoreDataSet;

DataSet createSimpleDataSet()
{
	//Prepare OR logic dataset.
	CoreDataSet* cds = new CoreDataSet();
	DataSet ds;
	vector<double> v1; v1.push_back(0); v1.push_back(0);
	vector<double> v2; v2.push_back(0); v2.push_back(1);
	vector<double> v3; v3.push_back(1); v3.push_back(0);
	vector<double> v4; v4.push_back(1); v4.push_back(1);
	vector<double> t1; t1.push_back(0);
	vector<double> t2; t2.push_back(1);
	Pattern p1("1", v1, t1);
	Pattern p2("2", v2, t2);
	Pattern p3("3", v3, t2);
	Pattern p4("4", v4, t1);
	cds->addPattern(p1);
	cds->addPattern(p2);
	cds->addPattern(p3);
	cds->addPattern(p4);
	ds.coreDataSet(*cds);
	return ds;
}

Pattern createIndividual()
{
	vector<double> genome;
	vector<double> target(1,1);
	PopulationGenerator pg;

	for(uint i=0; i<8; ++i)
		genome.push_back(round(pg.drawRandomNumber()*4));

	Pattern pattern("", genome, target);
	return pattern;
}

Pattern createBackground1()
{
	vector<double> genome; 
	vector<double> target(1,0);
	PopulationGenerator pg;

	/* Background 1 contains 2 1's and 1 3's */
	genome.push_back(1); genome.push_back(1); genome.push_back(3);

	/* Fill up with numbers != 1 and 3 */
	while(genome.size() < 8){
		uint value = round(pg.drawRandomNumber()*4);
		if(value != 1 and value != 3) genome.push_back(value);
	}
	random_shuffle(genome.begin(), genome.end());

	Pattern pattern("", genome, target);
	return pattern;
}


DataSet createAdvancedDataSet(uint n)
{
	CoreDataSet* coreDataSet = new CoreDataSet();
	for(uint i=0; i<n; ++i){
		coreDataSet->addPattern(createIndividual());
		coreDataSet->addPattern(createBackground1());
	}
	DataSet dataSet;
	dataSet.coreDataSet(*coreDataSet);
	//Normaliser norm;
	//norm.calcAndNormalise(*dataSet, true);
	return dataSet;
}

int main(int argc, char* argv[])
{
	//DataSet ds = createSimpleDateSet();
	DataSet ds = createAdvancedDataSet(100);
	//Train Neural Network
	srand48(time(0));
	NeuralNetworkKeeper nnh(8);
	//nnh.getMlp().regenerateWeights();
	//nnh.getMlp().regenerateWeights();
	nnh.train(ds);
	
	//Cleanup
	ds.killCoreData();

	return EXIT_SUCCESS;
}
