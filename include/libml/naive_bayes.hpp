#ifndef LIBML_NAIVEBAYES_H
#define LIBML_NAIVEBAYES_H

#include<stdio.h>
#include<iostream>
#include <map>
//#include "DataforClassification.h"
//#include "LabelsforClassification.h"
#include "perceptron.hpp"

namespace libml {
class NaiveBayes
{
public:

        using Data_type = libml::matrix2<double>;
        using Label_type = std::vector<int>;
	
	Data_type d;
	Label_type l;

	void train(Data_type& x, Label_type& y)
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
			std::cout<<std::endl;
		}

		std::map<int,int> prior;
		std::map<int,int>::iterator it;
		for(int i=0;i<numberofexamples;i++)
		{
			it=prior.find(y[i]);
			if(it==prior.end())
			{
				prior.insert(std::pair<int,int>(y[i],1));
			}
			else
				prior[y[i]]=prior[y[i]]+1;
		}


		it=prior.begin();
		while(it!=prior.end())
		{
			std::cout<<"prior";
			std::cout<<it->first;
			std::cout<<it->second<<std::endl;it++;
		}
	};
	void classify(Data_type& x)
	{
		std::cout<<"classify the data(NaiveBayes)\n";
	};
	
};
} // namespace libml

#endif // ifndef LIBML_NAIVEBAYES_H
