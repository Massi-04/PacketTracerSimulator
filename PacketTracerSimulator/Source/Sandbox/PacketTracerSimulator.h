#pragma once
#include "Core/Application.h"

class PacketTracerSimulator : public Application
{
public:
	PacketTracerSimulator();

protected:
	virtual void Start() override;
	virtual void Update() override;

private:
	void FindInteractable();
	void Interact();
	void ResetConnection();
	Actor* hovered;
	Actor* selected;
	class Computer* connection[2];
	class Light* connectionStatus;
	bool sending;
	Vec2 mouseLocation;
};

