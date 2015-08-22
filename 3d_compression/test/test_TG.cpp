#include "../src/TG/TG.h"

int main() {
	TG tg;
	tg.ReadMesh("../../models/bunny.obj");
	tg.EncodeConnectivity();
	system("PAUSE");
}