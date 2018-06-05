#include "ExampleAIModule.h"

#include <cassert>
#include <iostream>

#include <bwem.h>
#include <mapPrinter.h>

#include "../../examples.h"

using namespace BWAPI;
using namespace Filter;

void ExampleAIModule::onStart()
{
  // Print the map name.
  // BWAPI returns std::string when retrieving a string, don't forget to add .c_str() when printing!
  Broodwar << "The map is " << Broodwar->mapName() << "!" << std::endl;

  // Enable the UserInput flag, which allows us to control the bot and type messages.
  Broodwar->enableFlag(Flag::UserInput);

  // Uncomment the following line and the bot will know about everything through the fog of war (cheat).
  //Broodwar->enableFlag(Flag::CompleteMapInformation);

  // Set the command optimization level so that common commands can be grouped
  // and reduce the bot's APM (Actions Per Minute).
  Broodwar->setCommandOptimizationLevel(2);

  try {
	  // Enable the UserInput flag, which allows us to control the bot and type messages.
	  Broodwar->enableFlag(Flag::UserInput);

	  // Uncomment the following line and the bot will know about everything through the fog of war (cheat).
	  //Broodwar->enableFlag(Flag::CompleteMapInformation);

	  // Set the command optimization level so that common commands can be grouped
	  // and reduce the bot's APM (Actions Per Minute).
	  Broodwar->setCommandOptimizationLevel(2);

	  // Initialize BWEM.
	  BWEM::Map::Instance().Initialize(BroodwarPtr);
	  BWEM::Map::Instance().EnableAutomaticPathAnalysis();
	  bool startingLocationsOK = BWEM::Map::Instance().FindBasesForStartingLocations();
	  assert(startingLocationsOK);
	  BWEM::utils::MapPrinter::Initialize(&(BWEM::Map::Instance()));
	  BWEM::utils::printMap(BWEM::Map::Instance()); // will print the map into the file <StarCraftFolder>bwapi-data/map.bmp
	  BWEM::utils::pathExample(BWEM::Map::Instance()); // add to the printed map a path between two starting locations
  }
  catch (const std::exception &e) {
	  Broodwar << "EXCEPTION: " << e.what() << std::endl;
  }
}

void ExampleAIModule::onEnd(bool isWinner)
{
}

void ExampleAIModule::onFrame()
{
	try {
		BWEM::utils::gridMapExample(BWEM::Map::Instance(), BWAPI::Broodwar);
		BWEM::utils::drawMap(BWEM::Map::Instance(), BWAPI::BroodwarPtr);
	}
	catch (const std::exception & e) {
		Broodwar << "EXCEPTION: " << e.what() << std::endl;
	}
}

void ExampleAIModule::onSendText(std::string text)
{
	Broodwar->sendText("%s", text.c_str());
}

void ExampleAIModule::onReceiveText(BWAPI::Player player, std::string text)
{
}

void ExampleAIModule::onPlayerLeft(BWAPI::Player player)
{
}

void ExampleAIModule::onNukeDetect(BWAPI::Position target)
{
}

void ExampleAIModule::onUnitDiscover(BWAPI::Unit unit)
{
}

void ExampleAIModule::onUnitEvade(BWAPI::Unit unit)
{
}

void ExampleAIModule::onUnitShow(BWAPI::Unit unit)
{
}

void ExampleAIModule::onUnitHide(BWAPI::Unit unit)
{
}

void ExampleAIModule::onUnitCreate(BWAPI::Unit unit)
{
}

void ExampleAIModule::onUnitDestroy(BWAPI::Unit unit)
{
	try {
		if (unit->getType().isMineralField()) BWEM::Map::Instance().OnMineralDestroyed(unit);
		else if (unit->getType().isSpecialBuilding()) BWEM::Map::Instance().OnStaticBuildingDestroyed(unit);
	}
	catch (const std::exception & e) {
		Broodwar << "EXCEPTION: " << e.what() << std::endl;
	}
}

void ExampleAIModule::onUnitMorph(BWAPI::Unit unit)
{
}

void ExampleAIModule::onUnitRenegade(BWAPI::Unit unit)
{
}

void ExampleAIModule::onSaveGame(std::string gameName)
{
}

void ExampleAIModule::onUnitComplete(BWAPI::Unit unit)
{
}
