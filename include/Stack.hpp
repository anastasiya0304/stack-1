#pragma once
#ifndef STACK_HPP
#define STACK_HPP
#include <cstdlib>
#include <iostream>
#include <memory>
using namespace std;

template <typename T>
class stack
{
public:
	stack();
	size_t count() const;
	void push(T const &);
	void pop();
	const T& top();
	~stack();
	stack(const stack & tmp);
	stack & operator=(const stack &obj);
	bool operator==(stack const & rhs);
private:
	size_t array_size_;
	size_t count_;
	T * array_;
};
#include "Stack.cpp"
#endif
