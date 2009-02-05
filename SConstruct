import os
env = Environment(ENV = {'PATH' : os.environ['PATH']});
env.Program('camouflage',
		['camouflage.cc', 'Habitat.cc', 'Predator.cc', 'Individual.cc',
		'NeuralNetworkKeeper.cc', 'PopulationGenerator.cc'], 
		CXXFLAGS='$CXXFLAGS -Wall -pedantic -g3 -gdwarf-2 -O0',
		CCFLAGS='-I/home/michael/include', 
		LIBS=['libneuralnethack', 'gsl', 'gslcblas', 'm'], 
		LIBPATH='/home/michael/lib')
env.Program('testNeuralNetworkKeeper',
		['testNeuralNetworkKeeper.cc', 'Habitat.cc', 'Predator.cc', 'Individual.cc',
		'NeuralNetworkKeeper.cc', 'PopulationGenerator.cc'], 
		CXXFLAGS='$CXXFLAGS -Wall -pedantic -g3 -gdwarf-2 -O0',
		CCFLAGS='-I/home/michael/include', 
		LIBS=['libneuralnethack', 'gsl', 'gslcblas', 'm'], 
		LIBPATH='/home/michael/lib')
