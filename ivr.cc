#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <signal.h>
#include "sharedspice.h"
#include <dlfcn.h> /* to load libraries*/
#include <unistd.h>
#include <ctype.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include "circuit_simulator.h"
#include "ivr_functions.h"


using namespace std;

IVR::IVR()
{
Delta_voltage = 0;
}


float IVR::measure_voltage(const char* measure_voltage_instruction, const char* file_name)
{
  citcuit_simulator_instruction(measure_voltage_instruction);
  string voltage;
  const char* feedback_voltage;
  string voltage_file_name;
  ifstream voltage_file_name_infile(file_name);
  getline(voltage_file_name_infile,voltage);
  cout<< "before erase voltage: "<< voltage << endl;
  voltage = voltage.erase(0,41);
  cout<< "after erase voltage: "<< voltage << endl;
  feedback_voltage = voltage.c_str();
  FILE* fp = fopen(file_name,"w");
  fclose(fp);
  return atof(feedback_voltage);

}

float IVR::Trans_Fun_Calculation(float input_voltage)
{
  Delta_voltage = Delta_voltage + (1 - input_voltage);
  cout << input_voltage << endl;
  return Delta_voltage;
}

const char* IVR::IVR_Update_Instruction(float update_voltage)
{
  ostringstream oss;
  oss << update_voltage;
  string Delta_voltage_string = oss.str();


  string IVR_alter;

  IVR_alter = "alter v.xivr1.vadd dc = ";


  string bbb = Delta_voltage_string;
  string aaa = IVR_alter;
  string ccc = "V";
  aaa+=bbb;
  aaa+=ccc;
  const char* IVR_alter_instruction = aaa.c_str();


  citcuit_simulator_instruction(IVR_alter_instruction);
}
