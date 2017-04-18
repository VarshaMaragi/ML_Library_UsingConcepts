#include<stdio.h>
#include<iostream>
#include <map>
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
		cout<<"Inside naive bayes";
		ofstream f;
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
		}

		map<int,int> prior;
		map<int,int>::iterator it;
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
			cout<<"prior";
			cout<<it->first;
			cout<<it->second<<endl;it++;
		}
	};
	void classify(NaiveBayes &p,data1 &x)
	{
		cout<<"classify the data(NaiveBayes)\n";
	};