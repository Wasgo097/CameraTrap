#pragma once
#include "Interfaces/IObservable.h"
#include <unordered_set>
#include <algorithm>
template<class NotificationParamType>
class MultipleObservableBasic : public IObservable<NotificationParamType>
{
public:
	virtual ~MultipleObservableBasic() = default;
	void AddNewObserver(std::shared_ptr<IObserver<NotificationParamType>> newObserver)override
	{
		_observers.emplace(std::move(newObserver));
	}
	void RemoveObserver(IObserver<NotificationParamType>* observerToRemove) override
	{
		auto toRemove{ std::ranges::find_if(_observers,[observerToRemove](const std::weak_ptr<IObserver<NotificationParamType>>& current)
			{
				if (auto ptr{current.lock()})
				return ptr == observerToRemove;
			}) };
		if (toRemove != _observers.end())
			_observers.erase(toRemove);
	}
	void NotifyAllObservers(const NotificationParamType& param) override
	{
		for (const auto& weakObserver : _observers)
		{
			if (auto observer{ weakObserver.lock() })
				observer->Notify(param);

		}
	}
protected:
	std::unordered_set<std::weak_ptr<IObserver<NotificationParamType>>> _observers;
};