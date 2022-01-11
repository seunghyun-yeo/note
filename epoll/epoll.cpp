#include <iostream>
#include <sys/epoll.h>
#include <sys/signalfd.h>
#include <signal.h>

using namespace std;

int main()
{
    //structure for epoll
    struct epoll_event event, ev;
    int fd = 0, ret = 0, epoll_fd = 0;

    //structure for signalfd
    sigset_t mask;

    //signal setting
    sigemptyset(&mask);
    sigaddset(&mask, SIGUSR1);
    fd=signalfd(-1, &mask,0 );
    //epoll setting
    epoll_fd = epoll_create1(0);
    ev.events = EPOLLIN;
    ev.data.fd = fd;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, &ev);
    cout << "waiting for epoll\n";
    epoll_wait(epoll_fd,&event,1,-1);
    return 0;
}