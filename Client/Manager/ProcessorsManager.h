#pragma once
#include "Processor/ProcessorHelper.h"
#include <vector>
class ProcessorsManager
{
public:
	ProcessorsManager(std::vector<Processors>&& processors);
protected:
	std::vector<Processors> _processors;
};