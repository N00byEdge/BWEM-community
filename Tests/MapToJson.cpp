#if 0

#include <string>
#include <iomanip>
#include "bwem.h"
#include "mapImpl.h"
#include "MapTest.hpp"

#include "gtest/gtest.h"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

namespace BWAPI
{
	void to_json(json & j, TilePosition p)
	{
		j = { "tile", p.x, p.y };
	}

	void to_json(json & j, WalkPosition p)
	{
		j = { "walk", p.x, p.y };
	}

	void to_json(json & j, Position p)
	{
		j = { "pixel", p.x, p.y };
	}
}

namespace BWEM
{
	void to_json(json & j, Ressource const & r)
	{
		j["location"] = r.Pos();
		// Must call InitialAmount here, not Amount,
		// because we're out of scope of the BWAPI Game.
		j["amount"] = r.InitialAmount();
	}
}

json base_minerals(BWEM::Base const & base)
{
	json ret;
	for (auto const & mineral : base.Minerals())
		ret.push_back(*mineral);
	return ret;
}

json base_geysers(BWEM::Base const & base)
{
	json ret;
	for (auto const & geyser : base.Geysers())
		ret.push_back(*geyser);
	return ret;
}

namespace BWEM
{
	void to_json(json& j, Base const & base)
	{
		j["starting_location"] = base.Starting();
		j["tile_location"] = base.Location();
		j["center"] = base.Center();
		j["minerals"] = base_minerals(base);
		j["geysers"] = base_geysers(base);
	}
}

json map_bases(BWEM::detail::MapImpl const & map)
{
	json ret;

	for (auto const & area : map.Areas())
		for (auto const & base : area.Bases())
			ret.push_back(base);
	
	return ret;
}

json map_resources(BWEM::detail::MapImpl const & map)
{
	json ret;

	ret["number_geysers"] = map.Geysers().size();
	ret["number_minerals"] = map.Minerals().size();

	return ret;
}

json mapToJson(BWEM::detail::MapImpl const & map)
{
	json ret;

	ret["tile_dimensions"] = map.Size();
	ret["walk_dimensions"] = map.WalkSize();
	ret["center_position"] = map.Center();
	ret["altitude_limit"] = map.MaxAltitude();

	ret["resources"] = map_resources(map);
	ret["bases"] = map_bases(map);

	return ret;
}

TEST(test, test)
{
	BWEM::detail::MapImpl map;
	std::string mapName = "data/maps/onlydirt.scx";

	runOnMap(mapName, [&](auto game) {
		map.Initialize(game);
		map.FindBasesForStartingLocations();
	});

	std::cerr << std::setw(4) << mapToJson(map) << "\n";
}
#endif
