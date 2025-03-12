#include "minitalk.h"

void handle_signal(int sig, siginfo_t *info, void *context)
{
    static char c;
    static int bit_count;
    ssize_t ret;

    c = 0;
    bit_count = 0;
    (void)context;
    if (sig == SIGUSR1)
        c |= (1 << (7 - bit_count));
    bit_count++;
    if (bit_count == 8)
    {
        if (c == '\0')
            kill(info->si_pid, SIGUSR1);
        ret = write(1, &c, 1);
        if (ret == -1)
        {
            ft_printf("Error: write failed\n");
            exit(1);
        }
        c = 0;
        bit_count = 0;
    }
}

int main(void)
{
    struct sigaction sa;

    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = handle_signal;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);

    ft_printf("Server PID: %d\n", getpid());

    while (1)
        pause();

    return 0;
}

