#pragma once

#include "custom_structs.h"

Vec4f plane_equation_solve(Vec3i p1, Vec3i p2, Vec3i p3);

Vec3f baricentric_koefs(Vec3i a, Vec3i b, Vec3i c, Vec3i point);
