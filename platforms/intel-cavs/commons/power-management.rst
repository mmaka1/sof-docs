.. _platform-cavs-power-management:

Power Management
################

Mechanisms used on CAVS platforms to reduce amount of power consumed by the
DSP.

Platform Initialization
***********************

Power settings applied during platform initialization:

* Core 0 is powered on, other cores are power off.

* Memory clocks are programmed to maximum available frequencies.

* Idle power gating is activated for all cores.

* All DMACs not used so far, during the boot stage, stays power gated (turned
  on demand).

* All DAIs stays power gated (turned on demand).

Once the boot process is complete, the frequency of Core 0 clock should be
throttled down to the level sufficient for IPC handling.

DMAC and DAI Power Management
*****************************

DMAC and DAI power is turned on and off on demand. Unused devices stays powered
off. Device drivers' pm-runtime handlers take care of platform specific HW
programming sequences.

See also :ref:`drivers-probing-on-demand`.
