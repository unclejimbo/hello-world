#include "../src/TG/TG.h"

int main() {
	TG tg;
	tg.ReadMesh("../../models/untitled.obj");
	tg.EncodeConnectivity();
	system("PAUSE");
}