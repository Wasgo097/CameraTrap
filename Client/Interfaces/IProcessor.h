#pragma once
#include "Utilities/SingleObservableBasic.h"
template<class ProcessorResult, class ProcessorInput>
class IProcessor :public SingleObservableBasic<ProcessorResult>, public IObserver<ProcessorInput> {
public:
	virtual ~IProcessor() = default;
	virtual void SetInput(ProcessorInput input) = 0;
	virtual ProcessorResult Process() = 0;
};