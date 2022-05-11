#include "pm.h"
#include "mproc.h"
#include <errno.h>

int find_depth(struct mproc current) {
	int parent = current.mp_parent;
	int depth = 0;

	while (current.mp_pid != mproc[parent].mp_pid) {
		current = mproc[parent];
		parent = current.mp_parent;
		depth++;
	}

	return depth;
}

void shorten(struct mproc given, int given_depth, int final_depth) {
	while (given_depth > final_depth) {
		given = mproc[given.mp_parent];
		given_depth--;
	}
}


pid_t find_lca(struct mproc proc1, struct mproc proc2) {
	while (mproc[proc1.mp_parent].mp_pid != mproc[proc2.mp_parent].mp_pid) {
		proc1 = mproc[proc1.mp_parent];
		proc2 = mproc[proc2.mp_parent];
	}

	return mproc[proc1.mp_parent].mp_pid;
}

int do_getlcapid(void) {
	struct mproc* proc1 = find_proc(m_in.m1_i1);

	m_in.m1_i3 = -1;
	if (!proc1) {
		return EINVAL;
	}

	struct mproc* proc2 = find_proc(m_in.m1_i2);
	if (!proc2) {
		return EINVAL;
	}

	int depth1 = find_depth(*proc1);
	if (depth1 == 0) {
		return ESRCH;
	}

	int depth2 = find_depth(*proc2);
	if (depth2 == 0) {
		return ESRCH;
	}

//	if (proc1->mp_pid == proc2->mp_pid) {
//		return mproc[proc1->mp_parent]->mp_pid;
//	}

	if (depth1 > depth2) {
		shorten(*proc1, depth1, depth2);
	} else if (depth2 > depth1) {
		shorten(*proc2, depth2, depth1);
	}

	m_in.m1_i3 = find_lca(*proc1, *proc2);

	return m_in.m1_i3;
}

