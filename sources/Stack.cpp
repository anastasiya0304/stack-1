#include "Stack.hpp"
#include <stdexcept>
#ifndef STACK_CPP
#define STACK_CPP
template <typename T1, typename T2>
void construct(T1 * ptr, T2 const & value)
{
	new(ptr) T1(value);
}

template <typename T>
void destroy(T * array) noexcept
{
	array->~T();
}

template <typename FwdIter>
void destroy(FwdIter first, FwdIter last) noexcept
{
	for (; first != last; ++first) 
	{
		destroy(&*first);
	}
}



template <typename T>
T* copy_with_new(const T * arr, size_t count, size_t array_size)
{
	T * stk = new T[array_size];
	try
	{
		std::copy(arr, arr + count, stk);
	}
	catch (...)
	{
		delete[] stk;
		throw;
	}
	return stk;
};
template <typename T>// конструктор аллокатора
allocator<T>::allocator(size_t size) : array_(static_cast<T *>(size == 0 ? nullptr : operator new(size * sizeof(T)))), array_size_(0), count_(size) {
};
template <typename T>//деструктор аллокатора
allocator<T>::~allocator() 
{
	operator delete(array_);
};
template <typename T>//swap allocator
void allocator<T>::swap(allocator& stk)
{
	std::swap(array_, stk.array_);
	std::swap(array_size_, stk.array_size_);
	std::swap(count_, stk.count_);
};

template <typename T>
stack<T>::stack()  
{
	destroy(array_);
}
template <typename T>
size_t stack<T>::count() const noexcept
{
	return count_;
}
template <typename T>
void stack<T>::push(T const &elem)
{

	if (allocator<T>::count_ == allocator<T>::array_size_)
	{
		size_t array_size = allocator<T>::array_size_*2+(allocator<T>::array_size_==0);
		T * stk = copy_with_new(array_, count_, array_size);
		delete[] array_;
		allocator<T>::array_ = stk;
		allocator<T>::array_size_ = array_size;
	}
	construct(array_ + count_, elem);
	++count_;

}
template <typename T>
void stack<T>::pop()
{
	if (count_ == 0)
	{
		throw std::logic_error("Stack is empty!");
	}
	destroy(array_ + count_);
	--count_;
}
template <typename T>
const T& stack<T>::top()
{
	if (count_ == 0)
	{
		throw std::logic_error("Stack is empty!");
	}
	return array_[count_ - 1];
}
template <typename T>
stack<T>::~stack()
{}

template <typename T>
stack<T>::stack(const stack&tmp) 
{
	count_ = tmp.count_;
	array_size_ = tmp.array_size_;
	array_=copy_with_new(tmp.array_, tmp.count_, tmp.array_size_) 
}
template <typename T>
stack<T>& stack<T>::operator=(const stack &obj)
{

	if (this != &obj)
	{
		T* stk = copy_with_new(obj.array_, count_, array_size_);
		delete[] array_;
		array_size_ = obj.array_size_;
		count_ = obj.count_;
		array_ = stk;
	}

	return *this;
}

template<typename T>
bool stack<T>::operator==(stack const & rhs)
{
	if ((rhs.count_ != count_) || (rhs.array_size_ != array_size_)) {
		return false;
	}
	else {
		for (size_t i = 0; i < count_; i++) {
			if (rhs.array_[i] != array_[i]) {
				return false;
			}
		}
	}
	return true;
}

#endif