#pragma once

class Vec4f
{
public:
	union
	{
		struct
		{
			float x, y, z, w;
		};
		float v[4];
	};
	Vec4f();
	Vec4f(Vec4f &other);
	Vec4f(float x, float y, float z, float w);
	float& operator [](int);
};

class Vec3f
{
public:
	union
	{
		struct
		{
			float x, y, z;
		};
		float v[3];
	};
	Vec3f();
	Vec3f(Vec3f &other);
	Vec3f(float x, float y, float z);
	float& operator [](int);
};

class Vec2f
{
public:
	union
	{
		struct
		{
			float x, y;
		};
		float v[2];
	};
	Vec2f();
	Vec2f(float x, float y);
	Vec2f(Vec2f &other);
	float& operator [](int);
};