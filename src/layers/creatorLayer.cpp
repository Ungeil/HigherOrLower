#include <Geode/modify/CreatorLayer.hpp>
#include <Geode/Geode.hpp>
#include "../HighLow.hpp"

using namespace geode::prelude;

class $modify(CustomCreatorLayer, CreatorLayer) {

	bool init() {

		if (!CreatorLayer::init()) {
			return false;
		}
		auto sprite = CCSprite::createWithSpriteFrameName("GJ_playBtn2_001.png");
		sprite->setScale(0.5);
		auto hlButton = CCMenuItemSpriteExtra::create(
			sprite,
			this,
			menu_selector(CustomCreatorLayer::onHLButton)
		);

		auto menu = this->getChildByID("bottom-left-menu");
		menu->addChild(hlButton);
		hlButton->setID("HLButton"_spr);
		menu->updateLayout();
		return true;
	}

	void onHLButton(CCObject*) {
		HighLow::setIsHLMenu(true);
		auto scene = CCScene::create();
		auto searchObj = GJSearchObject::create(SearchType(1));
		auto layer = LevelBrowserLayer::create(searchObj);
		layer->setID("HLLayer"_spr);
		scene->addChild(layer);
		auto transition = CCTransitionFade::create(0.5, scene);
		CCDirector::sharedDirector()->pushScene(transition);
	}
};