#pragma once
#include <memory>
#include <shared_mutex>
template<typename T>
struct ThreadsResourcePtr
{
	ThreadsResourcePtr(std::shared_ptr<T> val) :_pVal{ std::move(val) }
	{}
	std::shared_ptr<T> _pVal;
	std::shared_ptr<std::shared_mutex> _pMtx{std::make_shared<std::shared_mutex>()};
};
template<typename T>
struct ThreadsResourceVal
{
	ThreadsResourceVal(T val) :_val{ std::move(val) }
	{}
	T _val;
	std::shared_ptr<std::shared_mutex> _pMtx{std::make_shared<std::shared_mutex>()};
};