#pragma once

class ComputeShader : public Shader
{
private:
	friend class Shader; // private까지 접근 가능

	ComputeShader(wstring file);
	~ComputeShader();

public:
	virtual void Set() override; // 인터페이스

private:
	ID3D11ComputeShader* shader;
};

