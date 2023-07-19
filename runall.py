#!/usr/bin/env python

import argparse
import math
import os
import subprocess
import time


def print_stats(reports, name):
    data = [d[name] for d in reports]
    mini = min(data)
    maxi = max(data)
    avg = sum(data) / len(data)
    sdata = sorted(data)
    q1 = sdata[len(sdata)//4]
    median = sdata[len(data)//2]
    q3 = sdata[3 * len(data)//4]
    print(f"{name:>16s}", f"min={mini:.03f}", f"max={maxi:.03f}", f"avg={avg:.03f}", f"q1|med|q3={q1:.03f}|{median:.03f}|{q3:.03f}")

def main():
    parser = argparse.ArgumentParser(allow_abbrev=False)
    parser.add_argument("--build-folder", default="build", dest="binfolder")
    parser.add_argument("--count", default=100, type=int)
    args = parser.parse_args()

    NAMES = [
        "sdl3_testsurround",
        "sdl3_testaudioinfo",
        "sdl3_testatomic",
        "sdl3_testerror",
        "sdl3_testevdev",
        "sdl3_testfile",
        "sdl3_testthread",
        "sdl3_testkeys",
        "sdl3_testlocale",
    ]


    reports = []
    for run_i in range(args.count):
        report = {}
        env = {k: v for k, v in os.environ.items()}
        env["SDL_AUDIO_DRIVER"] = "dummy"
        env["SDL_VIDEO_DRIVER"] = "dummy"
        env["SDL_TESTS_QUICK"] = "1"
        for name in NAMES:
            start = time.time()
            subprocess.run([f"{args.binfolder}/{name}"], env=env)
            end = time.time()
            print(name, end - start)
            report[name] = end - start
        print(run_i, report)
        reports.append(report)

    for name in NAMES:
        print_stats(reports, name)

    return 0

if __name__ == "__main__":
    raise SystemExit(main())
