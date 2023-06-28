#pragma once
#include <chrono>
class Stopwatch
{
public:
	void Start();
	void Stop();
	void Reset();
	double ElapsedMilliseconds();
	double ElapsedSeconds();
private:
	std::chrono::time_point<std::chrono::high_resolution_clock> _startTime, _endTime;
	bool _running{ false };
};

