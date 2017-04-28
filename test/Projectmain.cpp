#include <cstdio>
#include <iostream>
#include <libml/csv.hpp>
#include <libml/functions.hpp>
#include <libml/linear_regression.hpp>
#include <libml/kmeans.hpp>
#include <libml/knn.hpp>
#include <libml/naive_bayes.hpp>
#include <libml/online_perceptron.hpp>
#include <libml/perceptron.hpp>

using namespace std;

int main()
{

	
	

	//Test cases for all the models
	vector<vector<int>> perceptrondata;
	vector<vector<int>> parseddata;
	vector<int> perceptronlabels;

        int col_1, col_2, col_3, col_4, col_5;

        io::CSVReader<3> in_pinp("data/perceptroninput.csv");
        while(in_pinp.read_row(col_1, col_2, col_3)) {
                parseddata.push_back({col_1, col_2, col_3});
                perceptronlabels.push_back(col_3);
                perceptrondata.push_back({col_1, col_2});
        }
	

	//Create a perceptron object
        libml::Perceptron p;
	p.d=perceptrondata;
	
	p.l=perceptronlabels;

	//Call the train function
        libml::train_classification(p,p.d,p.l);
	

	//Create perceptron test data
	vector<vector<int>> perceptrontestdata;
	 
        io::CSVReader<2> in_ptest("data/perceptrontestdatainp.csv");
        while(in_ptest.read_row(col_1, col_2)) {
                perceptrontestdata.push_back({col_1, col_2});
        }

        vector<int> pred_labels = libml::predict_classification(p,perceptrontestdata);


	//testing the perceptron.(Hardcoding the true labels for the corresponding test data to check the accuracy)
	vector<int> trainy={-1,1,1,1}; 
	float acc=libml::accuracy(trainy,pred_labels);
	cout<<"Accuracy of the classifier"<<acc;
	

	//Create training data for naive bayes model
	vector<vector<int>> nbdata;
	vector<int> nblabels;

	io::CSVReader<4> in_nbinp("data/naivebayesinp.csv");
        while(in_nbinp.read_row(col_1, col_2, col_3, col_4)) {
                nbdata.push_back({col_1, col_2, col_3});
                nblabels.push_back(col_4);
        }
       

    //Call the model
        libml::NaiveBayes nb;
	nb.d=nbdata;
	nb.l=nblabels;
	
	//train the naive bayes classifier
        libml::train_classification(nb,nb.d,nb.l);
	
	vector<vector<int>> nbtestdata;
	
	//test the Naive Bayes classifier
	io::CSVReader<3> in_nbtest("data/nbtestdatainp.csv");
        while(in_nbtest.read_row(col_1, col_2, col_3)) {
                nbtestdata.push_back({col_1, col_2, col_3});
        }

        vector<int> pred_classes = libml::predict_classification(nb,nbtestdata);

	
	float accnb=libml::accuracy(trainy,pred_classes);
	cout<<"Accuracy of the classifier"<<accnb;

	//Train and Test the knn model
        libml::KNN knn;
	knn.d=perceptrondata;
	knn.l=perceptronlabels;
	 
	knn.k=(int)8;


        libml::train_classification(knn,knn.d,knn.l);
	vector<vector<int>> knntestdata;
	vector<vector<string>> parseddataknn;
	cout<<"in here";

	io::CSVReader<2> in_knntestinp("data/knntestdatainp.csv");
        while(in_knntestinp.read_row(col_1, col_2)) {
                knntestdata.push_back({col_1, col_2});
        } 
	
	//  //knntestdata={{8,-11},{14,-3}};
        pred_classes = libml::predict_classification(knn,knntestdata);
	 //testing the KNN classifier
	
	float accknn=libml::accuracy(trainy,pred_classes);
	cout<<"Accuracy of the classifier"<<accknn;


	// Read Data
	io::CSVReader<3> in_input2("data/input2.csv");
	in_input2.set_header("age", "weight", "height");

	vector<vector<double>> train_data;
	vector<vector<double>> test_data;
	vector<double> train_labels;
	double age, weight, height;

	while(in_input2.read_row(age, weight, height))
	{
		train_data.push_back({1, age, weight});
		test_data.push_back({1, age, weight});
		train_labels.push_back(height);
	}

	vector<double> mean = libml::calculate_mean(train_data);
	vector<double> std = libml::calculate_std(train_data);
	
	int nSamples = train_data.size();	
	int nDimensions = train_data[0].size();

	for (int j = 1; j < nDimensions; j++)
	{
		for (int i = 0; i < nSamples; i++)
		{
			train_data[i][j] -= mean[j];
			train_data[i][j] /= std[j];
		}
	}

	/* ###### Linear Regression ###### */
        libml::LinearRegression lr;
	cout << "Calling Linear Regression train" << endl;
        libml::train_regression(lr, train_data, train_labels);

	cout << "Calling Linear Regression Predict" << endl;
	//auto predicted_labels = libml::predict_regression(lr, test_data);



	//Create an online perceptron model
        libml::OnlinePerceptron op;
	
	libml::OnlinePerceptron::Label_type l;
	ifstream file("perceptroninput.csv");

	string line;
	
/*	while(getline(file,line))
	{
                libml::OnlinePerceptron::Data_type s;
		s<<line;
		//Pass the csv stream
                libml::train_classification(op,s,l);
		s.str(string());

	}*/

        cout<<endl<<"Testing K-Means"<<endl;
	
	

	/* ###### K-Means ###### */
	double d1, d2, d3, d4;
	string s;
	io::CSVReader<5> km_data("data/iris.data.txt");
	vector<vector<double>> asd;
	while(km_data.read_row(d1, d2, d3, d4, s))
	{
		// cout << d1;
		asd.push_back({d1,d2,d3,d4});
	}

        libml::KMeans km;
	//x has the predicted values
	libml::train_unsupervised(km, asd);
	// for (auto l : x)
	// {
	// 	cout << l << endl;
	// }




	
	return 1;
}
