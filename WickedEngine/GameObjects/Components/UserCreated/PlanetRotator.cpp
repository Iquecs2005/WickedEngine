#include "PlanetRotator.h"

#include "../../GameObject.h"
#include "../../Time.h"
#include <iostream>

void PlanetRotator::Update()
{
	gameObject->transform.rotation += Vector3(0, 0, rotatingSpeed * Time::GetDeltaTime());
}