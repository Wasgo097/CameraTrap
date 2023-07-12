#pragma once
#include "Interfaces/IObservable.h"
template<class NotificationParamType>
class SingleObservableBasic : public IObservable<NotificationParamType>
{
public:
	virtual ~SingleObservableBasic() = default;
	void AddNewObserver(std::shared_ptr<IObserver<NotificationParamType>> newObserver) override
	{
		_observer = std::move(newObserver);
	}
	void RemoveObserver(IObserver<NotificationParamType>* observerToRemove) override
	{
		if (auto observer{ _observer.lock() }; observer.get() != observerToRemove)
			_observer.reset();
	}
	void NotifyAllObservers(const NotificationParamType& param) override
	{
		if (auto observer{ _observer.lock() })
			observer->Notify(param);
	}
protected:
	std::weak_ptr<IObserver<NotificationParamType>> _observer;
};