#ifndef GO_AI_CONVOLUTION_H
#define GO_AI_CONVOLUTION_H

#include <vector>
#include <algorithm>
#include "Go.h"
#include "C:/Users/29753/Desktop/External_Library/eigen/Eigen/Core"

using namespace std;

/*
 *  Convolution
 */
namespace GoAI {

/*
 *  Img2Col convolutional algorithm
 */
void img2col(int kernelSize, int channels, vector<float>& in, vector<float>& out) {
    if (kernelSize == 1) {
        copy(begin(in), begin(in) + channels * BOARDNUM * sizeof(float), begin(out));
        return;
    }
    
    const int 
        h = BOARDSIZE, 
        w = BOARDSIZE,
        pad = (kernelSize / 2),
        out_h = h + 2 * pad - kernelSize + 1,
        out_w = w + 2 * pad - kernelSize + 1;

    float* data_im  = in.data(),
         * data_col = out.data();

    for (int c = channels; c--; data_im += BOARDNUM) {
        for (int k_r = 0; k_r < kernelSize; k_r++) {
            for (int k_c = 0; k_c < kernelSize; k_c++) {

                int i_r = -pad + k_r;

                for (int o_r = out_h; o_r > 0; o_r--) {
                    if (i_r < h) {

                        int in_col = -pad + k_c;

                        for (int o_c = out_w; o_c > 0; o_c--) {
                            if (in_col < w)
                                *(data_col++) = data_im[i_r * w + in_col];
                            else
                                *(data_col++) = 0;
                            in_col++;
                        }
                    }
                    else 
                        for (int o_c = out_w; o_c > 0; o_c--)
                            *(data_col++) = 0;
                    i_r++;
                }
            }
        }
    }
}

void convolve_img2col(int w, int h, int inC, int outC,
    int kernelSize, int padding, int stride,
    vector<float>& in,
    vector<float>& weights,
    vector<float>& biases,
    vector<float>& out) {

    // parameter
    const int 
        c = weights.size() / (biases.size() * kernelSize * kernelSize),
        outputs = 0;

    // kernel
    vector<float> col(kernelSize * kernelSize * inC * w * h);
    img2col(kernelSize, c, in, col);

    auto C_mat = Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic>>(out.data(), BOARDNUM, outputs);
    C_mat.noalias() =
        Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic>>(col.data(), BOARDNUM, kernelSize * kernelSize * inC) *
        Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic>>(weights.data(), kernelSize * kernelSize * inC, outputs);

    // biases
    for (int o = 0; o < outputs; o++)
        for (int b = 0; b < BOARDNUM; b++)
            out[(o * BOARDNUM) + b] += biases[o];
}



/*
 *  winograd convolutional algorithm
 */

 // Winograd filter transformation changes 3x3 filters to M + 3 - 1
#define WINOGRAD_M      4
#define WINOGRAD_ALPHA  (WINOGRAD_M + 3 - 1)
#define WINOGRAD_WTILES (BOARDSIZE / WINOGRAD_M + (BOARDSIZE % WINOGRAD_M != 0))
#define WINOGRAD_TILE   (WINOGRAD_ALPHA * WINOGRAD_ALPHA)
#define WINOGRAD_P      (WINOGRAD_WTILES * WINOGRAD_WTILES)
#define SQRT2           1.4142135623730951f


inline void winograd_transform_in(vector<float>& in, 
	                              vector<float>& V, const int C) {
    constexpr auto W = BOARDSIZE;
    constexpr auto H = BOARDSIZE;
    constexpr auto WTILES = WINOGRAD_WTILES;
    constexpr auto P = WINOGRAD_P;
    constexpr auto Wpad = 2 + WINOGRAD_M * WTILES;
    constexpr auto buffersize = 32;

    array<array<float, Wpad>, Wpad> in_pad{ {{0.0f}} };
    array<float, buffersize* WINOGRAD_ALPHA* WINOGRAD_ALPHA> buffer;
    auto buffer_offset = 0;
    auto buffer_entries = 0;

    const auto multiply_bt = [](float& o0, float& o1, float& o2,
                                float& o3, float& o4, float& o5,
                                const float i0, const float i1, const float i2,
                                const float i3, const float i4, const float i5) {

            auto i3m1 = i1 * -SQRT2 + i3 * (SQRT2 / 2.0f);
            auto i4m2 = i2 * -2.0f + i4 * 1.0f;
            auto i3m1_2 = i3 * (SQRT2)+i1 * (-SQRT2 / 2.0f);
            auto i4m2_2 = i2 * (-1.0f / 2.0f) + i4;

            o0 = i0 + i2 * (-5.0f / 2.0f) + i4;
            o1 =  i3m1 + i4m2;
            o2 = -i3m1 + i4m2;
            o3 =  i3m1_2 + i4m2_2;
            o4 = -i3m1_2 + i4m2_2;
            o5 = i1 + i3 * (-5.0f / 2.0f) + i5;
    };

    for (auto ch = 0; ch < C; ch++) {
        for (auto yin = 0; yin < H; yin++) 
            for (auto xin = 0; xin < W; xin++) 
                in_pad[yin + 1][xin + 1] = in[ch * (W * H) + yin * W + xin];

        for (auto block_y = 0; block_y < WTILES; block_y++) {
            // Tiles overlap by 2
            const auto yin = WINOGRAD_M * block_y;
            for (auto block_x = 0; block_x < WTILES; block_x++) {
                const auto xin = WINOGRAD_M * block_x;

#define DECL_T1(XX)                                                            \
    float T1_##XX##_0, T1_##XX##_1, T1_##XX##_2, T1_##XX##_3, T1_##XX##_4,     \
        T1_##XX##_5;
                DECL_T1(0)
                DECL_T1(1)
                DECL_T1(2)
                DECL_T1(3)
                DECL_T1(4)
                DECL_T1(5)

                    // Calculates transpose(B).x.B
#define MULTIPLY_BT(XX)                                                        \
    multiply_bt(T1_0_##XX, T1_1_##XX, T1_2_##XX, T1_3_##XX, T1_4_##XX,         \
                T1_5_##XX,                                                     \
                in_pad[yin + 0][xin + XX],                                     \
                in_pad[yin + 1][xin + XX],                                     \
                in_pad[yin + 2][xin + XX],                                     \
                in_pad[yin + 3][xin + XX],                                     \
                in_pad[yin + 4][xin + XX],                                     \
                in_pad[yin + 5][xin + XX]);
                MULTIPLY_BT(0)
                MULTIPLY_BT(1)
                MULTIPLY_BT(2)
                MULTIPLY_BT(3)
                MULTIPLY_BT(4)
                MULTIPLY_BT(5)

#define MULTIPLY_B(XX)                                                         \
    multiply_bt(                                                               \
        buffer[buffersize * (XX * WINOGRAD_ALPHA + 0) + buffer_entries],       \
        buffer[buffersize * (XX * WINOGRAD_ALPHA + 1) + buffer_entries],       \
        buffer[buffersize * (XX * WINOGRAD_ALPHA + 2) + buffer_entries],       \
        buffer[buffersize * (XX * WINOGRAD_ALPHA + 3) + buffer_entries],       \
        buffer[buffersize * (XX * WINOGRAD_ALPHA + 4) + buffer_entries],       \
        buffer[buffersize * (XX * WINOGRAD_ALPHA + 5) + buffer_entries],       \
        T1_##XX##_0, T1_##XX##_1, T1_##XX##_2, T1_##XX##_3, T1_##XX##_4,       \
        T1_##XX##_5);
                    MULTIPLY_B(0)
                    MULTIPLY_B(1)
                    MULTIPLY_B(2)
                    MULTIPLY_B(3)
                    MULTIPLY_B(4)
                    MULTIPLY_B(5)

                    if (buffer_entries == 0) {
                        buffer_offset = ch * P + block_y * WTILES + block_x;
                    }
                buffer_entries++;

                if (buffer_entries >= buffersize
                    || (ch == C - 1 && block_x == WTILES - 1
                        && block_y == WTILES - 1)) {

                    for (auto i = 0; i < WINOGRAD_ALPHA * WINOGRAD_ALPHA; i++) {
                        for (auto entry = 0; entry < buffer_entries; entry++) {
                            V[i * C * P + buffer_offset + entry] =
                                buffer[i * buffersize + entry];
                        }
                    }
                    buffer_entries = 0;
                }
            }
        }
    }
}

void winograd_sgemm(vector<float>& U,
                    vector<float>& V,
                    vector<float>& M,
                    const int C, const int K) {

    auto P = WINOGRAD_P;

    for (auto b = 0; b < WINOGRAD_TILE; b++) {
        const int
            offset_u = b * K * C,
            offset_v = b * C * P,
            offset_m = b * K * P;

        auto C_mat = Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic>>(M.data() + offset_m, P, K);
        C_mat.noalias() =
            Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic>>(V.data() + offset_v, P, C) *
            Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic>>(U.data() + offset_u, K, C).transpose();

    }
}

void winograd_transform_out(vector<float>& M,
                            vector<float>& Y, const int K) {
    int W = BOARDSIZE,
        H = BOARDSIZE,
        WTILES = WINOGRAD_WTILES,
        P = WINOGRAD_P;

    // A^T ��
    const auto multiply_at = [](float& o0, float& o1, float& o2, float& o3,
                                const float i0, const float i1,
                                const float i2, const float i3,
                                const float i4, const float i5) {
            auto t1p2 = (i1 + i2) * (1.0f / 2.0f);
            auto t1m2 = (i1 - i2) * (SQRT2 / 4.0f);
            auto t3p4 = i3 + i4;
            auto t3m4 = (i3 - i4) * (SQRT2);

            o0 = i0 + t1p2 + t1p2 + t3p4;
            o1 = t1m2 + t1m2 + t3m4;
            o2 = t1p2 + t3p4 + t3p4;
            o3 = t1m2 + t3m4 + t3m4 + i5;
    };

    for (auto k = 0; k < K; k++) {
        for (auto block_x = 0; block_x < WTILES; block_x++) {
            const auto x = WINOGRAD_M * block_x;

            for (auto block_y = 0; block_y < WTILES; block_y++) {
                const auto 
                    y = WINOGRAD_M * block_y,
                    b = block_y * WTILES + block_x;

                array<array<float, WINOGRAD_ALPHA>, WINOGRAD_ALPHA> temp_m;
                array<array<float, WINOGRAD_ALPHA>, WINOGRAD_M> temp;
                array<array<float, WINOGRAD_M>, WINOGRAD_M> o;

                for (auto xi = 0; xi < WINOGRAD_ALPHA; xi++) 
                    for (auto nu = 0; nu < WINOGRAD_ALPHA; nu++) 
                        temp_m[xi][nu] = M[(xi * WINOGRAD_ALPHA + nu) * K * P + k * P + b];

                // Calculates transpose(A).temp_m.A
                for (auto j = 0; j < WINOGRAD_ALPHA; j++) 
                    multiply_at(temp[0][j], temp[1][j], temp[2][j], temp[3][j],
                                temp_m[0][j], temp_m[1][j], temp_m[2][j],
                                temp_m[3][j], temp_m[4][j], temp_m[5][j]);

                for (auto i = 0; i < WINOGRAD_M; i++) 
                    multiply_at(o[i][0], o[i][1], o[i][2], o[i][3],
                                temp[i][0], temp[i][1], temp[i][2],
                                temp[i][3], temp[i][4], temp[i][5]);

                const auto y_ind = k * H * W + y * W + x;

                for (auto i = 0; i < WINOGRAD_M; i++) 
                    for (auto j = 0; j < WINOGRAD_M; j++) 
                        if (y + i < H && x + j < W) 
                            Y[y_ind + i * W + j] = o[i][j];
            }
        }
    }
}

void convolve_3_winograd(int outs,
                         vector<float>& in,
                         vector<float>& U,
                         vector<float>& V,
                         vector<float>& M,
                         vector<float>& out) {

    int filter_len = WINOGRAD_ALPHA * WINOGRAD_ALPHA;
    const auto in_channels = U.size() / (outs * filter_len);

    winograd_transform_in(in, V, in_channels);
    winograd_sgemm(U, V, M, in_channels, outs);
    winograd_transform_out(M, out, outs);
}

}

#endif