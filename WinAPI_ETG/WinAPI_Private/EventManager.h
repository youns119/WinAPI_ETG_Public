#pragma once

#include "EventType.h"

class CObject;

struct Event
{
	EVENT_TYPE	eEventType;
	DWORD_PTR	LParam;
	DWORD_PTR	RParam;
	CObject* pObject;
};

class CEventManager : public Singleton<CEventManager>
{
public :
	CEventManager();
	virtual ~CEventManager();

public:
	void Update();

private:
	void ExcuteEvent(const Event& _tEvent);

public:
	void AddEvent(const Event& _tEvent)
	{
		m_vecEvents.emplace_back(_tEvent);
	}

private:
	vector<Event> m_vecEvents;
	vector<CObject*> m_vecDead;
};