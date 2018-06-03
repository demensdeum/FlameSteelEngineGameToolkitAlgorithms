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
#include <FlameSteelEngineGameToolkit/Data/Components/GameMap/FSEGTGameMap.h>
#include <FlameSteelEngineGameToolkit/Data/FSEGTSimpleDirection.h>
#include <FlameSteelEngineGameToolkit/Utils/FSEGTUtils.h>
#include <FlameSteelEngineGameToolkit/Data/Components/FSEGTFactory.h>
#include <FlameSteelEngineGameToolkitAlgorithms/Const/Const.h>
#include <iostream>

using namespace std;
using namespace FlameSteelEngine::GameToolkit::Algorithms;

shared_ptr<FSEGTGameMap> MapGenerator::generate(shared_ptr<FSEGTAMapGeneratorParams> params, shared_ptr<FSEGTObjectsContext> objectsContext, shared_ptr<FSCObjects> objects) {

  if (params.get() == nullptr) {

    cout << "DMMapGenerator: cannot generate map - params are nullptr" << endl;

    exit(1);
  }

  if (objectsContext.get() == nullptr) {

    cout << "DMMapGenerator: cannot generate map - objectsContext are nullptr"
         << endl;

    exit(1);
  }

  auto gameMap = make_shared<FSEGTGameMap>();

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

  objectsContext->removeAllObjects();

  MapGenerator::drawFreeTilesAtXY(gameMap, params, cursorX, cursorY, objectsContext);

	auto startPoint = FSEGTFactory::makeOnSceneObject(
            make_shared<string>(ConstMapGameplayEntityClass.c_str()),
            make_shared<string>(ConstMapEntityStartPoint.c_str()),
            shared_ptr<string>(),
            shared_ptr<string>(),
		shared_ptr<string>(),
            cursorX, 0, cursorY,
            1, 1, 1,
            0, 0, 0,
            0);    	

	objectsContext->addObject(startPoint);

  for (auto x = 0; x < maxIterations; x++) {

    int cursorDirection = FSCUtils::FSCRandomInt(FSEGTSimpleDirectionCount);
    int cursorSteps = maxLineLength;

    for (auto y = 0; y < cursorSteps; y++) {

      MapGenerator::drawFreeTilesAtXY(gameMap, params, cursorX, cursorY, objectsContext);

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

	auto endPoint = FSEGTFactory::makeOnSceneObject(
            make_shared<string>(ConstMapGameplayEntityClass.c_str()),
            make_shared<string>(ConstMapEntityEndPoint.c_str()),
            make_shared<string>(),
            make_shared<string>(),
		make_shared<string>(),
            cursorX, 0, cursorY,
            1, 1, 1,
            0, 0, 0,
            0);    	

	objectsContext->addObject(endPoint);

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
    shared_ptr<FSEGTGameMap> gameMap,
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

      if (putTileX < 2 || putTileY < 2 || putTileX > gameMap->width - 2 ||
          putTileY > gameMap->height - 2) {
        continue;
      }

      gameMap->setTileAtXY(freeTileIndex, putTileX, putTileY);
    }
  }

  gameMap->setTileAtXY(freeTileIndex, cursorX, cursorY);
}