#ifndef _Habitat_h_
#define _Habitat_h_

#include "Individual.hh"
#include "PopulationGenerator.hh"
#include "Predator.hh"

#include <neuralnethack/Config.hh>
#include <neuralnethack/datatools/Pattern.hh>
#include <neuralnethack/datatools/DataSet.hh>

#include <vector>
#include <iostream>
#include <utility>

enum HabitatType { H1=1, H2=2 };

class Habitat
{
	public:

		Habitat(HabitatType type);
		~Habitat();

		void scoreIndividuals(); /** Make the Predator run through the Habitat. */
		uint killOffPrey(); /** Make the Predator run through the Habitat. Return number of Individuals killed. */
		uint exterminate(); /** Kill everything in the Habitat. Return number of Individuals killed. */
		double getAverageSum(); /** Get the average sum of all alleles in the genome of the population. */
		double getAverageFitness(); /** Get the average fitness of the population. */
		double getAverageBackgroundFitness(); /** Get the average fitness of the background. */
		std::vector<double> getAverageIndividual(); /** Get the average Individual from the Habitat. */
		std::vector<double> getFeatureValues(); /** Get the feature value for all Individuals in the Habitat. */
		void printIndividuals(std::ostream& os); /** Print the Individuals and their fitness. */
		void printMedianIndividual(std::ostream& os); /** Print the average Individual. */
		uint getNumIndividuals() { return individuals.size(); } /** Get the number of Individual in this Habitat. */
		std::vector<Individual>& getIndividuals() { return individuals; } /** Get all Individuals in the Habitat. */

		/** Trains the Predator on the Habitat. */
		void trainPredator(bool init);
		/** Creates a new population from the old one. */
		void replicate();
		/** Migrates Individual from both Habitat. */
		std::pair<uint, uint> migrate(Habitat& habitat);


	private:
		PopulationGenerator* pg; /** The random number generator. */
		std::vector<Individual> individuals; /** The list of Individual living in this habitat */
		const uint type; /** The habitat type */
		Predator* predator; /** The Predator */

		/** Creates a random background sample. */
		DataTools::Pattern createBackground();
		/** Creates a random Individual and returns it as a pattern. */
		DataTools::Pattern createIndividual();
		/** Creates a pure Individual that is for sure not a background. */
		DataTools::Pattern createPureIndividual();
		/** Checks if an Individual is pure or not. */
		bool isIndividualPure(std::vector<double>& vec);
		/** Creates a DataSet that contains every Individual present in the Habitat. */
		DataTools::DataSet createDataSet();
		/** Creates a new DataSet that does not contain any Individual present in the Habitat. */
		DataTools::DataSet createNewDataSet();
		/** Creates a DataSet that contains all individuals with Fitness < 0.5 in the Habitat. */
		DataTools::DataSet createFeedbackDataSet();
		/** Converts a genome into a Pattern. */
		DataTools::Pattern genomeToPattern(std::vector<double>& genome, bool individual=true);
};

#endif
