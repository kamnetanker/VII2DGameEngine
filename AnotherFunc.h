#pragma once
#include "SomeHeadersAndParams.h"
float loop(float &a) {
	if ((a - (int)a) <= 0.5) {
		return floor(a);
	}
	else {
		return ceil(a);
	}

}