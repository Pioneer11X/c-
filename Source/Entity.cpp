#include "Entity.h"

Entity::Entity(GenericMesh * _mesh, vec3 _trans, vec3 _rot, vec3 _scal)
{

	mesh = _mesh;

	translation = _trans;
	rotation = _rot;
	scaling = _scal;

	worldMatrix = transMatrix = rotatMatrix = scaleMatrix = glm::mat4();

	transMatrix = glm::translate(transMatrix, translation);
	rotatMatrix = glm::rotate(rotatMatrix, 0.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	scaleMatrix = glm::scale(scaleMatrix, scaling);

	/*transMatrix = transMatrix.setTranslation(translation);
	rotatMatrix = rotatMatrix.rotationZYX(rotation);
	scaleMatrix = scaleMatrix.scale(scaling);*/

	worldMatrix = scaleMatrix * rotatMatrix * transMatrix;

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

	if (dirty) {

		transMatrix = glm::translate(transMatrix, translation);
		rotatMatrix = glm::rotate(rotatMatrix, rotation.x, vec3(1.0f, 0.0f, 0.0f));
		rotatMatrix = glm::rotate(rotatMatrix, rotation.y, vec3(0.0f, 1.0f, 0.0f));
		rotatMatrix = glm::rotate(rotatMatrix, rotation.z, vec3(0.0f, 0.0f ,1.0f));
		scaleMatrix = glm::scale(scaleMatrix, scaling);

		worldMatrix = transMatrix * rotatMatrix * scaleMatrix;

	}

	// This depends on which renderer we are returning to...
	return glm::transpose(worldMatrix);
}
