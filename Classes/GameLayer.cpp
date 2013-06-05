#include "GameLayer.h"
using namespace cocos2d;

GameLayer::GameLayer(void)
{
	_tileMap = NULL;
	_hero = NULL;
}

GameLayer::~GameLayer(void)
{
}

bool GameLayer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CCLayer::init());

		this->setTouchEnabled(true);
		
		
		
		 /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

	//关闭按钮
    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(GameLayer::menuCloseCallback) );
    pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20) );

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);
		
		
		

		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("pd_sprites.plist");
		_actors = CCSpriteBatchNode::create("pd_sprites.pvr.ccz");
		_actors->getTexture()->setAliasTexParameters();
		this->addChild(_actors, -5);

		this->initHero();
		this->initTileMap();

		bRet = true;
	} while (0);

	return bRet;
}

void GameLayer::initTileMap()
{
	_tileMap = CCTMXTiledMap::create("pd_tilemap.tmx");
	CCObject *pObject = NULL;
	CCARRAY_FOREACH(_tileMap->getChildren(), pObject)
	{
		CCTMXLayer *child = (CCTMXLayer*)pObject;
		child->getTexture()->setAliasTexParameters();
	}
	this->addChild(_tileMap, -6);
}

void GameLayer::initHero()
{
	_hero = Hero::create();
	_actors->addChild(_hero);
	_hero->setPosition(ccp(_hero->getCenterToSides(), 80));
	_hero->setDesiredPosition(_hero->getPosition());
	_hero->idle();
}

void GameLayer::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
	_hero->attack();
}

void GameLayer::didChangeDirectionTo(SimpleDPad *simpleDPad, CCPoint direction)
{

}

void GameLayer::isHoldingDirection(SimpleDPad *simpleDPad, CCPoint direction)
{

}

void GameLayer::simpleDPadTouchEnded(SimpleDPad *simpleDPad)
{

}
//关闭按钮
void GameLayer::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}