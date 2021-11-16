#pragma once
#include "GameFramework/Actor.h"
#include "Utils/List.h"
#include "Utils/Delegate.h"
#include "PacketTracerSimulator.h"

class Packet : public Actor
{
public:
	Packet();

	void AddTarget(Actor* target);
	DelegateNoParam<PacketTracerSimulator> lastPacketReachedCallback;

protected:
	virtual void Update(float deltaTime) override;

private:
	static const std::string colors[3];

	List<class Actor*> targets;
	int currentTarget;
	float collisionDistance;
	float speed;
	int GetNextTarget();
	void MoveToTarget(float deltaTime);
};

