#include <sys/types.h>
#include <grp.h>

/*
 *  返回struct groub结构，包含了组相关的信息
 */
struct group *getgrnam(const char *name);
struct group *getgrgid(gid_t gid);

int getgrnam_r(const char *name, struct group *grp,
                char *buf, size_t buflen, struct group **result);
int getgrgid_r(gid_t gid, struct group *grp,
                char *buf, size_t buflen, struct group **result);

