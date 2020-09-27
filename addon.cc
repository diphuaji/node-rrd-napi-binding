#include <assert.h>
#include <node_api.h>
#include <stdio.h>
#include <stdlib.h>
#include <rrd.h>

napi_value Create(napi_env env, napi_callback_info info) {
  napi_status status;

  size_t argc;
  // allow args of variable size
  status = napi_get_cb_info(env, info, &argc, nullptr, nullptr, nullptr);
  assert(status == napi_ok);
  napi_value args[argc];
  status = napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
  assert(status == napi_ok);

  if(argc<2){
    napi_throw_type_error(env, nullptr, "Wrong arguments");
    exit(1);
  }
  
  char *argv_tmp;
  size_t num;
  size_t sizes[argc];
  size_t totalBytes = 0;

  for(int i=0;i<argc;i++){
    napi_get_value_string_latin1(env, args[i], nullptr, NULL, &num);
    sizes[i] = num+1;
    totalBytes += num+1;
    char arg[num+1];
    napi_get_value_string_latin1(env, args[i], arg, NULL, nullptr);
    if(!i){
      argv_tmp = (char *)malloc(totalBytes);
    }else{
      argv_tmp = (char *)realloc(argv_tmp, totalBytes);
      printf("%zu\n", totalBytes);
    }
    printf("total: %zu\n", totalBytes);
    printf("num: %zu\n", num+1);
    printf("size of: %zu\n", sizeof(arg));
    printf("memcpy num: %zu\n", totalBytes-num-1);
    memcpy(argv_tmp+totalBytes-num-1, arg, num+1);
    printf("ARG: %s\n", arg);
    printf("loop: %s\n", argv_tmp);
  }
  printf("Total bytes: %zu\n", totalBytes);

  char **argv = (char **)malloc(argc*sizeof(void *));
  size_t tmp_start = 0;
  size_t start_pos = 0;
  for(int i=0;i<argc;i++){
    char *ptr = argv_tmp+start_pos;
    memcpy(argv+i, &ptr, sizeof(void *));
    start_pos += sizes[i];
  }
  
  napi_value result;
  status = napi_create_int32(env, rrd_create(argc, argv), &result);
  assert(status == napi_ok);

  free(argv);
  free(argv_tmp);

  // check if there is any error;
  rrd_context_t * ctx = rrd_get_context();
  printf("Error from librrd: %s\n",ctx->rrd_error);
  return result;
}

napi_value Update(napi_env env, napi_callback_info info) {
  
}

#define DECLARE_NAPI_METHOD(name, func)                                        \
  { name, 0, func, 0, 0, 0, napi_default, 0 }

napi_value Init(napi_env env, napi_value exports) {
  napi_status status;
  napi_property_descriptor addDescriptor = DECLARE_NAPI_METHOD("create", Create);
  status = napi_define_properties(env, exports, 1, &addDescriptor);
  assert(status == napi_ok);
  return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)
