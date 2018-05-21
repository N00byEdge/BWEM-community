#pragma once

#include "BWAPI/GameImpl.h"
#include "BW/BWData.h"

extern std::vector<std::string> mapsForTest;
extern std::vector<std::pair<int, int>> mapTileDimensions;
extern std::vector<std::pair<int, int>> mapWalkDimensions;
extern std::vector<std::pair<int, int>> mapCenterPositions;
extern std::vector<std::pair<int, int>> mapAltitudeLimits;

extern std::vector<std::string> sscaitMaps;
extern std::vector<std::pair<int, int>> sscaitMapTileDimensions;
extern std::vector<std::pair<int, int>> sscaitMapWalkDimensions;
extern std::vector<std::pair<int, int>> sscaitMapCenterPositions;
extern std::vector<std::pair<int, int>> sscaitMapAltitudeLimits;

template<typename Functor> void runOnMap(std::string const &mapName, Functor f) {
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
  BWAPI::BroodwarImpl.bwgame.setMapFileName(mapName);
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
  h->update();

  f(&(*h));
}
