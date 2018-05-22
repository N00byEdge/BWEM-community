#if 0
#include "bwem.h"
#include "mapImpl.h"
#include "DummyBWAPIMap.h"
#include "MapTest.hpp"

#include "gtest/gtest.h"

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

TEST(MapInitialization, MapInitializedUsingOpenBW) {
  BWEM::detail::MapImpl map;

  runOnMap("data/maps/(2)Showdown.scx", [&](auto game) {
    map.Initialize(game);
  });

	EXPECT_EQ(true, map.Initialized());
}
#endif
