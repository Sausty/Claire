#pragma once

#include <Windows.h>

#include "Core/Input/Keyboard.h"
#include "Core/Input/KeyCodes.h"
#include "Core/Input/Mouse.h"
#include "Core/Input/MouseCodes.h"
#include "Core/Input/InputManager.h"

#include "Graphics/Window.h"

#ifdef CLAIRE_VERSION_11
	#include "Graphics/DX11/View/DX11Viewport.h"
	#include "Graphics/DX11/DX11Types.h"
	#include "Graphics/DX11/DX11Context.h"
	#include "Graphics/DX11/DX11RenderContext.h"
	#include "Graphics/DX11/Buffers/DX11VertexArray.h"
	#include "Graphics/DX11/Buffers/DX11IndexBuffer.h"
	#include "Graphics/DX11/Buffers/DX11VertexBuffer.h"
	#include "Graphics/DX11/Buffers/DX11ConstantBuffer.h"
	#include "Graphics/DX11/Shaders/DX11Shader.h"
	#include "Graphics/DX11/Textures/DX11Texture2D.h"

	typedef DX11Viewport Viewport;
	typedef DX11Shader Shader;
	typedef DX11VertexArray VertexArray;
	typedef DX11VertexBuffer VertexBuffer;
	typedef DX11IndexBuffer IndexBuffer;
	typedef DX11ConstantBuffer ConstantBuffer;
	typedef DX11Texture2D Texture2D;
	typedef DX11BufferLayout BufferLayout;
	typedef DX11Context Context;
#elif defined(CLAIRE_VERSION_12)
	#include "Graphics/DX12/DX12Context.h"
	typedef DX12Context Context;
#endif

#include "Maths/vectors/tvec2.h"
#include "Maths/vectors/tvec3.h"
#include "Maths/vectors/tvec4.h"
#include "Maths/matrices/mat4.h"
#include "Maths/transform/mat4transform.h"