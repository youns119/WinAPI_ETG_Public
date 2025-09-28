#include "pch.h"
#include "Menu.h"

#include "Main.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "ColliderManager.h"
#include "Camera.h"
#include "Mouse.h"
#include "SoundManager.h"

#include "Texture.h"
#include "StartButton.h"
#include "Func.h"

CMenu::CMenu()
	: m_pTexture(nullptr)
	, m_bSceneChange(false)
{
	SetSceneType(SCENE_TYPE::MENU);
}

CMenu::~CMenu()
{
	CSceneManager::Get()->SetCurrScene(this);

	Release();
}

void CMenu::Init()
{
	SetVolume(.1f);

	m_pTexture = CResourceManager::Get()->FindTexture(L"Intro");

	CObject* pMouse = CMouse::Get()->GetMouse();
	CSceneManager::Get()->AddObject(pMouse, OBJECT_TYPE::MOUSE);

	CCamera::Get()->SetPrevLookPos({ CMain::Get()->GetResolution().x / 2.f, CMain::Get()->GetResolution().y / 2.f });
	CCamera::Get()->SetLookAtPos({ CMain::Get()->GetResolution().x / 2.f, CMain::Get()->GetResolution().y / 2.f });

	CObject* pStartButton = new CStartButton;
	pStartButton->SetPos({ 90.f, 580.f });
	CSceneManager::Get()->AddObject(pStartButton, OBJECT_TYPE::UI);

	__super::Init();
}

void CMenu::Update()
{
	__super::Update();
}

void CMenu::LateUpdate()
{
	__super::LateUpdate();

	if (m_bSceneChange)
	{
		CSoundManager::Get()->StopSound(CHANNELID::SOUND_BGM);
		CSoundManager::Get()->PlayBGM(L"BGM.wav", CSceneManager::Get()->GetScenes()[(UINT)SCENE_TYPE::DUNGEON]->GetVolume());

		ChangeScene(SCENE_TYPE::DUNGEON, nullptr);
	}
}

void CMenu::Render(HDC _hDC)
{
	BitBlt
	(
		_hDC,
		0, 0,
		CMain::Get()->GetResolution().x, 
		CMain::Get()->GetResolution().y,
		m_pTexture->GetHDC(),
		0, 0,
		SRCCOPY
	);

	__super::Render(_hDC);
}

void CMenu::Release()
{
}

void CMenu::Enter(CObject* _pPlayer)
{
	CMouse::Get()->SetTexture(CResourceManager::Get()->FindTexture(L"Crosshair"));

	CSoundManager::Get()->PlayBGM(L"Intro.wav", GetVolume());

	SetCollision();
}

void CMenu::Exit(CObject* _pPlayer)
{
}

void CMenu::SetCollision()
{
	CColliderManager::Get()->CheckGroup(OBJECT_TYPE::MOUSE, OBJECT_TYPE::UI);
}