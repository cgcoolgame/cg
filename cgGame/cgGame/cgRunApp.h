
#ifndef cgRunApp_h__
#define cgRunApp_h__
#include "CGGameApp.h"
#include "cgSingleton.h"
#include "cgGameMessageListenerManager.h"
#include "cgActor.h"

typedef struct
{
	unsigned idRegion;
	cgRectF rectBound;
	cgGameSpiritPtr spImage;
}cgRunMapRegion;
typedef std::map<unsigned, cgRunMapRegion> cgSceneRegionList;

class cgRunApp:
	public cgGameApp,
	public cgSingleton<cgRunApp>,
	public cgGameMessageListener
{
public:
	cgRunApp(void);
	~cgRunApp(void);

	virtual bool OnGameMessage(cgGameMessage msg, void * pData, int nLen);

protected:
	virtual bool DoInitGame();
	virtual bool DoProcessRawMessage(UINT message, WPARAM wParam, LPARAM lParam);
	virtual void DoUpdateGame(float fDeltaTime);
	virtual void DoRenderGame();

private:
	cgActorPtr LoadRole();

	void CheckVisibleRegion();
	void CheckLoadMap(int x, int y);
	bool CheckLoadLine(int x, int y);
	bool CheckLoadRegion(int x, int y);
	cgGameSpiritPtr FindRegion(int x, int y);

private:

	cgActorPtr m_spRole;

	cgGameObjectPtr m_spMap;
	cgGameObjectPtr m_spWorld;

	cgSceneRegionList m_kRegionList;
};

unsigned cgRunAppMakeRegionID(int x, int y);
#endif // cgRunApp_h__

