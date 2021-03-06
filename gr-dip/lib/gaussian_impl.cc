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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "gaussian_impl.h"

namespace gr {
  namespace dip {

    gaussian::sptr
    gaussian::make(float sigma, int n)
    {
      return gnuradio::get_initial_sptr
        (new gaussian_impl(sigma, n));
    }

    /*
     * The private constructor
     */
    gaussian_impl::gaussian_impl(float sigma, int n)
      : gr::sync_block("gaussian",
                       gr::io_signature::make(1, 1, sizeof(cv::Mat)),
                       gr::io_signature::make(1, 1, sizeof(cv::Mat))),
      d_sigma(sigma), d_sent(false)
    {
      d_n = cv::Size(n, n);
    }

    /*
     * Our virtual destructor.
     */
    gaussian_impl::~gaussian_impl()
    {
      d_img.release();
      d_result.release();
    }

    int
    gaussian_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const cv::Mat *in = (const cv::Mat *) input_items[0];
      cv::Mat *out = (cv::Mat *) output_items[0];
      memcpy(&d_img, in, sizeof(d_img));

      if(d_img.empty())
        {
          std::cout << "Received empty image\n";
          return 1;
        }
      if(!d_img.empty() && !d_sent)
        {
          d_sent = true;

          // Do <+signal processing+>
          cv::GaussianBlur(d_img, d_result, d_n, d_sigma);

          // send to buffer
          memcpy(out, &d_result, sizeof(d_result));

          // Tell runtime system how many input items we consumed on
          // each input stream.
          consume_each (noutput_items);
        }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace dip */
} /* namespace gr */
