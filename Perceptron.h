#include<stdio.h>
#include<iostream>
//#include "DataforClassification.h"
//#include "LabelsforClassification.h"
#include "ConceptDef.h"
using namespace std;

struct My_Data
{
using data_type=data1;
data_type val;

data_type value() const { return val; }
void value(const data_type& v){val=v;};
};

struct My_Label
{
	using label_type=labels;
	label_type val;
	label_type value() const {return val;}
	void value(const label_type& v){val=v;};
};

struct Perceptron
{
public:

	//using datatype=data1;
	//using labelstype=labels;
	using Data_type=My_Data;
	using Label_type=My_Label;


	//DataforClassification d=new DataforClassification();
	//LabelsforClassification l= new LabelsforClassification();
	
	
};
void train(Perceptron &p,My_Data &x,My_Label &y)
	{
		cout<<"train the model\n";
	};
	void classify(Perceptron &p,My_Data &x)
	{
		cout<<"classify the data\n";
	};