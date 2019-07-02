#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <queue>
#include <string>
#include <time.h>
#include <vector>

#define _USE_MATH_DEFINES
#include <cmath>

#include "../../../basic.h"

using namespace std;

#define IMG_SIZE 256

struct ValueCoordinate {
    int x, y, value;
    ValueCoordinate(int _x, int _y, int _value) : x(_x), y(_x), value(_value) {}};

struct CompareValue {
    bool operator()(ValueCoordinate const &p1,ValueCoordinate const &p2) {
        return p1.value < p2.value;
}};

class Solution : public Basic {
  public:
    Solution(const char *filepath, unsigned height, unsigned width)
        : Basic(filepath, height, width) {}
    Solution(unsigned height, unsigned width) : Basic(height, width) {}
    Solution() : Basic() {}

  public:
    Solution &hough_transform(Solution &accumulator) {
        int max_distance = hypot(this->image.rows, this->image.cols) + this->image.rows;

        accumulator.image.resize(max_distance, max_distance, 0);
        for (int i = 0; i < this->image.rows; i++) {
            for (int j = 0; j < this->image.cols; j++) {
                if (this->image(i, j) == 255) {
                    for (int k = 0; k < max_distance; k++) {
                        double theta = k * M_PI / max_distance;
                        double rho =
                            round(j * cos(theta) + i * sin(theta)) + this->image.rows;
                        accumulator.image((int)rho, k)++;
                    }
                }
            }
        }

        return accumulator;
    }

    Solution &draw_significant_lines(Solution &accumulator, int lines_number) {
        priority_queue<ValueCoordinate, vector<ValueCoordinate>, CompareValue> queue;
        for (int j = 0; j < accumulator.image.rows; j++) {
            for (int k = 0; k < accumulator.image.cols; k++) {
                queue.push(ValueCoordinate(k, j, accumulator.image(k, j)));
            }
        }
        for (int i = 0; i < lines_number; i++) {
            ValueCoordinate top = queue.top();
            queue.pop();

            draw_line(top.x, top.y, 128);
        }

        return *this;
    }

    void draw_line(int _rho, int theta, unsigned char color) {
        int rho = _rho - this->image.rows, x0, y0, x1, y1;
        polarToCartesian(rho, theta, x0, y0, x1, y1);

        if (abs(y1 - y0) < abs(x1 - x0)) {
            if (x0 > x1) {
                draw_line_low(x1, y1, x0, y0, color);
            } else {
                draw_line_low(x0, y0, x1, y1, color);
            }
        } else {
            if (y0 > y1) {
                draw_line_high(x1, y1, x0, y0, color);
            } else {
                draw_line_high(x0, y0, x1, y1, color);
            }
        }
    }

    void draw_line_low(int &x0, int &y0, int &x1, int &y1, unsigned char color) {
        int dx = x1 - x0, dy = y1 - y0, yi = 1;
        if (dy < 0) {
            yi = -1;
            dy = -dy;
        }
        int D = 2 * dy - dx, y = y0;
        for (int x = x0; x <= x1; x++) {
            if (this->image.cols > x && x >= 0 && this->image.rows > y && y >= 0) {
                this->image(x, y) = color;
            }
            if (D > 0) {
                y = y + yi;
                D = D - 2 * dx;
            }
            D = D + 2 * dy;
        }
    }

    void draw_line_high(int &x0, int &y0, int &x1, int &y1, unsigned char color) {
        int dx = x1 - x0, dy = y1 - y0, xi = 1;
        if (dy < 0) {
            xi = -1;
            dx = -dx;
        }
        int D = 2 * dx - dy, x = x0;
        for (int y = y0; y <= y1; y++) {
            if (this->image.cols > x && x >= 0 && this->image.rows > y && y >= 0) {

                this->image(x, y) = color;
            }
            if (D > 0) {
                x = x + xi;
                D = D - 2 * dy;
            }
            D = D + 2 * dx;
        }
    }
    void polarToCartesian(double rho, int theta, int &x1, int &y1, int &x2, int &y2) {

        int x0 = round(rho * cos(theta));
        int y0 = round(rho * sin(theta));

        x1 = round(x0 + 1000 * (-sin(theta)));
        y1 = round(y0 + 1000 * (cos(theta)));

        x2 = round(x0 - 1000 * (-sin(theta)));
        y2 = round(y0 - 1000 * (cos(theta)));
    }
};

int main(int argc, char *argv[]) {
    if (argc == 2) {
        try {
            Solution sample(argv[1], IMG_SIZE, IMG_SIZE);

            sample.process_edge_detection_canny(0.4, 5, 50).output("E.raw");

            Solution accumulator(IMG_SIZE, IMG_SIZE);
            sample.hough_transform(accumulator);

            Solution accumulator_H1 = accumulator;
            accumulator_H1.output("H1.raw");

            Solution accumulator_H2 = accumulator;
            accumulator_H2.global_equalize_hist().output("H2.raw");

            Solution sample_D1 = sample;
            sample_D1.draw_significant_lines(accumulator, 10).output("D1.raw");
            Solution sample_D2 = sample;
            sample_D2.draw_significant_lines(accumulator, 20).output("D2.raw");

        } catch (const char err[]) {
            printf("%s\n", err);
        }
    } else {
        printf("Need 1 image file. <inputImageName>");
    }
    return 0;
}
