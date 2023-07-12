#include "ProcessorsManager.h"

ProcessorsManager::ProcessorsManager(std::vector<Processors>&& processors) :_processors{ std::move(processors) }
{
}