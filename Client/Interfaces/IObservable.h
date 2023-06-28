#pragma once
#include <memory>
template<class ObserverType, class NotificationParamType>
class IObservable
{
public:
	virtual ~IObservable() = default;
	virtual void AddNewObserver(std::shared_ptr<ObserverType> newObserver) = 0;
	virtual void RemoveObserver(ObserverType* observer) = 0;
	virtual void Notify(const NotificationParamType& param) = 0;
};