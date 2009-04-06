#include "Habitat.hh"
#include "Predator.hh"
#include "Constants.hh"

#include <neuralnethack/Config.hh>
#include <neuralnethack/datatools/Pattern.hh>
#include <neuralnethack/datatools/DataSet.hh>
#include <neuralnethack/datatools/CoreDataSet.hh>

#include <vector>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <iterator>

using DataTools::Pattern;
using DataTools::DataSet;
using DataTools::CoreDataSet;
using std::vector;
using std::cout;
using std::endl;
using std::ostream_iterator;
using std::copy;
using std::accumulate;
using std::fill;

Habitat::Habitat(HabitatType type):pg(new PopulationGenerator()), individuals(maxSize, *pg), type(type), predator(new Predator())
{
	for(vector<Individual>::iterator it=individuals.begin(); it!=individuals.end(); ++it){
		Individual individual(*pg);
		*it = individual;
	}
	trainPredator(true);
}

Habitat::~Habitat()
{ 
	delete pg; 
	delete predator;
}

void Habitat::scoreIndividuals()
{
	for(vector<Individual>::iterator it=individuals.begin(); it!=individuals.end(); ++it){
		predator->predate(*it);
	}
}

double Habitat::getAverageSum()
{
	double sum = 0;
	double bgSum = 0;
	for(vector<Individual>::iterator it=individuals.begin(); it!=individuals.end(); ++it){
		sum += accumulate(it->getGenome().begin(), it->getGenome().end(), 0);
		vector<double> bggenome = createBackground().input();
		bgSum += accumulate(bggenome.begin(), bggenome.end(), 0);
	}
	cout<<"FeatureNum: "<<sum/individuals.size()<<"\tBgFeatureNum: "<<bgSum/individuals.size()<<endl;
	return sum/individuals.size();
}

double Habitat::getAverageFitness()
{
	double average = 0;
	double bgAverage = 0;
	for(vector<Individual>::iterator it=individuals.begin(); it!=individuals.end(); ++it){
		double indfitness = it->getFitness();
		/*
		cout<<"Individual: ";
		copy(it->getGenome().begin(), it->getGenome().end(), ostream_iterator<double>(cout, " "));
		cout<<": "<<indfitness<<"\t";
		*/
		average+=indfitness;
		vector<double> bggenome = createBackground().input();
		double bgfitness = 1-predator->predate(bggenome);
		bgAverage += bgfitness;
		/*
		cout<<"Background: ";
		copy(bggenome.begin(), bggenome.end(), ostream_iterator<double>(cout, " "));
		cout<<": "<<bgfitness<<endl;
		*/
	}
	cout<<"Fitness: "<<average/individuals.size()<<"\tBgFitness: "<<bgAverage/individuals.size()<<endl;
	return average/individuals.size();
}

/** TODO: Fix the number of genes present.
 */
Pattern Habitat::createBackground()
{
	vector<double> genome; 
	vector<double> target(1,0);

	if(type == H1){
		/* Background 1 contains 2 1's and 1 3's */
		//genome.push_back(1); genome.push_back(1); genome.push_back(3);

		/* Fill up with numbers != 1 and 3 */
		//while(genome.size() < genomeSize){
		//	uint value = round(pg->drawRandomNumber()*maxGenomeVal);
		//	if(value != 1 and value != 3) genome.push_back(value);
		//}
		while(genome.size() < genomeSize){
			genome.push_back(pg->drawRandomNumber(maxGenomeVal+1));
		}
		fill(genome.begin(), genome.begin()+genomeSize/2+1, 1);
		//fill(genome.begin(), genome.end(), 1);
	}else{
		/* Background 1 contains 2 2's and 1 4's */
		genome.push_back(2); genome.push_back(2); genome.push_back(4);

		/* Fill up with numbers != 2 and 4 */
		while(genome.size() < genomeSize){
			uint value = round(pg->drawRandomNumber()*maxGenomeVal);
			if(value != 2 and value != 4) genome.push_back(value);
		}
	}

	random_shuffle(genome.begin(), genome.end());

	Pattern pattern("", genome, target);
	return pattern;
}

Pattern Habitat::createIndividual()
{
	Individual individual(*pg);
	return individual.getPattern();
}

Pattern Habitat::genomeToPattern(vector<double>& genome, bool individual)
{
	vector<double> target(1, individual == true ? 1 : 0);
	Pattern pattern("", genome, target);
	return pattern;
}

DataSet Habitat::createDataSet()
{
	CoreDataSet* cds = new CoreDataSet();
	DataSet ds;
	for(uint i=0; i<individuals.size(); ++i){
		cds->addPattern(createBackground());
		cds->addPattern(individuals[i].getPattern());
	}
	ds.coreDataSet(*cds);
	return ds;
}

DataSet Habitat::createFeedbackDataSet()
{
	CoreDataSet* cds = new CoreDataSet();
	DataSet ds;
	for(uint i=0; i<individuals.size(); ++i){
		if(individuals[i].getFitness() < 0.5){
			cds->addPattern(createBackground());
			cds->addPattern(individuals[i].getPattern());
		}
	}
	ds.coreDataSet(*cds);
	return ds;
}

DataSet Habitat::createNewDataSet()
{
	CoreDataSet* cds = new CoreDataSet();
	DataSet ds;
	for(uint i=0; i<4*maxSize; ++i){
		cds->addPattern(createBackground());
		cds->addPattern(createIndividual());
	}
	ds.coreDataSet(*cds);
	return ds;
}

void Habitat::trainPredator(bool init)
{
	DataSet ds = init == true ? createNewDataSet() : createFeedbackDataSet();
	cout<<"DataSet Size: "<<ds.size()<<endl;
	if(ds.size() > 0){
		predator->train(ds);
	}
	//predator->printCurrentDataSet(cout);
	//ds.print(cout);
	ds.killCoreData();
}

void Habitat::killOffPrey()
{
	vector<Individual>::iterator it=individuals.begin(); 
	while(it!=individuals.end())
		if(it->getFitness() < 0.5)
			it = individuals.erase(it);
		else
			++it;
}

void Habitat::replicate(){
	vector<Individual> tmp;
	//for(uint i=0; i<individuals.size(); ++i){
	for(uint i=0; i<maxSize; ++i){
		uint rnd1 = pg->drawRandomNumber(individuals.size());
		uint rnd2 = pg->drawRandomNumber(individuals.size());
		vector<double> genome;
		vector<double> genome1 = individuals[rnd1].getGenome();
		genome.insert(genome.end(), genome1.begin(), genome1.begin()+genome1.size()/2);
		vector<double> genome2 = individuals[rnd2].getGenome();
		genome.insert(genome.end(), genome2.begin()+genome2.size()/2, genome2.end());
		//Mutate every 20th genome
		if(pg->drawRandomNumber() < 0.05)
			genome[pg->drawRandomNumber(genome.size())] = pg->drawRandomNumber(maxGenomeVal+1);
		Individual individual(*pg);
		individual.setGenome(genome);
		tmp.push_back(individual);
	}
	individuals = tmp;
}
