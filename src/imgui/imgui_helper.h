#ifndef IMGUI_HELPER_H
#define IMGUI_HELPER_H

#include "imgui.h"

ImVec2 operator+(const ImVec2& lhs, const ImVec2& rhs);
ImVec2 operator-(const ImVec2& lhs, const ImVec2& rhs);
ImVec2 operator-(const ImVec2&) ;
ImVec2 operator*(const ImVec2& lhs, float rhs);
ImVec2 operator*(float lhs, const ImVec2& rhs);
ImVec2 operator/(const ImVec2& lhs, float rhs);

ImVec2 ToScreen(ImVec2 origin, ImVec2 scale, float t, float v);
float ToScreenX(float origin, float scale, float t);
float FromScreenX(float screenX, float originX, float scaleX);
ImVec2 normalize2D(ImVec2 vector);
ImVec2 clamp(const ImVec2& vec, float min, float max);

#endif //IMGUI_HELPER_H
