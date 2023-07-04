#pragma once
#include "Interfaces/IObservable.h"
#include <unordered_set>
#include <algorithm>
template<class ObserverType, class NotificationParamType>
class ObservableBasic : public IObservable<ObserverType, NotificationParamType>
{
public:
	virtual ~ObservableBasic() = default;
	void AddNewObserver(std::shared_ptr<ObserverType> newObserver) override
	{
		_observers.emplace(std::move(newObserver));
	}
	void RemoveObserver(const std::shared_ptr<ObserverType>& observerToRemove) override
	{
		auto toRemove{ std::ranges::find_if(_observers,[=observer](const std::weak_ptr<ObserverType>& current)
			{
				return current == toRemove;
			}) };
		if (toRemove != _observers.end())
			_observers.erase(toRemove)
	}
protected:
	std::unordered_set<std::weak_ptr<ObserverType>> _observers;
};