/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DMMapGeneratorParams.h
 * Author: demensdeum
 *
 * Created on April 25, 2017, 10:34 AM
 */

#ifndef FSEGTAMAPGENERATORPARAMS_H
#define FSEGTAMAPGENERATORPARAMS_H

#include <vector>
#include <memory>

#include <FlameSteelCore/Object.h>

using namespace std;
using namespace FlameSteelCore;

class FSEGTAMapGeneratorParams {
public:
    FSEGTAMapGeneratorParams();
    
    int freeTileIndex = 0;
    int solidTileIndex = 0;
    
    vector<shared_ptr<Object> > tiles;
    
    int maxIterations = 0;
    int maxLineLength = 0;
    
    int minCursorSize = 0;
    int maxCursorSize = 0;
    
    int minFreeSpace = 0;
    int maxFreeSpace = 0;
    
    int difficulty = 0;
    int gameplayObjectRespawnChance = 0;
	int enemyRespawnChance = 0;

	shared_ptr<Objects> objects;
	shared_ptr<Objects> enemies;
    
private:

};

#endif

