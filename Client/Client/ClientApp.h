#pragma once
#include "Settings/MainSettings.h"
#include "Manager/VideoSourcesManager.h"
#include "Manager/InputManager.h"

#include "Processor/DifferenceProcessor.h"
#include "Processor/MoveDetectorProcessor.h"

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

	std::shared_ptr<DifferenceProcessor> _pDiferenceProcessor;
	std::shared_ptr<MoveDetectorProcessor> _pMoveDetectorProcessor;
	std::shared_ptr<ClientAppContext> _pContext;
	std::vector<cv::Mat> _drawBuffer;
};