#include<stdio.h>
#include<iostream>
//#include "KNN.h"
#include "Perceptron.h"
//#include "NaiveBayes.h"
#include "parsecsv.h"
#include "functions.hpp"
using namespace std;

int main()
{

	
	
	vector<vector<int>> perceptrondata;
	vector<vector<string>> parseddata;
	vector<int> perceptronlabels;
	parseddata=parsefile("perceptroninput.csv");
	//parseddata=parsefile("naivebayesinp.csv");
	for(int i=0;i<parseddata.size();i++)
	{
		perceptronlabels.push_back(stoi(parseddata[i][parseddata[0].size()-1]));
	}
	//Creating a dummy dataset

	for(int i=0;i<parseddata.size();i++)
	{
		vector<int> temp;
		for(int j=0;j<parseddata[0].size()-1;j++)
		{
			temp.push_back(stoi(parseddata[i][j]));
		}
		perceptrondata.push_back(temp);
	}
	


	Perceptron p;
	p.d=perceptrondata;
	
	//cout<<"First element of the training data  "<<p.d[2][1]<<endl;

	p.l=perceptronlabels;

	train_Classifier(p,p.d,p.l);
	//cout<<"First element of the training label  "<<p.l[0]<<endl;

	 vector<vector<int>> perceptrontestdata;
	vector<vector<string>> parseddatap;
	cout<<"in here";
	 //vector<vector<string>> knntestdata;
	 parseddatap=parsefile("perceptrontestdatainp.csv");
	 for(int i=0;i<parseddatap.size();i++)
	{
		vector<int> temp;
		for(int j=0;j<parseddatap[0].size();j++)
		{
			temp.push_back(stoi(parseddatap[i][j]));
			//cout<<"knn"<<temp[j];
		}
		perceptrontestdata.push_back(temp);
	}

	test_Classifier(p,perceptrontestdata);




	// NaiveBayes nb;
	// nb.d=perceptrondata;
	
	// //cout<<"First element of the training data  "<<nb.d[2][1]<<endl;

	// nb.l=perceptronlabels;
	
	// //cout<<"First element of the training label  "<<nb.l[0]<<endl;

	// //  KNN knn;
	// //  knn.d=perceptrondata;
	// //  knn.l=perceptronlabels;
	 
	// //  knn.k=(int)3;

	
	// // // train_Classifier(p,p.d,p.l);
	// train_Classifier(nb,nb.d,nb.l);
	// cout<<"NB PARAMETER"<<nb.logparameter.size()<<endl;
	//  vector<vector<int>> nbtestdata;
	// vector<vector<string>> parseddatanb;
	// cout<<"in here";
	//  //vector<vector<string>> knntestdata;
	//  parseddatanb=parsefile("nbtestdatainp.csv");
	//  for(int i=0;i<parseddatanb.size();i++)
	// {
	// 	vector<int> temp;
	// 	for(int j=0;j<parseddatanb[0].size();j++)
	// 	{
	// 		temp.push_back(stoi(parseddatanb[i][j]));
	// 		//cout<<"knn"<<temp[j];
	// 	}
	// 	nbtestdata.push_back(temp);
	// }

	// test_Classifier(nb,nbtestdata);

	// train_Classifier(knn,knn.d,knn.l);
	// vector<vector<int>> knntestdata;
	// vector<vector<string>> parseddataknn;
	// cout<<"in here";
	//  //vector<vector<string>> knntestdata;
	//  parseddataknn=parsefile("knntestdatainp.csv");
	//  for(int i=0;i<parseddataknn.size();i++)
	// {
	// 	vector<int> temp;
	// 	for(int j=0;j<parseddataknn[0].size();j++)
	// 	{
	// 		temp.push_back(stoi(parseddataknn[i][j]));
	// 		//cout<<"knn"<<temp[j];
	// 	}
	// 	knntestdata.push_back(temp);
	// }

	
	//  //knntestdata={{8,-11},{14,-3}};
	// test_Classifier(knn,knntestdata);
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
