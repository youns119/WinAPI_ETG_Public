#pragma once

#include "KeyState.h"

class CKeyboard : public Singleton<CKeyboard>
{
public :
    struct KeyInfo
    {
        KEY_STATE eKeyState;
        bool bPrevPush;
    };

public :
    CKeyboard();
	virtual ~CKeyboard();

public :
    void Init();
    void Update();

public :
    bool KeyDown(const int _iKey);
    bool KeyPress(const int _iKey);
    bool KeyUp(const int _iKey);

private :
    vector<KeyInfo> m_vecKey;
};