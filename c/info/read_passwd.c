#include<stdio.h>
#include<pwd.h>
#include<sys/types.h>

int main() {
    struct passwd *pw =NULL;
    puts("display passwd uid < 100 ============ ");
    pw = getpwent();
    while(pw && pw->pw_uid <100) {
        printf("UID passwd entry: name=%s uid=%d gid=%d home=%s shell=%s\n", 
                pw->pw_name, pw->pw_uid, pw->pw_gid, pw->pw_dir, pw->pw_shell);
        pw = getpwent();
    }
    
    puts("display next passwd ============ ");
    pw = getpwent();
    printf("UID passwd entry: name=%s uid=%d gid=%d home=%s shell=%s\n", 
            pw->pw_name, pw->pw_uid, pw->pw_gid, pw->pw_dir, pw->pw_shell);

    puts("display all passwd ============ ");
    setpwent();
    do {
        pw = getpwent();
        if(pw != NULL)
            printf("UID passwd entry: name=%s uid=%d gid=%d home=%s shell=%s\n", 
                    pw->pw_name, pw->pw_uid, pw->pw_gid, pw->pw_dir, pw->pw_shell);
    } while(pw);

    return 0;
}
