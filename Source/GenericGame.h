#pragma once
#include "Entity.h"
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <limits>

class GenericGame
{

public:
	GenericGame();
	~GenericGame();

	virtual void Init();

	virtual void Update();
	virtual void Draw();
	virtual void handleUserEvents();

};

