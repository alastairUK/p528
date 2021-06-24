#pragma once

// Define DLLEXPORT for any platform
#ifdef _WIN32
#define DLLEXPORT extern "C" __declspec(dllexport)
#else
#define DLLEXPORT
#endif

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#define PI                                  3.1415926535897932384
#define a_0__km                             6371.0
#define a_e__km                             9257.0
#define N_s                                 341
#define epsilon_r                           15.0
#define sigma                               0.005
#define LOS_EPSILON                         0.00001
#define THIRD                               1.0 / 3.0

// Consts
#define CONST_MODE__SEARCH                  0
#define CONST_MODE__DIFFRACTION             1
#define CONST_MODE__SCATTERING              2

#define CASE_1                              1
#define CASE_2                              2

#define PROP_MODE__NOT_SET                  0
#define PROP_MODE__LOS                      1
#define PROP_MODE__DIFFRACTION              2
#define PROP_MODE__SCATTERING               3

// List of valid polarizations
#define POLARIZATION__HORIZONTAL            0
#define POLARIZATION__VERTICAL              1

#define Y_pi_99_INDEX                       16

//
// RETURN CODES
///////////////////////////////////////////////

#define SUCCESS                             0
#define ERROR_VALIDATION__D_KM              1
#define ERROR_VALIDATION__H_1               2
#define ERROR_VALIDATION__H_2               3
#define ERROR_VALIDATION__TERM_GEO          4
#define ERROR_VALIDATION__F_MHZ_LOW         5
#define ERROR_VALIDATION__F_MHZ_HIGH        6
#define ERROR_VALIDATION__PERCENT_LOW       7
#define ERROR_VALIDATION__PERCENT_HIGH      8
#define ERROR_VALIDATION__POLARIZATION      9
#define ERROR_HEIGHT_AND_DISTANCE           10
#define WARNING__DFRAC_TROPO_REGION         20

//
// CONSTANTS
///////////////////////////////////////////////

#define RHO_0__M_KG                        7.5

//
// ERROR CODES
///////////////////////////////////////////////

#define ERROR_HEIGHT_TOO_SMALL              -1
#define ERROR_HEIGHT_TOO_LARGE              -2
