
API For 3rd Party Components
############################

This section describes API for processing components implemented on top of SOF
infrastructure by 3rd party vendors.

.. note:: Open: is non-audio input/output also acceptable?

.. uml:: images/api-coe-fdk-diag.pu

A component instance is inserted into a pipeline to process input data into
the output data. In general there are three types of components, classified by
number of inputs and outputs:

. *Processor* which is typical processing component that has at least one
   input and at least one output.

. *Terminator* that has no output, consumes the data and provides an output in
   form of events rather than data output into a pipeline.

. *Generator* that begins a pipeline, generates the data internally and has no
   input (OPEN: what about IPC gateway equivalent).

A component may require arbitrary input/output frame size (number of samples
required for a single processing cycle).

Working Mode
************

A component may work in either:

- *NORMAL* mode which means regular processing.
- *BYPASS* mode when input is copied as is to the output.

Mode may be requested by any time by the application by sending IPC request to
the component. The IPC request results in a call to
``ProcessingModuleInterface::SetProcessingMode()`` method.

Initialization
**************

Note there is no dedicates initialization function, it is assumed that a
module receives series of ``SetConfiguration()`` calls with parameters sent
via IPC by the configurator running on the host

.. note::

   OPEN: how the parameters are stored on the host, retrieved by the driver
   and translated into series of IPC calls. + How it maps to alsa config,
   position of the component instance inserted there, should all parameters go
   there as tokens and be read in a generic way by the driver? it would mean
   they are appended to the *init instance* IPC call. What about parameters
   (BLOBs) that cannot fit into a single IPC request buffer?

.. note::

   OPEN: how the initial configuration is different from run-time parameters
   sent by the tuning application or something similar?
