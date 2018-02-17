#pragma once

#include "ResourceFormats.h"

struct VertexData
{
	enum Type
	{
	        VERTEX_TYPE_POSITION = 0,
	        VERTEX_TYPE_NORMAL = 1,
	        VERTEX_TYPE_TANGENT = 2,
	        VERTEX_TYPE_BITANGENT = 3,
	        VERTEX_TYPE_COLOR0 = 4,
	        VERTEX_TYPE_TEX_COORD0 = 5,

			VERTEX_TYPE_COUNT = 6
	};

	VertexData(void) : vertexCount(0)
	{
		for (int i = 0; i < VERTEX_TYPE_COUNT; ++i)
		{
			vertices[i] = nullptr;
			vertexFormat[i] = (VertexFormat)0; // TODO : add "unknown" Format
		}
	}

	unsigned int vertexCount;
	void * vertices [VERTEX_TYPE_COUNT];
	VertexFormat vertexFormat [VERTEX_TYPE_COUNT];
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
