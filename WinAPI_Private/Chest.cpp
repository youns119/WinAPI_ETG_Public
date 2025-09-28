#include "pch.h"
#include "Chest.h"

#include "ResourceManager.h"
#include "SceneManager.h"
#include "Camera.h"
#include "SoundManager.h"

#include "Func.h"
#include "Collider.h"
#include "Animator.h"
#include "Animation.h"
#include "Physics.h"
#include "Player.h"
#include "Item_Gun.h"
#include "Medikit.h"
#include "ChestEffect.h"

CChest::CChest()
	: m_eChestState(CHEST_STATE::END)
	, m_bContact(false)
	, m_bOpened(false)
	, m_eItemType(ITEM_TYPE::END)
	, m_eGunType(GUN_TYPE::END)
{
	SetRenderType(RENDER_TYPE::RENDER_OBJECT);
	SetInteractType(INTERACT_TYPE::CHEST);
}

CChest::CChest(GUN_TYPE _eGunType)
	: m_eChestState(CHEST_STATE::END)
	, m_bContact(false)
	, m_bOpened(false)
	, m_eItemType(ITEM_TYPE::END)
	, m_eGunType(GUN_TYPE::END)
{
	SetRenderType(RENDER_TYPE::RENDER_OBJECT);
	SetInteractType(INTERACT_TYPE::CHEST);

	m_eItemType = ITEM_TYPE::GUN;
	m_eGunType = _eGunType;
}

CChest::CChest(ITEM_TYPE _eItemType)
	: m_eChestState(CHEST_STATE::END)
	, m_bContact(false)
	, m_bOpened(false)
	, m_eItemType(ITEM_TYPE::END)
	, m_eGunType(GUN_TYPE::END)
{
	SetRenderType(RENDER_TYPE::RENDER_OBJECT);
	SetInteractType(INTERACT_TYPE::CHEST);

	m_eItemType = ITEM_TYPE::MEDIKIT;
}

CChest::~CChest()
{
	Release();
}

void CChest::Init()
{
	SetName(L"Chest");
	SetScale({ 80.f, 30.f });
	SetRenderScale({ 108.f, 108.f });

	SetVolume(0.15f);

	m_eChestState = CHEST_STATE::IDLE;

	Vec2 vPos = { GetPos().fX, GetPos().fY };
	Vec2 vScale = { GetScale().fX + 40.f, GetScale().fY + 80.f };

	SetColOffset(vPos, vScale);

	SetHP(100);

	__super::Init();

	GetCollider()->SetOffsetPos(Vec2(0.f, -20.f));

	CreateAnimation();
}

void CChest::Update()
{
	CObject* pObject = CSceneManager::Get()->GetGroupObjects(OBJECT_TYPE::PLAYER)[0];

	CPlayer* pPlayer = dynamic_cast<CPlayer*>(pObject);

	if (m_eChestState == CHEST_STATE::IDLE)
	{
		if (isOffsetCollision(pObject))
		{
			pPlayer->SetCurrInteract(this);
			m_bContact = true;
		}
		else
		{
			if (pPlayer->GetCurrInteract() == this)
				pPlayer->SetCurrInteract(nullptr);
			m_bContact = false;
		}
	}
}

void CChest::LateUpdate()
{
	__super::LateUpdate();

	if (m_eChestState == CHEST_STATE::OPEN)
		if (GetAnimator()->GetCurrAnim()->GetFinish())
		{
			m_eChestState = CHEST_STATE::OPENED;
			m_bOpened = true;

			CreateItem();
		}

	if (GetHP() <= 0)
		if (m_eChestState != CHEST_STATE::BREAK && m_eChestState != CHEST_STATE::BROKEN)
		{
			m_eChestState = CHEST_STATE::BREAK;

			CSoundManager::Get()->PlaySound(L"Chest_Break.wav", CHANNELID::SOUND_EFFECT, GetVolume());

			CreateEffect();
		}

	if (m_eChestState == CHEST_STATE::BREAK)
		if (GetAnimator()->GetCurrAnim()->GetFinish())
		{
			m_eChestState = CHEST_STATE::BROKEN;
			CSceneManager::Get()->ChangeRender(this, GetObjectType(), RENDER_TYPE::RENDER_TILE_PREV);

			if(!m_bOpened)
				CreateItem();
		}

	Motion();
}

void CChest::Render(HDC _hDC)
{
	//Vec2 vRenderPos = CCamera::Get()->GetRenderPos(GetColOffset().vPos);

	__super::Render(_hDC);

	//Rectangle
	//(
	//	_hDC,
	//	vRenderPos.fX - GetColOffset().vScale.fX / 2.f,
	//	vRenderPos.fY - GetColOffset().vScale.fY / 2.f,
	//	vRenderPos.fX + GetColOffset().vScale.fX / 2.f,
	//	vRenderPos.fY + GetColOffset().vScale.fY / 2.f
	//);
}

void CChest::Release()
{
}

void CChest::CreateItem()
{
	if (m_eItemType == ITEM_TYPE::GUN)
	{
		CItem_Gun* pItemGun = new CItem_Gun(m_eGunType);
		pItemGun->Init();
		pItemGun->SetPos({ GetPos().fX, GetPos().fY });
		pItemGun->GetPhysics()->AddVelocity({ 0.f, pItemGun->GetPhysics()->GetMaxVelocity() });

		CSoundManager::Get()->PlaySound(L"Item_Throw.wav", CHANNELID::SOUND_EFFECT, GetVolume());

		CreateObjectEvent(pItemGun, pItemGun->GetObjectType());
	}
	else if (m_eItemType == ITEM_TYPE::MEDIKIT)
	{
		CMedikit* pMedikit = new CMedikit;
		pMedikit->Init();
		pMedikit->SetPos({ GetPos().fX, GetPos().fY });
		pMedikit->GetPhysics()->AddVelocity({ 0.f, pMedikit->GetPhysics()->GetMaxVelocity() });

		CSoundManager::Get()->PlaySound(L"Item_Throw.wav", CHANNELID::SOUND_EFFECT, GetVolume());

		CreateObjectEvent(pMedikit, pMedikit->GetObjectType());
	}
}

void CChest::Motion()
{
	if (m_eChestState == CHEST_STATE::IDLE)
	{
		if (m_bContact)
			GetAnimator()->PlayAnimation(L"Chest_Alt", true);
		else
			GetAnimator()->PlayAnimation(L"Chest", true);
	}
	else if (m_eChestState == CHEST_STATE::OPEN)
		GetAnimator()->PlayAnimation(L"Chest_Open", false);
	else if (m_eChestState == CHEST_STATE::OPENED)
		GetAnimator()->PlayAnimation(L"Chest_Opened", true);
	else if (m_eChestState == CHEST_STATE::BREAK)
		GetAnimator()->PlayAnimation(L"Chest_Break", false);
	else if (m_eChestState == CHEST_STATE::BROKEN)
		GetAnimator()->PlayAnimation(L"Chest_Broken", true);
}

void CChest::CreateAnimation()
{
	GetAnimator()->CreateAnimation(L"Chest", CResourceManager::Get()->FindTexture(L"Chest"), Vec2(0, 0), Vec2(108, 108), Vec2(108, 0), .1f, 1);
	GetAnimator()->CreateAnimation(L"Chest_Alt", CResourceManager::Get()->FindTexture(L"Chest_Alt"), Vec2(0, 0), Vec2(108, 108), Vec2(108, 0), .1f, 1);
	GetAnimator()->CreateAnimation(L"Chest_Opened", CResourceManager::Get()->FindTexture(L"Chest_Opened"), Vec2(0, 0), Vec2(108, 108), Vec2(108, 0), .1f, 1);
	GetAnimator()->CreateAnimation(L"Chest_Broken", CResourceManager::Get()->FindTexture(L"Chest_Broken"), Vec2(0, 0), Vec2(108, 108), Vec2(108, 0), .1f, 1);
	GetAnimator()->CreateAnimation(L"Chest_Open", CResourceManager::Get()->FindTexture(L"Chest_Open"), Vec2(0, 0), Vec2(108, 108), Vec2(108, 0), .1f, 5);
	GetAnimator()->CreateAnimation(L"Chest_Break", CResourceManager::Get()->FindTexture(L"Chest_Break"), Vec2(0, 0), Vec2(108, 108), Vec2(108, 0), .1f, 4);
}

void CChest::CreateEffect()
{
	CChestEffect* pChestEffect = new CChestEffect;

	pChestEffect->Init();
	pChestEffect->SetPos({ GetPos().fX, GetPos().fY + 10.f });
	CreateObjectEvent(pChestEffect, OBJECT_TYPE::EFFECT);
}

void CChest::OnCollision(CCollider& _pOther)
{
	CObject* pOwner = _pOther.GetOwner();

	if (pOwner->GetObjectType() == OBJECT_TYPE::PLAYER || pOwner->GetObjectType() == OBJECT_TYPE::ENEMY)
	{
		float fWidth = fabsf(GetCollider()->GetFinalPos().fX - _pOther.GetFinalPos().fX);
		float fHeight = fabsf(GetCollider()->GetFinalPos().fY - _pOther.GetFinalPos().fY);

		float fRadiusX = (GetCollider()->GetScale().fX + _pOther.GetScale().fX) * 0.5f;
		float fRadiusY = (GetCollider()->GetScale().fY + _pOther.GetScale().fY) * 0.5f;

		fWidth = fRadiusX - fWidth;
		fHeight = fRadiusY - fHeight;

		if (m_eChestState == CHEST_STATE::IDLE ||
			m_eChestState == CHEST_STATE::OPEN ||
			m_eChestState == CHEST_STATE::OPENED)
		{
			if (fWidth > fHeight)
			{
				if (GetCollider()->GetFinalPos().fY < _pOther.GetFinalPos().fY)
					pOwner->SetPos(Vec2(pOwner->GetPos().fX, pOwner->GetPos().fY + fHeight + 1.f));
				else
					pOwner->SetPos(Vec2(pOwner->GetPos().fX, pOwner->GetPos().fY - fHeight - 1.f));
			}
			else
			{
				if (GetCollider()->GetFinalPos().fX < _pOther.GetFinalPos().fX)
					pOwner->SetPos(Vec2(pOwner->GetPos().fX + fWidth + 1.f, pOwner->GetPos().fY));
				else
					pOwner->SetPos(Vec2(pOwner->GetPos().fX - fWidth - 1.f, pOwner->GetPos().fY));
			}
		}
		else if (m_eChestState == CHEST_STATE::BREAK || m_eChestState == CHEST_STATE::BROKEN)
			return;
	}
}

void CChest::OnCollisionEnter(CCollider& _pOther)
{
}

void CChest::OnCollisionExit(CCollider& _pOther)
{
}