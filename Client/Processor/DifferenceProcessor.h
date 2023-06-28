#pragma once
#include "Interfaces/IFrame.h"
#include "Interfaces/IProcessor.h"
#include "Settings/DifferenceProcessorSettings.h"
class DifferenceProcessor:public IProcessor<cv::Mat>
{
public:
	DifferenceProcessor(DifferenceProcessorSettings settings);
	void AddNewFrame(std::shared_ptr<IFrame> newFrame);
	void Process() override;
	cv::Mat GetResult()const override;
protected:
	std::shared_ptr<IFrame> _pCurrentImage;
	std::shared_ptr<IFrame> _pPreviousImage;
	cv::Mat _currentMat;
	cv::Mat _previousMat;
	cv::Mat _difference;
	cv::Mat _treshold;
	DifferenceProcessorSettings _settings;
};