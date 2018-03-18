#include "Material.h"



Material::Material(sf::Texture* tex, sf::Shader* shad)
{
	texture = tex;
	shader = shad;
}


Material::~Material()
{
}

void Material::BindShader()
{
	if (shader == nullptr) return;

	for (auto&& uniform : floatUniforms)
	{
		shader->setUniform(uniform.first, uniform.second);
	}
	for (auto&& uniform : vec4Uniforms)
	{
		shader->setUniform(uniform.first, uniform.second);
	}
	for (auto&& uniform : currentTextureTypeUniforms)
	{
		shader->setUniform(uniform.first, uniform.second);
	}
	for (auto&& uniform : vec2Uniforms)
	{
		shader->setUniform(uniform.first, uniform.second);
	}
}
