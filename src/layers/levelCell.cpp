#include <Geode/modify/LevelCell.hpp>
#include <Geode/Geode.hpp>
#include "../HighLow.hpp"

//this is the ugliest code i have written in the past 5 years I am sorry to whoever has to see this
class $modify(CustomLevelCell, LevelCell)
{
	void onButtonHigher(CCObject*)
	{
		HighLow::select(2);
	}

	void onButtonLower(CCObject*)
	{
		HighLow::select(1);
	}

	void onRestart(CCObject*) 
	{
		HighLow::reset();
	}


	void draw() {
		LevelCell::draw();
		if (!HighLow::getIsHLMenu()) return;

		CCLayer* mainLayer = (CCLayer*)this->getChildByID("main-layer");
		mainLayer->removeChildByID("completed-icon");
		mainLayer->removeChildByID("likes-icon");
		mainLayer->removeChildByID("likes-label");
		mainLayer->removeChildByID("orbs-icon");
		mainLayer->removeChildByID("orbs-label");
		mainLayer->removeChildByID("high-object-indicator");
		mainLayer->removeChildByID("copy-indicator");
		mainLayer->removeChildByID("percentage-label");

		CCNode* difficultyC = (CCNode*)mainLayer->getChildByID("difficulty-container");
		difficultyC->removeChildByID("stars-label");
		difficultyC->removeChildByID("stars-icon");
		difficultyC->removeChildByID("orbs-label");
		
		if (difficultyC->getChildByID("coin-icon-1") != NULL) difficultyC->removeChildByID("coin-icon-1");
		if (difficultyC->getChildByID("coin-icon-2") != NULL) difficultyC->removeChildByID("coin-icon-2");
		if (difficultyC->getChildByID("coin-icon-3") != NULL) difficultyC->removeChildByID("coin-icon-3");
		
		
		difficultyC->getChildByID("difficulty-sprite")->setPosition(CCPoint(0.0, 0.0));

		CCNode* mainMenu = (CCNode*)mainLayer->getChildByID("main-menu");
		mainMenu->removeChildByID("view-button");

		CCMenuItemSpriteExtra* creatorName = (CCMenuItemSpriteExtra*)mainMenu->getChildByID("creator-name");
		creatorName->m_animationEnabled = false;
		creatorName->setEnabled(false);
		double cellHeight = this->m_height;

		//setup for cell 2
		if (strcmp(((CCLabelBMFont*)mainLayer->getChildByID("level-name"))->getString(), ((std::string)HighLow::getL2()->m_levelName).c_str()) == 0)
		{
			mainLayer->getChildByID("downloads-label")->setVisible(false);
			mainLayer->getChildByID("downloads-icon")->setVisible(false);

			if(!HighLow::isGamePaused())
			{
				auto buttonLower = (CCMenuItemSpriteExtra*)mainMenu->getChildByID("LowerButton"_spr);
				auto buttonHigher = (CCMenuItemSpriteExtra*)mainMenu->getChildByID("HigherButton"_spr);

				//deleting items outside this branch
				mainMenu->removeChildByID("RestartButton"_spr);
								
				if (buttonLower == NULL)
				{
					buttonLower = CCMenuItemSpriteExtra::create(CircleButtonSprite::create(CCSprite::create("LowerButton.png"_spr)), this, menu_selector(CustomLevelCell::onButtonLower));
					mainMenu->addChild(buttonLower);
					buttonLower->setID("LowerButton"_spr);
					buttonLower->setPosition(CCPoint(-25, cellHeight / 2 - 160));
				}

				if (buttonHigher == NULL)
				{
					buttonHigher = CCMenuItemSpriteExtra::create(CircleButtonSprite::create(CCSprite::create("HigherButton.png"_spr)), this, menu_selector(CustomLevelCell::onButtonHigher));
					mainMenu->addChild(buttonHigher);
					buttonHigher->setID("HigherButton"_spr);
					buttonHigher->setPosition(CCPoint(25, cellHeight/2 - 160));
				}
			}
			else
			{
				//deleting items outside this branch
				mainMenu->removeChildByID("LowerButton"_spr);
				mainMenu->removeChildByID("HigherButton"_spr);


				CCMenuItemSpriteExtra* restart = (CCMenuItemSpriteExtra*)mainMenu->getChildByID("RestartButton"_spr);
				CCLabelBMFont* label = (CCLabelBMFont*)mainMenu->getChildByID("Scorelabel"_spr);

				if (restart == NULL)
				{
					restart = CCMenuItemSpriteExtra::create(CCSprite::createWithSpriteFrameName("GJ_updateBtn_001.png"), this, menu_selector(CustomLevelCell::onRestart));
					mainMenu->addChild(restart);
					restart->setID("RestartButton"_spr);
					restart->setPosition(CCPoint(0, cellHeight / 2 - 160));
				}

				mainLayer->getChildByID("downloads-icon")->setVisible(true);
				mainLayer->getChildByID("downloads-label")->setVisible(true);
				mainLayer->updateLayout(false);
			}
		}

		return;
	}
};