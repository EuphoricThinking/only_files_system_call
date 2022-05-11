#include <lib.h>
#include <minix/rs.h>
#include <stdio.h>

int get_pm_endpt(endpoint_t *pt) {
        return minix_rs_lookup("pm", pt);
}

pid_t getlcapid(pid_t pid1, pid_t pid2) {
        endpoint_t pm_pt;
        message m;
        m.m1_i1 = pid1;
        m.m1_i2 = pid2;
        
        if (get_pm_endpt(&pm_pt) != 0) {
                errno = ENOSYS;

                return -1;
        }

//        int res = _syscall(pm_pt, PM_GETLCAPID, &m);
//	printf("outside %d sys %d\n", m.m1_i3, res);
//	return m.m1_i3;
	return (_syscall(pm_pt, PM_GETLCAPID, &m));
}
