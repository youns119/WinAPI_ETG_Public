#include "pch.h"
#include "Player.h"

#include "Keyboard.h"
#include "ResourceManager.h"
#include "Camera.h"
#include "Mouse.h"
#include "Main.h"
#include "SoundManager.h"
#include "SceneManager.h"

#include "Func.h"
#include "Texture.h"
#include "Collider.h"
#include "Animator.h"
#include "Animation.h"
#include "Physics.h"
#include "Enemy.h"
#include "Item_Gun.h"
#include "Gun.h"
#include "Revolver.h"
#include "ShotGun.h"
#include "MachineGun.h"
#include "ReflectGun.h"
#include "HomingGun.h"
#include "Interact.h"
#include "Table.h"
#include "Chest.h"
#include "BulletKing.h"
#include "FearEffect.h"
#include "Medikit.h"

CPlayer::CPlayer()
	: m_bDodge(false)
	, m_bInvincible(false)
	, m_bReload(false)
	, m_bHit(false)
	, m_bShow(true)
	, m_bFlicker(false)
	, m_bFear(false)
	, m_fDodgeVelocity(0.f)
	, m_fHitTime(0.f)
	, m_fFlickerTime(0.f)
	, m_fWalkTime(0.f)
	, m_fFearTime(0.f)
	, m_iHitTick(0)
	, m_iFlickerTick(0)
	, m_iWalkTick(0)
	, m_iFearTick(0)
	, m_vCursorDir{}
	, m_iFearCount(0)
	, m_iKeyCount(0)
	, m_iCoinCount(0)
	, m_iWalkCount(0)
	, m_pCurrItem(nullptr)
	, m_iCurrGunIndex(0)
	, m_pCurrInteract(nullptr)
{
	SetObjectType(OBJECT_TYPE::PLAYER);
	SetRenderType(RENDER_TYPE::RENDER_OBJECT);

	m_vecGuns.assign((UINT)GUN_TYPE::END, nullptr);
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Init()
{
	SetName(L"Player");
	SetScale({ 48.f, 48.f });
	SetRenderScale(GetScale());
	SetVolume(0.2f);

	SetMaxHP(6);
	SetCurrHP(GetMaxHP());
	SetMass(1.f);
	SetFriction(700.f);
	SetMaxVelocity(250.f);

	m_fDodgeVelocity = 700.f;
	m_fHitTime = 1.5f;
	m_fFlickerTime = m_fHitTime / 10.f;
	m_fWalkTime = .35f;
	m_fFearTime = 1.f;

	SetCharState(CHAR_STATE::IDLE);
	SetCharDir(CHAR_DIR::D);

	m_iFearCount = 2;
	m_iKeyCount = 1;

	CreateCollider();
	GetCollider()->SetScale(GetScale());
	GetCollider()->SetShow(false);

	CreateAnimator();
	CreateAnimation();

	CreatePhysics();
	GetPhysics()->SetMass(GetMass());
	GetPhysics()->SetFriction(GetFriction());
	GetPhysics()->SetMaxVelocity(GetMaxVelocity());
}

void CPlayer::Update()
{
	m_vCursorDir = CMouse::Get()->GetPos() - GetPos();

	Input();
	PointDir();
}

void CPlayer::LateUpdate()
{
	__super::LateUpdate();

	if (m_bHit)
	{
		if (m_bFlicker && m_fFlickerTime * 1000.f < GetTickCount64() - m_iFlickerTick)
		{
			m_iFlickerTick = GetTickCount64();

			m_bInvincible = true;
			m_bShow = !m_bShow;
		}

		if (m_fHitTime * 1000.f < GetTickCount64() - m_iHitTick)
		{
			m_bInvincible = false;
			m_bFlicker = false;
			m_bHit = false;
			m_bShow = true;
		}
	}

	if (m_bDodge)
	{
		if (GetAnimator()->GetCurrAnim()->GetFinish())
		{
			m_bDodge = false;
			m_bInvincible = false;

			GetPhysics()->SetMaxVelocity(GetMaxVelocity());

			SetCharState(CHAR_STATE::IDLE);
		}
		else
			m_bInvincible = true;
	}

	if (m_bFear)
	{
		if (m_fFearTime * 1000.f < GetTickCount64() - m_iFearTick)
		{
			m_bFear = false;

			return;
		}

		vector<CObject*>& vProjectile = CSceneManager::Get()->GetGroupObjects(OBJECT_TYPE::PROJECTILE_ENEMY);

		for (int i = 0; i < vProjectile.size(); i++)
			DeleteObjectEvent(vProjectile[i]);
	}

	Motion();
}

void CPlayer::Render(HDC _hDC)
{
	//TCHAR szInvincible[100] = L"";
	//swprintf_s(szInvincible, L"Invincible : %d", m_bInvincible);
	//TextOut(_hDC, (int)100.f, (int)250.f, szInvincible, lstrlen(szInvincible));

	//TCHAR szShow[100] = L"";
	//swprintf_s(szShow, L"Show : %d", m_bShow);
	//TextOut(_hDC, (int)100.f, (int)300.f, szShow, lstrlen(szShow));

	//TCHAR szGun[100] = L"";
	//swprintf_s(szGun, L"CurrGun : %d", m_iCurrGunIndex);
	//TextOut(_hDC, (int)100.f, (int)100.f, szGun, lstrlen(szGun));

	if (!m_bShow) return;

	__super::Render(_hDC);

	//TCHAR szState[32] = L"";
	//swprintf_s(szState, L"State : %d", (UINT)GetCharState());
	//TextOut(_hDC, (int)100.f, (int)150.f, szState, lstrlen(szState));

	//TCHAR szVelocity[100] = L"";
	//swprintf_s(szVelocity, L"XVel: %.2f YVel : %.2f Speed : %.2f", 
	//	GetPhysics()->GetVelocity().fX, GetPhysics()->GetVelocity().fY, GetPhysics()->GetSpeed());
	//TextOut(_hDC, (int)100.f, (int)200.f, szVelocity, lstrlen(szVelocity));

	//TCHAR szCamPos[100] = L"";
	//swprintf_s(szCamPos, L"XCamPos : %.2f YCamPos : %.2f", CCamera::Get()->GetLookPos().fX, CCamera::Get()->GetLookPos().fY);
	//TextOut(_hDC, (int)100.f, (int)(CMain::Get()->GetResolution().y - 100.f), szCamPos, lstrlen(szCamPos));

	//TCHAR szDegree[100] = L"";
	//swprintf_s(szDegree, L"Radian : %.2f", GetRadian() * 180 / PI);
	//TextOut(_hDC, (int)100.f, (int)250.f, szDegree, lstrlen(szDegree));

	//TCHAR szRadian[100] = L"";
	//swprintf_s(szRadian, L"Radian : %.2f", GetRadian());
	//TextOut(_hDC, (int)100.f, (int)250.f, szRadian, lstrlen(szRadian));

	//if (GetCurrInteract())
	//{
	//	TCHAR szInteract[100] = L"";
	//	swprintf_s(szInteract, L"Interact : %d", GetCurrInteract()->GetInteractType());
	//	TextOut(_hDC, (int)100.f, (int)250.f, szInteract, lstrlen(szInteract));
	//}
}

void CPlayer::Release()
{
}

void CPlayer::Input()
{
	if (!m_bDodge)
	{
		if (CKeyboard::Get()->KeyPress('W'))
			GetPhysics()->AddForce({ 0.f, -1200.f });
		if (CKeyboard::Get()->KeyPress('S'))
			GetPhysics()->AddForce({ 0.f, 1200.f });
		if (CKeyboard::Get()->KeyPress('D'))
			GetPhysics()->AddForce({ 1200.f, 0.f });
		if (CKeyboard::Get()->KeyPress('A'))
			GetPhysics()->AddForce({ -1200.f, 0.f });

		if (CKeyboard::Get()->KeyDown(VK_RBUTTON))
			if (!GetPhysics()->GetVelocity().IsZero())
			{
				m_bDodge = true;

				m_bInvincible = true;

				Vec2 vCurrDir = GetPhysics()->GetVelocity().Normalize();
				DodgeDir(vCurrDir);
				GetPhysics()->SetMaxVelocity(m_fDodgeVelocity);
				GetPhysics()->AddVelocity(vCurrDir * 1000.f);

				CSoundManager::Get()->PlaySound(L"Dodge.wav", CHANNELID::SOUND_PLAYER, GetVolume());

				SetCharState(CHAR_STATE::DODGE);
			}

		if (GetCurrGun() && GetCurrGun()->GetTriggerType() == TRIGGER_TYPE::SEMIAUTO)
		{
			if (CKeyboard::Get()->KeyDown(VK_LBUTTON))
				if (GetCurrGun() && !m_bReload)
				{
					if (GetCurrGun()->GetCurrMag() == 0)
						CSoundManager::Get()->PlaySound(L"Gun_Empty.wav", CHANNELID::SOUND_EFFECT, GetVolume());

					if (DelayCheck((int)(GetCurrGun()->GetDelay() * 1000.f)))
						if (GetCurrGun()->GetCurrMag() > 0)
							CreateProjectile(GetCurrGun());
				}
		}
		else if (GetCurrGun() && GetCurrGun()->GetTriggerType() == TRIGGER_TYPE::AUTO)
		{
			if (CKeyboard::Get()->KeyPress(VK_LBUTTON))
				if (GetCurrGun() && !m_bReload)
				{
					if (DelayCheck((int)(GetCurrGun()->GetDelay() * 1000.f)))
						if (GetCurrGun()->GetCurrMag() > 0)
							CreateProjectile(GetCurrGun());
				}

			if (CKeyboard::Get()->KeyDown(VK_LBUTTON))
				if (GetCurrGun() && !m_bReload)
					if (GetCurrGun()->GetCurrMag() == 0)
						CSoundManager::Get()->PlaySound(L"Gun_Empty.wav", CHANNELID::SOUND_EFFECT, GetVolume());

		}

		if (CKeyboard::Get()->KeyDown('R'))
			if (GetCurrGun() &&
				GetCurrGun()->GetCurrMag() != GetCurrGun()->GetMag() &&
				!m_bReload)
				if (GetCurrGun()->GetCurrMax() != 0)
				{
					m_bReload = true;

					switch (GetCurrGun()->GetGunType())
					{
					case GUN_TYPE::REVOLVER :
						CSoundManager::Get()->PlaySound(L"Revolver_Reload.wav", CHANNELID::SOUND_PLAYER, GetVolume());
						break;
					case GUN_TYPE::SHOTGUN:
						CSoundManager::Get()->PlaySound(L"ShotGun_Reload.wav", CHANNELID::SOUND_PLAYER, GetVolume());
						break;
					case GUN_TYPE::MACHINEGUN:
						CSoundManager::Get()->PlaySound(L"MachineGun_Reload.wav", CHANNELID::SOUND_PLAYER, GetVolume());
						break;
					case GUN_TYPE::REFLECTGUN:
						CSoundManager::Get()->PlaySound(L"ReflectGun_Reload.wav", CHANNELID::SOUND_PLAYER, GetVolume());
						break;
					case GUN_TYPE::HOMINGGUN:
						CSoundManager::Get()->PlaySound(L"HomingGun_Reload.wav", CHANNELID::SOUND_PLAYER, GetVolume());
						break;
					}
				}
	}

	if (CKeyboard::Get()->KeyDown('1'))
	{
		int iCurrGunIndex = m_iCurrGunIndex;

		for (int i = 0; i < m_vecGuns.size(); i++)
		{
			iCurrGunIndex -= 1;
			CGun* pGun = GetCurrGun();

			if (iCurrGunIndex < 0)
				iCurrGunIndex = m_vecGuns.size() - 1;

			if (m_vecGuns[(UINT)iCurrGunIndex])
			{
				m_vecGuns[(UINT)m_iCurrGunIndex]->SetShow(false);
				m_iCurrGunIndex = iCurrGunIndex;
				SetCurrGun(m_vecGuns[(UINT)m_iCurrGunIndex]);
				GetCurrGun()->SetShow(true);

				if (pGun != GetCurrGun())
					CSoundManager::Get()->PlaySound(L"Gun_Switch.wav", CHANNELID::SOUND_EFFECT, GetVolume());

				break;
			}
		}
	}

	if (CKeyboard::Get()->KeyDown('2'))
	{
		int iCurrGunIndex = m_iCurrGunIndex;
		CGun* pGun = GetCurrGun();

		for (int i = 0; i < m_vecGuns.size(); i++)
		{
			iCurrGunIndex += 1;

			if (iCurrGunIndex == m_vecGuns.size())
				iCurrGunIndex = 0;

			if (m_vecGuns[(UINT)iCurrGunIndex])
			{
				m_vecGuns[(UINT)m_iCurrGunIndex]->SetShow(false);
				m_iCurrGunIndex = iCurrGunIndex;
				SetCurrGun(m_vecGuns[(UINT)m_iCurrGunIndex]);
				GetCurrGun()->SetShow(true);

				if(pGun != GetCurrGun())
					CSoundManager::Get()->PlaySound(L"Gun_Switch.wav", CHANNELID::SOUND_EFFECT, GetVolume());

				break;
			}
		}
	}

	if (CKeyboard::Get()->KeyDown('E'))
	{
		if (m_pCurrInteract)
		{
			if (m_pCurrInteract->GetInteractType() == INTERACT_TYPE::TABLE)
			{
				CTable* pTable = dynamic_cast<CTable*>(m_pCurrInteract);

				if (pTable->GetTableState() == TABLE_STATE::IDLE)
				{
					pTable->SetTableState(TABLE_STATE::FLIP);

					CSoundManager::Get()->PlaySound(L"Table_Flip.wav", CHANNELID::SOUND_EFFECT, pTable->GetVolume());

					m_pCurrInteract = nullptr;
				}
				else if (pTable->GetTableState() == TABLE_STATE::FLIPPED)
				{
					Vec2 vNorm = GetPhysics()->GetVelocity().Normalize();

					pTable->SetFly(true);
					pTable->GetPhysics()->SetVelocity(vNorm * 2500.f);
					pTable->GetCollider()->SetScale({ 100.f, 100.f });

					CSoundManager::Get()->PlaySound(L"Table_Fly.wav", CHANNELID::SOUND_EFFECT, pTable->GetVolume());
				}
			}
			else if (m_pCurrInteract->GetInteractType() == INTERACT_TYPE::CHEST)
			{
				CChest* pChest = dynamic_cast<CChest*>(m_pCurrInteract);

				if (pChest->GetChestState() == CHEST_STATE::IDLE)
				{
					if (m_iKeyCount > 0)
					{
						m_iKeyCount--;

						pChest->SetChestState(CHEST_STATE::OPEN);
						pChest->SetContact(false);

						CSoundManager::Get()->PlaySound(L"Chest_Open.wav", CHANNELID::SOUND_EFFECT, pChest->GetVolume());
					}
					else
						CSoundManager::Get()->PlaySound(L"Chest_Open_Unable.wav", CHANNELID::SOUND_EFFECT, pChest->GetVolume());

					m_pCurrInteract = nullptr;
				}
			}
		}
	}

	if (CKeyboard::Get()->KeyDown('Q'))
	{
		if (m_pCurrItem)
		{
			ITEM_TYPE eItemType = m_pCurrItem->GetItemType();
			CItem* pItem = m_pCurrItem;

			switch (eItemType)
			{
			case ITEM_TYPE::MEDIKIT :
			{
				CMedikit* pMedikit = dynamic_cast<CMedikit*>(pItem);

				if (!pMedikit->GetUsed()) pMedikit->Use();

				break;
			}
			}
		}
	}

	if (CKeyboard::Get()->KeyDown(VK_SPACE))
	{
		if (m_iFearCount > 0)
		{
			m_bFear = true;

			CObject* pFearEffect = new CFearEffect;
			pFearEffect->SetPos(GetPos());
			pFearEffect->Init();

			CCamera::Get()->Shake(2.f, 6.f);

			m_iFearCount--;
			m_iFearTick = GetTickCount64();

			CreateObjectEvent(pFearEffect, OBJECT_TYPE::EFFECT);
		}
	}

	if (CKeyboard::Get()->KeyUp('Q'))
	{
		//CCamera::Get()->FadeOut(2.f);
		//CCamera::Get()->FadeIn(2.f);
	}

	if (CKeyboard::Get()->KeyUp('3'))
	{
		if (m_iFearCount == 0) return;
		m_iFearCount--;
	}
	if (CKeyboard::Get()->KeyUp('4'))
	{
		m_iFearCount++;
	}

	if (CKeyboard::Get()->KeyUp('5'))
	{
		if (m_iKeyCount == 0) return;
		m_iKeyCount--;
	}
	if (CKeyboard::Get()->KeyUp('6'))
	{
		m_iKeyCount++;
	}

	if (CKeyboard::Get()->KeyUp('7'))
	{
		if (m_iCoinCount == 0) return;
		m_iCoinCount--;
	}
	if (CKeyboard::Get()->KeyUp('8'))
	{
		m_iCoinCount += 10;
	}
}

void CPlayer::PointDir()
{
	SetRadian(m_vCursorDir.DirToRadian());

	float fDegree = GetRadian() * 180 / PI;

	if (!m_bDodge)
	{
		if (fDegree > 60.f && fDegree <= 120.f)
			SetCharDir(CHAR_DIR::D);
		else if (fDegree > 0.f && fDegree <= 60.f)
			SetCharDir(CHAR_DIR::DR);
		else if (fDegree > 120.f && fDegree <= 180.f)
			SetCharDir(CHAR_DIR::DL);
		else if (fDegree > -120.f && fDegree <= -60.f)
			SetCharDir(CHAR_DIR::U);
		else if (fDegree > -60.f && fDegree <= 0.f)
			SetCharDir(CHAR_DIR::UR);
		else if (fDegree > -180.f && fDegree <= 120.f)
			SetCharDir(CHAR_DIR::UL);
	}
}

void CPlayer::DodgeDir(Vec2 _vDir)
{
	float fDegree = _vDir.DirToRadian() * 180 / PI;

	if (m_bDodge)
	{
		if (fDegree > 60.f && fDegree <= 120.f)
			SetCharDir(CHAR_DIR::D);
		else if (fDegree > 0.f && fDegree <= 60.f)
			SetCharDir(CHAR_DIR::DR);
		else if (fDegree > 120.f && fDegree <= 180.f)
			SetCharDir(CHAR_DIR::DL);
		else if (fDegree > -120.f && fDegree <= -60.f)
			SetCharDir(CHAR_DIR::U);
		else if (fDegree > -60.f && fDegree <= 0.f)
			SetCharDir(CHAR_DIR::UR);
		else if (fDegree > -180.f && fDegree <= 120.f)
			SetCharDir(CHAR_DIR::UL);
	}
}

bool CPlayer::WalkTickCheck(float _fTime)
{
	if (_fTime < GetTickCount64() - m_iWalkTick)
	{
		m_iWalkTick = GetTickCount64();

		return true;
	}

	return false;
}

void CPlayer::Motion()
{
	if (GetPhysics()->GetVelocity().IsZero() && !m_bDodge)
		SetCharState(CHAR_STATE::IDLE);
	else if (!m_bDodge)
	{
		SetCharState(CHAR_STATE::WALK);

		if (WalkTickCheck(m_fWalkTime * 1000.f))
		{
			if(m_iWalkCount == 0)
				CSoundManager::Get()->PlaySound(L"Walk1.wav", CHANNELID::SOUND_PLAYER, GetVolume());
			else if(m_iWalkCount == 1)
				CSoundManager::Get()->PlaySound(L"Walk2.wav", CHANNELID::SOUND_PLAYER, GetVolume());
			else if (m_iWalkCount == 2)
				CSoundManager::Get()->PlaySound(L"Walk3.wav", CHANNELID::SOUND_PLAYER, GetVolume());

			m_iWalkCount++;

			if (m_iWalkCount == 3)
				m_iWalkCount = 0;
		}
	}

	if (GetCharState() == CHAR_STATE::IDLE)
	{
		if(GetCharDir() == CHAR_DIR::D)
			GetAnimator()->PlayAnimation(L"Player_Idle_D", true);
		else if (GetCharDir() == CHAR_DIR::U)
			GetAnimator()->PlayAnimation(L"Player_Idle_U", true);
		else if (GetCharDir() == CHAR_DIR::DR)
			GetAnimator()->PlayAnimation(L"Player_Idle_DR", true);
		else if (GetCharDir() == CHAR_DIR::DL)
			GetAnimator()->PlayAnimation(L"Player_Idle_DL", true);
		else if (GetCharDir() == CHAR_DIR::UR)
			GetAnimator()->PlayAnimation(L"Player_Idle_UR", true);
		else if (GetCharDir() == CHAR_DIR::UL)
			GetAnimator()->PlayAnimation(L"Player_Idle_UL", true);
	}
	else if (GetCharState() == CHAR_STATE::WALK)
	{
		if (GetCharDir() == CHAR_DIR::D)
			GetAnimator()->PlayAnimation(L"Player_Walk_D", true);
		else if (GetCharDir() == CHAR_DIR::U)
			GetAnimator()->PlayAnimation(L"Player_Walk_U", true);
		else if (GetCharDir() == CHAR_DIR::DR)
			GetAnimator()->PlayAnimation(L"Player_Walk_DR", true);
		else if (GetCharDir() == CHAR_DIR::DL)
			GetAnimator()->PlayAnimation(L"Player_Walk_DL", true);
		else if (GetCharDir() == CHAR_DIR::UR)
			GetAnimator()->PlayAnimation(L"Player_Walk_UR", true);
		else if (GetCharDir() == CHAR_DIR::UL)
			GetAnimator()->PlayAnimation(L"Player_Walk_UL", true);
	}
	else if (GetCharState() == CHAR_STATE::DODGE)
	{
		if (GetCharDir() == CHAR_DIR::D)
			GetAnimator()->PlayAnimation(L"Player_Dodge_D", false);
		else if (GetCharDir() == CHAR_DIR::U)
			GetAnimator()->PlayAnimation(L"Player_Dodge_U", false);
		else if (GetCharDir() == CHAR_DIR::DR)
			GetAnimator()->PlayAnimation(L"Player_Dodge_DR", false);
		else if (GetCharDir() == CHAR_DIR::DL)
			GetAnimator()->PlayAnimation(L"Player_Dodge_DL", false);
		else if (GetCharDir() == CHAR_DIR::UR)
			GetAnimator()->PlayAnimation(L"Player_Dodge_UR", false);
		else if (GetCharDir() == CHAR_DIR::UL)
			GetAnimator()->PlayAnimation(L"Player_Dodge_UL", false);
	}
}

void CPlayer::CreateAnimation()
{
	GetAnimator()->CreateAnimation(L"Player_Idle_D", CResourceManager::Get()->FindTexture(L"Player_Idle_D"), Vec2(0, 0), Vec2(80, 80), Vec2(80, 0), .15f, 3);
	GetAnimator()->CreateAnimation(L"Player_Idle_DR", CResourceManager::Get()->FindTexture(L"Player_Idle_DR"), Vec2(0, 0), Vec2(80, 80), Vec2(80, 0), .15f, 3);
	GetAnimator()->CreateAnimation(L"Player_Idle_DL", CResourceManager::Get()->FindTexture(L"Player_Idle_DL"), Vec2(0, 0), Vec2(80, 80), Vec2(80, 0), .15f, 3);
	GetAnimator()->CreateAnimation(L"Player_Idle_U", CResourceManager::Get()->FindTexture(L"Player_Idle_U"), Vec2(0, 0), Vec2(80, 80), Vec2(80, 0), .15f, 3);
	GetAnimator()->CreateAnimation(L"Player_Idle_UR", CResourceManager::Get()->FindTexture(L"Player_Idle_UR"), Vec2(0, 0), Vec2(80, 80), Vec2(80, 0), .15f, 3);
	GetAnimator()->CreateAnimation(L"Player_Idle_UL", CResourceManager::Get()->FindTexture(L"Player_Idle_UL"), Vec2(0, 0), Vec2(80, 80), Vec2(80, 0), .15f, 3);
	GetAnimator()->CreateAnimation(L"Player_Walk_D", CResourceManager::Get()->FindTexture(L"Player_Walk_D"), Vec2(0, 0), Vec2(80, 80), Vec2(80, 0), .1f, 6);
	GetAnimator()->CreateAnimation(L"Player_Walk_DR", CResourceManager::Get()->FindTexture(L"Player_Walk_DR"), Vec2(0, 0), Vec2(80, 80), Vec2(80, 0), .1f, 6);
	GetAnimator()->CreateAnimation(L"Player_Walk_DL", CResourceManager::Get()->FindTexture(L"Player_Walk_DL"), Vec2(0, 0), Vec2(80, 80), Vec2(80, 0), .1f, 6);
	GetAnimator()->CreateAnimation(L"Player_Walk_U", CResourceManager::Get()->FindTexture(L"Player_Walk_U"), Vec2(0, 0), Vec2(80, 80), Vec2(80, 0), .1f, 6);
	GetAnimator()->CreateAnimation(L"Player_Walk_UR", CResourceManager::Get()->FindTexture(L"Player_Walk_UR"), Vec2(0, 0), Vec2(80, 80), Vec2(80, 0), .1f, 6);
	GetAnimator()->CreateAnimation(L"Player_Walk_UL", CResourceManager::Get()->FindTexture(L"Player_Walk_UL"), Vec2(0, 0), Vec2(80, 80), Vec2(80, 0), .1f, 6);
	GetAnimator()->CreateAnimation(L"Player_Dodge_D", CResourceManager::Get()->FindTexture(L"Player_Dodge_D"), Vec2(0, 0), Vec2(80, 80), Vec2(80, 0), .06f, 9);
	GetAnimator()->CreateAnimation(L"Player_Dodge_DR", CResourceManager::Get()->FindTexture(L"Player_Dodge_DR"), Vec2(0, 0), Vec2(80, 80), Vec2(80, 0), .06f, 9);
	GetAnimator()->CreateAnimation(L"Player_Dodge_DL", CResourceManager::Get()->FindTexture(L"Player_Dodge_DL"), Vec2(0, 0), Vec2(80, 80), Vec2(80, 0), .06f, 9);
	GetAnimator()->CreateAnimation(L"Player_Dodge_U", CResourceManager::Get()->FindTexture(L"Player_Dodge_U"), Vec2(0, 0), Vec2(80, 80), Vec2(80, 0), .06f, 9);
	GetAnimator()->CreateAnimation(L"Player_Dodge_UR", CResourceManager::Get()->FindTexture(L"Player_Dodge_UR"), Vec2(0, 0), Vec2(80, 80), Vec2(80, 0), .06f, 9);
	GetAnimator()->CreateAnimation(L"Player_Dodge_UL", CResourceManager::Get()->FindTexture(L"Player_Dodge_UL"), Vec2(0, 0), Vec2(80, 80), Vec2(80, 0), .06f, 9);
}

CPlayer* CPlayer::Clone()
{
	CPlayer* pPlayer = new CPlayer(*this);


	return new CPlayer(*this);
}

void CPlayer::OnCollision(CCollider& _pOther)
{
	CObject::OnCollision(_pOther);

	CObject* pOther = _pOther.GetOwner();

	if (pOther->GetObjectType() == OBJECT_TYPE::ITEM)
	{
		if (dynamic_cast<CItem*>(pOther)->GetItemType() == ITEM_TYPE::GUN)
		{
			CItem_Gun* pTempItemGun = dynamic_cast<CItem_Gun*>(pOther);

			if (CKeyboard::Get()->KeyDown('E'))
			{
				if (pTempItemGun->GetPrice() <= GetCoinCount())
				{
					GUN_TYPE eGunType = pTempItemGun->GetGunType();
					CGun* pGun = nullptr;

					switch (eGunType)
					{
					case GUN_TYPE::REVOLVER:
					{
						pGun = new CRevolver;
						break;
					}
					case GUN_TYPE::SHOTGUN:
					{
						pGun = new CShotGun;
						break;
					}
					case GUN_TYPE::MACHINEGUN:
					{
						pGun = new CMachineGun;
						break;
					}
					case GUN_TYPE::PIERCEGUN:
					{
						pGun = new CRevolver;
						break;
					}
					case GUN_TYPE::REFLECTGUN:
					{
						pGun = new CReflectGun;
						break;
					}
					case GUN_TYPE::HOMINGGUN:
					{
						pGun = new CHomingGun;
						break;
					}
					default:
						break;
					}

					pGun->Init();
					pGun->SetTarget(*this);

					if (GetCurrGun())
					{
						GetCurrGun()->SetShow(false);
						pGun->SetShow(true);
					}
					else pGun->SetShow(true);

					m_vecGuns[(UINT)eGunType] = pGun;

					m_iCurrGunIndex = (UINT)eGunType;
					SetCurrGun(m_vecGuns[m_iCurrGunIndex]);

					m_iCoinCount -= pTempItemGun->GetPrice();

					if (pTempItemGun->GetPrice() == 0)
						CSoundManager::Get()->PlaySound(L"Weapon_Pickup.wav", CHANNELID::SOUND_EFFECT, pTempItemGun->GetVolume());
					else
					{
						CSoundManager::Get()->PlaySound(L"Item_Purchase.wav", CHANNELID::SOUND_EFFECT, pTempItemGun->GetVolume());
						CSoundManager::Get()->PlaySound(L"Weapon_Pickup.wav", CHANNELID::SOUND_EFFECT, pTempItemGun->GetVolume());
					}

					CreateObjectEvent(pGun, OBJECT_TYPE::GUN);
					DeleteObjectEvent(pOther);
				}
				else
					CSoundManager::Get()->PlaySound(L"Item_Purchase_Unable.wav", CHANNELID::SOUND_EFFECT, pTempItemGun->GetVolume());
			}
		}
		else if (dynamic_cast<CItem*>(pOther)->GetItemType() == ITEM_TYPE::MEDIKIT)
		{
			if (CKeyboard::Get()->KeyDown('E'))
			{
				CItem* pMedikit = new CMedikit;
				pMedikit->Init();
				dynamic_cast<CMedikit*>(pMedikit)->SetTarget(this);

				m_pCurrItem = pMedikit;

				CSoundManager::Get()->PlaySound(L"Item_Pickup.wav", CHANNELID::SOUND_EFFECT, pOther->GetVolume());

				CreateObjectEvent(pMedikit, pMedikit->GetObjectType());
				DeleteObjectEvent(pOther);
			}
		}
	}

	if (pOther->GetObjectType() == OBJECT_TYPE::ENEMY)
	{
		if (GetCurrHP() != 0 && !m_bInvincible)
		{
			if (dynamic_cast<CEnemy*>(pOther)->GetEnemyType() == ENEMY_TYPE::BULLETKIN)
				if (dynamic_cast<CEnemy*>(pOther)->GetCharState() == CHAR_STATE::DEATH ||
					dynamic_cast<CEnemy*>(pOther)->GetCharState() == CHAR_STATE::DEAD)
					return;

			if (dynamic_cast<CEnemy*>(pOther)->GetEnemyType() == ENEMY_TYPE::BULLETKING)
				if(dynamic_cast<CBulletKing*>(pOther)->GetBossState() == BOSS_STATE::DIE ||
					dynamic_cast<CBulletKing*>(pOther)->GetBossState() == BOSS_STATE::DEAD)
				 return;

			//SetCurrHP(GetCurrHP() - 1);
			CCamera::Get()->Shake(3.f, 30.f);

			m_bInvincible = true;
			m_bHit = true;
			m_bFlicker = true;
			m_iHitTick = GetTickCount64();
			m_iFlickerTick = GetTickCount64();
			m_bShow = false;

			CSoundManager::Get()->PlaySound(L"Player_Hit.wav", CHANNELID::SOUND_PLAYER, GetVolume() * 0.5f);
		}
	}
}

void CPlayer::OnCollisionEnter(CCollider& _pOther)
{
	//CObject::OnCollisionEnter(_pOther);

	CObject* pOther = _pOther.GetOwner();

	if (pOther->GetObjectType() == OBJECT_TYPE::PROJECTILE_ENEMY ||
		pOther->GetObjectType() == OBJECT_TYPE::BLOW)
	{
		if (GetCurrHP() != 0 && !m_bInvincible)
		{
			SetCurrHP(GetCurrHP() - 1);
			CCamera::Get()->Shake(3.f, 30.f);

			m_bInvincible = true;
			m_bHit = true;
			m_bFlicker = true;
			m_iHitTick = GetTickCount64();
			m_iFlickerTick = GetTickCount64();
			m_bShow = false;

			CSoundManager::Get()->PlaySound(L"Player_Hit.wav", CHANNELID::SOUND_PLAYER, GetVolume() * 0.3f);

			DeleteObjectEvent(pOther);
		}
	}
}

void CPlayer::OnCollisionExit(CCollider& _pOther)
{
}