#pragma once

#include "ResourceFormats.h"

struct VertexData
{
	enum Type
	{
		VERTEX_TYPE_POSITION,
		VERTEX_TYPE_NORMAL,
		VERTEX_TYPE_TANGENT,
		VERTEX_TYPE_BITANGENT,
		VERTEX_TYPE_COLOR0,
		VERTEX_TYPE_TEX_COORD0,
	};

	unsigned int vertexCount;
	void * vertices [16];
	VertexFormat vertexFormat [16];
	Type vertexType [16];
};

struct IndexData
{
	unsigned int indexCount;
	void * indices;
	IndexFormat indexFormat;
};

struct TextureData1D
{
	unsigned int width;
	void * data;
	TexelFormat texelFormat;
};

struct TextureData2D
{
	unsigned int width;
	unsigned int height;
	void * data;
	TexelFormat texelFormat;
};

struct TextureData3D
{
	unsigned int width;
	unsigned int height;
	unsigned int depth;
	void * data;
	TexelFormat texelFormat;
};
