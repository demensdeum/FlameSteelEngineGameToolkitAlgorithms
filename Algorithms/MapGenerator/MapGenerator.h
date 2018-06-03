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

#ifndef FSEGTAMAPGENERATOR_H
#define FSEGTAGENERATOR_H

class FSCObjects;
class FSEGTGameMap;
class FSEGTObjectsContext;
class FSEGTAMapGeneratorParams;

#include <memory>

using namespace std;

namespace FlameSteelEngine {
namespace GameToolkit {
namespace Algorithms {

class MapGenerator {

public:
	static shared_ptr<FSEGTGameMap> generate(shared_ptr<FSEGTAMapGeneratorParams> params, shared_ptr<FSEGTObjectsContext> objectsContext, shared_ptr<FSCObjects> objects);

private:

	static void drawFreeTilesAtXY(shared_ptr<FSEGTGameMap> gameMap,
                                shared_ptr<FSEGTAMapGeneratorParams> params,
                                int cursorX, 
					int cursorY,
					shared_ptr<FSEGTObjectsContext> objectsContext);
};
};
};
};

#endif