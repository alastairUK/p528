#include "../include/p528Impl.h"

#include <algorithm>
#include <math.h>

/*=============================================================================
 |
 |  Description:  This function computes the line-of-sight ray optics
 |                as described in Annex 2, Section 7 of
 |                Recommendation ITU-R P.528-4, "Propagation curves for
 |                aeronautical mobile and radionavigation services using
 |                the VHF, UHF and SHF bands"
 |
 |        Input:  path          - Structure holding path parameters
 |                terminal_1    - Structure holding low terminal parameters
 |                terminal_2    - Structure holding high terminal parameters
 |                psi           - Reflection angle, in radians
 |
 |      Outputs:  params        - Structure holding resulting parameters
 |
 |      Returns:  [void]
 |
 *===========================================================================*/
void RayOptics(Path path, Terminal terminal_1, Terminal terminal_2, double psi, LineOfSightParams* params)
{
    // Step 1
    double z = (a_0__km / path.a_e__km) - 1;  // [Eqn 59]
    double k_a = 1 / (1 + z * cos(psi));      // [Eqn 60]
    params->a_a__km = a_0__km * k_a;          // [Eqn 61]

    // Step 2
    double delta_h_a1__km = terminal_1.delta_h__km * (params->a_a__km - a_0__km) / (path.a_e__km - a_0__km);  // [Eqn 62]
    double delta_h_a2__km = terminal_2.delta_h__km * (params->a_a__km - a_0__km) / (path.a_e__km - a_0__km);  // [Eqn 62]

    // Step 3
    double H__km[2] = { 0 };
    H__km[0] = terminal_1.h_r__km - delta_h_a1__km;  // [Eqn 63]
    H__km[1] = terminal_2.h_r__km - delta_h_a2__km;  // [Eqn 63]

    // Step 4
    double Hprime__km[2] = { 0 };
    for (int i = 0; i < 2; i++)
    {
        params->z__km[i] = params->a_a__km + H__km[i];                                 // [Eqn 64]
        params->theta[i] = acos(params->a_a__km * cos(psi) / params->z__km[i]) - psi;  // [Eqn 65]
        params->D__km[i] = params->z__km[i] * sin(params->theta[i]);                   // [Eqn 66]

        // [Eqn 67]
        if (psi > 1.56)
            Hprime__km[i] = H__km[i];
        else
            Hprime__km[i] = params->D__km[i] * tan(psi);
    }

    // Step 5
    double delta_z = fabs(params->z__km[0] - params->z__km[1]);  // [Eqn 68]

    // Step 6
    params->d__km = std::max(params->a_a__km * (params->theta[0] + params->theta[1]), 0.0);  // [Eqn 69]

    // Step 7
    double alpha = atan((Hprime__km[1] - Hprime__km[0]) / (params->D__km[0] + params->D__km[1]));  // [Eqn 70]
    params->r_0__km = (params->D__km[0] + params->D__km[1]) / cos(alpha);                          // [Eqn 71]
    params->r_12__km = (params->D__km[0] + params->D__km[1]) / cos(psi);                           // [Eqn 72]

    if (params->r_0__km < delta_z)
        params->r_0__km = delta_z;

    // Step 8
    params->delta_r = 4.0 * Hprime__km[0] * Hprime__km[1] / (params->r_0__km + params->r_12__km);  // [Eqn 73]

    // Step 9
    params->theta_h1 = alpha - params->theta[0];     // [Eqn 74]
    params->theta_h2 = -(alpha + params->theta[1]);  // [Eqn 75]
}