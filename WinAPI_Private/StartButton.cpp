#include "pch.h"
#include "StartButton.h"

#include "Keyboard.h"
#include "SceneManager.h"
#include "SoundManager.h"

#include "Collider.h"
#include "Menu.h"

CStartButton::CStartButton()
{
	SetRenderType(RENDER_TYPE::RENDER_UI);
}

CStartButton::~CStartButton()
{
	Release();
}

void CStartButton::Init()
{
	SetScale({ 120.f, 30.f });
	SetRenderScale(GetScale());
	SetVolume(0.1f);

	CreateCollider();
	GetCollider()->SetScale(GetScale());
	GetCollider()->SetShow(false);

	SetUIType(UI_TYPE::BUTTON);
}

void CStartButton::Update()
{
}

void CStartButton::LateUpdate()
{
	__super::LateUpdate();
}

void CStartButton::Render(HDC _hDC)
{
	__super::Render(_hDC);
}

void CStartButton::Release()
{
}

void CStartButton::OnCollision(CCollider& _pOther)
{
	CObject* pOwner = _pOther.GetOwner();

	if (pOwner->GetObjectType() == OBJECT_TYPE::MOUSE)
		if (CKeyboard::Get()->KeyDown(VK_LBUTTON))
		{
			dynamic_cast<CMenu*>(CSceneManager::Get()->GetCurrScene())->SetSceneChange(true);
			
			CSoundManager::Get()->PlaySound(L"Button_Input.wav", CHANNELID::SOUND_INTERFACE, GetVolume());
		}
}

void CStartButton::OnCollisionEnter(CCollider& _pOther)
{
}

void CStartButton::OnCollisionExit(CCollider& _pOther)
{
}