#pragma once

class Mesh;
class Shader;

class Game
{
	Mesh* quad;
	Shader* shader;

	const float fixedDeltaTime = 1.0f / 60.0f;
	float deltaTime;
	float time;
	float fixedTime;

	void FixedUpdate();
	void Update();
	void Draw();
	bool Continue();

public:
	inline const float FixedDeltaTime() const { return fixedDeltaTime; }
	inline const float DeltaTime() const { return deltaTime; }
	inline const float Time() const { return time; }
	inline const float FixedTime() const { return fixedTime; }

	void Run();

	static Game& Current();
};

