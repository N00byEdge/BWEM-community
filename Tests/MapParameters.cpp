#if 0
#include <tuple>
#include "bwem.h"
#include "mapImpl.h"

#include "MapTest.hpp"

#include "gtest/gtest.h"

typedef std::tuple<
	std::string,
	std::pair<int, int>,
	std::pair<int, int>,
	std::pair<int, int>,
	std::pair<int, int>> MapDimensionsTestParameters;

class MapDimensionsTest : public ::testing::TestWithParam<MapDimensionsTestParameters> {
};

TEST_P(MapDimensionsTest, VerifyDimensionsLoadedCorrectly) {
	BWEM::detail::MapImpl map;

	auto param = GetParam();
	auto mapName = std::get<0>(param);
	auto tileDimensions = std::get<1>(param);
	auto walkDimensions = std::get<2>(param);
	auto expectedCenter = std::get<3>(param);
	auto expectedMaxAltitude = std::get<4>(param);
	runOnMap(mapName, [&](auto game) {
		map.Initialize(game);
	});

	auto tileSize = map.Size();
	EXPECT_EQ(tileDimensions.first, tileSize.x);
	EXPECT_EQ(tileDimensions.second, tileSize.y);

	auto walkSize = map.WalkSize();
	EXPECT_EQ(walkDimensions.first, walkSize.x);
	EXPECT_EQ(walkDimensions.second, walkSize.y);

	auto center = map.Center();
	EXPECT_EQ(expectedCenter.first, center.x);
	EXPECT_EQ(expectedCenter.second, center.y);

	auto maxAltitude = map.MaxAltitude();
	EXPECT_EQ(expectedMaxAltitude.second, maxAltitude);
}

TEST(AltitudeTest, VerifyAltitudeCalculatedCorrectly) {
	BWEM::detail::MapImpl map;

	auto mapName = "data/maps/onlydirt.scm";
	runOnMap(mapName, [&](auto game) {
		map.Initialize(game);
	});

	auto leftTopCorner = map.GetMiniTile(BWAPI::WalkPosition(0, 0));
	EXPECT_EQ(8, leftTopCorner.Altitude());
	auto nearLeftTopCorner = map.GetMiniTile(BWAPI::WalkPosition(1, 1));
	EXPECT_EQ(16, nearLeftTopCorner.Altitude());

	// Around edge of the map in the bottom, there non walkable and non-accessible area
	// which is covered by the UI. That's why we don't have simple formula for calculation
	// altitude on trivial maps.
	auto nearRightBottomCorner = map.GetMiniTile(BWAPI::WalkPosition(510, 510));
	EXPECT_EQ(0, nearRightBottomCorner.Altitude());
	auto rightBottomCorner = map.GetMiniTile(BWAPI::WalkPosition(511, 511));
	EXPECT_EQ(0, rightBottomCorner.Altitude());

	// This is first walkable area not hidden by the UI
	// This is first in sense that if you find closest non-walkcable area hidden by UI
	// then if continue in the next direction closer to center.
	auto farRightBottomPosition = map.GetMiniTile(BWAPI::WalkPosition(491, 506));
	EXPECT_EQ(8, farRightBottomPosition.Altitude());

	auto maxAltitudePoint = map.GetMiniTile(BWAPI::WalkPosition(254, 254));
	EXPECT_EQ(2032, maxAltitudePoint.Altitude());

	auto mapCenter = map.GetMiniTile(BWAPI::WalkPosition(255, 255));
	EXPECT_EQ(2024, mapCenter.Altitude());
}

std::vector<MapDimensionsTestParameters> getTestData(
	std::vector<std::string> maps,
	std::vector<std::pair<int, int>> tileDimensions,
	std::vector<std::pair<int, int>> walkDimensions,
	std::vector<std::pair<int, int>> centerPositions,
	std::vector<std::pair<int, int>> altitudeLimits)
{
	auto tileIterator = tileDimensions.begin();
	auto walkIterator = walkDimensions.begin();
	auto centerIterator = centerPositions.begin();
	auto altitudeIterator = altitudeLimits.begin();
	std::vector<MapDimensionsTestParameters> parameters;
	for (auto map : maps)
	{
		parameters.push_back(std::make_tuple(
			map,
			*tileIterator,
			*walkIterator,
			*centerIterator,
			*altitudeIterator));
		tileIterator++;
		walkIterator++;
		centerIterator++;
		altitudeIterator++;
	}

	return parameters;
}

INSTANTIATE_TEST_CASE_P(
	SynteticCheck,
	MapDimensionsTest, 
	::testing::ValuesIn(getTestData(
		mapsForTest,
		mapTileDimensions,
		mapWalkDimensions,
		mapCenterPositions,
		mapAltitudeLimits)));

INSTANTIATE_TEST_CASE_P(
	SSCAITMaps,
	MapDimensionsTest,
	::testing::ValuesIn(getTestData(
		sscaitMaps,
		sscaitMapTileDimensions,
		sscaitMapWalkDimensions,
		sscaitMapCenterPositions,
		sscaitMapAltitudeLimits)));
#endif
