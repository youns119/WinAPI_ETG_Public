#pragma once

#include "SceneType.h"

class CObject;

class CScene
{
public :
	CScene();
	virtual ~CScene();

public :
	virtual void Init();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render(HDC _hDC);
	virtual void Release();

public :
	virtual void Enter(CObject* _pPlayer) PURE;
	virtual void Exit(CObject* _pPlayer)  PURE;

public :
	virtual void SetCollision() PURE;

public :
	void DeleteAllGroups();
	void DeleteGroupObjects(OBJECT_TYPE _eObjectType);
	void DeleteGroupRender(RENDER_TYPE _eRenderType);

public :
	wstring GetName() const { return m_strName; }
	float GetVolume() const { return m_fVolume; }
	SCENE_TYPE GetSceneType() const { return m_eSceneType; }

	void SetSceneType(const SCENE_TYPE _eSceneType) { m_eSceneType = _eSceneType; }
	void SetVolume(const float _fVolume) { m_fVolume = _fVolume; }
	void SetName(const wstring& _strName) { m_strName = _strName; }

private :
	wstring m_strName;

	float m_fVolume;

	SCENE_TYPE m_eSceneType;
};