
flange
******

Overview
========

flange is a tiny tool for Unix to connect stdin/stdout of two processes. The
final form which flange makes is::

    +---------+                     +---------+
    |         |stdin<---\ /--->stdin|         |
    |command A|          X          |command B|
    |         |stdout---/ \---stdout|         |
    +---------+                     +---------+

.. vim: tabstop=4 shiftwidth=4 expandtab softtabstop=4 filetype=rst
