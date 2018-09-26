
DAI Comp Driver
###############

Digital Audio Interface Component is a pipeline element responsible for
transferring data between the DSP memory and a peripheral device (codec).
It is attached to DAI instance and to a DMA instance.

Implements ``comp_driver`` interface.

dai_new()
*********

When a DAI component driver is being created, it calls ``dai_get()`` and
``dma_get()`` to obtain pointers to the requested DAI implementation and DMA
implementation.


.. uml:: images/comp-dai-new.pu

dai_params()
************

dai_drv -> dma : dma_channel_get()
dai_drv <-- dma

.. uml:: images/comp-dai-params.pu

The DMA channel is requested using ``stream_tag`` specified by the driver.

dai_prepare()
*************

.. uml:: images/comp-dai-prepare.pu

dai_comp_trigger()
******************

COMP_TRIGGER_START
   * Calls ``dai_pointer_init()`` to advance the local write pointer by one
     period in case of playback- is this giving one period buffer w/ zeroes?
   * ``dma_start()`` is called.
   * Trigger is passed to dai -> ``dai_trigger()`` is called.

dai_pointer_init()
******************

In case of playback, the local write pointer is advanced by one period
