#pragma once


typedef struct {
	float x;
	float y;
	float z;

} Vec3;


Vec3 addv3s(Vec3 *v, float s);
Vec3 subv3s(Vec3 *v, float s);
Vec3 mulv3s(Vec3 *v, float s);
Vec3 divv3s(Vec3 *v, float s);

Vec3 addv3v3(Vec3 *v1, Vec3 *v2);
Vec3 subv3v3(Vec3 *v1, Vec3 *v2);
Vec3 mulv3v3(Vec3 *v1, Vec3 *v2);
Vec3 divv3v3(Vec3 *v1, Vec3 *v2);


