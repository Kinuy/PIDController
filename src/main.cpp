

#include "PIDController.h"
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
    return 0;
}