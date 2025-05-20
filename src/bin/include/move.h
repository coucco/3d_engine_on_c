#pragma once

#include "custom_structs.h"
#include "matrix.h"
#include "my_math.h"
#include "constants.h"
#include <iostream>

Matrix lookat(Vec3f eye, Vec3f center, Vec3f up);

Matrix viewport(long double x, long double y);
