#pragma once

#include "Interact.h"

#include "ChestState.h"

#include "ItemType.h"
#include "GunType.h"

class CItem;

class CChest : public CInteract
{
public :
	CChest();
	CChest(GUN_TYPE _eGunType);
	CChest(ITEM_TYPE _eItemType);
	virtual ~CChest();

public :
	virtual void Init()				override;
	virtual void Update()			override;
	virtual void LateUpdate()		override;
	virtual void Render(HDC _hDC)	override;
	virtual void Release()			override;

public :
	CHEST_STATE GetChestState() const { return m_eChestState; }
	bool GetContact() const { return m_bContact; }

	void SetChestState(const CHEST_STATE _eChestState) { m_eChestState = _eChestState; }
	void SetContact(const bool _bContact) { m_bContact = _bContact; }

public :
	void CreateItem();

public :
	virtual void Motion() override;
	virtual void CreateAnimation() override;
	virtual void CreateEffect() override;

public :
	virtual void OnCollision(CCollider& _pOther);
	virtual void OnCollisionEnter(CCollider& _pOther);
	virtual void OnCollisionExit(CCollider& _pOther);

private :
	CHEST_STATE m_eChestState;

private :
	bool m_bContact;
	bool m_bOpened;

private :
	ITEM_TYPE m_eItemType;

	GUN_TYPE m_eGunType;
};