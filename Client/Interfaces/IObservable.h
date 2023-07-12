#pragma once
#include "IObserver.h"
#include <memory>
template<class NotificationParamType>
class IObservable
{
public:
	virtual ~IObservable() = default;
	virtual void AddNewObserver(std::shared_ptr<IObserver<NotificationParamType>> newObserver) = 0;
	virtual void RemoveObserver(IObserver<NotificationParamType>* observerToRemove) = 0;
	virtual void NotifyAllObservers(const NotificationParamType& param) = 0;
};