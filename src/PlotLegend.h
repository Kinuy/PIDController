#pragma once

#include <CvPlot/core.h>
#include <CvPlot/gui/show.h>

using namespace CvPlot;

class LegendLabel :public Drawable {
public:
    LegendLabel(RenderTarget& renderTarget);
    std::string _text;
    cv::Point _position;
    const int _fontFace = cv::FONT_HERSHEY_SIMPLEX;
    const double _fontScale = .4;
    const int _fontThickness = 1;
    cv::Scalar _color = cv::Scalar(0, 0, 0);
	void render(RenderTarget& renderTarget) override;
};
struct Legend :public Drawable {
public:
    int _width = 160;
    int _height = 70;
    int _margin = 20;
    Legend(RenderTarget& renderTarget);
	Axes* _parentAxes;
	void render(RenderTarget& renderTarget) override;
};
