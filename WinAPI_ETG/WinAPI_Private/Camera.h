#pragma once

#include "CameraEffect.h"

class CObject;
class CTexture;

struct CameraEffect
{
	float fDuration;
	float fCurrTime;
	CAMERA_EFFECT eEffectType;
};

class CCamera : public Singleton<CCamera>
{
public :
	CCamera();
	virtual ~CCamera();

public :
	void Init();
	void Update();
	void Render(HDC _hDC);

public :
	Vec2 GetLookPos() const { return m_vCurrLookPos; }
	CObject* GetTarget() const { return m_pTarget; }
	Vec2 GetRenderPos(Vec2 _vPos) const { return (_vPos - m_vDiff); }
	Vec2 GetRealPos(Vec2 _vRenderPos) const { return (_vRenderPos + m_vDiff); }

	void SetLookAtPos(Vec2 _vLookAtPos) { m_vLookAtPos = _vLookAtPos; }
	void SetCurrLookPos(Vec2 _vCurrLookPos) { m_vCurrLookPos = _vCurrLookPos; }
	void SetPrevLookPos(Vec2 _vPrevLookPos) { m_vPrevLookPos = _vPrevLookPos; }
	void SetTarget(CObject* _pTarget) { m_pTarget = _pTarget; };
	void SetTargettingSpeed(float _fTargettingSpeed) { m_fTargettingSpeed = _fTargettingSpeed; }

public :
	void CalDiff();

public :
	void Shake(float _fDuration, float _fDistance);
	void FadeIn(float _fDuration);
	void FadeOut(float _fDuration);

private :
	Vec2 m_vLookAtPos;
	Vec2 m_vCurrLookPos;
	Vec2 m_vPrevLookPos;

	CObject* m_pTarget;
	float m_fTargettingSpeed;
	Vec2 m_vDiff;

	bool m_bShake;
	int m_iRL;
	float m_fDistance;

private :
	list<CameraEffect> m_listCameraEffect;

	CameraEffect m_tCameraShake;

	CTexture* m_pVeilTexture;
};