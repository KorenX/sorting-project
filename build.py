import os
from sys import argv

TEST_CONFIG = "tests"
MAIN_CONFIG = "main"
CONFIGS = [TEST_CONFIG, MAIN_CONFIG]

if len(argv) < 2 or argv[1] not in CONFIGS:
    print(f"please run {argv[0]} {CONFIGS}")
    exit(1)

if argv[1] == TEST_CONFIG:
    print("building tests")
    os.system("gcc tests/MinHeapTests.cpp -I. -o compiled/bin/MinHeapTests.exe -DTESTING_BUILD")