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


#include "BelajarHanacaraka.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

using namespace cocos2d::network;
using namespace ui;


Scene* BelajarHanacaraka::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    // 'layer' is an autorelease object
    auto layer = BelajarHanacaraka::create();
    // add layer as a child to scene
    scene->addChild(layer);

    return  scene;
}

const std::string nama_object[] =
{
        "menubermain/hanacaraka/ha",
        "menubermain/hanacaraka/na",
        "menubermain/hanacaraka/ca",
        "menubermain/hanacaraka/ra",
        "menubermain/hanacaraka/ka",
        "menubermain/hanacaraka/da",
        "menubermain/hanacaraka/ta",
        "menubermain/hanacaraka/sa",
        "menubermain/hanacaraka/wa",
        "menubermain/hanacaraka/la",
        "menubermain/hanacaraka/pa",
        "menubermain/hanacaraka/dha",
        "menubermain/hanacaraka/ja",
        "menubermain/hanacaraka/ya",
        "menubermain/hanacaraka/nya",
        "menubermain/hanacaraka/ma",
        "menubermain/hanacaraka/ga",
        "menubermain/hanacaraka/ba",
        "menubermain/hanacaraka/tha",
        "menubermain/hanacaraka/nga"
        
};

bool BelajarHanacaraka::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    bg = Sprite::create("menubermain/hanacaraka/bg_hanacaraka.png");
    bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(bg);

    int get_y_posisi_button;
for (int i = 0; i < 20; i++)
{
    font[i] = Button::create(__String::createWithFormat("%s.png", nama_object[i].c_str())->getCString());
    font[i]->setAnchorPoint(Point(0.5, 0.5));
    font[i]->setPosition(Vec2(+ 410 + ((visibleSize.width / 2 + origin.x - 610) * i),
        (visibleSize.height / 2 + origin.y + 175) - (i % 5)));
    this->addChild(font[i]);
    font[i]->addClickEventListener([=](Ref* Sender) {
        font[i]->runAction(Sequence::create(ScaleTo::create(0.5, 1.3), ScaleTo::create(0.5, 1), nullptr));
    });

    if (i % 5 == 0 && i != 0)
    {
        //hitung_enter++;
        font[i]->setPosition(Vec2(font[i - 5]->getPositionX(),
            font[i - 5]->getPositionY() - font[i - 5]->getContentSize().height - 50));
        get_y_posisi_button = font[i - 5]->getPositionY() - font[i - 5]->getContentSize().height - 50;
    };
    if (i >= 5)
    {
        font[i]->setPosition(Vec2(font[i - 5]->getPositionX(),
            get_y_posisi_button));
    };
}


    return true;
}
