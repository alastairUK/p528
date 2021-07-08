# Recommendation ITU-R P.528-5 - U.S. Reference Implementation #

Persistent Identifier: [![DOI](https://zenodo.org/badge/DOI/10.5281/zenodo.5081071.svg)](https://doi.org/10.5281/zenodo.5081071)

This code repository contains the U.S. Reference Software Implementation of Recommendation ITU-R P.528. This Recommendation contains a method for predicting basic transmission loss in the frequency range 100-30 000 MHz for aeronautical services.  The software implements Annex 2 of Rec P.528, the Step-by-Step method to computing propagation loss for air-to-ground paths.

Companion software ([p528-gui](https://github.com/NTIA/p528-gui)) provides a Graphical User Interface (GUI) that can be used with this software implementation. 

## Inputs ##

| Variable          | Type   | Units | Limits       | Description  |
|-------------------|--------|-------|--------------|--------------|
| `d__km`           | double | km    | 0 <= `d__km` | Great circle path distance between terminals |
| `h_1__meter`      | double | meter | 1.5 <= `h_1__meter` <= 20 000 | Height of the low terminal |
| `h_2__meter`      | double | meter | 1.5 <= `h_2__meter` <= 20 000 | Height of the high terminal |
| `f__mhz`          | double | MHz   | 100 <= `f__mhz` <= 30 000 | Frequency |
| `T_pol`           | int    |       |              | Polarization <ul><li>0 = Horizontal</li><li>1 = Vertical</li></ul> |
| `time`            | double |       | 1 <= `time` <= 99 | Time percentage |
 
## Outputs ##

Outputs to P.528 are contained within a defined `Results` structure.

| Variable   | Type   | Units | Description |
|------------|--------|-------|-------------|
| `d__km`    | double | km    | Great circle path distance.  Could be slightly different than specified in input variable if within LOS region |
| `A__db`    | double | dB    | Basic transmission loss |
| `A_fs__db` | double | dB    | Free space basic transmission loss |
| `A_a__db`  | double | dB    | Median atmospheric absorption loss |
| `theta_h1__rad` | double | rad | Elevation angle of the ray at the low terminal |
| `propagation_mode` | int |  | Mode of propagation <ul><li>1 = Line of Sight</li><li>2 = Diffraction</li><li>3 = Troposcatter</li></ul> |

## Return Codes ##

Possible return codes, including the corresponding defined constant name as defined in `p528.h`:

| Value | Const Name                       | Description  |
| ------|----------------------------------|--------------|
|     0 | `SUCCESS`                        | Successful execution |
|     1 | `ERROR_VALIDATION__D_KM`         | Path distance must be >= 0 km |
|     2 | `ERROR_VALIDATION__H_1`          | Low terminal height must be >= 1.5 meters |
|     3 | `ERROR_VALIDATION__H_2`          | High terminal height must be >= 1.5 meters |
|     4 | `ERROR_VALIDATION__TERM_GEO`     | Low terminal must be <= high terminal height |
|     5 | `ERROR_VALIDATION__F_MHZ_LOW`    | Frequency must be >= 100 MHz |
|     6 | `ERROR_VALIDATION__F_MHZ_HIGH`   | Frequency must be <= 30 000 MHz |
|     7 | `ERROR_VALIDATION__PERCENT_LOW`  | Time percentage must be >= 1 |
|     8 | `ERROR_VALIDATION__PERCENT_HIGH` | Time percentage must be <= 99 |
|     9 | `ERROR_VALIDATION__POLARIZATION` | Polarization must be 0 (Horizontal) or 1 (Vertical) |
|    10 | `ERROR_HEIGHT_AND_DISTANCE`      | Terminals are occupying the same point in space (they are the same height and 0 km apart) |
| 0xFF1 | `WARNING__DFRAC_TROPO_REGION`    | Warning that the diffraction and troposcatter model may not be physically consistent with each other. Caution should be taken when using the result |

Note: Return codes over 0xFF0 signify warnings occured in the calculation.  Use bitwise OR operations to diagnosis, as more than one warning could be possible.

## Example Values ##

The below table includes a select set of example inputs and outputs for testing purposes. The [P.528 CSV data files](https://www.itu.int/rec/R-REC-P.528/en) contain an extensive set of validation example values.

| `d__km` | `h_1__meter` | `h_2__meter` | `f__mhz` | `T_pol` | `time` | `A__db` |
| --------|--------------|--------------|----------|---------|--------|---------|
|      15 |           10 |        1 000 |      500 |       0 |     50 |   110.0 |
|     100 |          100 |       15 000 |    3 600 |       0 |     90 |   151.6 |
|   1 500 |           15 |       10 000 |    5 700 |       0 |     10 |   293.4 |
|      30 |            8 |       20 000 |   22 000 |       1 |     50 |   151.1 |

## Notes on Code Style ##

 * In general, variables follow the naming convention in which a single underscore denotes a subscript (pseudo-LaTeX format), where a double underscore is followed by the units, i.e. h_1__meter.
 * Variables are named to match their corresponding mathematical variables in the underlying Recommendation text.
 * Wherever possible, equation numbers are provided.  It is assumed that a user reviewing this source code would have a copy of the Recommendation's text available as a primary reference.

## Configure and Build ##

### C++ Software

The software is designed to be built into a DLL (or corresponding library for non-Windows systems).  The source code can be built for any OS that supports the standard C++ libraries.  A Visual Studio 2019 project file is provided for Windows users to support the build process and configuration.

### C#/.NET Wrapper Software

The .NET support of P.528 consists of a simple pass-through wrapper around the native DLL.  It is compiled to target .NET Framework 4.7.2.  Distribution and updates are provided through the published [NuGet package](https://github.com/NTIA/p528/packages).

## References ##

 * [Recommendation ITU-R P.528](https://www.itu.int/rec/R-REC-P.528/en)
 * [Rec ITU-R P.528 GUI](https://github.com/NTIA/p528-gui)

## Contact ##

For questions, contact Billy Kozma, (303) 497-6082, wkozma@ntia.gov
