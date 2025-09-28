#pragma once

#include "SceneType.h"

#include "Scene.h"
//class CScene;

class CSceneManager : public Singleton<CSceneManager>
{
public :
	CSceneManager();
	virtual ~CSceneManager();

public :
	void Init();
	void Update();
	void Render(HDC _hDC);
	void Release();

public :
	vector<CObject*>& GetObjectsVec(UINT _iIndex) { return m_vecObject[(UINT)(m_pCurrScene->GetSceneType())][_iIndex]; }
	vector<CObject*>& GetRenderVec(UINT _iIndex) { return m_vecRender[(UINT)(m_pCurrScene->GetSceneType())][_iIndex]; }
	vector<CObject*>& GetGroupObjects(const OBJECT_TYPE _eObjectType)
	{
		return m_vecObject[(UINT)(m_pCurrScene->GetSceneType())][(UINT)_eObjectType];
	}
	vector<CObject*>& GetGroupRender(const RENDER_TYPE _eRenderType)
	{
		return m_vecRender[(UINT)(m_pCurrScene->GetSceneType())][(UINT)_eRenderType];
	}
	CScene* GetCurrScene() const 
	{ 
		if (m_pCurrScene != nullptr)
			return m_pCurrScene;
		else
			return nullptr;
	}
	vector<CScene*> GetScenes() const { return m_vecScene; }

	void SetCurrScene(CScene* _pScene) { m_pCurrScene = _pScene; }

public :
	void AddObject(CObject* _pObject, OBJECT_TYPE _eObjectType);
	void ChangeRender(CObject* _pObject, OBJECT_TYPE _eObjectType, RENDER_TYPE _eRenderType);
	void ChangeRealScene(SCENE_TYPE _eSceneType, CObject* _pPlayer);


private :
	vector<CScene*> m_vecScene;
	vector<CObject*> m_vecObject[(UINT)SCENE_TYPE::END][(UINT)OBJECT_TYPE::END];
	vector<CObject*> m_vecRender[(UINT)SCENE_TYPE::END][(UINT)RENDER_TYPE::END];

	CScene* m_pCurrScene;

private :
	vector<CScene*>::iterator m_SceneIter;
};