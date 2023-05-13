#pragma once
#include "Settings/MainSettings.h"
#include "Manager/VideoSourcesManager.h"
#include "Processor/DifferenceProcessor.h"
#include "Processor/MoveDetectorProcessor.h"
class ClientApp
{
public:
	ClientApp();
	int main();
protected:
	MainSettings _mainSettings;
	std::unique_ptr<VideoSourcesManager> _pVideoSourceManager;
	std::shared_ptr<DifferenceProcessor> _diferenceProcessor;
	std::shared_ptr<MoveDetectorProcessor> _moveDetectorProcessor;
	std::optional<std::vector<cv::Mat>> _drawBuffer;
};

