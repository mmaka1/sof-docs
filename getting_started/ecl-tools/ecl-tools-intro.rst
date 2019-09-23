.. _ecl_tools_intro:

Overview
########

There is a set of SOF development tools, provided as plug-ins for the Eclipse
IDE.

.. uml:: images/plugins-overview.pu

**core** : basic common features:

- SOF nature for the projects to be recognized by other parts,
- Remote (SSH) connection management, remote commands file transfer,
- Lightweight infrastructure for binary file parsing and bindings.

**ui** : UI elements for *core*:

- SOF Project wizard,
- Tree viewer for binary file bindings,
- SOF Logger output view with navigable locations,
- Linux dmesg output view,
- Downloading topologies and SOF binaries from remote machine,
- Common elements for graphs: editor elements, zest x-y layout, ...

**fw** : SOF binary image tools:

- Binding for SOF image,
- SOF memory map model.

**fw.ui** : UI elements for *fw*:

- SOF binary graph editor displaying the structure of binary and memory map,
- Outline content provider.

**topo.ui** : UI elements for \*Topology graphs:

- Editor and actions: new node, delete node, connect nodes, serialize graph, ...
- Outline content provider,
- Properties provider,
- Extension point and interface for topologies.

**alsa.topo** : Alsa tools and topology for *topo.ui*:

- Binding for *tplg* files,
- Visualization of parsed *tplg* as *topo.ui* extension,
- Topology serialization to *conf* files.

Plug-ins Required for ...
*************************

Deploying and Downloading SOF Binaries
======================================

... as well as displaying logs and dmesg from the target machine:

.. uml:: images/plugins-deps-basic.pu

All the above plus ...

Visualizing SOF Binaries and Memory Maps
========================================

.. uml:: images/plugins-deps-fw-bin.pu

Editing Alsa Topology for SOF
=============================

.. uml:: images/plugins-deps-alsa-topo.pu

Running a Plug-in for Another Topology
======================================

.. uml:: images/plugins-deps-new-topo.pu

.. uml:: images/plugins-deps-new-topo-if.pu
