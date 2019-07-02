#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "../../../basic.h"

using namespace std;

#define IMG_SIZE 256

class Solution : public Basic {
  public:
    Solution(const char *filepath, unsigned height, unsigned width)
        : Basic(filepath, height, width) {}
};

int main(int argc, char *argv[]) {
    if (argc == 2) {
        try {
            Solution warmup(argv[1], IMG_SIZE, IMG_SIZE);

            warmup.horizontal_flipping().output("B_process_horizontal_flipping.raw");
            warmup.power_law(1.2).output("B_power_law_1.2.raw");
        } catch (const char err[]) {
            printf("%s\n", err);
        }
    } else {
        printf("Need 1 image file. <inputImageName>");
    }
    return 0;
}
