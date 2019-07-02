#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>

#include "../../../basic.h"

using namespace std;

#define IMG_SIZE 256
#define PI 3.1415926535

class Solution : public Basic {
  public:
    Solution(const char *filepath, unsigned height, unsigned width)
        : Basic(filepath, height, width) {}
    Solution() : Basic() {}
};

int main(int argc, char *argv[]) {
    if (argc == 2) {
        try {
            Solution sample(argv[1], IMG_SIZE, IMG_SIZE);

            sample.boundary_extraction().output("B.raw").reset();

            sample.connected_component_labeling().output("C.raw").reset();

            sample.thinning().output("D_1.raw").reset();
            sample.skeletonizing().output("D_2.raw").reset();

        } catch (const char err[]) {
            printf("%s\n", err);
        }
    } else {
        printf("Need 1 image file. <inputImageName>");
    }
    return 0;
}
