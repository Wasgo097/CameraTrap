#pragma once
#include "Processor/ProcessorStructs.h"
#include <string>
class DetectionResultSerializer
{
public:
	std::string Serialize(const MoveDetectionResult& detectionResult);
protected:
	void SerializeImage(const cv::Mat& image);
	void SerializeObjects(const Objects& objects);
	std::string _serializationHeader;
	std::string _serializationImage;
	std::string _serializationObjects;
	std::string _serializationResult;
	const std::string _separator{"||||||"};
};