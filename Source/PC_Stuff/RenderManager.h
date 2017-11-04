#pragma once

#include "Shader.h"
#include "../SharedCode/Entity.h"
#include "../SharedCode/Camera.h"

#include <vector>

#define DISPLAY_WIDTH			1200
#define DISPLAY_HEIGHT			800

class RenderManager {

private:

	unsigned int transformLoc;

public:

	Shader playerShader;
	Shader blockShader;

	Camera camera;

	Entity * playerEntity;
	std::vector<Entity *> scene;

	RenderManager() {

	};

	~RenderManager() {

	};

	void Init() {

		glViewport(0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT);

		glDepthRangef(0.1f, 10.0f);


		playerShader.Init("../Source/PC_Stuff/Shaders/core.vs", "../Source/PC_Stuff/Shaders/core.frag");
		blockShader.Init("../Source/PC_Stuff/Shaders/platform.vs", "../Source/PC_Stuff/Shaders/platform.frag");

		camera = Camera();

		return;

	}

	void drawScene() {
		
		playerEntity->RecalculateWorldMatrix();

		// Set it in there
		playerShader.setMat4("transform", playerEntity->worldMatrix);
		playerShader.setMat4("projection", glm::perspective(glm::radians(camera.Zoom), float(DISPLAY_HEIGHT / DISPLAY_WIDTH), 0.1f, 100.0f));
		playerShader.setMat4("view", camera.GetViewMatrix());
		playerEntity->Draw(playerShader, camera);

		for (std::vector<Entity *>::iterator it = scene.begin(); it != scene.end(); it++) {
			(*it)->RecalculateWorldMatrix();
		}

	}

	void drawEntity(Entity * e, Shader _shader) {
		e->RecalculateWorldMatrix();

		playerShader.Use();

		//int programID = glGetUniformLocation(playerShader.Program, "transform");
		//glUniformMatrix4fv(programID, 1, GL_FALSE, glm::value_ptr(e->worldMatrix));

		// Set it in there
		playerShader.setMat4("transform", e->worldMatrix);
		playerShader.setMat4("projection", glm::perspective(glm::radians(camera.Zoom), float(DISPLAY_HEIGHT / DISPLAY_WIDTH), 0.1f, 100.0f));
		playerShader.setMat4("view", camera.GetViewMatrix());
		e->Draw(playerShader, camera);
	}

};