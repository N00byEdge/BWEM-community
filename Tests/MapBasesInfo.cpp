#include "bwem.h"
#include "mapImpl.h"
#include "BWAPI/GameImpl.h"
#include "BW/BWData.h"

#include "gtest/gtest.h"

TEST(MapBasesInfo, MapFindBasesForStartingLocations) {
	BWEM::detail::MapImpl map;

	BW::GameOwner gameOwner;

	gameOwner.setPrintTextCallback([](const char* str) {
		std::string s;
		while (*str) {
			char c = *str++;
			if (static_cast<unsigned>(c) >= 0x20 || c == 9 || c == 10 || c == 13) s += c;
		}
		printf("%s\n", s.c_str());
	});

	BWAPI::BroodwarImpl_handle h(gameOwner.getGame());
	h->setCharacterName("bwapi");
	h->setGameType(BWAPI::GameTypes::Melee);
	BWAPI::BroodwarImpl.bwgame.setMapFileName("data\\maps\\(2)Showdown.scx");
	h->createSinglePlayerGame([&h]()
	{
		if (!h->self())
		{
			auto firstPlayer = h->getPlayer(0);
			h->switchToPlayer(firstPlayer);
		}
		else
		{
			auto self = h->self();
			self->setRace(BWAPI::Races::Terran);
			h->startGame();
		}
	});
	map.Initialize(&(*h));
	EXPECT_EQ(true, map.FindBasesForStartingLocations());
}

TEST(MapBasesInfo, MapStartLocationCount2PlayersMap) {
	BWEM::detail::MapImpl map;

	BW::GameOwner gameOwner;

	gameOwner.setPrintTextCallback([](const char* str) {
		std::string s;
		while (*str) {
			char c = *str++;
			if (static_cast<unsigned>(c) >= 0x20 || c == 9 || c == 10 || c == 13) s += c;
		}
		printf("%s\n", s.c_str());
	});

	BWAPI::BroodwarImpl_handle h(gameOwner.getGame());
	h->setCharacterName("bwapi");
	h->setGameType(BWAPI::GameTypes::Melee);
	BWAPI::BroodwarImpl.bwgame.setMapFileName("data\\maps\\(2)Showdown.scx");
	h->createSinglePlayerGame([&h]()
	{
		if (!h->self())
		{
			auto firstPlayer = h->getPlayer(0);
			h->switchToPlayer(firstPlayer);
		}
		else
		{
			auto self = h->self();
			self->setRace(BWAPI::Races::Terran);
			h->startGame();
		}
	});
	map.Initialize(&(*h));
	map.FindBasesForStartingLocations();
	EXPECT_EQ(2, map.StartingLocations().size());
}

TEST(MapBasesInfo, MapBaseCount) {
	BWEM::detail::MapImpl map;

	BW::GameOwner gameOwner;

	gameOwner.setPrintTextCallback([](const char* str) {
		std::string s;
		while (*str) {
			char c = *str++;
			if (static_cast<unsigned>(c) >= 0x20 || c == 9 || c == 10 || c == 13) s += c;
		}
		printf("%s\n", s.c_str());
	});

	BWAPI::BroodwarImpl_handle h(gameOwner.getGame());
	h->setCharacterName("bwapi");
	h->setGameType(BWAPI::GameTypes::Melee);
	BWAPI::BroodwarImpl.bwgame.setMapFileName("data\\maps\\(2)Showdown.scx");
	h->createSinglePlayerGame([&h]()
	{
		if (!h->self())
		{
			auto firstPlayer = h->getPlayer(0);
			h->switchToPlayer(firstPlayer);
		}
		else
		{
			auto self = h->self();
			self->setRace(BWAPI::Races::Terran);
			h->startGame();
		}
	});
	map.Initialize(&(*h));
	EXPECT_EQ(8, map.BaseCount());
}