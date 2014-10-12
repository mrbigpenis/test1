#include "MainScene.h"
#include <iostream>

int hp1 = 100, hp2 = 100 , mp1=200 , mp2=200;

int priority=0;

std::string hp1string = std::to_string(hp1);
std::string hp2string = std::to_string(hp2);
std::string mp1string = std::to_string(mp1);
std::string mp2string = std::to_string(mp2);
auto label = LabelTTF::create("Such Battle", "Comic Sans MS", 24);
auto label1 = LabelTTF::create("HP: " + hp1string, "Verdana", 15);

auto label2 = LabelTTF::create("HP: " + hp2string, "Verdana", 15);
auto label1_1 = LabelTTF::create("MP: " + mp1string, "Verdana", 15);

auto label2_1 = LabelTTF::create("MP: " + mp2string, "Verdana", 15);

Scene* MainScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = MainScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    // :D
	Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
	//auto attack = MenuItemImage::create("attack.png", "attack.png" ,CC_CALLBACK_1(MainScene::menuCloseCallback, this));
	auto attack = MenuItemImage::create("attack.png", "attack.png" ,CC_CALLBACK_1(MainScene::buttonnn, this));
	auto attack2 = MenuItemImage::create("attack.png", "attack.png", CC_CALLBACK_1(MainScene::buttonnn2, this));

	//bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);

	auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
										   CC_CALLBACK_1(MainScene::menuCloseCallback, this));
	attack->setScale(0.50, 0.50);
	attack->setPosition(90, 350);
	attack2->setScale(0.50, 0.50);
	attack2->setPosition(850, 350);
	this->addChild(attack, 1);
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, attack, attack2,  NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

	
	//auto label3 = LabelTTF::create("HP", "Verdana", 15);


    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

	label1->setPosition(80,300);
	label1_1->setPosition(80, 320);
	label2_1->setPosition(840, 320);
	label2->setPosition(840, 300);

    this->addChild(label, 1);
	this->addChild(label1, 1);
	this->addChild(label2, 1);
	this->addChild(label1_1, 1);
	this->addChild(label2_1, 1);



    auto sprite = Sprite::create("background.jpg");
	auto spritef = Sprite::create("yolo.png");//Profile image
	auto spriteff = Sprite::create("yolo.png");//Profile image
    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	spritef->setPosition(90, 400);
	spriteff->setPosition(850, 400);

	spritef->setScale(0.23, 0.23);
	spriteff->setScale(0.23, 0.23);

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
	this->addChild(spritef, 0);
	this->addChild(spriteff, 0);
	String a;
  
    return true;
	

}
//P1 Normal attack
void MainScene::buttonnn(Ref* pSender){
	
	if (priority == 0){
		hp2 = hp2 - 5;
		std::string hp2string = std::to_string(hp2);


		label2->setString("HP: " + hp2string);
	}
	else
	{
		
     //something flashing and cool to advise/

	}
	priority = 1;
	if (hp1 <= 0){

		priority = 2;
		label2->setString("SWAG");
		label1->setString("LOST");



	}
	}  

//P2 Normal attack

void MainScene::buttonnn2(Ref* pSender){
	
	if (priority == 1){
		hp1 = hp1 - 5;
		std::string hp1string = std::to_string(hp1);
		label1->setString("HP: " + hp1string);

	}
	else{

		//something flashing and cool to advise/


	}
	priority = 0;
	if (hp2 <= 0){

		priority = 2;
		label1->setString("SWAG");
		label2->setString("LOST");



	}
}



//EXIT

void MainScene::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();
	//k void everywhere
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
