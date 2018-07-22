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
	static shared_ptr<string> generateCube(int x, int z, shared_ptr<string> textureName);
	static shared_ptr<string> generatePlane(float width, float height, shared_ptr<string> textureName);
	static shared_ptr<string> generateBox(float width, float height, float length, float u, float v, shared_ptr<string> textureName);

private:
	static void putFloorAtXYZWidthHeightUV(shared_ptr<string> serializedMaze, float x, float y, float z, float width, float height, float u, float v, int dotsCount);
	static void putLeftWallAtXYZWidthHeightUV(shared_ptr<string> serializedMaze, float x, float y, float z, float width, float height, float u, float v, int dotsCount);
	static void putRightWallAtXYZWidthHeightUV(shared_ptr<string> serializedMaze, float x, float y, float z, float width, float height, float u, float v, int dotsCount);
	static void putTopWallAtXYZWidthHeightUV(shared_ptr<string> serializedMaze, float x, float y, float z, float width, float height, float u, float v, int dotsCount);
	static void putDownWallAtXYZWidthHeightUV(shared_ptr<string> serializedMaze, float x, float y, float z, float width, float height, float u, float v, int dotsCount);


	static void putDotAtXYZ(shared_ptr<string> serializedMaze, float x, float y, float z, float u, float v);

};

#endif