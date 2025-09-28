#include "pch.h"
#include "BulletKing.h"

#include "ResourceManager.h"
#include "SceneManager.h"
#include "Camera.h"
#include "Timer.h"
#include "Mouse.h"
#include "SoundManager.h"
#include "UIManager.h"

#include "Func.h"
#include "Collider.h"
#include "Animator.h"
#include "Animation.h"
#include "Projectile.h"
#include "BossChair.h"
#include "Projectile_Revolver.h"
#include "BlowEffect.h"
#include "SmokeEffect.h"

CBulletKing::CBulletKing()
	: m_bShow(true)
	, m_bSpin(false)
	, m_iCount(0)
	, m_iSoundCount(0)
	, m_fDelay(0.f)
	, m_fPatternDelay(0.f)
	, m_fDeathTime(0.f)
	, m_ePatternType(PATTERN_TYPE::END)
	, m_eBossState(BOSS_STATE::END)
	, m_pChair(nullptr)
{
	SetEnemyType(ENEMY_TYPE::BULLETKING);

	m_vProjectile.reserve(100);
}

CBulletKing::~CBulletKing()
{
	Release();
}

void CBulletKing::Init()
{
	SetName(L"BulletKing");
	SetScale({ 140.f, 140.f });
	SetVolume(0.2f);

	SetMaxHP(950);
	SetCurrHP(GetMaxHP());

	SetRange(500.f);
	SetSpeed(30.f);

	SetMass(1);
	SetFriction(250.f);
	SetMaxVelocity(300.f);

	m_fDeathTime = 3.3f;
	m_bShow = true;
	m_eBossState = BOSS_STATE::IDLE;

	__super::Init();

	CreateAnimation();

	m_pChair = new CBossChair;
	dynamic_cast<CBossChair*>(m_pChair)->SetTarget(this);
	
	CSceneManager::Get()->AddObject(m_pChair, OBJECT_TYPE::EFFECT);
}

void CBulletKing::Update()
{
	if (m_eBossState == BOSS_STATE::DIE || m_eBossState == BOSS_STATE::DEAD)
		return;

	if (GetTarget())
	{
		Vec2 vDist = GetTarget()->GetPos() - GetPos();
		Vec2 vNorm = vDist.Normalize();
		float fDist = vDist.Length();
		float fRadian = vDist.DirToRadian();

		SetRadian(fRadian);

		if (m_ePatternType != PATTERN_TYPE::END)
		{
			if (m_iCount == 0)
				m_eBossState = BOSS_STATE::ATTACK;
			else if (m_ePatternType == PATTERN_TYPE::PATTERN4)
			{
				if (m_iCount == 15)
				{
					m_eBossState = BOSS_STATE::IDLE;
					m_bShow = true;

					CBossChair* pChair = dynamic_cast<CBossChair*>(m_pChair);
					pChair->SetChairState(CHAIR_STATE::IDLE);
				}
			}

			Attack();

			return;
		}

		if (fDist <= GetRange() && DelayCheck((int)(m_fPatternDelay * 1000.f)))
		{
			//int iRand = rand() % (UINT)(PATTERN_TYPE::END);
			int iRand = rand() % (UINT)(PATTERN_TYPE::PATTERN5);
			m_ePatternType = (PATTERN_TYPE)iRand;

			if (m_ePatternType == PATTERN_TYPE::PATTERN4)
				m_bSpin = true;

			ResetTick();
		}
		else
			SetPos(GetPos() + vNorm * GetSpeed() * CTimer::Get()->GetDelta());
	}
}

void CBulletKing::LateUpdate()
{
	if (m_eBossState == BOSS_STATE::DEAD)
		return;

	CCharacter::LateUpdate();

	if (GetCurrHP() <= 0)
		if (m_eBossState != BOSS_STATE::DIE && m_eBossState != BOSS_STATE::DEAD)
		{
			m_bShow = true;

			m_eBossState = BOSS_STATE::DIE;
			SetTick(GetTickCount64());

			CCamera::Get()->SetTarget(this);

			CSceneManager::Get()->GetCurrScene()->DeleteGroupObjects(OBJECT_TYPE::PROJECTILE_ENEMY);

			CSoundManager::Get()->StopSound(CHANNELID::SOUND_BGM);
			CSoundManager::Get()->PlaySound(L"BulletKing_Explode.wav", CHANNELID::SOUND_EFFECT, GetVolume() * 1.5f);
		}

	if (m_eBossState == BOSS_STATE::DIE)
	{
		if (DelayCheck(m_fDeathTime * 1000.f))
		{
			m_eBossState = BOSS_STATE::DEAD;

			CCamera::Get()->SetTarget(CMouse::Get()->GetPoint());
			CUIManager::Get()->DeleteBossUI();

			CreateEffect();
		}
	}

	if (m_eBossState == BOSS_STATE::HIT)
		if (GetAnimator()->GetCurrAnim()->GetFinish())
			m_eBossState = BOSS_STATE::IDLE;

	if (m_eBossState == BOSS_STATE::ATTACK)
		if (GetAnimator()->GetCurrAnim()->GetFinish())
			m_eBossState = BOSS_STATE::IDLE;

	Motion();
}

void CBulletKing::Render(HDC _hDC)
{
	if (!m_bShow)
		return;

	__super::Render(_hDC);
}

void CBulletKing::Release()
{
}

void CBulletKing::Attack()
{
	switch (m_ePatternType)
	{
	case PATTERN_TYPE::PATTERN1 :
		m_fDelay = 0.3f;
		m_fPatternDelay = 1.5f;
		Pattern1();
		break;
	case PATTERN_TYPE::PATTERN2 :
		m_fDelay = 1.f;
		m_fPatternDelay = 2.5f;
		Pattern2();
		break;
	case PATTERN_TYPE::PATTERN3 :
		m_fDelay = 0.07f;
		m_fPatternDelay = 2.5f;
		Pattern3();
		break;
	case PATTERN_TYPE::PATTERN4 :
		m_fDelay = .2f;
		m_fPatternDelay = 2.5f;
		Pattern4();
		break;
	case PATTERN_TYPE::PATTERN5 :
		m_fDelay = 1.f;
		m_fPatternDelay = 2.f;
		Pattern5();
		break;
	default :
		break;
	}
}

void CBulletKing::Pattern1()
{
	if (m_iCount == 2)
	{
		m_iCount = 0;
		m_ePatternType = PATTERN_TYPE::END;

		return;
	}

	if (DelayCheck((int)(m_fDelay * 1000.f)))
	{
		vector<CProjectile*> vProjectile;
		vProjectile.assign(3, nullptr);

		float fDegree = GetRadian() * 180.f / PI - 30.f;

		for (int i = 0; i < vProjectile.size(); i++)
		{
			vProjectile[i] = new CProjectile_Revolver;

			float fFinalDegree = fDegree + 30.f * i;

			Vec2 vFinalPos = 
			{ GetPos().fX + GetScale().fX / 2.f * cosf(fFinalDegree * PI / 180.f),
				GetPos().fY + GetScale().fY / 2.f * sinf(fFinalDegree * PI / 180.f)};

			vProjectile[i]->SetPos(vFinalPos);
			vProjectile[i]->SetRadian(GetRadian());
			vProjectile[i]->SetObjectType(OBJECT_TYPE::PROJECTILE_ENEMY);
			vProjectile[i]->SetSpeed(16.f);
			vProjectile[i]->SetRange(50.f);
			vProjectile[i]->Init();

			CreateObjectEvent(vProjectile[i], OBJECT_TYPE::PROJECTILE_ENEMY);
		}

		ShotSound();
		AddSoundCount();

		m_iCount++;
	}
}

void CBulletKing::Pattern2()
{
	if (DelayCheck((int)(m_fDelay * 1000.f)))
	{
		vector<CProjectile*> vProjectile;
		float fDegree = 10.f;

		vProjectile.assign((int)(360.f / fDegree), nullptr);

		for (int i = 0; i < (int)(360.f / fDegree); i++)
		{
			vProjectile[i] = new CProjectile_Revolver;

			float fFinalDegree = fDegree * i;

			Vec2 vFinalPos =
			{ GetPos().fX + GetScale().fX / 3.f * cosf(fFinalDegree * PI / 180.f),
				GetPos().fY + GetScale().fY / 3.f * sinf(fFinalDegree * PI / 180.f) };

			vProjectile[i]->SetPos(vFinalPos);
			vProjectile[i]->SetRadian(fFinalDegree * PI / 180.f);
			vProjectile[i]->SetObjectType(OBJECT_TYPE::PROJECTILE_ENEMY);
			vProjectile[i]->SetSpeed(16.f);
			vProjectile[i]->SetRange(50.f);
			vProjectile[i]->Init();

			CreateObjectEvent(vProjectile[i], OBJECT_TYPE::PROJECTILE_ENEMY);
		}

		ShotSound();
		AddSoundCount();
	}

	m_ePatternType = PATTERN_TYPE::END;
}

void CBulletKing::Pattern3()
{
	if (m_iCount == 4)
	{
		m_iCount = 0;
		m_ePatternType = PATTERN_TYPE::END;

		return;
	}

	if (DelayCheck((int)(m_fDelay * 1000.f)))
	{
		vector<CProjectile*> vProjectile;
		int iDivide = 8;
		float fDegree = (float)((int)360.f / (int)iDivide);

		vProjectile.assign(iDivide * 3, nullptr);

		for (int i = 0; i < iDivide; i++)
		{
			float fFinalDegree = fDegree * i - 10.f;

			for (int j = 0; j < 3; j++)
			{
				int iIndex = i * 3 + j;

				vProjectile[iIndex] = new CProjectile_Revolver;

				fFinalDegree = fFinalDegree + 10.f * j;

				Vec2 vFinalPos =
				{ GetPos().fX + GetScale().fX / 3.f * cosf(fFinalDegree * PI / 180.f),
					GetPos().fY + GetScale().fY / 3.f * sinf(fFinalDegree * PI / 180.f) };

				vProjectile[iIndex]->SetPos(vFinalPos);
				vProjectile[iIndex]->SetRadian(fFinalDegree * PI / 180.f);
				vProjectile[iIndex]->SetObjectType(OBJECT_TYPE::PROJECTILE_ENEMY);
				vProjectile[iIndex]->SetSpeed(16.f - m_iCount * 2.f);
				vProjectile[iIndex]->SetRange(50.f);
				vProjectile[iIndex]->Init();



				CreateObjectEvent(vProjectile[iIndex], OBJECT_TYPE::PROJECTILE_ENEMY);
			}
		}

		ShotSound();
		AddSoundCount();

		m_iCount++;
	}
}

void CBulletKing::Pattern4()
{
	if (m_iCount == 15)
	{
		m_iCount = 0;
		m_ePatternType = PATTERN_TYPE::END;

		return;
	}

	if (DelayCheck((int)(m_fDelay * 1000.f)))
	{
		vector<CProjectile*> vProjectile;
		int iDivide = 6;
		float fDegree = (float)((int)360.f / (int)iDivide);
		float fOffset = (360.f / 10) * m_iCount;

		vProjectile.assign(iDivide, nullptr);

		for (int i = 0; i < iDivide; i++)
		{
			float fFinalDegree = fOffset + fDegree * i;

			vProjectile[i] = new CProjectile_Revolver;

			Vec2 vFinalPos =
			{ GetPos().fX + GetScale().fX / 3.f * cosf(fFinalDegree * PI / 180.f),
				GetPos().fY + GetScale().fY / 3.f * sinf(fFinalDegree * PI / 180.f) };

			vProjectile[i]->SetPos(vFinalPos);
			vProjectile[i]->SetRadian(fFinalDegree * PI / 180.f);
			vProjectile[i]->SetObjectType(OBJECT_TYPE::PROJECTILE_ENEMY);
			vProjectile[i]->SetSpeed(3.f);
			vProjectile[i]->SetRange(50.f);
			vProjectile[i]->Init();

			CreateObjectEvent(vProjectile[i], OBJECT_TYPE::PROJECTILE_ENEMY);
		}

		m_iCount++;

		if (m_bSpin)
		{
			CSoundManager::Get()->PlaySound(L"BulletKing_Spin.wav", CHANNELID::SOUND_PROJECTILE, GetVolume() * 2.f);

			m_bSpin = false;
		}

		m_eBossState = BOSS_STATE::ROTATE;
	}
}

void CBulletKing::Pattern5()
{
	if (m_iCount == 3)
	{
		m_iCount = 0;
		m_ePatternType = PATTERN_TYPE::END;

		m_vProjectile.clear();

		return;
	}

	int iDivide = 8;

	if (m_iCount == 0 && DelayCheck((int)(m_fDelay * 1000.f)))
	{
		CProjectile* pProjectile = new CProjectile_Revolver;

		Vec2 vFinalPos =
		{ GetPos().fX + GetScale().fX / 3.f * cosf(-90.f * PI / 180.f),
			GetPos().fY + GetScale().fY / 3.f * sinf(-90.f * PI / 180.f) };

		pProjectile->SetPos(vFinalPos);
		pProjectile->SetRadian(-90.f * PI / 180.f);
		pProjectile->SetObjectType(OBJECT_TYPE::PROJECTILE_ENEMY);
		pProjectile->SetSpeed(3.f);
		pProjectile->SetRange(50.f);
		pProjectile->Init();

		m_vProjectile.push_back(pProjectile);
		CreateObjectEvent(pProjectile, OBJECT_TYPE::PROJECTILE_ENEMY);

		m_iCount++;
	}

	if (m_iCount == 1 && DelayCheck((int)(m_fDelay * 1000.f)))
	{
		Vec2 vStartPos = m_vProjectile[0]->GetPos();
		DeleteObjectEvent(m_vProjectile[0]);

		int iDivide = 8;

		for (int i = 0; i < iDivide; i++)
		{
			float fDegree =  (360.f / (float)iDivide) * i;

			CProjectile* pProjectile = new CProjectile_Revolver;

			pProjectile->SetPos(vStartPos);
			pProjectile->SetRadian(fDegree * PI / 180.f);
			pProjectile->SetObjectType(OBJECT_TYPE::PROJECTILE_ENEMY);
			pProjectile->SetSpeed(8.f);
			pProjectile->SetRange(50.f);
			pProjectile->Init();

			m_vProjectile.push_back(pProjectile);
			CreateObjectEvent(pProjectile, OBJECT_TYPE::PROJECTILE_ENEMY);
		}
	}

	if (m_iCount == 2 && DelayCheck((int)(m_fDelay * 1000.f)))
	{
		Vec2 vStartPos;

		for (int i = 1; i < m_vProjectile.size(); i++)
		{
			vStartPos = m_vProjectile[i]->GetPos();
			DeleteObjectEvent(m_vProjectile[i]);
		}

		for (int i = 0; i < iDivide; i++)
		{
			float fDegree = (360.f / (float)iDivide) * i;

			CProjectile* pProjectile = new CProjectile_Revolver;

			pProjectile->SetPos(vStartPos);
			pProjectile->SetRadian(fDegree * PI / 180.f);
			pProjectile->SetObjectType(OBJECT_TYPE::PROJECTILE_ENEMY);
			pProjectile->SetSpeed(8.f);
			pProjectile->SetRange(50.f);
			pProjectile->Init();

			m_vProjectile.push_back(pProjectile);
			CreateObjectEvent(pProjectile, OBJECT_TYPE::PROJECTILE_ENEMY);
		}

		m_iCount++;
	}
}

void CBulletKing::CreateEffect()
{
	CBlowEffect* pBlowEffect = new CBlowEffect;
	CSmokeEffect* pSmokeEffect = new CSmokeEffect;

	pBlowEffect->Init();
	pSmokeEffect->Init();

	pBlowEffect->SetPos({ GetPos().fX, GetPos().fY });
	pSmokeEffect->SetPos({ GetPos().fX, GetPos().fY });

	CreateObjectEvent(pBlowEffect, OBJECT_TYPE::EFFECT);
	CreateObjectEvent(pSmokeEffect, OBJECT_TYPE::EFFECT);
}

void CBulletKing::Motion()
{
	if (m_eBossState == BOSS_STATE::IDLE)
		GetAnimator()->PlayAnimation(L"BulletKing_Idle", true);
	else if (m_eBossState == BOSS_STATE::ATTACK)
		GetAnimator()->PlayAnimation(L"BulletKing_Attack", false);
	else if (m_eBossState == BOSS_STATE::HIT)
		GetAnimator()->PlayAnimation(L"BulletKing_Hit", false);
	else if (m_eBossState == BOSS_STATE::DIE)
	{
		GetAnimator()->PlayAnimation(L"BulletKing_Die", true);

		CBossChair* pChair = dynamic_cast<CBossChair*>(m_pChair);

		pChair->SetChairState(CHAIR_STATE::DIE);
	}
	else if (m_eBossState == BOSS_STATE::ROTATE)
	{
		CBossChair* pChair = dynamic_cast<CBossChair*>(m_pChair);

		pChair->SetChairState(CHAIR_STATE::ROTATE);

		m_eBossState = BOSS_STATE::ROTATE;
		m_bShow = false;
	}
	else if (m_eBossState == BOSS_STATE::DEAD)
		m_bShow = false;
}

void CBulletKing::CreateAnimation()
{
	GetAnimator()->CreateAnimation(L"BulletKing_Idle", CResourceManager::Get()->FindTexture(L"BulletKing_Idle"), Vec2(0, 0), Vec2(120, 120), Vec2(120, 0), .2f, 2);
	GetAnimator()->CreateAnimation(L"BulletKing_Attack", CResourceManager::Get()->FindTexture(L"BulletKing_Attack"), Vec2(0, 0), Vec2(120, 120), Vec2(120, 0), .08f, 3);
	GetAnimator()->CreateAnimation(L"BulletKing_Hit", CResourceManager::Get()->FindTexture(L"BulletKing_Hit"), Vec2(0, 0), Vec2(120, 120), Vec2(120, 0), .5f, 1);
	GetAnimator()->CreateAnimation(L"BulletKing_Die", CResourceManager::Get()->FindTexture(L"BulletKing_Die"), Vec2(0, 0), Vec2(120, 120), Vec2(120, 0), .2f, 3);
}

void CBulletKing::ShotSound()
{
	float fVolume = GetVolume();

	//if (m_ePatternType == PATTERN_TYPE::PATTERN3 || m_ePatternType == PATTERN_TYPE::PATTERN2)
	//	fVolume *= 0.7f;

	switch (m_iSoundCount)
	{
	case 0 :
		CSoundManager::Get()->PlaySound(L"BulletKing_Shot1.wav", CHANNELID::SOUND_PROJECTILE, fVolume);
		break;
	case 1:
		CSoundManager::Get()->PlaySound(L"BulletKing_Shot2.wav", CHANNELID::SOUND_PROJECTILE, fVolume);
		break;
	case 2:
		CSoundManager::Get()->PlaySound(L"BulletKing_Shot3.wav", CHANNELID::SOUND_PROJECTILE, fVolume);
		break;
	}
}

void CBulletKing::OnCollision(CCollider& _pOther)
{
}

void CBulletKing::OnCollisionEnter(CCollider& _pOther)
{
	CObject::OnCollisionEnter(_pOther);

	CObject* pOther = _pOther.GetOwner();

	if (pOther->GetObjectType() == OBJECT_TYPE::PROJECTILE_PLAYER)
	{
		if (m_eBossState != BOSS_STATE::DIE && m_eBossState != BOSS_STATE::DEAD)
		{
			CProjectile* pProjectile = dynamic_cast<CProjectile*>(pOther);
			float fDamage = pProjectile->GetDamage();

			SetCurrHP(GetCurrHP() - (int)fDamage);

			m_eBossState = BOSS_STATE::HIT;

			DeleteObjectEvent(pOther);
			pProjectile->CreateEffect();
		}
	}
}

void CBulletKing::OnCollisionExit(CCollider& _pOther)
{
}