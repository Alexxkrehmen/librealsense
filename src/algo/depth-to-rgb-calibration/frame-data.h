// License: Apache 2.0. See LICENSE file in root directory.
// Copyright(c) 2020 Intel Corporation. All Rights Reserved.

#pragma once

#include <vector>
#include <map>
#include <types.h>

#include "calibration-types.h"


namespace librealsense {
namespace algo {
namespace depth_to_rgb_calibration {


    struct frame_data
    {
        size_t width;
        size_t height;
    };

    typedef uint16_t yuy_t;
    typedef uint8_t ir_t;
    typedef uint16_t z_t;

    struct ir_frame_data : frame_data
    {
        std::vector< ir_t > ir_frame;
        std::vector< double > ir_edges;
    };

    struct z_frame_data : frame_data
    {
        rs2_intrinsics_double intrinsics;
        float depth_units;

        std::vector< z_t > frame;
        std::vector<double> gradient_x;
        std::vector<double> gradient_y;
        std::vector<double> edges;
        std::vector<double> supressed_edges;                
        size_t n_strong_edges;
        std::vector<direction> directions;
        std::vector<double> subpixels_x;
        std::vector<double> subpixels_y;
        std::vector< uint16_t> closest;
        std::vector<double> weights;
        std::vector<double> direction_deg;
        std::vector<double3> vertices;

        // input validation
        std::vector<byte> section_map;
        bool is_edge_distributed;
        std::vector<double>sum_weights_per_section;
        std::vector<double> sum_weights_per_direction;
        double min_max_ratio;

        // output validation
        std::vector< double > cost_diff_per_section;
    };

    struct yuy2_frame_data : frame_data
    {
        std::vector< yuy_t > orig_frame;
        std::vector< yuy_t > prev_frame;
        std::vector<uint8_t> lum_frame;
        std::vector<uint8_t> prev_lum_frame;
        std::vector<double> yuy_diff;
        std::vector<uint8_t> dilated_image;
        std::vector<double> gaussian_filtered_image;
        std::vector<double> gaussian_diff_masked;
        std::vector<uint8_t> move_suspect;
        std::vector<double> edges;                          // W*H, pre-smearing
        std::vector<double> prev_edges;                     // W*H, for prev_frame
        std::vector<uint8_t> logic_edges;
        std::vector<uint8_t> prev_logic_edges;
        std::vector<double> edges_IDT;                      // W*H, smeared, for cost
        std::vector<double> edges_IDTx;                     // W*H, smeared, dedge/dx, for gradients
        std::vector<double> edges_IDTy;                     // W*H, smeared, dedge/dy, for gradients
        std::vector<unsigned char> section_map;
        bool is_edge_distributed;
        std::vector<double>sum_weights_per_section;
        double min_max_ratio;
    };

}  // librealsense::algo::depth_to_rgb_calibration
}  // librealsense::algo
}  // librealsense