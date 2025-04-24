Overview
--------

The SimpleBLE project delivers enterprise-grade Bluetooth Low Energy (BLE) libraries
with a consistent cross-platform API. By abstracting platform-specific complexities,
developers can focus on building BLE applications rather than handling OS quirks. The
library supports full Central role functionality and preview Peripheral features, with
commercial licensing available for proprietary applications.

**NOTICE: Since January 20th 2025 the license terms of SimpleBLE have changed. Please make sure to read and understand the new licensing scheme.**

Key Features
^^^^^^^^^^^^

* **Cross-Platform**: Enterprise-grade support for Windows, macOS, Linux, iOS, and Android
* **Device Roles**: Full Central support, with Peripheral functionality in early preview
* **Easy Integration**: Clean, consistent API across all platforms
* **Multiple Language Bindings**: Production-ready bindings for C, C++, and Python, more coming soon
* **Commercial Ready**: Source-available commercial license for proprietary applications

Language Bindings
^^^^^^^^^^^^^^^^^

* **C/C++**: Core implementation with full platform support
* **Python (SimplePyBLE)**: Python bindings. See the `SimplePyBLE`_ PyPI page for more details.
* **Rust (SimpleRsBLE) - Alpha**: Rust bindings (under major refactor). See the `SimpleRsBLE`_ Crates.io page for more details.
* **Android (SimpleDroidBLE) - Alpha**: Android-only bindings (alpha).
* More languages coming soon!

Extension Libraries
^^^^^^^^^^^^^^^^^^^

* **SimpleBluez**: BlueZ abstraction layer over DBus
* **SimpleDBus**: DBus object hierarchy handler

Support & Resources
^^^^^^^^^^^^^^^^^^^^

We're here to help you succeed with SimpleBLE:

* **Documentation**: Visit our `ReadTheDocs`_ page for comprehensive guides
* **Commercial Support**: Check our `website`_ or `email us <mailto:contact@simpleble.org>`_ for licensing and professional services
* **Community**: Join our `Discord`_ server for discussions and help

Don't hesitate to reach out - we're happy to help!

Supported platforms
^^^^^^^^^^^^^^^^^^^

Windows
"""""""
* **Supported Versions:** Windows 10 and newer
* **Notes:**

  - WSL does not support Bluetooth.
  - Only a single adapter is supported by the OS backend.

Linux
"""""
* **Supported Distributions:** Ubuntu 20.04 and newer
* **Notes:**

  - While Ubuntu is our primary supported distribution, the software may work on other major distributions using Bluez as their Bluetooth backend.

MacOS
"""""
* **Supported Versions:** 10.15 (Catalina) and newer
* **Exceptions:** MacOS 12.0, 12.1, and 12.2 have a bug where the adapter won't return any peripherals after scanning.
* **Notes:**

  - Only a single adapter is supported by the OS backend.

iOS
"""
* **Supported Versions:** iOS 15.8 and newer
* **Notes:**

  - Older versions of iOS might work but haven't been formally tested.

Android
"""""""
* **Supported Versions:** API 31 and newer
* **Notes:**

  - Older APIs are missing certain features of the JVM API that are required by SimpleBLE
  - Removing bonds is not supported, as the public API does not provide a way to do this and some work is required to make it work using non-public APIs.
  - Address type is not supported, as this is only available on API 35 and newer.

.. Links

.. _website: https://simpleble.org
.. _SimplePyBLE: https://pypi.org/project/simplepyble/
.. _SimpleRsBLE: https://crates.io/crates/simplersble
.. _Discord: https://discord.gg/N9HqNEcvP3
.. _ReadTheDocs: https://simpleble.readthedocs.io/en/latest/

.. Other projects using SimpleBLE

.. _GDSimpleBLE: https://github.com/jferdelyi/GDSimpleBLE
.. _BrainFlow: https://github.com/brainflow-dev/brainflow
.. _InsideBlue: https://github.com/eriklins/InsideBlue-BLE-Tool
.. _NodeWebBluetooth: https://github.com/thegecko/webbluetooth
