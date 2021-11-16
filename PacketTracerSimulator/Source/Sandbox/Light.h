#pragma once
#include "GameFramework/Actor.h"

class Light : public Actor
{
public:
	Light();

	void SetSending(bool sending);

protected:
	virtual void Update(float deltaTime) override;

private:
	class Shader* lightShader;
	float colorChangeSpeed, currentAlpha;
	bool sending;
};

