#pragma once
#include "IFrame.h"
#include "Utilities/SingleObservableBasic.h"
class IVideoSource :public SingleObservableBasic<std::shared_ptr<IFrame>>
{
public:
	virtual ~IVideoSource() = default;
	virtual std::shared_ptr<IFrame> GetNextFrame() = 0;
	virtual std::string GetId()const = 0;
};