#ifndef _Habitat_h_
#define _Habitat_h_

#include "Individual.hh"
#include "PopulationGenerator.hh"
#include "Predator.hh"

#include <neuralnethack/Config.hh>
#include <neuralnethack/datatools/Pattern.hh>
#include <neuralnethack/datatools/DataSet.hh>

#include <vector>

enum HabitatType { H1=1, H2=2 };

class Habitat
{
	public:

		Habitat(HabitatType type);
		~Habitat();

		void scoreIndividuals(); /** Make the Predator run through the Habitat. */
		void killOffPrey(); /** Make the Predator run through the Habitat. */
		double getAverageSum(); /** Get the average sum of all alleles in the genome of the population. */
		double getAverageFitness(); /** Get the average fitness of the population. */
		uint getNumIndividuals() { return individuals.size(); } /** Get the number of Individual in this Habitat. */

		/** Trains the Predator on the Habitat. */
		void trainPredator(bool init);

		/** Creates a new population from the old one. */
		void replicate();


	private:
		PopulationGenerator* pg; /** The random number generator. */
		std::vector<Individual> individuals; /** The list of Individual living in this habitat */
		const uint type; /** The habitat type */
		Predator* predator; /** The Predator */

		/** Creates a random background sample. */
		DataTools::Pattern createBackground();
		/** Creates a random Individual and returns it as a pattern. */
		DataTools::Pattern createIndividual();
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
