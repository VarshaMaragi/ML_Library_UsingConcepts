#ifndef LIBML_PERCEPTRON_H
#define LIBML_PERCEPTRON_H

#include<stdio.h>
#include <iostream>
#include <numeric>
//#include "DataforClassification.h"
//#include "LabelsforClassification.h"
#include "ConceptDef.h"
using namespace std;
#include <fstream>

namespace libml {
class Perceptron
{
private:
	std::vector<int> weights;

public:
	//using datatype=data1;
	//using labelstype=labels;

	using Data_type=data1;
	using Label_type=labels;
	Data_type d;
	Label_type l;


	//DataforClassification d=new DataforClassification();
	//LabelsforClassification l= new LabelsforClassification();
	
	void train(data1& x, labels& y) {
		std::ofstream f;
		f.open ("trainingweights.txt");

		// TODO: Need to make sure that every data entry
		// has the same number of features and throw an
		// exception if not.
		int numberoffeatures=x[0].size()+1;
		int numberofexamples=x.size();

		for(int i=0;i<numberoffeatures;i++)
			weights.push_back(0);

		for(int i=0;i<numberofexamples;i++)
		{
			x[i].insert(x[i].begin(),1);
		}

		std::cout<<"Data size"<<x[0].size();
		for(int i=0;i<numberofexamples;i++)
		{
			for(int j=0;j<numberoffeatures;j++)
			{
				cout<<x[i][j]<<" ";
			}
			cout<<endl;
		}


		int flag=1;
		while(flag==1)
		{
			flag=0;
			for(int i=0;i<numberofexamples;i++)
			{
				if(y[i]*(inner_product(begin(x[i]), end(x[i]), begin(weights), 0.0))<=0)
				{
					for(int j=0;j<numberoffeatures;j++)
						weights[j]=weights[j]+y[i]*x[i][j];
					flag=1;
				}
			}
			int j;
			for(j=0;j<numberoffeatures-1;j++)
			{
			f<<weights[j]<<",";
			}
			f<<weights[j]<<"\n";
		}

		std::cout<<"train the model\n";
	}

	void classify(data1& x) {
		std::cout<<"classify the data\n";
	}
};
} // namespace libml

#endif // ifndef LIBML_PERCEPTRON_H
