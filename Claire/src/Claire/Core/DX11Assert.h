#pragma once

#include <d3d11.h>
#include <Windows.h>

#define GraphicsAssert(func) if (FAILED(func)) { __debugbreak(); }