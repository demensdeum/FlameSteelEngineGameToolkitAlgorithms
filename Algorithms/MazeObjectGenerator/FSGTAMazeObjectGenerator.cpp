#include <memory>
#include "FSGTAMazeObjectGenerator.h"
#include <FlameSteelCore/Object.h>
#include <FlameSteelEngineGameToolkit/Data/Components/GameMap/GameMap.h>
#include <FlameSteelEngineGameToolkit/Data/Components/FSEGTFactory.h>

#include <iostream>

using namespace std;

shared_ptr<string> FSGTAMazeObjectGenerator::generateCube(int x, int z, shared_ptr<string> textureName)
{
	shared_ptr<string> serializedModel = make_shared<string>("Flame Steel Graphics Library Model @ Demens Deum\nModel version = Happy Sasquatch (1.0)\nMesh");
	putTopWallAtXYZWidthHeightUV(serializedModel, x, 0, z + 1, 1, 1, 0, 1, 0);
	putLeftWallAtXYZWidthHeightUV(serializedModel, x + 1, 0, z, 1, 1, 0, 1, 4);
	putRightWallAtXYZWidthHeightUV(serializedModel, x -1, 0, z, 1, 1, 0, 1, 8);
	putDownWallAtXYZWidthHeightUV(serializedModel, x, 0, z - 1, 1, 1, 0, 1, 12);
	serializedModel->append(string("\nMaterial - Texture path = /home/demensdeum/Sources/Death-Mask/DeathMask/data/"));
	serializedModel->append(*textureName);

	return serializedModel;
}

shared_ptr<string> FSGTAMazeObjectGenerator::generateBox(float width, float height, float length, float u, float v, shared_ptr<string> textureName) {

	shared_ptr<string> serializedModel = make_shared<string>("Flame Steel Graphics Library Model @ Demens Deum\nModel version = Happy Sasquatch (1.0)\nMesh");
	putFloorAtXYZWidthHeightUV(serializedModel, 0, height, 0, width, length, u, v, 0);
	putTopWallAtXYZWidthHeightUV(serializedModel, 0, 0, 0, width, height, u, v, 4);
	putLeftWallAtXYZWidthHeightUV(serializedModel, width, 0, 0, length, height, u, v, 8);
	putRightWallAtXYZWidthHeightUV(serializedModel, 0, 0, 0, length, height, u, v, 12);
	putDownWallAtXYZWidthHeightUV(serializedModel, 0, 0, -length, width, height, u, v, 16);
	serializedModel->append(string("\nMaterial - Texture path = /home/demensdeum/Sources/Death-Mask/DeathMask/data/"));
	serializedModel->append(*textureName);

	return serializedModel;	

}

shared_ptr<string> FSGTAMazeObjectGenerator::generatePlane(float width, float height, shared_ptr<string> textureName) {

	shared_ptr<string> serializedModel = make_shared<string>("Flame Steel Graphics Library Model @ Demens Deum\nModel version = Happy Sasquatch (1.0)\nMesh");

	FSGTAMazeObjectGenerator::putDotAtXYZ(serializedModel, width, height, 0, 1, 0);
	FSGTAMazeObjectGenerator::putDotAtXYZ(serializedModel, width, 0, 0, 1, 1);
	FSGTAMazeObjectGenerator::putDotAtXYZ(serializedModel, 0, 0, 0, 0, 1);
	FSGTAMazeObjectGenerator::putDotAtXYZ(serializedModel, 0, height, 0, 0, 0);

	serializedModel->append(string("\nIndex = "));
	serializedModel->append(to_string(0));
	serializedModel->append(", ");
	serializedModel->append(to_string(2));
	serializedModel->append(", ");
	serializedModel->append(to_string(1));

	serializedModel->append(string("\nIndex = "));
	serializedModel->append(to_string(2));
	serializedModel->append(", ");
	serializedModel->append(to_string(0));
	serializedModel->append(", ");
	serializedModel->append(to_string(3));

	serializedModel->append(string("\nMaterial - Texture path = /home/demensdeum/Sources/Death-Mask/DeathMask/data/"));
	serializedModel->append(*textureName);

	return serializedModel;
}

shared_ptr<Object> FSGTAMazeObjectGenerator::generate(shared_ptr<GameMap> gameMap) {

	auto serializedMaze = make_shared<string>("Flame Steel Graphics Library Model @ Demens Deum\nModel version = Happy Sasquatch (1.0)\nMesh");

	//cout << "Map Object Generator" << endl;

	int dotsCount = 0;

	for (auto z = 0; z < gameMap->height; z++) {
		for (auto x = 0; x < gameMap->width; x++) {

			auto tile = gameMap->getTileIndexAtXY(x , z);

			if (tile == 0) {

				FSGTAMazeObjectGenerator::putFloorAtXYZWidthHeightUV(serializedMaze, x, 0, z, 1, 1, 0, 1, dotsCount);

				dotsCount += 4;

				if (gameMap->getTileIndexAtXY(x-1,z) == 1) {

					FSGTAMazeObjectGenerator::putLeftWallAtXYZWidthHeightUV(serializedMaze, x, 0, z, 1, 1, 0, 1, dotsCount);

					dotsCount += 4;					

				}

				if (gameMap->getTileIndexAtXY(x+1,z) == 1) {

					FSGTAMazeObjectGenerator::putRightWallAtXYZWidthHeightUV(serializedMaze, x, 0, z, 1, 1, 0, 1, dotsCount);

					dotsCount += 4;					

				}

				if (gameMap->getTileIndexAtXY(x, z - 1) == 1) {

					FSGTAMazeObjectGenerator::putTopWallAtXYZWidthHeightUV(serializedMaze, x, 0, z, 1, 1, 0, 1, dotsCount);

					dotsCount += 4;					

				}

				if (gameMap->getTileIndexAtXY(x, z + 1) == 1) {

					FSGTAMazeObjectGenerator::putDownWallAtXYZWidthHeightUV(serializedMaze, x, 0, z, 1, 1, 0, 1, dotsCount);

					dotsCount += 4;					

				}

			}

			//cout << tile;
		}
		//cout << endl;
	}

	serializedMaze->append(string("\nMaterial - Texture path = /home/demensdeum/Sources/Death-Mask/DeathMask/data/com.demensdeum.testenvironment.blocktextue.bmp"));

	auto maze = FSEGTFactory::makeOnSceneObject(
            make_shared<string>("scene object"),
            make_shared<string>("maze"),
            shared_ptr<string>(),
            shared_ptr<string>(),
		serializedMaze,
		0,0,0,
            1, 1, 1,
		0,0,0,
            0);

	return maze;

}

void FSGTAMazeObjectGenerator::putFloorAtXYZWidthHeightUV(shared_ptr<string> serializedMaze, float x, float y, float z, float width, float height, float u, float v, int dotsCount) {

	FSGTAMazeObjectGenerator::putDotAtXYZ(serializedMaze, x, y, z, 0, v);
	FSGTAMazeObjectGenerator::putDotAtXYZ(serializedMaze, x + width, y, z, u, v);
	FSGTAMazeObjectGenerator::putDotAtXYZ(serializedMaze, x + width, y, z - height, u, 0);
	FSGTAMazeObjectGenerator::putDotAtXYZ(serializedMaze, x, y, z - height, 0, 0);

	serializedMaze->append(string("\nIndex = "));
	serializedMaze->append(to_string(dotsCount));
	serializedMaze->append(", ");
	serializedMaze->append(to_string(dotsCount + 1));
	serializedMaze->append(", ");
	serializedMaze->append(to_string(dotsCount + 2));

	serializedMaze->append(string("\nIndex = "));
	serializedMaze->append(to_string(dotsCount + 3));
	serializedMaze->append(", ");
	serializedMaze->append(to_string(dotsCount));
	serializedMaze->append(", ");
	serializedMaze->append(to_string(dotsCount + 2));

}

void FSGTAMazeObjectGenerator::putLeftWallAtXYZWidthHeightUV(shared_ptr<string> serializedMaze, float x, float y, float z, float width, float height, float u, float v, int dotsCount) {

	FSGTAMazeObjectGenerator::putDotAtXYZ(serializedMaze, x, height, y, 0, v);
	FSGTAMazeObjectGenerator::putDotAtXYZ(serializedMaze, x, 0, y, u, v);
	FSGTAMazeObjectGenerator::putDotAtXYZ(serializedMaze, x, 0, y - width, u, 0);
	FSGTAMazeObjectGenerator::putDotAtXYZ(serializedMaze, x, height, y - width, 0, 0);

	serializedMaze->append(string("\nIndex = "));
	serializedMaze->append(to_string(dotsCount));
	serializedMaze->append(", ");
	serializedMaze->append(to_string(dotsCount + 1));
	serializedMaze->append(", ");
	serializedMaze->append(to_string(dotsCount + 2));

	serializedMaze->append(string("\nIndex = "));
	serializedMaze->append(to_string(dotsCount + 3));
	serializedMaze->append(", ");
	serializedMaze->append(to_string(dotsCount));
	serializedMaze->append(", ");
	serializedMaze->append(to_string(dotsCount + 2));

}

void FSGTAMazeObjectGenerator::putRightWallAtXYZWidthHeightUV(shared_ptr<string> serializedMaze, float x, float y, float z, float width, float height, float u, float v, int dotsCount) {

	FSGTAMazeObjectGenerator::putDotAtXYZ(serializedMaze, x, height, y, 0, v);
	FSGTAMazeObjectGenerator::putDotAtXYZ(serializedMaze, x, 0, y, u, v);
	FSGTAMazeObjectGenerator::putDotAtXYZ(serializedMaze, x, 0, y - width, u, 0);
	FSGTAMazeObjectGenerator::putDotAtXYZ(serializedMaze, x, height, y - width, 0, 0);

	serializedMaze->append(string("\nIndex = "));
	serializedMaze->append(to_string(dotsCount));
	serializedMaze->append(", ");
	serializedMaze->append(to_string(dotsCount + 2));
	serializedMaze->append(", ");
	serializedMaze->append(to_string(dotsCount + 1));

	serializedMaze->append(string("\nIndex = "));
	serializedMaze->append(to_string(dotsCount + 2));
	serializedMaze->append(", ");
	serializedMaze->append(to_string(dotsCount));
	serializedMaze->append(", ");
	serializedMaze->append(to_string(dotsCount + 3));

}

void FSGTAMazeObjectGenerator::putTopWallAtXYZWidthHeightUV(shared_ptr<string> serializedMaze, float x, float y, float z, float width, float height, float u, float v, int dotsCount) {

	FSGTAMazeObjectGenerator::putDotAtXYZ(serializedMaze, x + width, height, y, 0, v);
	FSGTAMazeObjectGenerator::putDotAtXYZ(serializedMaze, x + width, 0, y, u, v);
	FSGTAMazeObjectGenerator::putDotAtXYZ(serializedMaze, x, 0, y, u, 0);
	FSGTAMazeObjectGenerator::putDotAtXYZ(serializedMaze, x, height, y, 0, 0);

	serializedMaze->append(string("\nIndex = "));
	serializedMaze->append(to_string(dotsCount));
	serializedMaze->append(", ");
	serializedMaze->append(to_string(dotsCount + 2));
	serializedMaze->append(", ");
	serializedMaze->append(to_string(dotsCount + 1));

	serializedMaze->append(string("\nIndex = "));
	serializedMaze->append(to_string(dotsCount + 2));
	serializedMaze->append(", ");
	serializedMaze->append(to_string(dotsCount));
	serializedMaze->append(", ");
	serializedMaze->append(to_string(dotsCount + 3));	

}

void FSGTAMazeObjectGenerator::putDownWallAtXYZWidthHeightUV(shared_ptr<string> serializedMaze, float x, float y, float z, float width, float height, float u, float v, int dotsCount) {

	FSGTAMazeObjectGenerator::putDotAtXYZ(serializedMaze, x + width, height, z, u, v);
	FSGTAMazeObjectGenerator::putDotAtXYZ(serializedMaze, x + width, y, z, v, v);
	FSGTAMazeObjectGenerator::putDotAtXYZ(serializedMaze, x, y, z, v, u);
	FSGTAMazeObjectGenerator::putDotAtXYZ(serializedMaze, x, height, z, u, u);

	serializedMaze->append(string("\nIndex = "));
	serializedMaze->append(to_string(dotsCount));
	serializedMaze->append(", ");
	serializedMaze->append(to_string(dotsCount + 1));
	serializedMaze->append(", ");
	serializedMaze->append(to_string(dotsCount + 2));

	serializedMaze->append(string("\nIndex = "));
	serializedMaze->append(to_string(dotsCount + 3));
	serializedMaze->append(", ");
	serializedMaze->append(to_string(dotsCount));
	serializedMaze->append(", ");
	serializedMaze->append(to_string(dotsCount + 2));

}

void FSGTAMazeObjectGenerator::putDotAtXYZ(shared_ptr<string> serializedMaze, float x, float y, float z, float u, float v) {

	serializedMaze->append(string("\nVertex - x = "));
	serializedMaze->append(to_string(x));

	serializedMaze->append(string(", y = "));
	serializedMaze->append(to_string(y));

	serializedMaze->append(string(", z = "));
	serializedMaze->append(to_string(z));

	serializedMaze->append(string(", u = "));
	serializedMaze->append(to_string(u));

	serializedMaze->append(string(", v = "));
	serializedMaze->append(to_string(v));

}