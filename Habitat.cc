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
#include <iostream>
#include <utility>

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
using std::ostream;
using std::pair;

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
	//cout<<"FeatureNum: "<<sum/individuals.size()<<"\tBgFeatureNum: "<<bgSum/individuals.size()<<endl;
	return sum/individuals.size();
}

double Habitat::getAverageFitness()
{
	double average = 0;
	double bgAverage = 0;
	for(vector<Individual>::iterator it=individuals.begin(); it!=individuals.end(); ++it){
		double indfitness = it->getFitness();
		average+=indfitness;
		vector<double> bggenome = createBackground().input();
		double bgfitness = 1-predator->predate(bggenome);
		bgAverage += bgfitness;
	}
	return average/individuals.size();
}

double Habitat::getAverageBackgroundFitness()
{
	double bgAverage = 0;
	for(uint i=0; i<individuals.size(); ++i)
		bgAverage += 1-predator->predate(createBackground().input());
	return bgAverage/individuals.size();
}

void Habitat::printIndividuals(ostream& os)
{
	for(vector<Individual>::iterator it=individuals.begin(); it!=individuals.end(); ++it){
		double indfitness = it->getFitness();
		os<<"Individual: ";
		copy(it->getGenome().begin(), it->getGenome().end(), ostream_iterator<double>(os, " "));
		os<<": "<<indfitness<<"\t";
		vector<double> bggenome = createBackground().input();
		double bgfitness = 1-predator->predate(bggenome);
		os<<"Background: ";
		copy(bggenome.begin(), bggenome.end(), ostream_iterator<double>(os, " "));
		os<<": "<<bgfitness<<endl;
	}
}

Pattern Habitat::createBackground()
{
	vector<double> genome; 
	vector<double> target(1,0);

	if(type == H1){
		while(genome.size() < genomeSize){
			genome.push_back(pg->drawRandomNumber(maxGenomeVal+1));
		}
		fill(genome.begin(), genome.begin()+genomeSize/2+1, 1);
	}else{
		while(genome.size() < genomeSize){
			genome.push_back(pg->drawRandomNumber(maxGenomeVal+1));
		}
		fill(genome.begin(), genome.begin()+genomeSize/2+1, 0);
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

bool Habitat::isIndividualPure(vector<double>& vec)
{
	bool pure=false;

	if(type == H1){
		uint sum = accumulate(vec.begin(), vec.end(), 0);
		if(sum < 5) pure = true;
	}else{
		uint sum = accumulate(vec.begin(), vec.end(), 0);
		if(sum > 3) pure = true;
	}
	return pure;
}

Pattern Habitat::createPureIndividual()
{
	Individual individual(*pg);
	while(!isIndividualPure(individual.getGenome())){
		Individual tmp(*pg);
		individual = tmp;
	}
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
		if(isIndividualPure(individuals[i].getGenome())){
			cds->addPattern(createBackground());
			cds->addPattern(individuals[i].getPattern());
		}
	}
	ds.coreDataSet(*cds);
	return ds;
}

DataSet Habitat::createFeedbackDataSet()
{
	CoreDataSet* cds = new CoreDataSet();
	DataSet ds;
	for(uint i=0; i<individuals.size(); ++i){
		if(individuals[i].getFitness() < fitnessCutOff){
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
	for(uint i=0; i<maxSize; ++i){
		cds->addPattern(createBackground());
		cds->addPattern(createPureIndividual());
	}
	ds.coreDataSet(*cds);
	return ds;
}

void Habitat::trainPredator(bool init)
{
	//DataSet ds = init == true ? createNewDataSet() : createFeedbackDataSet();
	DataSet ds = init == true ? createNewDataSet() : createDataSet();
	cout<<"DataSet Size: "<<ds.size()<<endl;
	if(ds.size() > 0){
		predator->train(ds);
	}
	//predator->printCurrentDataSet(cout);
	//ds.print(cout);
	ds.killCoreData();
}

uint Habitat::killOffPrey()
{
	uint n=individuals.size();
	vector<Individual>::iterator it=individuals.begin(); 
	while(it!=individuals.end())
		if(it->getFitness() < fitnessCutOff && individuals.size() > minSizeFrac*maxSize)
			it = individuals.erase(it);
		else
			++it;
	return n-individuals.size();
}

uint Habitat::exterminate()
{
	uint n=individuals.size();
	vector<Individual>::iterator it=individuals.begin(); 
	individuals.erase(individuals.begin(), individuals.end());
	return n;
}

void Habitat::replicate(){
	// Sanity check
	assert(individuals.size() != 0);
	if(individuals.size() >= maxSize) return;

	vector<Individual> tmp;
	uint howmany = (maxSize < 2*individuals.size()+1) ? maxSize : 2*individuals.size()+1;
	for(uint i=0; i<howmany; ++i){
		uint rnd1 = pg->drawRandomNumber(individuals.size());
		uint rnd2 = pg->drawRandomNumber(individuals.size());
		vector<double> genome;
		vector<double> genome1 = individuals[rnd1].getGenome();
		genome.insert(genome.end(), genome1.begin(), genome1.begin()+genome1.size()/2);
		vector<double> genome2 = individuals[rnd2].getGenome();
		genome.insert(genome.end(), genome2.begin()+genome2.size()/2, genome2.end());
		//Mutate every 20th genome
		if(pg->drawRandomNumber() < mutationRate)
			genome[pg->drawRandomNumber(genome.size())] = pg->drawRandomNumber(maxGenomeVal+1);
		Individual individual(*pg);
		individual.setGenome(genome);
		tmp.push_back(individual);
	}
	individuals = tmp;
}

/** \TODO When to do migration? What if there is already a full Habitat? */
std::pair<uint, uint> Habitat::migrate(Habitat& habitat){
	vector<Individual>& individuals2 = habitat.getIndividuals();

	vector<Individual> tmp1;
	uint nMigrate1 = migrationRate*individuals.size();
	for(uint i=0; i<nMigrate1; ++i){
		uint rnd = pg->drawRandomNumber(individuals.size());
		tmp1.push_back(individuals[rnd]);
		individuals.erase(individuals.begin()+rnd);
	}
	vector<Individual> tmp2;
	uint nMigrate2 = migrationRate*individuals2.size();
	for(uint i=0; i<nMigrate2; ++i){
		uint rnd = pg->drawRandomNumber(individuals2.size());
		tmp2.push_back(individuals2[rnd]);
		individuals2.erase(individuals2.begin()+rnd);
	}

	individuals.insert(individuals.begin(), tmp2.begin(), tmp2.end());
	individuals2.insert(individuals2.begin(), tmp1.begin(), tmp1.end());

	return std::make_pair<uint, uint>(nMigrate1, nMigrate2);
}
