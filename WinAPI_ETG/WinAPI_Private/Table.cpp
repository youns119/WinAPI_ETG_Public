#include "pch.h"
#include "Table.h"

#include "ResourceManager.h"
#include "SceneManager.h"
#include "Camera.h"
#include "SoundManager.h"

#include "Collider.h"
#include "Animator.h"
#include "Animation.h"
#include "Physics.h"
#include "Player.h"
#include "Enemy.h"
#include "Func.h"
#include "TableEffect.h"

CTable::CTable()
	: m_eTableState(TABLE_STATE::END)
	, m_eTableDir(TABLE_DIR::END)
	, m_bFly(false)
	, m_fDamage(0.f)
{
	SetRenderType(RENDER_TYPE::RENDER_OBJECT);
	SetInteractType(INTERACT_TYPE::TABLE);
}

CTable::~CTable()
{
	Release();
}

void CTable::Init()
{
	SetName(L"Table");
	SetScale({ 100.f, 20.f });
	SetRenderScale({ 144.f, 144.f });

	SetVolume(0.3f);

	SetMass(1.f);
	SetFriction(1900.f);
	SetMaxVelocity(2000.f);

	m_eTableState = TABLE_STATE::IDLE;
	
	Vec2 vPos = { GetPos().fX, GetPos().fY - 13.f };
	Vec2 vScale = { GetScale().fX + 50.f, GetScale().fY + 80.f };

	SetColOffset(vPos, vScale);

	SetHP(100);
	m_fDamage = 10.f;

	__super::Init();

	GetCollider()->SetOffsetPos(Vec2(0.f, -20.f));

	CreateAnimation();
}

void CTable::Update()
{
	CObject* pObject = CSceneManager::Get()->GetGroupObjects(OBJECT_TYPE::PLAYER)[0];

	if (m_eTableState == TABLE_STATE::FLIPPED)
		SetColOffset({ GetPos().fX, GetPos().fY }, GetScale() * 2.f);

	CPlayer* pPlayer = dynamic_cast<CPlayer*>(pObject);

	if(m_eTableState == TABLE_STATE::IDLE || m_eTableState == TABLE_STATE::FLIPPED)
	{
		if (isOffsetCollision(pObject))
		{
			pPlayer->SetCurrInteract(this);

			if (m_eTableState == TABLE_STATE::FLIPPED)
				return;

			float fWidth = fabsf(GetColOffset().vPos.fX - pObject->GetPos().fX);
			float fHeight = fabsf(GetColOffset().vPos.fY - pObject->GetPos().fY);

			float fRadiusX = (GetColOffset().vScale.fX + pObject->GetScale().fX) * 0.5f;
			float fRadiusY = (GetColOffset().vScale.fY + pObject->GetScale().fY) * 0.5f;

			fWidth = fRadiusX - fWidth;
			fHeight = fRadiusY - fHeight;

			if (fWidth > fHeight)
			{
				if (GetColOffset().vPos.fY < pObject->GetPos().fY)
					SetTableDir(TABLE_DIR::U);
				else
					SetTableDir(TABLE_DIR::D);
			}
			else
			{
				if (GetColOffset().vPos.fX < pObject->GetPos().fX)
					SetTableDir(TABLE_DIR::R);
				else
					SetTableDir(TABLE_DIR::L);
			}
		}
		else
		{
			if(pPlayer->GetCurrInteract() == this)
				pPlayer->SetCurrInteract(nullptr);
			m_eTableDir = TABLE_DIR::END;
		}
	}
}

void CTable::LateUpdate()
{
	__super::LateUpdate();

	if (m_eTableState == TABLE_STATE::FLIP)
	{
		if (GetAnimator()->GetCurrAnim()->GetFinish())
			m_eTableState = TABLE_STATE::FLIPPED;

		Vec2 vCollider{};
		Vec2 vOffset{};

		switch (m_eTableDir)
		{
		case TABLE_DIR::D :
			vCollider = { 100.f, 50.f };
			vOffset = { 0.f, 10.f };
			break;
		case TABLE_DIR::U :
			vCollider = { 100.f, 50.f };
			vOffset = { 0.f, -10.f };
			break;
		case TABLE_DIR::R :
			vCollider = { 50.f, 100.f };
			break;
		case TABLE_DIR::L :
			vCollider = { 50.f, 100.f };
			break;
		}

		SetScale(vCollider);
		GetCollider()->SetScale(GetScale());
		GetCollider()->SetOffsetPos(vOffset);
	}

	if (GetPhysics()->GetSpeed() == 0.f)
		m_bFly = false;

	if (GetHP() <= 0)
		if (m_eTableState == TABLE_STATE::FLIPPED ||
			m_eTableState == TABLE_STATE::IDLE)
		{
			m_eTableState = TABLE_STATE::BREAK;

			CSoundManager::Get()->PlaySound(L"Table_Break.wav", CHANNELID::SOUND_EFFECT, GetVolume());

			CreateEffect();
		}

	if (m_eTableState == TABLE_STATE::BREAK)
		if (GetAnimator()->GetCurrAnim()->GetFinish())
		{
			m_eTableState = TABLE_STATE::DEAD;
			CSceneManager::Get()->ChangeRender(this, GetObjectType(), RENDER_TYPE::RENDER_TILE_PREV);
		}

	Motion();
}

void CTable::Render(HDC _hDC)
{
	__super::Render(_hDC);
}

void CTable::Release()
{
}

void CTable::Motion()
{
	if (m_eTableState == TABLE_STATE::IDLE)
	{
		if (m_eTableDir == TABLE_DIR::D)
			GetAnimator()->PlayAnimation(L"Table_Alt_D", true);
		else if (m_eTableDir == TABLE_DIR::U)
			GetAnimator()->PlayAnimation(L"Table_Alt_U", true);
		else if (m_eTableDir == TABLE_DIR::R)
			GetAnimator()->PlayAnimation(L"Table_Alt_R", true);
		else if (m_eTableDir == TABLE_DIR::L)
			GetAnimator()->PlayAnimation(L"Table_Alt_L", true);
		else
			GetAnimator()->PlayAnimation(L"Table", true);
	}
	else if (m_eTableState == TABLE_STATE::FLIP)
	{
		if (m_eTableDir == TABLE_DIR::D)
			GetAnimator()->PlayAnimation(L"Table_Flip_D", false);
		else if(m_eTableDir == TABLE_DIR::U)
			GetAnimator()->PlayAnimation(L"Table_Flip_U", false);
		else if (m_eTableDir == TABLE_DIR::R)
			GetAnimator()->PlayAnimation(L"Table_Flip_R", false);
		else if (m_eTableDir == TABLE_DIR::L)
			GetAnimator()->PlayAnimation(L"Table_Flip_L", false);
	}
	else if (m_eTableState == TABLE_STATE::FLIPPED)
	{
		if (m_eTableDir == TABLE_DIR::D)
			GetAnimator()->PlayAnimation(L"Table_D", true);
		else if (m_eTableDir == TABLE_DIR::U)
			GetAnimator()->PlayAnimation(L"Table_U", true);
		else if (m_eTableDir == TABLE_DIR::R)
			GetAnimator()->PlayAnimation(L"Table_R", true);
		else if (m_eTableDir == TABLE_DIR::L)
			GetAnimator()->PlayAnimation(L"Table_L", true);
	}
	else if (m_eTableState == TABLE_STATE::BREAK)
		GetAnimator()->PlayAnimation(L"Table_Break", false);
	else if(m_eTableState == TABLE_STATE::DEAD)
		GetAnimator()->PlayAnimation(L"Table_Broken", true);
}

void CTable::CreateAnimation()
{
	GetAnimator()->CreateAnimation(L"Table", CResourceManager::Get()->FindTexture(L"Table"), Vec2(0, 0), Vec2(144, 144), Vec2(144, 0), .1f, 1);
	GetAnimator()->CreateAnimation(L"Table_Alt_D", CResourceManager::Get()->FindTexture(L"Table_Alt_D"), Vec2(0, 0), Vec2(144, 144), Vec2(144, 0), .1f, 1);
	GetAnimator()->CreateAnimation(L"Table_Alt_U", CResourceManager::Get()->FindTexture(L"Table_Alt_U"), Vec2(0, 0), Vec2(144, 144), Vec2(144, 0), .1f, 1);
	GetAnimator()->CreateAnimation(L"Table_Alt_R", CResourceManager::Get()->FindTexture(L"Table_Alt_R"), Vec2(0, 0), Vec2(144, 144), Vec2(144, 0), .1f, 1);
	GetAnimator()->CreateAnimation(L"Table_Alt_L", CResourceManager::Get()->FindTexture(L"Table_Alt_L"), Vec2(0, 0), Vec2(144, 144), Vec2(144, 0), .1f, 1);
	GetAnimator()->CreateAnimation(L"Table_Flip_D", CResourceManager::Get()->FindTexture(L"Table_Flip_D"), Vec2(0, 0), Vec2(144, 144), Vec2(144, 0), .1f, 4);
	GetAnimator()->CreateAnimation(L"Table_Flip_U", CResourceManager::Get()->FindTexture(L"Table_Flip_U"), Vec2(0, 0), Vec2(144, 144), Vec2(144, 0), .1f, 4);
	GetAnimator()->CreateAnimation(L"Table_Flip_R", CResourceManager::Get()->FindTexture(L"Table_Flip_R"), Vec2(0, 0), Vec2(144, 144), Vec2(144, 0), .1f, 4);
	GetAnimator()->CreateAnimation(L"Table_Flip_L", CResourceManager::Get()->FindTexture(L"Table_Flip_L"), Vec2(0, 0), Vec2(144, 144), Vec2(144, 0), .1f, 4);
	GetAnimator()->CreateAnimation(L"Table_D", CResourceManager::Get()->FindTexture(L"Table_D"), Vec2(0, 0), Vec2(144, 144), Vec2(144, 0), .1f, 1);
	GetAnimator()->CreateAnimation(L"Table_U", CResourceManager::Get()->FindTexture(L"Table_U"), Vec2(0, 0), Vec2(144, 144), Vec2(144, 0), .1f, 1);
	GetAnimator()->CreateAnimation(L"Table_R", CResourceManager::Get()->FindTexture(L"Table_R"), Vec2(0, 0), Vec2(144, 144), Vec2(144, 0), .1f, 1);
	GetAnimator()->CreateAnimation(L"Table_L", CResourceManager::Get()->FindTexture(L"Table_L"), Vec2(0, 0), Vec2(144, 144), Vec2(144, 0), .1f, 1);
	GetAnimator()->CreateAnimation(L"Table_Break", CResourceManager::Get()->FindTexture(L"Table_Break"), Vec2(0, 0), Vec2(144, 144), Vec2(144, 0), .1f, 3);
	GetAnimator()->CreateAnimation(L"Table_Broken", CResourceManager::Get()->FindTexture(L"Table_Broken"), Vec2(0, 0), Vec2(144, 144), Vec2(144, 0), .1f, 1);
}

void CTable::CreateEffect()
{
	CTableEffect* pTableEffect = new CTableEffect;

	pTableEffect->Init();
	pTableEffect->SetPos({ GetPos().fX, GetPos().fY + 10.f });
	CreateObjectEvent(pTableEffect, OBJECT_TYPE::EFFECT);
}

void CTable::OnCollision(CCollider& _pOther)
{
	CObject* pOwner = _pOther.GetOwner();

	if (pOwner->GetObjectType() == OBJECT_TYPE::WALL && m_eTableState == TABLE_STATE::DEAD)
	{
		float fWidth = fabsf(GetCollider()->GetFinalPos().fX - _pOther.GetFinalPos().fX);
		float fHeight = fabsf(GetCollider()->GetFinalPos().fY - _pOther.GetFinalPos().fY);

		float fRadiusX = (GetCollider()->GetScale().fX + _pOther.GetScale().fX) * 0.5f;
		float fRadiusY = (GetCollider()->GetScale().fY + _pOther.GetScale().fY) * 0.5f;

		fWidth = fRadiusX - fWidth;
		fHeight = fRadiusY - fHeight;

		if (fWidth > fHeight)
		{
			if (GetCollider()->GetFinalPos().fY < _pOther.GetFinalPos().fY)
				SetPos(Vec2(GetPos().fX, GetPos().fY - fHeight - 1.f));
			else
				SetPos(Vec2(GetPos().fX, GetPos().fY + fHeight + 1.f));
		}
		else
		{
			if (GetCollider()->GetFinalPos().fX < _pOther.GetFinalPos().fX)
				SetPos(Vec2(GetPos().fX - fWidth - 1.f, GetPos().fY));
			else
				SetPos(Vec2(GetPos().fX + fWidth + 1.f, GetPos().fY));
		}
	}

	if (pOwner->GetObjectType() == OBJECT_TYPE::PLAYER || pOwner->GetObjectType() == OBJECT_TYPE::ENEMY)
	{
		float fWidth = fabsf(GetCollider()->GetFinalPos().fX - _pOther.GetFinalPos().fX);
		float fHeight = fabsf(GetCollider()->GetFinalPos().fY - _pOther.GetFinalPos().fY);

		float fRadiusX = (GetCollider()->GetScale().fX + _pOther.GetScale().fX) * 0.5f;
		float fRadiusY = (GetCollider()->GetScale().fY + _pOther.GetScale().fY) * 0.5f;

		fWidth = fRadiusX - fWidth;
		fHeight = fRadiusY - fHeight;

		if (m_eTableState == TABLE_STATE::IDLE ||
			m_eTableState == TABLE_STATE::FLIP)
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
		else if (pOwner->GetObjectType() == OBJECT_TYPE::PLAYER && m_eTableState == TABLE_STATE::FLIPPED)
		{
			if (fWidth > fHeight)
			{
				if (GetCollider()->GetFinalPos().fY < _pOther.GetFinalPos().fY)
					SetPos(Vec2(GetPos().fX, GetPos().fY - fHeight - 1.f));
				else
					SetPos(Vec2(GetPos().fX, GetPos().fY + fHeight + 1.f));
			}
			else
			{
				if (GetCollider()->GetFinalPos().fX < _pOther.GetFinalPos().fX)
					SetPos(Vec2(GetPos().fX - fWidth - 1.f, GetPos().fY));
				else
					SetPos(Vec2(GetPos().fX + fWidth + 1.f, GetPos().fY));
			}
		}
		else if (m_eTableState == TABLE_STATE::BREAK || m_eTableState == TABLE_STATE::DEAD)
			return;

		pOwner->GetPhysics()->SetVelocity(pOwner->GetPhysics()->GetVelocity() - pOwner->GetPhysics()->GetVelocity() * 1.f / 4.f);
	}
}

void CTable::OnCollisionEnter(CCollider& _pOther)
{
	CObject* pOwner = _pOther.GetOwner();

	if (pOwner->GetObjectType() == OBJECT_TYPE::WALL)
	{
		if (m_bFly)
		{
			GetPhysics()->SetVelocity(Vec2(0.f, 0.f));
			m_eTableState = TABLE_STATE::BREAK;

			CSoundManager::Get()->PlaySound(L"Table_Break.wav", CHANNELID::SOUND_EFFECT, GetVolume());

			CreateEffect();
		}
	}

	if (pOwner->GetObjectType() == OBJECT_TYPE::ENEMY)
	{
		if (dynamic_cast<CEnemy*>(pOwner)->GetCharState() != CHAR_STATE::DEAD && 
			dynamic_cast<CEnemy*>(pOwner)->GetCharState() != CHAR_STATE::DEATH)
		{
			if (m_bFly)
			{
				CEnemy* pEnemy = dynamic_cast<CEnemy*>(pOwner);

				pEnemy->SetCurrHP(pEnemy->GetCurrHP() - (int)m_fDamage);
				pEnemy->GetPhysics()->AddVelocity(GetPhysics()->GetVelocity().Normalize() * 1000.f);
				pEnemy->SetCharState(CHAR_STATE::HIT);
				GetPhysics()->SetVelocity(Vec2(0.f, 0.f));
				m_eTableState = TABLE_STATE::BREAK;

				CSoundManager::Get()->PlaySound(L"Table_Break.wav", CHANNELID::SOUND_EFFECT, GetVolume());

				CreateEffect();
			}
		}
	}

	if (pOwner->GetObjectType() == OBJECT_TYPE::INTERACT)
	{
		if (m_bFly)
		{
			CInteract* pInteract = dynamic_cast<CInteract*>(pOwner);

			pInteract->SetHP(0);
			GetPhysics()->SetVelocity(Vec2(0.f, 0.f));
			m_eTableState = TABLE_STATE::BREAK;

			CSoundManager::Get()->PlaySound(L"Table_Break.wav", CHANNELID::SOUND_EFFECT, GetVolume());

			CreateEffect();
		}
	}
}

void CTable::OnCollisionExit(CCollider& _pOther)
{
}