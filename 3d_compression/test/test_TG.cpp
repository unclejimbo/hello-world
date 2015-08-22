#include "../src/TG/TG.h"

int main() {
	TG tg;
	tg.ReadMesh("../../models/sphere_geodesic.obj");
	tg.EncodeConnectivity();
	system("PAUSE");
}