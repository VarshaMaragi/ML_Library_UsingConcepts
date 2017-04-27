#ifndef LIBML_FUNCTIONS_HPP
#define LIBML_FUNCTIONS_HPP

#include "concepts.hpp"

namespace libml {

template<typename T>
void regression_train(T& lr, typename T::Data_type& train_data, typename T::Label_type& train_labels) requires Regression<T>
{
	lr.train(train_data, train_labels);
}

template<typename T>
typename T::Label_type regression_predict(T& lr, typename T::Data_type& test_data) requires Regression<T>
{
	return lr.regress(test_data);
}

template<typename T>
void classification_train(T& lr, typename T::Data_type& train_data, typename T::Label_type& train_labels) requires Classification<T>
{
	lr.train(train_data, train_labels);
}

template<typename T>
typename T::Label_type classification_predict(T& lr, typename T::Data_type& test_data) requires Classification<T>
{
	return lr.classify(test_data);
}

} // namespace libml

#endif // ifndef LIBML_FUNCTIONS_HPP
