/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   DMMapGenerator.cpp
 * Author: demensdeum
 *
 * Created on April 25, 2017, 10:33 AM
 */

#include "MapGenerator.h"
#include "FSEGTAMapGeneratorParams.h"

#include <FlameSteelCore/FSCUtils.h>
#include <FlameSteelEngineGameToolkit/Controllers/FSEGTObjectsContext.h>
#include <FlameSteelEngineGameToolkit/Data/Components/GameMap/GameMap.h>
#include <FlameSteelEngineGameToolkit/Data/FSEGTSimpleDirection.h>
#include <FlameSteelEngineGameToolkit/Utils/FSEGTUtils.h>
#include <FlameSteelEngineGameToolkit/Data/Components/FSEGTFactory.h>
#include <FlameSteelEngineGameToolkitAlgorithms/Const/Const.h>
#include <iostream>
#include <set>
#include <FlameSteelEngineGameToolkitAlgorithms/Algorithms/MazeObjectGenerator/FSGTAMazeObjectGenerator.h>
#include <FlameSteelEngineGameToolkit/Data/Components/SerializedModel/FSEGTSerializedModel.h>

using namespace std;
using namespace FlameSteelEngine::GameToolkit::Algorithms;

namespace FlameSteelEngine {
namespace GameToolkit {
namespace Algorithms {

struct MapGeneratorFreeTile {
	int x;
	int y;
};

inline bool operator<(const MapGeneratorFreeTile& lhs, const MapGeneratorFreeTile& rhs)
{
  return lhs.x < rhs.x && lhs.y < lhs.y;
}

};
};
};

shared_ptr<GameMap> MapGenerator::generate(shared_ptr<FSEGTAMapGeneratorParams> params, shared_ptr<FSEGTObjectsContext> objectsContext) {

	set<MapGeneratorFreeTile> freeTiles;

  if (params.get() == nullptr) {

    cout << "DMMapGenerator: cannot generate map - params are nullptr" << endl;

    exit(1);
  }

  auto gameMap = make_shared<GameMap>();

  auto solidTileIndex = params->solidTileIndex;

  auto maxIterations = params->maxIterations;
  auto maxLineLength = params->maxLineLength;

  for (auto tile : params->tiles) {

    gameMap->addTile(tile);

  }

  for (int x = 0; x < gameMap->width; x++) {

    for (int y = 0; y < gameMap->height; y++) {

      gameMap->setTileAtXY(solidTileIndex, x, y);
    }
  }

  int cursorX = FSCUtils::FSCRandomInt(gameMap->width);
  int cursorY = FSCUtils::FSCRandomInt(gameMap->height);

  if (cursorX < 2) {
    cursorX = 2;
  }

  if (cursorX > gameMap->width - 2) {
    cursorX = gameMap->width - 2;
  }

  if (cursorY < 2) {
    cursorY = 2;
  }

  if (cursorY > gameMap->height - 2) {
    cursorY = gameMap->height - 2;
  }

	if (objectsContext.get() != nullptr) {
	  objectsContext->removeAllObjects();
	}

  MapGenerator::drawFreeTilesAtXY(gameMap, params, cursorX, cursorY, objectsContext);

	if (objectsContext.get() != nullptr) {
		auto startPoint = FSEGTFactory::makeOnSceneObject(
            make_shared<string>(ConstMapGameplayEntityClass.c_str()),
            make_shared<string>(ConstMapEntityStartPoint.c_str()),
            shared_ptr<string>(),
            shared_ptr<string>(),
		shared_ptr<string>(),
            cursorX, 0.5, cursorY,
            1, 1, 1,
            0, 0, 0,
            0);    	

		objectsContext->addObject(startPoint);
	}

  for (auto x = 0; x < maxIterations; x++) {

    int cursorDirection = FSCUtils::FSCRandomInt(FSEGTSimpleDirectionCount);
    int cursorSteps = maxLineLength;

    for (auto y = 0; y < cursorSteps; y++) {

      MapGenerator::drawFreeTilesAtXY(gameMap, params, cursorX, cursorY, objectsContext);
	MapGenerator::putObjectAtXYIfCan(gameMap, params, cursorX, cursorY, objectsContext);

	auto freeTile = MapGeneratorFreeTile();
	freeTile.x = cursorX;
	freeTile.y = cursorY;

	freeTiles.insert(freeTile);

      switch (cursorDirection) {

      case FSEGTSimpleDirectionUp:

        if (cursorY > 2) {
          cursorY -= 1;
        }

        break;

      case FSEGTSimpleDirectionDown:

        if (cursorY < gameMap->height - 2) {
          cursorY += 1;
        }

        break;

      case FSEGTSimpleDirectionLeft:

        if (cursorX > 2) {
          cursorX -= 1;
        }

        break;

      case FSEGTSimpleDirectionRight:

        if (cursorX < gameMap->width - 2) {
          cursorX += 1;
        }

        break;
      }
    }
  }

  MapGenerator::drawFreeTilesAtXY(gameMap, params, cursorX, cursorY, objectsContext);

	auto serializedCardModel = FSGTAMazeObjectGenerator::generateCube(0, 0, make_shared<string>("com.demensdeum.testenvironment.teleport.bmp"));

	auto endPoint = FSEGTFactory::makeOnSceneObject(
            make_shared<string>(ConstMapGameplayEntityClass.c_str()),
            make_shared<string>(ConstMapEntityEndPoint.c_str()),
            shared_ptr<string>(),
            shared_ptr<string>(),
	       serializedCardModel->serializedModelString(),
            cursorX, 0, cursorY,
            1, 1, 1,
            0, 0, 0,
            0);    	

	objectsContext->addObject(endPoint);

	auto enemies = params->enemies;

	while (enemies.get() != nullptr && enemies->size() > 0)
	{
		auto enemy = enemies->objectAtIndex(0);

		auto enemyPosition = FSEGTUtils::getObjectPosition(enemy);
		enemyPosition->x = cursorX;
		enemyPosition->z = cursorY;

		objectsContext->addObject(enemy);

		enemies->removeObjectAtIndex(0);
	}




  // printout

  for (int y = 0; y < gameMap->width; y++) {

    for (int x = 0; x < gameMap->height; x++) {

      auto tileIndex = gameMap->getTileIndexAtXY(x, y);
      auto tile = gameMap->getTileAtXY(x, y);

      if (tile.get() == nullptr) {

        continue;
      }

      //cout << std::to_string(tileIndex);
    }

    //cout << endl;
  }

  return gameMap;
}

void MapGenerator::drawFreeTilesAtXY(
    shared_ptr<GameMap> gameMap,
    shared_ptr<FSEGTAMapGeneratorParams> params, int cursorX, int cursorY,
    shared_ptr<FSEGTObjectsContext> objectsContext) {

  auto minCursorSize = params->minCursorSize;
  auto maxCursorSize = params->maxCursorSize;

  auto freeTileIndex = params->freeTileIndex;

  int cursorSize = FSCUtils::FSCRandomInt(maxCursorSize);

  if (cursorSize < minCursorSize) {

    cursorSize = minCursorSize;
  }

  for (int x = 0; x < cursorSize; x++) {

    for (int y = 0; y < cursorSize; y++) {

      int putTileX = x + cursorX;
      int putTileY = y + cursorY;

      if (putTileX < 2 || putTileY < 2 || putTileX > gameMap->width - 2 || putTileY > gameMap->height - 2) {
        continue;
      }

      gameMap->setTileAtXY(freeTileIndex, putTileX, putTileY);

    }
  }

  gameMap->setTileAtXY(freeTileIndex, cursorX, cursorY);
}

void MapGenerator::putObjectAtXYIfCan(shared_ptr<GameMap> gameMap,
                                shared_ptr<FSEGTAMapGeneratorParams> params,
                                int cursorX, 
					int cursorY,
					shared_ptr<FSEGTObjectsContext> objectsContext)
{
	auto objects = params->objects;

	if (objects.get() != nullptr && objects->size() > 0 && FSCUtils::FSCRandomInt(params->gameplayObjectRespawnChance) == 1)
	{
		auto object = objects->objectAtIndex(0);

		auto objectPosition = FSEGTUtils::getObjectPosition(object);
		objectPosition->x = cursorX;
		objectPosition->z = cursorY;

		objectsContext->addObject(object);

		objects->removeObjectAtIndex(0);
	}

	auto enemies = params->enemies;

	if (enemies.get() != nullptr && enemies->size() > 0 && FSCUtils::FSCRandomInt(params->enemyRespawnChance) == 1)
	{
		auto enemy = enemies->objectAtIndex(0);

		auto enemyPosition = FSEGTUtils::getObjectPosition(enemy);
		enemyPosition->x = cursorX;
		enemyPosition->z = cursorY;

		objectsContext->addObject(enemy);

		enemies->removeObjectAtIndex(0);
	}

}
