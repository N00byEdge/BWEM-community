#pragma once
#include <BWAPI.h>
#include <list>

class DummyBWAPIMap : public BWAPI::Game
{

	BWAPI::TilePosition::list startLocations;
	BWAPI::Forceset forces;
	BWAPI::Playerset _allies;
	BWAPI::Playerset _enemies;
	BWAPI::Playerset _observers;

	BWAPI::Playerset playerset;
	BWAPI::Unitset allUnits;
	BWAPI::Unitset minerals;
	BWAPI::Unitset gaysers;
	BWAPI::Unitset neutralUnits;
	BWAPI::Unitset staticMinerals;
	BWAPI::Unitset staticGaysers;
	BWAPI::Unitset staticNeutralUnits;
	BWAPI::Bulletset bullets;
	BWAPI::Position::list nukes;
	std::list< BWAPI::Event > events;
	BWAPI::Unitset selectedUnits;
	BWAPI::Regionset regions;
public:
	const BWAPI::Forceset& getForces() const { return forces; }

	const BWAPI::Playerset& getPlayers() const { return playerset; }

	const BWAPI::Unitset& getAllUnits() const { return allUnits; }

	const BWAPI::Unitset& getMinerals() const { return minerals; }

	const BWAPI::Unitset& getGeysers() const { return gaysers; }

	const BWAPI::Unitset& getNeutralUnits() const { return neutralUnits; }

	const BWAPI::Unitset& getStaticMinerals() const { return staticMinerals; }

	const BWAPI::Unitset& getStaticGeysers() const { return staticGaysers; }

	const BWAPI::Unitset& getStaticNeutralUnits() const { return staticNeutralUnits; }

	const BWAPI::Bulletset& getBullets() const { return bullets; }

	const BWAPI::Position::list& getNukeDots() const { return nukes; }

	const std::list< BWAPI::Event >& getEvents() const { return events; }

	BWAPI::Force getForce(int forceID) const { return nullptr; }

	BWAPI::Player getPlayer(int playerID) const { return nullptr; }

	BWAPI::Unit getUnit(int unitID) const { return nullptr; }

	BWAPI::Unit indexToUnit(int unitIndex) const { return nullptr; }

	BWAPI::Region getRegion(int regionID) const { return nullptr; }

	BWAPI::GameType getGameType() const { return BWAPI::GameType(); }

	int getLatency() const { return 0; }

	int getFrameCount() const { return 0; }

	int getReplayFrameCount() const { return 0; }

	int getFPS() const { return 0; }

	double getAverageFPS() const { return 0; }

	BWAPI::Position getMousePosition() const { return BWAPI::Position(); }

	bool getMouseState(BWAPI::MouseButton button) const { return false; }

	bool getKeyState(BWAPI::Key key) const { return false; }

	BWAPI::Position getScreenPosition() const { return BWAPI::Position(); }
	void setScreenPosition(int x, int y) {}

	void pingMinimap(int x, int y) {}

	bool isFlagEnabled(int flag) const { return false; }

	void enableFlag(int flag) {}

	BWAPI::Unitset getUnitsInRectangle(int left, int top, int right, int bottom, const BWAPI::UnitFilter &pred = nullptr) const
	{
		return BWAPI::Unitset();
	}

	BWAPI::Unit getClosestUnitInRectangle(BWAPI::Position center, const BWAPI::UnitFilter &pred = nullptr, int left = 0, int top = 0, int right = 999999, int bottom = 999999) const
	{
		return nullptr;
	}

	BWAPI::Unit getBestUnit(const BWAPI::BestUnitFilter &best, const BWAPI::UnitFilter &pred, BWAPI::Position center = BWAPI::Positions::Origin, int radius = 999999) const
	{
		return nullptr;
	}

	BWAPI::Error getLastError() const
	{
		return BWAPI::Errors::None;
	}

	bool setLastError(BWAPI::Error e = BWAPI::Errors::None) const
	{
		return false;
	}

	int mapWidth() const { return 64; }

	int mapHeight() const { return 64; }

	std::string mapFileName() const { return ""; }

	std::string mapPathName() const { return ""; }

	std::string mapName() const { return ""; }

	std::string mapHash() const { return ""; }

	bool isWalkable(int walkX, int walkY) const { return true; }

	int  getGroundHeight(int tileX, int tileY) const { return 0; }

	bool isBuildable(int tileX, int tileY, bool includeBuildings = false) const { return true; }

	bool isVisible(int tileX, int tileY) const { return true; }

	bool isExplored(int tileX, int tileY) const { return false; }

	bool hasCreep(int tileX, int tileY) const { return false; }

	bool hasPowerPrecise(int x, int y, BWAPI::UnitType unitType = BWAPI::UnitTypes::None) const { return false; }

	bool canBuildHere(BWAPI::TilePosition position, BWAPI::UnitType type, BWAPI::Unit builder = nullptr, bool checkExplored = false) { return false; }

	bool canMake(BWAPI::UnitType type, BWAPI::Unit builder = nullptr) const { return false; }
	bool canResearch(BWAPI::TechType type, BWAPI::Unit unit = nullptr, bool checkCanIssueCommandType = true) { return false; }

	bool canUpgrade(BWAPI::UpgradeType type, BWAPI::Unit unit = nullptr, bool checkCanIssueCommandType = true) { return false; }

	const BWAPI::TilePosition::list& getStartLocations() const { return startLocations; }

	void vPrintf(const char *format, va_list args) {}
	void vSendTextEx(bool toAllies, const char *format, va_list args) {}
	bool isInGame() const { return true; }
	bool isMultiplayer() const { return false; }
	bool isBattleNet() const { return false; }
	bool isPaused() const { return false; }
	bool isReplay() const { return false; }
	void pauseGame() {}
	void resumeGame() {}
	void leaveGame() {}
	void restartGame() {}
	void setLocalSpeed(int speed) {}
	bool issueCommand(const BWAPI::Unitset& units, BWAPI::UnitCommand command) { return false; }
	const BWAPI::Unitset& getSelectedUnits() const { return selectedUnits; }
	BWAPI::Player self() const { return nullptr; }
	BWAPI::Player enemy() const { return nullptr; }
	BWAPI::Player neutral() const { return nullptr; }
	BWAPI::Playerset& allies() { return _allies; }
	BWAPI::Playerset& enemies() { return _enemies; }
	BWAPI::Playerset& observers() { return _observers; }
	void setTextSize(BWAPI::Text::Size::Enum size = BWAPI::Text::Size::Default) {}
	void vDrawText(BWAPI::CoordinateType::Enum ctype, int x, int y, const char *format, va_list arg) {}
	void drawBox(BWAPI::CoordinateType::Enum ctype, int left, int top, int right, int bottom, BWAPI::Color color, bool isSolid = false) {};
	void drawTriangle(BWAPI::CoordinateType::Enum ctype, int ax, int ay, int bx, int by, int cx, int cy, BWAPI::Color color, bool isSolid = false) {}
	void drawCircle(BWAPI::CoordinateType::Enum ctype, int x, int y, int radius, BWAPI::Color color, bool isSolid = false) {}
	void drawEllipse(BWAPI::CoordinateType::Enum ctype, int x, int y, int xrad, int yrad, BWAPI::Color color, bool isSolid = false) {}
	void drawDot(BWAPI::CoordinateType::Enum ctype, int x, int y, BWAPI::Color color) {}
	void drawLine(BWAPI::CoordinateType::Enum ctype, int x1, int y1, int x2, int y2, BWAPI::Color color) {}
	int getLatencyFrames() const { return 0; }
	int getLatencyTime() const { return 0; }
	int getRemainingLatencyFrames() const { return 0; }
	int getRemainingLatencyTime() const { return 0; }
	int getRevision() const { return 0; }
	int getClientVersion() const { return 0; }
	bool isDebug() const { return false; }
	bool isLatComEnabled() const { return false; }
	void setLatCom(bool isEnabled) {}
	bool isGUIEnabled() const { return false; }
	void setGUI(bool isEnabled) {}
	int getInstanceNumber() const { return 0; }

	int getAPM(bool includeSelects = false) const { return 0; }
	bool setMap(const char *mapFileName) { return true; }
	void setFrameSkip(int frameSkip) {}
	bool setAlliance(BWAPI::Player player, bool allied = true, bool alliedVictory = true) {
		return true;
	}
	bool setVision(BWAPI::Player player, bool enabled = true) {
		return true;
	}

	int elapsedTime() const { return 0; }
	void setCommandOptimizationLevel(int level) {}
	int countdownTimer() const { return 0; }
	const BWAPI::Regionset &getAllRegions() const { return regions; }
	BWAPI::Region getRegionAt(int x, int y) const { return nullptr; }
	int getLastEventTime() const { return 0; }
	bool setRevealAll(bool reveal = true) { return true; }

	unsigned getRandomSeed() const { return 0U; }
};