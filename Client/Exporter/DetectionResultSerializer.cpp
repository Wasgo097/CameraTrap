#include "DetectionResultSerializer.h"
#include <format>
std::string DetectionResultSerializer::Serialize(const MoveDetectionResult& detectionResult)
{
	const auto& imageToSerialization{ detectionResult.lowBrightnessCompensationResultOpt ?
		detectionResult.pRawFrame->GetMatCRef() : *detectionResult.lowBrightnessCompensationResultOpt };
	auto rows{ imageToSerialization.rows },
		cols{ imageToSerialization.cols },
		type{ imageToSerialization.type() };
	_serializationHeader = std::format("{};{};{}", rows, cols, type);
	SerializeImage(imageToSerialization);
	SerializeObjects(detectionResult.moveDetectionResult);
	_serializationResult.clear();
	_serializationResult = std::move(_serializationHeader) + _separator +
		std::move(_serializationImage) + _separator +
		std::move(_serializationObjects);
	return _serializationResult;
}

void DetectionResultSerializer::SerializeImage(const cv::Mat& image)
{
	_serializationImage.clear();
	if (image.isContinuous())
		_serializationImage.assign(image.data, image.data + image.total() * image.elemSize());
	else
		for (int i = 0; i < image.rows; ++i)
			_serializationImage.insert(_serializationImage.end(), image.ptr<uchar>(i), image.ptr<uchar>(i) + image.cols * image.channels());
	return;
}

void DetectionResultSerializer::SerializeObjects(const Objects& objects)
{
	_serializationObjects.clear();
}