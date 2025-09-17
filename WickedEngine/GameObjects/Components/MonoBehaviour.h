#pragma once

class MonoBehaviour
{
public:
	virtual void Awake() {};
	virtual void Start() {};
	virtual void Update() {};
	virtual void FixedUpdate() {};
	virtual void OnDestroy() {};
	virtual ~MonoBehaviour() {};
};

