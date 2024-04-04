#pragma once
#include <memory>

class Object {
protected:
	std::weak_ptr<Object> selfPointer;
	bool isDestroyed = false;
	bool isEnabled = false;
public:

#pragma region Constructor/Destructor
	Object();
	virtual ~Object();
#pragma endregion

#pragma region Utility
	virtual bool IsEnabledGlobal();
	bool GetDestroyStatus()const;
#pragma endregion

#pragma region State
	virtual void Enable(const bool pState);
	virtual void Destroy();
#pragma endregion

};