/*
 * Copyright (c) 2018, Intel Corporation
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

#ifndef __INCLUDE_EXC_REC__
#define __INCLUDE_EXC_REC__

/**
 * \brief Parameters of a single DMA channel associated with the Probe service.
 */
struct probe_dma_attribs {
	uint32_t stream_tag;       /**< id of dma */
	uint32_t dma_buffer_size;  /**< preferred size of the buffer (in bytes) */
};

/**
 * \brief Array of DMA channel parameters.
 */
struct probe_dma_array {
	uint32_t pda_count;               /**< number of items in dma[] */
	struct probe_dma_attribs dma[0];  /**< channel attributes */
};

/**
 * \brief Array of DMA channel ids.
 */
struct probe_dma_id_array {
	uint32_t pd_count;      /**< number of items in stream_tag[] */
	uint32_t stream_tag[0]; /**< channels */
};

#define PROBE_POINT_INPUT		0 /**< input (source) */
#define PROBE_POINT_OUTPUT		1 /**< output (sink) */
#define PROBE_POINT_INTERNAL		2 /**< internal */

/**
 * \brief Probe point id.
 *
 * type is set to one of PROBE_POINT_INPUT, PROBE_POINT_OUTPUT,
 * PROBE_POINT_INTERNAL.
 *
 * index is a 0-based index of the target point, e.g.
 * {PROBE_POINT_INPUT, 0} - firts source buffer,
 * {PROBE_POINT_OUTPUT, 1} - second sink buffer.
 */
struct probe_point_id {
	uint32_t component_id : 16; /**< id of target component */
	uint32_t device_id : 8;     /**< id of target device */
	uint32_t type : 2;          /**< type */
	uint32_t index : 6;         /**< index */
};

#define PROBE_POINT_EXTRACT		0 /**< Extraction probe point */
#define PROBE_POINT_INJECT		1 /**< Injection probe point */
#define PROBE_POINT_INJECT_REEXTRACT	2 /**< Injection & re-extraction */

/**
 * \brief Probe point attributes.
 *
 * purpose is set to one of PROBE_POINT_EXTRACT, PROBE_POINT_INJECT,
   PROBE_POINT_INJECT_REEXTRACT.
 */
struct probe_point_attribs {
	struct probe_point_id id; /**< id */
	uint32_t purpose;         /**< purpose */
	uint32_t stream_tag;      /**< channel */
};

/**
 * \brief Array of probe point attributes.
 */
struct probe_point_array {
	uint32_t ppa_count;                /**< number of items in ppa[] */
	struct probe_point_attribs ppa[0]; /**< pp attributes */
};

/**
 * \brief Array of probe point ids.
 */
struct probe_point_id_array {
	uint32_t pp_count;            /**< number of items in pp[] */
	struct probe_point_id pp[0];  /**< probe point ids */
};

#define PROBE_PACKET_SYNC_WORD 0xBABEBEBA   /**< probe packet sync word */

#define PROBE_PACKET_FMT_BASIC 		0   /**< basic data format */
#define PROBE_PACKET_FMT_STANDARD	1   /**< standard data format */

/**
 * \brief Basic data format.
 */
struct probe_data_fmt_basic {
	uint32_t fmt_type : 1; /**< set to PROBE_PACKET_FMT_BASIC */
	uint32_t basic_type_enc : 31; /**< basic type encoding TBD */
};

#define STD_TYPE_AUDIO_STR	0  /**< audio stream */
#define STD_TYPE_VIDEO_STR	1  /**< video stream */

#define AUDIO_FMT_PCM		0  /**< PCM format */
#define AUDIO_FMT_MP3		1  /**< MP3 format */

#define SR_8000HZ		0
#define SR_11025HZ		1
#define SR_12000HZ		2
#define SR_16000HZ		3
#define SR_22050HZ		4
#define SR_24000HZ		5
#define SR_32000HZ		6
#define SR_44100HZ		7
#define SR_48000HZ		8
#define SR_64000HZ		9
#define SR_88200HZ		10
#define SR_96000HZ		11
#define SR_128000HZ		12
#define SR_176400HZ		13
#define SR_192000HZ		14
#define SR_INVALID		15

#define SF_INTEGER		0
#define SF_FLOAT32		1

#define SE_LITTLE		0
#define SE_BIG			1

#define INT_CHANNEL		0
#define INT_SAMPLE		1

/**
 * \brief Standard data format.
 *
 * sample_size and container_size are expressed in bytes and are 0-based.
 */
struct probe_data_fmt_standard {
	uint32_t fmt_type : 1;       /**< set to PROBE_PACKET_FMT_STANDARD */
	uint32_t standard_type : 4;  /**< stream type, STD_TYPE_... */
	uint32_t audio_fmt :4;       /**< audio encoding type, AUDIO_FMT_... */
	uint32_t sample_rate :4;     /**< sample rate, SR_... */
	uint32_t nb_channels : 5;    /**< channel count, 0-based */
	uint32_t sample_size : 2;    /**< sample size */
	uint32_t container_size : 2; /**< container size */
	uint32_t sample_fmt : 1;     /**< sample format, SF_... */
	uint32_t sample_end : 1;     /**< sample endianess, SE_... */
	uint32_t interleaving_st :1; /**< interleaving, INT_... */
	uint32_t rsvd : 7;
};

/**
 * \brief Probe packet header.
 *
 * probe_data_format is set to one of probe_data_fmt_...
 *
 * timestamp is translated to the host time domain (see logging).
 */
struct probe_packet_header {
	uint32_t sync_word;              /**< set to PROBE_PACKET_SYNC_WORD */
	struct probe_point_id probe_id;  /**< probe point id */
	uint32_t probe_data_format;      /**< data format */
	uint32_t timestamp_low;          /**< low dword of timestamp */
	uint32_t timestamp_high;         /**< high dword of timestamp */
	uint32_t data_size;              /**< size of data (in bytes) */
};

#endif //#ifndef __INCLUDE_EXC_REC__
