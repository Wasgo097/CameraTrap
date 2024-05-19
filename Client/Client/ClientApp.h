#pragma once
#include "Settings/MainSettings.h"
#include "Manager/InputManager.h"
#include "Manager/CalculationManager.h"
#include "Manager/CalculationResultManager.h"
class ClientApp
{
public:
	ClientApp();
	~ClientApp();
	int main();
protected:
	void InitMainSettings();
	void InitManagers();
	void InitAppContext();
	MainSettings _mainSettings;
	std::unique_ptr<InputManager> _pInputManager;
	std::unique_ptr<CalculationManager> _pCalculationManager;
	std::unique_ptr<CalculationResultManager> _pCalculationResultManager;
	std::shared_ptr<ClientAppContext> _pContext;
	ThreadsResourcePtr<cv::Mat> _matToGui;
	std::vector<std::shared_ptr<ProcessingResultProducerConsumer>> _processingResultsBuffer;
	const cv::Mat _emptyMatToGui{1, 1, CV_8UC3, cv::Scalar(255, 255, 255)};
	const static std::string _windowName;
};