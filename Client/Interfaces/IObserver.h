#pragma once
template<class NotificationParamType>
class IObserver
{
public:
	virtual ~IObserver() = default;
	void Notify(const NotificationParamType& param) = 0;
};