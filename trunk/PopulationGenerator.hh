#ifndef _PopulationGenerator_h_
#define _PopulationGenerator_h_

#include <neuralnethack/Config.hh>
#include <neuralnethack/datatools/DataSet.hh>
#include <neuralnethack/datatools/Pattern.hh>

#include <stdio.h>
#include <gsl/gsl_rng.h>

class PopulationGenerator
{
	public:
		PopulationGenerator(); 
		~PopulationGenerator();
		double drawRandomNumber() { return gsl_rng_uniform (r); }
		uint drawRandomNumber(uint x) { return gsl_rng_uniform_int (r, x); }
		DataTools::DataSet* createInitialDataSet(uint n);

		DataTools::Pattern createIndividual();
		DataTools::Pattern createBackground1();
		DataTools::Pattern createBackground2();

	private:
		const gsl_rng_type* T;
		gsl_rng* r;
};

#endif
