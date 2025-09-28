#pragma once

#include "Object.h"

#include "ItemType.h"

class CTexture;

class CItem : public CObject
{
public :
	CItem();
	~CItem();

public :
	virtual void Init()				override;
	virtual void Update()			override;
	virtual void LateUpdate()		override;
	virtual void Render(HDC _hDC)	override;
	virtual void Release()			override;

public :
	int GetPrice() const { return m_iPrice; }
	ITEM_TYPE GetItemType() const { return m_eItemType; }
	CTexture* GetTexture() const { return m_pTexture; }

	void SetPrice(const int _iPrice) { m_iPrice = _iPrice; }
	void SetColOffset(const Vec2 _vOffset) { m_vColOffset = _vOffset; }
	void SetItemType(ITEM_TYPE _eItemType) { m_eItemType = _eItemType; }
	void SetTexture(CTexture* _pTexture) { m_pTexture = _pTexture; }

public :
	void PriceUpdate();

public:
	virtual void OnCollision(CCollider& _pOther)		override;
	virtual void OnCollisionEnter(CCollider& _pOther)	override;
	virtual void OnCollisionExit(CCollider& _pOther)	override;

private :
	int m_iPrice;

	bool m_bShowPrice;

	Vec2 m_vColOffset;

private:
	vector<int> m_vecCount;

private :
	CTexture* m_pTexture;

	ITEM_TYPE m_eItemType;
};