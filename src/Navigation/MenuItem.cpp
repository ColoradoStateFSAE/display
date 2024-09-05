#include "MenuItem.h"

MenuItem MenuItem::heading() {
	_heading = true;
	return *this;
}

bool MenuItem::isHeading() {
	return _heading;
}
