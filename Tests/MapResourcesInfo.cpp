#if 1
#include "bwem.h"
#include "mapImpl.h"
#include <optional>

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
	std::vector<MapResourcesTestParameters> const & v)
{
	std::vector<MapResourcesTestParameters> params;

	for (auto const & test : v) {
		std::string root = test.mapName.substr(0, test.mapName.size() - 3);
		std::cout << root << "json" << std::endl;
		std::ifstream json_file("../Tests/" + root + "json");
		if (!json_file) {
			params.emplace_back(
				test.mapName,
				"could not open JSON file"
			);
		}
		else {
			nlohmann::json json;
			json_file >> json;

			if (json["resources"]["number_geysers"] != test.expectedGeysers) {
				std::cerr << "number_geyesers bad\n";
				abort();
			}
			else if (json["resources"]["number_minerals"] != test.expectedMinerals) {
				std::cerr << "number_minerals bad\n";
				abort();
			}
			else {
				params.emplace_back(
					test.mapName,
					json["resources"]["number_geysers"],
					json["resources"]["number_minerals"]
				);
			}
		}
	}
	return params;
}

INSTANTIATE_TEST_CASE_P(
	SynteticCheck,
	MapResourcesInfo,
	::testing::ValuesIn(getTestData({
		MapResourcesTestParameters("data/maps/(2)Showdown.scx", 6, 46),

		// Map without resources
		MapResourcesTestParameters("data/maps/onlydirt.scm", 0, 0),

		// Open BW does not support small-sized minerals and gases
		// See when https://github.com/OpenBW/openbw/issues/19 resolved to unlock
		// MapResourcesTestParameters("data/maps/resources.scm", 3 /* + 9 small gases */, 13 /* + 4 small minerals */),
		MapResourcesTestParameters("data/maps/resources_usual.scm", 3, 13),

		// In this map all minerals and geysers have just 1% of their total amount 
		// of 1500 minerals or 5000 gas
		MapResourcesTestParameters("data/maps/resources_smallamount.scm", 3, 13)
	})));



INSTANTIATE_TEST_CASE_P(
	SSCAITMaps,
	MapResourcesInfo,
	::testing::ValuesIn(getTestData({
		MapResourcesTestParameters("data/maps/sscai/(2)Benzene.scx", 10, 86),
		MapResourcesTestParameters("data/maps/sscai/(2)Destination.scx", 10, 128),
		MapResourcesTestParameters("data/maps/sscai/(2)Heartbreak Ridge.scx", 10, 120),

		MapResourcesTestParameters("data/maps/sscai/(3)Neo Moon Glaive.scx", 12, 84),
		MapResourcesTestParameters("data/maps/sscai/(3)Tau Cross.scx", 9, 93),

		MapResourcesTestParameters("data/maps/sscai/(4)Andromeda.scx", 14, 126),
		MapResourcesTestParameters("data/maps/sscai/(4)Circuit Breaker.scx", 12, 124),
		MapResourcesTestParameters("data/maps/sscai/(4)Electric Circuit.scx", 12, 148),
		MapResourcesTestParameters("data/maps/sscai/(4)Empire of the Sun.scm", 14, 114),
		MapResourcesTestParameters("data/maps/sscai/(4)Fighting Spirit.scx", 14, 108),
		MapResourcesTestParameters("data/maps/sscai/(4)Icarus.scm", 12, 96),
		MapResourcesTestParameters("data/maps/sscai/(4)Jade.scx", 12, 96),
		MapResourcesTestParameters("data/maps/sscai/(4)La Mancha1.1.scx", 12, 96),
		MapResourcesTestParameters("data/maps/sscai/(4)Python.scx", 12, 110),
		MapResourcesTestParameters("data/maps/sscai/(4)Roadrunner.scx", 12, 96)
	})));
#endif
