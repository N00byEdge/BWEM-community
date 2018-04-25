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

TEST_P(MapDimensionsTest, VerifyTileSizeLoadedCorrectly) {
	BWEM::detail::MapImpl map;

	auto param = GetParam();
	auto mapName = std::get<0>(param);
	auto tileDimensions = std::get<1>(param);
	runOnMap(mapName, [&](auto game) {
		map.Initialize(game);
	});

	auto size = map.Size();
	EXPECT_EQ(tileDimensions.first, size.x);
	EXPECT_EQ(tileDimensions.second, size.y);
}

TEST_P(MapDimensionsTest, VerifyWalkSizeLoadedCorrectly) {
	BWEM::detail::MapImpl map;

	auto param = GetParam();
	auto mapName = std::get<0>(param);
	auto walkDimensions = std::get<2>(param);
	runOnMap(mapName, [&](auto game) {
		map.Initialize(game);
	});

	auto size = map.WalkSize();
	EXPECT_EQ(walkDimensions.first, size.x);
	EXPECT_EQ(walkDimensions.second, size.y);
}

TEST_P(MapDimensionsTest, VerifyCenterCalculatedCorrectly) {
	BWEM::detail::MapImpl map;

	auto param = GetParam();
	auto mapName = std::get<0>(param);
	auto expectedCenter = std::get<3>(param);
	runOnMap(mapName, [&](auto game) {
		map.Initialize(game);
	});

	auto center = map.Center();
	EXPECT_EQ(expectedCenter.first, center.x);
	EXPECT_EQ(expectedCenter.second, center.y);
}

TEST_P(MapDimensionsTest, DISABLED_VerifyMaxAltitudeCalculatedCorrectly) {
	BWEM::detail::MapImpl map;

	auto param = GetParam();
	auto mapName = std::get<0>(param);
	auto expectedMaxAltitude = std::get<4>(param);
	runOnMap(mapName, [&](auto game) {
		map.Initialize(game);
	});

	auto maxAltitude = map.MaxAltitude();
	EXPECT_EQ(expectedMaxAltitude.second, maxAltitude);
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
