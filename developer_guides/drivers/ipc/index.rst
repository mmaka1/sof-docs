.. _ipc-drivers:

IPC Drivers
###########

cAVS (1.5) Implementation
*************************

Host IPC registers do not use sideband format.

.. uml:: images/cavs-15-ipc-int-handler.pu
   :caption: (1.5) IPC Driver: interrupt handler

.. uml:: images/cavs-15-ipc-task.pu
   :caption: (1.5) IPC Task: request processing

cAVS (1.8) Implementation
*************************

Host IPC registers use sideband format.

.. uml:: images/cavs-18-ipc-int-handler.pu
   :caption: (1.8) IPC Driver: interrupt handler

.. uml:: images/cavs-18-ipc-task.pu
   :caption: (1.8) IPC Task: request processing
