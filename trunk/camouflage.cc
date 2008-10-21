#include <vector>
#include <string>

#include <neuralnethack/Config.hh>
#include <neuralnethack/mlp/Mlp.hh>

using std::string;
using std::vector;

using namespace NeuralNetHack;
using namespace MultiLayerPerceptron;

Mlp* createMlp()
{
	vector<uint> arch; arch.push_back(8); arch.push_back(1); arch.push_back(1);
	vector<string> types; types.push_back("tansig"); types.push_back("logsig");
	Mlp* mlp = new Mlp(arch, types, false);
	return mlp;
}

bool trainMlp(Mlp* mlp)
{
	return true;
}

bool cleanup(Mlp* mlp)
{
	if(mlp != 0) delete mlp;
	return true;
}

int main(int argc, char* argv[])
{
	Mlp* mlp = createMlp();
	trainMlp(mlp);

	/*while(){
		scoreIndividuals();
		killOffPrey();
		migrate();
		replicate();
	}*/
	cleanup(mlp);
	return EXIT_SUCCESS;
}
