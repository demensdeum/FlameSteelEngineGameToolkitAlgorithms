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

namespace FlameSteelEngine {
namespace GameToolkit {
namespace Algorithms {
class SerializedModelConstructable {

public:
	SerializedModelConstructable(shared_ptr<string> modelText);
	void append(shared_ptr<string> string);
	shared_ptr<string> serializedModelString();
	const char* c_str();
	int getDotsCount();

private:
	shared_ptr<string> text;
	int dotsCount = 0;
};
};
};
};

using namespace FlameSteelCore;
using namespace FlameSteelEngine::GameToolkit;
using namespace FlameSteelEngine::GameToolkit::Algorithms;

class FSGTAMazeObjectGenerator {

public:
	static shared_ptr<Object> generate(shared_ptr<GameMap> gameMap);
	static shared_ptr<SerializedModelConstructable> generateSkybox(shared_ptr<string> textureName);
	static shared_ptr<SerializedModelConstructable> generateCube(int x, int z, shared_ptr<string> textureName);
	static shared_ptr<SerializedModelConstructable> generatePlane(float width, float height, shared_ptr<string> textureName, float diffX = 0, float diffY = 0);
	static shared_ptr<SerializedModelConstructable> generateBox(float width, float height, float length, float u, float v, shared_ptr<string> textureName);

private:
	static void putCeilAtXYZWidthHeightUV(shared_ptr<SerializedModelConstructable> serializedMaze, float x, float y, float z, float width, float height, float u, float v, int dotsCount);
	static void putFloorAtXYZWidthHeightUV(shared_ptr<SerializedModelConstructable> serializedMaze, float x, float y, float z, float width, float height, float u, float v, int dotsCount);
	static void putLeftWallAtXYZWidthHeightUV(shared_ptr<SerializedModelConstructable> serializedMaze, float x, float y, float z, float width, float height, float u, float v, int dotsCount);
	static void putRightWallAtXYZWidthHeightUV(shared_ptr<SerializedModelConstructable> serializedMaze, float x, float y, float z, float width, float height, float u, float v, int dotsCount);
	static void putTopWallAtXYZWidthHeightUV(shared_ptr<SerializedModelConstructable> serializedMaze, float x, float y, float z, float width, float height, float u, float v, int dotsCount);
	static void putDownWallAtXYZWidthHeightUV(shared_ptr<SerializedModelConstructable> serializedMaze, float x, float y, float z, float width, float height, float u, float v, int dotsCount);

	static void putDotAtXYZ(shared_ptr<SerializedModelConstructable> serializedMaze, float x, float y, float z, float u, float v);

};

#endif