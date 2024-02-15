#include "SimpleMoveDetectorProcessor.h"
#include <opencv2/imgproc.hpp>
#include <algorithm>
SimpleMoveDetectorProcessor::SimpleMoveDetectorProcessor(SimpleMoveDetectorProcessorSettings settings) :
	_result{ .moveDetectionResult = Objects(_settings.initBufferSize, _settings.maxObjectsCount) },
	_settings{ std::move(settings) }
{
}

void SimpleMoveDetectorProcessor::SetInput(DifferenceResult input)
{
	_result.pRawFrame = std::move(input.pRawFrame);
	_result.lowBrightnessCompensationResultOpt = std::move(input.lowBrightnessCompensationResultOpt);
	_differenceInput = input.differenceResult;
}

MoveDetectionResult SimpleMoveDetectorProcessor::Process()
{
	if (_differenceInput.empty())
		return _result;
	ClearInternalBuffers();
	cv::findContours(_differenceInput, _contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
	for (const auto& objectPoints : _contours)
	{
		auto rect{ cv::boundingRect(objectPoints) };
		if (_settings.minObjectArea > 0 and rect.area() >= _settings.minObjectArea)
			_tempObjects.emplace_back(rect);
	}
	ManageTempObjects();
	for (auto&& object : _tempObjects)
		if (!_result.moveDetectionResult.PushNewObject(std::move(object)))
			break;
	return _result;
}

void SimpleMoveDetectorProcessor::Notify(DifferenceResult param)
{
	SetInput(std::move(param));
	NotifyAllObservers(Process());
}

void SimpleMoveDetectorProcessor::ClearInternalBuffers()
{
	_result.moveDetectionResult.ClearAllObjects();
	_contours.clear();
	_tempObjects.clear();
}

void SimpleMoveDetectorProcessor::ManageTempObjects()
{
	//if (_settings.minObjectArea > 0)
	//{
	//	auto rangeToRemove{ std::ranges::remove_if(_tempObjects, [this](const auto& rect)
	//		{
	//			return rect.area() < _settings.minObjectArea;
	//		}) };
	//	_tempObjects.erase(rangeToRemove.begin(), rangeToRemove.end());
	//}
}