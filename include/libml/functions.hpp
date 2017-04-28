#ifndef LIBML_FUNCTIONS_HPP
#define LIBML_FUNCTIONS_HPP

#include "concepts.hpp"

namespace libml {

template<typename T>
void train_regression(T& lr, typename T::Data_type& train_data, typename T::Label_type& train_labels) requires Regression<T>
{
	lr.train(train_data, train_labels);
}

template<typename T>
typename T::Label_type predict_regression(T& lr, typename T::Data_type& test_data) requires Regression<T>
{
	return lr.regress(test_data);
}

template<typename T>
void train_classification(T& lr, typename T::Data_type& train_data, typename T::Label_type& train_labels) requires Classification<T>
{
	lr.train(train_data, train_labels);
}

template<typename T>
typename T::Label_type predict_classification(T& lr, typename T::Data_type& test_data) //requires Classification<T>
{
	return lr.classify(test_data);
}

template<typename T>
void train_unsupervised(T& lr, typename T::Data_type& train_data) requires UnsupervisedClassification<T>
{
	lr.classify(train_data);
}




} // namespace libml

#endif // ifndef LIBML_FUNCTIONS_HPP
