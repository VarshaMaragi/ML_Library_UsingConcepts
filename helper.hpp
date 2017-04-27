#include <cmath>

vector<double> calculate_mean(vector<vector<double>>& train_data)
{
	int nSamples = train_data.size();
	int nDimensions = train_data[0].size();
	vector<double> mean(train_data[0].size(),0);
	
	for (int j = 0; j < nDimensions; j++)
	{
		for (int i = 0; i < nSamples; i++)
		{
			mean[j] += train_data[i][j];
		}
		mean[j] /= nSamples;
	}
	return mean;
}

vector<double> calculate_std(vector<vector<double>>& train_data)
{
	int nSamples = train_data.size();
	int nDimensions = train_data[0].size();
	vector<double> mean = calculate_mean(train_data);
	vector<double> std(train_data[0].size(),0);

	for (int j = 1; j < nDimensions; j++)
	{
		for (int i = 0; i < nSamples; i++)
		{
			std[j] += pow(train_data[i][j] - mean[j], 2);
		}
		std[j] /= nSamples;
		std[j] = sqrt(std[j]);
	}
	return std;
}