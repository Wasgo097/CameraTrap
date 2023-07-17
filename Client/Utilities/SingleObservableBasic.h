#pragma once
#include "Interfaces/IObservable.h"
template<class NotificationParamType>
class SingleObservableBasic : public IObservable<NotificationParamType>
{
public:
	virtual ~SingleObservableBasic() = default;
	void AddNewObserver(std::shared_ptr<IObserver<NotificationParamType>> pNewObserver) override
	{
		_pObserver = std::move(pNewObserver);
	}
	void RemoveObserver(IObserver<NotificationParamType>* pObserverToRemove) override
	{
		if (auto observer{ _pObserver.lock() }; observer.get() != pObserverToRemove)
			_pObserver.reset();
	}
	void NotifyAllObservers(const NotificationParamType& param) override
	{
		if (auto observer{ _pObserver.lock() })
			observer->Notify(param);
	}
protected:
	std::weak_ptr<IObserver<NotificationParamType>> _pObserver;
};