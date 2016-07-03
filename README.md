web_link_timer
==============

Web links timed queue for Firefox on Windows.

Tested on Win7 with:
 - **MinGW v4.8**.
 - and also **Cygwin 2.5.1** with **Clang v3.7.1**.

This program is intended to open web pages during user-defined time.

Config file
___________

Link1;MINUTES:SECONDS
Link2;MINUTES:SECONDS
Link3;MINUTES:SECONDS
...
LinkN[;MINUTES:SECONDS]

Duration is not needed for the last link. 

.. code-block::

  https://github.com/broija/enum_bit_flags;15:03
  https://github.com/broija/subdetection;14:15
  https://github.com/broija/web_link_timer

Usage
_____

.. code-block:: sh

  web_link_timer.exe /PATH/TO/CONFIG/FILE.ini
