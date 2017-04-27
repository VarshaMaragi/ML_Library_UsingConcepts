#include <vector>
#include <stdio.h>
#include <iostream>
#include <numeric>
#include <cmath>
#include <stdexcept>

// beta = np.zeros(x.shape[1])
// p_beta = np.empty_like(beta)
// if alpha == 0.8:
// 	max_iter = 80

// for i in range(max_iter):
// 	beta = beta - alpha * grad(beta, x_scaled, y)
// 	# print("beta: ", beta)
// 	# print("pbeta: ", p_beta)
// 	# print("pbeta - beta: ", p_beta - beta)

// 	if i!=0 and not printed and abs(obj(beta, x, y) - obj(p_beta, x, y)) <= 0.0000001:
// 		print("Converged, Iter: {0} alpha: {1}\n".format(i, alpha))
// 		# print("p:{0} b:{1}".format(obj(beta, x, y), obj(p_beta, x, y)))
// 		# print("Diff: ", obj(beta, x, y) - obj(p_beta, x, y))
// 		printed = True
// 	p_beta = beta

// out.write("{0},{1},{2},{3},{4}\n".format(alpha, max_iter, beta[0], beta[1], beta[2]))

// def grad(beta, x, y):
// 	# print("Val", np.sum((x.T * (np.sum(x * beta, axis=1) - y)).T, axis=0))
// 	d = (np.dot(x, beta) -  y).T
// 	return np.dot(d, x).T / x.shape[0]

namespace libml {
class LinearRegression{
public:
	double alpha;
	double maxIter;
	double tol;
	std::string method;
	bool fit_intercept;
	bool verbose;
	std::vector<double> beta;

// def obj(beta, x, y):
// 	return (np.power((np.dot(x, beta) - y), 2).sum() / (2*x.shape[0]))

	// Operations for saving and restoring the state of the regression
	// after initial training.
	friend std::ostream& operator<<(std::ostream& os, const LinearRegression& lr);
	friend std::istream& operator>>(std::istream& is, LinearRegression& lr);

	// The Linear Regression Objective value
	double obj(std::vector<double> beta, std::vector<std::vector<double>> train_data, std::vector<double> train_labels)
	{
		vector<double> d(train_labels.size());
		for (int i = 0; i < train_labels.size(); i++)
		{
			d[i] = inner_product(train_data[i].begin(), train_data[i].end(), beta.begin(), 0.0) ;
			d[i] = d[i] - train_labels[i];
			d[i] = pow(d[i], 2);
		}
		return accumulate(d.begin(), d.end(), 0.0) / (2 * train_data.size());
	}


	// Calculating the gradient
	std::vector<double> grad(std::vector<double>& beta, std::vector<std::vector<double>>& train_data, std::vector<double>& train_labels)
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

	void train(std::vector<std::vector<double>>& train_data, std::vector<double>& train_labels)
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
				beta[i] = beta[i] - alpha * g[i];
			}

			if (verbose)
			{
				for (auto b: beta)
					cout << b << " ";
				cout << endl;
			}

			if (iter !=1 && abs(obj(beta, train_data, train_labels) - obj(p_beta, train_data, train_labels)) <= tol)
			{
				if (verbose)
				{
					cout << "Converged at iter: " << iter << endl;
				}
				break;
			}
			p_beta = beta;
			iter++;
		}
	}

	std::vector<double> regress(std::vector<std::vector<double>> test_data)
	{
		if (test_data[0].size() != this->beta.size())
		{
			// cout << "Test data dimensions must be same as the training data" << endl;
			throw std::invalid_argument( "No. of columns in Test data must be same as the Training data");
		}

		if (verbose)
		{
			cout << "Regressing on test data" << endl;
		}
		
		std::vector<double> predicted_values(test_data.size());
		for (int i = 0; i < test_data.size(); i++)
		{
			predicted_values[i] = inner_product(test_data[i].begin(), test_data[i].end(), this->beta.begin(), 0.0);
		}

		if (verbose)
		{	
			cout << "Predicted Values" << endl;
			for (auto p: predicted_values)
			cout << p << endl;
		}
		return predicted_values;
	}

	LinearRegression(double alpha = 0.8, double maxIter = 1000, double tol = 0.00001, bool fit_intercept = 0, bool verbose = 0)   
        : alpha(alpha), maxIter(maxIter), tol(tol), fit_intercept(fit_intercept), verbose(verbose) // member init list  
	{
	}
};

// Writes the state of the regression model out to an ostream
std::ostream& operator<<(std::ostream& os, const LinearRegression& lr) {
	// TODO: If alpha, maxIter and related properties are constants
	// these first couple of lines can be omitted.
	os << lr.alpha << ' ' << lr.maxIter << ' ' << lr.tol << ' ' << lr.fit_intercept;
	os << std::endl;

	for (const double& value : lr.beta) {
		os << value << ' ';
	}

	return os;
}

std::istream& operator>>(std::istream& is, LinearRegression& lr) {
	// TODO: Again, if these are constants we can omit these
	is >> lr.alpha;
	is >> lr.maxIter;
	is >> lr.tol;
	is >> lr.fit_intercept;
	
	double d;
	while (!is.eof()) {
		is >> d;
		lr.beta.push_back(d);
	}

	return is;
}
} // namespace libml
