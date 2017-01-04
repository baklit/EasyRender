#include "Vector.h"


Vec3 addv3s(Vec3 *v, float s)
{
	return (Vec3) {
			v->x + s,
			v->y + s,
			v->z + s};
}

Vec3 subv3s(Vec3 *v, float s)
{
	return (Vec3) {
			v->x - s,
	 		v->y - s,
	 		v->z - s};
}

Vec3 mulv3s(Vec3 *v, float s)
{
	return (Vec3) {
			v->x * s,
	 		v->y * s,
	 		v->z * s};
}

Vec3 divv3s(Vec3 *v, float s)
{
	return (Vec3) {
			v->x / s,
	 		v->y / s,
	 		v->z / s};
}

Vec3 addv3v3(Vec3 *v1, Vec3 *v2)
{
	return (Vec3) {
			v1->x + v2->x,
			v1->y + v2->y,
			v1->z + v2->z};
}

Vec3 subv3v3(Vec3 *v1, Vec3 *v2)
{
	return (Vec3) {
			v1->x - v2->x,
	 		v1->y - v2->y,
	 		v1->z - v2->z};
}

Vec3 mulv3v3(Vec3 *v1, Vec3 *v2)
{
	return (Vec3) {
			v1->x * v2->x,
	 		v1->y * v2->y,
	 		v1->z * v2->z};
}

Vec3 divv3v3(Vec3 *v1, Vec3 *v2)
{
	return (Vec3) {
			v1->x / v2->x,
	 		v1->y / v2->y,
	 		v1->z / v2->z};
}


