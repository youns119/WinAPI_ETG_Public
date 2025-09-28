#include "pch.h"
#include "SoundManager.h"

CSoundManager::CSoundManager()
{
	ZeroMemory(&m_pChannelArr, sizeof(FMOD::Channel*) * (UINT)CHANNELID::MAXCHANNEL);
	m_pSystem = nullptr;
}

CSoundManager::~CSoundManager()
{
	Release();
}

void CSoundManager::Init()
{
	FMOD::System_Create(&m_pSystem);
	m_pSystem->init(64, FMOD_INIT_NORMAL, nullptr);
	LoadSoundFile();
}

void CSoundManager::Release()
{
	for (auto& Mypair : m_mapSound)
	{
		delete[] Mypair.first;
		Mypair.second->release();
	}
	m_mapSound.clear();

	m_pSystem->close();
	m_pSystem->release();
}

void CSoundManager::PlaySound(const TCHAR* _pSoundKey, CHANNELID _eID, float _fVolume)
{
	map<const TCHAR*, FMOD::Sound*>::iterator iter;

	// iter = find_if(m_mapSound.begin(), m_mapSound.end(), CTag_Finder(_pSoundKey));
	iter = find_if(m_mapSound.begin(), m_mapSound.end(),
		[&](auto& iter)->bool
		{
			return !lstrcmp(_pSoundKey, iter.first);
		});

	if (iter == m_mapSound.end())
		return;

	FMOD_BOOL bPlay = FALSE;

	//bool isPlaying = false;
	//if (m_pChannelArr[(UINT)_eID])
	//{
	//	m_pChannelArr[(UINT)_eID]->isPlaying(&isPlaying);
	//	if (isPlaying)
	//	{
	//		m_pChannelArr[(UINT)_eID]->stop();
	//	}
	//}

	m_pSystem->playSound(iter->second, nullptr, false, &m_pChannelArr[(UINT)_eID]);
	//m_pSystem->playSound(iter->second, nullptr, true, &m_pChannelArr[(UINT)_eID]);
	m_pChannelArr[(UINT)_eID]->setVolume(_fVolume);

	m_pSystem->update();
}

void CSoundManager::PlayBGM(const TCHAR* _pSoundKey, float _fVolume)
{
	map<const TCHAR*, FMOD::Sound*>::iterator iter;

	// iter = find_if(m_mapSound.begin(), m_mapSound.end(), CTag_Finder(_pSoundKey));
	iter = find_if(m_mapSound.begin(), m_mapSound.end(), [&](auto& iter)->bool
		{
			return !lstrcmp(_pSoundKey, iter.first);
		});

	if (iter == m_mapSound.end())
		return;

	m_pSystem->playSound(iter->second, nullptr, false, &m_pChannelArr[(UINT)CHANNELID::SOUND_BGM]);
	m_pChannelArr[(UINT)CHANNELID::SOUND_BGM]->setMode(FMOD_LOOP_NORMAL);
	m_pChannelArr[(UINT)CHANNELID::SOUND_BGM]->setVolume(_fVolume);

	m_pSystem->update();
}

void CSoundManager::PlayBGMOnce(const TCHAR* _pSoundKey, CHANNELID _eID, float _fVolume)
{
	map<const TCHAR*, FMOD::Sound*>::iterator iter;

	// iter = find_if(m_mapSound.begin(), m_mapSound.end(), CTag_Finder(_pSoundKey));
	iter = find_if(m_mapSound.begin(), m_mapSound.end(), [&](auto& iter)->bool
		{
			return !lstrcmp(_pSoundKey, iter.first);
		});

	if (iter == m_mapSound.end())
		return;

	bool isPlaying = false;
	if (m_pChannelArr[(UINT)_eID])
	{
		m_pChannelArr[(UINT)_eID]->isPlaying(&isPlaying);
		if (isPlaying)
		{
			m_pChannelArr[(UINT)_eID]->stop();
		}
	}

	m_pSystem->playSound(iter->second, nullptr, false, &m_pChannelArr[(UINT)_eID]);
	m_pChannelArr[(UINT)_eID]->setVolume(_fVolume);

	m_pSystem->update();
}

void CSoundManager::StopSound(CHANNELID _eID)
{
	if (m_pChannelArr[(UINT)_eID])
	{
		m_pChannelArr[(UINT)_eID]->stop();
	}
}

void CSoundManager::StopAll()
{
	for (int i = 0; i < (UINT)CHANNELID::MAXCHANNEL; ++i)
		if (m_pChannelArr[i])
			m_pChannelArr[i]->stop();
}

void CSoundManager::SetChannelVolume(CHANNELID _eID, float _fVolume)
{
	if (m_pChannelArr[(UINT)_eID])
		m_pChannelArr[(UINT)_eID]->setVolume(_fVolume);

	m_pSystem->update();
}

void CSoundManager::LoadSoundFile()
{
	// _finddata_t : <io.h>에서 제공하며 파일 정보를 저장하는 구조체
	_finddata_t fd;

	// _findfirst : <io.h>에서 제공하며 사용자가 설정한 경로 내에서 가장 첫 번째 파일을 찾는 함수
	intptr_t handle = _findfirst("../Debug/content/sound/*.*", &fd);

	if (handle == -1)
		return;

	int iResult = 0;

	char szCurPath[128] = "../Debug/content/sound/";	 // 상대 경로
	char szFullPath[128] = "";

	while (iResult != -1)
	{
		strcpy_s(szFullPath, szCurPath);

		// "../Sound/" + "Success.wav"
		strcat_s(szFullPath, fd.name);
		// "../Sound/Success.wav"

		FMOD::Sound* pSound = nullptr;

		FMOD_RESULT eRes = m_pSystem->createSound(szFullPath, FMOD_DEFAULT, 0, &pSound);

		if (eRes == FMOD_OK)
		{
			int iLength = strlen(fd.name) + 1;

			TCHAR* pSoundKey = new TCHAR[iLength];
			ZeroMemory(pSoundKey, sizeof(TCHAR) * iLength);

			// 아스키 코드 문자열을 유니코드 문자열로 변환시켜주는 함수
			MultiByteToWideChar(CP_ACP, 0, fd.name, -1, pSoundKey, static_cast<int>(iLength));

			m_mapSound.emplace(pSoundKey, pSound);
		}
		//_findnext : <io.h>에서 제공하며 다음 위치의 파일을 찾는 함수, 더이상 없다면 -1을 리턴
		iResult = _findnext(handle, &fd);
	}

	m_pSystem->update();

	_findclose(handle);
}