#include <Geode/modify/GJListLayer.hpp>
#include <Geode/Geode.hpp>
#include "../HighLow.hpp"
using namespace geode::prelude;

class $modify(CustomListLayer, GJListLayer) {
	bool init(BoomListView* p0, char const* p1, cocos2d::ccColor4B p2, float p3, float p4, int p5)
	{
		if (!GJListLayer::init(p0, p1, p2, p3, p4, p5)) return false;
		if (HighLow::getIsHLMenu())
		{
			CCLabelBMFont* title = (CCLabelBMFont*)this->getChildByID("title");
			std::stringstream ss;
			ss << "Score: " << HighLow::getScore();
			auto text = ss.str();
			if (title != NULL) title->setString(text.c_str());
		}
		return true;
	}

};