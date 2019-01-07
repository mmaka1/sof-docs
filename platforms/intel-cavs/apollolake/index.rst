.. _platform-apollolake:

Intel Apollo Lake
#################

Intel Apollo Lake (APL) platform is built on cAVS 1.5 HW and uses Xtensa SMP
DSP architecture.

Power Management
****************

DSP Core clocks:

* 400 MHz (/1)
* 100 MHz (/4)

Clock gated in WAITI.

Memory clocks:

* HP memory - clocked by PLL /2
* LP memory - clocked by PLL /4

DMACs:

* dw-dma - clock (un)gated on demand
* hda-dma - clock (un)gated on demand

DAIs:

* ssp - clock (un)gated on demand
* dmic - clock (un)gated on demand
* hda - clock (un)gated on demand

Memory Map
**********

8000 0000h
   Address aliasing to A000 0000h - BFFF FFFFh range (non L1 cacheable)

9000 0000h
   L2 cache alias address (non L1 cacheable).
   HPSRAM alias 9E00 0000h.
   LPSRAM alias 9E80 0000h

A000 0000h
   L2 cacheable memory (L1 cacheable).
   Code/data in IMR accessed via L1 and L2 cache.

B000 0000h
   L2 uncacheable memory (L1 cacheable).
   Code/data in IMR accessed via L1 cache.

BE00 0000h
   L2 local HPSRAM (L1 cacheable). 8 * 64KB

BE80 0000h
   L2 local LPSRAM (L1 cacheable). 2 * 64KB

.. graphviz:: images/apl-memory.dot
   :caption: APL Memory Map
