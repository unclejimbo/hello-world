#include "../src/TG/TG.h"
#include "../src/TMesh/TMesh.h"
#include <string>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

GLuint screenW = 800, screenH = 600;

int main() {
	TG tg;
	TMesh mesh;
	mesh.ReadObj("../../models/untitled.obj");
	tg.Encode(mesh);
	system("PAUSE");
}