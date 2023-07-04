#include "Objects.h"
#include <algorithm>
Objects::Objects(size_t initObjectsBufferSize, size_t maxObjectsBufferSize) :_MAXOBJECTS{ maxObjectsBufferSize }
{
	_objects.reserve(std::min(_MAXOBJECTS, initObjectsBufferSize));
}

bool Objects::PushNewObject(cv::Rect newObject)
{
	if (_MAXOBJECTS > 0 and _objects.size() == _MAXOBJECTS)
		return false;
	_objects.emplace_back(std::move(newObject));
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
