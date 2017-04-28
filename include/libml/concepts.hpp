/**
 * @file concepts.hpp
 * @brief Definitions for concepts used by LibML
 *
 * In order to enforce the compliance of computational models
 * and storage structures used, LibML uses concepts to check
 * constraints at compile-time, all of which are defined here.
 *
 * The use of concepts is intended to show more accurate error
 * messages should some entity fail a constraint, such as data
 * types for most models requiring two-dimensional array
 * semantics.
 */

#ifndef LIBML_CONCEPTS_HPP
#define LIBML_CONCEPTS_HPP

#include <cstddef>
#include <iostream>
#include <type_traits>

namespace libml {

/**
 * @brief Enforces that T is an arithmetic type (i.e. float or integer)
 */
template<typename T>
concept bool Numeric = std::is_arithmetic<T>::value;

/**
 * @brief Enforces that T is an integer type, signed or unsigned
 */
template<typename T>
concept bool Integral = std::is_integral<T>::value;

/**
 * @brief Enforces that T is an array storing items of type R with exactly D dimensions
 * @bug For D > 1, the dimension constraint is not accurately enforced
 */
template<typename T, typename R, std::size_t D>
concept bool NDimensional() {
	return (D == 0 && requires(T t) {
				{ t } -> R&;
			})
		|| (D == 1 && requires(T t, std::size_t n) {
				{ t[n] } -> R&;
				{ t.size() } -> Integral;
			})
		|| (requires(T t, std::size_t n) {
				{ t[n] };
			} /*&& NDimensional<T, R, D - 1>()*/); // This hangs the compiler!
}

/**
 * @brief Enforces that T can be written to an ostream using << and read from an istream using >>
 */
template<typename T>
concept bool Serializable = requires(T t, std::istream& i, std::ostream& o)
{
	{ i >> t };
	{ i << t };
};

/**
 * @brief Enforces that T is has two-dimensional array semantics and stores type R
 */
template<typename T, typename R>
concept bool Data() {
	return NDimensional<T, R, 2>();
}

/**
 * @brief Enforces that T is has one-dimensional array semantics storing type R
 */
template<typename T, typename R>
concept bool Labels() {
	return NDimensional<T, R, 1>();
}

/**
 * @brief Enforces that T is a regression model
 *
 * In order for a type to be a regression model it must have two methods, one
 * for training and one for calculating a regression, and must have exposed
 * associate types specifying the primitive data type being stored (i.e.
 * floats or ints) and the types used for designating arrays of #Data
 * and #Labels.
 */
template<typename T>
concept bool Regression = requires()
{
	typename T::Data_type;
	typename T::Label_type;

        typename T::Data_primitive;
        typename T::Label_primitive;

	requires Data<typename T::Data_type, typename T::Data_primitive>();
	requires Labels<typename T::Label_type, typename T::Label_primitive>();

} && requires(T t, typename T::Data_type d, typename T::Label_type l) {
	t.train(d,l);
	t.regress(d);
};

/**
 * @brief Enforces that T is a classification model
 *
 * In order for a type to be a classification model it must have two methods,
 * one for training and one for classifying items, and must have exposed
 * associate types specifying the primitive data type being stored (i.e.
 * floats or ints) and the types used for designating arrays of #Data
 * and #Labels.
 */
template<typename T>
concept bool Classification = requires()
{
	typename T::Data_type;
	typename T::Label_type;

	typename T::Data_primitive;
	typename T::Label_primitive;

	requires Data<typename T::Data_type, typename T::Data_primitive>();
	requires Labels<typename T::Label_type, typename T::Label_primitive>();

} && requires(T t, typename T::Data_type d, typename T::Label_type l) {
	t.train(d,l);
	t.classify(d);
};

/**
 * @brief Enforces that T is an unsupervised classification model
 *
 * Unlike #Classification, unsupervised classifications do not have labels,
 * and instead perform classifications on sets of #Data.
 */
template<typename T>
concept bool UnsupervisedClassification = requires()
{
	typename T::Data_type;
	typename T::Data_primitive;

	requires Data<typename T::Data_type, typename T::Data_primitive>();

} && requires(T t, typename T::Data_type d) {
	t.classify(d);
};

/**
 * @brief Enforces that T is an online learning classifier
 *
 * Unlike #Classification, online classifiers do not have primitive types
 * and are responsible themselves for parsing the input coming over the
 * wire. It also will not enforce array semantics on data and labels.
 *
 * Data_type and Label_type should be streams when working with online
 * classification.
 */
template<typename T>
concept bool OnlineLearningClassify = requires()
{
        typename T::Data_type;
        typename T::Label_type;
} && requires(T t,typename T::Data_type d,typename T::Label_type l) {
        t.classify(d,l);
};

} // namespace libml

#endif // ifndef LIBML_CONCEPTS_HPP
