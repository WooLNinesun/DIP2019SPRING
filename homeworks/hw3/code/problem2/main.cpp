#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>

#include "../../../basic.h"

using namespace std;

#define IMG_SIZE 512
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

            vector<Matrix<double>> T(9);
            for (int i = 0; i < 9; i++) {
                T[i].resize(IMG_SIZE, IMG_SIZE, 0);
            }
            sample.laws_method(T, 15);

        } catch (const char err[]) {
            printf("%s\n", err);
        }
    } else {
        printf("Need 1 image file. <inputImageName>");
    }
    return 0;
}
