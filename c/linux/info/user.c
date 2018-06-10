#include<sys/types.h>
#include<pwd.h>
#include<stdio.h>
#include<unistd.h>

int main() {
    uid_t uid;
    gid_t gid;
    char *username = NULL;

    struct passwd *pw;
    uid = getuid();  // 启动程序的uid
    gid = getgid();
    username = getlogin(); // 当前登陆终端 name 与uid有可能不匹配
    printf("User is %s uid:%d gid=%d\n", username, uid, gid);

    pw = getpwuid(uid);
    printf("UID passwd entry: name=%s uid=%d gid=%d home=%s shell=%s\n", 
            pw->pw_name, pw->pw_uid, pw->pw_gid, pw->pw_dir, pw->pw_shell);
    pw = getpwnam(username);
    printf("Username=%s passwd entry: name=%s uid=%d gid=%d home=%s shell=%s\n", 
            username, pw->pw_name, pw->pw_uid, pw->pw_gid, pw->pw_dir, pw->pw_shell);

    username = "root";
    pw = getpwnam(username);
    printf("Username=%s passwd entry: name=%s uid=%d gid=%d home=%s shell=%s\n", 
            username, pw->pw_name, pw->pw_uid, pw->pw_gid, pw->pw_dir, pw->pw_shell);

    return 0;
}
