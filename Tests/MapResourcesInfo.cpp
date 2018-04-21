#include "bwem.h"
#include "mapImpl.h"

#include "MapTest.hpp"

#include "gtest/gtest.h"

TEST(MapResourcesInfo, MapGeyserCount) {
	BWEM::detail::MapImpl map;

  runOnMap("data/maps/(2)Showdown.scx", [&](auto game) {
    map.Initialize(game);
  });

	EXPECT_EQ(6, map.Geysers().size());
}

TEST(MapResourcesInfo, MapMineralCount) {
	BWEM::detail::MapImpl map;

  runOnMap("data/maps/(2)Showdown.scx", [&](auto game) {
    map.Initialize(game);
  });

	EXPECT_EQ(46, map.Minerals().size());
}