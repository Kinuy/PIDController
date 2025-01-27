#include <CvPlot/gui/show.h>
#include <CvPlot/core.h>
#include <opencv2/opencv.hpp>

#include "PIDController.h"
#include "Legend.h"
using namespace std;

int main() {
    double pGain = 0.05;
    double iGain = 0.05;
    double dGain = 0.01;
    double exitCriteria = 0.001;

    

    PIDController pidController(pGain, iGain, dGain);
    pidController.initLogger();

    double targetValue = 100.0;
    double measuredValue = 0.0;
    double steeringValue = 0.0;

    // sim loop
    for (int i = 0; i < 1000; i++){
        steeringValue = pidController.calculateCurrentSteeringValue(targetValue, measuredValue);

        measuredValue += steeringValue;

        std::cout << "Step: " << i
            << ", steeringValue: " << steeringValue
            << ", measuredValue: " << measuredValue
            << std::endl;

        pidController.logger();

        if (abs(targetValue - measuredValue) < 0.001) {
            break;
        }

        Sleep(10.0);
    }


    CvPlot::Axes axes = CvPlot::makePlotAxes();
    axes.create<CvPlot::Series>(pidController.getProportionalValues(), "-r").setName("prop. part");;
    axes.create<CvPlot::Series>(pidController.getIntegralValues(), "-g").setName("integr. part");;
    axes.create<CvPlot::Series>(pidController.getDifferentialValues(), "-b").setName("diff. part");;
    axes.create<CvPlot::Series>(pidController.getSteeringValues(), "-c").setName("steering");;
    axes.create<CvPlot::Series>(pidController.getMeasuredValues(), "-k").setName("measured");;

    axes.title("PID controller response -> target: 100");
    axes.create<Legend>()._parentAxes = &axes;
    CvPlot::show("PID Controller", axes);


    return 0;
}