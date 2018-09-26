
Host Comp Driver
################

Host Component is a pipeline element responsible for transferring data between
the host memory and the DSP memory. It is attached to a DMA channel connected
to the host driver at the other end.

Data Structures
***************

.. uml:: images/comp-host-data.pu

Host Buffers
============

.. todo:: host buffer initialization and handling.

Operations
**********

Implements ``comp_driver`` interface.

The diagrams show interaction with the DMA package.

host_new()
==========

Memory for the component is allocated and the DMAC instance reference
is obtained.

.. note:: First element for host SGL is allocated here for any DMA

.. graphviz:: images/comp-host-new.dot

.. uml:: images/comp-host-new.pu

host_params()
=============

Configures the DMA parameters and descriptors for host buffer IO.

.. uml:: images/comp-host-params.pu

host_trigger()
==============

.. uml:: images/comp-host-trigger.pu

host_reset()
============

.. uml:: images/comp-host-reset.pu

host_copy()
===========

Copies and processes data from source to sink buffers.

.. todo:: calls host_gw_dma_update() when CONFIG_DMA_GW is set.

.. uml:: images/comp-host-copy.pu

host_free()
===========

Releases allocated resources (dma channel and memory).

.. uml:: images/comp-host-free.pu
