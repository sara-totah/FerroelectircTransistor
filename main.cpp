#include <iomanip>
#include "Ferroelectric_Transistor.cpp" // Include the FeFET header file

int main() {
  FeFET fefet;

  // set FeFET parameters
  fefet.setOxideCapacitance(3e-9);
  fefet.setWidthAndLength(1e-6, 0.1e-6);
  fefet.setThresholdVoltage(0.5);
  fefet.setPolarization(0.2);
  fefet.setMobility(100);

  // test drain current calculation
  double V_GS = 1.0;
  double I_D = fefet.DrainCurrent(V_GS);

  std::cout << "For V_GS = " << V_GS << " V, the drain current is " << std::scientific << std::setprecision(6) << I_D << " A" << std::endl;

  // test getters
  std::cout << "Oxide Capacitance: " << fefet.getOxideCapacitance() << " F/m^2" << std::endl;
  std::cout << "Channel Width: " << fefet.getChannelWidth() << " m" << std::endl;
  std::cout << "Channel Length: " << fefet.getChannelLength() << " m" << std::endl;
  std::cout << "Threshold Voltage: " << fefet.getThresholdVoltage() << " V" << std::endl;
  std::cout << "Polarization: " << fefet.getPolarization() << std::endl;
  std::cout << "Mobility: " << fefet.getMobility() << " cm^2/Vs" << std::endl;

  return 0;
}
