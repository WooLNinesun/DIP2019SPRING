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
    if (argc == 4) {
        try {
            // smaple 1
            {
                Solution sample1(argv[1], IMG_SIZE, IMG_SIZE);

                sample1.process_edge_detection_1st_order(1, -1);
                sample1.output("sample1_1st_order_with_Prewitt_NT.raw");
                sample1.reset();
                sample1.process_edge_detection_1st_order(1, 27);
                sample1.output("sample1_1st_order_with_Prewitt_T.raw");
                sample1.reset();
                sample1.process_edge_detection_1st_order(2, -1);
                sample1.output("sample1_1st_order_with_Sobel_NT.raw");
                sample1.reset();
                sample1.process_edge_detection_1st_order(2, 28);
                sample1.output("sample1_1st_order_with_Sobel_T.raw");

                sample1.reset();
                sample1.process_edge_detection_2nd_order(1.4, 3);
                sample1.output("sample1_2nd_order.raw");

                sample1.reset();
                sample1.process_edge_detection_canny(1.4, 8, 30);
                sample1.output("sample1_canny.raw");
            }

            // smaple 2
            {
                Solution sample2(argv[2], IMG_SIZE, IMG_SIZE);

                sample2.process_edge_detection_1st_order(1, -1);
                sample2.output("sample2_1st_order_with_Prewitt_NT.raw");
                sample2.reset();
                sample2.process_edge_detection_1st_order(1, 32);
                sample2.output("sample2_1st_order_with_Prewitt_T.raw");
                sample2.reset();
                sample2.process_edge_detection_1st_order(2, -1);
                sample2.output("sample2_1st_order_with_Sobel_NT.raw");
                sample2.reset();
                sample2.process_edge_detection_1st_order(2, 33);
                sample2.output("sample2_1st_order_with_Sobel_T.raw");

                sample2.reset();
                sample2.process_edge_detection_2nd_order(1.4, 3);
                sample2.output("sample2_2nd_order.raw");

                sample2.reset();
                sample2.process_edge_detection_canny(1.4, 8, 30);
                sample2.output("sample2_canny.raw");
            }

            // smaple 3
            {
                Solution sample3(argv[3], IMG_SIZE, IMG_SIZE);

                sample3.process_edge_detection_1st_order(1, -1);
                sample3.output("sample3_1st_order_with_Prewitt_NT.raw");
                sample3.reset();
                sample3.process_edge_detection_1st_order(1, 39);
                sample3.output("sample3_1st_order_with_Prewitt_T.raw");
                sample3.reset();
                sample3.process_edge_detection_1st_order(2, -1);
                sample3.output("sample3_1st_order_with_Sobel_NT.raw");
                sample3.reset();
                sample3.process_edge_detection_1st_order(2, 40);
                sample3.output("sample3_1st_order_with_Sobel_T.raw");

                sample3.reset();
                sample3.process_edge_detection_2nd_order(1.4, 3);
                sample3.output("sample3_2nd_order.raw");

                sample3.reset();
                sample3.process_edge_detection_canny(1.4, 8, 20);
                sample3.output("sample3_canny.raw");
            }
        } catch (const char err[]) {
            printf("%s\n", err);
        }
    } else {
        printf("Need 1 image file. <inputImageName>");
    }
    return 0;
}
