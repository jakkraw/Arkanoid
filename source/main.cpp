#include "ezGame.h"
#include "arkanoid.h"

#include <Windows.h>
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nCmdShow) {
start(new Arkanoid);
}