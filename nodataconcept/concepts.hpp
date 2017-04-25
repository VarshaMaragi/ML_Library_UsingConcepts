#ifndef CONCEPTS_HPP
#define CONCEPTS_HPP

#include <iostream>

template<typename T>
concept bool Serializable = requires(T t, std::istream& i, std::ostream& o)
{
	{ i >> t } -> std::istream&;
	{ i << t } -> std::ostream&;
};

template<typename T, typename D, typename L>
concept bool Regression = Serializable<T> && requires(T t, D d, L l)
{
	t.train(d,l);
	t.regress(d);
};

#endif
