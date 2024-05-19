#pragma once
#include "IObserver.h"
#include <memory>
template<class NotificationParamType>
class IObservable
{
public:
	virtual ~IObservable() = default;
	virtual void AddNewObserver(std::shared_ptr<IObserver<NotificationParamType>> pNewObserver) = 0;
	virtual void RemoveObserver(IObserver<NotificationParamType>* pObserverToRemove) = 0;
	virtual void NotifyAllObservers(const NotificationParamType& param) = 0;
};