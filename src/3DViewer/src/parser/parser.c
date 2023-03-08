#include "../../include/viewer.h"

static int relevant_file(const char *s) {
  int i;

  i = strlen(s) - 4;
  return (s[i] == '.' && s[i + 1] == 'o' && s[i + 2] == 'b' && s[i + 3] == 'j');
}

static FILE *get_file(const char *s, t_viewer *viewer) {
  FILE *file;

  file = fopen(s, "r");
  if (!file) {
    viewer->filename = strdup("Can't open file");
    if (!viewer->filename) exit_message("Malloc error");
    return (NULL);
  }
  if (!relevant_file(s)) {
    fclose(file);
    viewer->filename = strdup("File is not in obj format");
    if (!viewer->filename) exit_message("Malloc error");
    return (NULL);
  }
  return (file);
}

int parse_values(int *max_point, char **line, t_viewer *viewer) {
  char **split_line;
  int status;

  split_line = ft_split((*line) + 2, ' ');
  if ((*line)[0] == 'v')
    status = parse_vertex(split_line, viewer);
  else
    status = parse_face(max_point, split_line, viewer);
  free(*line);
  clean_massive_2d(&split_line);
  return (status);
}

static int parse_file(int *max_point, FILE *file, t_viewer *viewer) {
  char *line;
  size_t len;

  line = NULL;
  len = 0;
  errno = 0;
  if (getline(&line, &len, file) == -1) {
    free(line);
    if (errno) {
      return (-1);
    }
    return (1);
  }
  if (len > 2) {
    if ((line[0] == 'v' || line[0] == 'f') && line[1] == ' ')
      return (parse_values(max_point, &line, viewer));
  }
  free(line);
  return (0);
}

static void get_file_name(t_viewer *viewer, const char *s) {
  int i;

  i = strlen(s);
  while (--i >= 0) {
    if (s[i] == '/') {
      viewer->filename = strdup(&(s[i + 1]));
      return;
    }
  }
}

int parser(const char *s, t_viewer *viewer) {
  FILE *file;
  int read_end;
  int max_point;
  int status;

  status = 0;
  if (!s) return (1);
  file = get_file(s, viewer);
  if (!file)
    status = 1;
  else {
    max_point = 0;
    read_end = 0;
    while (!read_end) read_end = parse_file(&max_point, file, viewer);
    fclose(file);
    if (read_end == -1)
      status = 1;
    else if ((size_t)max_point > viewer->info.count_v) {
      viewer->filename = strdup("Error");
      status = 1;
    } else if (!viewer->info.count_v) {
      viewer->filename = strdup("No points in file");
      status = 1;
    } else
      get_file_name(viewer, s);
  }
  return (status);
}
