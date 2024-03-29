#include "../../include/viewer.h"

double ft_atof(char *str) {
  double value = 0, decimal = 1;
  unsigned char sign = 0, dec = 0;

  if (*str == '+') str++;
  if (*str == '-') {
    sign = 1;
    str++;
  }
  while (*str) {
    if (isdigit(*str)) {
      value = (value * 10) + (*str - '0');
      if (dec) decimal *= 10;
    } else if (*str == '.')
      dec = 1;
    else
      break;
    str++;
  }
  return (!sign) ? (value / decimal) : -(value / decimal);
}

static void set_start_value(double value, int axes, t_viewer *viewer) {
  if (axes == X_AXES) {
    viewer->dimensions.x_max = value;
    viewer->dimensions.x_min = value;
  } else if (axes == Y_AXES) {
    viewer->dimensions.y_max = value;
    viewer->dimensions.y_min = value;
  } else if (axes == Z_AXES) {
    viewer->dimensions.z_max = value;
    viewer->dimensions.z_min = value;
  }
}

static void set_dimensions(double value, t_viewer *viewer, int axes) {
  if (viewer->info.count_v == 1)
    set_start_value(value, axes, viewer);
  else if (axes == X_AXES) {
    if (value > viewer->dimensions.x_max)
      viewer->dimensions.x_max = value;
    else if (value < viewer->dimensions.x_min)
      viewer->dimensions.x_min = value;
  } else if (axes == Y_AXES) {
    if (value > viewer->dimensions.y_max)
      viewer->dimensions.y_max = value;
    else if (value < viewer->dimensions.y_min)
      viewer->dimensions.y_min = value;
  } else if (axes == Z_AXES) {
    if (value > viewer->dimensions.z_max)
      viewer->dimensions.z_max = value;
    else if (value < viewer->dimensions.z_min)
      viewer->dimensions.z_min = value;
  }
}

static int fill_vertex(char **split_line, t_viewer *viewer) {
  double *vertex;
  t_list *list;
  int i;

  vertex = malloc(sizeof(double) * 3);
  if (!vertex) exit_message("Malloc error");
  viewer->info.count_v++;
  i = -1;
  while (++i < 3) {
    vertex[i] = ft_atof(split_line[i]);
    set_dimensions(vertex[i], viewer, i);
  }
  list = ft_lstnew(vertex);
  if (!list) exit_message("Malloc error");
  if (!viewer->vertex_list)
    viewer->vertex_list = list;
  else
    viewer->tmp->next = list;
  viewer->tmp = list;
  return (0);
}

int parse_vertex(char **split_line, t_viewer *viewer) {
  int i;

  i = -1;
  while (split_line[++i])
    ;
  if (i != 3 && i != 4) {
    if (viewer->filename) free(viewer->filename);
    viewer->filename = strdup("Incorrect number of coordinates in file");
    return (-1);
  }
  fill_vertex(split_line, viewer);
  return (0);
}

int parse_face(int *max_point, char **split_line, t_viewer *viewer) {
  int i;
  t_plane *plane;
  t_list *list;

  i = -1;
  while (split_line[++i])
    ;
  plane = malloc(sizeof(t_plane));
  if (!plane) exit_message("Malloc error");
  plane->indexes = (int *)malloc((sizeof(int) * i));
  if (!plane->indexes) exit_message("Malloc error");
  plane->size = i;
  viewer->info.count_indexes += i;
  i = -1;
  while ((size_t)++i < plane->size) {
    plane->indexes[i] = atoi(split_line[i]);
    if (plane->indexes[i] > *max_point) *max_point = plane->indexes[i];
  }
  list = ft_lstnew(plane);
  if (!list) exit_message("Malloc error");
  if (!viewer->faces)
    viewer->faces = list;
  else
    viewer->tmp2->next = list;
  viewer->tmp2 = list;
  return (0);
}
