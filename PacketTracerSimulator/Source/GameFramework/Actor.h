#pragma once
#include "Core/Base.h"

class Actor
{
	friend class Application;

public:
	Actor();
	virtual ~Actor();

protected:
	virtual void Start();
	virtual void Update(float deltaTime);

public:
	void Destroy();
	void SetName(const std::string& name);
	inline const std::string& GetName() const { return name; }

public:
	inline class Mesh* GetMesh() { return mesh; }
	inline Vec2 GetLocation() const { return location; }
	inline Vec2 GetScale() const { return scale; }
	void SetLocation(const Vec2& location);
	void SetScale(const Vec2& scale);
	void SetMesh(class Mesh* mesh);

	void GetQuadCollision(Vec2 outQuad[4]) const;
	bool IsPointInQuadCollision(const Vec2& normalizedPoint) const;

private:
	bool bPendingKill;
	Vec2 location;
	Vec2 scale;
	class Mesh* mesh;
	std::string name;
};

