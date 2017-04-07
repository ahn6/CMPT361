#ifndef LIGHT_H
#define LIGHT_H
#include "drawable.h"
#include "client.h"
#pragma once

class Light
{
public:
	Light(iMatrix currentCTM, Shading ShadeType, std::vector<Vertex> Vert, std::vector<Normal> Norms);

	void setLightSource();

	void setPhong();

	void setFlat();

	void setGouraud();

private:
	iMatrix CTM;
	Shading shade;

	std::vector<Normal> Normals;
	std::vector<Vertex> Vertices;

};

#endif // CLIENT_H