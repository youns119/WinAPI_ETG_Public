#pragma once

class CObject;

class CPhysics
{
public :
	CPhysics();
	~CPhysics();

public :
	void Update();
	void LateUpdate();

public :
	float GetMass() const { return m_fMass; }
	Vec2 GetVelocity() const { return m_vVelocity; }
	float GetMaxVelocity() const { return m_fMaxVelocity; }
	float GetSpeed() { return m_vVelocity.Length(); }
	Vec2 GetDir() { return m_vVelocity.Normalize(); }

	void SetMass(const float _fMass) { m_fMass = _fMass; }
	void SetFriction(const float _fFriction) { m_fFriction = _fFriction; }
	void SetVelocity(Vec2 _vVelocity) { m_vVelocity = _vVelocity; }
	void SetMaxVelocity(float _fMaxVelocity) { m_fMaxVelocity = _fMaxVelocity; }
	void SetAccelAlpha(Vec2 _vAccelAlpha) { m_vAccelAlpha = _vAccelAlpha; }
	void SetOwner(CObject& _pOwner) { m_pOwner = &_pOwner; }

public :
	void AddForce(Vec2 _vForce) { m_vForce += _vForce; }
	void AddVelocity(Vec2 _vVelocity) { m_vVelocity += _vVelocity; }

public :
	void Move();

private :
	float m_fMass;
	float m_fFriction;
	float m_fMaxVelocity;

	Vec2 m_vForce;
	Vec2 m_vAccel;
	Vec2 m_vAccelAlpha;
	Vec2 m_vVelocity;

private :
	CObject* m_pOwner;
};