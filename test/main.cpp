#include <string>
#include <fstream>
#include <cmath>
#include <cmath>

#include <libml/concepts.hpp>
#include <libml/linear_regression.hpp>
#include <libml/csv.hpp>
#include <libml/helpers.hpp>
#include <libml/functions.hpp>

using namespace std;

int main()
{

// Read Data
io::CSVReader<3> in("data/input2.csv");
in.set_header("age", "weight", "height");

vector<vector<double>> train_data;
vector<vector<double>> test_data;
vector<double> train_labels;
double age, weight, height;

while(in.read_row(age, weight, height))
{
	train_data.push_back({1, age, weight});
	test_data.push_back({1, age, weight});
	train_labels.push_back(height);
}

vector<double> mean = libml::calculate_mean(train_data);
vector<double> std = libml::calculate_std(train_data);
// cout << "Mean:" << mean[0] << " " << mean[1] << " " << mean[2] << endl;
// cout << "STD:" << std[0] << " " << std[1] << " " << std[2] << endl;
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
libml::regression_train(lr, train_data, train_labels);

cout << "Calling Linear Regression Predict" << endl;
auto predicted_labels = regression_predict(lr, test_data);

// for (auto p: predicted_labels)
// 	cout << p << endl;

cout << "Saving regression data" << endl;
std::ofstream state_out("lr_state.txt", std::ofstream::out);
state_out << lr;
state_out.close();
// lr.regress(test_data)
}
