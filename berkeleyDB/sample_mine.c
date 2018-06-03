#include<db.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<pthread.h>

#define DATA_PATH "/home/hypertable/data/berkeleyDB/test"
#define DATABASE "pustian.db"

// mkdir -p "/home/hypertable/data/berkeleyDB/test" 
// 读写权限
// gcc -I/usr/local/BerkeleyDB.4.8/include/ -g -o sample_1 sample_1.c  -L/usr/local/BerkeleyDB.4.8/lib/ -ldb  -lpthread

typedef struct employee_rec {
    int id;
    char name[32];
    char addr[128];
    char birthday[9]; // yyyymmdd
} employee;

void fill_employee(employee *ptr_emp, int id, char *name, char *addr, char *birthday){
    if(NULL == ptr_emp || strlen(name) > 32 || strlen(addr) > 128 || strlen(birthday) > 9) {
        fprintf(stderr, "fill_employ input error\n");
    }
    memset(ptr_emp, 0, sizeof(employee));
    ptr_emp->id = id;
    memcpy(ptr_emp->name, name, strlen(name));
    memcpy(ptr_emp->addr, addr, strlen(addr));
    memcpy(ptr_emp->birthday, birthday, strlen(birthday));
}

int main(void) {
    int ret = -1;
    DB_ENV *ptr_db_env;

    // init environment 
    ret = db_env_create(&ptr_db_env, 0);
    if(ret) {
        perror("db_env_create error:");
        goto end;
    }
    // if environment not exist, create and initialize the in-memory cache and thread
    uint32_t flags = DB_CREATE |DB_INIT_MPOOL /* |DB_INIT_CDB |DB_THREAD*/ ;
    ret = ptr_db_env->open(ptr_db_env, DATA_PATH, flags, 0);
    if(ret) {
        perror("db_env_open error:");
        goto end;
    }

    // init db
    DB *ptr_db;
    ret = db_create(&ptr_db, ptr_db_env, 0);
    if(ret) {
        perror("db_create error:");
        goto end;
    }
    // open db
    flags = DB_CREATE /*|DB_THREAD*/;
    DBT key;
    DBT data;
    mode_t mode = 0644;
    ret = ptr_db->open(ptr_db, NULL, DATABASE, NULL, DB_BTREE, flags, mode);
    if(ret) {
        perror("db_open error:");
        goto end;
    }

    // write record; initialize DBT
    memset(&key, 0, sizeof(DBT));
    memset(&data, 0, sizeof(DBT));
    employee emp;
    int id = 0;
    char *name = "tianpusen";
    char *addr = "shanghai";
    char *birthday = "20180522";
    fill_employee(&emp, id, name, addr, birthday);

    key.data = &id;
    key.size = sizeof(int);
    data.data = &emp;
    data.size = sizeof(employee);

    ret = ptr_db->put(ptr_db, NULL, &key, &data, DB_NOOVERWRITE);
    if(ret) {
        perror("db_put error:");
        ptr_db->err(ptr_db, ret, "DB->put");
        goto end;
    } 
    // flush
    ptr_db->sync(ptr_db, 0);
    /// **********************************************

    // read record
    memset(&key, 0, sizeof(DBT) );
    memset(&data, 0, sizeof(DBT) );
    key.data = &id;
    key.size = sizeof(int);
    employee get_empl;
    data.data = &get_empl;
    data.size = sizeof(employee);

    ret = ptr_db->get(ptr_db, NULL, &key, &data, 0);
    if(ret) {
        perror("db_get error:");
        ptr_db->err(ptr_db, ret, "DB->get");
        goto end;
    }
    employee *ptr_employee = data.data;
    printf("id:%d, name:%s, addr:%s, birthday:%d\n",
            ptr_employee->id, ptr_employee->name, ptr_employee->addr, ptr_employee->birthday);

    printf("data.data:%p get_empl:%p\n", data.data, &get_empl);
    // del
    
end:
    if(ptr_db) {
       ptr_db->close(ptr_db, 0);
    }
    if(ptr_db_env) {
        ptr_db_env->close(ptr_db_env, 0);
    }
    return ret;
}
