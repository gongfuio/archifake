/*
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.


    Authors:
    -------

    Antony Ducommun <nitro@tmsrv.org>

*/

#include "archifake.hpp"


f64 Clock::frequencyScale = 1.0;


void Clock::setup() {
    struct timespec ts;

    memset(&ts, 0, sizeof(struct timespec));
    clock_getres(CLOCK_MONOTONIC, &ts);
    Clock::frequencyScale = (f64)(((i64u)ts.tv_sec + (i64u)ts.tv_nsec) * 1000l * 1000l * 1000l);
}


i64u Clock::tick() {
    struct timespec ts;

    memset(&ts, 0, sizeof(struct timespec));
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ((i64u)ts.tv_sec * 1000l * 1000l * 1000l + (i64u)ts.tv_nsec);
}

f64 Clock::elapsed(i64u lastTick) {
    return (f64)(Clock::tick() - lastTick) / Clock::frequencyScale;
}

void Clock::sleep(f64 dt) {
    struct timespec ts;
    f64 seconds;
    f64 nanoseconds = modf(dt, &seconds);

    memset(&ts, 0, sizeof(struct timespec));
    ts.tv_sec = (i64u)seconds;
    ts.tv_nsec = (i64u)nanoseconds * 1000l * 1000l * 1000l;
    nanosleep(&ts, NULL);
}
