#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <queue>
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

  public:
    bool check_is_dot(int i, int j) {
        for (int k = i - 1, mi = 0; k <= i + 1; k++) {
            int x = symmetry(k, this->image.rows);
            for (int l = j - 1; l <= j + 1; l++, mi++) {
                int y = symmetry(l, this->image.cols);
                if (x == i && y == j) {
                    continue;
                }
                if (this->image(x, y) == 255) {
                    return false;
                }
            }
        }
        return true;
    }

    Solution &find_berries() {
        this->process_edge_detection_1st_order(1, 55).output("1st_order.raw");
        this->close({1, 1, 1, 1, 1, 1, 1, 1, 1}).output("close.raw");
        this->reverse().output("reverse.raw");
        this->shrinking().output("shrinking.raw");

        int count = 0;
        for (int i = 0; i < this->image.rows; i++) {
            for (int j = 0; j < this->image.cols; j++) {
                if (this->image(i, j) == 255 && check_is_dot(i, j)) {
                    count += 1;
                }
            }
        }

        printf("berries: %d\n", count);

        return *this;
    }
};

int main(int argc, char *argv[]) {
    if (argc == 2) {
        try {
            Solution sample(argv[1], IMG_SIZE, IMG_SIZE);

            sample.find_berries();

        } catch (const char err[]) {
            printf("%s\n", err);
        }
    } else {
        printf("Need 1 image file. <inputImageName>");
    }
    return 0;
}
