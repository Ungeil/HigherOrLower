#include <Geode/Geode.hpp>
#include "utils/ServerUtils.hpp"
#include "HighLow.hpp"
using namespace geode::prelude;

//i hope this does not crash ._.
$on_mod(Loaded) 
{
	auto searchObj = GJSearchObject::create(SearchType(1));
	searchObj->m_difficulty = "-2";
	searchObj->m_demonFilter = GJDifficulty(0);
	for (int i = 0; i < 25; i++)
	{
		searchObj->m_page = i;
		ServerUtils::getOnlineLevels(searchObj, [](std::shared_ptr<std::vector<Ref<GJGameLevel>>> levels)
		{
			HighLow::addLevels(levels);
			if (g_data.levels.size() > 2) { 
				HighLow::reset(); 
				HighLow::generateNew();
			}
		});
	}
}