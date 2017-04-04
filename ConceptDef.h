#include<stdio.h>
#include<iostream>
#include<vector>
//#include "LinearRegression.h"

using namespace std;

struct data1
{
	vector<vector<int>> d;
};
struct labels
{
	vector<int> l;
};


/*template<class T> concept bool Data=requires(T t){
	typename T::datatype;

};
template<class T> concept bool Labels=requires(T t) {
	typename T::labelstype;
};*/
/*template<typename T> concept bool Regression=//requires() {
//typename T::dataforreg;
//typename T::labelforreg;
//requires Data<typename T::dataforreg>;
//requires Labels<typename T::labelforreg>;
//}&&
requires(T t,typename T::dataforreg d,typename T::labelforreg l)
{t.train(d, l);
t.regress(d);
};
template<typename T,typename Data,typename Labels> concept bool Classification= requires(T t, Data d, Labels l) {
t.train(d, l);
t.classify(d);
};
template<typename T,typename Data,typename Inputstream> concept bool OnlineLearningRegression=requires(T t,Inputstream
a,Data d)
{
t.train(a);
t.regress(d);
};
template<typename T,typename Data,typename Inputstream> concept bool OnlineLearningClassify=requires(T t,Inputstream a,Data d)
{
t.train(a);
t.classify(d);
};*/

template<typename T>
concept bool Data=requires(T t)
{
	typename T::data_type;
};

template<typename T>
concept bool Labels=requires(T t)
{
	typename T::label_type;
};

template<typename T>
concept bool Classification =  requires()
	{

		typename T::Data_type;
		typename T::Label_type;
		requires Data<typename T::Data_type>;
		requires Labels<typename T::Label_type>;
		
}&&requires(T t, typename T::Data_type d,typename T::Label_type l){
	train(t,d,l);
		classify(t,d);
};

void check(Classification &x)
{
	cout<<"Check the classifier";
}








