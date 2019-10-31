#pragma once

#include "p528.h"

constexpr double PI = 3.1415926535897932384;
constexpr double a_0__km = 6370.0;
constexpr double T_eo__km = 3.25;
constexpr double T_ew__km = 1.36;
constexpr double N_0 = 301;
constexpr double N_9000 = 329;
constexpr double epsilon = 15.0;
constexpr double sigma = 0.005;
constexpr double LOS_EPSILON = 0.0001;
constexpr double LOS_ITERATION = 25;
constexpr double THIRD = 1.0 / 3.0;

class data
{
  public:
    const static int NUM_OF_PROBS = 17;
    const static int K_ROWS = 17;

    const static double NR_Data[17][18];  // Data table with K-values and corresponding Nakagami-Rice distributions
    const static double P[NUM_OF_PROBS];  // Probabilities for interpolation and data tables
};

// Private Functions
//////////////////////

void GetPathLoss(double psi, Path path, Terminal terminal_1, Terminal terminal_2,
                 double f__mhz, double psi_limit, double A_dML__db, double A_d_0__db, LineOfSightParams* params, double* R_Tg);
void RayOptics(Path path, Terminal terminal_1, Terminal terminal_2, double psi, LineOfSightParams* result);
void TerminalGeometry(double N_s, double a_e__km, Terminal* terminal);
void Troposcatter(Path path, Terminal terminal_1, Terminal terminal_2, double d__km, double f__mhz, double N_s, TroposcatterParams* tropo_params);
int TranshorizonSearch(Path* path, Terminal terminal_1, Terminal terminal_2, double f__mhz,
                       double N_s, double A_dML__db, double* M_d, double* A_d0, double* d_crx__km, int* MODE);
double LinearInterpolation(double x1, double y1, double x2, double y2, double x);
void AtmosphericAbsorptionParameters(double f__mhz, double* gamma_oo, double* gamma_ow);
double CalculateEffectiveRayLength(double z_1__km, double z_2__km, double a_e__km, double d_arc__km, double beta__rad, double T_e__km);
void ReflectionCoefficients(double psi, double f__mhz, double* R_g, double* phi_g);
void LineOfSight(Path* path, Terminal terminal_1, Terminal terminal_2, LineOfSightParams* los_params, double f__mhz, double A_dML__db,
                 double time_percentage, double d__km, Result* result, double* K_LOS);
double SmoothEarthDiffraction(double d_1__km, double d_2__km, double f__mhz, double d_0__km);
double InverseComplementaryCumulativeDistributionFunction(double q);
void LongTermVariability(double h_r1__km, double h_r2__km, double d__km, double f__mhz, double time_percentage, double f_theta_h, double PL, double* Y_e__db, double* A_Y);
double TranshorizonAtmosphericAbsorptionLoss(Terminal terminal_1, Terminal terminal_2, Path path, TroposcatterParams tropo, double f__mhz);
void RayTrace(double N_s, double h_rx__km, double* arc_distance, double* theta_rx);
double FindKForYpiAt99Percent(double Y_pi__db);
double NakagamiRice(double K, double q);
double CombineDistributions(double A_M, double A_i, double B_M, double B_i, double q);
int ValidateInputs(double d__km, double h_1__meter, double h_2__meter, double f__mhz, double time_percentage);
