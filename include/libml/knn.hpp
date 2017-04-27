#ifndef LIBML_KNN_H
#define LIBML_KNN_H

#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <map>
#include <math.h>
#include <vector>
#include "naive_bayes.hpp"

namespace libml {
class KNN
{
public:

	//using datatype=data1;
	//using labelstype=labels;

	using Data_type = libml::matrix2<double>;;
	using Label_type = std::vector<int>;
	Data_type d;
	Label_type l;


	//DataforClassification d=new DataforClassification();
	//LabelsforClassification l= new LabelsforClassification();
	
	void train(Data_type& x, Label_type& y)
	{
		std::cout<<"Inside KNN";
		/*ofstream f;
		f.open ("outputknn.txt");
		int numberoffeatures=x[0].size()+1;
		int numberofexamples=x.size();
		vector<int> weights;
		for(int i=0;i<numberoffeatures;i++)
			weights.push_back(0);
		for(int i=0;i<numberofexamples;i++)
		{
			x[i].insert(x[i].begin(),1);
		}

		cout<<"Data size"<<x[0].size();
		for(int i=0;i<numberofexamples;i++)
		{
			for(int j=0;j<numberoffeatures;j++)
			{
				cout<<x[i][j]<<" ";
			}
			cout<<endl;
		}*/


		/*int flag=1;
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
		}*/
			





		std::cout<<"train the model\n";
	};

	void classify(Data_type& testdata)
	{
		std::cout<<"classify the data\n";
		std::cout<<"Inside KNN classify";
		std::ofstream f;
		f.open ("outputknn.txt");
		std::vector<std::vector<int>> x;
		//x=p.d; // FIXME: p is never defined!
		int numberoffeatures=x[0].size();
		int numberofexamples=x.size();
		std::vector<int> weights;
		for(int i=0;i<numberoffeatures;i++)
			weights.push_back(0);
		

		std::cout<<"Data size"<<x[0].size();
		for(int i=0;i<numberofexamples;i++)
		{
			for(int j=0;j<numberoffeatures;j++)
			{
				std::cout<<x[i][j]<<" ";
			}
			std::cout << std::endl;
		}
		
		std::vector<int> predy;
		//std::vector<int> y=p.l; // FIXME: p is never defined!
		for(int j=0;j<testdata.size();j++)
		{
			
			std::vector<double> eucdist;
			for(int i=0;i<numberofexamples;i++)
			{
				std::vector<double> dist;
				std::transform(x[i].begin(), x[i].end(), testdata[j].begin(), std::back_inserter(dist),
    			[&](int a, int b) { return ((a-b)*(a-b)); });

    			int sum = std::accumulate(dist.begin(), dist.end(), 0);
    			eucdist.push_back(sqrt(sum));


			}
			std::vector<std::pair<int,int>> p;
			for(int i=0;i<eucdist.size();i++)
			{
				p.push_back(std::make_pair(eucdist[i], i));

			}

			std::sort(p.begin(),p.end());
			//K=3 assumption
			int classy=0;
			for(int i=0;i<5;i++)
			{
				//cout<<"pi first"<<p[i].first<<endl;
				//cout<<"pi"<<y[p[i].second]<<endl;
				//classy=classy+(y[p[i].second]); // FIXME: p is never defined!
			}

			//Assuming the classes are 1 and -1
			if(classy>0)
				predy.push_back(1);
			else
				predy.push_back(-1);
		}

		for(int j=0;j<predy.size();j++)
		{
			std::cout << predy[j];
		}


	};
	
};
} // namespace libml

#endif // ifndef LIBML_KNN_H
