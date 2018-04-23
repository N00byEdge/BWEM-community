#include <tuple>
#include "bwem.h"
#include "mapImpl.h"

#include "MapTest.hpp"

#include "gtest/gtest.h"

typedef std::tuple<std::string, std::pair<int, int>, std::pair<int, int>> MapDimensionsTestParameters;

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

std::vector<MapDimensionsTestParameters> getTestData(
	std::vector<std::string> maps,
	std::vector<std::pair<int, int>> tileDimensions,
	std::vector<std::pair<int, int>> walkDimensions)
{
	auto tileIterator = tileDimensions.begin();
	auto walkIterator = walkDimensions.begin();
	std::vector<MapDimensionsTestParameters> parameters;
	for (auto map : maps)
	{
		parameters.push_back(std::make_tuple(map, *tileIterator, *walkIterator));
		tileIterator++;
		walkIterator++;
	}

	return parameters;
}

INSTANTIATE_TEST_CASE_P(
	SynteticCheck,
	MapDimensionsTest, 
	::testing::ValuesIn(getTestData(mapsForTest, mapTileDimensions, mapWalkDimensions)));

INSTANTIATE_TEST_CASE_P(
	SSCAITMaps,
	MapDimensionsTest,
	::testing::ValuesIn(getTestData(sscaitMaps, sscaitMapTileDimensions, sscaitMapWalkDimensions)));
