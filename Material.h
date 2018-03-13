#pragma once
#include "Common.h"

class Material
{
public:
	Material() {}
	Material(sf::Texture* tex, sf::Shader* shad);
	~Material();

	void SetTexture(sf::Texture* tex) { texture = tex; }
	void SetShader(sf::Shader* shad) { shader = shad; }

	sf::Texture* GetTexture() { return texture; }
	sf::Shader* GetShader() { return shader; }

	void BindShader();

	std::map<char*, float> floatUniforms;
	std::map<char*, sf::Shader::CurrentTextureType> currentTextureTypeUniforms;
	std::map<char*, sf::Glsl::Vec4> vec4Uniforms;

	void ClearAllUniforms()
	{
		floatUniforms.clear();
		currentTextureTypeUniforms.clear();
		vec4Uniforms.clear();
	}
	void AddFloatUniform(char* name, float value) { floatUniforms.insert(std::pair<char*, float>(name, value)); }
	void AddCurrentTextureTypeUniform(char* name, sf::Shader::CurrentTextureType type) { currentTextureTypeUniforms.insert(std::pair<char*, sf::Shader::CurrentTextureType>(name, type)); }
	void AddVec4Uniform(char* name, sf::Color vec4) { vec4Uniforms.insert(std::pair<char*, sf::Glsl::Vec4>(name, sf::Glsl::Vec4(vec4.r, vec4.g, vec4.b, vec4.a))); }

private:
	sf::Texture* texture;
	sf::Shader* shader;
};

