#include <memory>
#include "FSGTAMazeObjectGenerator.h"
#include <FlameSteelCore/Object.h>
#include <FlameSteelEngineGameToolkit/Data/Components/GameMap/GameMap.h>
#include <FlameSteelEngineGameToolkit/Data/Components/FSEGTFactory.h>

#include <iostream>

using namespace std;

SerializedModelConstructable::SerializedModelConstructable(shared_ptr<string> modelText)
{
	dotsCount = 0;
	text = modelText;
}

void SerializedModelConstructable::append(shared_ptr<string> string)
{
	text->append(*string);
}

shared_ptr<string> SerializedModelConstructable::serializedModelString() {
	return text;
}

const char* SerializedModelConstructable::c_str() {
	return text->c_str();
}

shared_ptr<SerializedModelConstructable> FSGTAMazeObjectGenerator::generateSkybox(shared_ptr<string> textureName)
{

	auto serializedModel = make_shared<SerializedModelConstructable>(make_shared<string>("Flame Steel Graphics Library Model @ Demens Deum\nModel version = Happy Sasquatch (1.0)\nMesh"));	

	putLeftWallAtXYZWidthHeightUV(serializedModel, 0, 0, 0, 1, 1, 1, 1, 0);
	putRightWallAtXYZWidthHeightUV(serializedModel, 1, 0, 0, 1, 1, 1, 1, 4);
	putTopWallAtXYZWidthHeightUV(serializedModel, 0, 0, 0, 1, 1, 1, 1, 8);
	putDownWallAtXYZWidthHeightUV(serializedModel, 0, 0, 1, 1, 1, 1, 1, 12);

	serializedModel->append(make_shared<string>("\nMaterial - Texture path = data/"));
	serializedModel->append(textureName);

	return serializedModel;
}

shared_ptr<SerializedModelConstructable> FSGTAMazeObjectGenerator::generateCube(int x, int z, shared_ptr<string> textureName)
{
	auto serializedModel = make_shared<SerializedModelConstructable>(make_shared<string>("Flame Steel Graphics Library Model @ Demens Deum\nModel version = Happy Sasquatch (1.0)\nMesh"));
	putFloorAtXYZWidthHeightUV(serializedModel, x, 1, z, 1, 1, 1, 1, 0);
	putTopWallAtXYZWidthHeightUV(serializedModel, x, 0, z + 1, 1, 1, 1, 1, 4);
	putLeftWallAtXYZWidthHeightUV(serializedModel, x + 1, 0, z, 1, 1, 1, 1, 8);
	putRightWallAtXYZWidthHeightUV(serializedModel, x, 0, z, 1, 1, 1, 1, 12);
	putDownWallAtXYZWidthHeightUV(serializedModel, x, 0, z, 1, 1, 1, 1, 16);
	putCeilAtXYZWidthHeightUV(serializedModel, x, 0, z, 1, 1, 1, 1, 20);

	serializedModel->append(make_shared<string>("\nMaterial - Texture path = data/"));
	serializedModel->append(textureName);

	return serializedModel;
}

shared_ptr<SerializedModelConstructable> FSGTAMazeObjectGenerator::generateBox(float width, float height, float length, float u, float v, shared_ptr<string> textureName) {

	auto serializedModel = make_shared<SerializedModelConstructable>(make_shared<string>("Flame Steel Graphics Library Model @ Demens Deum\nModel version = Happy Sasquatch (1.0)\nMesh"));
	putFloorAtXYZWidthHeightUV(serializedModel, 0, height, 0, width, length, u, v, 0);
	putTopWallAtXYZWidthHeightUV(serializedModel, 0, 0, length, width, height, u, v, 4);
	putLeftWallAtXYZWidthHeightUV(serializedModel, width, 0, 0, length, height, u, v, 8);
	putRightWallAtXYZWidthHeightUV(serializedModel, 0, 0, 0, length, height, u, v, 12);
	putDownWallAtXYZWidthHeightUV(serializedModel, 0, 0, 0, width, height, u, v, 16);
	putCeilAtXYZWidthHeightUV(serializedModel, 0, 0, 0, width, length, u, v, 20);
	serializedModel->append(make_shared<string>("\nMaterial - Texture path = data/"));
	serializedModel->append(textureName);

	return serializedModel;	

}

shared_ptr<SerializedModelConstructable> FSGTAMazeObjectGenerator::generatePlane(float width, float height, shared_ptr<string> textureName, float diffX, float diffY) {

	auto serializedModel = make_shared<SerializedModelConstructable>(make_shared<string>("Flame Steel Graphics Library Model @ Demens Deum\nModel version = Happy Sasquatch (1.0)\nMesh"));

	FSGTAMazeObjectGenerator::putDotAtXYZ(serializedModel, width + diffX, height + diffY, 0, 1, 0);
	FSGTAMazeObjectGenerator::putDotAtXYZ(serializedModel, width + diffX, diffY, 0, 1, 1);
	FSGTAMazeObjectGenerator::putDotAtXYZ(serializedModel, diffX, diffY, 0, 0, 1);
	FSGTAMazeObjectGenerator::putDotAtXYZ(serializedModel, diffX, height  + diffY, 0, 0, 0);

	serializedModel->append(make_shared<string>("\nIndex = "));
	serializedModel->append(make_shared<string>(to_string(0)));
	serializedModel->append(make_shared<string>(", "));
	serializedModel->append(make_shared<string>(to_string(2)));
	serializedModel->append(make_shared<string>(", "));
	serializedModel->append(make_shared<string>(to_string(1)));

	serializedModel->append(make_shared<string>("\nIndex = "));
	serializedModel->append(make_shared<string>(to_string(2)));
	serializedModel->append(make_shared<string>(", "));
	serializedModel->append(make_shared<string>(to_string(0)));
	serializedModel->append(make_shared<string>(", "));
	serializedModel->append(make_shared<string>(to_string(3)));

	serializedModel->append(make_shared<string>("\nMaterial - Texture path = data/"));
	serializedModel->append(textureName);

	return serializedModel;
}

shared_ptr<Object> FSGTAMazeObjectGenerator::generate(shared_ptr<GameMap> gameMap) {

	auto serializedMaze = make_shared<SerializedModelConstructable>(make_shared<string>("Flame Steel Graphics Library Model @ Demens Deum\nModel version = Happy Sasquatch (1.0)\nMesh"));

	////cout << "Map Object Generator" << endl;

	int dotsCount = 0;

	for (auto z = 0; z < gameMap->height; z++) {
		for (auto x = 0; x < gameMap->width; x++) {

			auto tile = gameMap->getTileIndexAtXY(x , z);

			if (tile == 0) {

				FSGTAMazeObjectGenerator::putFloorAtXYZWidthHeightUV(serializedMaze, x, 0, z, 
																											  1, 1, 
																											  1, 1, 
																											  dotsCount);

				dotsCount += 4;

				
				if (gameMap->getTileIndexAtXY(x-1,z) == 1) {

					FSGTAMazeObjectGenerator::putLeftWallAtXYZWidthHeightUV(serializedMaze, x, 0, z,
																													 1, 1,
																													 1, 1, dotsCount);

					dotsCount += 4;					

				}

				if (gameMap->getTileIndexAtXY(x+1,z) == 1) {

					FSGTAMazeObjectGenerator::putRightWallAtXYZWidthHeightUV(serializedMaze, x + 1, 0, z, 
																																1, 1, 
																																1, 1, dotsCount);

					dotsCount += 4;					

				}

				if (gameMap->getTileIndexAtXY(x, z - 1) == 1) {

					FSGTAMazeObjectGenerator::putTopWallAtXYZWidthHeightUV(serializedMaze, x, 0, z, 
																														1, 1, 
																														1, 1, dotsCount);

					dotsCount += 4;					

				}

				if (gameMap->getTileIndexAtXY(x, z + 1) == 1) {

					FSGTAMazeObjectGenerator::putDownWallAtXYZWidthHeightUV(serializedMaze, x, 0, z + 1, 
																																1, 1, 
																																1, 1, dotsCount);

					dotsCount += 4;					

				}

			}
			////cout << tile;
		}
		////cout << endl;
	}

	serializedMaze->append(make_shared<string>("\nMaterial - Texture path = data/com.demensdeum.testenvironment.blocktextue.png"));

	//cout << "serializedMaze: " << serializedMaze->c_str() << endl;

	auto maze = FSEGTFactory::makeOnSceneObject(
            make_shared<string>("scene object"),
            make_shared<string>("maze"),
            shared_ptr<string>(),
            shared_ptr<string>(),
		serializedMaze->serializedModelString(),
		0, 0, 0,
            1, 1, 1,
		0,0,0,
            0);


	return maze;

}

void FSGTAMazeObjectGenerator::putFloorAtXYZWidthHeightUV(shared_ptr<SerializedModelConstructable> serializedMaze, float x, float y, float z, float width, float height, float u, float v, int dotsCount) {

	FSGTAMazeObjectGenerator::putDotAtXYZ(serializedMaze, x, y, z, 0, v);
	FSGTAMazeObjectGenerator::putDotAtXYZ(serializedMaze, x + width, y, z, 0, 0);
	FSGTAMazeObjectGenerator::putDotAtXYZ(serializedMaze, x + width, y, z + height, u, 0);
	FSGTAMazeObjectGenerator::putDotAtXYZ(serializedMaze, x, y, z + height, u, v);

	serializedMaze->append(make_shared<string>("\nIndex = "));
	serializedMaze->append(make_shared<string>(to_string(dotsCount + 0)));
	serializedMaze->append(make_shared<string>(", "));
	serializedMaze->append(make_shared<string>(to_string(dotsCount + 2)));
	serializedMaze->append(make_shared<string>(", "));
	serializedMaze->append(make_shared<string>(to_string(dotsCount + 1)));

	serializedMaze->append(make_shared<string>("\nIndex = "));
	serializedMaze->append(make_shared<string>(to_string(dotsCount + 2)));
	serializedMaze->append(make_shared<string>(", "));
	serializedMaze->append(make_shared<string>(to_string(dotsCount + 0)));
	serializedMaze->append(make_shared<string>(", "));
	serializedMaze->append(make_shared<string>(to_string(dotsCount + 3)));

}

void FSGTAMazeObjectGenerator::putCeilAtXYZWidthHeightUV(shared_ptr<SerializedModelConstructable> serializedMaze, float x, float y, float z, float width, float height, float u, float v, int dotsCount) {

	FSGTAMazeObjectGenerator::putDotAtXYZ(serializedMaze, x, y, z, 0, v);
	FSGTAMazeObjectGenerator::putDotAtXYZ(serializedMaze, x + width, y, z, 0, 0);
	FSGTAMazeObjectGenerator::putDotAtXYZ(serializedMaze, x + width, y, z + height, u, 0);
	FSGTAMazeObjectGenerator::putDotAtXYZ(serializedMaze, x, y, z + height, u, v);

	serializedMaze->append(make_shared<string>("\nIndex = "));
	serializedMaze->append(make_shared<string>(to_string(dotsCount + 1)));
	serializedMaze->append(make_shared<string>(", "));
	serializedMaze->append(make_shared<string>(to_string(dotsCount + 2)));
	serializedMaze->append(make_shared<string>(", "));
	serializedMaze->append(make_shared<string>(to_string(dotsCount + 0)));

	serializedMaze->append(make_shared<string>("\nIndex = "));
	serializedMaze->append(make_shared<string>(to_string(dotsCount + 3)));
	serializedMaze->append(make_shared<string>(", "));
	serializedMaze->append(make_shared<string>(to_string(dotsCount + 0)));
	serializedMaze->append(make_shared<string>(", "));
	serializedMaze->append(make_shared<string>(to_string(dotsCount + 2)));

}

void FSGTAMazeObjectGenerator::putLeftWallAtXYZWidthHeightUV(shared_ptr<SerializedModelConstructable> serializedMaze, float x, float y, float z, float width, float height, float u, float v, int dotsCount) {

	FSGTAMazeObjectGenerator::putDotAtXYZ(serializedMaze, x, y + height, z, 0, 0);
	FSGTAMazeObjectGenerator::putDotAtXYZ(serializedMaze, x, y, z, 0, v);
	FSGTAMazeObjectGenerator::putDotAtXYZ(serializedMaze, x, y, z + width, u, v);
	FSGTAMazeObjectGenerator::putDotAtXYZ(serializedMaze, x, y + height, z + width, u, 0);

	serializedMaze->append(make_shared<string>("\nIndex = "));
	serializedMaze->append(make_shared<string>(to_string(dotsCount + 0)));
	serializedMaze->append(make_shared<string>(", "));
	serializedMaze->append(make_shared<string>(to_string(dotsCount + 2)));
	serializedMaze->append(make_shared<string>(", "));
	serializedMaze->append(make_shared<string>(to_string(dotsCount + 1)));

	serializedMaze->append(make_shared<string>(string("\nIndex = ")));
	serializedMaze->append(make_shared<string>(to_string(dotsCount + 2)));
	serializedMaze->append(make_shared<string>(", "));
	serializedMaze->append(make_shared<string>(to_string(dotsCount + 0)));
	serializedMaze->append(make_shared<string>(", "));
	serializedMaze->append(make_shared<string>(to_string(dotsCount + 3)));

}

void FSGTAMazeObjectGenerator::putRightWallAtXYZWidthHeightUV(shared_ptr<SerializedModelConstructable> serializedMaze, float x, float y, float z, float width, float height, float u, float v, int dotsCount) {

	FSGTAMazeObjectGenerator::putDotAtXYZ(serializedMaze, x, y, z, 0, v);
	FSGTAMazeObjectGenerator::putDotAtXYZ(serializedMaze, x, y + height, z, 0, 0);
	FSGTAMazeObjectGenerator::putDotAtXYZ(serializedMaze, x, y + height, z + width, u, 0);
	FSGTAMazeObjectGenerator::putDotAtXYZ(serializedMaze, x, y, z + width, u, v);

	serializedMaze->append(make_shared<string>("\nIndex = "));
	serializedMaze->append(make_shared<string>(to_string(dotsCount + 0)));
	serializedMaze->append(make_shared<string>(", "));
	serializedMaze->append(make_shared<string>(to_string(dotsCount + 2)));
	serializedMaze->append(make_shared<string>(", "));
	serializedMaze->append(make_shared<string>(to_string(dotsCount + 1)));

	serializedMaze->append(make_shared<string>(string("\nIndex = ")));
	serializedMaze->append(make_shared<string>(to_string(dotsCount + 2)));
	serializedMaze->append(make_shared<string>(", "));
	serializedMaze->append(make_shared<string>(to_string(dotsCount + 0)));
	serializedMaze->append(make_shared<string>(", "));
	serializedMaze->append(make_shared<string>(to_string(dotsCount + 3)));

}

void FSGTAMazeObjectGenerator::putTopWallAtXYZWidthHeightUV(shared_ptr<SerializedModelConstructable> serializedMaze, float x, float y, float z, float width, float height, float u, float v, int dotsCount) {

	FSGTAMazeObjectGenerator::putDotAtXYZ(serializedMaze, x, y, z, 0, v);
	FSGTAMazeObjectGenerator::putDotAtXYZ(serializedMaze, x, y + height, z, 0, 0);
	FSGTAMazeObjectGenerator::putDotAtXYZ(serializedMaze, x + width, y + height, z, u, 0);
	FSGTAMazeObjectGenerator::putDotAtXYZ(serializedMaze, x + width, y, z, u, v);

	serializedMaze->append(make_shared<string>(string("\nIndex = ")));
	serializedMaze->append(make_shared<string>(to_string(dotsCount + 0)));
	serializedMaze->append(make_shared<string>(", "));
	serializedMaze->append(make_shared<string>(to_string(dotsCount + 2)));
	serializedMaze->append(make_shared<string>(", "));
	serializedMaze->append(make_shared<string>(to_string(dotsCount + 1)));

	serializedMaze->append(make_shared<string>("\nIndex = "));
	serializedMaze->append(make_shared<string>(to_string(dotsCount + 2)));
	serializedMaze->append(make_shared<string>(", "));
	serializedMaze->append(make_shared<string>(to_string(dotsCount + 0)));
	serializedMaze->append(make_shared<string>(", "));
	serializedMaze->append(make_shared<string>(to_string(dotsCount + 3)));

}

void FSGTAMazeObjectGenerator::putDownWallAtXYZWidthHeightUV(shared_ptr<SerializedModelConstructable> serializedMaze, float x, float y, float z, float width, float height, float u, float v, int dotsCount) {

	FSGTAMazeObjectGenerator::putDotAtXYZ(serializedMaze, x, y, z, 0, v);
	FSGTAMazeObjectGenerator::putDotAtXYZ(serializedMaze, x + width, y, z, u, v);
	FSGTAMazeObjectGenerator::putDotAtXYZ(serializedMaze, x + width, y + height, z, u, 0);
	FSGTAMazeObjectGenerator::putDotAtXYZ(serializedMaze, x, y + height, z, 0, 0);

	serializedMaze->append(make_shared<string>(string("\nIndex = ")));
	serializedMaze->append(make_shared<string>(to_string(dotsCount + 0)));
	serializedMaze->append(make_shared<string>(", "));
	serializedMaze->append(make_shared<string>(to_string(dotsCount + 2)));
	serializedMaze->append(make_shared<string>(", "));
	serializedMaze->append(make_shared<string>(to_string(dotsCount + 1)));

	serializedMaze->append(make_shared<string>(string("\nIndex = ")));
	serializedMaze->append(make_shared<string>(to_string(dotsCount + 2)));
	serializedMaze->append(make_shared<string>(", "));
	serializedMaze->append(make_shared<string>(to_string(dotsCount + 0)));
	serializedMaze->append(make_shared<string>(", "));
	serializedMaze->append(make_shared<string>(to_string(dotsCount + 3)));

}

void FSGTAMazeObjectGenerator::putDotAtXYZ(shared_ptr<SerializedModelConstructable> serializedMaze, float x, float y, float z, float u, float v) {

	serializedMaze->append(make_shared<string>(string("\nVertex - x = ")));
	serializedMaze->append(make_shared<string>(to_string(x)));

	serializedMaze->append(make_shared<string>(string(", y = ")));
	serializedMaze->append(make_shared<string>(to_string(y)));

	serializedMaze->append(make_shared<string>(string(", z = ")));
	serializedMaze->append(make_shared<string>(to_string(z)));

	serializedMaze->append(make_shared<string>(string(", u = ")));
	serializedMaze->append(make_shared<string>(to_string(u)));

	serializedMaze->append(make_shared<string>(string(", v = ")));
	serializedMaze->append(make_shared<string>(to_string(v)));

}