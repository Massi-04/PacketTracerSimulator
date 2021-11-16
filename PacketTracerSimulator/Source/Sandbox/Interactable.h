#pragma once

class IInteractable
{
public:
	virtual bool CanInteract() const = 0;
};
