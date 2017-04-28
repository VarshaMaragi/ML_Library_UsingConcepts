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
#include <libml/ridge_regression.hpp>
#include <libml/lasso_regression.hpp>
using namespace std::chrono;
using namespace std;

int main()
{

	
	

	//Test cases for all the models
	vector<vector<int>> perceptrondata;
	vector<vector<int>> parseddata;
	vector<int> perceptronlabels;

        int col_1, col_2, col_3, col_4;

        io::CSVReader<3> in_pinp("data/perceptroninput.csv");
        while(in_pinp.read_row(col_1, col_2, col_3)) {
                parseddata.push_back({col_1, col_2, col_3});
                perceptronlabels.push_back(col_3);
                perceptrondata.push_back({col_1, col_2});
        }
	



	//Create a perceptron object
    cout<<"------------------Perceptron--------------------"<<endl<<endl;
    libml::Perceptron p;
	p.d=perceptrondata;
	
	p.l=perceptronlabels;

	//Call the train function
	//Measuring training time
	auto start1 = chrono::steady_clock::now();
    libml::train_classification(p,p.d,p.l);
	auto ei1= chrono::steady_clock::now();
	
	cout<<"Training time  "<<(ei1-start1).count()<<endl;	

	//Create perceptron test data
	vector<vector<int>> perceptrontestdata;
	 
        io::CSVReader<2> in_ptest("data/perceptrontestdatainp.csv");
        while(in_ptest.read_row(col_1, col_2)) {
                perceptrontestdata.push_back({col_1, col_2});
        }

        vector<int> pred_labels = libml::predict_classification(p,perceptrontestdata);


	//testing the perceptron.(Hardcoding the true labels for the corresponding test data to check the accuracy)
	//The user can change this to take true labels
    auto start2 = chrono::steady_clock::now();
	vector<int> trainy={1,-1,1,-1}; 
	float acc=libml::accuracy(trainy,pred_labels);
	auto ei2= chrono::steady_clock::now();
	cout<<"Testing time  "<<(ei2-start2).count()<<endl;
	cout<<"Accuracy of the classifier "<<acc<<endl<<endl;
	cout<<"---------------Naive Bayes--------------------"<<endl;

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
	auto start3 = chrono::steady_clock::now();
    libml::train_classification(nb,nb.d,nb.l);
	auto end3 = chrono::steady_clock::now();

	cout<<"Training time  "<<(end3-start3).count()<<endl;
	vector<vector<int>> nbtestdata;
	
	//test the Naive Bayes classifier
	io::CSVReader<3> in_nbtest("data/nbtestdatainp.csv");
        while(in_nbtest.read_row(col_1, col_2, col_3)) {
                nbtestdata.push_back({col_1, col_2, col_3});
        }

        auto start4 = chrono::steady_clock::now();
        vector<int> pred_classes = libml::predict_classification(nb,nbtestdata);
        auto end4 = chrono::steady_clock::now();
	vector<int>nbtrainy = {0,1,1,0};
	
	
	float accnb=libml::accuracy(nbtrainy,pred_classes);
	cout<<"Testing time  "<<(end4-start4).count()<<endl;
	cout<<"Accuracy of the classifier "<<accnb<<endl;
	
	cout<<"---------------KNN--------------------"<<endl<<endl;
	//Train and Test the knn model
        libml::KNN knn;
	knn.d=perceptrondata;
	knn.l=perceptronlabels;
	 
	knn.k=(int)3;

	auto start5 = chrono::steady_clock::now();
    libml::train_classification(knn,knn.d,knn.l);
    auto end5 = chrono::steady_clock::now();
    cout<<"Training time  "<<(end5-start5).count()<<endl;
	vector<vector<int>> knntestdata;
	vector<vector<string>> parseddataknn;
	//cout<<"in here";

	io::CSVReader<2> in_knntestinp("data/knntestdatainp.csv");
        while(in_knntestinp.read_row(col_1, col_2)) {
                knntestdata.push_back({col_1, col_2});
        } 
	
	//  //knntestdata={{8,-11},{14,-3}};
        auto start6 = chrono::steady_clock::now();
        pred_classes = libml::predict_classification(knn,knntestdata);
        auto end6 = chrono::steady_clock::now();
        cout<<"Testing time  "<<(end6-start6).count()<<endl;
	 //testing the KNN classifier
	
	vector<int> knntrainy={-1,1,1,1};
	float accknn=libml::accuracy(knntrainy,pred_classes);

	cout<<"Accuracy of the classifier "<<accknn<<endl;


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

	cout<<"-------------Linear Regression-----------------"<<endl<<endl;
    libml::LinearRegression lr;
	auto start7 = chrono::steady_clock::now();
    libml::train_regression(lr, train_data, train_labels);
    auto end7 = chrono::steady_clock::now();
    cout<<"Training time  "<<(end7-start7).count()<<endl;
	auto start8 = chrono::steady_clock::now();
	auto predicted_labels = libml::predict_regression(lr, test_data);
	auto end8 = chrono::steady_clock::now();
	cout<<"Testing time  "<<(end8-start8).count()<<endl;

	float acclr=libml::euclidean_distance(train_labels,predicted_labels);

	cout<<"Euclidean distance of the predicted label and true label "<<acclr<<endl;

	cout<<"-------------Ridge Regression-----------------"<<endl<<endl;
    libml::RidgeRegression rr;
	start7 = chrono::steady_clock::now();
    libml::train_regression(rr, train_data, train_labels);
	end7 = chrono::steady_clock::now();
    cout<<"Training time  "<<(end7-start7).count()<<endl;
	start8 = chrono::steady_clock::now();
	predicted_labels = libml::predict_regression(rr, test_data);
	end8 = chrono::steady_clock::now();
	cout<<"Testing time  "<<(end8-start8).count()<<endl;

	acclr=libml::euclidean_distance(train_labels,predicted_labels);

	cout<<"Euclidean distance of the predicted label and true label(Ridge)"<<acclr<<endl;
	
	cout<<"-------------Lasso Regression-----------------"<<endl<<endl;
    libml::LassoRegression lar;
	start7 = chrono::steady_clock::now();
    libml::train_regression(lar, train_data, train_labels);
	end7 = chrono::steady_clock::now();
    cout<<"Training time  "<<(end7-start7).count()<<endl;
	start8 = chrono::steady_clock::now();
	predicted_labels = libml::predict_regression(lar, test_data);
	end8 = chrono::steady_clock::now();
	cout<<"Testing time  "<<(end8-start8).count()<<endl;

	acclr=libml::euclidean_distance(train_labels,predicted_labels);

	cout<<"Euclidean distance of the predicted label and true label(Lasso)"<<acclr<<endl;

	cout<<"-------------Online Perceptron-----------------"<<endl<<endl;
	//Create an online perceptron model
    libml::OnlinePerceptron op;
	
	libml::OnlinePerceptron::Label_type l;
	ifstream file("data/perceptroninput.csv");

	string line;
	cout<<"OnlinePerceptron"<<endl;
	stringstream s;

	while(getline(file,line))
	{
                libml::OnlinePerceptron::Data_type s;
		s<<line;
		//Pass the csv stream
                libml::classify_online(op,s,l);
		s.str(string());


	 }

        
	
	
	cout<<"-------------K-means-----------------"<<endl<<endl;
	/* ###### K-Means ###### */
	double d1, d2, d3, d4;
	string s1;
	io::CSVReader<5> km_data("data/iris.data.txt");
	vector<vector<double>> asd;
	while(km_data.read_row(d1, d2, d3, d4, s1))
	{
		// cout << d1;
		asd.push_back({d1,d2,d3,d4});
	}

        libml::KMeans km;
	//x has the predicted values
    auto start9 = chrono::steady_clock::now();
	libml::train_unsupervised(km, asd);
	auto end9 = chrono::steady_clock::now();
	cout<<"Training time  "<<(end9-start9).count()<<endl;
	cout<<"--------------------------------"<<endl<<endl;
	// for (auto l : x)
	// {
	// 	cout << l << endl;
	// }




	
	return 1;
}
