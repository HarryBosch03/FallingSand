#pragma once
class Texture
{
public:
	Texture();
	Texture(const Texture& other) = delete;
	Texture& operator=(const Texture& other) = delete;
	~Texture();
};

