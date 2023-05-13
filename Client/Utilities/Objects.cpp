#include "Objects.h"
#include <algorithm>
Objects::Objects(size_t initObjectsBufferSize, size_t maxObjectsBufferSize) :_maxObjects{ maxObjectsBufferSize }
{
	_objects.reserve(std::min(_maxObjects, initObjectsBufferSize));
}

bool Objects::PushNewObject(cv::Rect newObject)
{
	if (_maxObjects > 0 and _objects.size() == _maxObjects)
		return false;
	_objects.emplace_back(newObject);
	return true;
}

void Objects::ClearAllObjects()
{
	_objects.clear();
}

const std::vector<cv::Rect>& Objects::GetObjects() const
{
	return _objects;
}
