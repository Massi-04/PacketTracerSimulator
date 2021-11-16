#pragma once
#include "GameFramework/Actor.h"
#include "Interactable.h"

class Switch : public Actor, public IInteractable
{
public:
	Switch();

	virtual bool CanInteract() const override;
};

