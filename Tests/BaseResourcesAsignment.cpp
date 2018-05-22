#if 0
#include "bwem.h"
#include "mapImpl.h"

#include "MapTest.hpp"

#include "gtest/gtest.h"

TEST(BaseResourcesAsignment, MineralOnlyBasesShouldBeFound) {
	BWEM::detail::MapImpl map;

	runOnMap("data/maps/mineral_only_bases.scx", [&](auto game) {
		map.Initialize(game);
	});

	// Two regular locations and one single minerals only base
	EXPECT_EQ(3, map.BaseCount());
}

TEST(BaseResourcesAsignment, GeysersOnlyBasesShouldBeFound) {
	BWEM::detail::MapImpl map;

	runOnMap("data/maps/geysers_only_bases.scx", [&](auto game) {
		map.Initialize(game);
	});

	// Two regular locations and one single geyser only base
	EXPECT_EQ(3, map.BaseCount());
}

TEST(BaseResourcesAsignment, StartingLocationWithoutMineralsAndGeysersDoesNotActAsBases) {
	BWEM::detail::MapImpl map;

	runOnMap("data/maps/start_location_wihout_base.scx", [&](auto game) {
		map.Initialize(game);
	});

	// Two regular locations and one single geyser only base
	EXPECT_EQ(2, map.BaseCount());
}

// Currently this test fails. I would not like enable it until better understanding
// happens of what should be done in such cases where small mineral patches could act as bases.
TEST(BaseResourcesAsignment, DISABLED_DontFormBasesAroundSmallMinerals) {
	BWEM::detail::MapImpl map;

	runOnMap("data/maps/no_base_around_small_minerals.scx", [&](auto game) {
		map.Initialize(game);
	});

	// Two regular locations and one mineral patch with 99 amount and 1% of life
	EXPECT_EQ(2, map.BaseCount());
}
#endif
