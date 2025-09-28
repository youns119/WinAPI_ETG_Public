#include "pch.h"
#include "Character.h"

#include "Camera.h"
#include "SoundManager.h"

#include "Func.h"
#include "Gun.h"
#include "Revolver.h"
#include "MachineGun.h"
#include "ShotGun.h"
#include "ReflectGun.h"
#include "HomingGun.h"
#include "Projectile_Revolver.h"
#include "Projectile_ShotGun.h"
#include "Projectile_MachineGun.h"
#include "Projectile_ReflectGun.h"
#include "Projectile_HomingGun.h"

CCharacter::CCharacter()
	: m_iMaxHP(0)
	, m_iCurrHP(0)
	, m_iTick(0)
	, m_eCharState(CHAR_STATE::END)
	, m_eCharDir(CHAR_DIR::END)
	, m_pCurrGun(nullptr)
{
}

CCharacter::~CCharacter()
{
	Release();
}

void CCharacter::Init()
{
}

void CCharacter::Update()
{
}

void CCharacter::LateUpdate()
{
	__super::LateUpdate();
}

void CCharacter::Render(HDC _hDC)
{
	__super::Render(_hDC);
}

void CCharacter::Release()
{
}

void CCharacter::CreateProjectile(CGun* _pGun)
{
	GUN_TYPE eGunType = _pGun->GetGunType();

	vector<CProjectile*> vProjectile;
	vProjectile.reserve(5);
	CProjectile* pProjectile = nullptr;

	switch (eGunType)
	{
	case GUN_TYPE::REVOLVER :
	{
		for (int i = 0; i < 1; i++)
			vProjectile.push_back(new CProjectile_Revolver(*m_pCurrGun));

		CCamera::Get()->Shake(1.f, 3.f);
		
		switch (dynamic_cast<CRevolver*>(_pGun)->GetSoundCount())
		{
		case 0:
			CSoundManager::Get()->PlaySound(L"Revolver_Shot1.wav", CHANNELID::SOUND_PROJECTILE, _pGun->GetVolume());
			break;
		case 1:
			CSoundManager::Get()->PlaySound(L"Revolver_Shot2.wav", CHANNELID::SOUND_PROJECTILE, _pGun->GetVolume());
			break;
		case 2:
			CSoundManager::Get()->PlaySound(L"Revolver_Shot3.wav", CHANNELID::SOUND_PROJECTILE, _pGun->GetVolume());
			break;
		}

		dynamic_cast<CRevolver*>(_pGun)->AddSoundCount();

		break;
	}
	case GUN_TYPE::SHOTGUN :
	{
		for (int i = 0; i < 10; i++)
			vProjectile.push_back(new CProjectile_ShotGun(*m_pCurrGun));

		CCamera::Get()->Shake(2.f, 6.f);
		
		switch (dynamic_cast<CShotGun*>(_pGun)->GetSoundCount())
		{
		case 0:
			CSoundManager::Get()->PlaySound(L"ShotGun_Shot1.wav", CHANNELID::SOUND_PROJECTILE, _pGun->GetVolume());
			break;
		case 1:
			CSoundManager::Get()->PlaySound(L"ShotGun_Shot2.wav", CHANNELID::SOUND_PROJECTILE, _pGun->GetVolume());
			break;
		case 2:
			CSoundManager::Get()->PlaySound(L"ShotGun_Shot3.wav", CHANNELID::SOUND_PROJECTILE, _pGun->GetVolume());
			break;
		}

		dynamic_cast<CShotGun*>(_pGun)->AddSoundCount();

		break;
	}
	case GUN_TYPE::MACHINEGUN:
	{
		for (int i = 0; i < 1; i++)
			vProjectile.push_back(new CProjectile_MachineGun(*m_pCurrGun));

		CCamera::Get()->Shake(1.f, 2.f);

		switch (dynamic_cast<CMachineGun*>(_pGun)->GetSoundCount())
		{
		case 0 :
			CSoundManager::Get()->PlaySound(L"MachineGun_Shot1.wav", CHANNELID::SOUND_PROJECTILE, _pGun->GetVolume());
			break;
		case 1:
			CSoundManager::Get()->PlaySound(L"MachineGun_Shot2.wav", CHANNELID::SOUND_PROJECTILE, _pGun->GetVolume());
			break;
		case 2:
			CSoundManager::Get()->PlaySound(L"MachineGun_Shot3.wav", CHANNELID::SOUND_PROJECTILE, _pGun->GetVolume());
			break;
		}

		dynamic_cast<CMachineGun*>(_pGun)->AddSoundCount();

		break;
	}
	case GUN_TYPE::PIERCEGUN :
		break;
	case GUN_TYPE::REFLECTGUN :
	{
		for (int i = 0; i < 1; i++)
			vProjectile.push_back(new CProjectile_ReflectGun(*m_pCurrGun));

		CCamera::Get()->Shake(1.f, 2.f);

		switch (dynamic_cast<CReflectGun*>(_pGun)->GetSoundCount())
		{
		case 0:
			CSoundManager::Get()->PlaySound(L"ReflectGun_Shot1.wav", CHANNELID::SOUND_PROJECTILE, _pGun->GetVolume());
			break;
		case 1:
			CSoundManager::Get()->PlaySound(L"ReflectGun_Shot2.wav", CHANNELID::SOUND_PROJECTILE, _pGun->GetVolume());
			break;
		}

		dynamic_cast<CMachineGun*>(_pGun)->AddSoundCount();

		break;
	}
	case GUN_TYPE::HOMINGGUN :
	{
		for (int i = 0; i < 1; i++)
			vProjectile.push_back(new CProjectile_HomingGun(*m_pCurrGun));

		CCamera::Get()->Shake(1.f, 2.f);

		CSoundManager::Get()->PlaySound(L"HomingGun_Shot.wav", CHANNELID::SOUND_PROJECTILE, _pGun->GetVolume());

		break;
	}
	default :
		break;
	}

	if (GetObjectType() == OBJECT_TYPE::PLAYER)
	{
		for (int i = 0; i < vProjectile.size(); i++)
		{
			vProjectile[i]->SetPos(m_pCurrGun->GetEnd());
			vProjectile[i]->SetRadian(GetRadian());
			vProjectile[i]->SetObjectType(OBJECT_TYPE::PROJECTILE_PLAYER);
			vProjectile[i]->Init();

			CreateObjectEvent(vProjectile[i], OBJECT_TYPE::PROJECTILE_PLAYER);
		}
	}
	else if (GetObjectType() == OBJECT_TYPE::ENEMY)
	{
		for (int i = 0; i < vProjectile.size(); i++)
		{
			vProjectile[i]->SetPos(m_pCurrGun->GetEnd());
			vProjectile[i]->SetRadian(GetRadian());
			vProjectile[i]->SetObjectType(OBJECT_TYPE::PROJECTILE_ENEMY);
			vProjectile[i]->Init();

			CreateObjectEvent(vProjectile[i], OBJECT_TYPE::PROJECTILE_ENEMY);
		}
	}

	m_pCurrGun->SetCurrMag(m_pCurrGun->GetCurrMag() - 1);

	if(m_pCurrGun->GetMagType() == MAG_TYPE::LIMITED)
		m_pCurrGun->SetCurrMax(m_pCurrGun->GetCurrMax() - 1);

	m_iTick = GetTickCount64();
}

bool CCharacter::DelayCheck(int _iDelay)
{
	if ((ULONGLONG)_iDelay < GetTickCount64() - m_iTick)
	{
		m_iTick = GetTickCount64();
		return true;
	}

	return false;
}