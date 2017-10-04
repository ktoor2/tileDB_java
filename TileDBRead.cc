#include "tiledb.h"
#include "TileDBRead.h"
#include <jni.h>
#include <cstdio>
#include <iostream>

 JNIEXPORT void JNICALL Java_TileDBRead_display(JNIEnv *env, jobject obj){
  // Initialize context with the default configuration parameters
  tiledb_ctx_t* ctx;
  tiledb_ctx_create(&ctx);

  // Prepare cell buffers
  int buffer_a1[16];
  uint64_t buffer_a2[16];
  char buffer_var_a2[40];
  float buffer_a3[32];
  void* buffers[] = {buffer_a1, buffer_a2, buffer_var_a2, buffer_a3};
  uint64_t buffer_sizes[] = {sizeof(buffer_a1),
                             sizeof(buffer_a2),
                             sizeof(buffer_var_a2),
                             sizeof(buffer_a3)};

  // Create query
  tiledb_query_t* query;
  tiledb_query_create(
      ctx,
      &query,
      "my_dense_array",
      TILEDB_READ,
      TILEDB_GLOBAL_ORDER,
      nullptr,
      nullptr,
      0,
      buffers,
      buffer_sizes);

  // Submit query
  tiledb_query_submit(ctx, query);

  // Print only non-empty cell values
  int64_t result_num = buffer_sizes[0] / sizeof(int);
  std::cout << "result num: " << result_num << "\n";
  printf(" a1\t    a2\t   (a3.first, a3.second)\n");
  printf("-----------------------------------------\n");
  for (int i = 0; i < result_num; ++i) {
    printf("%3d", buffer_a1[i]);
    uint64_t var_size = (i != result_num - 1) ?
                            buffer_a2[i + 1] - buffer_a2[i] :
                            buffer_sizes[2] - buffer_a2[i];
    printf("\t %4.*s", int(var_size), &buffer_var_a2[buffer_a2[i]]);
    printf("\t\t (%5.1f, %5.1f)\n", buffer_a3[2 * i], buffer_a3[2 * i + 1]);
  }

  // Clean up
  tiledb_query_free(ctx, query);
  tiledb_ctx_free(ctx);

  return;
}
