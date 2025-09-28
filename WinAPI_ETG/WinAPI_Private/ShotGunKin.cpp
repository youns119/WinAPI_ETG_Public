#include "pch.h"
#include "ShotGunKin.h"

#include "ResourceManager.h"
#include "Camera.h"

#include "Physics.h"
#include "Animator.h"
#include "Animation.h"
#include "Func.h"
#include "ShotGun.h"

CShotGunKin::CShotGunKin()
{
	SetEnemyType(ENEMY_TYPE::BULLETKIN);
}

CShotGunKin::~CShotGunKin()
{
	Release();
}

void CShotGunKin::Init()
{
	SetName(L"ShotGunKin");
	SetScale({ 50.f, 70.f });
	SetVolume(0.1f);

	SetMaxHP(20);
	SetCurrHP(GetMaxHP());

	SetRange(500.f);
	SetSpeed(100.f);

	CGun* pGun = new CShotGun();

	pGun->Init();
	pGun->SetTarget(*this);
	pGun->SetShow(true);
	pGun->SetDelay(pGun->GetDelay() * 7.f);

	SetCurrGun(pGun);

	CreateObjectEvent(pGun, OBJECT_TYPE::GUN);

	SetMass(1);
	SetFriction(150.f);
	SetMaxVelocity(200.f);

	__super::Init();

	CreateAnimation();
}

void CShotGunKin::Update()
{
	__super::Update();
}

void CShotGunKin::LateUpdate()
{
	__super::LateUpdate();
}

void CShotGunKin::Render(HDC _hDC)
{
	__super::Render(_hDC);
}

void CShotGunKin::Release()
{
}

void CShotGunKin::PointDir()
{
	float fDegree = GetRadian() * 180 / PI;

	if (fDegree > 0.f && fDegree <= 90.f)
		SetCharDir(CHAR_DIR::DR);
	else if (fDegree > 90.f && fDegree <= 180.f)
		SetCharDir(CHAR_DIR::DL);
	else if (fDegree > -90.f && fDegree <= 0.f)
		SetCharDir(CHAR_DIR::UR);
	else if (fDegree > -180.f && fDegree <= -90.f)
		SetCharDir(CHAR_DIR::UL);
}

void CShotGunKin::Attack()
{
	if (DelayCheck((int)(GetCurrGun()->GetDelay() * 1000.f)))
		CreateProjectile(GetCurrGun());
}

void CShotGunKin::Motion()
{
	if (GetCharState() == CHAR_STATE::IDLE)
	{
		if (GetCharDir() == CHAR_DIR::DR)
			GetAnimator()->PlayAnimation(L"ShotGunKin_Idle_D", true);
		else if (GetCharDir() == CHAR_DIR::DL)
			GetAnimator()->PlayAnimation(L"ShotGunKin_Idle_D", true);
		else if (GetCharDir() == CHAR_DIR::UR)
			GetAnimator()->PlayAnimation(L"ShotGunKin_Idle_U", true);
		else if (GetCharDir() == CHAR_DIR::UL)
			GetAnimator()->PlayAnimation(L"ShotGunKin_Idle_U", true);
	}
	else if (GetCharState() == CHAR_STATE::WALK)
	{
		if (GetCharDir() == CHAR_DIR::DR)
			GetAnimator()->PlayAnimation(L"ShotGunKin_Walk_DR", true);
		else if (GetCharDir() == CHAR_DIR::DL)
			GetAnimator()->PlayAnimation(L"ShotGunKin_Walk_DL", true);
		else if (GetCharDir() == CHAR_DIR::UR)
			GetAnimator()->PlayAnimation(L"ShotGunKin_Walk_U", true);
		else if (GetCharDir() == CHAR_DIR::UL)
			GetAnimator()->PlayAnimation(L"ShotGunKin_Walk_U", true);
	}
	else if (GetCharState() == CHAR_STATE::HIT)
	{
		if (GetCharDir() == CHAR_DIR::DR)
			GetAnimator()->PlayAnimation(L"ShotGunKin_Hit_R", false);
		else if (GetCharDir() == CHAR_DIR::DL)
			GetAnimator()->PlayAnimation(L"ShotGunKin_Hit_L", false);
		else if (GetCharDir() == CHAR_DIR::UR)
			GetAnimator()->PlayAnimation(L"ShotGunKin_Hit_R", false);
		else if (GetCharDir() == CHAR_DIR::UL)
			GetAnimator()->PlayAnimation(L"ShotGunKin_Hit_L", false);
	}
	else if (GetCharState() == CHAR_STATE::DEATH)
	{
		if (GetCharDir() == CHAR_DIR::DR)
			GetAnimator()->PlayAnimation(L"ShotGunKin_Death", false);
		else if (GetCharDir() == CHAR_DIR::DL)
			GetAnimator()->PlayAnimation(L"ShotGunKin_Death", false);
		else if (GetCharDir() == CHAR_DIR::UR)
			GetAnimator()->PlayAnimation(L"ShotGunKin_Death", false);
		else if (GetCharDir() == CHAR_DIR::UL)
			GetAnimator()->PlayAnimation(L"ShotGunKin_Death", false);
	}
	else if (GetCharState() == CHAR_STATE::DEAD)
	{
		//if (GetCharDir() == CHAR_DIR::DR)
		//	GetAnimator()->PlayAnimation(L"ShotGunKin_Dead_R", true);
		//else if (GetCharDir() == CHAR_DIR::DL)
		//	GetAnimator()->PlayAnimation(L"ShotGunKin_Dead_L", true);
		//else if (GetCharDir() == CHAR_DIR::UR)
		//	GetAnimator()->PlayAnimation(L"ShotGunKin_Dead_R", true);
		//else if (GetCharDir() == CHAR_DIR::UL)
		//	GetAnimator()->PlayAnimation(L"ShotGunKin_Dead_L", true);
	}
}

void CShotGunKin::CreateAnimation()
{
	GetAnimator()->CreateAnimation(L"ShotGunKin_Idle_D", CResourceManager::Get()->FindTexture(L"ShotGunKin_Idle_D"), Vec2(0, 0), Vec2(100, 100), Vec2(100, 0), .1f, 2);
	GetAnimator()->CreateAnimation(L"ShotGunKin_Idle_U", CResourceManager::Get()->FindTexture(L"ShotGunKin_Idle_U"), Vec2(0, 0), Vec2(100, 100), Vec2(100, 0), .1f, 2);
	GetAnimator()->CreateAnimation(L"ShotGunKin_Walk_DR", CResourceManager::Get()->FindTexture(L"ShotGunKin_Walk_DR"), Vec2(0, 0), Vec2(100, 100), Vec2(100, 0), .1f, 6);
	GetAnimator()->CreateAnimation(L"ShotGunKin_Walk_DL", CResourceManager::Get()->FindTexture(L"ShotGunKin_Walk_DL"), Vec2(0, 0), Vec2(100, 100), Vec2(100, 0), .1f, 6);
	GetAnimator()->CreateAnimation(L"ShotGunKin_Walk_U", CResourceManager::Get()->FindTexture(L"ShotGunKin_Walk_U"), Vec2(0, 0), Vec2(100, 100), Vec2(100, 0), .1f, 6);
	GetAnimator()->CreateAnimation(L"ShotGunKin_Hit_R", CResourceManager::Get()->FindTexture(L"ShotGunKin_Hit_R"), Vec2(0, 0), Vec2(100, 100), Vec2(100, 0), .2f, 1);
	GetAnimator()->CreateAnimation(L"ShotGunKin_Hit_L", CResourceManager::Get()->FindTexture(L"ShotGunKin_Hit_L"), Vec2(0, 0), Vec2(100, 100), Vec2(100, 0), .2f, 1);
	GetAnimator()->CreateAnimation(L"ShotGunKin_Death", CResourceManager::Get()->FindTexture(L"ShotGunKin_Death"), Vec2(0, 0), Vec2(120, 120), Vec2(120, 0), .08f, 7);
	//GetAnimator()->CreateAnimation(L"ShotGunKin_Dead_R", CResourceManager::Get()->FindTexture(L"ShotGunKin_Dead_R"), Vec2(0, 0), Vec2(100, 100), Vec2(100, 0), .1f, 1);
	//GetAnimator()->CreateAnimation(L"ShotGunKin_Dead_L", CResourceManager::Get()->FindTexture(L"ShotGunKin_Dead_L"), Vec2(0, 0), Vec2(100, 100), Vec2(100, 0), .1f, 1);
}

void CShotGunKin::OnCollision(CCollider& _pOther)
{
	__super::OnCollision(_pOther);
}

void CShotGunKin::OnCollisionEnter(CCollider& _pOther)
{
	__super::OnCollisionEnter(_pOther);
}

void CShotGunKin::OnCollisionExit(CCollider& _pOther)
{
}