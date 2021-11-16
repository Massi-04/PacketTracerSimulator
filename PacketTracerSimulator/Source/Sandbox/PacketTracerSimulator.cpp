#include "PacketTracerSimulator.h"
#include "Computer.h"
#include "Switch.h"
#include "Packet.h"
#include "Cable.h"
#include "Light.h"
#include "Input/InputManager.h"

SET_APPLICATION(PacketTracerSimulator)

PacketTracerSimulator::PacketTracerSimulator() : hovered(nullptr), selected(nullptr)
{ 
	ResetConnection();
}

void PacketTracerSimulator::Start()
{
	// Spawn computers
	Computer* computers[4];
	Vec2 computerLocations[4] = { { 60.0f, 0.0f }, { -60.0f, 0.0f }, { 0.0f, 60.0f }, { 0.0f, -60.0f } };
	for (int i = 0; i < 4; i++)
	{
		computers[i] = SpawnActor<Computer>();
		computers[i]->SetLocation(computerLocations[i]);
		computers[i]->SetName("Computer " + std::to_string(i + 1));
	}
	// Spawn switch
	Switch* ciscoSwitch = SpawnActor<Switch>();
	ciscoSwitch->SetLocation({ 0.0f, 0.0f });
	ciscoSwitch->SetName("Switch");
	// Spawn cables
	Cable* cables[4];
	for (int i = 0; i < 4; i++)
	{
		cables[i] = SpawnActor<Cable>();
		cables[i]->SetConnected(ciscoSwitch, computers[i]);
		cables[i]->SetName("Cable " + std::to_string(i + 1));
	}
	// Spawn light
	Light* light = SpawnActor<Light>();
	light->SetLocation({ 90.0f, 90.0f });
	light->SetScale({ 0.1f, 0.1f });
	light->SetName("Light");
	connectionStatus = light;
}

void PacketTracerSimulator::Update()
{
	Application::Update();
	FindInteractable();
	Interact();
}

void PacketTracerSimulator::FindInteractable()
{
	mouseLocation = InputManager::GetMousePosition(true) / ENGINE_UNIT;
	for (int i = 0; i < GetActors().GetSize(); i++)
	{
		IInteractable* interactable = dynamic_cast<IInteractable*>(GetActors()[i]);
		if (interactable != nullptr && interactable->CanInteract())
		{
			hovered = GetActors()[i];
			return;
		}
	}
	hovered = nullptr;
}

void PacketTracerSimulator::Interact()
{
	static Vec2 selectedSpaceDelta;
	static bool leftButtonPressed = false;
	static bool rightButtonPressed = false;

	// get current button status
	bool currentLeftButtonPressed = InputManager::GetMouseButton(EMouseButton::LeftButton);
	bool currentRightButtonPressed = InputManager::GetMouseButton(EMouseButton::RightButton);

	// left mouse button
	if (!leftButtonPressed && currentLeftButtonPressed) // just pressed
	{
		selected = hovered;
		if (selected != nullptr)
			selectedSpaceDelta = mouseLocation - selected->GetLocation();
	}
	else if (leftButtonPressed && !currentLeftButtonPressed) // just released
	{
		selected = nullptr;
		selectedSpaceDelta = { 0.0f, 0.0f };
	}

	// right mouse button
	if (!rightButtonPressed && currentRightButtonPressed) // just pressed
		if (hovered != nullptr && selected == nullptr && !sending) // no interaction while dragging
		{
			Computer* pc = dynamic_cast<Computer*>(hovered);
			if (pc != nullptr) // only computers can be selected
			{
				if (connection[0] == nullptr)
				{
					connection[0] = pc;
					LOG("First computer selected\n");
				}
				else if (connection[1] == nullptr && connection[0] != hovered)
				{
					connection[1] = pc;
					LOG("Second computer selected\n");
					for (int i = 0; i < GetActors().GetSize(); i++)
						if (dynamic_cast<Switch*>(GetActors()[i])) // find the switch
						{
							sending = true;
							Packet* packet = SpawnActor<Packet>();
							// set packet location (computer1)
							packet->SetLocation(connection[0]->GetLocation());
							// set packet first target (switch)
							packet->AddTarget(GetActors()[i]);
							// set packet second target (computer2)
							packet->AddTarget(connection[1]);
							connectionStatus->SetSending(true);
							packet->lastPacketReachedCallback.SetObject(this);
							packet->lastPacketReachedCallback.SetProcedure(&PacketTracerSimulator::ResetConnection);
							break;
						}
				}
			}
			else
				LOG("Not a computer\n");
		}

	// update selected location
	if (selected != nullptr)
		selected->SetLocation(mouseLocation - selectedSpaceDelta);
	// update status
	leftButtonPressed = currentLeftButtonPressed;
	rightButtonPressed = currentRightButtonPressed;
}

void PacketTracerSimulator::ResetConnection()
{
	connection[0] = connection[1] = nullptr;
	sending = false;
	if (connectionStatus != nullptr)
		connectionStatus->SetSending(false);
	LOG("Connection reset\n");
}
