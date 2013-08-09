
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

First of all, flange executes two commands. In assuming that the first command
is "command A", and that the second command is "command B", flange connects
STDIN of command A to STDOUT of command B. flange also connects STDIN of command
B to STDOUT of command A. Command A and command B can communicate by
STDIN/STDOUT.

The objective of flange is avoiding the work to implement code for making a
connection. Developers can use ssh(1) to make a connection. They do not need to
include code to connect in both of command A and command B. All they need is
just like::

    flange "foobarbazquux" "ssh hostname hogehoge"

The above one command connects a process of foobarbazquux with that of hogehoge
in a remote machine of hostname through ssh.

.. vim: tabstop=4 shiftwidth=4 expandtab softtabstop=4 filetype=rst
