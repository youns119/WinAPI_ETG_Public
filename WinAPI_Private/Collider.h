#pragma once

class CObject;

class CCollider
{
public :
	CCollider();
	CCollider(const CCollider& _origin);
	virtual ~CCollider();

	CCollider& operator= (CCollider& _origin) = delete;

public:
	void LateUpdate();
	void Render(HDC _hDC);

public :
	Vec2 GetOffsetPos() { return m_vOffsetPos; }
	Vec2 GetFinalPos() { return m_vFinalPos; }
	Vec2 GetScale() { return m_vScale; }
	CObject* GetOwner() { return m_pOwner; }
	UINT GetID() { return m_iID; }
	bool GetShow() { return m_bShow; }
	
	void SetOwner(CObject& _pOwner) { m_pOwner = &_pOwner; }
	void SetOffsetPos(const Vec2& _vPos) { m_vOffsetPos = _vPos; }
	void SetScale(const Vec2& _vScale) { m_vScale = _vScale; }
	void SetShow(bool _bShow) { m_bShow = _bShow; }

public :

public:
	void OnCollision(CCollider& _pOther);
	void OnCollisionEnter(CCollider& _pOther);
	void OnCollisionExit(CCollider& _pOther);

private:
	CObject* m_pOwner;
	Vec2 m_vOffsetPos;
	Vec2 m_vFinalPos;
	Vec2 m_vScale;

	UINT m_iID;
	UINT m_iCollided;

	bool m_bActive;
	bool m_bShow;

	static UINT g_iNextID;
};