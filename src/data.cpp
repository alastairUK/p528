#include "..\include\p528.h"

// Data table with K-values and corresponding Nakagami-Rice distributions
const double data::NR_Data[K_ROWS][NUM_OF_PROBS + 1] = {
    { -40.0000, -0.1417, -0.1252, -0.1004, -0.0784, -0.0634,
      -0.0516, -0.0321, -0.0155, 0.0000, 0.0156, 0.0323,
      0.0518, 0.0639, 0.0790, 0.1016, 0.1270, 0.1440 },
    { -25.0000, -0.7676, -0.6811, -0.5496, -0.4312, -0.3487,
      -0.2855, -0.1764, -0.0852, 0.0000, 0.0897, 0.1857,
      0.2953, 0.3670, 0.4538, 0.5868, 0.7391, 0.8421 },
    { -20.0000, -1.3184, -1.1738, -0.9524, -0.7508, -0.6072,
      -0.5003, -0.3076, -0.1484, 0.0000, 0.1624, 0.3363,
      0.5309, 0.6646, 0.8218, 1.0696, 1.3572, 1.5544 },
    { -18.0000, -1.6264, -1.4508, -1.1846, -0.9332, -0.7609,
      -0.6240, -0.3888, -0.1878, 0.0000, 0.2023, 0.4188,
      0.6722, 0.8373, 1.0453, 1.3660, 1.7416, 2.0014 },
    { -16.0000, -1.9963, -1.7847, -1.4573, -1.1558, -0.9441,
      -0.7760, -0.4835, -0.2335, 0.0000, 0.2564, 0.5308,
      0.8519, 1.0647, 1.3326, 1.7506, 2.2463, 2.5931 },
    { -14.0000, -2.4355, -2.1829, -1.7896, -1.4247, -1.1664,
      -0.9613, -0.5989, -0.2893, 0.0000, 0.3251, 0.6730,
      1.0802, 1.3558, 1.7028, 2.2526, 2.9156, 3.3872 },
    { -12.0000, -2.9491, -2.6507, -2.1831, -1.7455, -1.4329,
      -1.1846, -0.7381, -0.3565, 0.0000, 0.4123, 0.8535,
      1.3698, 1.7289, 2.1808, 2.9119, 3.8143, 4.4715 },
    { -10.0000, -3.5384, -3.1902, -2.6408, -2.1218, -1.7471,
      -1.4495, -0.9032, -0.4363, 0.0000, 0.5221, 1.0809,
      1.7348, 2.2053, 2.7975, 3.7820, 5.0372, 5.9833 },
    { -8.0000, -4.1980, -3.7975, -3.1602, -2.5528, -2.1091,
      -1.7566, -1.0945, -0.5287, 0.0000, 0.6587, 1.3638,
      2.1887, 2.3535, 3.5861, 4.9287, 6.7171, 8.1418 },
    { -6.0000, -4.9132, -4.4591, -3.7313, -3.0307, -2.5127,
      -2.1011, -1.3092, -0.6324, 0.0000, 0.8239, 1.7057,
      2.7374, 3.5494, 4.5714, 6.4059, 8.9732, 11.0972 },
    { -4.0000, -5.6559, -5.1494, -4.3315, -3.5366, -2.9421,
      -2.4699, -1.5390, -0.7434, 0.0000, 1.0115, 2.0942,
      3.3610, 4.4009, 5.7101, 8.1216, 11.5185, 14.2546 },
    { -2.0000, -6.3811, -5.8252, -4.9219, -3.9366, -3.3234,
      -2.8363, -1.5390, -0.7434, 0.0000, 1.1969, 2.0942,
      3.9770, 4.6052, 6.7874, 9.6278, 13.4690, 16.4258 },
    { 0.0000, -7.0246, -6.4248, -5.4449, -4.4782, -3.7425,
      -3.1580, -1.9678, -0.9505, 0.0000, 1.3384, 2.7709,
      4.4471, 5.8105, 7.5267, 10.5553, 14.5401, 17.5512 },
    { 2.0000, -7.5228, -6.8861, -5.8423, -4.8088, -4.0196,
      -3.3926, -2.1139, -1.0211, 0.0000, 1.4189, 2.9376,
      4.7145, 6.1724, 8.0074, 11.0005, 15.0271, 18.0527 },
    { 4.0000, -7.8525, -7.1873, -6.0956, -5.0137, -4.1879,
      -3.5318, -2.2007, -1.0630, 0.0000, 1.4563, 3.0149,
      4.8385, 6.2706, 8.0732, 11.1876, 15.2273, 18.2573 },
    { 6.0000, -8.1435, -7.3588, -6.2354, -5.1233, -4.2762,
      -3.6032, -2.2451, -1.0845, 0.0000, 1.8080, 3.7430,
      6.0071, 6.9508, 8.1386, 11.2606, 15.3046, 18.3361 },
    { 20.0000, -8.2238, -7.5154, -6.3565, -5.2137, -4.3470,
      -3.6584, -2.2795, -1.1011, 0.0000, 1.4815, 3.0672,
      4.9224, 6.3652, 8.1814, 11.3076, 15.3541, 18.3864 }
};

// Probabilities for interpolation and data tables
const double data::P[NUM_OF_PROBS] = { 0.01, 0.02, 0.05, 0.10, 0.15, 0.20, 0.30, 0.40, 0.50,
                                       0.60, 0.70, 0.80, 0.85, 0.90, 0.95, 0.98, 0.99 };