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
    if (argc == 4) {
        try {
            Solution p3_a(argv[1], IMG_SIZE, IMG_SIZE);
            Solution p3_b(argv[2], IMG_SIZE, IMG_SIZE);
            Solution p3_c(argv[3], IMG_SIZE, IMG_SIZE);

            p3_b.reset().low_pass_filter(1.5).output("3.b_low_pass_filter.raw");
            Solution p3_b_better(p3_b);
            p3_b.reset().outlier_detection(3).output("3.b_outlier_detection.raw");
            p3_b.reset().median_filtering().output("3.b_median_filtering.raw");

            p3_c.reset().low_pass_filter(1.5).output("3.c_low_pass_filter.raw");
            p3_c.reset().outlier_detection(5).output("3.c_outlier_detection.raw");
            p3_c.reset().median_filtering().output("3.c_median_filtering.raw");
            Solution p3_c_better(p3_c);

            printf("\n");
            printf("p3_N1 PSNR:%f\n", p3_b_better.computer_psnr(p3_a.image.data));
            printf("p3_N2 PSNR:%f\n", p3_c_better.computer_psnr(p3_a.image.data));
        } catch (const char err[]) {
            printf("%s\n", err);
        }
    } else {
        printf("Need 3 image file. <origin> <noise image1> <noise image2>");
    }
    return 0;
}
