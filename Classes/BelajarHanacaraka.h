/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __BelajarHanacaraka_H__
#define __BelajarHanacaraka_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "network/HttpClient.h"
#include "cocos/platform/CCDevice.h"

USING_NS_CC;

using namespace cocostudio::timeline;
using namespace cocos2d::ui;
using namespace tinyxml2;

class BelajarHanacaraka : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(BelajarHanacaraka);
private:
    Sprite* bg;

    Button* font[20];
    /*Button* ha;
    Button* na;
    Button* ca;
    Button* ra;
    Button* ka;
    Button* da;
    Button* ta;
    Button* sa;
    Button* wa;
    Button* la;
    Button* pa;
    Button* dha;
    Button* ja;
    Button* ya;
    Button* nya;
    Button* ma;
    Button* ga;
    Button* ba;
    Button* tha;
    Button* nga;*/
};

#endif // __HELLOWORLD_SCENE_H__
