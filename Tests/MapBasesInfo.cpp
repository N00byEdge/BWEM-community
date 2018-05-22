#if 0
#include "bwem.h"
#include "mapImpl.h"

#include "MapTest.hpp"

#include "gtest/gtest.h"

TEST(MapBasesInfo, MapFindBasesForStartingLocations) {
	BWEM::detail::MapImpl map;

  runOnMap("data/maps/(2)Showdown.scx", [&](auto game) {
    map.Initialize(game);
  });

	EXPECT_EQ(true, map.FindBasesForStartingLocations());
}

TEST(MapBasesInfo, MapStartLocationCount2PlayersMap) {
	BWEM::detail::MapImpl map;

  runOnMap("data/maps/(2)Showdown.scx", [&](auto game) {
    map.Initialize(game);
  });

	EXPECT_EQ(2, map.StartingLocations().size());
}

TEST(MapBasesInfo, MapBaseCount) {
	BWEM::detail::MapImpl map;

  runOnMap("data/maps/(2)Showdown.scx", [&](auto game) {
    map.Initialize(game);
  });
	
	EXPECT_EQ(8, map.BaseCount());
}
#endif
