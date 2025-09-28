#include "pch.h"
#include "BulletKin.h"

#include "ResourceManager.h"
#include "Camera.h"

#include "Physics.h"
#include "Animator.h"
#include "Animation.h"
#include "Func.h"
#include "Revolver.h"

CBulletKin::CBulletKin()
{
	SetEnemyType(ENEMY_TYPE::BULLETKIN);
}

CBulletKin::~CBulletKin()
{
	Release();
}

void CBulletKin::Init()
{
	SetName(L"BulletKin");
	SetScale({ 50.f, 50.f });
	SetVolume(0.1f);

	SetMaxHP(15);
	SetCurrHP(GetMaxHP());

	SetRange(500.f);
	SetSpeed(100.f);

	CGun* pGun = new CRevolver();

	pGun->Init();
	pGun->SetTarget(*this);
	pGun->SetShow(true);
	pGun->SetDelay(pGun->GetDelay() * 5.f);

	SetCurrGun(pGun);

	CreateObjectEvent(pGun, OBJECT_TYPE::GUN);

	SetMass(1);
	SetFriction(150.f);
	SetMaxVelocity(200.f);

	__super::Init();

	CreateAnimation();
}

void CBulletKin::Update()
{
	__super::Update();
}

void CBulletKin::LateUpdate()
{
	__super::LateUpdate();
}

void CBulletKin::Render(HDC _hDC)
{
	__super::Render(_hDC);

	//TCHAR szHP[100] = L"";
	//swprintf_s(szHP, L"HP : %d", GetCurrHP());
	//TextOut(_hDC, (int)100.f, (int)250.f, szHP, lstrlen(szHP));
}

void CBulletKin::Release()
{
}

void CBulletKin::PointDir()
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

void CBulletKin::Attack()
{
	if (DelayCheck((int)(GetCurrGun()->GetDelay() * 1000.f)))
		CreateProjectile(GetCurrGun());
}

void CBulletKin::Motion()
{
	if (GetCharState() == CHAR_STATE::IDLE)
	{
		if (GetCharDir() == CHAR_DIR::DR)
			GetAnimator()->PlayAnimation(L"BulletKin_Idle_DR", true);
		else if (GetCharDir() == CHAR_DIR::DL)
			GetAnimator()->PlayAnimation(L"BulletKin_Idle_DL", true);
		else if (GetCharDir() == CHAR_DIR::UR)
			GetAnimator()->PlayAnimation(L"BulletKin_Idle_U", true);
		else if (GetCharDir() == CHAR_DIR::UL)
			GetAnimator()->PlayAnimation(L"BulletKin_Idle_U", true);
	}
	else if (GetCharState() == CHAR_STATE::WALK)
	{
		if (GetCharDir() == CHAR_DIR::DR)
			GetAnimator()->PlayAnimation(L"BulletKin_Walk_DR", true);
		else if (GetCharDir() == CHAR_DIR::DL)
			GetAnimator()->PlayAnimation(L"BulletKin_Walk_DL", true);
		else if (GetCharDir() == CHAR_DIR::UR)
			GetAnimator()->PlayAnimation(L"BulletKin_Walk_U", true);
		else if (GetCharDir() == CHAR_DIR::UL)
			GetAnimator()->PlayAnimation(L"BulletKin_Walk_U", true);
	}
	else if (GetCharState() == CHAR_STATE::HIT)
	{
		if (GetCharDir() == CHAR_DIR::DR)
			GetAnimator()->PlayAnimation(L"BulletKin_Hit_R", false);
		else if (GetCharDir() == CHAR_DIR::DL)
			GetAnimator()->PlayAnimation(L"BulletKin_Hit_L", false);
		else if (GetCharDir() == CHAR_DIR::UR)
			GetAnimator()->PlayAnimation(L"BulletKin_Hit_R", false);
		else if (GetCharDir() == CHAR_DIR::UL)
			GetAnimator()->PlayAnimation(L"BulletKin_Hit_L", false);
	}
	else if (GetCharState() == CHAR_STATE::DEATH)
	{
		if (GetCharDir() == CHAR_DIR::DR)
			GetAnimator()->PlayAnimation(L"BulletKin_Death_R", false);
		else if (GetCharDir() == CHAR_DIR::DL)
			GetAnimator()->PlayAnimation(L"BulletKin_Death_L", false);
		else if (GetCharDir() == CHAR_DIR::UR)
			GetAnimator()->PlayAnimation(L"BulletKin_Death_R", false);
		else if (GetCharDir() == CHAR_DIR::UL)
			GetAnimator()->PlayAnimation(L"BulletKin_Death_L", false);
	}
	else if (GetCharState() == CHAR_STATE::DEAD)
	{
		if (GetCharDir() == CHAR_DIR::DR)
			GetAnimator()->PlayAnimation(L"BulletKin_Dead_R", true);
		else if (GetCharDir() == CHAR_DIR::DL)
			GetAnimator()->PlayAnimation(L"BulletKin_Dead_L", true);
		else if (GetCharDir() == CHAR_DIR::UR)
			GetAnimator()->PlayAnimation(L"BulletKin_Dead_R", true);
		else if (GetCharDir() == CHAR_DIR::UL)
			GetAnimator()->PlayAnimation(L"BulletKin_Dead_L", true);
	}
}

void CBulletKin::CreateAnimation()
{
	GetAnimator()->CreateAnimation(L"BulletKin_Idle_DR", CResourceManager::Get()->FindTexture(L"BulletKin_Idle_DR"), Vec2(0, 0), Vec2(80, 80), Vec2(80, 0), .1f, 2);
	GetAnimator()->CreateAnimation(L"BulletKin_Idle_DL", CResourceManager::Get()->FindTexture(L"BulletKin_Idle_DL"), Vec2(0, 0), Vec2(80, 80), Vec2(80, 0), .1f, 2);
	GetAnimator()->CreateAnimation(L"BulletKin_Idle_U", CResourceManager::Get()->FindTexture(L"BulletKin_Idle_U"), Vec2(0, 0), Vec2(80, 80), Vec2(80, 0), .1f, 2);
	GetAnimator()->CreateAnimation(L"BulletKin_Walk_DR", CResourceManager::Get()->FindTexture(L"BulletKin_Walk_DR"), Vec2(0, 0), Vec2(80, 80), Vec2(80, 0), .1f, 6);
	GetAnimator()->CreateAnimation(L"BulletKin_Walk_DL", CResourceManager::Get()->FindTexture(L"BulletKin_Walk_DL"), Vec2(0, 0), Vec2(80, 80), Vec2(80, 0), .1f, 6);
	GetAnimator()->CreateAnimation(L"BulletKin_Walk_U", CResourceManager::Get()->FindTexture(L"BulletKin_Walk_U"), Vec2(0, 0), Vec2(80, 80), Vec2(80, 0), .1f, 7);
	GetAnimator()->CreateAnimation(L"BulletKin_Hit_R", CResourceManager::Get()->FindTexture(L"BulletKin_Hit_R"), Vec2(0, 0), Vec2(80, 80), Vec2(80, 0), .2f, 3);
	GetAnimator()->CreateAnimation(L"BulletKin_Hit_L", CResourceManager::Get()->FindTexture(L"BulletKin_Hit_L"), Vec2(0, 0), Vec2(80, 80), Vec2(80, 0), .2f, 3);
	GetAnimator()->CreateAnimation(L"BulletKin_Death_R", CResourceManager::Get()->FindTexture(L"BulletKin_Death_R"), Vec2(0, 0), Vec2(80, 80), Vec2(80, 0), .1f, 5);
	GetAnimator()->CreateAnimation(L"BulletKin_Death_L", CResourceManager::Get()->FindTexture(L"BulletKin_Death_L"), Vec2(0, 0), Vec2(80, 80), Vec2(80, 0), .1f, 5);
	GetAnimator()->CreateAnimation(L"BulletKin_Dead_R", CResourceManager::Get()->FindTexture(L"BulletKin_Dead_R"), Vec2(0, 0), Vec2(80, 80), Vec2(80, 0), .1f, 1);
	GetAnimator()->CreateAnimation(L"BulletKin_Dead_L", CResourceManager::Get()->FindTexture(L"BulletKin_Dead_L"), Vec2(0, 0), Vec2(80, 80), Vec2(80, 0), .1f, 1);
}

void CBulletKin::OnCollision(CCollider& _pOther)
{
	__super::OnCollision(_pOther);
}

void CBulletKin::OnCollisionEnter(CCollider& _pOther)
{
	__super::OnCollisionEnter(_pOther);
}

void CBulletKin::OnCollisionExit(CCollider& _pOther)
{
}