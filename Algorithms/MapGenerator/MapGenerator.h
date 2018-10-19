/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   DMMapGenerator.h
 * Author: demensdeum
 *
 * Created on April 25, 2017, 10:33 AM
 */

#ifndef FSEGTAMAPGENERATOR_H_
#define FSEGTAMAPGENERATOR_H_

class Objects;
namespace FlameSteelEngine {
namespace GameToolkit {
class GameMap;
}
}
class FSEGTObjectsContext;
struct MapGeneratorFreeTile;
class FSEGTAMapGeneratorParams;

#include <memory>

using namespace std;
using namespace FlameSteelEngine::GameToolkit;

namespace FlameSteelEngine {
namespace GameToolkit {
namespace Algorithms {

class MapGenerator {

public:
	static shared_ptr<GameMap> generate(shared_ptr<FSEGTAMapGeneratorParams> params, shared_ptr<FSEGTObjectsContext> objectsContext);

private:
	static void putObjectAtXYIfCan(shared_ptr<GameMap> gameMap,
                                shared_ptr<FSEGTAMapGeneratorParams> params,
                                int cursorX, 
					int cursorY,
					shared_ptr<FSEGTObjectsContext> objectsContext);

	static void drawFreeTilesAtXY(shared_ptr<GameMap> gameMap,
                                shared_ptr<FSEGTAMapGeneratorParams> params,
                                int cursorX, 
					int cursorY,
					shared_ptr<FSEGTObjectsContext> objectsContext);
};
};
};
};

#endif
