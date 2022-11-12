#pragma once
#include <iostream>
#include "TextureManager.h"
#include "LoaderParams.h"
#include "InputHandler.h"
#include "Vector2D.h"
#include "GameEnum.h"

class GameObject {
public:
	virtual void draw() = 0;
	virtual void update() = 0;
	virtual void clean()= 0;
	virtual ~GameObject(){}
protected:
	GameObject(const LoaderParams* pParams) {}
};