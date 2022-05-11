#include <lib.h>
#include <minix/rs.h>

int get_pm_endpt(endpoint_t *pt) {
        return minix_rs_lookup("pm", pt);
}

int printmessage(void) {
        endpoint_t pm_pt;
        message m;
        if (get_pm_endpt(&pm_pt) != 0) {
                errno = ENOSYS;

                return -1;
        }

        _syscall(pm_pt, PM_GETLCAPID, &m);

	return m.m1_i3;
}
