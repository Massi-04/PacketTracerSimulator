#pragma once
#include "GameFramework/Actor.h"

class Cable : public Actor
{
public:
	Cable();

	void SetConnected(Actor* start, Actor* end);

protected:
	virtual void Update(float ts) override;

private:
	class LineMesh* cableMesh;
	Actor* connected[2];
};

