#if 0
#include "bwem.h"
#include "mapImpl.h"

#include "MapTest.hpp"

#include "gtest/gtest.h"

typedef std::tuple<
	std::string,
	int,
	int> MapDimensionsTestParameters;

class MapResourcesInfo : public ::testing::TestWithParam<MapDimensionsTestParameters> {
};

TEST_P(MapResourcesInfo, MapGeyserCount) {
	BWEM::detail::MapImpl map;
	
	auto param = GetParam();
	auto mapName = std::get<0>(param);
	auto expectedGeysersCount = std::get<1>(param);
	auto countedGeysers = 0;

  runOnMap(mapName, [&](auto game) {
    map.Initialize(game);
	countedGeysers = game->getGeysers().size();
  });

	auto bwemCalculatedGeysersCount = map.Geysers().size();
	
	// BWEM report all gaysers independenctly on the amount of gas inside.
	EXPECT_EQ(countedGeysers, bwemCalculatedGeysersCount);
	EXPECT_EQ(expectedGeysersCount, bwemCalculatedGeysersCount);
}

TEST_P(MapResourcesInfo, MapMineralCount) {
	BWEM::detail::MapImpl map;

	auto param = GetParam();
	auto mapName = std::get<0>(param);
	auto expectedMineralsCount = std::get<2>(param);
	auto countedMinerals = 0;
  runOnMap(mapName, [&](auto game) {
    map.Initialize(game);
	countedMinerals = game->getMinerals().size();
  });

	auto bwemCalculatedMineralsCount = map.Minerals().size();
	
	// BWEM report all minerals independenctly on the amount of gas inside.
	EXPECT_EQ(countedMinerals, bwemCalculatedMineralsCount);
	EXPECT_EQ(expectedMineralsCount, bwemCalculatedMineralsCount);
}

INSTANTIATE_TEST_CASE_P(
	SynteticCheck,
	MapResourcesInfo,
	::testing::Values(
		std::make_tuple("data/maps/(2)Showdown.scx", 6, 46),

		// Map without resources
		std::make_tuple("data/maps/onlydirt.scm", 0, 0),
		
		// Open BW does not support small-sized minerals and gases
		// See when https://github.com/OpenBW/openbw/issues/19 resolved to unlock
		// std::make_tuple("data/maps/resources.scm", 3 /* + 9 small gases */, 13 /* + 4 small minerals */),
		std::make_tuple("data/maps/resources_usual.scm", 3, 13),

		// In this map all minerals and geysers have just 1% of their total amount 
		// of 1500 minerals or 5000 gas
		std::make_tuple("data/maps/resources_smallamount.scm", 3, 13)
	));

INSTANTIATE_TEST_CASE_P(
	SSCAITMaps,
	MapResourcesInfo,
	::testing::Values(
		std::make_tuple("data/maps/sscai/(2)Benzene.scx", 10, 86),
		std::make_tuple("data/maps/sscai/(2)Destination.scx", 10, 128),
		std::make_tuple("data/maps/sscai/(2)Heartbreak Ridge.scx", 10, 120),

		std::make_tuple("data/maps/sscai/(3)Neo Moon Glaive.scx", 12, 84),
		std::make_tuple("data/maps/sscai/(3)Tau Cross.scx", 9, 93),

		std::make_tuple("data/maps/sscai/(4)Andromeda.scx", 14, 126),
		std::make_tuple("data/maps/sscai/(4)Circuit Breaker.scx", 12, 124),
		std::make_tuple("data/maps/sscai/(4)Electric Circuit.scx", 12, 148),
		std::make_tuple("data/maps/sscai/(4)Empire of the Sun.scm", 14, 114),
		std::make_tuple("data/maps/sscai/(4)Fighting Spirit.scx", 14, 108),
		std::make_tuple("data/maps/sscai/(4)Icarus.scm", 12, 96),
		std::make_tuple("data/maps/sscai/(4)Jade.scx", 12, 96),
		std::make_tuple("data/maps/sscai/(4)La Mancha1.1.scx", 12, 96),
		std::make_tuple("data/maps/sscai/(4)Python.scx", 12, 110),
		std::make_tuple("data/maps/sscai/(4)Roadrunner.scx", 12, 96)
	));
#endif
