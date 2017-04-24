#include <vector>
#include <stdio.h>
#include <iostream>
#include <numeric>

using namespace std;

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

class LinearRegression{
public:
	double alpha = 0.8;
	double maxIter = 80;
	double tol;
	string method;
	bool fit_intercept = 1;
	vector<double> beta;

	double obj(vector<double> beta,vector<vector<double>> x,vector<double> y)
	{
		return 0;
	}

	vector<double> grad(vector<double>& beta, vector<vector<double>>& train_data, vector<double>& train_labels)
	{
		vector<double> d(train_labels.size());
		vector<double> gradient(train_data[0].size(), 0);

		for (int i = 0; i < train_labels.size(); i++)
		{
			d[i] = inner_product(train_data[i].begin(), train_data[i].end(), beta.begin(), 0.0) ;
			d[i] = d[i] - train_labels[i];
		}

		vector<double> col(train_labels.size());
		// cout << "Size:" << train_data[0].size() << endl;

		for (int i = 0; i < train_data[0].size(); i++)
		{
			for(int j = 0; j < train_data.size(); j++)
			{
				col[j] = train_data[j][i];
			}

			gradient[i] = inner_product(d.begin(), d.end(), col.begin(), 0.0);
			// cout << "i:" << i  << endl;

			// for (auto x : col)
			// 	cout << x << endl;
		}
		for (auto& g: gradient)
			g = g / train_labels.size();
		return gradient;
	}
	
	void train(vector<vector<double>>& train_data, vector<double>& train_labels)
	{
		vector<double> beta(train_data[0].size(), 0);
		this->beta = beta;

		vector<double> p_beta(train_data[0].size(), 0);
		int iter = 1;

		// if (fit_intercept)
		// 	train_data
		while(iter <= maxIter)
		{	
			vector<double> g = grad(beta, train_data, train_labels);
			// for (auto x : g)
			// cout << "beta" << x << endl;
			
			for (int i = 0; i < train_data[0].size(); i++)
			{
				beta[i] = beta[i] - alpha * g[i];
			}
			iter++;

			for (auto b: beta)
				cout << b << " ";
			cout << endl;
		}
	}

	// void set_beta)()
	
	void regress(vector<vector<double>> test_data)
	{
		// vector<double> beta = this->beta;
		// cout << this->beta << endl;
	}
};