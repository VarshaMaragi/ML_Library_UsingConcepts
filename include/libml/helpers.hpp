/**
 * @file helpers.hpp
 * @brief Statistical helper functions for calculations in models
 */

#ifndef LIBML_HELPER_HPP
#define LIBML_HELPER_HPP

#include <cmath>
#include <vector>

namespace libml {

template<typename T>
using matrix2 = std::vector<std::vector<T>>;

/**
 * @brief Calculates the means for each row in a set of training data
 * @return A vector of doubles corresponding to the means of each row in the data
 */
std::vector<double> calculate_mean(matrix2<double>& train_data)
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

/**
 * @brief Calculates the standard deviations for each row in a set of training data
 * @return A vector of doubles corresponding to the standard deviations of each row in the data
 */
std::vector<double> calculate_std(matrix2<double>& train_data)
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

/**
 * @brief Measures the rate of errors between a set of samples and another vector
 *
 * Accuracy is a measure of 1 - (number of errors the model makes / total number of samples)
 */
float accuracy(std::vector<auto> a, std::vector<auto> b)
{
	float sum=0;
        float accuracy;

	for(int i=0;i<a.size();i++)
	{
		if(a[i]!=b[i])
			sum=sum+1;
	}

	accuracy=1-float((sum/a.size()));
	return accuracy;
}

/**
 * @brief Calculates the euclidean distance between two vectors
 */
double euclidean_distance(std::vector<double> x, std::vector<double> y)
{
	double dist = 0;
	for(int i = 0; i < x.size(); i++)
	{
		dist += pow(x[i] - y[i], 2);
	}
	return sqrt(dist);
}

} // namespace libml

#endif // ifndef LIBML_HELPER_HPP
