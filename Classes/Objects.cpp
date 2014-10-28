#include "Objects.h"

MyMenuItem* MyMenuItem::create(cocos2d::Node* icon, cocos2d::Sprite* bg, const cocos2d::ccMenuCallback& callback)
{
	return create(icon, nullptr, bg, callback);
}

MyMenuItem* MyMenuItem::create(cocos2d::Node* enabledIcon, cocos2d::Node* disabledIcon, cocos2d::Sprite* bg, const cocos2d::ccMenuCallback& callback)
{
	MyMenuItem* ret = new MyMenuItem();
	ret->initWithNormalSprite(bg, nullptr, nullptr, callback);
	ret->mEnabled = true;
	ret->mIconEnabled = enabledIcon;
	ret->mIconDisabled = disabledIcon;
	ret->autorelease();
	ret->setCascadeOpacityEnabled(true);
	
	ret->mIconEnabled->setPosition(ret->getContentSize().width/2, ret->getContentSize().height/2);
	ret->addChild(ret->mIconEnabled);
	if (ret->mIconDisabled)
	{
		ret->mIconDisabled->setPosition(ret->getContentSize().width/2, ret->getContentSize().height/2);
		ret->mIconDisabled->setVisible(false);
		ret->addChild(ret->mIconDisabled);
	}
	
	return ret;
}


void MyMenuItem::selected()
{
//	MenuItem::selected();
	
	runAction(cocos2d::Sequence::create(
			cocos2d::ScaleTo::create(0.07f, 0.9f),
			cocos2d::ScaleTo::create(0.07f, 1),
			NULL
	));
}

void MyMenuItem::unselected()
{
	MenuItem::unselected();
}

void MyMenuItem::activate()
{
	MenuItemSprite::activate();
}

bool MyMenuItem::getEnabled()
{
	return mEnabled;
}

void MyMenuItem::setEnabled(bool state)
{
	if (state != mEnabled)
	{
		mEnabled = state;
		if (mIconDisabled)
		{
			mIconEnabled->setVisible(mEnabled);
			mIconDisabled->setVisible(!mEnabled);
		}
	}
}

void ObjectPool::init(int capacity, cocos2d::SpriteFrame* spriteFrame, cocos2d::Node* parent)
{
	if (getAvailableItemCount() > 0)
		clearPool();
	
	mSpriteFrame = spriteFrame;
	mParent = parent;
	
	initWithCapacity(capacity);
}
