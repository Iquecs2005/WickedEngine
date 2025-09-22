#include "Renderer.h"

#include "../GameObject.h"

Renderer::Renderer(GameObject* gameObject) : MonoBehaviour(gameObject)
{
	gameObject->AddToRenderQueue(this);
}