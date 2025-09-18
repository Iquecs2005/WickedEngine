#pragma once

#include <memory>

class GameObject;

class MonoBehaviour
{
public:
	const GameObject* gameObject;

	MonoBehaviour(GameObject* gameObject) : gameObject(gameObject){}
	virtual void Awake() {};
	virtual void Start() {};
	virtual void Update() {};
	virtual void FixedUpdate() {};
	virtual void OnDestroy() {};
	virtual ~MonoBehaviour() {};
};

