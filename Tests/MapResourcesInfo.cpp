#if 1
#include "bwem.h"
#include "mapImpl.h"
#include <optional>
#include <string_view>

#include "MapTest.hpp"

#include "nlohmann/json.hpp"
#include "gtest/gtest.h"

struct MapResourcesTestParameters
{
	std::string mapName;
	int expectedMinerals;
	int expectedGeysers;
	std::optional<std::string> maybeError;

	MapResourcesTestParameters(std::string n, int g, int m)
		: mapName(std::move(n)), expectedMinerals(m), expectedGeysers(g)
	{}

	MapResourcesTestParameters(std::string n, std::string e)
		: mapName(std::move(n))
		, expectedMinerals(-1)
		, expectedGeysers(-1)
		, maybeError(std::move(e))
	{}
};

class MapResourcesInfo : public ::testing::TestWithParam<MapResourcesTestParameters> {
};

TEST_P(MapResourcesInfo, MapGeyserCount) {
	BWEM::detail::MapImpl map;
	
	auto param = GetParam();
	auto mapName = param.mapName;
	auto expectedGeysersCount = param.expectedGeysers;
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
	auto mapName = param.mapName;
	auto expectedMineralsCount = param.expectedMinerals;
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

std::vector<MapResourcesTestParameters> getTestData(
	std::vector<std::string> const & v)
{
	std::vector<MapResourcesTestParameters> params;

	for (auto const & test : v) {
		std::string root = test.substr(0, test.size() - 3);
		std::cout << root << "json" << std::endl;
		std::ifstream json_file("../Tests/" + root + "json");
		if (!json_file) {
			params.emplace_back(
				test,
				"could not open JSON file"
			);
		}
		else {
			nlohmann::json json;
			json_file >> json;

			params.emplace_back(
				test,
				json["resources"]["number_geysers"],
				json["resources"]["number_minerals"]
			);
		}
	}
	return params;
}

INSTANTIATE_TEST_CASE_P(
	SynteticCheck,
	MapResourcesInfo,
	::testing::ValuesIn(getTestData({
		"data/maps/(2)Showdown.scx",

		// Map without resources
		"data/maps/onlydirt.scm",

		// Open BW does not support small-sized minerals and gases
		// See when https://github.com/OpenBW/openbw/issues/19 resolved to unlock
		// MapResourcesTestParameters("data/maps/resources.scm", 3 /* + 9 small gases */, 13 /* + 4 small minerals */),
		"data/maps/resources_usual.scm",

		// In this map all minerals and geysers have just 1% of their total amount 
		// of 1500 minerals or 5000 gas
		"data/maps/resources_smallamount.scm"
	})));



INSTANTIATE_TEST_CASE_P(
	SSCAITMaps,
	MapResourcesInfo,
	::testing::ValuesIn(getTestData({
		"data/maps/sscai/(2)Benzene.scx",
		"data/maps/sscai/(2)Destination.scx",
		"data/maps/sscai/(2)Heartbreak Ridge.scx",

		"data/maps/sscai/(3)Neo Moon Glaive.scx",
		"data/maps/sscai/(3)Tau Cross.scx",

		"data/maps/sscai/(4)Andromeda.scx",
		"data/maps/sscai/(4)Circuit Breaker.scx",
		"data/maps/sscai/(4)Electric Circuit.scx",
		"data/maps/sscai/(4)Empire of the Sun.scm",
		"data/maps/sscai/(4)Fighting Spirit.scx",
		"data/maps/sscai/(4)Icarus.scm",
		"data/maps/sscai/(4)Jade.scx",
		"data/maps/sscai/(4)La Mancha1.1.scx",
		"data/maps/sscai/(4)Python.scx",
		"data/maps/sscai/(4)Roadrunner.scx"
	})));
#endif
