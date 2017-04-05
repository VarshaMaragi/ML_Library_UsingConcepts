#include<stdio.h>
#include<iostream>
#include "NaiveBayes.h"

using namespace std;

int main()
{


	
	vector<vector<int>> perceptrondata;


	//Creating a dummy dataset
	for(int j=0;j<3;j++)
	{
		vector<int> temp;
		for(int i=0;i<10;i++)
		{	
			temp.push_back(j+i);
		}
		perceptrondata.push_back(temp);
	}
	vector<int> perceptronlabels;
	for(int i=0;i<3;i++)
	{
		perceptronlabels.push_back(1);
	}


	Perceptron p;
	p.d=perceptrondata;
	
	cout<<"First element of the training data  "<<p.d[2][1]<<endl;

	p.l=perceptronlabels;
	
	cout<<"First element of the training label  "<<p.l[0]<<endl;




	NaiveBayes nb;
	nb.d=perceptrondata;
	
	cout<<"First element of the training data  "<<nb.d[2][1]<<endl;

	nb.l=perceptronlabels;
	
	cout<<"First element of the training label  "<<nb.l[0]<<endl;

	
	check(p,p.d,p.l);
	check(nb,nb.d,nb.l);

	/*NB_Data nd;
	nd.val=perceptrondata;

	NB_Label nl;
	nl.val=perceptronlabels;
	NaiveBayes nb;
	check(nb,nd,nl);*/
	//Creating a My_Data object
	/*My_Data md;
	data1 dt;
	
	dt.d=perceptrondata;
	
	//Set the value
	md.value(dt);

	//cout<<md.val.d.size();
	
	//Get the first element
	cout<<"First element of the training data  "<<md.value().d[0][1]<<endl;


	//Creating a My_Label object
	My_Label ml;
	labels l1;
	l1.l=perceptronlabels;

	//Set the label value
	ml.value(l1);

	//Get the first label
	cout<<"First element of the training label  "<<ml.value().l[0]<<endl;
	Perceptron p;

	//check if it satisfies the classification concept
	check(p,md,ml);*/
	return 1;
}