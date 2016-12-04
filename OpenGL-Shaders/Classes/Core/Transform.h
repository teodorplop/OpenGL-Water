#pragma once

#include <glm\glm.hpp>

class Transform {
private:
	glm::vec3 position, rotation, scale;
	glm::mat4 translationMatrix, rotationMatrix, scalingMatrix;
	glm::mat4 matrix;

public:
	Transform();
	~Transform();

	glm::vec3 GetPosition();
	glm::vec3 GetRotation();
	glm::vec3 GetScale();
	glm::mat4 GetMatrix();

	void TranslateTo(const glm::vec3& position);
	void ScaleTo(const glm::vec3& scale);
	void RotateTo(const glm::vec3& rotation);

	void TranslateBy(const glm::vec3& distance);
	void ScaleBy(const glm::vec3& scale);
	void RotateBy(float angle, const glm::vec3& axis);
};