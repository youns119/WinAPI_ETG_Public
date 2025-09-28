#include "pch.h"
#include "SceneManager.h"

#include "Edit.h"
#include "Menu.h"
#include "Dungeon.h"
#include "BossRoom.h"
#include "Gun.h"

CSceneManager::CSceneManager()
	: m_pCurrScene(nullptr)
{
	m_vecScene.clear();

	for (int i = 0; i < (UINT)SCENE_TYPE::END; i++)
		for (int j = 0; j < (UINT)OBJECT_TYPE::END; j++)
			m_vecObject[i][j].clear();

	for (int i = 0; i < (UINT)SCENE_TYPE::END; i++)
		for (int j = 0; j < (UINT)RENDER_TYPE::END; j++)
			m_vecRender[i]->clear();
}

CSceneManager::~CSceneManager()
{
	Release();
}

void CSceneManager::Init()
{
	m_vecScene.reserve((UINT)SCENE_TYPE::END);

	m_vecScene.emplace_back(new CEdit);
	m_vecScene.emplace_back(new CMenu);
	m_vecScene.emplace_back(new CDungeon);
	m_vecScene.emplace_back(new CBossRoom);

	for (int i = 0; i < m_vecScene.size(); i++)
	{
		m_pCurrScene = m_vecScene[i];
		m_pCurrScene->Init();
	}

	//m_pCurrScene = m_vecScene[(UINT)SCENE_TYPE::EDIT];
	m_pCurrScene = m_vecScene[(UINT)SCENE_TYPE::MENU];
	//m_pCurrScene = m_vecScene[(UINT)SCENE_TYPE::DUNGEON];
	//m_pCurrScene = m_vecScene[(UINT)SCENE_TYPE::BOSSROOM];

	m_pCurrScene->Enter(nullptr);
}

void CSceneManager::Update()
{
	m_pCurrScene->Update();
	m_pCurrScene->LateUpdate();
}

void CSceneManager::Render(HDC _hDC)
{
	m_pCurrScene->Render(_hDC);
}

void CSceneManager::Release()
{
	Safe_Delete_Vec<CScene*>(m_vecScene);
}

void CSceneManager::AddObject(CObject* _pObject, OBJECT_TYPE _eObjectType)
{
	m_vecObject[(UINT)(m_pCurrScene->GetSceneType())][(UINT)_eObjectType].push_back(_pObject);

	RENDER_TYPE	eRenderType = _pObject->GetRenderType();
	m_vecRender[(UINT)(m_pCurrScene->GetSceneType())][(UINT)eRenderType].push_back(_pObject);
}

void CSceneManager::ChangeRender(CObject* _pObject, OBJECT_TYPE _eObjectType, RENDER_TYPE _eRenderType)
{
	vector<CObject*>& vecObject = CSceneManager::Get()->GetGroupObjects(_eObjectType);
	RENDER_TYPE eRenderType = RENDER_TYPE::END;

	{
		auto iter = vecObject.begin();

		for (iter = vecObject.begin(); iter != vecObject.end();)
		{
			if ((*iter) == _pObject)
			{
				eRenderType = _pObject->GetRenderType();
				break;
			}
			else ++iter;
		}
	}

	vector<CObject*>& vecRender = CSceneManager::Get()->GetGroupRender(eRenderType);

	{
		auto iter = vecRender.begin();

		for (iter = vecRender.begin(); iter != vecRender.end();)
		{
			if ((*iter) == _pObject)
			{
				iter = vecRender.erase(iter);
				break;
			}
			else ++iter;
		}
	}

	m_vecRender[(UINT)(m_pCurrScene->GetSceneType())][(UINT)_eRenderType].push_back(_pObject);
}

void CSceneManager::ChangeRealScene(SCENE_TYPE _eSceneType, CObject* _pPlayer)
{
	m_pCurrScene->Exit(nullptr);

	CScene* pPreScene = m_pCurrScene;
	m_pCurrScene = m_vecScene[(UINT)_eSceneType];

	{
		vector<CObject*>& vecObject = m_vecObject[(UINT)pPreScene->GetSceneType()][(UINT)OBJECT_TYPE::PLAYER];
		auto iter = vecObject.begin();

		for (iter = vecObject.begin(); iter != vecObject.end();)
		{
			if ((*iter) != nullptr)
			{
				vector<CObject*>& vecRender = m_vecRender[(UINT)pPreScene->GetSceneType()][(UINT)((*iter)->GetRenderType())];
				auto iter2 = vecRender.begin();

				for (iter2 = vecRender.begin(); iter2 != vecRender.end();)
				{
					if ((*iter) == (*iter2))
					{
						vecRender.erase(iter2);
						break;
					}
					else iter2++;
				}

				AddObject((*iter), OBJECT_TYPE::PLAYER);
				iter = vecObject.erase(iter);
			}
			else ++iter;
		}
	}

	{
		vector<CObject*>& vecObject = m_vecObject[(UINT)pPreScene->GetSceneType()][(UINT)OBJECT_TYPE::GUN];
		auto iter = vecObject.begin();

		for (iter = vecObject.begin(); iter != vecObject.end();)
		{
			if ((*iter) != nullptr)
			{
				CGun* pGun = dynamic_cast<CGun*>((*iter));

				if (pGun->GetTarget() == m_vecObject[(UINT)_eSceneType][(UINT)OBJECT_TYPE::PLAYER][0])
				{
					vector<CObject*>& vecRender = m_vecRender[(UINT)pPreScene->GetSceneType()][(UINT)(*iter)->GetRenderType()];
					auto iter2 = vecRender.begin();

					for (iter2 = vecRender.begin(); iter2 != vecRender.end();)
					{
						if ((*iter) == (*iter2))
						{
							vecRender.erase(iter2);
							break;
						}
						else iter2++;
					}

					AddObject((*iter), OBJECT_TYPE::GUN);
					iter = vecObject.erase(iter);
				}
				else ++iter;
			}
			else ++iter;
		}
	}

	{
		vector<CObject*>& vecObject = m_vecObject[(UINT)pPreScene->GetSceneType()][(UINT)OBJECT_TYPE::UI];
		auto iter = vecObject.begin();

		for (iter = vecObject.begin(); iter != vecObject.end();)
		{
			if ((*iter) != nullptr)
			{
				vector<CObject*>& vecRender = m_vecRender[(UINT)pPreScene->GetSceneType()][(UINT)(*iter)->GetRenderType()];
				auto iter2 = vecRender.begin();

				for (iter2 = vecRender.begin(); iter2 != vecRender.end();)
				{
					if ((*iter) == (*iter2))
					{
						vecRender.erase(iter2);
						break;
					}
					else iter2++;
				}

				AddObject((*iter), OBJECT_TYPE::UI);
				iter = vecObject.erase(iter);
			}
			else ++iter;
		}
	}

	{
		vector<CObject*>& vecObject = m_vecObject[(UINT)pPreScene->GetSceneType()][(UINT)OBJECT_TYPE::MOUSE];
		auto iter = vecObject.begin();

		for (iter = vecObject.begin(); iter != vecObject.end();)
		{
			if ((*iter) != nullptr)
			{
				vector<CObject*>& vecRender = m_vecRender[(UINT)pPreScene->GetSceneType()][(UINT)(*iter)->GetRenderType()];
				auto iter2 = vecRender.begin();

				for (iter2 = vecRender.begin(); iter2 != vecRender.end();)
				{
					if ((*iter) == (*iter2))
					{
						vecRender.erase(iter2);
						break;
					}
					else iter2++;
				}

				AddObject((*iter), OBJECT_TYPE::MOUSE);
				iter = vecObject.erase(iter);
			}
			else ++iter;
		}
	}

	m_pCurrScene->Enter(_pPlayer);
}