#include "Stopwatch.h"

void Stopwatch::Start() 
{
	_startTime = std::chrono::high_resolution_clock::now();
	_running = true;
}

void Stopwatch::Stop() 
{
	_endTime = std::chrono::high_resolution_clock::now();
	_running = false;
}

void Stopwatch::Reset()
{
	_startTime = std::chrono::high_resolution_clock::now();
}

double Stopwatch::ElapsedMilliseconds() 
{
	std::chrono::time_point<std::chrono::high_resolution_clock> endTimePoint;
	if (_running) 
		endTimePoint = std::chrono::high_resolution_clock::now();
	else 
		endTimePoint = _endTime;
	return std::chrono::duration<double, std::milli>(endTimePoint - _startTime).count();
}

double Stopwatch::ElapsedSeconds() 
{
	return ElapsedMilliseconds() / 1000.0;
}
