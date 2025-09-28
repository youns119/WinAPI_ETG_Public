#include "pch.h"
#include "Scene.h"

#include "SceneManager.h"
#include "Main.h"
#include "Camera.h"

#include "Object.h"

CScene::CScene()
	: m_strName(L"")
	, m_fVolume(0.f)
	, m_eSceneType(SCENE_TYPE::END)
{
}

CScene::~CScene()
{
	Release();
}

void CScene::Init()
{
	for (UINT i = 0; i < (UINT)OBJECT_TYPE::END; i++)
	{
		vector<CObject*>& vecObject = CSceneManager::Get()->GetObjectsVec(i);

		for (size_t j = 0; j < vecObject.size(); j++)
			if (!vecObject[j]->GetDead())
				vecObject[j]->Init();
	}
}

void CScene::Update()
{
	for (UINT i = 0; i < (UINT)OBJECT_TYPE::END; i++)
	{
		vector<CObject*>& vecObject = CSceneManager::Get()->GetObjectsVec(i);

		for (size_t j = 0; j < vecObject.size(); j++)
			if (!vecObject[j]->GetDead())
				vecObject[j]->Update();
	}
}

void CScene::LateUpdate()
{
	for (UINT i = 0; i < (UINT)OBJECT_TYPE::END; i++)
	{
		vector<CObject*>& vecObject = CSceneManager::Get()->GetObjectsVec(i);

		for (size_t j = 0; j < vecObject.size(); j++)
			if (!vecObject[j]->GetDead())
				vecObject[j]->LateUpdate();
	}
}

void CScene::Render(HDC _hDC)
{
	for (UINT i = 0; i < (UINT)RENDER_TYPE::END; i++)
	{
		vector<CObject*>& vecRender = CSceneManager::Get()->GetRenderVec(i);

		sort(vecRender.begin(), vecRender.end(), [](CObject* pDst, CObject* pSrc)->bool
			{
				return pDst->GetPos().fY < pSrc->GetPos().fY;
			});

		vector<CObject*>::iterator iter = vecRender.begin();

		for (iter = vecRender.begin(); iter != vecRender.end();)
		{
			if ((*iter)->GetObjectType() == OBJECT_TYPE::UI)
			{
				(*iter)->Render(_hDC);
				++iter;
			}
			else if (!(*iter)->GetDead())
			{
				Vec2 vPos = (*iter)->GetPos();
				Vec2 vScale = (*iter)->GetRenderScale();

				Vec2 vRenderPos = CCamera::Get()->GetRenderPos(vPos);

				if (vRenderPos.fX + vScale.fX / 2.f < -10.f ||
					vRenderPos.fX - vScale.fX / 2.f > (float)CMain::Get()->GetResolution().x + 10.f ||
					vRenderPos.fY + vScale.fY / 2.f < -10.f ||
					vRenderPos.fY - vScale.fY / 2.f > (float)CMain::Get()->GetResolution().y + 10.f)
				{
					++iter;
					continue;
				}

				(*iter)->Render(_hDC);
				++iter;
			}
			else
				iter = vecRender.erase(iter);
		}
	}

	for (UINT i = 0; i < (UINT)OBJECT_TYPE::END; i++)
	{
		vector<CObject*>& vecObject = CSceneManager::Get()->GetObjectsVec(i);

		vector<CObject*>::iterator iter = vecObject.begin();

		for (iter = vecObject.begin(); iter != vecObject.end();)
		{
			if ((*iter)->GetDead())
				iter = vecObject.erase(iter);
			else ++iter;
		}
	}

	for (UINT i = 0; i < (UINT)RENDER_TYPE::END; i++)
	{
		vector<CObject*>& vecRender = CSceneManager::Get()->GetRenderVec(i);

		vector<CObject*>::iterator iter = vecRender.begin();

		for (iter = vecRender.begin(); iter != vecRender.end(); iter++)
			(*iter)->ColliderRender(_hDC);
	}
}

void CScene::Release()
{
	for (UINT i = 0; i < (UINT)OBJECT_TYPE::END; i++)
		if (CSceneManager::Get()->GetObjectsVec(i).size() > 0)
			DeleteGroupObjects(OBJECT_TYPE(i));

	//for (UINT i = 0; i < (UINT)RENDER_TYPE::END; i++)
	//	if (CSceneManager::Get()->GetGroupRender((RENDER_TYPE)i).size() > 0)
	//		DeleteGroupRender((RENDER_TYPE)i);
}

void CScene::DeleteGroupObjects(OBJECT_TYPE _eObjectType)
{
	vector<CObject*>& vecObject = CSceneManager::Get()->GetObjectsVec((UINT)_eObjectType);
	Safe_Delete_Vec<CObject*>(vecObject);
}

void CScene::DeleteGroupRender(RENDER_TYPE _eRenderType)
{
	vector<CObject*>& vecRender = CSceneManager::Get()->GetGroupRender(_eRenderType);
	Safe_Delete_Vec<CObject*>(vecRender);
}

void CScene::DeleteAllGroups()
{
	for (UINT i = 0; i < (UINT)OBJECT_TYPE::END; i++)
	{
		if ((UINT)(OBJECT_TYPE::PLAYER) == i ||
			(UINT)(OBJECT_TYPE::GUN) == i ||
			(UINT)(OBJECT_TYPE::ITEM) == i ||
			(UINT)(OBJECT_TYPE::UI) == i ||
			(UINT)(OBJECT_TYPE::MOUSE) == i)
			continue;

		if (CSceneManager::Get()->GetObjectsVec(i).size() > 0)
			DeleteGroupObjects(OBJECT_TYPE(i));
	}
}