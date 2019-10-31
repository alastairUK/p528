#pragma once

// Operating system preprocessor directives *********************************************************

// Define DLLEXPORT for any platform
#ifdef _WIN32
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT
#endif


// Consts
enum CONST_MODE
{
    CONST_MODE__SEARCH = 0,
    CONST_MODE__DIFFRACTION = 1,
    CONST_MODE__SCATTERING = 2
};

enum PROP_MODE
{
    PROP_MODE__NOT_SET = 0,
    PROP_MODE__LOS = 1,
    PROP_MODE__DIFFRACTION = 2,
    PROP_MODE__SCATTERING = 3
};

//
// RETURN CODES
///////////////////////////////////////////////
enum ReturnCodes
{
    SUCCESS = 0,
    ERROR_VALIDATION__D_KM = 1,
    ERROR_VALIDATION__H_1 = 2,
    ERROR_VALIDATION__H_2 = 3,
    ERROR_VALIDATION__TERM_GEO = 4,
    ERROR_VALIDATION__F_MHZ_LOW = 5,
    ERROR_VALIDATION__F_MHZ_HIGH = 6,
    ERROR_VALIDATION__PERCENT_LOW = 7,
    ERROR_VALIDATION__PERCENT_HIGH = 8,
    ERROR_HEIGHT_AND_DISTANCE = 10,
    WARNING__DFRAC_TROPO_REGION = 0xFF1,
    WARNING__LOW_FREQUENCY = 0xFF2
};

// Struct
struct Path
{
    // Distances
    double d_ML__km;  // Maximum line of sight distance
    double d_0__km;   //
    double d_d__km;   // Distance where smooth earth diffraction is 0 dB

    // Earth
    double a_e__km;  // Effective earth radius
};

struct Terminal
{
    // Heights
    double h_r__km;      // Real terminal height
    double h_e__km;      // Effective terminal height
    double h__km;        // Terminal height used in model
    double delta_h__km;  //

    // Distances
    double d_r__km;  // Ray traced horizon distance
    double d__km;    // Horizon distance used in model

    // Angles
    double phi__rad;    // Central angle between the terminal and its smooth earth horizon
    double theta__rad;  // Incident angle of the grazing ray at the terminal
};

struct LineOfSightParams
{
    // Heights
    double z__km[2];

    // Distances
    double d__km;     // Path distance between terminals
    double r_0__km;   // Direct ray length
    double r_12__km;  // Indirect ray length
    double D__km[2];

    // Angles
    double theta_h1;
    double theta_h2;
    double theta[2];

    // Misc
    double a_a__km;    // Adjusted earth radius
    double delta_r;    // Ray length path difference
    double A_LOS__db;  // Loss due to LOS path
};

struct TroposcatterParams
{
    // Distances
    double d_s__km;  // Scattering distance
    double d_z__km;  // Half the scattering distance

    // Heights
    double h_v__km;  // Height of the common volume cross-over point

    // Angles
    double theta_s;  // Scattering angle
    double theta_A;  // cross-over angle

    // Losses
    double A_s__db;       // Troposcattter Loss
    double A_s_prev__db;  // Troposcatter Loss of Previous Test Point

    // Misc
    double M_s;  // Troposcatter Line Slope
};

struct Result
{
    int propagation_mode;  // Mode of propagation

    double d__km;     // Path distance used in calculations
    double A__db;     // Total loss
    double A_fs__db;  // Free space path loss
};

// Public Functions
////////////////////

DLLEXPORT int Main(double d__km, double h_1__meter, double h_2__meter, double f__mhz, double time_percentage, Result* result);
DLLEXPORT int MainEx(double d__km, double h_1__meter, double h_2__meter, double f__mhz, double time_percentage, Result* result,
                     Terminal* terminal_1, Terminal* terminal_2, TroposcatterParams* tropo, Path* path, LineOfSightParams* los_params);
