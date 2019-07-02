#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "../../../basic.h"

using namespace std;

#define IMG_SIZE 256
#define PI 3.1415926535

class Solution : public Basic {
  public:
    Solution(const char *filepath, unsigned height, unsigned width)
        : Basic(filepath, height, width) {}

  public:
    Basic &warping() {
        Matrix<unsigned char> temp(IMG_SIZE, IMG_SIZE);
        for (int i = 0; i < IMG_SIZE; i++) {
            for (int j = 0; j < IMG_SIZE; j++) {
                int x = i - IMG_SIZE / 2, y = j - IMG_SIZE / 2, r = IMG_SIZE / 2;
                double theta = -PI / 2 * (1 - sqrt(x * x + y * y) / 128);

                temp(i, j) = 255;
                if (x * x + y * y <= r * r) {
                    int u = get_u(x, y, theta), v = get_v(x, y, theta);
                    temp(i, j) = this->image(get_u(x, y, theta), get_v(x, y, theta));
                }
            }
        }
        for (int i = 0; i < this->image.size(); i++) {
            this->image(i) = temp(i);
        }
        return *this;
    }
    int get_u(int x, int y, double theta) {
        return cos(theta) * x + sin(theta) * y + IMG_SIZE / 2;
    }
    int get_v(int x, int y, double theta) {
        return cos(theta) * y - sin(theta) * x + IMG_SIZE / 2;
    }
};

int main(int argc, char *argv[]) {
    if (argc == 2) {
        try {
            Solution sample4(argv[1], IMG_SIZE, IMG_SIZE);

            sample4.high_pass_filter(1).output("sample4_high_pass_filter_5.raw");

            sample4.reset();
            sample4.high_pass_filter(2).output("sample4_high_pass_filter_9.raw");

            sample4.reset();
            sample4.unsharp_masking(4.0 / 5.0).output("sample4_unsharp_masking.raw");

            sample4.reset();
            sample4.warping().output("sample4_warping.raw");
        } catch (const char err[]) {
            printf("%s\n", err);
        }
    } else {
        printf("Need 1 image file. <inputImageName>");
    }
    return 0;
}
