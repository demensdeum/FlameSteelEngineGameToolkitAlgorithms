#ifndef DMMAZEOBJECTGENERATORDEFINED
#define DMMAZEOBJECTGENERATORDEFINED

#include <memory>

using namespace std;

namespace FlameSteelCore {
class Object;
};

namespace FlameSteelEngine {
namespace GameToolkit {
class GameMap;
}
}

using namespace FlameSteelCore;
using namespace FlameSteelEngine::GameToolkit;

class FSGTAMazeObjectGenerator {

public:
	static shared_ptr<Object> generate(shared_ptr<GameMap> gameMap);
	static shared_ptr<string> generateCube(int x, int y, shared_ptr<string> textureName);

private:
	static void putFloorAtXY(shared_ptr<string> serializedMaze, int x, int y, int dotsCount);
	static void putLeftWallAtXY(shared_ptr<string> serializedMaze, int x, int y, int dotsCount);
	static void putRightWallAtXY(shared_ptr<string> serializedMaze, int x, int y, int dotsCount);
	static void putTopWallAtXY(shared_ptr<string> serializedMaze, int x, int y, int dotsCount);
	static void putDownWallAtXY(shared_ptr<string> serializedMaze, int x, int y, int dotsCount);

	static void putDotAtXYZ(shared_ptr<string> serializedMaze, int x, int y, int z, int u, int v);

};

#endif