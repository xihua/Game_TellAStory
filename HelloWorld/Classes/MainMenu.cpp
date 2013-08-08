#include "pch.h"

#include "MainMenu.h"
#include "GameScene.h"
#include "ShelfScene.h"
#include "AppDelegate.h"

#include "CCCommon.h"
#include "BasicLoader.h"
#include <CCParticleExamples.h>
#include <vector>
#include <time.h>
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace Windows::Foundation;
using namespace Windows::Devices::Sensors;
using namespace CocosDenshion;

HelloWorld::HelloWorld()
{

}
HelloWorld::~HelloWorld()
{

}

CCScene* HelloWorld::scene()
{
	CCScene * scene = NULL;
	do 
	{		// 'scene' is an autorelease object
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		HelloWorld *layer = HelloWorld::create();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	bool bRet = false;

	do 
	{
		if ( !CCLayer::init() )
		{
			break;
		}

		//显示HelloWorld
		//CCLabelTTF* pLabel = CCLabelTTF::create("故事书", "msyh", 24);
		CCSize size = CCDirector::sharedDirector()->getWinSize();
		//pLabel->setPosition( ccp(size.width * 0.5, size.height * 0.5) );
		//pLabel->setColor(ccc3(160, 80, 5));
		//this->addChild(pLabel, 10);

		//添加背景
		CCSprite *b = CCSprite::create("bg.png");
		b->setPosition(ccp(size.width * 0.5, size.height * 0.5));	
		b->setScale(AppDelegate::getResRate());
		this->addChild(b);

		//添加背景音乐
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Assets\\background.wav", true);//绝对路径

		//添加按钮
		CCSprite* cplay=CCSprite::create("PLAY_btn.png");
		CCSprite* cplay1=CCSprite::create("PLAY_btn2.png");
		CCMenuItemSprite* mplay=CCMenuItemSprite::create(cplay,cplay1,NULL,this,menu_selector(HelloWorld::playCallback));
		CCMenu* menu=CCMenu::createWithItem(mplay);	
		menu->setPosition(ccp(size.width * 0.8, size.height * 0.2));
        this->addChild(menu);

		//heart动画
		CCSprite *pSprite;
		CCSpriteFrameCache *cache;
		cache = CCSpriteFrameCache::sharedSpriteFrameCache();
		cache->addSpriteFramesWithFile("ani.plist", "ani.png");
		CCArray *animFrames = new CCArray(7); 
		CCSpriteFrame *frame = cache->spriteFrameByName("heart_0.png"); 
		animFrames->addObject(frame);
		frame = cache->spriteFrameByName("heart_1.png"); 
		animFrames->addObject(frame);
		frame = cache->spriteFrameByName("heart_3.png"); 
		animFrames->addObject(frame);
		frame = cache->spriteFrameByName("heart_2.png"); 
		animFrames->addObject(frame);
		frame = cache->spriteFrameByName("heart_4.png"); 
		animFrames->addObject(frame);
		frame = cache->spriteFrameByName("heart_5.png"); 
		animFrames->addObject(frame);
		frame = cache->spriteFrameByName("heart_6.png"); 
		animFrames->addObject(frame);
		CCAnimation *animation = CCAnimation::createWithSpriteFrames(animFrames,0.3f);
		pSprite = CCSprite::createWithSpriteFrameName("heart_0.png");
		this->addChild(pSprite,80);
		pSprite->setPosition(ccp(size.width*0.4, size.height*0.6));

		pSprite->runAction(CCRepeatForever::create(CCAnimate::create(animation)));

		setTouchEnabled(true);

		bRet = true;
	} while (0);

	return bRet;
}

void HelloWorld::ccTouchesBegan(CCSet* touches, CCEvent *event)
{

}

void HelloWorld::ccTouchesMoved(CCSet* touches, CCEvent* event)
{

}

// cpp with cocos2d-x
void HelloWorld::ccTouchesEnded(CCSet* touches, CCEvent* event)
{

}

//void HelloWorld::registerWithTouchDispatcher()
//{
	// CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this,0,true);
	//CCTouchDispatcher::sharedDispatcher()->addStandardDelegate(this,0);
//}

void HelloWorld::playCallback(CCObject* sender)
{
	//切换到下一个场景
	//CCDirector::sharedDirector()->replaceScene(CCTransitionMoveInR::create(1,ShelfScene::scene()));
	CCDirector::sharedDirector()->replaceScene(ShelfScene::scene());
}
