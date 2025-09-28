#include "pch.h"
#include "Func.h"

#include "EventManager.h"

void CreateObjectEvent(CObject* _pObject, OBJECT_TYPE _eObjectType)
{
	Event tEvent = {};

	tEvent.eEventType = EVENT_TYPE::CREATE_OBJECT;
	tEvent.LParam = (DWORD_PTR)_pObject;
	tEvent.RParam = (DWORD_PTR)_eObjectType;
	tEvent.pObject = nullptr;

	CEventManager::Get()->AddEvent(tEvent);
}

void DeleteObjectEvent(CObject* _pObject)
{
	Event tEvent = {};
	tEvent.eEventType = EVENT_TYPE::DELETE_OBJECT;
	tEvent.LParam = (DWORD_PTR)_pObject;
	tEvent.pObject = nullptr;

	CEventManager::Get()->AddEvent(tEvent);
}

void ChangeScene(SCENE_TYPE _eSceneType, CObject* _pObject)
{
	Event tEvent = {};
	tEvent.eEventType = EVENT_TYPE::SCENE_CHANGE;
	tEvent.LParam = (DWORD_PTR)_eSceneType;
	tEvent.pObject = _pObject;

	CEventManager::Get()->AddEvent(tEvent);
}

void FScanf(char* _pBuffer, FILE* _pFile)
{
	int i = 0;

	while (true)
	{
		char c = static_cast<char>(getc(_pFile));
		if (c == '\n')
		{
			_pBuffer[i++] = '\0';
			break;
		}
		_pBuffer[i++] = c;
	}
}