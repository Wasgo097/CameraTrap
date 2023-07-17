#pragma once
#include <mutex>
#include <condition_variable>
#include <deque>
template<typename T>
class ProducerConsumerBase
{
public:
	void Produce(T&& data)
	{
		std::unique_lock<std::mutex> lock(_mtx);
		_dataQueue.push_back(std::move(data));
		lock.unlock();
		_cv.notify_one();
	}

	T ConsumeNewest()
	{
		std::unique_lock<std::mutex> lock(_mtx);
		_cv.wait(lock, [this]
			{
				return !_dataQueue.empty();
			});
		T data = _dataQueue.back();
		_dataQueue.pop_back();
		return data;
	}

	T ConsumeOldest()
	{
		std::unique_lock<std::mutex> lock(_mtx);
		_cv.wait(lock, [this]
			{
				return !_dataQueue.empty();
			});
		T data = _dataQueue.front();
		_dataQueue.pop_front();
		return data;
	}
protected:
	std::deque<T> _dataQueue;
	std::mutex _mtx;
	std::condition_variable _cv;
};