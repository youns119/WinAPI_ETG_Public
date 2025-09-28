#pragma 

#include "Effect.h"

#include "ProjectileType.h"

class CMachineGunEffect : public CEffect
{
public :
	CMachineGunEffect();
	virtual ~CMachineGunEffect();

public :
	virtual void Init()				override;
	virtual void Update()			override;
	virtual void LateUpdate()		override;
	virtual void Render(HDC _hDC)	override;
	virtual void Release()			override;

public :
	virtual void CreateAnimation() override;
};