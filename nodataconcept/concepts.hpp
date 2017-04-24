#ifndef CONCEPTS_HPP
#define CONCEPTS_HPP

template<typename T, typename D, typename L>
concept bool Regression = requires(T t, D d, L l)
{
	t.train(d,l);
	t.regress(d);
};

#endif