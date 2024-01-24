#ifndef GameObjClass
#define GameObjClass

#include <Shader_s.h>
#include <Camera.h>
#include <Model.h>

string modelpath;

Shader ourShader("shader1.vert", "shader1.frag");
Model ourModel(modelpath);

class GameObject
{
public: 
	string modelpath;
	unsigned int shaderID;
	glm::mat4 GOmodelmat = glm::mat4(1.f);



	void transform(glm::vec3 tvec, glm::vec3 svec, float angle, glm::vec3 rvec)
	{
		GOmodelmat = glm::translate(GOmodelmat, tvec);
		GOmodelmat = glm::scale(GOmodelmat, svec);
		GOmodelmat = glm::rotate(GOmodelmat, glm::radians(angle), rvec);
	}
	void draw(string modelpath) 
	{
		ourModel.Draw(ourShader);
	}
};

#endif