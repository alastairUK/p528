#include "gtest/gtest.h"

#define FMT_HEADER_ONLY
#include "fmt/format.h"
#include "fmt/printf.h"
#include "fmt/ranges.h"

#define APPROVALS_GOOGLETEST
#include "ApprovalTests.v.6.0.0.hpp"
#include "p528.h"

#include <cassert>
#include <sstream>
#include <vector>

//GTEST_API_ int _tmain(int argc, char* argv[])
//{
//    return RUN_ALL_TESTS();
//}

namespace
{
const std::vector<int> h2__m = { 1000, 1000, 1000, 1000, 1000, 10000, 10000, 10000, 10000, 10000, 10000, 20000, 20000, 20000, 20000, 20000, 20000, 20000 };
const std::vector<double> h1__m = { 1.5, 15, 30, 60, 1000, 1.5, 15, 30, 60, 1000, 10000, 1.5, 15, 30, 60, 1000, 10000, 20000 };
const std::vector<int> d__km = []() { std::vector<int> v(1001); std::iota(v.begin(), v.end(), 0); return v; }();

void writeHeader(std::ostream& os, int freq__MHz, double Lb)
{
    fmt::fprintf(os, "%dMHz / Lb(%.2f) dB\n", freq__MHz, Lb);

    fmt::fprintf(os, ",h2(m),");
    for (auto it = h2__m.begin(); it < h2__m.end(); ++it)
    {
        if (it != h2__m.begin())
            os << ',';

        fmt::fprintf(os, "%d", *it);
    }
    os << '\n';

    fmt::fprintf(os, ",h1(m),");
    for (auto it = h1__m.begin(); it < h1__m.end(); ++it)
    {
        if (it != h1__m.begin())
            os << ',';

        fmt::fprintf(os, "%g", *it);
    }
    os << '\n';

    os << "D (km),FSL";
}

std::string formatString(double val)
{
    auto str = fmt::format("{:.1f}", val);

    if (str.substr(str.size() - 2, 2) == ".0")
    {
        str = str.substr(0, str.size() - 2);

        if (str == "-0")
            str = "0";
    }

    return str;
}

void doCheck(int freqMHz, double Lb)
{
    std::ostringstream os;
    writeHeader(os, freqMHz, Lb);

    auto numCols = std::max(h2__m.size(), h1__m.size());

    for (const auto d : d__km)
    {
        fmt::fprintf(os, "\n%d", d);

        for (decltype(numCols) i = 0; i < numCols; ++i)
        {
            Result res{};
            auto ret = Main(d, h1__m[i], h2__m[i], freqMHz, Lb, &res);

            os << ',';

            auto loss = fmt::format("{:.1f}", -res.A__db);
            if (loss.substr(loss.size() - 2, 2) == ".0")
            {
                loss = loss.substr(0, loss.size() - 2);

                if (loss == "-0")
                    loss = "0";
            }

            if (i == 0)
            {
                fmt::fprintf(os, "%s,%s", formatString(-res.A_fs__db), formatString(-res.A__db));
            }
            else
            {
                fmt::fprintf(os, "%s", formatString(-res.A__db));
            }
        }
    }

    ApprovalTests::Approvals::verify(os.str());
}
}  // namespace

TEST(ApprovalTests, Test125MHz_0_01)
{
    doCheck(125, 0.01);
}

TEST(ApprovalTests, Test125MHz_0_05)
{
    doCheck(125, 0.05);
}

TEST(ApprovalTests, Test125MHz_0_10)
{
    doCheck(125, 0.10);
}

TEST(ApprovalTests, Test125MHz_0_50)
{
    doCheck(125, 0.50);
}

TEST(ApprovalTests, Test125MHz_0_95)
{
    doCheck(125, 0.95);
}

TEST(ApprovalTests, Test300MHz_0_01)
{
    doCheck(300, 0.01);
}

TEST(ApprovalTests, Test300MHz_0_05)
{
    doCheck(300, 0.05);
}

TEST(ApprovalTests, Test300MHz_0_10)
{
    doCheck(300, 0.10);
}

TEST(ApprovalTests, Test300MHz_0_50)
{
    doCheck(300, 0.50);
}

TEST(ApprovalTests, Test300MHz_0_95)
{
    doCheck(300, 0.95);
}

TEST(ApprovalTests, Test600MHz_0_01)
{
    doCheck(600, 0.01);
}

TEST(ApprovalTests, Test600MHz_0_05)
{
    doCheck(600, 0.05);
}

TEST(ApprovalTests, Test600MHz_0_10)
{
    doCheck(600, 0.10);
}

TEST(ApprovalTests, Test600MHz_0_50)
{
    doCheck(600, 0.50);
}

TEST(ApprovalTests, Test600MHz_0_95)
{
    doCheck(600, 0.95);
}

TEST(ApprovalTests, Test1200MHz_0_01)
{
    doCheck(1200, 0.01);
}

TEST(ApprovalTests, Test1200MHz_0_05)
{
    doCheck(1200, 0.05);
}

TEST(ApprovalTests, Test1200MHz_0_10)
{
    doCheck(1200, 0.10);
}

TEST(ApprovalTests, Test1200MHz_0_50)
{
    doCheck(1200, 0.50);
}

TEST(ApprovalTests, Test1200MHz_0_95)
{
    doCheck(1200, 0.95);
}

TEST(ApprovalTests, Test2400MHz_0_01)
{
    doCheck(2400, 0.01);
}

TEST(ApprovalTests, Test2400MHz_0_05)
{
    doCheck(2400, 0.05);
}

TEST(ApprovalTests, Test2400MHz_0_10)
{
    doCheck(2400, 0.10);
}

TEST(ApprovalTests, Test2400MHz_0_50)
{
    doCheck(2400, 0.50);
}

TEST(ApprovalTests, Test2400MHz_0_95)
{
    doCheck(2400, 0.95);
}

TEST(ApprovalTests, Test5100MHz_0_01)
{
    doCheck(5100, 0.01);
}

TEST(ApprovalTests, Test5100MHz_0_05)
{
    doCheck(5100, 0.05);
}

TEST(ApprovalTests, Test5100MHz_0_10)
{
    doCheck(5100, 0.10);
}

TEST(ApprovalTests, Test5100MHz_0_50)
{
    doCheck(5100, 0.50);
}

TEST(ApprovalTests, Test5100MHz_0_95)
{
    doCheck(5100, 0.95);
}

TEST(ApprovalTests, Test9400MHz_0_01)
{
    doCheck(9400, 0.01);
}

TEST(ApprovalTests, Test9400MHz_0_05)
{
    doCheck(9400, 0.05);
}

TEST(ApprovalTests, Test9400MHz_0_10)
{
    doCheck(9400, 0.10);
}

TEST(ApprovalTests, Test9400MHz_0_50)
{
    doCheck(9400, 0.50);
}

TEST(ApprovalTests, Test9400MHz_0_95)
{
    doCheck(9400, 0.95);
}

TEST(ApprovalTests, Test15500MHz_0_01)
{
    doCheck(15500, 0.01);
}

TEST(ApprovalTests, Test15500MHz_0_05)
{
    doCheck(15500, 0.05);
}

TEST(ApprovalTests, Test15500MHz_0_10)
{
    doCheck(15500, 0.10);
}

TEST(ApprovalTests, Test15500MHz_0_50)
{
    doCheck(15500, 0.50);
}

TEST(ApprovalTests, Test15500MHz_0_95)
{
    doCheck(15500, 0.95);
}