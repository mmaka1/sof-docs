.. _dbg-exceptions:

DSP Core Exceptions
###################


..
   DSP Core Exceptions
   *******************

   There is a mechanism in the DSP FW that records DSP core state as well as other
   information helpful for debug when a DSP exception is caught. FW notifies the
   host driver via IPC that DSP exception occurred. The data is stored in SRAM
   memory accessible via the memory window. The core enters infinite loop leaving
   that SRAM area powered so the driver may copy the dump asynchronously to  the
   host file system for further analysis and power off the core when done.

   Probes
   ******

   Probes is a mechanism to intercept in/out data interfaces of module instances
   and inject/eavesdrop data to/from those interfaces. An outgoing probe may be
   also used to transfer log traces data to the driver.

   Topology & Debug Info
   *********************

   A client application, such as FDK Debug Agent, may retrieve current DSP
   firmware and hardware configuration as well as topology data, recorded
   performance data, etc. directly from the DSP.


The host driver should react to the *Exception Caught* IPC notification by
reading the basic exception data recorded by the FW in the SRAM area exposed
via a memory window, as well as other available information, like the
unconsumed log buffers content.

Depending on the extensions of the exception recoding procedure, there may be
some other information available in log memory buffer, which follows unread log
entries. This is for example a crashed module's stack content.

.. graphviz:: images/exc-rec-data-in-log.dot

All the data may be stored by the driver in the local file system for offline
analysis of the cause.

.. TODO: make tags symbols linked to defs

While reading the log buffer FIFOs, the host driver should poll the write
pointers until the *End of Dump* (``LOGE_TAG_EOCD``) tag appears in the log
buffer as the DSP exception recorder may have much more data to flush which
does not fit into the space available at the beginning. So the DSP exception
recorder may actively follow the host reader with a new content in case there
is not enough space to dump all information at once.

If, for any reason, the host driver cannot search for tags in the log buffer
content, it may alternatively pool for the ``rec_state`` status in the
exception records being recorded. A client application may still check for data
completeness by checking for existence of the tags in the received dump.

Recording Exception Data
************************

.. uml:: images/exception-rec.pu
   :caption: Recording DSP Exception

Recording of exception data is done by the DSP core that originally received
the exception. But the IPC notification is sent to the host by the master core.
Once the basic exception record is stored in the FW Registers area, an IDC
notification is sent (asynchronously) to the master core by the core executing
the exception handler. Then the master core's IPC handler waits until uplink
IPC channel is emptied by the host driver and sends the *Exception Caught*
Notification. Now the IPC communication is stopped on the master core. Core
that executes exception handler goes on with recording additional data to the
log buffer FIFO.

Note that the master core may be in a bad state as well, and the IPC
notification may be lost, therefore the host driver should check for available
exceptions reported by FW while handling DSP communication timeouts etc.

Any data appended to the log buffers begins with regular ``log_entry`` headers,
so that log parsers are able to process that information.

The exception data recorder copies the data synchronously, polling host's read
pointer position and copying data when there is more space made available by
the host driver consuming the buffer content and advancing the read pointer.

Once all data is copied, *End of Dump* tag is written to the FIFO,
``rec_state`` is updated and the core enters infinite loop.

Note that the log entry preceding the exception data should not be corrupted
even if the crash happened in the FW Logger component if the latter is
implemented in exception safe way, i.e. the write pointer is increased in a
single operation for the entire log entry at the very end of the logging
routine.

Recording an exception by a one core is not synchronized with other cores,
except for IPC communication that is handled by the master core only to avoid
additional synchronization of access to the IPC uplink channel.

Since other active cores keep on running, they may also cause exceptions which
may be recorded independently into their dedicated entries in the exception
record array). But always only one notification is sent to the host as the
entire IPC communication is blocked right after sending the notification.

The driver should wait until there is at least one complete exception record
available plus additional data flushed into the log FIFO. It may examine state
of other core's exception records and attempt to dump their data as well,
however usually the first one is the most interesting for analysis. Note that
DSP cores may crash completely while attempting to dump the exception data
leaving the exception records and/or additional data incomplete.

.. uml:: images/exception-rec-state.pu
   :caption: Exception Record States

In order to keep the exception recorder routine simple, pointers to all
information required to dump additional data associated with the failed
component device must be available inside the execution context record
accessible via the thread pointer register of the DSP core:

- component device id,
- current stack base address and size.

All information is updated on each context switch.

Reference
*********

.. TODO: to be moved to the sof sources.

.. note:: To be moved to the sof sources and ref'ed to dox output.

.. literalinclude:: exc_rec.h
   :language: c
