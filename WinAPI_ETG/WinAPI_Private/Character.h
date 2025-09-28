#pragma once

#include "Object.h"

#include "CharacterState.h"
#include "CharacterDir.h"

class CGun;

class CCharacter : public CObject
{
public:
	CCharacter();
	virtual ~CCharacter();

public:
	virtual void Init()				override;
	virtual void Update()			override;
	virtual void LateUpdate()		override;
	virtual void Render(HDC _hDC)	override;
	virtual void Release()			override;

public:
	int GetMaxHP() const { return m_iMaxHP; }
	int GetCurrHP() const { return m_iCurrHP; }
	CHAR_STATE GetCharState() const { return m_eCharState; }
	CHAR_DIR GetCharDir() const { return m_eCharDir; }
	CGun* GetCurrGun() const { return m_pCurrGun; }

	void SetMaxHP(const int _iMaxHP) { m_iMaxHP = _iMaxHP; }
	void SetCurrHP(const int _iCurrHP) { m_iCurrHP = _iCurrHP; }
	void SetTick(const ULONGLONG _iTick) { m_iTick = _iTick; }
	void SetCharState(const CHAR_STATE _eCharState) { m_eCharState = _eCharState; }
	void SetCharDir(const CHAR_DIR _eCharDir) { m_eCharDir = _eCharDir; }
	void SetCurrGun(CGun* _pCurrGun) { m_pCurrGun = _pCurrGun; }

public :
	virtual void PointDir() {};
	virtual void CreateProjectile(CGun* _pGun);
	virtual bool DelayCheck(int _iDelay);
	void ResetTick() { m_iTick = 0; }

public:
	virtual void Motion() {}
	virtual void CreateAnimation() {}
	virtual CCharacter* Clone() { return nullptr; }

private :
	int m_iMaxHP;
	int m_iCurrHP;

	ULONGLONG m_iTick;

private :
	CHAR_STATE m_eCharState;
	CHAR_DIR m_eCharDir;
private :
	CGun* m_pCurrGun;
};