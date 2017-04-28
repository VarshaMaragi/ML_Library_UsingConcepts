/**
 * @file functions.hpp
 * @brief Functions used for running regressions and classifications
 *
 * Functions here are used to provide the end user with a frontend
 * to work with models, data and labels while enforcing the
 * constraints of concepts.
 */

#ifndef LIBML_FUNCTIONS_HPP
#define LIBML_FUNCTIONS_HPP

#include "concepts.hpp"
#include <iostream>

namespace libml {

/**
 * @brief Trains a #Regression model
 */
template<typename T>
void train_regression(T& lr, typename T::Data_type& train_data, typename T::Label_type& train_labels) requires Regression<T>
{
	lr.train(train_data, train_labels);
}

/**
 * @brief Performs a regression using the given data
 * @return A vector of labels respective to the data
 */
template<typename T>
typename T::Label_type predict_regression(T& lr, typename T::Data_type& test_data) requires Regression<T>
{
	return lr.regress(test_data);
}

/**
 * @brief Trains a #Classification model
 */
template<typename T>
void train_classification(T& lr, typename T::Data_type& train_data, typename T::Label_type& train_labels) requires Classification<T>
{
	lr.train(train_data, train_labels);
}

/**
 * @brief Classifies the given data using the given model
 * @return A vector of labels respective to the data
 */
template<typename T>
typename T::Label_type predict_classification(T& lr, typename T::Data_type& test_data) //requires Classification<T>
{
	return lr.classify(test_data);
}

/**
 * @brief Trains an #UnsupervisedClassification model
 */
template<typename T>
void train_unsupervised(T& lr, typename T::Data_type& train_data) requires UnsupervisedClassification<T>
{
	lr.classify(train_data);
}

/**
 * @brief Trains an #OnlineLearningClassify model
 */
template<typename T>
void classify_online(T& lr, typename T::Data_type& test_data, typename T::Label_type& test_labels) requires OnlineLearningClassify<T>
{
        std::cout << "Testing classify" << std::endl;
        return lr.classify(test_data, test_labels);
}

} // namespace libml

#endif // ifndef LIBML_FUNCTIONS_HPP
