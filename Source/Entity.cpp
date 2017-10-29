#include "Entity.h"

Entity::Entity(std::vector<GL_Mesh *> _meshes, vec3 _trans, vec3 _rot, vec3 _scal)
{

	meshes = _meshes;

	translation = _trans;
	rotation = _rot;
	scaling = _scal;

	

	worldMatrix = glm::mat4(1.0f);

	dirty = true;

}

Entity::Entity(GL_Mesh * _mesh, vec3 _trans, vec3 _rot, vec3 _scal)
{

	// Make a single element Mesh and pass it to the constructor
	std::vector<GL_Mesh *> _meshes;
	_meshes.push_back(_mesh);

	meshes = _meshes;
	translation = _trans;
	rotation = _rot;
	scaling = _scal;

	dirty = true;

}

Entity::~Entity()
{
}

void Entity::MoveRight(float factor)
{

	// TODO: This is frame dependant. We need an independant timer to get a fixed rate.
	translation.x += factor * 0.01f;
	dirty = true;


}

void Entity::MoveUp(float factor)
{
	// TODO: This is frame dependant. We need an independant timer to get a fixed rate.
	translation.y += factor * 0.01f;
	dirty = true;
}

void Entity::RotateZ(float factor)
{

	/*rotation.setZ(rotation.getZ() + factor * 0.001f);*/
	rotation.z += glm::radians(factor);
	dirty = true;

}

void Entity::ScaleBumpy()
{
	/*scaling.setX(scaling.getX() + 0.05f);*/
	scaling.x += 0.05f;
	dirty = true;

}

void Entity::RecalculateWorldMatrix()
{

	if (dirty) {

		worldMatrix = glm::mat4(1.0f);

		worldMatrix = glm::translate(worldMatrix, translation);
		worldMatrix = glm::rotate(worldMatrix, rotation.x, vec3(1.0f, 0.0f, 0.0f));
		worldMatrix = glm::rotate(worldMatrix, rotation.y, vec3(0.0f, 1.0f, 0.0f));
		worldMatrix = glm::rotate(worldMatrix, rotation.z, vec3(0.0f, 0.0f ,1.0f));
		worldMatrix = glm::scale(worldMatrix, scaling);

		// worldMatrix = transMatrix * rotatMatrix * scaleMatrix;

		dirty = false;

	}

	 // This depends on which renderer we are returning to...
	 // return glm::transpose(worldMatrix);

	// For OpenGL.
	// return worldMatrix;
}

void Entity::GLDraw(GL_Shader _shader)
{

	RecalculateWorldMatrix();

	// Draw the meshes with the transformation of the Entity
	unsigned int tranformLoc = glGetUniformLocation(_shader.Program, "transform");

	// glUniformMatrix4fv(tranformLoc, 1, GL_FALSE, glm::value_ptr(glm::transpose(worldMatrix)));
	glUniformMatrix4fv(tranformLoc, 1, GL_FALSE, glm::value_ptr(worldMatrix));

	for (std::vector<GL_Mesh *>::iterator it = meshes.begin(); it != meshes.end(); it++) {

		((GL_Mesh *)(*it))->Draw(_shader);

	}

}
