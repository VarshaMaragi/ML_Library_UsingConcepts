#ifndef LIBML_NAIVEBAYES_H
#define LIBML_NAIVEBAYES_H

#include<stdio.h>
#include<iostream>
#include <map>
#include <numeric>
#include <stdexcept>
//#include "DataforClassification.h"
//#include "LabelsforClassification.h"
#include "perceptron.hpp"

namespace libml {
        class NaiveBayes
        {
                public:

                        using Data_type = libml::matrix2<int>;
                        using Label_type = std::vector<int>;

                        using Data_primitive = int;
                        using Label_primitive = int;

                        Data_type d;
                        Label_type l;

                        std::vector<std::vector<float>> logparameter;
                        std::vector<std::vector<float>> logoneminusparameter;
                        std::map<int, int> prior;

        void train(Data_type& x, Label_type& y)
        {

		if (x.size() != y.size())
		{
        	throw std::invalid_argument( "No. of rows in Train data and Train Labels must be equal");
		}

                prior.clear();
                logparameter.clear();
                logoneminusparameter.clear();
		
		int numberoffeatures=x[0].size();
		int numberofexamples=x.size();
		

               
                std::vector<std::vector<int>> transpose_x;
		//transpose_x = boost::numeric::ublas::trans(x);
		for(int i=0;i<numberofexamples;i++)
		{
			
			//If data has a class of -1 convert to 0
			if(y[i]==-1)
				y[i]=0;
			
		}


		//calculating the transpose
		for(int i=0;i<numberoffeatures;i++)
		{
                        std::vector<int> temp;
			for(int j=0;j<numberofexamples;j++)
			{
                                
				temp.push_back(x[j][i]	);
			}
			transpose_x.push_back(temp);
                        
		}


                std::map<int,int>::iterator it;
		//Adding the labels matrix for just 2 classes.Classes assumed to be 0 or 1.
                std::map<int,std::vector<int>> labelsmatrix;
                std::map<int,std::vector<int>>::iterator it2;
                std::vector<int> temp;
		labelsmatrix.insert(std::pair<int,std::vector<int>>(1,temp));
		labelsmatrix.insert(std::pair<int,std::vector<int>>(0,temp));

		//Calculate the labelsmatrix(a binary matrix of labels for each class).Calculate the prior
		for(int i=0;i<numberofexamples;i++)
		{
			it=prior.find(y[i]);
			if(y[i]==1)
			{
				labelsmatrix[1].push_back(1);
				labelsmatrix[0].push_back(0);
			}
			else
			{
				labelsmatrix[0].push_back(1);
				labelsmatrix[1].push_back(0);
			}
			
			if(it==prior.end())
			{
				prior.insert(std::pair<int,int>(y[i],1));
			}
			else
				prior[y[i]]=prior[y[i]]+1;
			
		}

		//Store the log of the prior
		it=prior.begin();
		while(it!=prior.end())
		{
			
			it->second=log(it->second/(y.size()));
			it++;

		}
		
		it2=labelsmatrix.begin();
        std::vector<std::vector<float>> parameter;
        std::vector<int> sumoflabelsmatrix;

		//Calculate the parameter matrix(x*labelsmatrix)
		while(it2!=labelsmatrix.end())
		{
                        std::vector<float> temp;
			for(int j=0;j<numberoffeatures;j++)
			{
				
				
				
				float ip=inner_product(begin(it2->second), end(it2->second), begin(transpose_x[j]), 0);

				
				temp.push_back(ip);
			}
			parameter.push_back(temp);
			it2++;
		}
		

		//Store the sum of labels matrix
		it2=labelsmatrix.begin();
		while(it2!=labelsmatrix.end())
		{
			int sum=std::accumulate(it2->second.begin(), it2->second.end(), 0);
			sumoflabelsmatrix.push_back(sum);
			it2++;
		}
		it=prior.begin();
		
		//Find the log parameters
		for(int i=0;i<parameter.size();i++)
		{
                        std::vector<float> temp1;
                        std::vector<float> temp2;
			for(int j=0;j<numberoffeatures;j++)
			{
				parameter[i][j]=(1+parameter[i][j])/(2+sumoflabelsmatrix[i]);
				
				temp1.push_back(log(parameter[i][j]));
				
				temp2.push_back(log(1-(parameter[i][j])));
			}
                        //std::cout<<std::endl;
			logparameter.push_back(temp1);
			logoneminusparameter.push_back(temp2);
		
		}
		

		//As it is Bernoulli we need (1-x) values.
                std::vector<std::vector<float>> oneminusx;
		for(int i=0;i<numberofexamples;i++)
		{
                        std::vector<float> temp;
			for(int j=0;j<numberoffeatures;j++)
			{
				temp.push_back(1-x[i][j]);
			}
			oneminusx.push_back(temp);
		}

		//Calculate the classifier first term and second term
                std::vector<std::vector<float>> classifier_first_term;
                std::vector<std::vector<float>> classifier_second_term;
		for(int j=0;j<logparameter.size();j++)
		{
                        std::vector<float> temp1;
                        std::vector<float> temp2;
			for(int i=0;i<numberofexamples;i++)
			{
				
			
				float ip=inner_product(begin(logparameter[j]), end(logparameter[j]), begin(x[i]), 0.0);
				float ip2=inner_product(begin(logoneminusparameter[j]), end(logoneminusparameter[j]), begin(oneminusx[i]), 0.0);
				
				temp1.push_back(ip);
				temp2.push_back(ip2);

			}	
			classifier_first_term.push_back(temp1);
			classifier_second_term.push_back(temp2);
		
		

		}

		//Calculate the matrix prob which estimates the y value by addind classifier first,second and third term
                std::vector<std::vector<float>> prob;
		for(int i=0;i<classifier_second_term.size();i++)
		{
                        std::vector<float> temp;
			for(int j=0;j<classifier_second_term[0].size();j++)
			{
				temp.push_back(classifier_second_term[i][j]+classifier_first_term[i][j]);
			}
			prob.push_back(temp);
		}

		//Adding prior to the matrix prob
		it=prior.begin();
		for(int i=0;i<parameter.size();i++)
		{
			for(int j=0;j<parameter[0].size();j++)
			{
				prob[i][j]=prob[i][j]+(prior[it->first]);
			}
			it++;
		}

                std::vector<int> predy;
		
		for(int i=0;i<numberofexamples;i++)
		{	
			//hardcoded for 2 classes
			float max=-1*std::numeric_limits<double>::infinity();
			int py;
			for(int j=0;j<2;j++)
			{
				if(prob[j][i]>max)
				{
					max=prob[j][i];
					py=j;
				}

			}
			predy.push_back(py);
			//Print the predicted y values for the training dataset
            //std::cout<<py<<std::endl;

		}
        }

        std::vector<int> classify(Data_type& x)
        {
		int numberoffeatures=x[0].size();
		int numberofexamples=x.size();
		
		
		
                std::vector<std::vector<int>> transpose_x;
		
		

		//calculating the transpose
		for(int i=0;i<numberoffeatures;i++)
		{
                        std::vector<int> temp;
			for(int j=0;j<numberofexamples;j++)
			{
                                
				temp.push_back(x[j][i]	);
			}
			transpose_x.push_back(temp);
			//std::cout<<std::endl;
		}


                


		//As it is Bernoulli calculate (1-x) for test data
                std::vector<std::vector<float>> oneminusx;
		for(int i=0;i<numberofexamples;i++)
		{
                        std::vector<float> temp;
			for(int j=0;j<numberoffeatures;j++)
			{
				temp.push_back(1-x[i][j]);
			}
			oneminusx.push_back(temp);
		}


		//Calculate the first and second term of the classifier
                std::vector<std::vector<float>> classifier_first_term;
                std::vector<std::vector<float>> classifier_second_term;
		for(int j=0;j<logparameter.size();j++)
		{
                        std::vector<float> temp1;
                        std::vector<float> temp2;
			for(int i=0;i<numberofexamples;i++)
			{
				
			
				float ip=inner_product(begin(logparameter[j]), end(logparameter[j]), begin(x[i]), 0.0);
				float ip2=inner_product(begin(logoneminusparameter[j]), end(logoneminusparameter[j]), begin(oneminusx[i]), 0.0);
				
				temp1.push_back(ip);
				temp2.push_back(ip2);

			}	
			classifier_first_term.push_back(temp1);
			classifier_second_term.push_back(temp2);
		
		

		}
                std::vector<std::vector<float>> prob;
		for(int i=0;i<classifier_second_term.size();i++)
		{
                        std::vector<float> temp;
			for(int j=0;j<classifier_second_term[0].size();j++)
			{
				temp.push_back(classifier_second_term[i][j]+classifier_first_term[i][j]);
			}
			prob.push_back(temp);
		}
		//Adding prior
                std::map<int,int>::iterator it;
		it=prior.begin();
		for(int i=0;i<logparameter.size();i++)
		{
			for(int j=0;j<logparameter[0].size();j++)
			{
				prob[i][j]=prob[i][j]+(prior[it->first]);
			}
			it++;
		}

                std:: vector<int> predy;
		
		for(int i=0;i<numberofexamples;i++)
		{	
			//Assuming data is for 2 classes
			float max=-1*std::numeric_limits<double>::infinity();
			int py;
			for(int j=0;j<2;j++)
			{
				if(prob[j][i]>max)
				{
					max=prob[j][i];
					py=j;
				}

			}
			predy.push_back(py);
			//Print predicted y values
            //std::cout<<py<<std::endl;

		}

                return predy;

        }
};
} // namespace libml

#endif // ifndef LIBML_NAIVEBAYES_H
