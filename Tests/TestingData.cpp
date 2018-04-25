#include <vector>

std::vector<std::string> mapsForTest = {
	"data/maps/(2)Showdown.scx",
	"data/maps/onlywater.scm",
	"data/maps/onlydirt.scm",
};

std::vector<std::pair<int, int>> mapTileDimensions = {
	{ 64, 192 },
	{ 128, 128 },
	{ 128, 128 },
};

std::vector<std::pair<int, int>> mapWalkDimensions = {
	{ 256, 768 },
	{ 512, 512 },
	{ 512, 512 },
};

std::vector<std::pair<int, int>> mapCenterPositions = {
	{ 1024, 3072 },
	{ 2048, 2048 },
	{ 2048, 2048 },
};

std::vector<std::pair<int, int>> mapAltitudeLimits = {
	{ 0, 426 },
	{ 0, 66 },		// Could not calculate this value manually. It seems very large for me.
					// I have to probably create a too for dumping altitudes in the txt file
	{ 0, 2032 },	// This value = 2048 - 16, but should be 2048, since from both borders this is maximal distance to edges.
					// how this become less then 2048 not clear for me.
};

std::vector<std::string> sscaitMaps = {
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
	"data/maps/sscai/(4)Roadrunner.scx",
};

std::vector<std::pair<int, int>> sscaitMapTileDimensions = {
	{ 128, 112 },
	{ 96, 128 },
	{ 128, 96 },

	{ 128, 128 },
	{ 128, 128 },

	{ 128, 128 },
	{ 128, 128 },
	{ 128, 128 },
	{ 128, 128 },
	{ 128, 128 },
	{ 128, 128 },
	{ 128, 128 },
	{ 128, 128 },
	{ 128, 128 },
	{ 128, 128 },
};

std::vector<std::pair<int, int>> sscaitMapWalkDimensions = {
	{ 512, 448 },
	{ 384, 512 },
	{ 512, 384 },

	{ 512, 512 },
	{ 512, 512 },

	{ 512, 512 },
	{ 512, 512 },
	{ 512, 512 },
	{ 512, 512 },
	{ 512, 512 },
	{ 512, 512 },
	{ 512, 512 },
	{ 512, 512 },
	{ 512, 512 },
	{ 512, 512 },
};

std::vector<std::pair<int, int>> sscaitMapCenterPositions = {
	{ 2048, 1792 },
	{ 1536, 2048 },
	{ 2048, 1536 },

	{ 2048, 2048 },
	{ 2048, 2048 },

	{ 2048, 2048 },
	{ 2048, 2048 },
	{ 2048, 2048 },
	{ 2048, 2048 },
	{ 2048, 2048 },
	{ 2048, 2048 },
	{ 2048, 2048 },
	{ 2048, 2048 },
	{ 2048, 2048 },
	{ 2048, 2048 },
};

std::vector<std::pair<int, int>> sscaitMapAltitudeLimits = {
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },

	{ 0, 0 },
	{ 0, 0 },

	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
};