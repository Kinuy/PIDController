

#include "PIDController.h"
using namespace std;




int main() {
    double pGain = 1.0;
    double iGain = 0.5;
    double dGain = 0.1;
    double exitCriteria = 0.001;

    PIDController pidController(pGain, iGain, dGain);
    pidController.initLogger();

    double targetValue = 100.0;
    double measuredValue = 50.0;
    double steeringValue = 0.0;

    // sim loop
    for (int i = 0; i < 100; i++){
        steeringValue = pidController.calculateCurrentSteeringValue(targetValue, measuredValue);

        measuredValue += steeringValue*0.2;

        std::cout << "Step: " << i
            << ", steeringValue: " << steeringValue
            << ", measuredValue: " << measuredValue
            << std::endl;

        pidController.logger();

        if (abs(targetValue - measuredValue) < 0.001) {
            break;
        }
    }
    return 0;
}