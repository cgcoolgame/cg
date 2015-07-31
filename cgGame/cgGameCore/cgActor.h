
#ifndef cgAnimationManager_h__
#define cgAnimationManager_h__

// 一个动作管理器
// 一个角色往往会有很多组动画组成
// 每个动画有不同的标识，在游戏中根据
// 需要播放对应的动画序列帧

#include "cgAnimation.h"
#include <map>

// 常用的角色动作枚举
enum cgActorAction
{
	cgActorAction_Idle,			// 默认空闲状态，站立
	cgActorAction_Walk,			// 行走，慢走
	cgActorAction_Run,			// 跑步，快走
	cgActorAction_SitDown,		// 坐下(过程）
	cgActorAction_Sit,			// 坐下（状态）
	cgActorAction_Jump,			// 跳
	cgActorAction_Fly,			// 飞行
	cgActorAction_Attack,		// 攻击，默认攻击动作
	cgActorAction_Hurt,			// 被攻击
	cgActorAction_Sing,			// 默认吟唱动作
	cgActorAction_Cast,			// 默认释放动作，紧接吟唱动作，也可做技能释放动作
	cgActorAction_Die,			// 死亡（过程）
	cgActorAction_Dead,			// 死亡（躺尸）

};


typedef std::map<cgID , cgAnimationPtr> cgAnimationPtrMap;

class cgActor:
	public cgGameObject
{
public:
	cgActor(void);
	~cgActor(void);

	// 添加一组动作
	void AddAnimation(cgAnimationPtr spAnimation);
	cgAnimationPtr GetAnimation(cgID id);

	// 设置当前的面向
	void SetDirection(cgDirectionEnum enmDir);
	cgDirectionEnum GetDirection();

	// 设置当前的动作
	void SetCurAnimation(cgID id);
	cgAnimationPtr GetCurAnimation();

protected:
	cgAnimationPtrMap m_kAnimationMap;
	cgAnimationPtr m_spCurAnimation;
	cgDirectionEnum m_enmDir;
};

typedef cgSmartPointer<cgActor> cgActorPtr;
#endif // cgAnimationManager_h__
