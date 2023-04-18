#include <iostream>
#include <cmath>

class FeFET {
  private:
    double mobility; // electron mobility in the channel
    double oxideCapacitance; // oxide capacitance per unit area
    double channelWidth; // width of the channel
    double channelLength; // length of the channel
    double thresholdVoltage; // threshold voltage
    double polarization; // polarization state of the ferroelectric material in the gate stack
    double gateVoltage;
  public:
    // Constructor
    FeFET() {
      oxideCapacitance = 0.0;
      channelWidth = 0.0;
      channelLength = 0.0;
      thresholdVoltage = 0.0;
      polarization = 0.0; // initialize polarization to zero
      mobility = 0.0; // initialize mobilty to zero
    }

    

     // Set Length and Width of the FeFET
    void setOxideCapacitance(double Cox) {
      oxideCapacitance = Cox;
    }

    // Set Length and Width of the FeFET
    void setWidthAndLength(double W, double L) {
      channelWidth = W;
      channelLength = L;
    }

    // Set Threshold Voltage to a constant value
    void setThresholdVoltage(double Vth) {
      thresholdVoltage = Vth;
    }

    // Set polarization state of the ferroelectric material in the gate stack
    void setPolarization(double pol) {
      polarization = pol;
    }

    // Set mobilty of the elecron ferroelectric material in the gate stack
    void setMobility(double mob) {
      mobility = mob;
    }

    double getOxideCapacitance() const {
  return oxideCapacitance;
}

double getWidth() const {
  return channelWidth;
}

double getLength() const {
  return channelLength;
}

double getThresholdVoltage() const {
  return thresholdVoltage;
}

double getPolarization() const {
  return polarization;
}

double getMobility() const {
  return mobility;
}

double getGateVoltage() const {
  return gateVoltage;
}

double getChannelWidth() const {
      return channelWidth;
    }

double getChannelLength() const {
      return channelLength;
    }


    // Calculate drain current for given gate-source voltage
    double DrainCurrent(double V_GS) {
      double V_T_mod = thresholdVoltage + polarization; // modify threshold voltage based on polarization state
      double I_D = mobility * oxideCapacitance * (channelWidth/channelLength) * pow((V_GS - V_T_mod), 2) / 2.0;
      return I_D;
    }
};
