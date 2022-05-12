import os
from sys import argv

TEST_CONFIG = "tests"
MAIN_CONFIG = "main"
CONFIGS = [TEST_CONFIG, MAIN_CONFIG]

def create_folder(path):
    if not os.path.exists(path):
        os.mkdir(path)


if len(argv) < 2 or argv[1] not in CONFIGS:
    print(f"please run {argv[0]} {CONFIGS}")
    exit(1)

create_folder("compiled")
create_folder("compiled/bin")

if argv[1] == TEST_CONFIG:
    print("building tests")
    os.system("gcc tests/TestsMain.cpp tests/MinHeap/MinHeapTests.cpp tests/QuickSort/QuickSortTests.cpp -I. -o compiled/bin/Tests.exe -DTESTING_BUILD")