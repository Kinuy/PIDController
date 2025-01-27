#include "PlotLegend.h"


LegendLabel::LegendLabel(RenderTarget& renderTarget){


    render(renderTarget);

};

void LegendLabel::render(RenderTarget& renderTarget){
    int baseline;
    cv::Size size = cv::getTextSize(_text, _fontFace, _fontScale, _fontThickness, &baseline);
    auto pos = renderTarget.innerToOuter(renderTarget.project(_position)) + cv::Point2d(size.height * 2, size.height / 2);
    cv::putText(renderTarget.outerMat(), _text, pos, _fontFace, _fontScale, _color, _fontThickness, cv::LINE_AA);
}



Legend::Legend(RenderTarget& renderTarget){
    //Axes* _parentAxes;


    render(renderTarget);

};

void Legend::render(RenderTarget& renderTarget){
    std::vector<Series*> seriesVec;
    for (const auto& drawable : _parentAxes->drawables()) {
        auto series = dynamic_cast<Series*>(drawable.get());
        if (series) {
            seriesVec.push_back(series);
        }
    }
    Axes axes;
    axes.setMargins(5, _width - 2 * _margin - 60, 5, 5)
        .setXLim({ -.2,1.2 })
        .setYLim({ -.2,seriesVec.size() - 1 + .2 })
        .setYReverse();
    for (size_t i = 0; i < seriesVec.size(); i++) {
        auto& series = *seriesVec[i];
        axes.create<Series>(std::vector<cv::Point>{ {0, (int)i}, { 1,(int)i } })
            .setLineType(series.getLineType())
            .setLineWidth(series.getLineWidth())
            .setColor(series.getColor())
            .setMarkerType(series.getMarkerType())
            .setMarkerSize(series.getMarkerSize());
        auto& label = axes.create<LegendLabel>();
        label._position = { 1,(int)i };
        label._text = series.getName();
    }
    cv::Rect rect(renderTarget.innerMat().cols - _width - _margin, _margin, _width, _height);
    if (rect.x >= 0 && rect.x + rect.width < renderTarget.innerMat().cols && rect.y >= 0 && rect.y + rect.height < renderTarget.innerMat().rows) {
        axes.render(renderTarget.innerMat()(rect));
        cv::rectangle(renderTarget.innerMat(), rect, cv::Scalar::all(0));
    }
}