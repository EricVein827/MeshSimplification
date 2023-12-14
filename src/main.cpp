#include "Simplification.h"


int main(int argc, char* argv[])
{
	// ************************************  basic *******************************************
	const string fileName = "Buddha.obj";
	Simplification* meshSimplify = new Simplification(fileName);
	meshSimplify->setRatio(0.1);
	clock_t start = clock();
	meshSimplify->initialize();
	clock_t end = clock();
	cout << "initialize model cost " << end - start << " ms" << endl;

	start = clock();
	meshSimplify->simplify();
	end = clock();
	cout << "simplify model cost " << end - start << " ms" << endl;

	meshSimplify->output();
	return 0;
}