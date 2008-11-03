#ifndef _PopulationGenerator_h_
#define _PopulationGenerator_h_

#include <neuralnethack/Config.hh>
#include <neuralnethack/datatools/DataSet.hh>

#include <stdio.h>
#include <gsl/gsl_rng.h>

class PopulationGenerator
{
	public:
		PopulationGenerator() { gsl_rng_env_setup(); T = gsl_rng_default; r = gsl_rng_alloc (T); }
		~PopulationGenerator() { gsl_rng_free (r); }
		double drawRandomNumber();
		DataTools::DataSet* createInitialDataSet();
	private:
		const gsl_rng_type * T;
		gsl_rng * r;

};

inline double PopulationGenerator::drawRandomNumber() { return gsl_rng_uniform (r); }

#endif
