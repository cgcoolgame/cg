
#ifndef cgRichCharSpawner_h__
#define cgRichCharSpawner_h__

#include <map>
#include "cgUIRichChar.h"
#include "cgStringDef.h"

class cgUIRichChar;

struct cgUIRichCharCreator
{
	virtual const cgString& GetTypeString() = NULL;
	virtual cgUIRichChar * Create() = NULL;
};

#define MAX_UI_RICH_CHAR_CREATOR_NUM 128

class cgUIRichCharSpawner
{
public:

	static void Register( cgUIRichCharCreator * pCreator);
	static cgUIRichChar * Spawn(const cgString& strType);

protected:
	static cgUIRichCharCreator * FindCreator(const cgString& strType);

protected:
	static int ms_CreatorNum;
	static cgUIRichCharCreator* ms_kCreatorList[MAX_UI_RICH_CHAR_CREATOR_NUM];
};

template<typename T>
class cgUIRichCharCreatorT:
	public cgUIRichCharCreator
{
public:
	cgUIRichCharCreatorT(const cgString& strType)
	{
		m_strType = strType;
		cgUIRichCharSpawner::Register(this);
	}

	virtual const cgString& GetTypeString()
	{
		return m_strType;
	}
	virtual cgUIRichChar * Create()
	{
		return new T;
	}
protected:
	cgString m_strType;
};


#define REGISTE_RICHCHAR_CREATOR(TypeString,Class) \
	static cgUIRichCharCreatorT<Class> Class##_Creator(TypeString);

#endif // cgRichCharSpawner_h__
