.. _api-uapi-channel-mapping:

Channel Mapping
###############

Use: ALH aggregation, I2S aggregation, I2S TDM mode

.. note::

   The code example below is just a proposal, to be removed from the
   final doc once approved.

.. code:: c

   /*
    * Copyright (c) 2019, Intel Corporation
    * All rights reserved.
    *
    * Redistribution and use in source and binary forms, with or without
    * modification, are permitted provided that the following conditions are met:
    *   * Redistributions of source code must retain the above copyright
    *     notice, this list of conditions and the following disclaimer.
    *   * Redistributions in binary form must reproduce the above copyright
    *     notice, this list of conditions and the following disclaimer in the
    *     documentation and/or other materials provided with the distribution.
    *   * Neither the name of the Intel Corporation nor the
    *     names of its contributors may be used to endorse or promote products
    *     derived from this software without specific prior written permission.
    *
    * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
    * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
    * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
    * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
    * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
    * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
    * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
    * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
    * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
    * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
    * POSSIBILITY OF SUCH DAMAGE.
    */

   /**
    * \brief Channel map, specifies transformation of one-to-many or many-to-one.
    *
    * In case of one-to-many specifies how the output channels are computed out of
    * a single source channel,
    * in case of many-to-one specifies how a single target channel is computed
    * from a multichannel input stream.
    *
    * Channel index specifies position of the channel in the stream on the 'one'
    * side.
    *
    * Ext ID is the identifier of external part of the transformation. Depending
    * on the context, it may be pipeline ID, dai ID, ...
    *
    * Channel mask describes which channels are taken into account on the "many"
    * side. Bit[i] set to 1 means that i-th channel is used for computation
    * (either as source or as a target).
    *
    * Channel mask is followed by array of coefficients in Q2.30 format,
    * one per each channel set in the mask (left to right, LS bit set in the
    * mask corresponds to ch_coeffs[0]).
    */
   struct channel_map {
   	uint32_t ch_index;
   	uint32_t ext_id;
   	uint32_t ch_mask;
   	int32_t ch_coeffs[];
   };

   /**
    * \brief Complete map for each channel of a multichannel stream.
    *
    * num_ch_map Specifies number of items in the ch_map.
    * More than one transformation per a single channel is allowed (in case
    * multiple external entities are transformed).
    * A channel may be skiped in the transformation list, then it is filled
    * with 0's by the transformation function.
    */
   struct stream_map {
   	uint32_t num_ch_map;
   	struct channel_map ch_map[];
   };


I2S TDM Configuration
*********************

Let's consider an example stream where 0th channel goes to 4th TDM slot and 1st
channel goes to the 3rd TDM slot.

.. graphviz:: images/ch-mapping-tdm.dot
   :caption: TDM example

.. code:: c

   struct stream_map s_map = {
      .num_ch_map = 2,
      .ch_map[] = {
         {
            .ch_index = 0,
            .ext_id = -1, // not used
            .ch_mask = BIT(4),
            .ch_coeffs[] = {1}
         },
         {
            .ch_index = 1,
            .ext_id = -1,
            .ch_mask = BIT(3),
            .ch_coeffs[] = {1}
         }
      }
   };

ALH Aggregation
***************

Let's consider an example where 4 channel stream is transmitted to two ALH
DAIs, 0th channel and 2nd channel go to the first DAI (id 5) in reversed order
while 1-st channel and 3rd channel go to the second DAI (id 7).

.. graphviz:: images/ch-mapping-alh.dot
   :caption: ALH aggregation example

.. code:: c

   struct stream_map s_map = {
      .num_ch_map = 4,
      .ch_map[] = {
         {
            .ch_index = 0,
            .ext_id = 5,
            .ch_mask = BIT(1),
            .ch_coeffs[] = {1}
         },
         {
            .ch_index = 2,
            .ext_id = 5,
            .ch_mask = BIT(0),
            .ch_coeffs[] = {1}
         },
         {
            .ch_index = 1,
            .ext_id = 7,
            .ch_mask = BIT(0),
            .ch_coeffs[] = {1}
         },
         {
            .ch_index = 3,
            .ext_id = 7,
            .ch_mask = BIT(1),
            .ch_coeffs[] = {1}
         }
      }
   };

(DE)MUX
*******

Let's consider a complex example of two input pipelines being muxed into a
single three channel stream. The first input pipeline has four channels, the
second input one has two channels. There are some coefficients and mixing
(adding with saturation) used to produce the output.

.. graphviz:: images/ch-mapping-mux.dot
   :caption: MUX aggregation example

.. code:: c

   struct stream_map s_map = {
      .num_ch_map = 5,
      .ch_map[] = {
         {
            .ch_index = 0,
            .ext_id = 3,
            .ch_mask = BIT(2) + BIT(3),
            .ch_coeffs[]  = {.5, .5}
         },
         {
            .ch_index = 1,
            .ext_id = 3,
            .ch_mask = BIT(0),
            .ch_coeffs[] = {1}
         },
         {
            .ch_index = 2,
            .ext_id = 3,
            .ch_mask = BIT(1),
            .ch_coeffs[] = {1}
         },
         {
            .ch_index = 1,
            .ext_id = 5,
            .ch_mask = BIT(0),
            .ch_coeffs[] = {.3}
         },
         {
            .ch_index = 2,
            .ext_id = 5,
            .ch_mask = BIT(1),
            .ch_coeffs[] = {.4}
         }
      },
   };
