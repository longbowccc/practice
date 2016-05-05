#include <stdio.h>
#include <sys/inotify.h>

#define BUF_LEN 1024

/*
 * test inode watch notify
 */
void tnotify() {
    printf("test inotify\n");
    int fd = inotify_init();
    int mask = IN_ACCESS | IN_MODIFY | IN_ATTRIB | IN_OPEN;
    int wd = inotify_add_watch(fd, "/opt/logs/higo/201604/06/pay_new.log", mask);
    char buf[BUF_LEN];
    size_t len = read(fd, buf, BUF_LEN);
    struct inotify_event* evt = (struct inotify_event*)buf;
    printf("evt->wd=%d, evt->mask=%d, evt->cookie=%d, evt->len=%d, evt->name=%s\n", evt->wd, evt->mask, evt->cookie, evt->len, evt->name);
}

int main(int argc, char* argv[]) {
    tnotify();
    return 0;
}
