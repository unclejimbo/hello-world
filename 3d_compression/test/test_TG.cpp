#include "../src/TG/TG.h"

int main() {
	TG tg;
	tg.ReadMesh("../../models/sphere.obj");
	tg.EncodeConnectivity();
	system("PAUSE");
}