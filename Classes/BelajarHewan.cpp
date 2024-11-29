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


#include "BelajarHewan.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

using namespace cocos2d::network;
using namespace ui;


Scene* BelajarHewan::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    // 'layer' is an autorelease object
    auto layer = BelajarHewan::create();
    // add layer as a child to scene
    scene->addChild(layer);

    return  scene;
}

const std::string nama_object[] =
{
        "menubermain/namahewan/bandeng",
        "menubermain/namahewan/bebek",
        "menubermain/namahewan/babi",
        "menubermain/namahewan/cacing",
        "menubermain/namahewan/kodok",
        "menubermain/namahewan/ayam",
        "menubermain/namahewan/sapi",
        "menubermain/namahewan/kambing",
        "menubermain/namahewan/kelelawar",
        "menubermain/namahewan/kadal"
};

const std::string hewan[] =
{
        "menubermain/UNTUK PANEL TENGAH/IKAN",
        "menubermain/UNTUK PANEL TENGAH/BEBEK",
        "menubermain/UNTUK PANEL TENGAH/BABI",
        "menubermain/UNTUK PANEL TENGAH/CACING",
        "menubermain/UNTUK PANEL TENGAH/KATAK",
        "menubermain/UNTUK PANEL TENGAH/AYAM",
        "menubermain/UNTUK PANEL TENGAH/SAPI",
        "menubermain/UNTUK PANEL TENGAH/KAMBING",
        "menubermain/UNTUK PANEL TENGAH/KELELAWAR",
        "menubermain/UNTUK PANEL TENGAH/KADAL"
};

const std::string nama_hewan[] =
{
        "Bandeng",
        "Bebek",
        "Babi",
        "Cacing",
        "Kodok",
        "Ayam",
        "Sapi",
        "Kambing",
        "Kelelawar",
        "Kadal"
};

bool BelajarHewan::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    bg = Sprite::create("menubermain/UNTUK PANEL TENGAH/BG-NON-PANEL.png");
    bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(bg);
    
    panel = Sprite::create("menubermain/namahewan/bg_panelbawah.png");
    panel->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 650));
    panel->runAction(EaseBackOut::create(MoveTo::create(1, Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 340))));
    this->addChild(panel);
    
    panelutama = Sprite::create("menubermain/UNTUK PANEL TENGAH/panel putih.png");
    panelutama->setScale(0);
    panelutama->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 150));
    panelutama->runAction(EaseBackOut::create(ScaleTo::create(0.5, 1)));
    this->addChild(panelutama);

    scroll = ScrollView::create();
    scroll->setDirection(ScrollView::Direction::HORIZONTAL);
    scroll->setContentSize(Size(panel->getContentSize().width, 230));
    scroll->setInnerContainerSize(Size(3520, 50));
    scroll->setAnchorPoint(Point(0.5, 0.5));
    scroll->setPosition(Vec2(visibleSize.width / 2 + origin.x + 155, visibleSize.height / 2 + origin.y - 260));
    scroll->setBounceEnabled(true);
    scroll->setClippingEnabled(true);
    scroll->setSwallowTouches(false);
    scroll->setScrollBarOpacity(0);

    currentLabel = nullptr;
    int get_y_posisi_button;
    for (int i = 0; i < 10; i++)
    {
        pict[i] = Button::create(__String::createWithFormat("%s.png", nama_object[i].c_str())->getCString());
        pict[i]->setAnchorPoint(Point(0.5, 0.5));
        pict[i]->setScale(0);
        pict[i]->setPosition(Vec2(+165 + ((visibleSize.width / 2 + origin.x - 485) * i),
            (visibleSize.height / 2 + origin.y - 378) - (i % 5)));
        pict[i]->runAction(CallFunc::create(CC_CALLBACK_0(BelajarHewan::animasi, this)));
        scroll->addChild(pict[i]);
        if (currentLabel != nullptr) {
            currentLabel->removeFromParentAndCleanup(true);
            currentLabel = nullptr; // Set ke nullptr setelah dihapus
        }
        // Tampilkan label baru
        currentLabel = Label::createWithTTF(nama_hewan[0], "fonts/JandaManateeSolid.ttf", 36);
        currentLabel->setPosition(Vec2(visibleSize.width / 2 + 280, visibleSize.height / 2 + 300));
        currentLabel->setColor(getRandomColor());
        currentLabel->runAction(EaseBackOut::create(ScaleTo::create(0.5, 1.5)));
        this->addChild(currentLabel);

        /*Sprite* hewan = Sprite::create(__String::createWithFormat("%s.png", hewan[i].c_str())->getCString());
        hewan->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
        this->addChild(hewan);*/


        auto listener = EventListenerTouchOneByOne::create();
        listener->setSwallowTouches(true);
        listener->onTouchBegan = [=](Touch* touch, Event* event) {
            Vec2 touchPos = touch->getLocation();
            Rect labelRect = currentLabel->getBoundingBox();

            if (labelRect.containsPoint(touchPos)) {
                currentLabel->stopAllActions();
                currentLabel->runAction(Sequence::create(
                    ScaleTo::create(0.3, 2),
                    ScaleTo::create(0.3, 1.5),
                    nullptr
                ));
                return true;
            }
            return false;
            };
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, currentLabel);
        pict[i]->addClickEventListener([=](Ref* Sender) {
            if (currentLabel != nullptr) {
                currentLabel->removeFromParentAndCleanup(true);
                currentLabel = nullptr; // Set ke nullptr setelah dihapus
            }
            // Tampilkan label baru
            currentLabel = Label::createWithTTF(nama_hewan[i], "fonts/JandaManateeSolid.ttf", 36);
            currentLabel->setPosition(Vec2(visibleSize.width / 2 + 280, visibleSize.height / 2 + 300));
            currentLabel->setColor(getRandomColor());
            currentLabel->runAction(EaseBackOut::create(ScaleTo::create(0.5, 1.5)));
            this->addChild(currentLabel);
            auto listener = EventListenerTouchOneByOne::create();
            listener->setSwallowTouches(true);
            listener->onTouchBegan = [=](Touch* touch, Event* event) {
                Vec2 touchPos = touch->getLocation();
                Rect labelRect = currentLabel->getBoundingBox();

                if (labelRect.containsPoint(touchPos)) {
                    currentLabel->stopAllActions();
                    currentLabel->runAction(Sequence::create(
                        ScaleTo::create(0.3, 2),
                        ScaleTo::create(0.3, 1.5),
                        nullptr
                    ));
                    return true;
                }
                return false;
                };
            _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, currentLabel);
            });

        if (i % 10 == 0 && i != 0)
        {
            //hitung_enter++;
            pict[i]->setPosition(Vec2(pict[i - 10]->getPositionX(),
                pict[i - 10]->getPositionY() - pict[i - 10]->getContentSize().height - 50));
            get_y_posisi_button = pict[i - 10]->getPositionY() - pict[i - 10]->getContentSize().height - 50;
        };
        if (i >= 10)
        {
            pict[i]->setPosition(Vec2(pict[i - 10]->getPositionX(),
                get_y_posisi_button));
        };
    }
    this->addChild(scroll);
    return true;
}
void BelajarHewan::animasi()
{
    DelayTime* delay1 = DelayTime::create(1);
    DelayTime* delay2 = DelayTime::create(1.3);
    DelayTime* delay3 = DelayTime::create(1.6);
    DelayTime* delay4 = DelayTime::create(1.9);
    DelayTime* delay5 = DelayTime::create(2.2);
    DelayTime* delay6 = DelayTime::create(2.5);
    DelayTime* delay7 = DelayTime::create(2.8);
    DelayTime* delay8 = DelayTime::create(3.1);
    DelayTime* delay9 = DelayTime::create(3.4);
    DelayTime* delay10 = DelayTime::create(3.7);
    pict[0]->runAction(Sequence::create(delay1, EaseBackOut::create(ScaleTo::create(0.3, 1)), nullptr));
    pict[1]->runAction(Sequence::create(delay2, EaseBackOut::create(ScaleTo::create(0.3, 1)), nullptr));
    pict[2]->runAction(Sequence::create(delay3, EaseBackOut::create(ScaleTo::create(0.3, 1)), nullptr));
    pict[3]->runAction(Sequence::create(delay4, EaseBackOut::create(ScaleTo::create(0.3, 1)), nullptr));
    pict[4]->runAction(Sequence::create(delay5, EaseBackOut::create(ScaleTo::create(0.3, 1)), nullptr));
    pict[5]->runAction(Sequence::create(delay6, EaseBackOut::create(ScaleTo::create(0.3, 1)), nullptr));
    pict[6]->runAction(Sequence::create(delay7, EaseBackOut::create(ScaleTo::create(0.3, 1)), nullptr));
    pict[7]->runAction(Sequence::create(delay8, EaseBackOut::create(ScaleTo::create(0.3, 1)), nullptr));
    pict[8]->runAction(Sequence::create(delay9, EaseBackOut::create(ScaleTo::create(0.3, 1)), nullptr));
    pict[9]->runAction(Sequence::create(delay10, EaseBackOut::create(ScaleTo::create(0.3, 1)), nullptr));
}

Color3B BelajarHewan::getRandomColor() {
    // Array of bright, kid-friendly colors
    const Color3B colors[] = {
        Color3B(255, 0, 0),    // Red
        Color3B(0, 150, 255),  // Blue
        Color3B(0, 255, 0),    // Green
        Color3B(255, 165, 0),  // Orange
        Color3B(238, 130, 238),// Violet
        Color3B(255, 255, 0),   // Kuning
        Color3B(139, 69, 19),  // Coklat Tua
        Color3B(169, 169, 169)   // abuabu
    };
    return colors[rand() % 7];  // Randomly select a color
}