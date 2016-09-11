#pragma once
#ifndef STACK_H

#define STACK_H

#include <iostream>


template <typename T>
class stack
{
public:
	stack();
	size_t count() const;
	void push(T const &);
	T pop();
	~stack();
	stack(const stack & obj)=delete;
private:
	T * array_;
	size_t array_size_;
	size_t count_;
};
template <typename T>
stack<T>::stack()
{
	count_ = 0;
	array_size_ = 1;
	array_ = new T[array_size_];
}
template <typename T>
size_t stack<T>::count() const
{
	return count_;
}
template <typename T>
void stack<T>::push(T const &elem)
{

	if (count_ == array_size_)
	{
		array_size_ *= 2;
		T * stk = new T[array_size_];
		memcpy(stk, array_, array_size_*sizeof(T));
		delete [] array_;

		array_ = stk;
		stk = nullptr;
	}
		array_[count_] = elem;
		count_++;
		
}
template <typename T>
T stack<T>::pop()
{
	if (count_ <= 0) 
	{
		throw std::logic_error("Stack is empty!");
	}
	return array_[--count_];

}
template <typename T>
stack<T>::~stack()
{
	delete [] array_;
}
#endif
