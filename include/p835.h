#pragma once

/*=============================================================================
 |
 |       Author:  William Kozma Jr
 |                wkozma@ntia.gov
 |                US Dept of Commerce, NTIA/ITS
 |                June 2021 : Geneva Study Group 3 Meetings
 |
 *===========================================================================*/
#include "constants.h"

//
// FUNCTIONS
///////////////////////////////////////////////

double ConvertToGeopotentialHeight(double h__km);
double ConvertToGeometricHeight(double h_prime__km);
double WaterVapourDensityToPressure(double rho, double T__kelvin);

double GlobalTemperature(double h__km);
double GlobalTemperature_Regime1(double h_prime__km);
double GlobalTemperature_Regime2(double h__km);
double GlobalPressure(double h__km);
double GlobalPressure_Regime1(double h_prime__km);
double GlobalPressure_Regime2(double h__km);
double GlobalWaterVapourDensity(double h__km, double rho_0);
double GlobalWaterVapourPressure(double h__km, double rho_0);
