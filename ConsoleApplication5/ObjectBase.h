#pragma once
#include <Windows.h>
#include <d3dx10.h>
#include <vector>
#include"Collision.h"	
class ObjectBase
{
protected:
	float x;
	float y;
	bool isDeleted;
public:
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void GetPosition(float& x, float& y) { x = this->x; y = this->y; }
	virtual void Delete() { isDeleted = true; }
	bool IsDeleted() { return isDeleted; }
	ObjectBase();
	ObjectBase(float x, float y) :ObjectBase() { this->x = x; this->y = y; }
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) {};

	//
	// Collision ON or OFF ? This can change depending on object's state. For example: die
	//
	virtual int IsCollidable() { return 0; };

	// When no collision has been detected (triggered by CCollision::Process)
	virtual void OnNoCollision(DWORD dt) {};

	// When collision with an object has been detected (triggered by CCollision::Process)
	virtual void OnCollisionWith(LPCOLLISIONEVENT e) {};

	// Is this object blocking other object? If YES, collision framework will automatically push the other object
	virtual int IsBlocking() { return 1; }

	~ObjectBase();

	static bool IsDeleted(const LPGAMEOBJECT& o) { return o->isDeleted; }
};
};

