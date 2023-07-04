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
	if (_running)
		return std::chrono::duration<double, std::milli>(std::chrono::high_resolution_clock::now() - _startTime).count();
	return std::chrono::duration<double, std::milli>(_endTime - _startTime).count();
}

double Stopwatch::ElapsedSeconds()
{
	return ElapsedMilliseconds() / 1000.0;
}
