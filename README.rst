web_link_timer
==============

Web links timed queue for Firefox on Windows.

Tested on Win7 with:
 - **MinGW v4.8**.
 - and also **Cygwin 2.5.1** with **Clang v3.7.1**.

This program is intended to trigger web page openings after user-defined durations.

Config file
___________

.. code::

  Link1;MINUTES:SECONDS
  Link2;MINUTES:SECONDS
  Link3;MINUTES:SECONDS
  ...
  LinkN[;MINUTES:SECONDS]

Duration is not needed for the last link. 

.. code::

  https://github.com/broija/enum_bit_flags;15:03
  https://github.com/broija/subdetection;14:15
  https://github.com/broija/web_link_timer

Usage
_____

.. code:: sh

  web_link_timer.exe /PATH/TO/CONFIG/FILE.ini
