#include "MoveDetectorProcessor.h"
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <algorithm>
MoveDetectorProcessor::MoveDetectorProcessor(MoveDetectorProcessorSettings settings) :_settings{ std::move(settings) }
{
	_objects = { _settings.initBufferSize,_settings.maxObjectsCount };
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
	for (const auto& object : _tempObjects)
		if (!_objects.PushNewObject(object))
			break;
	_enableProcess = false;
}

Objects MoveDetectorProcessor::GetResult() const
{
	return _objects;
}

void MoveDetectorProcessor::ClearInternalBuffers()
{
	_objects.ClearAllObjects();
	_contours.clear();
	_tempObjects.clear();
}

void MoveDetectorProcessor::ManageTempObjects()
{
	if (_settings.mergeIntersectedObjects)
		cv::groupRectangles(_tempObjects,2);
	if (_settings.minObjectArea > 0)
	{
		auto rangeToRemove{ std::ranges::remove_if(_tempObjects, [&](const auto& rect)
			{
				return rect.area() < _settings.minObjectArea;
			}) };
		_tempObjects.erase(rangeToRemove.begin(), rangeToRemove.end());
	}
}