#ifndef LIBML_PERCEPTRON_H
#define LIBML_PERCEPTRON_H

#include <cstdio>
#include <iostream>
#include <numeric>
#include <fstream>
#include <vector>
#include "helpers.hpp"
#include "concepts.hpp"

namespace libml {
class Perceptron
{
public:
	//using datatype=data1;
	//using labelstype=labels;

	using Data_type = libml::matrix2<double>;
	using Label_type = std::vector<int>;

	Data_type d;
	Label_type l;

        std::vector<int> weights;

	//DataforClassification d=new DataforClassification();
	//LabelsforClassification l= new LabelsforClassification();
	
	void train(Perceptron &p, Data_type& x, Label_type& y) {
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
				std::cout << x[i][j] << " ";
			}
			std::cout << std::endl;
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

        std::vector<int> classify(Data_type& x) {
                std::cout<<"classify the data\n";
                std::vector<int> predy;
		for(int i=0;i<x.size();i++)
		{
			x[i].insert(x[i].begin(),1);
		}
		for(int i=0;i<x.size();i++)
		{
			
			predy.push_back(inner_product(begin(x[i]), end(x[i]), begin(weights), 0.0));
			
		}
		for(int i=0;i<x.size();i++)
		{
			if(predy[i]<0)
			{
			
			predy[i]=-1;
			}
			else
			{
				
				predy[i]=1;
			}

		}

                return predy;
	}
};
} // namespace libml

#endif // ifndef LIBML_PERCEPTRON_H
