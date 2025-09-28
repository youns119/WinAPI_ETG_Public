#include "pch.h"
#include "EventManager.h"

#include "SceneManager.h"
#include "UIManager.h"

#include "Object.h"
#include "Texture.h"
#include "Scene.h"

CEventManager::CEventManager()
{
	m_vecEvents.reserve(20);
}

CEventManager::~CEventManager()
{
}

void CEventManager::Update()
{
	for (size_t i = 0; i < m_vecDead.size(); ++i)
		Safe_Delete(m_vecDead[i]);

	m_vecDead.clear();

	for (size_t i = 0; i < m_vecEvents.size(); ++i)
		ExcuteEvent(m_vecEvents[i]);

	m_vecEvents.clear();
}

void CEventManager::ExcuteEvent(const Event& _tEvent)
{
	switch (_tEvent.eEventType)
	{
		case EVENT_TYPE::CREATE_OBJECT:
		{
			CObject* pObject = (CObject*)_tEvent.LParam;
			OBJECT_TYPE ObjectType = (OBJECT_TYPE)_tEvent.RParam;

			CSceneManager::Get()->AddObject(pObject, ObjectType);

			break;
		}
		case EVENT_TYPE::DELETE_OBJECT:
		{
			CObject* pObject = (CObject*)_tEvent.LParam;

			if (!pObject->GetDead())
			{
				pObject->SetDead(true);
				m_vecDead.push_back(pObject);
			}

			break;
		}
		case EVENT_TYPE::SCENE_CHANGE:
		{
			CSceneManager::Get()->ChangeRealScene((SCENE_TYPE)_tEvent.LParam, _tEvent.pObject);

			//UIManager::GetInstance()->SetFocusUI(nullptr);

			break;
		}
	}
}