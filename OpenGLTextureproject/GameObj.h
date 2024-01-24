#ifndef GameObjClass
#define GameObjClass

#include <Shader_s.h>
#include <Camera.h>
#include <Model.h>
using namespace std;

Shader ourShader("shader1.vert", "shader1.frag");

class GameObject
{
public: 
	string path;
	unsigned int shaderID;
	glm::mat4 GOmodelmat = glm::mat4(1.f);

	GameObject(string const& modelpath)
	{
		path = modelpath;
	}

	void transform(glm::vec3 tvec, glm::vec3 svec, float angle, glm::vec3 rvec)
	{
		GOmodelmat = glm::translate(GOmodelmat, tvec);
		GOmodelmat = glm::scale(GOmodelmat, svec);
		GOmodelmat = glm::rotate(GOmodelmat, glm::radians(angle), rvec);
	}


	void draw() 
	{
		Model ourModel(path);
		ourModel.Draw(ourShader);
	}
};

#endif