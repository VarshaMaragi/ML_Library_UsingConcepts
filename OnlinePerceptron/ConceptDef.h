#include<stdio.h>
#include<iostream>
#include<vector>
#include "csv.h"
#include <sstream> 
//#include "LinearRegression.h"

using namespace std;

using data1=vector<vector<int>>;
using labels=vector<int>;
using datas=stringstream;
using datal=stringstream;

//Concept for classification
template<typename T>
concept bool Classification =  requires()
	{

		typename T::Data_type;
		typename T::Label_type;
		//requires Data<typename T::Data_type>;
		//requires Labels<typename T::Label_type>;
		
}&&requires(T t, typename T::Data_type d,typename T::Label_type l){
	train(t,d,l);
		classify(t,d);
};

template<typename T>
concept bool OnlineLearningClassify =requires()
{
	typename T::Data_stream;
	typename T::Label_stream;
}&&requires(T t,typename T::Data_stream d,typename T::Label_stream l)
{
	classify(t,d,l);

};










