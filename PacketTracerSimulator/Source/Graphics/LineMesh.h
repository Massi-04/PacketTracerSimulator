#pragma once
#include "Mesh.h"

class LineMesh : public Mesh
{
public:
	LineMesh();

	void SetLineCoords(const Vec2& start, const Vec2& end);

	virtual void UpdateMesh() override;

private:
	Vec2 start;
	Vec2 end;
};

