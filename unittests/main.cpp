/*****************************************************************************
 * Alpine Terrain Builder
 * Copyright (C) 2022 alpinemaps.org
 * Copyright (C) 2022 Adam Celarek <family name at cg tuwien ac at>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *****************************************************************************/

#include <chrono>
#include <cmath>
#include <limits>
#include <array>

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_session.hpp>

int main( int argc, char* argv[] ) {
#ifdef __ANDROID__
    std::vector<char*> argv_2;
    for (int i = 0; i < argc; ++i) {
        argv_2.push_back(argv[i]);
    }
    std::array<char, 20> logcat_switch = {"-o %debug"};
    argv_2.push_back(logcat_switch.data());
    int argc_2 = argc + 1;
    int result = Catch::Session().run( argc_2, argv_2.data() );
#else
    int result = Catch::Session().run( argc, argv );
#endif
    std::fflush(stdout);
    return result;
}

#ifdef NDEBUG
constexpr bool asserts_are_enabled = false;
#else
constexpr bool asserts_are_enabled = true;
#endif

TEST_CASE("sherpa/main: check that asserts are enabled")
{
    CHECK(asserts_are_enabled);
}

TEST_CASE("sherpa/main: check that NaNs are enabled (-ffast-math removes support, -fno-finite-math-only puts it back in)")
{
    CHECK(std::isnan(std::numeric_limits<float>::quiet_NaN() * float(std::chrono::system_clock::now().time_since_epoch().count())));
    CHECK(std::isnan(double(std::numeric_limits<float>::quiet_NaN() * float(std::chrono::system_clock::now().time_since_epoch().count()))));
}
