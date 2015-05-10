#pragma once

#include "..\..\packages\nupengl.core.0.0.0.1\build\native\include\GL\glew.h" 
#include "..\..\packages\nupengl.core.0.0.0.1\build\native\include\GL\freeglut.h" 

#include "..\Rendering\VertexFormat.h"

#include <vector>
#include <map>

namespace Models
{
	//I explain this structure in Part III
	struct Model
	{
		unsigned int vao;
		std::vector<unsigned int> vbos;

		Model(){}
	};

	class GameModels
	{
	public:
		GameModels();
		~GameModels();
		void CreateTriangleModel(const std::string& gameModelName);
		void DeleteModel(const std::string& gameModelName);
		unsigned int GetModel(const std::string& gameModelName);
	private:
		std::map<std::string, Model> GameModelList;//keep our models
	};
}