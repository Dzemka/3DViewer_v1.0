#include <stdlib.h>

#include "../include/viewer.h"

static int cmp_arrays(double *test_array, double *result_array, int size) {
  int i;
  int status;

  i = -1;
  status = 0;
  while (++i < size) {
    if (round(test_array[i] * 1000000) / 1000000.0 != result_array[i])
      return (1);
  }
  if (i != size)
    status = 1;
  else
    status = 0;
  return (status);
}

int main() {
  t_viewer *viewer;
  int result;

  viewer = malloc(sizeof(t_viewer));
  viewer->vertex_list = NULL;
  viewer->info.vertexes3d = NULL;
  viewer->info.count_v = 0;
  viewer->dimensions.x_min = 0;
  viewer->dimensions.x_max = 0;
  viewer->dimensions.y_min = 0;
  viewer->dimensions.y_max = 0;
  viewer->dimensions.z_min = 0;
  viewer->dimensions.z_max = 0;
  viewer->info.width = 1360;
  viewer->info.height = 1000;

  //файл не существует
  result = parser("3DViewer/tests/test1_file", viewer);
  if (result == 1)
    printf("Parser Test1: OK\n");
  else
    printf("Parser Test1: NO\n");
  clean_info(viewer);

  //файл не имеет формат .obj
  result = parser("3DViewer/tests/test2_file", viewer);
  if (result == 1)
    printf("Parser Test2: OK\n");
  else
    printf("Parser Test2: NO\n");
  clean_info(viewer);

  //в файле нет точек
  result = parser("3DViewer/tests/test3_file.obj", viewer);
  if (result && !viewer->info.count_v)
    printf("Parser Test3: OK\n");
  else
    printf("Parser Test3: NO\n");
  clean_info(viewer);

  //у точек недостаточно координат
  result = parser("3DViewer/tests/test4_file.obj", viewer);
  if (result)
    printf("Parser Test4: OK\n");
  else
    printf("Parser Test4: NO\n");
  clean_info(viewer);

  //плоскость ссылается на несуществующую точку
  result = parser("3DViewer/tests/test5_file.obj", viewer);
  if (result == 1)
    printf("Parser Test5: OK\n");
  else
    printf("Parser Test5: NO\n");
  clean_info(viewer);

  //хороший файл
  result = parser("3DViewer/tests/test6_file.obj", viewer);
  if (!result && viewer->info.count_v == 5) {
    int i;
    int j = 0;
    double vertexes[15] = {1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0};
    size_t faces[6] = {1, 2, 3, 4, 2, 5};
    t_list *tmp = viewer->vertex_list;
    while (tmp) {
      i = 0;
      while (i < 3) {
        if (((double *)tmp->content)[i] != vertexes[j]) {
          printf("Parser Test6: NO\n");
          tmp = NULL;
          break;
        }
        i++;
        j++;
      }
      if (tmp) tmp = tmp->next;
    }
    if (j == 15) {
      j = 0;
      t_list *tmp = viewer->faces;
      while (tmp) {
        i = 0;
        while ((size_t)i < ((t_plane *)tmp->content)->size) {
          if (j > 5 ||
              ((size_t)((int *)((t_plane *)tmp->content)->indexes)[i]) !=
                  faces[j]) {
            tmp = NULL;
            j = 0;
            break;
          }
          i++;
          j++;
        }
        if (tmp) tmp = tmp->next;
      }
      if (j == 6)
        printf("Parser Test6: OK\n");
      else
        printf("Parser Test6: NO\n");
    }
  } else
    printf("Parser Test6: NO\n");
  clean_info(viewer);

  if (viewer->filename) {
    free(viewer->filename);
    viewer->filename = NULL;
  }
  free(viewer);

  double test1_array[12] = {0, 0, 0, 1, 1, 1, -2, 3, 4, 5, 1.1, -3};
  moveArray(test1_array, 12, 2, 0);
  double result1_array[12] = {2, 0, 0, 3, 1, 1, 0, 3, 4, 7, 1.1, -3};
  result = cmp_arrays(test1_array, result1_array, 12);
  if (!result)
    printf("Transformation Test1: OK\n");
  else
    printf("Transformation Test1: NO\n");

  double test2_array[12] = {0, 0, 0, 1, 1, 1, -2, 3, 4, 5, 1.1, -3};
  moveArray(test2_array, 12, 2, 1);
  double result2_array[12] = {0, 2, 0, 1, 3, 1, -2, 5, 4, 5, 3.1, -3};
  result = cmp_arrays(test2_array, result2_array, 12);
  if (!result)
    printf("Transformation Test2: OK\n");
  else
    printf("Transformation Test2: NO\n");

  double test3_array[12] = {0, 0, 0, 1, 1, 1, -2, 3, 4, 5, 1.1, -3};
  moveArray(test3_array, 12, 2, 2);
  double result3_array[12] = {0, 0, 2, 1, 1, 3, -2, 3, 6, 5, 1.1, -1};
  result = cmp_arrays(test3_array, result3_array, 12);
  if (!result)
    printf("Transformation Test3: OK\n");
  else
    printf("Transformation Test3: NO\n");

  double test4_array[9] = {0, 0, 0, 1, 0, 1, -2, 1.5, 0};
  rotateArray(test4_array, 9, 90, 0);
  double result4_array[9] = {0, 0, 0, 1, 1, 0, -2, 0, -1.5};
  result = cmp_arrays(test4_array, result4_array, 9);
  if (!result)
    printf("Transformation Test4: OK\n");
  else
    printf("Transformation Test4: NO\n");

  double test5_array[9] = {0, 0, 0, 1, 0, 1, -2, 1.5, 0};
  rotateArray(test5_array, 9, 90, 1);
  double result5_array[9] = {0, 0, 0, -1, 0, 1, 0, 1.5, -2};
  result = cmp_arrays(test5_array, result5_array, 9);
  if (!result)
    printf("Transformation Test5: OK\n");
  else
    printf("Transformation Test5: NO\n");

  double test6_array[9] = {0, 0, 0, 1, 0, 1, -2, 1.5, 0};
  rotateArray(test6_array, 9, 90, 2);
  double result6_array[9] = {0, 0, 0, 0, -1, 1, 1.5, 2, 0};
  result = cmp_arrays(test6_array, result6_array, 9);
  if (!result)
    printf("Transformation Test6: OK\n");
  else
    printf("Transformation Test6: NO\n");

  double test7_array[9] = {0, 0, 0, 1, 0, 1, -2, 1.5, 0};
  scaleArray(test7_array, 9, 2);
  double result7_array[9] = {0, 0, 0, 2, 0, 2, -4, 3, 0};
  result = cmp_arrays(test7_array, result7_array, 9);
  if (!result)
    printf("Transformation Test7: OK\n");
  else
    printf("Transformation Test7: NO\n");
}
