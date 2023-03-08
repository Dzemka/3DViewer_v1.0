#ifndef VIEWER3D_H
#define VIEWER3D_H

#ifdef __cplusplus
extern "C" {
#endif

#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define X_AXES 0
#define Y_AXES 1
#define Z_AXES 2

#define FRUSTUM 0
#define ORTHO 1

#define BMP 0
#define JPEG 1
#define GIF 2

#define ENGLISH 0
#define RUSSIAN 1

#define FRAMES 50
#define GIF_WIDTH 640
#define GIF_HEIGHT 480

#define VERTEX_TYPE_NONE 0
#define VERTEX_TYPE_CIRCLE 1
#define VERTEX_TYPE_SQUARE 2

#define EDGE_TYPE_SOLID 0
#define EDGE_TYPE_DASHED 1

#define MIN_EDGE_THICKNESS 1
#define MAX_EDGE_THICKNESS 10

#define MIN_VERTEX_SIZE 1
#define MAX_VERTEX_SIZE 10

typedef struct s_list {
  void *content;
  struct s_list *next;
} t_list;

typedef struct s_plane {
  int *indexes;
  size_t size;
} t_plane;

typedef struct s_dimensions {
  double x_min;
  double x_max;
  double y_min;
  double y_max;
  double z_min;
  double z_max;
} t_dimensions;

typedef struct s_transform {
  double xRot;
  double yRot;
  double zRot;
  double xTra;
  double yTra;
  double zTra;
  double nSca;
  double rSca;
} t_transform;

typedef struct s_rgb {
  double r;
  double g;
  double b;
} t_rgb;

typedef struct s_info {
  double width;
  double height;
  double *vertexes3d;
  unsigned int *index_array;
  size_t count_v;
  unsigned int count_indexes;
} t_info;

typedef struct s_viewer {
  char *filename;
  t_info info;
  t_dimensions dimensions;
  t_list *vertex_list;
  t_list *faces;
  t_list *tmp;
  t_list *tmp2;
} t_viewer;

int parser(const char *s, t_viewer *viewer);
int parse_values(int *max_point, char **line, t_viewer *viewer);
int parse_vertex(char **split_line, t_viewer *viewer);
int parse_face(int *max_point, char **split_line, t_viewer *viewer);
void create_stringlabel(char *text, t_viewer *viewer);
void free_all(t_viewer *viewer);
void set_values(t_viewer *viewer);
char *ft_strjoin(char const *s1, char const *s2);
void clean_massive_2d(char ***m);
void exit_message(char *s);
char **ft_split(char const *s, char c);
size_t ft_lstsize(t_list *lst);
void ft_lstclear(t_list **lst, void (*del)(void *));
void ft_lstdelone(t_list *lst, void (*del)(void *));
t_list *ft_lstnew(void *content);
void ft_lstadd_back(t_list **alst, t_list *new_list);
void moveArray(double *array, size_t size, double move, int axis);
void rotateArray(double *array, size_t size, double rotate, int axes);
void scaleArray(double *array, size_t size, double scale);
void clean_data_object(t_viewer *viewer);
void clean_data_parse(t_viewer *viewer);
void clean_info(t_viewer *viewer);

#ifdef __cplusplus
}
#endif

#endif  // VIEWER_H
