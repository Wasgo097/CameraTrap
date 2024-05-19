#pragma once
#include "Interfaces/IDetectionResultSerializer.h"
class SimpleDetectionResultSerializer :public IDetectionResultSerializer
{
public:
	std::string Serialize(const MoveDetectionResult& detectionResult) override;
	SerializationType GetSerializationType() const override;
protected:
	void SerializeImage(const cv::Mat& image);
	void SerializeObjects(const Objects& objects);
	std::string _serializationHeader;
	std::string _serializationImage;
	std::string _serializationObjects;
	std::string _serializationResult;
	const std::string _separator{"||||||"};
	const std::string _packetEnd{";;;;;;"};
};