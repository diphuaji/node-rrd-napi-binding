#include <addon.h>
#ifndef utils_h
#define utils_h

void create_string_array(napi_env env, int length, char ** string_array, napi_value* value_ptr);
void convert_time_to_int(napi_env, time_t, napi_value*);
void free_argv_info_related_resources(ArgvInfo argv_info);
void print_rrd_error();

bool assign_argv_info(
    napi_env env,
    napi_callback_info info,
    ArgvInfo * argv_info_ptr
);
#endif
