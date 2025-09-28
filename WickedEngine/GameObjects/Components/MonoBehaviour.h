#pragma once

class GameObject;

class MonoBehaviour
{
public:
	const GameObject* gameObject;

	virtual void Awake() {};
	virtual void Start() {};
	virtual void Update() {};
	virtual void FixedUpdate() {};
	virtual void OnDestroy() {};

	friend class GameObject;

protected:
	MonoBehaviour(GameObject* gameObject) : gameObject(gameObject){}
	virtual ~MonoBehaviour() {};
};

