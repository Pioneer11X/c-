#pragma once
#include "BasicVertex.h"

#include "GL_Mesh.h"

#include "Shader.h"

#include <vector>
#include "Camera.h"

using namespace std;
using namespace glm;

class Entity
{

	std::vector<GL_Mesh *> meshes;

	mat4x4 worldMatrix;
	mat4x4 transMatrix;
	mat4x4 rotatMatrix;
	mat4x4 scaleMatrix;

public:

	vec3 translation;
	vec3 rotation;
	vec3 scaling;

	bool dirty;

public:

	Entity(std::vector<GL_Mesh *> _meshes, vec3 _trans, vec3 _rot, vec3 _scal);
	Entity(GL_Mesh * _mesh, vec3 _trans, vec3 _rot, vec3 _scal);
	~Entity();

	void MoveRight(float factor);
	void MoveUp(float factor);
	void MoveRightUsingMatrix(float factor);
	void MoveUpUsingMatrix(float factor);

	void RotateZ(float factor);

	void ScaleBumpy();

	void RecalculateWorldMatrix();

	void GLDraw(GL_Shader _shader, Camera gameCamera);

	void inline setTranslate(vec3 _translate) { translation = _translate; dirty = true; }

};
