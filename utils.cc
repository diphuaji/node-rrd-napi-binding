#include <assert.h>
#include <node_api.h>
#include <stdio.h>
#include <stdlib.h>
#include <rrd.h>
#include <utils.h>

void create_string_array(napi_env env, int length, char ** string_array, napi_value* value_ptr){
  napi_status status;
  status = napi_create_array(env, value_ptr);
  assert(status == napi_ok);
  for(uint32_t i=0; i<length; i++){
    napi_value el;
    status = napi_create_string_utf8(env, string_array[i], NAPI_AUTO_LENGTH, &el);
    assert(status == napi_ok);
    status = napi_set_element(env, (*value_ptr), i, el);
    assert(status == napi_ok);
  }
}

void convert_time_to_int(napi_env env, time_t t, napi_value* value_ptr){
  napi_status status;
  if(sizeof(t)==32){
    status = napi_create_int32(env, t, value_ptr);
  }else{
    status = napi_create_int64(env, t, value_ptr);
  }
  assert(status == napi_ok);
}

void free_argv_info_related_resources(ArgvInfo argv_info){
    free(argv_info.argv);
    free(argv_info.argv_values);
}

void print_rrd_error() {
    // check if there is any error;
    rrd_context_t * ctx = rrd_get_context();
    if(strlen(ctx->rrd_error))
      printf("Error from librrd: %s\n",ctx->rrd_error);
}

bool assign_argv_info(
    napi_env env,
    napi_callback_info info,
    ArgvInfo * argv_info_ptr
) {
    napi_status status;
    size_t argc;

    // allow args of variable size
    status = napi_get_cb_info(env, info, &argc, nullptr, nullptr, nullptr);
    assert(status == napi_ok);

    if (!argc) {
        napi_throw_error(env, nullptr, "Wrong Number of Arguments");
        return false;
    }

    napi_value args[argc];
    status = napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    assert(status == napi_ok);


    size_t num;
    size_t sizes[argc];
    size_t totalBytes = 0;
    char ** argv;
    char * argv_values;

    for(int i=0; i<argc; i++) {
        napi_get_value_string_latin1(env, args[i], nullptr, NULL, &num);
        sizes[i] = num+1;
        totalBytes += num+1;
        char arg[num+1];
        napi_get_value_string_latin1(env, args[i], arg, NULL, nullptr);
        if(!i) {
            argv_values = (char *)malloc(totalBytes);
        } else {
            argv_values = (char *)realloc(argv_values, totalBytes);
        }
        memcpy(argv_values+totalBytes-num-1, arg, num+1);
    }

    argv = (char **)malloc(argc*sizeof(void *));
    size_t tmp_start = 0;
    size_t start_pos = 0;
    for(int i=0; i<argc; i++) {
        char *ptr = argv_values+start_pos;
        memcpy(argv+i, &ptr, sizeof(void *));
        start_pos += sizes[i];
    }
    argv_info_ptr->argc = argc;
    argv_info_ptr->argv = argv;
    argv_info_ptr->argv_values= argv_values;
    return true;
}
