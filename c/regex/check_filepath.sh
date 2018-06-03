 gcc -g -o check_filepath  check_filepath.c
 ./check_filepath 
 ./check_filepath ./
 ./check_filepath .//
 ./check_filepath .///
 ./check_filepath ./tian/
 ./check_filepath ./1/.2/x/.4/.5
 ./check_filepath ./1/.2/x/.4/.5  1
 ./check_filepath ./1/.2/x/.4/.5/ 1
 ./check_filepath ./1/.2/x/.4/.5/ 

