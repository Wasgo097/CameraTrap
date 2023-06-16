#pragma once
#include <memory>
#include "IFrame.h"
class IVideoSource
{
public:
	virtual ~IVideoSource() = default;
	virtual std::shared_ptr<IFrame> GetNextFrame() = 0;
	virtual std::string GetId()const = 0;
};