#include <string>
#include <vector>

#include "matrix.h"

#ifndef __BASIC_H
#define __BASIC_H

using namespace std;

struct Coordinate {
    int x, y;
    Coordinate(int paramx, int paramy) : x(paramx), y(paramy) {}
};

class Basic {
  public:
    Matrix<unsigned char> origin;
    Matrix<unsigned char> image;

  public:
    static const vector<int> Prewitt_mask;
    static const vector<int> Sobel_mask;
    static const vector<int> four_neighbor_mask;
    static const vector<int> eight_neighbor_non_separable_mask;
    static const vector<int> eight_neighbor_separable_mask;
    static const vector<int> high_pass_filter_5;
    static const vector<int> high_pass_filter_9;

    // homework3
    // Digital Image processing, 3rd Edition, Table 14.3-1, pp.413,414
    // Shrink, Thin, and Skeletonize Conditional Mark Patterns [M = 1 if hit]
    // the value which represents black in the binary image
    static const unsigned char I = 255;
    static const vector<int> S_conditional_patterns_indeies;
    static const vector<int> T_conditional_patterns_indeies;
    static const vector<int> K_conditional_patterns_indeies;
    static const vector<vector<vector<unsigned char>>> conditional_patterns;

    // Digital Image processing, 3rd Edition, Table 14.3-I, p. 414
    // Shrink, Thin, and Skeletonize Unconditional Mark Patterns
    // P(M,M0,M1,M2,M3,M4,M5,M6,M7) = 1 if hit]

    // A ∪ B ∪ C = 1, A ∪ B = 1, D = 0 ∪ 1
    static const unsigned char M = 1;
    static const unsigned char A = 2;
    static const unsigned char B = 3;
    static const unsigned char C = 4;
    static const unsigned char D = 5;
    static const vector<vector<unsigned char>> ST_unconditional_patterns;
    static const vector<vector<unsigned char>> K_unconditional_patterns;
    static const vector<vector<double>> laws_mask;

  public:
    Basic();
    Basic(const char *filepath, unsigned height, unsigned width);
    Basic(unsigned height, unsigned width);

    int symmetry(int n, int bound);

  public:
    Basic &reset();
    Basic &output(const char *filepath);
    Basic &reverse();
    void BFS(Matrix<unsigned char> &out, Coordinate Coord, unsigned char neighbor_method,
             unsigned char target, unsigned char modify);

    // homework1
    Basic &horizontal_flipping();
    Basic &power_law(double p);
    Basic &intensity_dividing(unsigned d);
    Basic &global_equalize_hist();
    Basic &local_equalize_hist(unsigned window_size);
    Basic &low_pass_filter(double b);
    Basic &low_pass_filter(Matrix<unsigned char> &out, double b);
    Basic &high_pass_filter(int mask_num);
    Basic &high_pass_filter(Matrix<unsigned char> &out, int mask_num);
    Basic &outlier_detection(double e);
    Basic &median_filtering();
    double computer_mse(const vector<unsigned char> &a);
    double computer_psnr(const vector<unsigned char> &a);

    // homework2
    Basic &process_edge_detection_1st_order(int mask_k, int threshold);
    Basic &process_edge_detection_2nd_order(double gaussian_sigma, int threshold);
    Basic &process_edge_detection_canny(double gaussian_sigma, int low_threshold,
                                        int high_threshold);
    Basic &generate_gradient(Matrix<unsigned char> &magnitude,
                             Matrix<unsigned char> &orientation, vector<int> mask);
    Basic &generate_laplacian(Matrix<int> &out, const vector<int> &mask);
    Basic &generate_zero_crossing(Matrix<unsigned char> &out, Matrix<int> &laplacian,
                                  int threshold);
    Basic &generate_gaussian(Matrix<unsigned char> &out, double sigma);
    Basic &generate_gaussian_filter(vector<double> &filter, double sigma);
    Basic &generate_non_maximal_suppression(Matrix<unsigned char> &out,
                                            Matrix<unsigned char> &orientation);
    Basic &generate_connected_component(Matrix<unsigned char> &out);
    Basic &unsharp_masking(double c);
    Basic &unsharp_masking(Matrix<unsigned char> &out, double c);

    // homework3
    Basic &Dilation(Matrix<unsigned char> &out, vector<bool> H);
    Basic &Erosion(Matrix<unsigned char> &out, vector<bool> H);
    Basic &Dilation(vector<bool> H);
    Basic &Erosion(vector<bool> H);

    Basic &boundary_extraction();
    Basic &connected_component_labeling();
    void mark_conditional(Matrix<unsigned char> &out,
                          vector<vector<unsigned char>> &table);
    bool match_unconditional(vector<unsigned char> &pixel_stack,
                             vector<unsigned char> &pattern);
    void mark_unconditional(Matrix<unsigned char> &out,
                            vector<vector<unsigned char>> patterns);
    Basic &shrinking();
    Basic &thinning();
    Basic &skeletonizing();
    void convolution(Matrix<double> &out, vector<double> mask);
    Basic &laws_method(vector<Matrix<double>> &T, int winsize);

    Basic &close(vector<bool> H);
};

#include "basic.cpp"

#endif
