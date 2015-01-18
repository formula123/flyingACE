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

	textureCache->addSpriteFramesWithFile("texture.plist");
	animationCache->addAnimationsWithFile("texture.plist");



	auto animition = Animation::create();
	animition->addSpriteFrameWithFileName("explosion01.png");
	animition->addSpriteFrameWithFileName("explosion02.png");
	animition->addSpriteFrameWithFileName("explosion03.png");
	animition->addSpriteFrameWithFileName("explosion04.png");
	animition->addSpriteFrameWithFileName("explosion05.png");
	animition->addSpriteFrameWithFileName("explosion06.png");
	animition->addSpriteFrameWithFileName("explosion07.png");
	animition->addSpriteFrameWithFileName("explosion08.png");
	animition->addSpriteFrameWithFileName("explosion09.png");

	animationCache->addAnimation(animition,"explosion");

	// create a scene. it's an autorelease object
	Scene* gameScene = Scene::create();

	GameBackgroundLayer* backgroundLayer = GameBackgroundLayer::create();
	gameScene->addChild(backgroundLayer);
	PlaneLayer* planeLayer = PlaneLayer::getInstance();
	gameScene->addChild(planeLayer);
	BulletLayer* bulletLayer = BulletLayer::getInstance();
	gameScene->addChild(bulletLayer);
	EnemyLayer* enemyLayer = EnemyLayer::create();
	gameScene->addChild(enemyLayer);

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
