#include "../../include/viewer.h"

void clean_data_parse(t_viewer *viewer) {
  t_list *tmp;
  t_plane *plane;

  while (viewer->faces) {
    plane = viewer->faces->content;
    tmp = viewer->faces->next;
    free(plane->indexes);
    free(plane);
    free(viewer->faces);
    viewer->faces = tmp;
  }
  viewer->faces = NULL;
  ft_lstclear(&viewer->vertex_list, free);
  viewer->vertex_list = NULL;
}

void clean_data_object(t_viewer *viewer) {
  if (viewer->info.vertexes3d) free(viewer->info.vertexes3d);
  viewer->info.vertexes3d = NULL;
  viewer->info.count_v = 0;
  if (viewer->info.index_array) free(viewer->info.index_array);
  viewer->info.index_array = NULL;
  viewer->info.count_indexes = 0;
  if (viewer->filename) free(viewer->filename);
  viewer->filename = NULL;
}

void clean_info(t_viewer *viewer) {
  clean_data_parse(viewer);
  if (viewer->filename) free(viewer->filename);
  viewer->filename = NULL;
  viewer->info.count_v = 0;
}