#include "StdAfx.h"
#include "cgTxtDataReader.h"

cgTxtRecord::cgTxtRecord()
{
	m_uFieldNum = 0;
	m_uFieldBuffLen = CG_DEFAULT_TEXT_FIELD_NUM;
	m_ppFieldList = new const char *[m_uFieldBuffLen];
}

cgTxtRecord::~cgTxtRecord()
{
	delete[] m_ppFieldList;
	m_uFieldBuffLen = 0;
	m_uFieldNum = 0;
}

void cgTxtRecord::AddField( const char * pcField )
{
	if (m_uFieldNum >= m_uFieldBuffLen)
		EnlargeBuffer(m_uFieldBuffLen);

	m_ppFieldList[m_uFieldNum++] = pcField;
}

const char * cgTxtRecord::GetField( unsigned index )const
{
	if (index < m_uFieldNum)
		return m_ppFieldList[index];

	return "";
}

unsigned cgTxtRecord::GetFieldNum()const
{
	return m_uFieldNum;
}

void cgTxtRecord::Clear()
{
	m_uFieldNum = 0;
}

void cgTxtRecord::EnlargeBuffer( unsigned uNum )
{
	const char ** ppList = new const char*[m_uFieldBuffLen+uNum];
	memcpy(ppList, m_ppFieldList, sizeof(char*)*m_uFieldBuffLen);

	delete[] m_ppFieldList;

	m_ppFieldList = ppList;

	m_uFieldBuffLen += uNum;
}

// --------------------------------------------------------------------------------

cgTxtDataReader::cgTxtDataReader(void)
{	
	m_pBuffer = NULL;
	m_uBufferLen = 0;
	m_uFileDataLen = 0;
	m_uBuffOffset = 0;
}


cgTxtDataReader::~cgTxtDataReader(void)
{
	Close();
}

void cgTxtDataReader::Close()
{
	if (m_pBuffer)
		delete [] m_pBuffer;
}


bool cgTxtDataReader::Initialize()
{
	return true;
}

// ------------------------------------------------------------------------------------

bool cgTxtDataReader::Open( const char * path )
{
	FILE * pkFile = fopen(path, "rb");
	if (!pkFile)
		return false;
	
	fseek(pkFile, 0, SEEK_END);
	m_uFileDataLen = ftell(pkFile);
	fseek(pkFile, 0, SEEK_SET);

	EnsureEnouphBuffer();

	fread(m_pBuffer, m_uFileDataLen, 1, pkFile);
	fclose(pkFile);

	m_pBuffer[m_uFileDataLen] = NULL;
	m_uBuffOffset = 0;

	return true;
}

void cgTxtDataReader::EnsureEnouphBuffer()
{
	if (m_uFileDataLen >= m_uBufferLen)
	{
		if (m_pBuffer)
			delete[] m_pBuffer;

		m_uBufferLen = m_uFileDataLen+1;
		m_pBuffer = new char[m_uBufferLen];
	}
}

unsigned cgTxtDataReader::GetBufferLen()
{
	return m_uBufferLen;
}

unsigned cgTxtDataReader::GetFileDataLen()
{
	return m_uFileDataLen;
}


const cgTxtRecord * cgTxtDataReader::Next()
{
	// ���
	m_kRecord.Clear();

	char * pFieldStart = NULL;

	bool bEndRecord = false;	 // ������¼�Ƿ����
	bool bInStr = false;		// �Ƿ��������м�
	bool bEndField = false;	// ���ֶ��Ƿ����
	bool bNormalChar = false;	// �ǲ���һ����ͨ���ַ���

	// ��m_uBuffOffset == m_uFileDataLen ʱ��û����
	while (m_uBuffOffset <= m_uFileDataLen && !bEndRecord )
	{
		bEndField = false;	// ���ֶ��Ƿ����
		bNormalChar = false;	// �ǲ���һ����ͨ���ַ���

		switch (m_pBuffer[m_uBuffOffset])
		{
		case '\n':
		case '\r':
		case NULL:
			{
				if (m_kRecord.GetFieldNum() >0 || pFieldStart)
					bEndRecord = true;
			}break;
		case ' ':
		case '\t':
			{
				// ����ֶ�û��ʼ�Ͳ���
				// ����Ѿ���ʼ�ˣ������������ͽ���һ���ֶ�
				bEndField = !bInStr;

				// ����������м䣬��ֻ��Ҫ��������һ����ͨ���ַ�
				bNormalChar = bInStr;
				
			}break;
		case '\'':
		case '\"':
			{
				// �������ţ��ض��᳢�Խ���һ���ֶ�
				bEndField = true;

				if (bInStr)
				{
					// ��������Ž����ˣ�pFieldStart ���� NULL����˵������һ������Ϊֹ�Ŀ��ַ���
					// �͵�ȡ��
					if (!pFieldStart)
						pFieldStart = m_pBuffer+m_uBuffOffset;
				}

				bInStr = !bInStr;

			}break;

		default:
				bNormalChar = true;
			break;
		}

		if (bNormalChar)
		{
			if (!pFieldStart)
				pFieldStart = m_pBuffer+m_uBuffOffset;

		}else if ((bEndField || bEndRecord) && pFieldStart)
		{
			m_pBuffer[m_uBuffOffset] = NULL;
			m_kRecord.AddField(pFieldStart);
			pFieldStart = NULL;
		}

		++m_uBuffOffset;
	}

	return m_kRecord.GetFieldNum()>0?&m_kRecord:NULL;
}

