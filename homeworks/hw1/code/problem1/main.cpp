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
            Solution D_1(argv[1], IMG_SIZE, IMG_SIZE);
            D_1.intensity_dividing(2);
            D_1.output("D_process_intensity_dividing_by_2.raw");

            Solution D_2(D_1);
            D_2.global_equalize_hist();
            D_2.output("D_global_equalize_hist.raw");

            Solution D_3(D_1);
            D_3.local_equalize_hist(51);
            D_3.output("D_local_equalize_hist.raw");

            Solution E_1(argv[1], IMG_SIZE, IMG_SIZE);
            E_1.intensity_dividing(3);
            E_1.output("E_process_intensity_dividing_by_3.raw");

            Solution E_2(E_1);
            E_2.global_equalize_hist();
            E_2.output("E_global_equalize_hist.raw");

            Solution E_3(E_1);
            E_3.local_equalize_hist(51);
            E_3.output("E_local_equalize_hist.raw");
        } catch (const char err[]) {
            printf("%s\n", err);
        }
    } else {
        printf("Need 1 image file. <inputImageName>");
    }
    return 0;
}
