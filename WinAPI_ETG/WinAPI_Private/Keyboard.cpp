#include "pch.h"
#include "Keyboard.h"

CKeyboard::CKeyboard()
{
	m_vecKey.clear();
}

CKeyboard::~CKeyboard()
{
}

void CKeyboard::Init()
{
	for (int i = 0; i <= VK_MAX; i++)
		m_vecKey.push_back(KeyInfo{ KEY_STATE::NONE, false });
}

void CKeyboard::Update()
{
	HWND hWnd = GetFocus();

	if (hWnd != nullptr)
	{
		for (int i = 0; i <= VK_MAX; i++)
		{
			if (GetAsyncKeyState(i) & 0x8000)
			{
				if (m_vecKey[i].bPrevPush)
					m_vecKey[i].eKeyState = KEY_STATE::PRESS;
				else
					m_vecKey[i].eKeyState = KEY_STATE::DOWN;

				m_vecKey[i].bPrevPush = true;
			}
			else
			{
				if (m_vecKey[i].bPrevPush)
					m_vecKey[i].eKeyState = KEY_STATE::UP;
				else
					m_vecKey[i].eKeyState = KEY_STATE::NONE;

				m_vecKey[i].bPrevPush = false;
			}
		}
	}
	else
	{
		for (int i = 0; i <= VK_MAX; i++)
		{
			if (m_vecKey[i].eKeyState == KEY_STATE::DOWN || m_vecKey[i].eKeyState == KEY_STATE::PRESS)
				m_vecKey[i].eKeyState = KEY_STATE::UP;

			m_vecKey[i].bPrevPush = false;
		}
	}
}

bool CKeyboard::KeyDown(int _iKey)
{
	return m_vecKey[_iKey].eKeyState == KEY_STATE::DOWN;
}

bool CKeyboard::KeyPress(int _iKey)
{
	return m_vecKey[_iKey].eKeyState == KEY_STATE::PRESS;
}

bool CKeyboard::KeyUp(int _iKey)
{
	return m_vecKey[_iKey].eKeyState == KEY_STATE::UP;
}