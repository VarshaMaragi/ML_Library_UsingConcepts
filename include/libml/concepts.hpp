#ifndef LIBML_CONCEPTS_HPP
#define LIBML_CONCEPTS_HPP

#include <cstddef>
#include <iostream>
#include <type_traits>

namespace libml {

template<typename T>
concept bool Numeric = std::is_arithmetic<T>::value;

template<typename T>
concept bool Integral = std::is_integral<T>::value;

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

template<typename T>
concept bool Serializable = requires(T t, std::istream& i, std::ostream& o)
{
	{ i >> t };
	{ i << t };
};

template<typename T, typename R>
concept bool Data() {
	return NDimensional<T, R, 2>();
}

template<typename T, typename R>
concept bool Labels() {
	return NDimensional<T, R, 1>();
}

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

template<typename T>
concept bool UnsupervisedClassification = requires()
{
	typename T::Data_type;
	typename T::Data_primitive;

	requires Data<typename T::Data_type, typename T::Data_primitive>();

} && requires(T t, typename T::Data_type d) {
	t.classify(d);
};

template<typename T>
concept bool OnlineLearningClassify = requires()
{
        typename T::Data_type;
        typename T::Label_type;
} && requires(T t,typename T::Data_type d,typename T::Label_type l) {
        t.classify(d,l);
};

template<typename T>
void check(T& x, typename T::Data_type& md, typename T::Label_type& ml) requires Classification<T>
{
	std::cout<<"Check the classifier\n";
	train(x,md,ml);
}

template<typename T>
void test(T& x, typename T::Data_type& td)
{
	std::cout<<"Test the classifier\n";
	classify(x,td);
}

} // namespace libml

#endif // ifndef LIBML_CONCEPTS_HPP
