#pragma once
template<class NotificationParamType>
class IObserver
{
public:
	virtual ~IObserver() = default;
	virtual void Notify(NotificationParamType param) = 0;
};