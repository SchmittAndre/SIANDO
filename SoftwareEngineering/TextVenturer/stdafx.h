#pragma once

#ifndef DISABLE_VLD
#include <vld.h>
#endif

#include <assert.h>
#include <vector>
#include <queue>
#include <stack>
#include <thread>
#include <mutex>
#include <atomic>

#include <Shlwapi.h>
#include <Windows.h>
#include <ShlObj.h>
#include <tchar.h>

#define GLEW_STATIC

#include <glew.h>
#include <wglew.h>

#include <algorithm>
#include <string>
#include <fstream>
#include <sstream> 
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <regex>
#include <iomanip>

#define _USE_MATH_DEFINES
#include <math.h>
#define PI M_PI

#define STRINGIZE_HELPER(x) #x
#define STRINGIZE(x) STRINGIZE_HELPER(x)
#define WARNING(desc) message (__FILE__ "(" STRINGIZE(__LINE__) "): warning: " #desc)

#include "StringUtils.h"
#include "TypeShortcuts.h"
#include "ErrorHandling.h"
#include "FileStream.h"
#include "EventFunctions.h"

#include "vec2.h"
#include "Matrix2.h"
#include "Matrix3.h"
#include "Color.h"

#include "lodePNG.h"
#include "GLEnums.h"
#include "Shader.h"
#include "VAO.h"
#include "TextureData.h"
#include "Texture.h"
#include "BMPFont.h"
#include "RBO.h"
#include "FBO.h"
