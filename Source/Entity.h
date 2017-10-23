#pragma once
#include "BasicVertex.h"
#include "GenericMesh.h"

#include "glm\glm.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include "glm\gtx\transform.hpp"

using namespace std;
using namespace glm;

class Entity
{

	GenericMesh * mesh;

	mat4x4 worldMatrix;
	mat4x4 transMatrix;
	mat4x4 rotatMatrix;
	mat4x4 scaleMatrix;

	vec3 translation;
	vec3 rotation;
	vec3 scaling;

	bool dirty;

public:

	Entity(GenericMesh * _mesh, vec3 _trans, vec3 _rot, vec3 _scal);
	~Entity();

	void MoveRight(float factor);
	void MoveUp(float factor);
	void MoveRightUsingMatrix(float factor);
	void MoveUpUsingMatrix(float factor);

	void RotateZ(float factor);

	void ScaleBumpy();

	mat4x4 GetWorldMatrix();

	inline  GenericMesh * GetMesh() { return mesh; }

};