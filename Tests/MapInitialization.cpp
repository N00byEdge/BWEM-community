#include "bwem.h"
#include "mapImpl.h"
#include "DummyBWAPIMap.h"
#include "MapTest.hpp"

#include "gtest/gtest.h"

class MapInitializationInfo : public ::testing::TestWithParam<std::string> {
};


TEST(MapInitialization, MapInitiallyNotInitialized) {
	BWEM::detail::MapImpl map;

	EXPECT_EQ(false, map.Initialized());
}

TEST(MapInitialization, MapInitialized) {
	BWEM::detail::MapImpl map;

	DummyBWAPIMap dummyMap;

	map.Initialize(&dummyMap);
	EXPECT_EQ(true, map.Initialized());
}

TEST_P(MapInitializationInfo, MapInitializedUsingOpenBW) {
	BWEM::detail::MapImpl map;

	auto mapName = GetParam();
	runOnMap(mapName, [&](auto game) {
		map.Initialize(game);
	});

	EXPECT_EQ(true, map.Initialized());
}

INSTANTIATE_TEST_CASE_P(
	SynteticCheck,
	MapInitializationInfo,
	::testing::Values(
		"data/maps/(2)Showdown.scx",
		"data/maps/(4)Sparkle 1.1.scx"
	));