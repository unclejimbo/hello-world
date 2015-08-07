#include "../src/TG/TG.h"

int main() {
	TG tg;
	tg.ReadMesh("../../models/bunny/bunny.obj");
	tg.EncodeConnectivity();
	system("PAUSE");
}