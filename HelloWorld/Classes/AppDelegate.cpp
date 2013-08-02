﻿/*
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

#include "AppDelegate.h"

#include "cocos2d.h"
#include "Classes\Mainmenu.h"


#include "CCEGLView.h"
USING_NS_CC;

static float resRate=1;
float AppDelegate::getResRate(){
	return resRate;//适应屏幕比例
}
AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
//    SimpleAudioEngine::end();
}

bool AppDelegate::initInstance()
{
    bool bRet = false;
    do 
    {

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN8_METRO)

	void* buff=_aligned_malloc(sizeof(CCEGLView),16);
	CCEGLView* mainView = new (buff) CCEGLView();
	mainView->Create();
	//mainView->setDesignResolution(480, 320);
	//mainView->setDesignResolution(640, 1066);
	CCLOG("Device Res:%d", m_deviceResolutionInPixels);
	
	switch (m_deviceResolutionInPixels) 
	{
	case DeviceResolutionInPixels_WVGA: 
		{
			mainView->setDesignResolution(480, 800);
			//mainView->setDesignResolutionSize(480, 800, kResolutionShowAll);
			break;
		}
	case DeviceResolutionInPixels_720p: 
		{
			//mainView->setDesignResolutionSize(720, 1280,kResolutionShowAll);//自适应分辨率引擎没有实现
			mainView->setDesignResolution(720, 1280);
			resRate=1.6f;//1280/800=1.6;
			break;
		}	
	case DeviceResolutionInPixels_WXGA: 
		{
			//mainView->setDesignResolutionSize(480, 800, kResolutionShowAll);
			mainView->setDesignResolution(768, 1280);
			resRate=1.6f;
			break;
		}
	}
	

#endif // CC_PLATFORM_WIN8_METRO

        bRet = true;
    } while (0);
    return bRet;
}

bool AppDelegate::applicationDidFinishLaunching()
{
	// initialize director
	CCDirector *pDirector = CCDirector::sharedDirector();


	pDirector->setOpenGLView(&CCEGLView::sharedOpenGLView());

	// turn on display FPS
	//pDirector->setDisplayFPS(false);
	//pDirector->setDeviceOrientation(kCCDeviceOrientationPortrait);//竖屏的界面，如果是横屏的就改成下面的。
	pDirector->setDeviceOrientation(CCDeviceOrientationLandscapeLeft);
	// set FPS. the default value is 1.0/60 if you don't call this
	//pDirector->setAnimationInterval(1.0 / 60);

	// create a scene. it's an autorelease object
	CCScene *pScene = HelloWorld::scene();

	// run
	pDirector->runWithScene(pScene);


	return true;

}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->pause();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->resume();
}
