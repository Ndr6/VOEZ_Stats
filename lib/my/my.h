#ifndef GNL_H_
#define GNL_H_

#ifndef READ_SIZE
#define READ_SIZE (5)
#endif

int my_putstr(char const *str);

char *my_strcat(char *src, char *src2);
int check_bsn(char *str);
void save_state(char *buffer, char *state, int bsn, int ret);
int restore_state(char **str, char *state);
char *get_next_line(int fd);

#endif /*! GNL_H_*/
