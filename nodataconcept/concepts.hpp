#ifndef CONCEPTS_HPP
#define CONCEPTS_HPP

#include <iostream>

namespace libml {
template<typename T>
concept bool Serializable = requires(T t, std::istream& i, std::ostream& o)
{
	{ i >> t };
	{ i << t };
};

template<typename T, typename D, typename L>
concept bool Regression = Serializable<T> && requires(T t, D d, L l)
{
	t.train(d,l);
	t.regress(d);
};
} // namespace libml

#endif
