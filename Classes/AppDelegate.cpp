#include "AppDelegate.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() {
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs() {
	//set OpenGL context attributions,now can only set six attributions:
	//red,green,blue,alpha,depth,stencil
	GLContextAttrs glContextAttrs = { 8, 8, 8, 8, 24, 8 };

	GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
	// initialize director
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	if (!glview) {
		glview = GLViewImpl::createWithRect("Flying ACE", Rect(0, 0, 720, 1280));
		director->setOpenGLView(glview);
	}

	// turn on display FPS
	director->setDisplayStats(true);

	// set FPS. the default value is 1.0/60 if you don't call this
	director->setAnimationInterval(1.0 / 60);

	cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile("texture.plist");

	Vector<SpriteFrame*> explosionAnimationVector;
	for (int i = 0; i < 9; i++){
		    char animitionFileName[128] = {0};
		    sprintf(animitionFileName, "explosion%02d.png", i+1);
		    SpriteFrame* fm = SpriteFrameCache::getInstance()->getSpriteFrameByName(animitionFileName);
		    explosionAnimationVector.pushBack(fm);
		}
	Animation* explosionAnimation = Animation::createWithSpriteFrames(explosionAnimationVector, 0.5f / 9.0f, 1);
	AnimationCache::getInstance()->addAnimation(explosionAnimation,"explosion");

	// create a scene. it's an autorelease object
	Scene* gameScene = Scene::create();

	GameBackgroundLayer* backgroundLayer = GameBackgroundLayer::getInstance();
	gameScene->addChild(backgroundLayer);
	UFOLayer* ufoLayer = UFOLayer::getInstance();
	gameScene->addChild(ufoLayer);
	BulletLayer* bulletLayer = BulletLayer::getInstance();
	gameScene->addChild(bulletLayer);
	EnemyLayer* enemyLayer = EnemyLayer::getInstance();
	gameScene->addChild(enemyLayer);
	PlaneLayer* planeLayer = PlaneLayer::getInstance();
	gameScene->addChild(planeLayer);
	ControlLayer* controlLayer = ControlLayer::getInstance();
	gameScene->addChild(controlLayer);

	// run
	director->runWithScene(gameScene);

	return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
	Director::getInstance()->stopAnimation();

	// if you use SimpleAudioEngine, it must be pause
	// SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
	Director::getInstance()->startAnimation();

	// if you use SimpleAudioEngine, it must resume here
	// SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
