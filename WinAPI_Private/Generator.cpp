#include "pch.h"
#include "Generator.h"

#include "ResourceManager.h"
#include "Main.h"
#include "Camera.h"
#include "SceneManager.h"

#include "Texture.h"
#include "Collider.h"
#include "Wall.h"
#include "EnemyGen.h"
#include "Func.h"

CGenerator::CGenerator()
	: m_pTexture(nullptr)
{
	m_vWall.reserve(200);
}

CGenerator::~CGenerator()
{
	Release();
}

void CGenerator::Init()
{
}

void CGenerator::Update()
{
}

void CGenerator::LateUpdate()
{
}

void CGenerator::Render(HDC _hDC)
{
	Vec2 vPos;
	vPos.fX = (float)m_pTexture->GetWidth() / 2.f;
	vPos.fY = (float)m_pTexture->GetHeight() / 2.f;

	Vec2 vRenderPos = CCamera::Get()->GetRenderPos(vPos);

	BitBlt
	(
		_hDC,
		0, 0,
		CMain::Get()->GetResolution().x,
		CMain::Get()->GetResolution().y,
		m_pTexture->GetHDC(),
		CCamera::Get()->GetLookPos().fX - CMain::Get()->GetResolution().x / 2,
		CCamera::Get()->GetLookPos().fY - CMain::Get()->GetResolution().y / 2,
		SRCCOPY
	);
}

void CGenerator::Release()
{
}

void CGenerator::CreateDungeon()
{
	m_vWall.clear();

	// Start
	m_vRoomPos.push_back({ 1230.f, 2300.f });
	// Room1
	m_vRoomPos.push_back({ 1825.f, 3450.f });
	// Room2
	m_vRoomPos.push_back({ 2040.f, 4580.f });
	// Room3
	m_vRoomPos.push_back({ 790.f, 4620.f });
	// Room4
	m_vRoomPos.push_back({ 2970.f, 3400.f });
	// Shop
	m_vRoomPos.push_back({ 3850.f, 3920.f });
	// PreBoss
	m_vRoomPos.push_back({ 2685.f, 1318.f });
	// ChestRoom
	m_vRoomPos.push_back({ 1990.f, 5350.f });

	CreateDungeonWall();
	CreateDungeonTrigger();
}

void CGenerator::CreateBossRoom()
{
	m_vWall.clear();
	CreateBossWall();
}

void CGenerator::CreateDungeonTrigger()
{
	vector<CObject*> vEnemyGen;
	vEnemyGen.reserve(10);

	for (int i = 1; i < 5; i++)
	{
		CObject* pEnemyGen = new CEnemyGen(ENEMY_GEN_TYPE::ROOM1);

		pEnemyGen->SetPos(m_vRoomPos[i]);
		pEnemyGen->SetScale({ 500.f, 500.f });
		vEnemyGen.push_back(pEnemyGen);
	}

	for (int i = 0; i < vEnemyGen.size(); i++)
		CSceneManager::Get()->AddObject(vEnemyGen[i], OBJECT_TYPE::EVENT_TRIGGER);
}

void CGenerator::CreateBossWall()
{
	CObject* pWall1 = new CWall;
	pWall1->SetPos({ 1500.f, 785.f });
	pWall1->SetScale({ 2000.f, 60.f });
	m_vWall.push_back(pWall1);

	CObject* pWall2 = new CWall;
	pWall2->SetPos({ 1500.f, 2265.f });
	pWall2->SetScale({ 2000.f, 60.f });
	m_vWall.push_back(pWall2);

	CObject* pWall3 = new CWall;
	pWall3->SetPos({ 480.f, 1520.f });
	pWall3->SetScale({ 60.f, 1530.f });
	m_vWall.push_back(pWall3);

	CObject* pWall4 = new CWall;
	pWall4->SetPos({ 2515.f, 1520.f });
	pWall4->SetScale({ 60.f, 1530.f });
	m_vWall.push_back(pWall4);

	for (int i = 0; i < m_vWall.size(); i++)
		CSceneManager::Get()->AddObject(m_vWall[i], OBJECT_TYPE::WALL);
}

void CGenerator::CreateDungeonWall()
{
	CObject* pWall1 = new CWall;
	pWall1->SetPos({ 580.f, 1825.f });
	pWall1->SetScale({ 50.f, 780.f });
	m_vWall.push_back(pWall1);

	CObject* pWall2 = new CWall;
	pWall2->SetPos({ 1390.f, 1820.f });
	pWall2->SetScale({ 50.f, 780.f });
	m_vWall.push_back(pWall2);

	CObject* pWall3 = new CWall;
	pWall3->SetPos({ 980.f, 1430.f });
	pWall3->SetScale({ 770.f, 50.f });
	m_vWall.push_back(pWall3);

	CObject* pWall4 = new CWall;
	pWall4->SetPos({ 870.f, 2235.f });
	pWall4->SetScale({ 535.f, 50.f });
	m_vWall.push_back(pWall4);

	CObject* pWall5 = new CWall;
	pWall5->SetPos({ 1295.f, 2235.f });
	pWall5->SetScale({ 150.f, 50.f });
	m_vWall.push_back(pWall5);

	CObject* pWall6 = new CWall;
	pWall6->SetPos({ 1110.f, 2295.f });
	pWall6->SetScale({ 50.f, 145.f });
	m_vWall.push_back(pWall6);

	CObject* pWall7 = new CWall;
	pWall7->SetPos({ 1240.f, 2295.f });
	pWall7->SetScale({ 50.f, 145.f });
	m_vWall.push_back(pWall7);

	CObject* pWall8 = new CWall;
	pWall8->SetPos({ 980.f, 1650.f });
	pWall8->SetScale({ 100.f, 100.f });
	m_vWall.push_back(pWall8);

	CObject* pWall9 = new CWall;
	pWall9->SetPos({ 1085.f, 2370.f });
	pWall9->SetScale({ 100.f, 50.f });
	m_vWall.push_back(pWall9);

	CObject* pWall10 = new CWall;
	pWall10->SetPos({ 1565.f, 2370.f });
	pWall10->SetScale({ 700.f, 50.f });
	m_vWall.push_back(pWall10);

	CObject* pWall11 = new CWall;
	pWall11->SetPos({ 1035.f, 2770.f });
	pWall11->SetScale({ 50.f, 850.f });
	m_vWall.push_back(pWall11);

	CObject* pWall12 = new CWall;
	pWall12->SetPos({ 1945.f, 2580.f });
	pWall12->SetScale({ 90.f, 750.f });
	m_vWall.push_back(pWall12);

	CObject* pWall13 = new CWall;
	pWall13->SetPos({ 1355.f, 3235.f });
	pWall13->SetScale({ 700.f, 155.f });
	m_vWall.push_back(pWall13);

	CObject* pWall14 = new CWall;
	pWall14->SetPos({ 1140.f, 3430.f });
	pWall14->SetScale({ 295.f, 390.f });
	m_vWall.push_back(pWall14);

	CObject* pWall15 = new CWall;
	pWall15->SetPos({ 935.f, 3390.f });
	pWall15->SetScale({ 110.f, 240.f });
	m_vWall.push_back(pWall15);

	CObject* pWall16 = new CWall;
	pWall16->SetPos({ 630.f, 3360.f });
	pWall16->SetScale({ 600.f, 50.f });
	m_vWall.push_back(pWall16);

	CObject* pWall17 = new CWall;
	pWall17->SetPos({ 325.f, 3425.f });
	pWall17->SetScale({ 110.f, 165.f });
	m_vWall.push_back(pWall17);

	CObject* pWall18 = new CWall;
	pWall18->SetPos({ 240.f, 3840.f });
	pWall18->SetScale({ 50.f, 850.f });
	m_vWall.push_back(pWall18);

	CObject* pWall19 = new CWall;
	pWall19->SetPos({ 630.f, 4260.f });
	pWall19->SetScale({ 800.f, 50.f });
	m_vWall.push_back(pWall19);

	CObject* pWall20 = new CWall;
	pWall20->SetPos({ 630.f, 4200.f });
	pWall20->SetScale({ 420.f, 90.f });
	m_vWall.push_back(pWall20);

	CObject* pWall21 = new CWall;
	pWall21->SetPos({ 1140.f, 4165.f });
	pWall21->SetScale({ 295.f, 915.f });
	m_vWall.push_back(pWall21);

	CObject* pWall22 = new CWall;
	pWall22->SetPos({ 630.f, 3810.f });
	pWall22->SetScale({ 40.f, 150.f });
	m_vWall.push_back(pWall22);

	CObject* pWall23 = new CWall;
	pWall23->SetPos({ 630.f, 3815.f });
	pWall23->SetScale({ 120.f, 70.f });
	m_vWall.push_back(pWall23);

	CObject* pWall24 = new CWall;
	pWall24->SetPos({ 1590.f, 4625.f });
	pWall24->SetScale({ 700.f, 50.f });
	m_vWall.push_back(pWall24);

	CObject* pWall25 = new CWall;
	pWall25->SetPos({ 1920.f, 4310.f });
	pWall25->SetScale({ 50.f, 600.f });
	m_vWall.push_back(pWall25);

	CObject* pWall26 = new CWall;
	pWall26->SetPos({ 1300.f, 4215.f });
	pWall26->SetScale({ 50.f, 65.f });
	m_vWall.push_back(pWall26);

	CObject* pWall27 = new CWall;
	pWall27->SetPos({ 1300.f, 4445.f });
	pWall27->SetScale({ 50.f, 65.f });
	m_vWall.push_back(pWall27);

	CObject* pWall28 = new CWall;
	pWall28->SetPos({ 1885.f, 4215.f });
	pWall28->SetScale({ 50.f, 65.f });
	m_vWall.push_back(pWall28);

	CObject* pWall29 = new CWall;
	pWall29->SetPos({ 1885.f, 4445.f });
	pWall29->SetScale({ 50.f, 65.f });
	m_vWall.push_back(pWall29);

	CObject* pWall30 = new CWall;
	pWall30->SetPos({ 1458.f, 4595.f });
	pWall30->SetScale({ 40.f, 65.f });
	m_vWall.push_back(pWall30);

	CObject* pWall31 = new CWall;
	pWall31->SetPos({ 1725.f, 4595.f });
	pWall31->SetScale({ 40.f, 65.f });
	m_vWall.push_back(pWall31);

	CObject* pWall32 = new CWall;
	pWall32->SetPos({ 1458.f, 4100.f });
	pWall32->SetScale({ 40.f, 65.f });
	m_vWall.push_back(pWall32);

	CObject* pWall33 = new CWall;
	pWall33->SetPos({ 1725.f, 4100.f });
	pWall33->SetScale({ 40.f, 65.f });
	m_vWall.push_back(pWall33);

	CObject* pWall34 = new CWall;
	pWall34->SetPos({ 1405.f, 4055.f });
	pWall34->SetScale({ 290.f, 90.f });
	m_vWall.push_back(pWall34);

	CObject* pWall35 = new CWall;
	pWall35->SetPos({ 1810.f, 4055.f });
	pWall35->SetScale({ 350.f, 90.f });
	m_vWall.push_back(pWall35);

	CObject* pWall36 = new CWall;
	pWall36->SetPos({ 2410.f, 3900.f });
	pWall36->SetScale({ 880.f, 400.f });
	m_vWall.push_back(pWall36);

	CObject* pWall37 = new CWall;
	pWall37->SetPos({ 2885.f, 3795.f });
	pWall37->SetScale({ 75.f, 100.f });
	m_vWall.push_back(pWall37);

	CObject* pWall38 = new CWall;
	pWall38->SetPos({ 2960.f, 3810.f });
	pWall38->SetScale({ 80.f, 55.f });
	m_vWall.push_back(pWall38);

	CObject* pWall39 = new CWall;
	pWall39->SetPos({ 3360.f, 3850.f });
	pWall39->SetScale({ 800.f, 60.f });
	m_vWall.push_back(pWall39);

	CObject* pWall40 = new CWall;
	pWall40->SetPos({ 3765.f, 3810.f });
	pWall40->SetScale({ 80.f, 55.f });
	m_vWall.push_back(pWall40);

	CObject* pWall41 = new CWall;
	pWall41->SetPos({ 3840.f, 3795.f });
	pWall41->SetScale({ 75.f, 100.f });
	m_vWall.push_back(pWall41);

	CObject* pWall42 = new CWall;
	pWall42->SetPos({ 3920.f, 3750.f });
	pWall42->SetScale({ 80.f, 100.f });
	m_vWall.push_back(pWall42);

	CObject* pWall43 = new CWall;
	pWall43->SetPos({ 3990.f, 3435.f });
	pWall43->SetScale({ 60.f, 700.f });
	m_vWall.push_back(pWall43);

	CObject* pWall44 = new CWall;
	pWall44->SetPos({ 3860.f, 3140.f });
	pWall44->SetScale({ 200.f, 120.f });
	m_vWall.push_back(pWall44);

	CObject* pWall45 = new CWall;
	pWall45->SetPos({ 3740.f, 3030.f });
	pWall45->SetScale({ 100.f, 100.f });
	m_vWall.push_back(pWall45);

	CObject* pWall46 = new CWall;
	pWall46->SetPos({ 3635.f, 2960.f });
	pWall46->SetScale({ 125.f, 100.f });
	m_vWall.push_back(pWall46);

	CObject* pWall47 = new CWall;
	pWall47->SetPos({ 3533.f, 2880.f });
	pWall47->SetScale({ 85.f, 100.f });
	m_vWall.push_back(pWall47);

	CObject* pWall48 = new CWall;
	pWall48->SetPos({ 3225.f, 2945.f });
	pWall48->SetScale({ 530.f, 130.f });
	m_vWall.push_back(pWall48);

	CObject* pWall49 = new CWall;
	pWall49->SetPos({ 2925.f, 3005.f });
	pWall49->SetScale({ 70.f, 90.f });
	m_vWall.push_back(pWall49);

	CObject* pWall50 = new CWall;
	pWall50->SetPos({ 2890.f, 3035.f });
	pWall50->SetScale({ 70.f, 90.f });
	m_vWall.push_back(pWall50);

	CObject* pWall51 = new CWall;
	pWall51->SetPos({ 2850.f, 3075.f });
	pWall51->SetScale({ 70.f, 90.f });
	m_vWall.push_back(pWall51);

	CObject* pWall52 = new CWall;
	pWall52->SetPos({ 2798.f, 2870.f });
	pWall52->SetScale({ 95.f, 1500.f });
	m_vWall.push_back(pWall52);

	CObject* pWall53 = new CWall;
	pWall53->SetPos({ 2365.f, 3385.f });
	pWall53->SetScale({ 780.f, 470.f });
	m_vWall.push_back(pWall53);

	CObject* pWall54 = new CWall;
	pWall54->SetPos({ 1885.f, 3230.f });
	pWall54->SetScale({ 200.f, 155.f });
	m_vWall.push_back(pWall54);

	CObject* pWall55 = new CWall;
	pWall55->SetPos({ 1945.f, 3095.f });
	pWall55->SetScale({ 85.f, 115.f });
	m_vWall.push_back(pWall55);

	CObject* pWall56 = new CWall;
	pWall56->SetPos({ 2005.f, 3145.f });
	pWall56->SetScale({ 40.f, 60.f });
	m_vWall.push_back(pWall56);

	CObject* pWall57 = new CWall;
	pWall57->SetPos({ 2735.f, 3145.f });
	pWall57->SetScale({ 40.f, 60.f });
	m_vWall.push_back(pWall57);

	CObject* pWall58 = new CWall;
	pWall58->SetPos({ 2735.f, 2185.f });
	pWall58->SetScale({ 40.f, 140.f });
	m_vWall.push_back(pWall58);

	CObject* pWall59 = new CWall;
	pWall59->SetPos({ 2005.f, 2185.f });
	pWall59->SetScale({ 40.f, 140.f });
	m_vWall.push_back(pWall59);

	CObject* pWall60 = new CWall;
	pWall60->SetPos({ 2450.f, 1730.f });
	pWall60->SetScale({ 530.f, 985.f });
	m_vWall.push_back(pWall60);

	CObject* pWall61 = new CWall;
	pWall61->SetPos({ 2050.f, 1730.f });
	pWall61->SetScale({ 100.f, 985.f });
	m_vWall.push_back(pWall61);

	CObject* pWall62 = new CWall;
	pWall62->SetPos({ 2372.f, 3000.f });
	pWall62->SetScale({ 228.f, 70.f });
	m_vWall.push_back(pWall62);

	CObject* pWall63 = new CWall;
	pWall63->SetPos({ 2277.f, 2975.f });
	pWall63->SetScale({ 40.f, 100.f });
	m_vWall.push_back(pWall63);

	CObject* pWall64 = new CWall;
	pWall64->SetPos({ 2466.f, 2975.f });
	pWall64->SetScale({ 40.f, 100.f });
	m_vWall.push_back(pWall64);

	CObject* pWall65 = new CWall;
	pWall65->SetPos({ 2372.f, 2410.f });
	pWall65->SetScale({ 228.f, 70.f });
	m_vWall.push_back(pWall65);

	CObject* pWall66 = new CWall;
	pWall66->SetPos({ 2277.f, 2425.f });
	pWall66->SetScale({ 40.f, 100.f });
	m_vWall.push_back(pWall66);

	CObject* pWall67 = new CWall;
	pWall67->SetPos({ 2466.f, 2425.f });
	pWall67->SetScale({ 40.f, 100.f });
	m_vWall.push_back(pWall67);

	CObject* pWall68 = new CWall;
	pWall68->SetPos({ 2360.f, 1010.f });
	pWall68->SetScale({ 60.f, 500.f });
	m_vWall.push_back(pWall68);

	CObject* pWall69 = new CWall;
	pWall69->SetPos({ 2140.f, 790.f });
	pWall69->SetScale({ 450.f, 120.f });
	m_vWall.push_back(pWall69);

	CObject* pWall70 = new CWall;
	pWall70->SetPos({ 1825.f, 500.f });
	pWall70->SetScale({ 250.f, 1000.f });
	m_vWall.push_back(pWall70);

	CObject* pWall71 = new CWall;
	pWall71->SetPos({ 1970.f, 1288.f });
	pWall71->SetScale({ 100.f, 100.f });
	m_vWall.push_back(pWall71);

	CObject* pWall72 = new CWall;
	pWall72->SetPos({ 1825.f, 1185.f });
	pWall72->SetScale({ 250.f, 200.f });
	m_vWall.push_back(pWall72);

	CObject* pWall73 = new CWall;
	pWall73->SetPos({ 870.f, 1315.f });
	pWall73->SetScale({ 1800.f, 100.f });
	m_vWall.push_back(pWall73);

	CObject* pWall74 = new CWall;
	pWall74->SetPos({ 3084.f, 3270.f });
	pWall74->SetScale({ 475.f, 60.f });
	m_vWall.push_back(pWall74);

	CObject* pWall75 = new CWall;
	pWall75->SetPos({ 3288.f, 3132.f });
	pWall75->SetScale({ 60.f, 300.f });
	m_vWall.push_back(pWall75);

	for (int i = 0; i < m_vWall.size(); i++)
	{
		m_vWall[i]->SetPos(m_vWall[i]->GetPos() * 5.f / 4.f);
		m_vWall[i]->SetScale(m_vWall[i]->GetScale() * 5.f / 4.f);
		CSceneManager::Get()->AddObject(m_vWall[i], OBJECT_TYPE::WALL);
	}
}