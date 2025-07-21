#ifndef TESTGUI_H
#define TESTGUI_H

#include <vector>

#include "imgui/animation_curve.h"
#include "window.h"

class TestGUI {
public:
    static std::vector<BezierKeyframe> myCurve;
    static std::vector<BezierKeyframe> previousCurve;
    static BezierEditor editor;

    static void renderGUI();
    static void initializeFrame();
    static void init(const Window &window);
};


#endif // TESTGUI_H
