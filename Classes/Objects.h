#ifndef __OBJECTS_H__
#define __OBJECTS_H__

#include "cocos2d.h"

class MyMenuItem : public cocos2d::MenuItemSprite
{
public:
	static MyMenuItem* create(cocos2d::Node* icon, cocos2d::Sprite* bg, const cocos2d::ccMenuCallback& callback);
	static MyMenuItem* create(cocos2d::Node* enabledIcon, cocos2d::Node* disabledIcon, cocos2d::Sprite* bg, const cocos2d::ccMenuCallback& callback);
	
	void selected() override;
	void unselected() override;
	void activate() override;
	
	bool getEnabled();
	void setEnabled(bool state);
private:
	bool mEnabled;
	cocos2d::Node* mIconEnabled;
	cocos2d::Node* mIconDisabled;
};

class Tile : public cocos2d::MenuItem
{
public:
	static Tile* create(int id, cocos2d::Node* front, cocos2d::Node* back, const cocos2d::ccMenuCallback& callback);
	
	void reveal(const std::function<void()>& callback = nullptr);
	void hide(float delay = 0, const std::function<void()>& callback = nullptr);
	int getCoupleId();
	bool isRevealed();
private:
	cocos2d::Node* mFrontView;
	cocos2d::Node* mBackView;
	bool mRevealed;
	int mCoupleId;
};

template<class T> class GenericPool
{
public:
	GenericPool() : mAvailableItems(), mUnrecycledItemCount(0)
	{
		
	}
	virtual ~GenericPool()
	{
		
	}
	
	void initWithCapacity(int capacity)
	{
		batchAllocatePoolItems(capacity);
	}
	int getUnrecycledItemCount()
	{
		return mUnrecycledItemCount;
	}
	int getAvailableItemCount()
	{
		return mAvailableItems.size();
	}
	void batchAllocatePoolItems(int pCount)
	{
		cocos2d::log("Increasing pool capacity with %d (current size %d)", pCount, mAvailableItems.size() + mUnrecycledItemCount);
		
		for (int i = 0; i < pCount; i++)
		{
			T item = onAllocatePoolItem();
			item->retain();
			mAvailableItems.push_back(item);
		}
	}
	T obtainPoolItem()
	{
		T item;
		if (mAvailableItems.size() == 0)
		{
			batchAllocatePoolItems(1);
		}
		
		item = mAvailableItems.back();
		mAvailableItems.pop_back();
		
		onObtainItem(item);
		
		mUnrecycledItemCount++;
		
		return item;
	}
	
	void recyclePoolItem(T pItem)
	{
		CCASSERT(pItem, "Cannot recycle null item!");
		
		onRecycleItem(pItem);
		mAvailableItems.push_back(pItem);
		mUnrecycledItemCount--;
		if (mUnrecycledItemCount < 0)
		{
			cocos2d::log("More items recycled than obtained!");
		}
	}
	
	void clearPool()
	{
		while (mAvailableItems.size() > 0)
		{
			mAvailableItems.pop_back();
		}
	}

protected:
	virtual T onAllocatePoolItem() = 0;
	virtual void onObtainItem(T pItem)
	{
		
	}
	virtual void onRecycleItem(T pItem)
	{
		
	}

private:
	std::vector<T> mAvailableItems;
	int mUnrecycledItemCount;
};

class SpritePool : public GenericPool<cocos2d::Sprite*>
{
public:
	void init(int capacity, cocos2d::SpriteFrame* spriteFrame, cocos2d::Node* parent);
protected:
	cocos2d::Node* mParent;
	cocos2d::SpriteFrame* mSpriteFrame;
	cocos2d::Sprite* onAllocatePoolItem() override;
};

class BanutzPool : public GenericPool<cocos2d::Sprite*>
{
public:
	void init(int capacity, cocos2d::SpriteFrame* spriteFrame, cocos2d::Node* parent);
protected:
	cocos2d::Node* mParent;
	cocos2d::SpriteFrame* mSpriteFrame;
	cocos2d::Sprite* onAllocatePoolItem() override;
};

class StatusDelegate {
public:
	/**
	* When the game start, this method will be called
	*/
	virtual void onGameStart(void) = 0;

	/**
	* During paying, after the score changed, this method will be called
	*/
	virtual void onGamePlaying(int score) = 0;

	/**
	* When game is over, this method will be called
	*/
	virtual void onGameEnd(int curSocre, int bestScore) = 0;
};

#endif // __OBJECTS_H__
