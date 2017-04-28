#ifndef LIBML_RIDGE_REGRESSION_HPP
#define LIBML_RIDGE_REGRESSION_HPP

#include <vector>
#include <stdio.h>
#include <iostream>
#include <numeric>
#include <cmath>
#include <stdexcept>
#include "helpers.hpp"

namespace libml {
class RidgeRegression{
public:
	double alpha;
	double maxIter;
	double tol;
	std::string method;
	bool fit_intercept;
	bool verbose;
	std::vector<double> beta;
	double lambda;

    using Data_type = libml::matrix2<double>;
    using Label_type = std::vector<double>;

    using Data_primitive = double;
    using Label_primitive = double;

	// Operations for saving and restoring the state of the regression
	// after initial training.
	friend std::ostream& operator<<(std::ostream& os, const RidgeRegression& lr);
	friend std::istream& operator>>(std::istream& is, RidgeRegression& lr);

	// The Ridge Regression Objective value
<<<<<<< HEAD
	double obj(std::vector<double> beta, std::vector<std::vector<double>> train_data, std::vector<double> train_labels)
=======
	double obj(const std::vector<double>& beta, const Data_type& train_data, const Label_type& train_labels)
>>>>>>> 52606822844d34ea4feabd3b3ee338419f033e2d
	{
		std::vector<double> d(train_labels.size());
		for (int i = 0; i < train_labels.size(); i++)
		{
			d[i] = inner_product(train_data[i].begin(), train_data[i].end(), beta.begin(), 0.0) ;
			d[i] = d[i] - train_labels[i];
			d[i] = 0.5 * pow(d[i], 2) ;
			d[i] += 0.5 * lambda * norm2(beta);
		}
		return accumulate(d.begin(), d.end(), 0.0) / (train_data.size());
	}


	// Calculating the gradient
	std::vector<double> grad(const std::vector<double>& beta, const Data_type& train_data, const Label_type& train_labels)
	{
		std::vector<double> d(train_labels.size());
		std::vector<double> gradient(train_data[0].size(), 0);

		for (int i = 0; i < train_labels.size(); i++)
		{
			d[i] = inner_product(train_data[i].begin(), train_data[i].end(), beta.begin(), 0.0) ;
			d[i] = d[i] - train_labels[i];
		}

		std::vector<double> col(train_labels.size());
		// cout << "Size:" << train_data[0].size() << endl;

		for (int i = 0; i < train_data[0].size(); i++)
		{
			for(int j = 0; j < train_data.size(); j++)
			{
				col[j] = train_data[j][i];
			}

			gradient[i] = inner_product(d.begin(), d.end(), col.begin(), 0.0);
		}
		for (auto& g: gradient)
			g = g / train_labels.size();
		return gradient;
	}

	// Train the Ridge regression model
	void train(const Data_type& train_data, const Label_type& train_labels)
	{
		if (train_data.size() != train_labels.size())
		{
        	throw std::invalid_argument( "No. of rows in Train data and Train Labels must be equal");
		}
		beta.resize(train_data[0].size(), 0);
		std::vector<double> p_beta(train_data[0].size(), 0);
		int iter = 1;

		while (iter <= maxIter)
		{	
			std::vector<double> g = grad(beta, train_data, train_labels);
			
			for (int i = 0; i < train_data[0].size(); i++)
			{
				beta[i] = beta[i] - alpha * (g[i] + (lambda/train_labels.size()) * beta[i]);
			}

			if (verbose)
			{
				for (auto b: beta)
					std::cout << b << " ";
				std::cout << std::endl;
			}

			if (iter !=1 && std::abs(obj(beta, train_data, train_labels) - obj(p_beta, train_data, train_labels)) <= tol)
			{
				if (verbose)
				{
					std::cout << "Converged at iter: " << iter << std::endl;
				}
				break;
			}
			p_beta = beta;
			iter++;
		}
	}

	// Regress on the model for test data
<<<<<<< HEAD
	std::vector<double> regress(std::vector<std::vector<double>> test_data)
=======
	std::vector<double> regress(const Data_type& test_data)
>>>>>>> 52606822844d34ea4feabd3b3ee338419f033e2d
	{
		if (test_data[0].size() != this->beta.size())
		{
			// cout << "Test data dimensions must be same as the training data" << endl;
			throw std::invalid_argument( "No. of columns in Test data must be same as the Training data");
		}

		if (verbose)
		{
			std::cout << "Regressing on test data" << std::endl;
		}
		
		std::vector<double> predicted_values(test_data.size());
		for (int i = 0; i < test_data.size(); i++)
		{
			predicted_values[i] = inner_product(test_data[i].begin(), test_data[i].end(), this->beta.begin(), 0.0);
		}

		if (verbose)
		{	
			std::cout << "Predicted Values" << std::endl;
			for (auto p: predicted_values)
			std::cout << p << std::endl;
		}
		return predicted_values;
	}



	// Ridge Regression constructor for initialising the model parameters
	RidgeRegression(double lambda = 0.1, double alpha = 0.8, double maxIter = 1000, double tol = 0.00001, bool fit_intercept = 0, bool verbose = 0)   
        : lambda(lambda), alpha(alpha), maxIter(maxIter), tol(tol), fit_intercept(fit_intercept), verbose(verbose) // member init list  
	{
	}
};

// Writes the state of the regression model out to an ostream
std::ostream& operator<<(std::ostream& os, const RidgeRegression& lr) {
	// TODO: If alpha, maxIter and related properties are constants
	// these first couple of lines can be omitted.
	os << lr.alpha << ' ' << lr.maxIter << ' ' << lr.tol << ' ' << lr.fit_intercept << ' ' << lr.lambda;
	os << std::endl;

	for (const double& value : lr.beta) {
		os << value << ' ';
	}

	return os;
}

std::istream& operator>>(std::istream& is, RidgeRegression& lr) {
	// TODO: Again, if these are constants we can omit these
	is >> lr.alpha;
	is >> lr.maxIter;
	is >> lr.tol;
	is >> lr.fit_intercept;
	is >> lr.lambda;
	
	double d;
	while (!is.eof()) {
		is >> d;
		lr.beta.push_back(d);
	}

	return is;
}
} // namespace libml

#endif // ifndef LIBML_Ridge_REGRESSION_HPP
