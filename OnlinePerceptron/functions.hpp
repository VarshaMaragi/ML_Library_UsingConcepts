#include "ConceptDef.h"
#include <iostream>

void train_checkol(OnlineLearningClassify &x,stringstream &streamd,stringstream &ls)
{
	cout<<"Online streaming\n";
	classify(x,streamd,ls);
}


void train_Classifier(Classification &x,data1 &md,labels &ml)
{
	cout<<"Check the classifier\n";
	train(x,md,ml);
}

void test_Classifier(Classification &x,data1 &td)
{
	cout<<"Test the classifier\n";
	classify(x,td);
}