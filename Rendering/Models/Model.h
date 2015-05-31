#pragma once

#include <vector>

#include "../IGameObject.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../tdogl/Texture.h"
#include "..\Camera.h"

namespace Rendering
{
	namespace Models //create another namespace
	{
		class Model :public IGameObject
		{
		public:
			Model();
			virtual ~Model();
			// methods from interface
			virtual void Draw() override;
			virtual void Update() override;
			virtual void SetProgram(GLuint shaderName) override;
			virtual void Destroy() override;

			virtual GLuint GetVao() const override;
			virtual const std::vector<GLuint>& GetVbos() const override;

			static tdogl::Bitmap ballTexture;
			static tdogl::Bitmap batTexture;
			static tdogl::Bitmap brickTexture;
			static tdogl::Bitmap grassTexture;

			static glm::vec3 getNorm(const glm::vec3 &, const glm::vec3 &, const glm::vec3 &);

		protected:
			GLuint vao;
			GLuint program;
			std::vector<GLuint> vbos;

			unsigned int verticesSize;
			tdogl::Texture* gTexture;

			GLuint camera;
			GLuint projection;
			GLuint model;
			GLuint texture2d;

			GLuint lightPosition;
			GLuint lightColor;

			glm::mat4 cameraMatrixCopy;

		};
	}
}