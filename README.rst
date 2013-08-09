
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

Usage
=====

The usage of flange is simple. flange accepts two arguments which are commands
to connect::

    $ flange "foo bar baz quux" "hoge fuga piyo"

If a command has more than one parameters, these must be quoted. In the above
example, flange executes the command of "foo" with the three arguments of "bar",
"baz" and "quux". Similaly, flange also executes the command of "hoge" whose
parameters are "fuga" and "piyo".

Actual applications using flange
================================

One example of applications using flange is `ubackup`_. ubackup is a backup tool
of using two executables -- ubackupee and ubackuper. The role of ubackupee is
sending file data to be backuped, and that of ubackuper is storing received
data. These two do not have functions to connect. It is a role of ssh(2). As a
result of this structure, both of a backuper machine and a backupee machine can
make connection to the other. For example, if you want to backup /etc in a local
machine to a remote machine directory such as /backup, you can do it with a
command of::

    $ flange "ubackupee /etc" "ssh example.com ubackuper /backup"

(ubackup prepared a wrapper for this command named as "ubackupme"). On the other
hand, if you want to backup /etc directory in a remote machine of example.com to
the directory of /backup in a local machine, the command for it is::

    $ flange "ubackuper /backup" "ssh example.com ubackupee /etc"

(ubackup also prepared a wrapper for this command named as "ubackupyou").

.. _ubackup: http://github.com/SumiTomohiko/ubackup

Anything else
=============

License
-------

This is open source software under the MIT license.

GitHub repository
-----------------

The source code repository of this project is hosted by `GitHub`_.

.. _GitHub: http://github.com/SumiTomohiko/flange

The author
----------

The author is `SumiTomohiko`_.

.. _SumiTomohiko: http://neko-daisuki.ddo.jp/~SumiTomohiko/index.html

.. vim: tabstop=4 shiftwidth=4 expandtab softtabstop=4 filetype=rst
