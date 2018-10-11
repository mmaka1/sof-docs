.. _dbg-probes:

Probes
######

Configuration
*************

Initial Parameters
==================

When probe service is activated, it must be provided with the address of the
probe capture DMA. On platforms with HD/A DMA available, this is one of the
Host Input HD/A DMA gateways id.

The preferred size of the DMA buffer allocated by the DSP FW should be
specified as well.

Run-time Parameters
===================

* Injection Probe DMA (RW)
* Injection Probe DMA Detach (W)
* Probe Points (RW)
* Disconnect Probe Points (W)

Injection Probe DMA
-------------------

Driver writes this parameter to associate host output DMAs as injection probes
with the Probe module.

Driver may read this parameter to obtain the list of host output DMAs currently
associated with the Probe module.

Payload: ``struct probe_dma_array``.

Injection Probe DMA Detach
--------------------------

.. note:: Copied exactly, but reduction to a single *Injection Probe DMA*
   could simplify a bit.

Driver sends this configuration parameter to detach one or more probe DMAs from
Probe module.

Payload: ``struct probe_dma_id_array``.

Probe Points
------------

Driver writes this parameter to create probe points.

Driver may read this parameter to obtain the list of currently created probe
points.

Remarks:

* All probes created by a single request are synchronously started at the same
  system tick by the FW.
* A probe point is automatically deleted once its target device is deleted.

Payload: ``struct probe_point_array``.

Disconnect Probe Points
-----------------------

Driver writes this parameter to disconnect one or more probe points.

Payload: ``struct probe_point_id_array``.

Probe Data Stream
*****************

Extraction Data Format
======================

Since a single extraction probe DMA is used to transfer data from multiple
probe points, the data is packetized where driver may expect that packets
coming from different probe points are interleaved.

Each pocket begins with the ``struct probe_packet_header``, followed by a byte
array of data and 64-bit checksum.

Injection Data Format
=====================

The data being injected is a pure data stream, without any headers. It must be
formatted accordingly to the format of the input/output pin or internal queue
of the target module instance.

Reference
*********

.. TODO: to be moved to the sof sources.

.. note:: To be moved to the sof sources and ref'ed to dox output.

.. literalinclude:: probes.h
   :language: c
