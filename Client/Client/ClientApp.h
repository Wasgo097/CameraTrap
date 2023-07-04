#pragma once
#include "Settings/MainSettings.h"
#include "Manager/VideoSourcesManager.h"
#include "Manager/InputManager.h"
#include "Processor/ProcessorHelper.h"
#include "Utilities/ClientAppContext.h"

class ClientApp
{
public:
	ClientApp();
	int main();
protected:
	MainSettings _mainSettings;
	std::unique_ptr<VideoSourcesManager> _pVideoSourceManager;
	std::unique_ptr<InputManager> _pInputManager;
	std::unordered_map <std::string, Processors> _processorsPerId;
	std::shared_ptr<ClientAppContext> _pContext;
	std::vector<cv::Mat> _drawBuffer;
};