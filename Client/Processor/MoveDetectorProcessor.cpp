#include "MoveDetectorProcessor.h"
#include <opencv2/imgproc.hpp>
#include <algorithm>
#include "ProcessorBuilder.h"
MoveDetectorProcessor::MoveDetectorProcessor(MoveDetectorProcessorSettings settings) :
	_result{ .moveDetectionResult = Objects(_settings.initBufferSize, _settings.maxObjectsCount) },
	_settings{ std::move(settings) }
{
}

void MoveDetectorProcessor::SetInput(DifferenceResult input)
{
	_input = std::move(input);
}

MoveDetectionResult MoveDetectorProcessor::Process()
{
	auto& differenceMatBuffer{ _input.differenceResult };
	if (differenceMatBuffer.empty())
		return {};
	ClearInternalBuffers();
	cv::findContours(differenceMatBuffer, _contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
	for (auto&& objectPoints : _contours)
		_tempObjects.emplace_back(cv::boundingRect(std::move(objectPoints)));
	ManageTempObjects();
	for (auto&& object : _tempObjects)
		if (!_result.moveDetectionResult.PushNewObject(std::move(object)))
			break;
	_result.rawMat = _input.rawMat;
	return _result;
}

void MoveDetectorProcessor::Notify(DifferenceResult param)
{
	SetInput(std::move(param));
	NotifyAllObservers(Process());
}

void MoveDetectorProcessor::ClearInternalBuffers()
{
	_result.moveDetectionResult.ClearAllObjects();
	_contours.clear();
	_tempObjects.clear();
}

void MoveDetectorProcessor::ManageTempObjects()
{
	if (_settings.minObjectArea > 0)
	{
		auto rangeToRemove{ std::ranges::remove_if(_tempObjects, [this](const auto& rect)
			{
				return rect.area() < _settings.minObjectArea;
			}) };
		_tempObjects.erase(rangeToRemove.begin(), rangeToRemove.end());
	}
}