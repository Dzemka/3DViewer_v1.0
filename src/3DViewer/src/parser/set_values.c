#include "../../include/viewer.h"

static void scale_dimensions(t_viewer *viewer, double scaling) {
  viewer->dimensions.x_max =
      (viewer->dimensions.x_max - viewer->dimensions.x_min) / 2 * scaling;
  viewer->dimensions.x_min = -viewer->dimensions.x_max;
  viewer->dimensions.y_max =
      (viewer->dimensions.y_max - viewer->dimensions.y_min) / 2 * scaling;
  viewer->dimensions.y_min = -viewer->dimensions.y_max;
  viewer->dimensions.z_max =
      (viewer->dimensions.z_max - viewer->dimensions.z_min) / 2 * scaling;
  viewer->dimensions.z_min = -viewer->dimensions.z_max;
}

static void fill_vertexes3d(t_viewer *viewer, double scaling, double width,
                            double height) {
  int i;
  int j;
  t_list *temp;
  temp = viewer->vertex_list;

  j = 0;
  while (temp) {
    i = -1;
    while (++i < 3) {
      if (i == 0) {
        viewer->info.vertexes3d[j] = ((double *)temp->content)[i] -
                                     (viewer->dimensions.x_min + width / 2);
      } else if (i == 1) {
        viewer->info.vertexes3d[j] = ((double *)temp->content)[i] -
                                     (viewer->dimensions.y_min + height / 2);
      } else
        viewer->info.vertexes3d[j] =
            ((double *)temp->content)[i] -
            (viewer->dimensions.z_min + viewer->dimensions.z_max) / 2;
      viewer->info.vertexes3d[j] *= scaling;
      j++;
    }
    temp = temp->next;
  }
}

static void get_scaling(t_viewer *viewer, double *scaling, double *width,
                        double *height) {
  *width = viewer->dimensions.x_max - viewer->dimensions.x_min;
  *height = viewer->dimensions.y_max - viewer->dimensions.y_min;
  if (*width / *height > viewer->info.width / viewer->info.height)
    *scaling = viewer->info.width / *width;
  else
    *scaling = viewer->info.height / *height;
}

static void fill_index_array(t_viewer *viewer) {
  int i;
  size_t j;
  t_list *tmp;
  size_t size;
  int *index;

  i = 0;
  tmp = viewer->faces;
  while (tmp) {
    size = ((t_plane *)tmp->content)->size;
    index = ((t_plane *)tmp->content)->indexes;
    j = 0;
    while (j + 1 < size) {
      if (index[j] < 0) index[j] += viewer->info.count_v;
      viewer->info.index_array[i] = index[j] - 1;
      if (index[j + 1] < 0) index[j + 1] += viewer->info.count_v;
      viewer->info.index_array[i + 1] = index[j + 1] - 1;
      i += 2;
      j++;
    }
    viewer->info.index_array[i] = index[j] - 1;
    viewer->info.index_array[i + 1] = index[0] - 1;
    i += 2;
    tmp = tmp->next;
  }
}

void set_values(t_viewer *viewer) {
  double width = 0;
  double height = 0;
  double scaling = 1;

  viewer->info.vertexes3d = malloc(sizeof(double) * viewer->info.count_v * 3);
  if (!viewer->info.vertexes3d) exit_message("Malloc error\n");
  viewer->info.index_array =
      malloc(sizeof(unsigned int) * viewer->info.count_indexes * 2);
  if (!viewer->info.index_array) exit_message("Malloc error\n");
  get_scaling(viewer, &scaling, &width, &height);
  fill_vertexes3d(viewer, scaling, width, height);
  fill_index_array(viewer);
  scale_dimensions(viewer, scaling);
}
