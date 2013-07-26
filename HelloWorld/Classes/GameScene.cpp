/*
* cocos2d-x   http://www.cocos2d-x.org
*
* Copyright (c) 2010-2011 - cocos2d-x community
* 
* Portions Copyright (c) Microsoft Open Technologies, Inc.
* All Rights Reserved
* 
* Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. 
* You may obtain a copy of the License at 
* 
* http://www.apache.org/licenses/LICENSE-2.0 
* 
* Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an 
* "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
* See the License for the specific language governing permissions and limitations under the License.
*/

#include "pch.h"

#include "GameScene.h"
#include "EndStory.h"
#include "ShelfScene.h"

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


static int SceneNo=0;
const int PageNo=15;
GameScene::~GameScene()
{
	//SceneNo=-1;//-1;
}

GameScene::GameScene()
{

}

CCScene* GameScene::scene()
{
	CCScene * scene = NULL;
	do 
	{		// 'scene' is an autorelease object
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		GameScene *layer = GameScene::create();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
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

		pString  =CCString ::createWithFormat("story\\sceneOrder\\scene%d.plist",SceneNo);
		SoundString  =CCString ::createWithFormat("Assets\\story\\audio\\%d.wav",SceneNo);
		
		SoundId=SimpleAudioEngine::sharedEngine()->playEffect(SoundString->getCString(),false);
		CCDictionary* plistDic = CCDictionary::createWithContentsOfFile(pString->getCString());
		CCArray* picture_array = (CCArray*)plistDic->objectForKey("picture");
		CCArray* point_array = (CCArray*)plistDic->objectForKey("point");
	
		for (int i=0;i<picture_array->count();i++)
		{
			CCString* pi_string = (CCString*)picture_array->objectAtIndex(i);//获取图片地址
			CCSprite* sprite = CCSprite::create(pi_string->getCString());
			CCString* point_string = (CCString*)point_array->objectAtIndex(i);//获取图片坐标
			CCPoint point = CCPointFromString(point_string->getCString());
			sprite->setPosition(ccp(size.width*point.x,size.height*point.y));
			this->addChild(sprite,1);
		}	

		//goToShelf button
		CCSprite* cplay=CCSprite::create("btn_home.png");
		CCSprite* cplay1=CCSprite::create("btn_home.png");
		CCMenuItemSprite* mplay=CCMenuItemSprite::create(cplay,cplay1,this,menu_selector(EndStory::goToShelf));//goToShelf page
		CCMenu* menu=CCMenu::createWithItem(mplay);		
		menu->setPosition(ccp(size.width * 0.1, size.height * 0.8));
		menu->setTouchEnabled(true);
        this->addChild(menu,10);
		

		//next button
		cplay=CCSprite::create("play_next.png");
		cplay1=CCSprite::create("play_next2.png");
		mplay=CCMenuItemSprite::create(cplay,cplay1,this,menu_selector(GameScene::NextScene));//next page
		menu=CCMenu::createWithItem(mplay);
		menu->setPosition(ccp(size.width * 0.95, size.height * 0.2));
		menu->setTouchEnabled(true);
        this->addChild(menu,10);

	
		if(SceneNo!=0){
		//forward button
		cplay=CCSprite::create("play_forward.png");
		cplay1=CCSprite::create("play_forward2.png");
		mplay=CCMenuItemSprite::create(cplay,cplay1,this,menu_selector(GameScene::ForwardScene));//forward page
		menu=CCMenu::createWithItem(mplay);	
		//menu->setRotation(180);	
		menu->setPosition(ccp(size.width * 0.05, size.height * 0.2));
		menu->setTouchEnabled(true);
        this->addChild(menu,10);
		}
	

		setTouchEnabled(false);

		bRet = true;
	} while (0);

	return bRet;
}

void GameScene::NextScene(CCObject *sender)
{

	if(SceneNo>=PageNo){
		 SceneNo=0;
		CCDirector::sharedDirector()->replaceScene(CCTransitionJumpZoom::create(1,EndStory::scene()));
		}
	else if(SceneNo>=0){
	CCString *SoundString=CCString ::createWithFormat("Assets\\story\\audio\\%d.wav",SceneNo);
	SimpleAudioEngine::sharedEngine()->stopEffect(SoundId);
	SimpleAudioEngine::sharedEngine()->unloadEffect(SoundString->getCString()); 

	//SimpleAudioEngine::sharedEngine()->unloadEffect("Assets\\open.wav");	
	SceneNo++;
	CCScene* sc =CCTransitionFade::create(1,GameScene::scene());
	//CCScene* sc =CCTransitionPageTurn::create(1,GameScene::scene(),false);
	CCDirector::sharedDirector()->replaceScene(sc);
	}
}

void GameScene::ForwardScene(CCObject *sender)
{

	if(SceneNo<0){
		 SceneNo=0;
		CCDirector::sharedDirector()->replaceScene(CCTransitionShrinkGrow::create(1,ShelfScene::scene()));
		}
	else if(SceneNo<=PageNo){
	CCString *SoundString=CCString ::createWithFormat("Assets\\story\\audio\\%d.wav",SceneNo);
	SimpleAudioEngine::sharedEngine()->stopEffect(SoundId);
	SimpleAudioEngine::sharedEngine()->unloadEffect(SoundString->getCString()); 

	//SimpleAudioEngine::sharedEngine()->unloadEffect("Assets\\open.wav");	
	SceneNo--;
	CCScene* sc =CCTransitionFade::create(1,GameScene::scene());
	//CCScene* sc =CCTransitionZoomFlipX::create(1,GameScene::scene());	
	CCDirector::sharedDirector()->replaceScene(sc);
	}
}

//void EndStory::goToShelf(CCObject *sender){
//	CCDirector::sharedDirector()->replaceScene(ShelfScene::scene());
//}

void GameScene::ccTouchesBegan(CCSet* touches, CCEvent *event)
{

}

void GameScene::ccTouchesMoved(CCSet* touches, CCEvent* event)
{

}

// cpp with cocos2d-x
void GameScene::ccTouchesEnded(CCSet* touches, CCEvent* event)
{

}

void GameScene::registerWithTouchDispatcher()
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}
