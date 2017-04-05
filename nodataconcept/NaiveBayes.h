#include<stdio.h>
#include<iostream>
//#include "DataforClassification.h"
//#include "LabelsforClassification.h"
#include "Perceptron.h"
using namespace std;

struct NaiveBayes
{
public:

	//using datatype=data1;
	//using labelstype=labels;
	using Data_type=data1;
	using Label_type=labels;
	Data_type d;
	Label_type l;

	//DataforClassification d=new DataforClassification();
	//LabelsforClassification l= new LabelsforClassification();
	
	
};
void train(NaiveBayes &p,data1 &x,labels &y)
	{
		cout<<"train the model(NaiveBayes)\n";
	};
	void classify(NaiveBayes &p,data1 &x)
	{
		cout<<"classify the data(NaiveBayes)\n";
	};