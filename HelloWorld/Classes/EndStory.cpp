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

#include "EndStory.h"
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


EndStory::~EndStory()
{
}

EndStory::EndStory()
{

}

CCScene* EndStory::scene()
{
	CCScene * scene = NULL;
	do 
	{		// 'scene' is an autorelease object
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		EndStory *layer = EndStory::create();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool EndStory::init()
{
	bool bRet = false;

	do 
	{
		if ( !CCLayer::init() )
		{
			break;
		}

		CCString * pString,*SoundString;
		CCSize size=CCDirector::sharedDirector()->getWinSize();

		
		pString  =CCString ::createWithFormat("end.plist");
		//CCDictionary* plistDic;
		//CCArray* picture_array ;
		//CCArray* point_array ;
		//按钮的载入
		CCDictionary* plistDic= CCDictionary::createWithContentsOfFile(pString->getCString());
		CCDictionary* Dic = (CCDictionary*)plistDic->objectForKey("button");
		CCArray* picture_array = (CCArray*)Dic->objectForKey("button_img");
		CCArray* point_array = (CCArray*)Dic->objectForKey("button_pos");
		CCArray* fun_array = (CCArray*)Dic->objectForKey("button_fun");

		for (int i=0;i<picture_array->count();i++)
		{
			CCString* pi_string = (CCString*)picture_array->objectAtIndex(i);//获取图片地址
			CCSprite* btn_sprite = CCSprite::create(pi_string->getCString());
			CCSprite* btn_sprite1 = CCSprite::create(pi_string->getCString());

			CCString* fun_string = (CCString*)fun_array->objectAtIndex(i);
			int fun_id = fun_string->intValue();//获取功能id
			CCMenuItemSprite* mplay=new CCMenuItemSprite();
            switch(fun_id){
				case 0:	
			            mplay=CCMenuItemSprite::create(btn_sprite,btn_sprite1,NULL,this,menu_selector(EndStory::goToShelf));
						break;//home page
				case 3:	
						mplay=CCMenuItemSprite::create(btn_sprite,btn_sprite1,NULL,this,menu_selector(EndStory::replayScene));
						break;//replay
			}
			CCMenu* menu=CCMenu::createWithItem(mplay);

			CCString* point_string = (CCString*)point_array->objectAtIndex(i);//获取图片坐标
			CCPoint point = CCPointFromString(point_string->getCString());
			menu->setPosition(ccp(size.width*point.x,size.height*point.y));
			menu->setTouchEnabled(true);
			this->addChild(menu,60);
		}	

		////图片的载入

		picture_array = (CCArray*)plistDic->objectForKey("picture");
		point_array = (CCArray*)plistDic->objectForKey("point");
		//CCArray* scale_array = (CCArray*)plistDic->objectForKey("scale");
		for (int i=0;i<picture_array->count();i++)
		{
			CCString* pi_string = (CCString*)picture_array->objectAtIndex(i);
			CCSprite* sprite = CCSprite::create(pi_string->getCString());

			//CCString* scale_string = (CCString*)scale_array->objectAtIndex(i);
			//int scale = scale_string->intValue();
			sprite->setScale(AppDelegate::getResRate());

			CCString* point_string = (CCString*)point_array->objectAtIndex(i);
			CCPoint point = CCPointFromString(point_string->getCString());
			sprite->setPosition(ccp(size.width*point.x,size.height*point.y));

			this->addChild(sprite,10);
		}	
	
		setTouchEnabled(false);//禁止触摸

		bRet = true;
	} while (0);

	return bRet;
}

void EndStory::goToShelf(CCObject *sender){
	CCDirector::sharedDirector()->replaceScene(CCTransitionShrinkGrow::create(1,ShelfScene::scene()));
}
void EndStory::replayScene(CCObject *sender){
	CCDirector::sharedDirector()->replaceScene(CCTransitionShrinkGrow::create(1,GameScene::scene()));
}

void EndStory::ccTouchesBegan(CCSet* touches, CCEvent *event)
{

}

void EndStory::ccTouchesMoved(CCSet* touches, CCEvent* event)
{

}

// cpp with cocos2d-x
void EndStory::ccTouchesEnded(CCSet* touches, CCEvent* event)
{

}

void EndStory::registerWithTouchDispatcher()
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}
