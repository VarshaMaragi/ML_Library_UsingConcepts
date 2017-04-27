#include <cmath>

namespace libml {
std::vector<double> calculate_mean(std::vector<std::vector<double>>& train_data)
{
	int nSamples = train_data.size();
	int nDimensions = train_data[0].size();
	std::vector<double> mean(train_data[0].size(),0);
	
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

std::vector<double> calculate_std(std::vector<std::vector<double>>& train_data)
{
	int nSamples = train_data.size();
	int nDimensions = train_data[0].size();
	std::vector<double> mean = calculate_mean(train_data);
	std::vector<double> std(train_data[0].size(),0);

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
} // namespace libml
