#pragma once

#include <list>

template <typename... parametersTypes>
class Event
{
public:
	void AddListener(void (*InvokeFunc)(parametersTypes...));
	void RemoveListener(void (*InvokeFunc)(parametersTypes...));
	void Invoke(parametersTypes... args);
private:
	std::list<void (*)(parametersTypes...)> listeners;
};

template <typename... parametersTypes>
void Event<parametersTypes...>::AddListener(void (*InvokeFunc)(parametersTypes...))
{
	listeners.push_back(InvokeFunc);
}

template <typename... parametersTypes>
void Event<parametersTypes...>::RemoveListener(void (*InvokeFunc)(parametersTypes...))
{
	listeners.remove(InvokeFunc);
}

template <typename... parametersTypes>
void Event<parametersTypes...>::Invoke(parametersTypes... args)
{
	for (auto invokedFunction : listeners)
		invokedFunction(args...);
}