#pragma once

#include "IObject.h"

#include "ObjectType.h"
#include "RenderType.h"

class CCollider;
class CAnimator;
class CPhysics;

class CObject : public IObject
{
public :
	CObject();
	CObject(const CObject& _Object);
	virtual ~CObject();

public :
	virtual void Init()				override;
	virtual void Update()			override;
	virtual void LateUpdate()		override;
	virtual void Render(HDC _hDC)	override;
	virtual void Release()			override;

public :
	const wstring& GetName() const { return m_strName; }
	Vec2 GetPos() const { return m_vPos; }
	Vec2 GetScale() const { return m_vScale; }
	Vec2 GetRenderScale() const { return m_vRenderScale; }
	float GetMass() const { return m_fMass; }
	float GetFriction() const { return m_fFriction; }
	float GetMaxVelocity() const { return m_fMaxVelocity; }
	float GetRadian() const { return m_fRadian; }
	float GetVolume() const { return m_fVolume; }
	bool GetDead()const { return m_bDead; }
	OBJECT_TYPE GetObjectType() const { return m_eObjectType; }
	RENDER_TYPE GetRenderType() const { return m_eRenderType; }
	CCollider* GetCollider() const { return m_pCollider; }
	CAnimator* GetAnimator() const { return m_pAnimator; }
	CPhysics* GetPhysics() const { return m_pPhysics; }

	void SetName(const wstring& _strName) { m_strName = _strName; }
	void SetPos(const Vec2& _vPos) { m_vPos = _vPos; }
	void SetScale(const Vec2& _vScale) { m_vScale = _vScale; }
	void SetRenderScale(const Vec2& _vRenderScale) { m_vRenderScale = _vRenderScale; }
	void SetMass(const float _fMass) { m_fMass = _fMass; }
	void SetFriction(const float _fFriction) { m_fFriction = _fFriction; }
	void SetMaxVelocity(const float _fMaxVelocity) { m_fMaxVelocity = _fMaxVelocity; }
	void SetRadian(const float _fRadian) { m_fRadian = _fRadian; }
	void SetVolume(const float _fVolume) { m_fVolume = _fVolume; }
	void SetDead(const bool _bDead) { m_bDead = _bDead; }
	void SetObjectType(const OBJECT_TYPE _eObjectType) { m_eObjectType = _eObjectType; }
	void SetRenderType(const RENDER_TYPE _eRenderType) { m_eRenderType = _eRenderType; }

public :
	virtual void CreateAnimation() {};
	virtual CObject* Clone() { return nullptr; }

public :
	void CreateCollider();
	void CreateAnimator();
	void CreatePhysics();

	void AnimationRender(HDC _hDC);
	void ColliderRender(HDC _hDC);

	virtual void OnCollision(CCollider& _pOther);
	virtual void OnCollisionEnter(CCollider& _pOther);
	virtual void OnCollisionExit(CCollider& _pOther);

private :
	wstring m_strName;

	Vec2 m_vPos;
	Vec2 m_vScale;
	Vec2 m_vRenderScale;

	float m_fMass;
	float m_fFriction;
	float m_fMaxVelocity;
	float m_fRadian;
	float m_fVolume;

	bool m_bDead;

	OBJECT_TYPE m_eObjectType;
	RENDER_TYPE m_eRenderType;

private :
	CCollider* m_pCollider;
	CAnimator* m_pAnimator;
	CPhysics* m_pPhysics;
};