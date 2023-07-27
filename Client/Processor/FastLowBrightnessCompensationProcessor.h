#pragma once
#include "Interfaces/IProcessor.h"
#include "ProcessorStructs.h"
class FastLowBrightnessCompensationProcessor :public IProcessor <LowBrightnessCompensationResult, std::shared_ptr<IFrame>>
{
public:
	void SetInput(std::shared_ptr<IFrame> input) override;
	virtual LowBrightnessCompensationResult Process() override;
	void Notify(std::shared_ptr<IFrame> param) override;
	bool CheckProcessingConditions()const;
protected:
	LowBrightnessCompensationResult _result;
	cv::Mat _buffer;
};