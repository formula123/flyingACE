#ifndef  _APP_DELEGATE_H_
#define  _APP_DELEGATE_H_

#include "cocos2d.h"
#include "GameBackgroundLayer.h"
#include "PlaneLayer.h"
#include "BulletLayer.h"
#include "EnemyLayer.h"

/**
@brief    The cocos2d Application.

The reason for implement as private inheritance is to hide some interface call by Director.
*/
class  AppDelegate : private cocos2d::Application
{
public:
    AppDelegate();
    virtual ~AppDelegate();

    virtual void initGLContextAttrs();

    /**
    @brief    Implement Director and Scene init code here.
    @return true    Initialize success, app continue.
    @return false   Initialize failed, app terminate.
    */
    virtual bool applicationDidFinishLaunching();

    /**
    @brief  The function be called when the application enter background
    @param  the pointer of the application
    */
    virtual void applicationDidEnterBackground();

    /**
    @brief  The function be called when the application enter foreground
    @param  the pointer of the application
    */
    virtual void applicationWillEnterForeground();
private:
    cocos2d::SpriteFrameCache* textureCache = cocos2d::SpriteFrameCache::getInstance();
    cocos2d::AnimationCache* animationCache = cocos2d::AnimationCache::getInstance();
};

#endif // _APP_DELEGATE_H_

