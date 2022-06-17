// Widget from: https://github.com/ocornut/imgui/issues/1496#issuecomment-655048353

#ifndef GROUP_PANEL_H
#define GROUP_PANEL_H

#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui_internal.h"

void BeginGroupPanel(const char* name, const ImVec2& size);
void EndGroupPanel();

#endif
