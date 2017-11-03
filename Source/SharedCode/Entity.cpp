#include "Entity.h"


Entity::Entity(std::vector<Mesh *> _meshes, vec3 _trans, vec3 _rot, vec3 _scal)
{

	meshes = _meshes;

	translation = _trans;
	rotation = _rot;
	scaling = _scal;

	
	///*Physics Stuff*/

	//b2BodyDef bodyDef;
	//if (isDynamic) {
	//	bodyDef.type = b2_dynamicBody;
	//}
	//bodyDef.position.Set(translation.x * 100.0f, translation.y * 100.0f);

	//physicsBody = (*world).CreateBody(&bodyDef);

	///*Physics Stuff End*/



	worldMatrix = glm::mat4(1.0f);

	dirty = true;

}

Entity::Entity(Mesh * _mesh, vec3 _trans, vec3 _rot, vec3 _scal)
{

	// Make a single element Mesh and pass it to the constructor
	std::vector<Mesh *> _meshes;
	_meshes.push_back(_mesh);

	meshes = _meshes;
	translation = _trans;
	rotation = _rot;
	scaling = _scal;

	///*Physics Stuff*/

	//b2BodyDef bodyDef;
	//if (isDynamic) {
	//	bodyDef.type = b2_dynamicBody;
	//}
	//bodyDef.position.Set(translation.x * 100.0f, translation.y * 100.0f);

	//physicsBody = (*world).CreateBody(&bodyDef);

	///*Physics Stuff End*/

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

void Entity::Draw(Shader _shader, Camera gameCamera)
{

	RecalculateWorldMatrix();

	// Draw the meshes with the transformation of the Entity
	unsigned int tranformLoc = glGetUniformLocation(_shader.Program, "transform");

	// glUniformMatrix4fv(tranformLoc, 1, GL_FALSE, glm::value_ptr(glm::transpose(worldMatrix)));
	glUniformMatrix4fv(tranformLoc, 1, GL_FALSE, glm::value_ptr(worldMatrix));
    
    // camera/view transformation
	// pass projection matrix to shader (note that in this case it could change every frame)
	glm::mat4 projection = glm::perspective(glm::radians(gameCamera.Zoom), float(800/600), 0.1f, 100.0f);
	_shader.setMat4("projection", projection);

	// camera/view transformation
	glm::mat4 view = gameCamera.GetViewMatrix();
	_shader.setMat4("view", view);

	for (std::vector<Mesh *>::iterator it = meshes.begin(); it != meshes.end(); it++) {

		((Mesh *)(*it))->Draw(_shader);

	}

}
