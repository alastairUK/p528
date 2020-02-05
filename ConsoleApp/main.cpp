#include "p528.h"

#include <cassert>
#include <iostream>
#include <map>

namespace
{
    const std::map<ReturnCodes, std::string> c_errorCodes = {
        { ERROR_VALIDATION__D_KM, "Path distance must be >= 0 km" },
        { ERROR_VALIDATION__H_1, "Low terminal height must be >= 1.5 meters" },
        { ERROR_VALIDATION__H_2, "High terminal height must be >= 1.5 meters" },
        { ERROR_VALIDATION__TERM_GEO, "Low terminal must be <= high terminal height" },
        { ERROR_VALIDATION__F_MHZ_LOW, "Frequency must be >= 125 MHz" },
        { ERROR_VALIDATION__F_MHZ_HIGH, "Frequency must be <= 15 500 MHz" },
        { ERROR_VALIDATION__PERCENT_LOW, "Time percentage must be >= 0.01" },
        { ERROR_VALIDATION__PERCENT_HIGH, "Time percentage must be <= 0.99" },
        { ERROR_HEIGHT_AND_DISTANCE, "Terminals are occupying the same point in space(they are the same height and 0 km apart)" },
        { WARNING__DFRAC_TROPO_REGION, "Warning that the diffraction and troposcatter model may not be physically consistent with each other.Caution should be taken when using the result" },
        { WARNING__LOW_FREQUENCY, "Warning that the entered frequency is less than the lower limit specified in P.528.Caution should be taken when using the result" },
    };

    void writeHeader()
    {
        std::cout << "\nDistance (km) (Path distance between terminals) -  0 <= d__km\n";
        std::cout << "Start Height (m) (Height of the low terminal) -  1.5 <= h_1__meter\n";
        std::cout << "End Height (m) (Height of the high terminal) -  1.5 <= h_2__meter\n";
        std::cout << "Frequency (MHz) (125 <= f__mhz <= 15 500)\n";
        std::cout << "Time Percentae (0.01 <= time_percentage <= 0.99)\n\n\n";
    }

    void runTest()
    {
        std::cout << "Enter Distance (km) \n";
        double d__km = 0;
        std::cin >> d__km;

        std::cout << "Enter Start Height (m) \n";
        double h1__m = 0;
        std::cin >> h1__m;

        std::cout << "Enter End Height (m) \n";
        double h2__m = 0;
        std::cin >> h2__m;

        std::cout << "Enter Frequency (MHz) \n";
        double f__mhz = 0;
        std::cin >> f__mhz;

        std::cout << "Enter Time Percentage \n";
        double time_percentage = 0;
        std::cin >> time_percentage;

        Result res{};
        auto ret = Main(d__km, h1__m, h2__m, f__mhz, time_percentage, &res);

        if (ret > 0)
        {
            std::cout << "===RESULT====\n";
            auto fnd = c_errorCodes.find(static_cast<ReturnCodes>(ret));

            if (fnd != c_errorCodes.end())
            {
                std::cout << fnd->second << "\n";
            }
            else
            {
                std::cout << "UNKNOWN ERROR\n";
            }
            std::cout << "=============\n\n\n";
        }
        else
        {
            std::string propModeStr;

            switch (res.propagation_mode)
            {
            case PROP_MODE__NOT_SET:
                propModeStr = "Not Set";
                break;
            case PROP_MODE__LOS:
                propModeStr = "LOS";
                break;
            case PROP_MODE__DIFFRACTION:
                propModeStr = "Diffraction";
                break;
            case PROP_MODE__SCATTERING:
                propModeStr = "Scattering";
                break;
            default:
                propModeStr = "Not Set";
                break;
            };

            std::cout << "===RESULT====\n";
            std::cout << "Propagation_mode:\t" << propModeStr << "\n";
            std::cout << "Path distance used in calculations (km):\t" << res.d__km << "\n";
            std::cout << "Total Loss (dB):\t" << res.A__db << "\n";
            std::cout << "Free space path loss (dB):\t" << res.A_fs__db << "\n";
            std::cout << "=============\n\n\n";
        }

    }
}
int main(void)
{
    writeHeader();

    while (true)
    {
        runTest();
    }
}