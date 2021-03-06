/* -*- c++ -*- */
/*
 * Copyright 2018 <+YOU OR YOUR COMPANY+>.
 *
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifndef INCLUDED_DIP_THRESHOLD_IMPL_H
#define INCLUDED_DIP_THRESHOLD_IMPL_H

#include <dip/threshold.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

typedef enum
  {
    Binary,
    BinaryInv,
    ThresholdTrunc,
    Threshold2Zero,
    Threshold2ZeroInv
  } ThreshMethod;

namespace gr {
  namespace dip {

    class threshold_impl : public threshold
    {
     private:
      cv::Mat d_img;
      cv::Mat d_result;
      bool d_sent;
      unsigned char  d_thresh;
      ThreshMethod d_method;

     public:
      threshold_impl(unsigned char thresh, int method);
      ~threshold_impl();

      // Where all the action really happens
      int work(int noutput_items,
         gr_vector_const_void_star &input_items,
         gr_vector_void_star &output_items);
    };

  } // namespace dip
} // namespace gr

#endif /* INCLUDED_DIP_THRESHOLD_IMPL_H */
