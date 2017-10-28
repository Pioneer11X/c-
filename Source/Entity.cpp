#include "Entity.h"

Entity::Entity(std::vector<GL_Mesh *> _meshes, vec3 _trans, vec3 _rot, vec3 _scal)
{

	meshes = _meshes;

	translation = _trans;
	rotation = _rot;
	scaling = _scal;

	

	worldMatrix = transMatrix = rotatMatrix = scaleMatrix = glm::mat4(1.0f);

	//transMatrix = glm::translate(transMatrix, translation);
	//rotatMatrix = glm::rotate(rotatMatrix, 0.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	//scaleMatrix = glm::scale(scaleMatrix, scaling);

	//worldMatrix = scaleMatrix * rotatMatrix * transMatrix;
	
	worldMatrix = glm::translate(worldMatrix, translation);
	worldMatrix = glm::rotate(worldMatrix, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	worldMatrix = glm::scale(worldMatrix, scaling);

	dirty = true;

}

Entity::~Entity()
{
}

void Entity::MoveRight(float factor)
{

	// TODO: This is frame dependant. We need an independant timer to get a fixed rate.
	translation.x += factor * 0.001f;

	/*float newPositionX = translation.getX() + factor * 0.001f;
	translation.setX(newPositionX);*/

	dirty = true;


}

void Entity::RotateZ(float factor)
{

	/*rotation.setZ(rotation.getZ() + factor * 0.001f);*/
	rotation.z += factor * 0.001f;
	dirty = true;

}

void Entity::ScaleBumpy()
{
	/*scaling.setX(scaling.getX() + 0.05f);*/
	scaling.x += 0.05f;
	dirty = true;

}

mat4x4 Entity::GetWorldMatrix()
{

	//if (dirty) {

	//	transMatrix = glm::translate(transMatrix, translation);
	//	rotatMatrix = glm::rotate(rotatMatrix, rotation.x, vec3(1.0f, 0.0f, 0.0f));
	//	rotatMatrix = glm::rotate(rotatMatrix, rotation.y, vec3(0.0f, 1.0f, 0.0f));
	//	rotatMatrix = glm::rotate(rotatMatrix, rotation.z, vec3(0.0f, 0.0f ,1.0f));
	//	scaleMatrix = glm::scale(scaleMatrix, scaling);

	//	worldMatrix = transMatrix * rotatMatrix * scaleMatrix;

	//}

	// This depends on which renderer we are returning to...
	// return glm::transpose(worldMatrix);

	// For OpenGL.
	return worldMatrix;
}

void Entity::GLDraw(Shader _shader)
{

	// Draw the meshes with the transformation of the Entity
	unsigned int tranformLoc = glGetUniformLocation(_shader.Program, "transform");
	glUniformMatrix4fv(tranformLoc, 1, GL_FALSE, glm::value_ptr(worldMatrix));

	for (std::vector<GL_Mesh *>::iterator it = meshes.begin(); it != meshes.end(); it++) {

		((GL_Mesh *)(*it))->Draw(_shader);

	}

}
