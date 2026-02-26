#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int parse_int(const char *s, int *out) {
  int sign = 1;
  int i = 0;
  if (s[0] == '\0') return -1;
  if (s[0] == '-') { sign = -1; i = 1; }
  int val = 0;
  for (; s[i]; ++i) {
    if (s[i] < '0' || s[i] > '9') return -1;
    val = val * 10 + (s[i] - '0');
  }
  *out = val * sign;
  return 0;
}

int main(int argc, char *argv[]) {
  char buf[128];
  int pos = 0;
  int r;
  while (pos < (int)sizeof(buf) - 1) {
    r = read(0, buf + pos, 1);
    if (r < 0) {
      fprintf(2, "read error\n");
      exit(1);
    }
    if (r == 0) break;
    if (buf[pos] == '\n') { buf[pos] = '\0'; break; }
    pos += r;
  }
  buf[pos] = '\0';
  printf("|%s|\n", buf);
  if (pos == 0) {
    fprintf(2, "empty input\n");
    exit(1);
  }
  char *p = buf;
  while (*p == ' ') p++;
  char *sp = p;
  while (*sp && *sp != ' ') sp++;
  if (*sp == '\0') {
    fprintf(2, "expected two numbers separated by space\n");
    exit(1);
  }
  *sp = '\0';
  sp++;
  while (*sp == ' ') sp++;
  int a, b;
  if (parse_int(p, &a) < 0) { fprintf(2, "invalid first number\n"); exit(1); }
  if (parse_int(sp, &b) < 0) { fprintf(2, "invalid second number\n"); exit(1); }
  int ssum = a + b;
  printf("%d\n", ssum);
  exit(0);
}
