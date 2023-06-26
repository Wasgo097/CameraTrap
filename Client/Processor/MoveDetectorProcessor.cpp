#include "MoveDetectorProcessor.h"
#include <opencv2/imgproc.hpp>
#include <algorithm>
#include "IntersectionProcessor.h"
#include "ProcessorBuilder.h"
MoveDetectorProcessor::MoveDetectorProcessor(MoveDetectorProcessorSettings settings) :_settings{ std::move(settings) }
{
	_result = { _settings.initBufferSize,_settings.maxObjectsCount };
	if (_settings.mergeIntersectedObjects)
	{
		ProcessorBuilder builder;
		_intersectionProcessor = builder.BuildProcessor<IntersectionProcessor, std::vector<cv::Rect>>();
	}
}

void MoveDetectorProcessor::SetNewDifferenceMat(const cv::Mat& differenceMat)
{
	_differenceMatBuffer = differenceMat.clone();
	_enableProcess = true;
}

void MoveDetectorProcessor::Process()
{
	if (!_enableProcess or _differenceMatBuffer.empty())
		return;
	ClearInternalBuffers();
	cv::findContours(_differenceMatBuffer, _contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
	for (auto&& objectPoints : _contours)
		_tempObjects.emplace_back(cv::boundingRect(std::move(objectPoints)));
	ManageTempObjects();
	for (auto&& object : _tempObjects)
		if (!_result.PushNewObject(std::move(object)))
			break;
	_enableProcess = false;
}

Objects MoveDetectorProcessor::GetResult() const
{
	return _result;
}

void MoveDetectorProcessor::ClearInternalBuffers()
{
	_result.ClearAllObjects();
	_contours.clear();
	_tempObjects.clear();
}

void MoveDetectorProcessor::ManageTempObjects()
{
	if (_intersectionProcessor)
	{
		_intersectionProcessor->SetRectToProcess(std::move(_tempObjects));
		_intersectionProcessor->Process();
		_tempObjects = _intersectionProcessor->GetResult();
	}
	if (_settings.minObjectArea > 0)
	{
		auto rangeToRemove{ std::ranges::remove_if(_tempObjects, [this](const auto& rect)
			{
				return rect.area() < _settings.minObjectArea;
			}) };
		_tempObjects.erase(rangeToRemove.begin(), rangeToRemove.end());
	}
}