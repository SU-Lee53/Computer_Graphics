#pragma once

class TransformManager
{
public:
	static TransformManager& GetInstance()
	{
		static TransformManager instance;
		return instance;
	}
	
	glm::mat4 GetTranslateMatrix(glm::vec3 move);
	glm::mat4 GetRotateMatrix(float degree, AXIS axis);
	glm::mat4 GetScaleMatrix(glm::vec3 scale);

private:
	TransformManager();
	~TransformManager();

};

