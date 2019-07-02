
#include <queue>
#include <string>
#include <vector>

#define _USE_MATH_DEFINES
#include <cmath>

#ifndef __BASIC_CPP
#define __BASIC_CPP

#include "basic.h"

using namespace std;

const vector<int> Basic::Prewitt_mask{
    -1, +0, +1, // row 1
    -1, +0, +1, // row 2
    -1, +0, +1, // row 3
    +1, +1, +1, // column 1
    +0, +0, +0, // column 2
    -1, -1, -1  // column 3
};
const vector<int> Basic::Sobel_mask{
    -1, +0, +1, // row 1
    -2, +0, +2, // row 2
    -1, +0, +1, // row 3
    +1, +2, +1, // column 1
    +0, +0, +0, // column 2
    -1, -2, -1  // column 3
};

const vector<int> Basic::four_neighbor_mask{
    +0, -1, +0, // line 1
    -1, +4, -1, // line 2
    +0, -1, +0, // line 3
};

const vector<int> Basic::eight_neighbor_non_separable_mask{
    -1, -1, -1, // line 1
    -1, +8, -1, // line 2
    -1, -1, -1, // line 3
};

const vector<int> Basic::eight_neighbor_separable_mask{
    -2, +1, -2, // line 1
    +1, +4, +1, // line 2
    -2, +1, -2, // line 3
};
const vector<int> Basic::high_pass_filter_9{
    -1, -1, -1, // line 1
    -1, +9, -1, // line 2
    -1, -1, -1  // line 3
};
const vector<int> Basic::high_pass_filter_5{
    +0, -1, +0, // line 1
    -1, +5, -1, // line 2
    +0, -1, +0  // line 3
};

const vector<int> Basic::S_conditional_patterns_indeies = {0, 1, 2,  4,  5, 7,
                                                           8, 9, 10, 11, 12};
const vector<int> Basic::T_conditional_patterns_indeies = {3, 4, 5, 6, 8, 9, 10, 11, 12};
const vector<int> Basic::K_conditional_patterns_indeies = {3, 4, 8, 9, 10, 11, 12, 13};

const vector<vector<vector<unsigned char>>> Basic::conditional_patterns = {
    {// S 1
     {0, 0, I, /**/ 0, I, 0, /**/ 0, 0, 0},
     {I, 0, 0, /**/ 0, I, 0, /**/ 0, 0, 0},
     {0, 0, 0, /**/ 0, I, 0, /**/ I, 0, 0},
     {0, 0, 0, /**/ 0, I, 0, /**/ 0, 0, I}},
    {// S 2
     {0, 0, 0, /**/ 0, I, I, /**/ 0, 0, 0},
     {0, I, 0, /**/ 0, I, 0, /**/ 0, 0, 0},
     {0, 0, 0, /**/ I, I, 0, /**/ 0, 0, 0},
     {0, 0, 0, /**/ 0, I, 0, /**/ 0, I, 0}},
    {// S 3
     {0, 0, I, /**/ 0, I, I, /**/ 0, 0, 0},
     {0, I, I, /**/ 0, I, 0, /**/ 0, 0, 0},
     {I, I, 0, /**/ 0, I, 0, /**/ 0, 0, 0},
     {I, 0, 0, /**/ I, I, 0, /**/ 0, 0, 0},
     {0, 0, 0, /**/ I, I, 0, /**/ I, 0, 0},
     {0, 0, 0, /**/ 0, I, 0, /**/ I, I, 0},
     {0, 0, 0, /**/ 0, I, 0, /**/ 0, I, I},
     {0, 0, 0, /**/ 0, I, I, /**/ 0, 0, I}},
    {// TK 4
     {0, I, 0, /**/ 0, I, I, /**/ 0, 0, 0},
     {0, I, 0, /**/ I, I, 0, /**/ 0, 0, 0},
     {0, 0, 0, /**/ I, I, 0, /**/ 0, I, 0},
     {0, 0, 0, /**/ 0, I, I, /**/ 0, I, 0}},
    {// STK 4
     {0, 0, I, /**/ 0, I, I, /**/ 0, 0, I},
     {I, I, I, /**/ 0, I, 0, /**/ 0, 0, 0},
     {I, 0, 0, /**/ I, I, 0, /**/ I, 0, 0},
     {0, 0, 0, /**/ 0, I, 0, /**/ I, I, I}},
    {// ST 5
     {I, I, 0, /**/ 0, I, I, /**/ 0, 0, 0},
     {0, I, 0, /**/ 0, I, I, /**/ 0, 0, I},
     {0, I, I, /**/ I, I, 0, /**/ 0, 0, 0},
     {0, 0, I, /**/ 0, I, I, /**/ 0, I, 0}},
    {// ST 5
     {0, I, I, /**/ 0, I, I, /**/ 0, 0, 0},
     {I, I, 0, /**/ I, I, 0, /**/ 0, 0, 0},
     {0, 0, 0, /**/ I, I, 0, /**/ I, I, 0},
     {0, 0, 0, /**/ 0, I, I, /**/ 0, I, I}},
    {// ST 6
     {I, I, 0, /**/ 0, I, I, /**/ 0, 0, I},
     {0, I, I, /**/ I, I, 0, /**/ I, 0, 0}},
    {// STK 6
     {I, I, I, /**/ 0, I, I, /**/ 0, 0, 0},
     {0, I, I, /**/ 0, I, I, /**/ 0, 0, I},
     {I, I, I, /**/ I, I, 0, /**/ 0, 0, 0},
     {I, I, 0, /**/ I, I, 0, /**/ I, 0, 0},
     {I, 0, 0, /**/ I, I, 0, /**/ I, I, 0},
     {0, 0, 0, /**/ I, I, 0, /**/ I, I, I},
     {0, 0, 0, /**/ 0, I, I, /**/ I, I, I},
     {0, 0, I, /**/ 0, I, I, /**/ 0, I, I}},
    {// STK 7
     {I, I, I, /**/ 0, I, I, /**/ 0, 0, I},
     {I, I, I, /**/ I, I, 0, /**/ I, 0, 0},
     {I, 0, 0, /**/ I, I, 0, /**/ I, I, I},
     {0, 0, I, /**/ 0, I, I, /**/ I, I, I}},
    {// STK 8
     {0, I, I, /**/ 0, I, I, /**/ 0, I, I},
     {I, I, I, /**/ I, I, I, /**/ 0, 0, 0},
     {I, I, 0, /**/ I, I, 0, /**/ I, I, 0},
     {0, 0, 0, /**/ I, I, I, /**/ I, I, I}},
    {// STK 9
     {I, I, I, /**/ 0, I, I, /**/ 0, I, I},
     {0, I, I, /**/ 0, I, I, /**/ I, I, I},
     {I, I, I, /**/ I, I, I, /**/ I, 0, 0},
     {I, I, I, /**/ I, I, I, /**/ 0, 0, I},
     {I, I, I, /**/ I, I, 0, /**/ I, I, 0},
     {I, I, 0, /**/ I, I, 0, /**/ I, I, I},
     {I, 0, 0, /**/ I, I, I, /**/ I, I, I},
     {0, 0, I, /**/ I, I, I, /**/ I, I, I}},
    {// STK 10
     {I, I, I, /**/ 0, I, I, /**/ I, I, I},
     {I, I, I, /**/ I, I, I, /**/ I, 0, I},
     {I, I, I, /**/ I, I, 0, /**/ I, I, I},
     {I, 0, I, /**/ I, I, I, /**/ I, I, I}},
    {// K 11
     {I, I, I, /**/ I, I, I, /**/ 0, I, I},
     {I, I, I, /**/ I, I, I, /**/ I, I, 0},
     {I, I, 0, /**/ I, I, I, /**/ I, I, I},
     {0, I, I, /**/ I, I, I, /**/ I, I, I}},
};
const vector<vector<unsigned char>> Basic::ST_unconditional_patterns = {
    // spur
    {0, 0, M, /**/ 0, M, 0, /**/ 0, 0, 0},
    {M, 0, 0, /**/ 0, M, 0, /**/ 0, 0, 0},
    {0, 0, 0, /**/ 0, M, 0, /**/ 0, M, 0},
    {0, 0, 0, /**/ 0, M, M, /**/ 0, 0, 0},
    // L Cluster
    {0, 0, M, /**/ 0, M, M, /**/ 0, 0, 0},
    {0, M, M, /**/ 0, M, 0, /**/ 0, 0, 0},
    {M, M, 0, /**/ 0, M, 0, /**/ 0, 0, 0},
    {M, 0, 0, /**/ M, M, 0, /**/ 0, 0, 0},
    {0, 0, 0, /**/ M, M, 0, /**/ M, 0, 0},
    {0, 0, 0, /**/ 0, M, 0, /**/ M, M, 0},
    {0, 0, 0, /**/ 0, M, 0, /**/ 0, M, M},
    {0, 0, 0, /**/ 0, M, M, /**/ 0, 0, M},
    // offset
    {0, M, M, /**/ M, M, 0, /**/ 0, 0, 0},
    {M, M, 0, /**/ 0, M, M, /**/ 0, 0, 0},
    {0, M, 0, /**/ 0, M, M, /**/ 0, 0, M},
    {0, 0, M, /**/ 0, M, M, /**/ 0, M, 0},
    // spur corner
    {0, A, M, /**/ 0, M, B, /**/ M, 0, 0},
    {M, B, 0, /**/ A, M, 0, /**/ 0, 0, M},
    {0, 0, M, /**/ A, M, 0, /**/ M, B, 0},
    {M, 0, 0, /**/ 0, M, B, /**/ 0, A, M},
    // corner clutter
    {M, M, D, /**/ M, M, D, /**/ D, D, D},
    // tee branch
    {D, M, 0, /**/ M, M, M, /**/ D, 0, 0},
    {0, M, D, /**/ M, M, M, /**/ 0, 0, D},
    {0, 0, D, /**/ M, M, M, /**/ 0, M, D},
    {D, 0, 0, /**/ M, M, M, /**/ D, M, 0},
    {D, M, D, /**/ M, M, 0, /**/ 0, M, 0},
    {0, M, 0, /**/ M, M, 0, /**/ D, M, D},
    {0, M, 0, /**/ 0, M, M, /**/ D, M, D},
    {D, M, D, /**/ 0, M, M, /**/ 0, M, 0},
    // vee branch
    {M, D, M, /**/ D, M, D, /**/ A, B, C},
    {M, D, C, /**/ D, M, B, /**/ M, D, A},
    {C, B, A, /**/ D, M, D, /**/ M, D, M},
    {A, D, M, /**/ B, M, D, /**/ C, D, M},
    // diagonal branch
    {D, M, 0, /**/ 0, M, M, /**/ M, 0, D},
    {0, M, D, /**/ M, M, 0, /**/ D, 0, M},
    {D, 0, M, /**/ M, M, 0, /**/ 0, M, D},
    {M, 0, D, /**/ 0, M, M, /**/ D, M, 0},
};
const vector<vector<unsigned char>> Basic::K_unconditional_patterns = {
    // spur
    {0, 0, 0, /**/ 0, M, 0, /**/ 0, 0, M},
    {0, 0, 0, /**/ 0, M, 0, /**/ M, 0, 0},
    {0, 0, M, /**/ 0, M, 0, /**/ 0, 0, 0},
    {M, 0, 0, /**/ 0, M, 0, /**/ 0, 0, 0},
    // single 4-connection
    {0, 0, 0, /**/ 0, M, 0, /**/ 0, M, 0},
    {0, 0, 0, /**/ 0, M, M, /**/ 0, 0, 0},
    {0, 0, 0, /**/ M, M, 0, /**/ 0, 0, 0},
    {0, M, 0, /**/ 0, M, 0, /**/ 0, 0, 0},
    // L corner
    {0, M, 0, /**/ 0, M, M, /**/ 0, 0, 0},
    {0, M, 0, /**/ M, M, 0, /**/ 0, 0, 0},
    {0, 0, 0, /**/ 0, M, M, /**/ 0, M, 0},
    {0, 0, 0, /**/ M, M, 0, /**/ 0, M, 0},
    // corner cluster
    {D, M, M, /**/ D, M, M, /**/ D, D, D},
    {D, D, D, /**/ M, M, D, /**/ M, M, D},
    {M, M, D, /**/ M, M, D, /**/ D, D, D},
    {D, D, D, /**/ D, M, M, /**/ D, M, M},
    // tee branch
    {D, M, D, /**/ M, M, M, /**/ D, 0, 0},
    {D, M, D, /**/ M, M, D, /**/ D, M, D},
    {D, D, D, /**/ M, M, M, /**/ D, M, D},
    {D, M, D, /**/ D, M, M, /**/ D, M, D},
    // vee branch
    {M, D, M, /**/ D, M, D, /**/ A, B, C},
    {M, D, C, /**/ D, M, B, /**/ M, D, A},
    {C, B, A, /**/ D, M, D, /**/ M, D, M},
    {A, D, M, /**/ B, M, D, /**/ C, D, M},
    // diagonal branch
    {D, M, 0, /**/ 0, M, M, /**/ M, 0, D},
    {0, M, D, /**/ M, M, 0, /**/ D, 0, M},
    {D, 0, M, /**/ M, M, 0, /**/ 0, M, D},
    {M, 0, D, /**/ 0, M, M, /**/ D, M, 0},
};

const vector<vector<double>> Basic::laws_mask = {
    {36, 1, 2, 1, 2, 4, 2, 1, 2, 1},       {12, 1, 0, -1, 2, 0, -2, 1, 0, -1},
    {12, -1, 2, -1, -2, 4, -2, -1, 2, -1}, {12, -1, -2, -1, 0, 0, 0, 1, 2, 1},
    {4, 1, 0, -1, 0, 0, 0, -1, 0, 1},      {4, -1, 2, -1, 0, 0, 0, 1, -2, 1},
    {12, -1, -2, -1, 2, 4, 2, -1, -2, -1}, {4, -1, 0, 1, 2, 0, -2, -1, 0, 1},
    {4, 1, -2, 1, -2, 4, -2, 1, -2, 1},
};

Basic::Basic() {}
Basic::Basic(const char *filepath, unsigned height, unsigned width) {
    this->origin.resize(height, width, 0);

    FILE *file;
    if (!(file = fopen(filepath, "rb"))) {
        printf("Cannot open file!");
        exit(1);
    }

    fread(&this->origin(0), sizeof(unsigned char), this->origin.size(), file);
    fclose(file);

    this->image = this->origin;
}
Basic::Basic(unsigned height, unsigned width) {
    this->origin.resize(height, width, 0);
    this->image = this->origin;
}

Basic &Basic::output(const char *filepath) {
    FILE *file;
    if (!(file = fopen(filepath, "wb"))) {
        printf("Cannot open file!");
    }

    fwrite(&this->image(0), sizeof(unsigned char), this->image.size(), file);
    fclose(file);

    return *this;
}

Basic &Basic::reset() {
    this->image = this->origin;
    return *this;
}

int Basic::symmetry(int n, int bound) {
    if (n < 0) {
        return -n;
    } else if (n >= bound) {
        return 2 * bound - n - 2;
    } else {
        return n;
    }
}

Basic &Basic::reverse() {
    for (int i = 0; i < this->image.size(); i++) {
        this->image(i) = (this->image(i) == 255) ? 0 : 255;
    }
    return *this;
}

void Basic::BFS(Matrix<unsigned char> &out, Coordinate Coord,
                unsigned char neighbor_method, unsigned char target,
                unsigned char modify) {
    queue<Coordinate> visit_queue;
    visit_queue.push(Coord);
    while (!visit_queue.empty()) {
        Coordinate now = visit_queue.front();
        visit_queue.pop();
        for (int i = -1; i <= 1; i++) {
            int x = symmetry(now.x + i, this->image.rows);
            for (int j = -1; j <= 1; j++) {
                int y = symmetry(now.y + j, this->image.cols);
                if (neighbor_method == 4 && i * j != 0) {
                    continue;
                }
                if (out(x, y) == target) {
                    out(x, y) = modify;
                    visit_queue.push(Coordinate(i, j));
                }
            }
        }
    }
}

Basic &Basic::horizontal_flipping() {
    for (int i = 0; i < this->image.rows; i++) {
        for (int j = 0; j < this->image.cols / 2; j++) {
            swap(this->image(i, j), this->image(i, 255 - j));
        }
    }

    return *this;
}

Basic &Basic::power_law(double p) {
    unsigned c = 1;
    for (int i = 0; i < this->image.rows; i++) {
        for (int j = 0; j < this->image.cols; j++) {
            double pixel = (double)this->image(i, j);
            this->image(i, j) = c * pow(pixel / 255.0, p) * 255;
        }
    }
    return *this;
}

Basic &Basic::intensity_dividing(unsigned d) {
    for (int i = 0; i < this->image.rows; i++) {
        for (int j = 0; j < this->image.cols; j++) {
            this->image(i, j) = this->image(i, j) / d;
        }
    }
    return *this;
}

Basic &Basic::global_equalize_hist() {
    int total = this->image.size();
    int n_bins = 256;

    vector<double> hist(n_bins, 0);
    for (int i = 0; i < total; i++) {
        hist[this->image(i)]++;
    }

    vector<double> cdf(hist);
    for (int i = 0; i < n_bins - 1; i++) {
        cdf[i + 1] += cdf[i];
    }

    double mincdf = 0.0;
    for (int i = 0; i < n_bins; i++) {
        if (cdf[i] != 0) {
            mincdf = cdf[i];
            break;
        }
    }

    vector<double> transfer_function(n_bins, 0);
    for (int i = 0; i < n_bins; i++) {
        // transfer_function(i) = round(
        //     ((cdf(i) - mincdf) / total - mincdf) * (n_bins - 1)
        // );
        transfer_function[i] = (unsigned char)round(
            (cdf[i] - mincdf) / (double)(total - mincdf) * (double)(n_bins - 1));
    }

    for (int i = 0; i < total; ++i) {
        this->image(i) = transfer_function[this->image(i)];
    }

    return *this;
}

Basic &Basic::local_equalize_hist(unsigned window_size) {
    int total = this->image.size();

    int half_size = (window_size / 2);
    for (int y = 0; y < this->image.rows; y++) {
        for (int x = 0; x < this->image.cols; x++) {
            double hist_sum = 0;
            double scale = 0;
            for (int yr = y - half_size; yr <= y + half_size; yr++) {
                for (int xr = x - half_size; xr <= x + half_size; xr++) {
                    if (yr < 0 || yr >= this->image.rows) {
                        continue;
                    }
                    if (xr < 0 || xr >= this->image.cols) {
                        continue;
                    }
                    scale++;

                    if (this->image(x, y) < this->image(xr, yr)) {
                        continue;
                    }
                    hist_sum++;
                }
            }
            this->image(x, y) = (255 / scale) * hist_sum;
        }
    }

    return *this;
}

Basic &Basic::low_pass_filter(double b) {
    double denominator = pow(b + 2, 2);
    double tmp1 = 1 / denominator;
    double tmp2 = tmp1 * b;
    double tmp3 = tmp2 * b;
    double filter[9] = {tmp1, tmp2, tmp1, tmp2, tmp3, tmp2, tmp1, tmp2, tmp1};

    Matrix<unsigned char> temp(this->image.rows, this->image.cols);
    for (int i = 0; i < this->image.rows; i++) {
        for (int j = 0; j < this->image.cols; j++) {
            for (int k = i - 1, fi = 0; k <= i + 1; k++) {
                int x = symmetry(k, this->image.rows);
                for (int l = j - 1; l <= j + 1; l++, fi++) {
                    int y = symmetry(l, this->image.cols);
                    temp(i, j) += filter[fi] * this->image(x, y);
                }
            }
        }
    }
    for (int i = 0; i < this->image.size(); i++) {
        this->image(i) = temp(i);
    }

    return *this;
}

Basic &Basic::low_pass_filter(Matrix<unsigned char> &out, double b) {
    double denominator = pow(b + 2, 2);
    double tmp1 = 1 / denominator;
    double tmp2 = tmp1 * b;
    double tmp3 = tmp2 * b;
    double filter[9] = {tmp1, tmp2, tmp1, tmp2, tmp3, tmp2, tmp1, tmp2, tmp1};

    Matrix<unsigned char> temp(this->image.rows, this->image.cols);
    for (int i = 0; i < this->image.rows; i++) {
        for (int j = 0; j < this->image.cols; j++) {
            for (int k = i - 1, fi = 0; k <= i + 1; k++) {
                int x = symmetry(k, this->image.rows);
                for (int l = j - 1; l <= j + 1; l++, fi++) {
                    int y = symmetry(l, this->image.cols);
                    temp(i, j) += filter[fi] * this->image(x, y);
                }
            }
        }
    }
    for (int i = 0; i < this->image.size(); i++) {
        out(i) = temp(i);
    }

    return *this;
}

Basic &Basic::high_pass_filter(int mask_num) {
    vector<int> mask;
    if (mask_num == 1) {
        mask = high_pass_filter_5;
    } else {
        mask = high_pass_filter_9;
    }

    Matrix<unsigned char> temp(this->image.rows, this->image.cols);
    for (int i = 0; i < this->image.rows; i++) {
        for (int j = 0; j < this->image.cols; j++) {
            for (int k = i - 1, mi = 0; k <= i + 1; k++) {
                int x = symmetry(k, this->image.rows);
                for (int l = j - 1; l <= j + 1; l++, mi++) {
                    int y = symmetry(l, this->image.cols);
                    temp(i, j) += mask[mi] * this->image(x, y);
                }
            }
        }
    }
    for (int i = 0; i < this->image.size(); i++) {
        this->image(i) = temp(i);
    }

    return *this;
}

Basic &Basic::high_pass_filter(Matrix<unsigned char> &out, int mask_num) {
    vector<int> mask;
    if (mask_num == 1) {
        mask = high_pass_filter_5;
    } else {
        mask = high_pass_filter_9;
    }

    Matrix<unsigned char> temp(this->image.rows, this->image.cols);
    for (int i = 0; i < this->image.rows; i++) {
        for (int j = 0; j < this->image.cols; j++) {
            for (int k = i - 1, mi = 0; k <= i + 1; k++) {
                int x = symmetry(k, this->image.rows);
                for (int l = j - 1; l <= j + 1; l++, mi++) {
                    int y = symmetry(l, this->image.cols);
                    temp(i, j) += mask[mi] * this->image(x, y);
                }
            }
        }
    }
    for (int i = 0; i < out.size(); i++) {
        out(i) = temp(i);
    }

    return *this;
}

Basic &Basic::outlier_detection(double e) {
    vector<unsigned char> temp(this->image.size(), 0);
    for (int i = 0; i < this->image.rows; i++) {
        for (int j = 0; j < this->image.cols; j++) {
            double sum = 0;
            for (int k = i - 1; k <= i + 1; k++) {
                int x = symmetry(k, this->image.rows);
                for (int l = j - 1; l <= j + 1; l++) {
                    int y = symmetry(l, this->image.cols);
                    if (k == i, l == j) {
                        continue;
                    }
                    sum += this->image(x, y);
                }
            }
            temp[i * this->image.cols + j] = sum / 8.0;
        }
    }
    for (int i = 0; i < this->image.size(); i++) {
        if (abs(this->image(i) - temp[i]) > e) {
            this->image(i) = temp[i];
        }
    }

    return *this;
}

Basic &Basic::median_filtering() {
    vector<unsigned char> temp(this->image.size(), 0);
    for (int i = 0; i < this->image.rows; i++) {
        for (int j = 0; j < this->image.cols; j++) {
            vector<unsigned char> median;
            for (int k = i - 1; k <= i + 1; k++) {
                int x = symmetry(k, this->image.rows);
                for (int l = j - 1; l <= j + 1; l++) {
                    int y = symmetry(l, this->image.cols);
                    median.push_back(this->image(x, y));
                }
            }
            sort(median.begin(), median.end());
            temp[i * this->image.cols + j] = median[4];
        }
    }
    for (int i = 0; i < this->image.size(); i++) {
        this->image(i) = temp[i];
    }

    return *this;
}

double Basic::computer_mse(const vector<unsigned char> &a) {
    double total = 0;
    for (int i = 0; i < this->image.rows; i++) {
        for (int j = 0; j < this->image.cols; j++) {
            total += pow(a[i * this->image.cols + j] - this->image(i, j), 2);
        }
    }
    return total / (this->image.size());
}

double Basic::computer_psnr(const vector<unsigned char> &a) {
    return 10 * log10(255 * 255 / computer_mse(a));
}

Basic &Basic::process_edge_detection_1st_order(int mask_k, int threshold) {
    Matrix<unsigned char> magnitude(this->image.rows, this->image.cols);
    Matrix<unsigned char> orientation(this->image.rows, this->image.cols);
    vector<int> mask((mask_k == 1) ? Basic::Prewitt_mask : Basic::Sobel_mask);
    generate_gradient(magnitude, orientation, mask);
    for (int i = 0; i < this->image.size(); i++) {
        if (threshold == -1) {
            this->image.data[i] = magnitude.data[i];
        } else {
            this->image.data[i] = (magnitude.data[i] > threshold) ? 255 : 0;
        }
    }

    return *this;
}

Basic &Basic::process_edge_detection_2nd_order(double gaussian_sigma, int threshold) {
    if (gaussian_sigma > 0) {
        Matrix<unsigned char> gaussian(this->image.rows, this->image.cols);
        generate_gaussian(gaussian, gaussian_sigma);
        for (int i = 0; i < this->image.size(); i++) {
            this->image.data[i] = gaussian.data[i];
        }
    }

    Matrix<int> laplacian(this->image.rows, this->image.cols);
    generate_laplacian(laplacian, Basic::four_neighbor_mask);
    for (int i = 0; i < this->image.size(); i++) {
        this->image.data[i] = laplacian.data[i] + 128;
    }

    for (int i = 0; i < this->image.size(); i++) {
        this->image.data[i] = 255;
        if (abs(laplacian.data[i]) < threshold) {
            this->image.data[i] = 0;
        }
    }

    // TODO
    // Matrix<unsigned char> zero_crossing(this->image.rows, this->image.cols);
    // generate_zero_crossing(zero_crossing, laplacian, threshold);
    // for (int i = 0; i < this->image.size(); i++) {
    //     this->image.data[i] = zero_crossing.data[i];
    // }
    return *this;
}

Basic &Basic::process_edge_detection_canny(double gaussian_sigma, int low_threshold,
                                           int high_threshold) {

    Matrix<unsigned char> gaussian(this->image.rows, this->image.cols);
    generate_gaussian(gaussian, gaussian_sigma);
    for (int i = 0; i < this->image.size(); i++) {
        this->image(i) = gaussian(i);
    }

    Matrix<unsigned char> magnitude(this->image.rows, this->image.cols);
    Matrix<unsigned char> orientation(this->image.rows, this->image.cols);
    generate_gradient(magnitude, orientation, Prewitt_mask);
    for (int i = 0; i < this->image.size(); i++) {
        this->image(i) = magnitude(i);
    }

    Matrix<unsigned char> suppression(this->image.rows, this->image.cols);
    generate_non_maximal_suppression(suppression, orientation);
    for (int i = 0; i < this->image.size(); i++) {
        this->image(i) = suppression(i);
    }

    // output("test.raw");

    for (int i = 0; i < this->image.size(); i++) {
        if (this->image(i) >= high_threshold) {
            this->image(i) = 255; // Edge Pixel
        } else if (this->image.data[i] < low_threshold) {
            this->image(i) = 0; // Non-Edge Pixel
        } else {
            this->image(i) = 128; // Candidate Pixel
        }
    }

    Matrix<unsigned char> connected(this->image.rows, this->image.cols);
    generate_connected_component(connected);
    for (int i = 0; i < this->image.size(); i++) {
        this->image.data[i] = (connected.data[i] == 255) ? 255 : 0;
    }

    return *this;
}

Basic &Basic::generate_gradient(Matrix<unsigned char> &magnitude,
                                Matrix<unsigned char> &orientation, vector<int> mask) {
    int mask_k = mask[5] + 2;
    vector<int> r_mask(mask.begin(), mask.begin() + 9);
    vector<int> c_mask(mask.begin() + 9, mask.end());
    for (int i = 0; i < this->image.rows; i++) {
        for (int j = 0; j < this->image.cols; j++) {
            double r_gradient = 0, c_gradient = 0;
            for (int k = i - 1, mi = 0; k <= i + 1; k++) {
                int x = symmetry(k, this->image.rows);
                for (int l = j - 1; l <= j + 1; l++, mi++) {
                    int y = symmetry(l, this->image.cols);
                    r_gradient += r_mask[mi] * this->image(x, y);
                    c_gradient += c_mask[mi] * this->image(x, y);
                }
            }

            r_gradient /= mask_k, c_gradient /= mask_k;

            magnitude(i, j) = hypot(r_gradient, c_gradient);
            orientation(i, j) = atan2(c_gradient, r_gradient);
            if (orientation(i, j) < 0) {
                orientation(i, j) += M_PI;
            }
        }
    }

    return *this;
}

Basic &Basic::generate_laplacian(Matrix<int> &out, const vector<int> &mask) {
    for (int i = 0; i < this->image.rows; i++) {
        for (int j = 0; j < this->image.cols; j++) {
            for (int k = i - 1, mi = 0; k <= i + 1; k++) {
                int x = symmetry(k, this->image.rows);
                for (int l = j - 1; l <= j + 1; l++, mi++) {
                    int y = symmetry(l, this->image.cols);
                    out(i, j) += mask[mi] * this->image(x, y);
                }
            }
            out(i, j) /= mask[4];
        }
    }

    return *this;
}

Basic &Basic::generate_zero_crossing(Matrix<unsigned char> &out, Matrix<int> &laplacian,
                                     int threshold) {
    for (int i = 0; i < this->image.size(); i++) {
        if (abs(laplacian.data[i]) <= threshold) {
            laplacian.data[i] = 0;
        }
    }

    for (int i = 0; i < this->image.rows; i++) {
        for (int j = 0; j < this->image.cols; j++) {
            out(i, j) = 0;

            int i_l = symmetry(i - 1, this->image.rows);
            int i_r = symmetry(i + 1, this->image.rows);
            int j_l = symmetry(j - 1, this->image.cols);
            int j_r = symmetry(j + 1, this->image.cols);
            if (laplacian(i, j) * laplacian(i_r, j) < 0) {
                out(i, j) = 255;
            }
            if (laplacian(i, j) * laplacian(i_r, j_r) < 0) {
                out(i, j) = 255;
            }
            if (laplacian(i, j) * laplacian(i, j_r) < 0) {
                out(i, j) = 255;
            }
            if (laplacian(i, j) == 0) {
                if (laplacian(i_l, j) * laplacian(i_r, j) < 0) {
                    out(i, j) = 255;
                }
                if (laplacian(i, j_l) * laplacian(i, j_r) < 0) {
                    out(i, j) = 255;
                }
                if (laplacian(i_l, j_l) * laplacian(i_r, j_r) < 0) {
                    out(i, j) = 255;
                }
                if (laplacian(i_l, j_r) * laplacian(i_r, j_l) < 0) {
                    out(i, j) = 255;
                }
            }
        }
    }

    return *this;
}

Basic &Basic::generate_gaussian(Matrix<unsigned char> &out, double sigma) {
    vector<double> filter(25, 0);
    generate_gaussian_filter(filter, sigma);
    for (int i = 0; i < this->image.rows; i++) {
        for (int j = 0; j < this->image.cols; j++) {
            for (int k = i - 2, fi = 0; k <= i + 2; k++) {
                int x = symmetry(k, this->image.rows);
                for (int l = j - 2; l <= j + 2; l++, fi++) {
                    int y = symmetry(l, this->image.cols);
                    out(i, j) += filter[fi] * this->image(x, y);
                }
            }
        }
    }

    return *this;
}

Basic &Basic::generate_gaussian_filter(vector<double> &filter, double sigma) {
    // sum is for normalization
    double sum = 0.0;

    // generating 5x5 filter
    double s = 2.0 * pow(sigma, 2.0);
    for (int x = -2; x <= 2; x++) {
        for (int y = -2; y <= 2; y++) {
            int index = (x + 2) * 5 + (y + 2);
            double r = x * x + y * y;
            filter[index] = (exp(-r / s)) / (M_PI * s);

            sum += filter[index];
        }
    }

    for (int i = 0; i < 25; i++) {
        filter[i] /= sum;
    }

    return *this;
}

Basic &Basic::generate_non_maximal_suppression(Matrix<unsigned char> &out,
                                               Matrix<unsigned char> &orientation) {
    double delta = M_PI / 8;
    for (int i = 1; i < this->image.rows - 1; i++) {
        for (int j = 1; j < this->image.cols - 1; j++) {
            double angle = orientation(i, j);
            int dx = 0, dy = 0;

            if ((0 <= angle && angle < delta) || (7 * delta <= angle && angle <= M_PI)) {
                dx = 1, dy = 0;
            } else if (delta <= angle && angle < 3 * delta) {
                dx = 1, dy = 1;
            } else if (3 * delta <= angle && angle < 5 * delta) {
                dx = 0, dy = 1;
            } else if (5 * delta <= angle && angle < 7 * delta) {
                dx = -1, dy = 1;
            }

            if ((this->image(i, j) > this->image(i + dx, j + dy)) &&
                (this->image(i, j) > this->image(i - dx, j - dy))) {
                out(i, j) = this->image(i, j);
            } else {
                out(i, j) = 0;
            }
        }
    }

    return *this;
}

Basic &Basic::generate_connected_component(Matrix<unsigned char> &out) {
    Matrix<unsigned char> temp(this->image);
    for (int i = 0; i < this->image.rows; i++) {
        for (int j = 0; j < this->image.cols; j++) {
            if (temp(i, j) == 255) {
                BFS(temp, Coordinate(i, j), 4, 128, 255);
            }
        }
    }
    out = temp;

    return *this;
}

Basic &Basic::unsharp_masking(double c) {
    Matrix<unsigned char> low_pass(this->image.rows, this->image.cols);
    low_pass_filter(low_pass, 2);

    Matrix<unsigned char> temp(this->image.rows, this->image.cols);
    for (int i = 0; i < this->image.size(); i++) {
        temp(i) = (c * this->image(i) - (1 - c) * low_pass(i)) / (2 * c - 1);
    }
    for (int i = 0; i < this->image.size(); i++) {
        this->image(i) = temp(i);
    }

    return *this;
}

Basic &Basic::unsharp_masking(Matrix<unsigned char> &out, double c) {
    Matrix<unsigned char> low_pass(this->image.rows, this->image.cols);
    low_pass_filter(low_pass, 2);

    Matrix<unsigned char> temp(this->image.rows, this->image.cols);
    for (int i = 0; i < this->image.size(); i++) {
        temp(i) = (c * this->image(i) - (1 - c) * low_pass(i)) / (2 * c - 1);
    }
    for (int i = 0; i < out.size(); i++) {
        out(i) = temp(i);
    }

    return *this;
}

Basic &Basic::Dilation(Matrix<unsigned char> &out, vector<bool> H) {
    Matrix<unsigned char> temp(this->image.rows + 2, this->image.cols + 2, 0);

    for (int i = 0, hi = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++, hi++) {
            if (H[hi] == 1) {
                for (int k = 0; k < this->image.rows; k++) {
                    for (int l = 0; l < this->image.cols; l++) {
                        temp(k + i, l + j) |= this->image(k, l);
                    }
                }
            }
        }
    }

    for (int i = 0; i < this->image.rows; i++) {
        for (int j = 0; j < this->image.cols; j++) {
            out(i, j) = temp(i + 1, j + 1);
        }
    }
    return *this;
}

Basic &Basic::Dilation(vector<bool> H) {
    Matrix<unsigned char> temp(this->image.rows + 2, this->image.cols + 2, 0);

    for (int i = 0, hi = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++, hi++) {
            if (H[hi] == 1) {
                for (int k = 0; k < this->image.rows; k++) {
                    for (int l = 0; l < this->image.cols; l++) {
                        temp(k + i, l + j) |= this->image(k, l);
                    }
                }
            }
        }
    }

    for (int i = 0; i < this->image.rows; i++) {
        for (int j = 0; j < this->image.cols; j++) {
            this->image(i, j) |= temp(i + 1, j + 1);
        }
    }
    return *this;
}

Basic &Basic::Erosion(Matrix<unsigned char> &out, vector<bool> H) {
    Matrix<unsigned char> temp(this->image.rows + 2, this->image.cols + 2, 255);

    for (int i = 0, hi = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++, hi++) {
            if (H[hi] == 1) {
                for (int k = 0; k < this->image.rows; k++) {
                    for (int l = 0; l < this->image.cols; l++) {
                        temp(k + i, l + j) &= this->image(k, l);
                    }
                }
            }
        }
    }

    for (int i = 0; i < this->image.rows; i++) {
        for (int j = 0; j < this->image.cols; j++) {
            out(i, j) = temp(i + 1, j + 1);
        }
    }
    return *this;
}

Basic &Basic::Erosion(vector<bool> H) {
    Matrix<unsigned char> temp(this->image.rows + 2, this->image.cols + 2, 255);

    for (int i = 0, hi = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++, hi++) {
            if (H[hi] == 1) {
                for (int k = 0; k < this->image.rows; k++) {
                    for (int l = 0; l < this->image.cols; l++) {
                        temp(k + i, l + j) &= this->image(k, l);
                    }
                }
            }
        }
    }

    for (int i = 0; i < this->image.rows; i++) {
        for (int j = 0; j < this->image.cols; j++) {
            this->image(i, j) &= temp(i + 1, j + 1);
        }
    }
    return *this;
}

Basic &Basic::boundary_extraction() {
    Matrix<unsigned char> temp(this->image.rows, this->image.cols);
    Erosion(temp, {1, 1, 1, 1, 1, 1, 1, 1, 1});
    this->image = this->image - temp;
    return *this;
}

Basic &Basic::connected_component_labeling() {
    srand(time(NULL));

    Matrix<unsigned char> temp(this->image);
    for (int i = 0; i < this->image.rows; i++) {
        for (int j = 0; j < this->image.cols; j++) {
            if (temp(i, j) == 255) {
                // make color range in [75, 180]
                unsigned char color = (rand() % (256 - 150)) + 75;
                BFS(temp, Coordinate(i, j), 8, 255, color);
            }
        }
    }

    this->image = temp;

    return *this;
}

void Basic::mark_conditional(Matrix<unsigned char> &out,
                             vector<vector<unsigned char>> &table) {
    for (int i = 0; i < this->image.rows; i++) {
        for (int j = 0; j < this->image.cols; j++) {
            vector<unsigned char> pixel_stack;
            for (int k = i - 1; k <= i + 1; k++) {
                int x = symmetry(k, this->image.rows);
                for (int l = j - 1; l <= j + 1; l++) {
                    int y = symmetry(l, this->image.cols);
                    pixel_stack.push_back(this->image(x, y));
                }
            }
            for (int it = 0; it < table.size(); it++) {
                if (table[it] == pixel_stack) {
                    out(i, j) = M;
                    break;
                }
            }
        }
    }
}

bool Basic::match_unconditional(vector<unsigned char> &pixel_stack,
                                vector<unsigned char> &pattern) {
    bool have_ab = false, have_c = false;
    bool a = false, b = false, c = false;
    for (int i = 0; i < pattern.size(); i++) {
        switch (pattern[i]) {
        case 0:
            if (pixel_stack[i] == M) {
                return false;
            }
            break;
        case Basic::M:
            if (pixel_stack[i] == 0) {
                return false;
            }
            break;
        case Basic::A:
            if (pixel_stack[i] == M) {
                a = true;
            } else {
                have_ab = true;
            }
            break;
        case Basic::B:
            if (pixel_stack[i] == M) {
                b = true;
            } else {
                have_ab = true;
            }
            break;
        case Basic::C:
            if (pixel_stack[i] == M) {
                c = true;
            } else {
                have_c = true;
            }
            break;
        case Basic::D:
            break;
        default:
            break;
        }
    }

    if (have_c == true) {
        return a || b || c;
    }
    if (have_ab == true) {
        return a || b;
    }
    return true;
}

void Basic::mark_unconditional(Matrix<unsigned char> &out,
                               vector<vector<unsigned char>> patterns) {
    Matrix<unsigned char> conditional(out);
    for (int i = 0; i < this->image.rows; i++) {
        for (int j = 0; j < this->image.cols; j++) {
            if (conditional(i, j) == 0) {
                continue;
            }
            vector<unsigned char> pixel_stack;
            for (int k = i - 1; k <= i + 1; k++) {
                int x = symmetry(k, this->image.rows);
                for (int l = j - 1; l <= j + 1; l++) {
                    int y = symmetry(l, this->image.cols);
                    pixel_stack.push_back(conditional(x, y));
                }
            }
            vector<vector<unsigned char>>::iterator it;
            for (it = patterns.begin(); it != patterns.end(); it++) {
                if (match_unconditional(pixel_stack, *it)) {
                    out(i, j) = 0;
                    break;
                }
            }
        }
    }
}
Basic &Basic::shrinking() {
    vector<vector<unsigned char>> table;
    vector<int> indeies = S_conditional_patterns_indeies;
    for (vector<int>::iterator it = indeies.begin(); it != indeies.end(); it++) {
        vector<vector<unsigned char>> patterns = this->conditional_patterns[*it];
        table.insert(table.end(), patterns.begin(), patterns.end());
    }

    size_t erasure_count;
    do {
        erasure_count = 0;
        Matrix<unsigned char> conditional(this->image.rows, this->image.cols);
        mark_conditional(conditional, table);
        mark_unconditional(conditional, ST_unconditional_patterns);
        for (int i = 0; i < this->image.size(); i++) {
            if (conditional(i) == M) {
                this->image(i) = 0;
                erasure_count++;
            }
        }
    } while (erasure_count > 0);

    return *this;
}
Basic &Basic::thinning() {
    vector<vector<unsigned char>> table;
    vector<int> indeies = T_conditional_patterns_indeies;
    for (vector<int>::iterator it = indeies.begin(); it != indeies.end(); it++) {
        vector<vector<unsigned char>> patterns = this->conditional_patterns[*it];
        table.insert(table.end(), patterns.begin(), patterns.end());
    }

    size_t erasure_count;
    do {
        erasure_count = 0;
        Matrix<unsigned char> conditional(this->image.rows, this->image.cols);
        mark_conditional(conditional, table);
        mark_unconditional(conditional, ST_unconditional_patterns);
        for (int i = 0; i < this->image.size(); i++) {
            if (conditional(i) == M) {
                this->image(i) = 0;
                erasure_count++;
            }
        }
    } while (erasure_count > 0);

    return *this;
}
Basic &Basic::skeletonizing() {
    vector<vector<unsigned char>> table;
    vector<int> indeies = K_conditional_patterns_indeies;
    for (vector<int>::iterator it = indeies.begin(); it != indeies.end(); it++) {
        vector<vector<unsigned char>> patterns = this->conditional_patterns[*it];
        table.insert(table.end(), patterns.begin(), patterns.end());
    }

    size_t erasure_count;
    do {
        erasure_count = 0;
        Matrix<unsigned char> conditional(this->image.rows, this->image.cols);
        mark_conditional(conditional, table);
        mark_unconditional(conditional, K_unconditional_patterns);
        for (int i = 0; i < this->image.size(); i++) {
            if (conditional(i) == M) {
                this->image(i) = 0;
                erasure_count++;
            }
        }
    } while (erasure_count > 0);

    return *this;
}

void Basic::convolution(Matrix<double> &out, vector<double> mask) {
    for (int i = 1; i < this->image.rows - 1; i++) {
        for (int j = 1; j < this->image.cols - 1; j++) {
            for (int k = i - 1, mi = 1; k <= i + 1; k++) {
                for (int l = j - 1; l <= j + 1; l++, mi++) {
                    out(i, j) += double(this->image(k, l)) * mask[mi];
                }
            }
            out(i, j) /= mask[0];
        }
    }
}

Basic &Basic::laws_method(vector<Matrix<double>> &T, int winsize) {
    vector<Matrix<double>> M(9);
    for (int i = 0; i < 9; i++) {
        M[i].resize(this->image.rows, this->image.cols, 0);
    }

    int half = winsize / 2;
    for (int m = 0; m < 9; m++) {
        convolution(M[m], laws_mask[m]);
        for (int i = half; i < this->image.rows - half; i++) {
            for (int j = half; j < this->image.cols - half; j++) {
                for (int k = i - half; k <= j + half; k++) {
                    for (int l = j - half; l <= j + half; l++) {
                        T[m](i, j) += pow(M[m](k, l), 2);
                    }
                }
            }
        }
    }
    return *this;
}

Basic &Basic::close(vector<bool> H) {
    vector<bool> H_r(9);
    for (int i = 0; i < H.size(); i++) {
        H_r[i] = !H[i];
    }

    this->Dilation(H).Erosion(H_r);
    return *this;
}

#endif
