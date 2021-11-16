#pragma once
#include "GameFramework/Actor.h"
#include "Interactable.h"

class Computer : public Actor, public IInteractable
{
public:
	Computer();

	virtual bool CanInteract() const override;

	void OnPacketReceived();

	inline uint GetPacketReceived() const { return packetReceived; }

protected:
	virtual void Update(float deltaTime) override;

private:
	uint packetReceived;
};

