#include "gtest/gtest.h"

#define FMT_HEADER_ONLY
#include "fmt/format.h"
#include "fmt/printf.h"

#define APPROVALS_GOOGLETEST
#include "ApprovalTests.v.10.9.1.hpp"
#include "p528.h"

#include <cassert>
#include <sstream>
#include <vector>
#include <numeric>
#include <random>

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

    void doCheck(int f__mhz, double Lb)
    {
        std::ostringstream os;
        writeHeader(os, f__mhz, Lb);

        auto numCols = std::max(h2__m.size(), h1__m.size());

        for (const auto d : d__km)
        {
            fmt::fprintf(os, "\n%d", d);

            for (decltype(numCols) i = 0; i < numCols; ++i)
            {
                Result res{};
                auto ret = Main(d, h1__m[i], h2__m[i], f__mhz, Lb, &res);

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

    void doCheckFullRes(int f__mhz, double Lb)
    {
        std::ostringstream os;
        writeHeader(os, f__mhz, Lb);

        auto numCols = std::max(h2__m.size(), h1__m.size());

        for (const auto d : d__km)
        {
            fmt::fprintf(os, "\n%d", d);

            for (decltype(numCols) i = 0; i < numCols; ++i)
            {
                Result res{};
                auto ret = Main(d, h1__m[i], h2__m[i], f__mhz, Lb, &res);

                os << ',';

                if (i == 0)
                {
                    fmt::fprintf(os, "%f,%f", -res.A_fs__db, -res.A__db);
                }
                else
                {
                    fmt::fprintf(os, "%f", -res.A__db);
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

TEST(ApprovalTests, Test125MHz_0_01FullRes)
{
    doCheckFullRes(125, 0.01);
}

TEST(ApprovalTests, Test125MHz_0_05FullRes)
{
    doCheckFullRes(125, 0.05);
}

TEST(ApprovalTests, Test125MHz_0_10FullRes)
{
    doCheckFullRes(125, 0.10);
}

TEST(ApprovalTests, Test125MHz_0_50FullRes)
{
    doCheckFullRes(125, 0.50);
}

TEST(ApprovalTests, Test125MHz_0_95FullRes)
{
    doCheckFullRes(125, 0.95);
}

TEST(ApprovalTests, Test300MHz_0_01FullRes)
{
    doCheckFullRes(300, 0.01);
}

TEST(ApprovalTests, Test300MHz_0_05FullRes)
{
    doCheckFullRes(300, 0.05);
}

TEST(ApprovalTests, Test300MHz_0_10FullRes)
{
    doCheckFullRes(300, 0.10);
}

TEST(ApprovalTests, Test300MHz_0_50FullRes)
{
    doCheckFullRes(300, 0.50);
}

TEST(ApprovalTests, Test300MHz_0_95FullRes)
{
    doCheckFullRes(300, 0.95);
}

TEST(ApprovalTests, Test600MHz_0_01FullRes)
{
    doCheckFullRes(600, 0.01);
}

TEST(ApprovalTests, Test600MHz_0_05FullRes)
{
    doCheckFullRes(600, 0.05);
}

TEST(ApprovalTests, Test600MHz_0_10FullRes)
{
    doCheckFullRes(600, 0.10);
}

TEST(ApprovalTests, Test600MHz_0_50FullRes)
{
    doCheckFullRes(600, 0.50);
}

TEST(ApprovalTests, Test600MHz_0_95FullRes)
{
    doCheckFullRes(600, 0.95);
}

TEST(ApprovalTests, Test1200MHz_0_01FullRes)
{
    doCheckFullRes(1200, 0.01);
}

TEST(ApprovalTests, Test1200MHz_0_05FullRes)
{
    doCheckFullRes(1200, 0.05);
}

TEST(ApprovalTests, Test1200MHz_0_10FullRes)
{
    doCheckFullRes(1200, 0.10);
}

TEST(ApprovalTests, Test1200MHz_0_50FullRes)
{
    doCheckFullRes(1200, 0.50);
}

TEST(ApprovalTests, Test1200MHz_0_95FullRes)
{
    doCheckFullRes(1200, 0.95);
}

TEST(ApprovalTests, Test2400MHz_0_01FullRes)
{
    doCheckFullRes(2400, 0.01);
}

TEST(ApprovalTests, Test2400MHz_0_05FullRes)
{
    doCheckFullRes(2400, 0.05);
}

TEST(ApprovalTests, Test2400MHz_0_10FullRes)
{
    doCheckFullRes(2400, 0.10);
}

TEST(ApprovalTests, Test2400MHz_0_50FullRes)
{
    doCheckFullRes(2400, 0.50);
}

TEST(ApprovalTests, Test2400MHz_0_95FullRes)
{
    doCheckFullRes(2400, 0.95);
}

TEST(ApprovalTests, Test5100MHz_0_01FullRes)
{
    doCheckFullRes(5100, 0.01);
}

TEST(ApprovalTests, Test5100MHz_0_05FullRes)
{
    doCheckFullRes(5100, 0.05);
}

TEST(ApprovalTests, Test5100MHz_0_10FullRes)
{
    doCheckFullRes(5100, 0.10);
}

TEST(ApprovalTests, Test5100MHz_0_50FullRes)
{
    doCheckFullRes(5100, 0.50);
}

TEST(ApprovalTests, Test5100MHz_0_95FullRes)
{
    doCheckFullRes(5100, 0.95);
}

TEST(ApprovalTests, Test9400MHz_0_01FullRes)
{
    doCheckFullRes(9400, 0.01);
}

TEST(ApprovalTests, Test9400MHz_0_05FullRes)
{
    doCheckFullRes(9400, 0.05);
}

TEST(ApprovalTests, Test9400MHz_0_10FullRes)
{
    doCheckFullRes(9400, 0.10);
}

TEST(ApprovalTests, Test9400MHz_0_50FullRes)
{
    doCheckFullRes(9400, 0.50);
}

TEST(ApprovalTests, Test9400MHz_0_95FullRes)
{
    doCheckFullRes(9400, 0.95);
}

TEST(ApprovalTests, Test15500MHz_0_01FullRes)
{
    doCheckFullRes(15500, 0.01);
}

TEST(ApprovalTests, Test15500MHz_0_05FullRes)
{
    doCheckFullRes(15500, 0.05);
}

TEST(ApprovalTests, Test15500MHz_0_10FullRes)
{
    doCheckFullRes(15500, 0.10);
}

TEST(ApprovalTests, Test15500MHz_0_50FullRes)
{
    doCheckFullRes(15500, 0.50);
}

TEST(ApprovalTests, Test15500MHz_0_95FullRes)
{
    doCheckFullRes(15500, 0.95);
}

TEST(LookForTroublesomInputs, Nan)
{
    Result res{};

    const auto d__km = 298;
    const auto h_1__meter = 20.000000001346052;
    const auto h_2__meter = 9000;
    const auto f__mhz = 3313;
    const auto time_percentage = 0.1;

    auto ret = Main(d__km, h_1__meter, h_2__meter, f__mhz, time_percentage, &res);

    EXPECT_EQ(std::isnan(res.A__db), false);
}

TEST(LookForTroublesomInputs, TestLotsOfInputs)
{
    std::mt19937 mt(12345678);

    auto         ud_d__km = std::uniform_real_distribution<>{ 0, 2000 };
    auto         ud_h_first = std::uniform_real_distribution<>{ 1.5, 20000 };
    auto         ud_h_second = std::uniform_real_distribution<>{ 1.5, 20000 };
    auto         ud_f__mhz  = std::uniform_real_distribution<>{ 125 , 15500 };
    auto         ud_time_percentage  = std::uniform_real_distribution<>{ 0.01 , 0.99 };

    const size_t numPoints = 1000000;

    for (size_t cnt = 0; cnt < numPoints; cnt++)
    {
        const auto d__km = ud_d__km(mt);
        const auto h_first = ud_h_first(mt);
        const auto h_second = ud_h_second(mt);
        const auto h_1__meter = std::min(h_first, h_second);
        const auto h_2__meter = std::max(h_first, h_second);
        const auto f__mhz = ud_f__mhz(mt);
        const auto time_percentage = ud_time_percentage(mt);

        Result res{};

        auto ret = Main(d__km, h_1__meter, h_2__meter, f__mhz, time_percentage, &res);

        EXPECT_EQ(std::isnan(res.A__db), false);
    }
}