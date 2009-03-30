import os
env = Environment(ENV = {'PATH' : os.environ['PATH']});
common = ['Habitat.cc', 'Predator.cc', 'Individual.cc', 'NeuralNetworkKeeper.cc', 'PopulationGenerator.cc']
#camouflage_files = ['camouflage.cc'] + common
#test_files = ['testNeuralNetworkKeeper.cc'] + common
env.Library('camouflagebase', common, 
		CCFLAGS='-I/home/michael/include', 
		LIBS=['libneuralnethack', 'gsl', 'gslcblas', 'm'],
		LIBPATH='/home/michael/lib'
		)
env.Program('camouflage', 'camouflage.cc',
		CXXFLAGS='$CXXFLAGS -Wall -pedantic -g3 -gdwarf-2 -O0',
		CCFLAGS=['-I/home/michael/include','-I.'], 
		LIBS=['libneuralnethack', 'gsl', 'gslcblas', 'm', 'camouflagebase'], 
		LIBPATH=['/home/michael/lib','.'])
env.Program('testNeuralNetworkKeeper', 'testNeuralNetworkKeeper.cc',
		CXXFLAGS='$CXXFLAGS -Wall -pedantic -g3 -gdwarf-2 -O0',
		CCFLAGS='-I/home/michael/include', 
		LIBS=['libneuralnethack', 'gsl', 'gslcblas', 'm', 'camouflagebase'], 
		LIBPATH=['/home/michael/lib','.'])
