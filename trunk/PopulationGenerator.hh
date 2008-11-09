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
		PopulationGenerator() { gsl_rng_env_setup(); T = gsl_rng_default; r = gsl_rng_alloc (T); }
		~PopulationGenerator();
		double drawRandomNumber() { return gsl_rng_uniform (r); }
		DataTools::DataSet* createInitialDataSet(uint n);

		DataTools::Pattern createIndividual();
		DataTools::Pattern createBackground1();
		DataTools::Pattern createBackground2();
	private:
		const gsl_rng_type * T;
		gsl_rng * r;

};

#endif
