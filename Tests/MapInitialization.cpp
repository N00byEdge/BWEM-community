#include "bwem.h"
#include "mapImpl.h"
#include "DummyBWAPIMap.h"

#include "gtest/gtest.h"

TEST(MapInitialization, MapInitiallyNotInitialized) {
	BWEM::detail::MapImpl map;

	DummyBWAPIMap dummyMap;

	EXPECT_EQ(false, map.Initialized());
}

TEST(MapInitialization, MapInitialized) {
	BWEM::detail::MapImpl map;
	
	DummyBWAPIMap dummyMap;

	map.Initialize(&dummyMap);
	EXPECT_EQ(true, map.Initialized());
}
