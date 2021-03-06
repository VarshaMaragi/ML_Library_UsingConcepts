/**
 * @file perceptron.hpp
 * @brief Contains the perceptron implementation
 */

#ifndef LIBML_PERCEPTRON_H
#define LIBML_PERCEPTRON_H

#include <cstdio>
#include <iostream>
#include <numeric>
#include <fstream>
#include <vector>
#include <stdexcept>
#include "helpers.hpp"
#include "concepts.hpp"

namespace libml {

        /**
         * @brief Perceptron classification model
         *
         * The perceptron is a #Classification algorithm that
         * makes predictions based on a linear predictor
         * function.
         *
         * The perceptron is adapatable for online learning
         * since it only processes elements in the training
         * set one at a time. This functionality is available
         * via the #OnlinePerceptron.
         */
class Perceptron
{
public:
	//using datatype=data1;
	//using labelstype=labels;

	using Data_type = libml::matrix2<int>;
	using Label_type = std::vector<int>;

        using Data_primitive = int;
        using Label_primitive = int;

	Data_type d;
	Label_type l;

        std::vector<int> weights;

	//DataforClassification d=new DataforClassification();
	//LabelsforClassification l= new LabelsforClassification();

        /**
         * @brief Trains the perceptron on a pre-created set of data
         */
	void train(Data_type& x, const Label_type& y) {
                std::ofstream f;
		f.open ("trainingweightsperceptron.txt");
		int numberoffeatures=x[0].size()+1;
		int numberofexamples=x.size();


		if (x.size() != y.size())
		{
        	throw std::invalid_argument( "No. of rows in Train data and Train Labels must be equal");
		}



		//Initialize the weights vector to zero
		for(int i=0;i<numberoffeatures;i++)
			weights.push_back(0);


		//Prepend ones to the x values 
		for(int i=0;i<numberofexamples;i++)
		{
			x[i].insert(x[i].begin(),1);
		}

		
		//Train the classifier untill all the examples are correctly classified
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

			//Write the weight vectors to a file
			for(j=0;j<numberoffeatures-1;j++)
			{
			f<<weights[j]<<",";
			}
			f<<weights[j]<<"\n";
		}
	}

        /**
         * @brief Classifies a set of sample points
         * @return A vector of ints (labels) corresponding to each row
         */
        std::vector<int> classify(Data_type& x) {
               // std::cout<<"classify the data\n";
                std::vector<int> predy;
		for(int i=0;i<x.size();i++)
		{
			x[i].insert(x[i].begin(),1);
		}
		for(int i=0;i<x.size();i++)
		{
			
			predy.push_back(inner_product(begin(x[i]), end(x[i]), begin(weights), 0.0));
			
		}

		std::ofstream f;
		f.open ("perceptronoutput.txt");
		for(int i=0;i<x.size();i++)
		{
			if(predy[i]<0)
			{
			
			predy[i]=-1;
			f<<"-1"<<"\n";
			}
			else
			{
				f<<"1"<<"\n";
				predy[i]=1;
			}

		}

                return predy;
	}
};
} // namespace libml

#endif // ifndef LIBML_PERCEPTRON_H
