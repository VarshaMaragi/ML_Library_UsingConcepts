#include "concepts.hpp"
#include <vector>

void classifier_train(Regression<std::vector<std::vector<double>>, std::vector<double>>& lr, std::vector<std::vector<double>>& train_data, std::vector<double>& train_labels)
{
	lr.train(train_data, train_labels);
}

std::vector<double> classifier_predict(Regression<std::vector<std::vector<double>>, std::vector<double>>& lr, std::vector<std::vector<double>>& test_data)
{
	return lr.regress(test_data);
}