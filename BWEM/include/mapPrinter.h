//////////////////////////////////////////////////////////////////////////
//
// This file is part of the BWEM Library.
// BWEM is free software, licensed under the MIT/X11 License. 
// A copy of the license is provided with the library in the LICENSE file.
// Copyright (c) 2015, 2017, Igor Dimitrijevic
//
//////////////////////////////////////////////////////////////////////////

#pragma once

#ifdef BWEM_USE_MAP_PRINTER

#include <BWAPI.h>
#include <memory>
#include "utils.h"
#include "defs.h"

namespace BWEM {
class Map;
namespace utils {



//////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                          //
//                                  class MapPrinter
//                                                                                          //
//////////////////////////////////////////////////////////////////////////////////////////////
//


class MapPrinter
{
public:
	static const bool		showAltitude;				// renders the Altitude() value for each MiniTile
	static const bool		showAreas;					// renders Areas with distinct colors
	static const bool		showContinents;				// renders continents with distinct colors, unless showAreas == true
	static const bool		showLakes;					// prints unwalkable MiniTiles in Areas
	static const bool		showSeaSide;				// highlights Sea-MiniTiles next to Terrain-MiniTiles
	static const bool		showUnbuildable;			// renders Tiles that are not Buildable()
	static const bool		showGroundHeight;			// renders Tiles for which GroundHeight() > 0
	static const bool		showChokePoints;			// renders the ChokePoints suggested by BWEM
	static const bool		showResources;
	static const bool		showMinerals;				// prints the Minerals, unless showResources == false
	static const bool		showGeysers;				// prints the Geysers, unless showResources == false
	static const bool		showStaticBuildings;		// prints the StaticBuildings
	static const bool		showBlockingBuildings;		// renders the StaticBuildings and the Minerals that are blocking some ChokePoint
	static const bool		showStackedNeutrals;		// renders the StaticBuildings and the Minerals that are stacked
	static const bool		showStartingLocations;		// renders the Bases that are at starting locations
	static const bool		showBases;					// prints the Bases suggested by BWEM
	static const bool		showAssignedRessources;		// renders the Ressources assigned to each Base, unless showBases == false
	static const bool		showData;					// renders the Data() value for each MiniTile

	struct Color
	{
		static const Color		higherGround;
		static const Color		unbuildable;
		static const Color		terrain;
		static const Color		sea;
		static const Color		seaSide;
		static const Color		lake;
		static const Color		tinyArea;
		static const Color		chokePoints;
		static const Color		minerals;
		static const Color		geysers;
		static const Color		staticBuildings;
		static const Color		blockingNeutrals;
		static const Color		startingLocations;
		static const Color		bases;

		Color() : red(0), green(0), blue(0) {}
		Color(int r, int g, int b) : red(uint8_t(r)), green(uint8_t(g)), blue(uint8_t(b))
		{
			bwem_assert(
				utils::CanTypeFitValue<uint8_t>(r) && 
				utils::CanTypeFitValue<uint8_t>(g) && 
				utils::CanTypeFitValue<uint8_t>(b));
		}

		uint8_t red;
		uint8_t green;
		uint8_t blue;
	};


	static void					Initialize(const Map * pMap);
	static MapPrinter &			Get()						{ bwem_assert_throw_plus(m_pMap, "MapPrinter not initialized"); return m_Instance; }

	enum dashed_t {not_dashed, dashed};
	enum fill_t {do_not_fill, fill};

	void						Point(int x, int y, Color col);
	void						Point(BWAPI::WalkPosition p, Color col) { Point(p.x, p.y, col); }

	void						Line(BWAPI::WalkPosition A, BWAPI::WalkPosition B, Color col, dashed_t dashedMode = not_dashed);

	void						Rectangle(BWAPI::WalkPosition TopLeft, BWAPI::WalkPosition BottomRight, Color col, fill_t fillMode = do_not_fill, dashed_t dashedMode = not_dashed);

	// This function will automatically crop the square so that it fits in the Map.
	void						Square(BWAPI::WalkPosition Center, int radius, Color col, fill_t fillMode = do_not_fill);

	// This function will automatically crop the circle so that it fits in the Map.
	void						Circle(BWAPI::WalkPosition Center, int radius, Color col, fill_t fillMode = do_not_fill);

								MapPrinter(const MapPrinter &) = delete;
	MapPrinter &				operator=(const MapPrinter &) = delete;

private:

	class MigImage
	{
	public:
		MigImage() = delete;

		MigImage(const int width, const int height)
			: _width(width)
			, _height(height)
			, _pixels(std::make_unique<RgbPixel[]>(size_t(width) * size_t(height)))
		{
			for (int y = 0; y < _height; ++y) {
				for (int x = 0; x < _width; ++x) {
					drawPixel(x, y, 0, 0, 0);
				}
			}
		}

		void drawPixel(const int x, const int y, const unsigned char red, const unsigned char green, const unsigned char blue)
		{
			const auto index = calculateIndex(x, y);
			auto &pixel = _pixels[index];
			pixel.r = red;
			pixel.g = green;
			pixel.b = blue;
		}

		bool isValid(const int x, const int y) const noexcept { return (x >= 0 && x < _width && y >= 0 && y < _height); }
		void writeToPNG(const std::string &filename) const;

	private:
		struct RgbPixel
		{
			static const unsigned char comp = 3;

			unsigned char r;
			unsigned char g;
			unsigned char b;

			RgbPixel() : r(0), g(0), b(0) {}
			RgbPixel(const unsigned char red, const unsigned char green, const unsigned char blue) : r(red), g(green), b(blue) {}
		};

		const int _width;
		const int _height;
		std::unique_ptr<RgbPixel[]> _pixels;

		size_t calculateIndex(const int x, const int y) const noexcept { return size_t(_width) * size_t(y) + size_t(x); }

		void copyRgbPixelsTo(std::unique_ptr<unsigned char[]> &pixelData) const
		{
			size_t index = 0;
			for (int y = 0; y < _height; ++y) {
				for (int x = 0; x < _width; ++x) {
					const auto &pixel = _pixels[calculateIndex(x, y)];
					pixelData[index++] = pixel.r;
					pixelData[index++] = pixel.g;
					pixelData[index++] = pixel.b;
				}
			}
		}
	};
	static std::unique_ptr<MigImage> m_pImage;

								MapPrinter() = default;
								~MapPrinter();

	static MapPrinter			m_Instance;
	static const Map *			m_pMap;
	static const std::string	m_fileName;
};


}} // namespace BWEM::detail::detail

#endif // BWEM_USE_MAP_PRINTER

