#pragma once
template<class T, class U>
class IProcessor {
public:
	~IProcessor() = default;
	virtual void SetInput(U input) = 0;
	virtual void Process() = 0;
	virtual T GetResult()const = 0;
};