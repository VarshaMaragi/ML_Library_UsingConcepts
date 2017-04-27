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
			} && NDimensional<T, R, D - 1>);
}

template<typename T>
concept bool Serializable = requires(T t, std::istream& i, std::ostream& o)
{
	{ i >> t };
	{ i << t };
};

template<typename T, typename D, typename L>
concept bool Regression = requires(T t, D d, L l)
{
	t.train(d,l);
	t.regress(d);
};

template<typename T>
concept bool Classification = requires()
{
	typename T::Data_type;
	typename T::Label_type;

	requires NDimensional<typename T::Data_type, 1>;
	requires NDimensional<typename T::Label_type, 2>;

} && requires(T t, typename T::Data_type d, typename T::Label_type l) {
	train(t,d,l);
	classify(t,d);
};

template<typename L>
void check(Classification& x, NDimensional<L, 1>& md, NDimensional<Numeric, 2>& ml)
{
	std::cout<<"Check the classifier\n";
	train(x,md,ml);
}

void test(Classification& x, NDimensional<Numeric, 2>& td)
{
	std::cout<<"Test the classifier\n";
	classify(x,td);
}

} // namespace libml

#endif // ifndef LIBML_CONCEPTS_HPP
