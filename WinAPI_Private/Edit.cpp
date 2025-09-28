#include "pch.h"
#include "Edit.h"

#include "SceneManager.h"

CEdit::CEdit()
{
	SetSceneType(SCENE_TYPE::EDIT);
}

CEdit::~CEdit()
{
	CSceneManager::Get()->SetCurrScene(this);

	Release();
}

void CEdit::Init()
{
}

void CEdit::Update()
{
	__super::Update();
}

void CEdit::LateUpdate()
{
	__super::LateUpdate();
}

void CEdit::Render(HDC _hDC)
{
	__super::Render(_hDC);
}

void CEdit::Release()
{
}

void CEdit::Enter(CObject* _pPlayer)
{
}

void CEdit::Exit(CObject* _pPlayer)
{
}

void CEdit::SetCollision()
{
}