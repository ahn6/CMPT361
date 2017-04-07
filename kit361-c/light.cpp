#include "light.h"

Light::Light(iMatrix currentCTM, Shading ShadingType, std::vector<Vertex> Vert, std::vector<Normal> Norms)
{
	CTM = currentCTM;
	shade = ShadingType;
	Vertices = Vert;
	Normals = Norms;
}

// We will set the light Source
void Light::setLightSource()
{
	if (shade == Gouraud)
	{
		setGouraud();
	}
	else if (shade == Flat)
	{
		setFlat();
	}
	else
	{
		setPhong();
	}

}

// Using Phong shading
void Light::setPhong()
{

}

// Using Flat shading
void Light::setFlat()
{

}

// Using Gouraud shading
void Light::setGouraud()
{

}