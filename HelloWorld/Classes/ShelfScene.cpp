#include "pch.h"

#include "ShelfScene.h"
#include "GameScene.h"
#include "CCCommon.h"
#include "BasicLoader.h"
#include <CCParticleExamples.h>
#include <vector>
#include <time.h>
#include "SimpleAudioEngine.h"
#include"AppDelegate.h"


using namespace cocos2d;
using namespace Windows::Foundation;
using namespace Windows::Devices::Sensors;
using namespace CocosDenshion;


ShelfScene::~ShelfScene()
{
}

ShelfScene::ShelfScene()
{

}

CCScene* ShelfScene::scene()
{
	CCScene * scene = NULL;
	do 
	{		// 'scene' is an autorelease object
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		ShelfScene *layer = ShelfScene::create();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool ShelfScene::init()
{
	bool bRet = false;

	do 
	{
		if ( !CCLayer::init() )
		{
			break;
		}
		//SimpleAudioEngine::sharedEngine()->stopAllEffects();

		CCString * pString,*SoundString;
		CCSize size=CCDirector::sharedDirector()->getWinSize();	
		
		SimpleAudioEngine::sharedEngine()->playEffect("Assets\\open.wav");
		SimpleAudioEngine::sharedEngine()->setEffectsVolume(1);

		//按钮的载入
		pString  =CCString ::createWithFormat("shelf.plist");
		CCDictionary* plistDic= CCDictionary::createWithContentsOfFile(pString->getCString());
		CCDictionary* Dic = (CCDictionary*)plistDic->objectForKey("button");

		CCArray* picture_array = (CCArray*)Dic->objectForKey("button_img");
		CCArray* point_array = (CCArray*)Dic->objectForKey("button_pos");
		CCArray* BookId_array = (CCArray*)Dic->objectForKey("button_fun");

		for (int i=0;i<picture_array->count();i++)
		{
			CCString* pi_string = (CCString*)picture_array->objectAtIndex(i);//获取图片地址
			CCSprite* btn_sprite = CCSprite::create(pi_string->getCString());
			CCSprite* btn_sprite1 = CCSprite::create(pi_string->getCString());

			CCString* BookId_string = (CCString*)BookId_array->objectAtIndex(i);
			int BookId = BookId_string->intValue();//获取BookId
			CCMenuItemSprite* mplay=new CCMenuItemSprite();
			mplay=CCMenuItemSprite::create(btn_sprite,btn_sprite1,NULL,this,menu_selector(ShelfScene::goToBook));
			CCMenu* menu=CCMenu::createWithItem(mplay);

			CCString* point_string = (CCString*)point_array->objectAtIndex(i);//获取图片坐标
			CCPoint point = CCPointFromString(point_string->getCString());
			menu->setPosition(ccp(size.width*point.x,size.height*point.y));
			menu->setTouchEnabled(true);
			this->addChild(menu,60);
		}	


		//图片的载入
//		plistDic = CCDictionary::createWithContentsOfFile(pString->getCString());

		picture_array = (CCArray*)plistDic->objectForKey("picture");
		point_array = (CCArray*)plistDic->objectForKey("point");
		//CCArray* scale_array = (CCArray*)plistDic->objectForKey("scale");
		for (int i=0;i<picture_array->count();i++)
		{
			CCString* pi_string = (CCString*)picture_array->objectAtIndex(i);
			CCSprite* sprite = CCSprite::create(pi_string->getCString());

			CCString* point_string = (CCString*)point_array->objectAtIndex(i);
			CCPoint point = CCPointFromString(point_string->getCString());
			sprite->setPosition(ccp(size.width*point.x,size.height*point.y));
		
			//CCString* scale_string = (CCString*)scale_array->objectAtIndex(i);
			//int scale = scale_string->intValue();
			//sprite->setScale(scale);
			sprite->setScale(AppDelegate::getResRate());

			this->addChild(sprite,10);
		}	
		
		//动画载入
		CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
		cache->addSpriteFramesWithFile("gameart.plist", "gameart.png");
		Dic = (CCDictionary*)plistDic->objectForKey("animation");
		picture_array = (CCArray*)Dic->objectForKey("ani_img");
		CCArray *animFrames = new CCArray(picture_array->count()); 
		for (int i=0;i<picture_array->count();i++)
		{
			CCString* pi_string = (CCString*)picture_array->objectAtIndex(i);
			CCSpriteFrame *frame = cache->spriteFrameByName(pi_string->getCString()); 
			animFrames->addObject(frame);
		}	

		CCAnimation *animation = CCAnimation::createWithSpriteFrames(animFrames,0.1f);
		CCString* pi_string = (CCString*)picture_array->objectAtIndex(0);
		CCSprite *pSprite = CCSprite::createWithSpriteFrameName(pi_string->getCString());
		this->addChild(pSprite,20);
		pSprite->setPosition(ccp(size.width*0.8, size.height*0.15));
		pSprite->runAction(CCRepeatForever::create(CCAnimate::create(animation)));


		CCMoveTo* MoveToM= CCMoveTo::create(1.0f,ccp(size.width*0.5, size.height*.15));
		CCDelayTime *waiting=CCDelayTime::create(1);  
		CCMoveTo* MoveToL= CCMoveTo::create(1.0f,ccp(size.width*0.2, size.height*.15));
		CCFlipX * fX=CCFlipX::create(true); 
		CCMoveTo* MoveToR= CCMoveTo::create(1.0f,ccp(size.width*0.8, size.height*.15));
		CCFlipX * fX2=CCFlipX::create(false);

		CCFiniteTimeAction* action= CCSequence::create(MoveToM,waiting,MoveToL,fX,MoveToM,waiting,MoveToR,fX2,NULL);  //动画序列
		CCActionInterval* actionMove=CCRepeatForever::create((CCActionInterval*)action);  
		pSprite->runAction(actionMove);


		setTouchEnabled(false);//禁止触摸

		bRet = true;
	} while (0);

	return bRet;
}

void ShelfScene::goToBook(CCObject *sender){
	SimpleAudioEngine::sharedEngine()->unloadEffect("Assets\\open.wav");AppDelegate::setContorlNo(1);
	CCDirector::sharedDirector()->replaceScene(CCTransitionJumpZoom::create(1,GameScene::scene()));
}

void ShelfScene::ccTouchesBegan(CCSet* touches, CCEvent *event)
{

}

void ShelfScene::ccTouchesMoved(CCSet* touches, CCEvent* event)
{

}

// cpp with cocos2d-x
void ShelfScene::ccTouchesEnded(CCSet* touches, CCEvent* event)
{

}

//void ShelfScene::registerWithTouchDispatcher()
//{
//    CCDirector* pDirector = CCDirector::sharedDirector();
//    pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
//}
