#pragma once
#include <mutex>
#include <condition_variable>
#include <queue>
template<typename T>
class ProducerConsumerBase
{
public:
	void Produce(T&& data)
	{
		std::unique_lock<std::mutex> lock(_mtx);
		_dataQueue.push(std::move(data));
		lock.unlock();
		_cv.notify_one();
	}

	T Consume()
	{
		std::unique_lock<std::mutex> lock(_mtx);
		_cv.wait(lock, [this]
			{
				return !_dataQueue.empty();
			});
		T data = _dataQueue.front();
		_dataQueue.pop();
		return data;
	}
protected:
	std::queue<T> _dataQueue;
	std::mutex _mtx;
	std::condition_variable _cv;
};