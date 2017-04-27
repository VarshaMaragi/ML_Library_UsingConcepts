#include<stdio.h>

#include <iostream>
#include <numeric>
//#include "DataforClassification.h"
//#include "LabelsforClassification.h"
#include "ConceptDef.h"
using namespace std;
#include <fstream>
#include "csv.h"
#include <sstream> 
using namespace io;



struct OnlinePerceptron
{
public:

	
	//Uses data as a stream of values
	using Data_type=stringstream;
	using Label_type=stringstream;
	Data_type d;
	Label_type l;
	//Weights are calculated on the fly
	vector<int> weights;
	//Check if weights are initialized
	bool initialised = 0;


	
	
};
void classify(OnlinePerceptron &p,stringstream &x,stringstream &y)
	{

		
		
		string s;
		
		//Convert stream to vector
		vector<int> xvec;
		
		while(getline(x, s, ','))
		{
			xvec.push_back(stoi(s));
			
		}

		//The last element of the stream is the y value
		int yvec=xvec[xvec.size()-1];

		//Initialize the weights vector
		if (!p.initialised)
		{
			vector<int> temp(xvec.size(), 0);
			p.weights = temp;
			p.initialised=1;
		}
		

		//Append one		
		xvec.insert(xvec.begin(),1);

		//Remove the y value
		xvec.pop_back();
		int numberoffeatures=xvec.size();
		
		if(yvec*(inner_product(begin(xvec), end(xvec), begin(p.weights), 0.0))<=0)
		{
			for(int j=0;j<numberoffeatures;j++)
				p.weights[j]=p.weights[j]+yvec*xvec[j];
				
		}
		
		int j;

		//Print the weights vector after every example
		cout<<"----------Weights vector------------"<<endl;
		for(j=0;j<numberoffeatures;j++)
		{
			cout<<p.weights[j]<<",";
		}
		cout<<"-------------------------------------"<<endl;
		
		//cout<<"train the model\n";
	};
	