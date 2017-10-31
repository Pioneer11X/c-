#pragma once

#ifndef MAP_LOADER_H
#define MAP_LOADER_H

// This file Should load the Map and pass it over to the Game

#include <fstream>
#include <string>

#include "Game.h"

class MapLoader {

	char * fileName;

public:

	MapLoader(char * _fileName) { fileName = _fileName; };

	bool LoadMap( Game * _game ) {

		float x = -1, y = 1;

		// float xStep = _game.HEIGHT / 10;
		float xStep = 2.0f / 10;

		std::ifstream file(fileName);
		std::string str;

		Entity * e;

		while (std::getline(file, str)) {
			x = -1;
			for (unsigned i = 0; i < str.length(); i++) {

				switch (str.at(i))
				{

				case 'X':
					e = new Entity(_game->blockMesh, vec3(x, y, 1.0f), vec3(0, 0, 0), vec3(1.0f));
					_game->platformEntites.push_back(e);
					break;

				case 'P':
					_game->playerEntity->setTranslate(vec3(x, y, 1.0f));
					break;

				default:
					break;
				}

				// P for Player

				// X for Platform
				x += xStep;
			}
			y -= xStep;
		}

		return true; 
	};

};

#endif // !MAP_LOADER_H

