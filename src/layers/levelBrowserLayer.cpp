#include <Geode/modify/LevelBrowserLayer.hpp>
#include <Geode/Geode.hpp>
#include <Geode/binding/BoomListView.hpp>
#include "../HighLow.hpp"

using namespace geode::prelude;

class $modify(CustomLevelBrowserLayer, LevelBrowserLayer) {
	
	bool init(GJSearchObject* p0) 
	{
		if (!LevelBrowserLayer::init(p0)) return false;
		if (HighLow::getIsHLMenu())
		{
			//not removing to prevent crashes
			this->getChildByID("level-count-label")->setVisible(false);
			this->getChildByID("search-menu")->setVisible(false);
			this->getChildByIDRecursive("refresh-button")->setVisible(false);
			this->getChildByID("page-menu")->setVisible(false);
			this->getChildByID("next-page-menu")->setVisible(false);
			this->getChildByID("prev-page-menu")->setVisible(false);
			auto infoMenu = (CCMenuItem*) this->getChildByID("info-menu");
			((CCMenuItem*) infoMenu->getChildByID("info-button"))->setTarget(this, menu_selector(CustomLevelBrowserLayer::onInfoButton));
		}
		return true;
	}

	virtual void onEnter()
	{
		LevelBrowserLayer::onEnter();
		if (HighLow::getIsHLMenu())
		{
			CCLabelBMFont* title = (CCLabelBMFont*)this->getChildByID("GJListLayer")->getChildByID("title");
			std::stringstream ss;
			ss << "Score: " << HighLow::getScore();
			auto text = ss.str();
			if (title != NULL) title->setString(text.c_str());
		}
	}
	
	virtual void onBack(CCObject* sender)
	{
		LevelBrowserLayer::onBack(sender);
		HighLow::setIsHLMenu(false);
	}

	virtual void loadLevelsFinished(CCArray* p0, char const* p1, int p2) 
	{
		CCArray* arr = CCArray::create();
		auto l1 = HighLow::getL1();
		auto l2 = HighLow::getL2();
		if (l1 != NULL) arr->addObject(l1);
		if (l2 != NULL) arr->addObject(l2);
		if(!HighLow::getIsHLMenu()) LevelBrowserLayer::loadLevelsFinished(p0, p1, p2);
		else 
		{
			LevelBrowserLayer::loadLevelsFinished(arr, p1, p2);
			CCLabelBMFont* title = (CCLabelBMFont*)this->getChildByID("GJListLayer")->getChildByID("title");	
			std::stringstream ss;
			ss << "Score: " << HighLow::getScore();
			auto text = ss.str();
			if (title != NULL) title->setString(text.c_str());
		}
	}

	void onRefresh(CCObject* p0) 
	{
		CCLabelBMFont* title = (CCLabelBMFont*)this->getChildByID("GJListLayer")->getChildByID("title");
		std::stringstream ss;
		ss << "Score: " << HighLow::getScore();
		auto text = ss.str();
		if (title != NULL) title->setString(text.c_str());

		LevelBrowserLayer::onRefresh(p0);
	}

	void onInfoButton(CCObject* sender) 
	{
		FLAlertLayer::create(
			"Higher or lower",
			"This is the Higher or lower game, your goal is to guess which these two levels has more downloads!\nYour Score is tracked at the top.\nThanks for using my mod <3",
			"OK"
		)->show();
	}
};