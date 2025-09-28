#pragma once

class CObject;
class CTexture;

class CMouse : public Singleton<CMouse>
{
public :
	CMouse();
	virtual ~CMouse();

public :
	void Init();
	void Update();
	void Render(HDC _hDC);
	void Release();

public :
	CObject* GetMouse() const { return m_pMouse; }
	CObject* GetPoint() const { return m_pPoint; }
	Vec2 GetPos() const { return m_pMouse->GetPos(); }
	Vec2 GetScale() const { return m_pMouse->GetScale(); }
	float GetDistance() const { return m_fDistance; }

	void SetPos(const Vec2& _vPos) { m_pMouse->SetPos(_vPos); }
	void SetScale(const Vec2& _vScale) { m_pMouse->SetScale(_vScale); }
	void SetDistance(const float _fDistance) { m_fDistance = _fDistance; }
	void SetTarget(CObject* _pTarget) { m_pTarget = _pTarget; }
	void SetPointPos();
	void SetTexture(CTexture* _pTexture) { m_pTexture = _pTexture; }

private :
	CObject* m_pMouse;
	CObject* m_pPoint;
	CObject* m_pTarget;

	float m_fDistance;

private :
	CTexture* m_pTexture;
};