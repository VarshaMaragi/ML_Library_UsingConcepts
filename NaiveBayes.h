#ifndef LIBML_NAIVEBAYES_H
#define LIBML_NAIVEBAYES_H

#include<stdio.h>
#include<iostream>
#include <map>
//#include "DataforClassification.h"
//#include "LabelsforClassification.h"
#include "Perceptron.h"

namespace libml {
class NaiveBayes
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
	
	void train(data1 &x,labels &y)
	{
		std::cout<<"train the model(NaiveBayes)\n";
		std::cout<<"Inside naive bayes";
		std::ofstream f;
		f.open ("outputknn.txt");
		int numberoffeatures=x[0].size()+1;
		int numberofexamples=x.size();
		std::vector<int> weights;
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
				std::cout<<x[i][j]<<" ";
			}
			std::cout<<endl;
		}

		std::map<int,int> prior;
		std::map<int,int>::iterator it;
		for(int i=0;i<numberofexamples;i++)
		{
			it=prior.find(y[i]);
			if(it==prior.end())
			{
				prior.insert(pair<int,int>(y[i],1));
			}
			else
				prior[y[i]]=prior[y[i]]+1;
		}


		it=prior.begin();
		while(it!=prior.end())
		{
			std::cout<<"prior";
			std::cout<<it->first;
			std::cout<<it->second<<endl;it++;
		}
	};
	void classify(data1 &x)
	{
		std::cout<<"classify the data(NaiveBayes)\n";
	};
	
};
} // namespace libml

#endif // ifndef LIBML_NAIVEBAYES_H
