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

#define EXC_REC_VER_MAJOR	1  /**< Major version of exc rec structure */
#define EXC_REC_VER_MINOR	0  /**< Minor version of exc rec structure */

#define EXC_REC_UNAVAILABLE	0  /**< Exc rec state: unavailable */
#define EXC_REC_STARTED		1  /**< Exc rec state: started */
#define EXC_REC_DATA_DUMP	2  /**< Exc rec state: collecting data */
#define EXC_REC_COMPLETE	3  /**< Exc rec state: complete */

#define AREGS_COUNT		64 /**< Max number of aregs */

/**
 * \brief Exception Record.
 */
struct core_exception_record {
	uint32_t version;          /**< Version { 16-bit MAJOR, 16-bit MINOR } */
	uint32_t rsvd;             /**< reserved */
	uint64_t timestamp;        /**< Timestamp */
	uint32_t rec_state;        /**< State */
	uint32_t exec_ctx;         /**< Component's device id */
	uint32_t epc_1;            /**< EPC 1 */
	uint32_t eps_2;            /**< EPS 2 */
	uint32_t epc_2;            /**< EPC 2 */
	uint32_t depc;             /**< DEPC */
	uint32_t debugcause;       /**< DEBUGCAUSE */
	uint32_t exccause;         /**< EXCCAUSE */
	uint32_t excvaddr;         /**< EXCVADDR */
	uint32_t excsave;          /**< EXCSAVE */
	uint32_t interrupt;        /**< INTERRUPT */
	uint32_t ar[AREGS_COUNT];  /**< AR registers */
	uint32_t windowbase;       /**< WINDOWBASE */
	uint32_t windowstart;      /**< WINDOWSTART */
	uint32_t mem_epc[4];       /**< Mem around EPC */
	uint32_t rsvd2;            /**< reserved */
};

#endif //#ifndef __INCLUDE_EXC_REC__
