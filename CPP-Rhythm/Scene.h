#pragma once
class Scene
{
public:
	Scene() {};
	~Scene() {};

	virtual void Initialize() = 0;
	virtual void Run() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
};
