#include "Utils.h"
#include "MoneyBag.h"

MoneyBag::MoneyBag(Vec2 _pos) {
	pos = _pos;
	value = 1;
	size.x = 500; size.y = 500;
	mySprite = Sprite::MONEYBAG;
}