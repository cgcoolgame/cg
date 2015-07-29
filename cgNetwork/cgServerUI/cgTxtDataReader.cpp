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
	// 清空
	m_kRecord.Clear();

	char * pFieldStart = NULL;

	bool bEndRecord = false;	 // 本条记录是否结束
	bool bInStr = false;		// 是否处于引号中间
	bool bEndField = false;	// 本字段是否结束
	bool bNormalChar = false;	// 是不是一个普通的字符？

	// 当m_uBuffOffset == m_uFileDataLen 时，没问题
	while (m_uBuffOffset <= m_uFileDataLen && !bEndRecord )
	{
		bEndField = false;	// 本字段是否结束
		bNormalChar = false;	// 是不是一个普通的字符？

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
				// 如果字段没开始就不管
				// 如果已经开始了，碰到这俩个就结束一个字段
				bEndField = !bInStr;

				// 如果在引号中间，则只需要把他当作一个普通的字符
				bNormalChar = bInStr;
				
			}break;
		case '\'':
		case '\"':
			{
				// 遇到引号，必定会尝试结束一个字段
				bEndField = true;

				if (bInStr)
				{
					// 如果是引号结束了，pFieldStart 还是 NULL，则说明这是一个特意为止的空字符串
					// 就地取材
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

