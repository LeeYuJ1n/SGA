#include "Framework.h"

void Observer::AddEvent(string key, Event event)
{
    totalEvent[key].push_back(event);
}

void Observer::AddParamEvent(string key, ParamEvent paramEvent)
{
    totalParamEvent[key].push_back(paramEvent);
}

void Observer::ExcuteEvent(string key)
{
    for (Event event : totalEvent[key])
    {
        event();
    }
}

void Observer::ExcuteParamEvent(string key, void* object)
{
    for (ParamEvent paramEvent : totalParamEvent[key])
    {
        paramEvent(object);
    }
}
