#pragma once
template<class T>
class IProcessor {
public:
	~IProcessor() = default;
	virtual void Process() = 0;
	virtual T GetResult()const = 0;
};