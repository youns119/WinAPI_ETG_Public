#include "pch.h"
#include "PathManager.h"

#include "Main.h"

CPathManager::CPathManager()
	: m_szRelativePath{}
{
}

CPathManager::~CPathManager()
{
}

void CPathManager::Init()
{
	GetCurrentDirectory(255, m_szRelativePath);

	int iLength = (int)wcslen(m_szRelativePath);

	for (int i = iLength - 1; i >= 0; i--)
		if ('\\' == m_szRelativePath[i])
		{
			m_szRelativePath[i] = '\0';
			break;
		}

#ifdef _DEBUG
	wcscat_s(m_szRelativePath, 255, L"\\Debug\\content\\");
#else
	wcscat_s(m_szRelativePath, 255, L"\\Release\\content\\");
#endif
}