#include <assert.h>
#include <node_api.h>
#include <stdio.h>
#include <stdlib.h>
#include <rrd.h>
#include <addon.h>
#include <utils.h>

napi_value register_rrd_func_v1(
    napi_env env,
    napi_callback_info info,
    int rrd_func(int, char **argv))
{
    napi_status status;
    napi_value result;
    status = napi_get_boolean(env, false, &result);
    assert(status == napi_ok);
    ArgvInfo argv_info;
    if (!assign_argv_info(env, info, &argv_info))
        return result;
    status = napi_get_boolean(env, rrd_func(argv_info.argc, argv_info.argv) == 0, &result);
    assert(status == napi_ok);
    free_argv_info_related_resources(argv_info);
    print_rrd_error();
    return result;
}

napi_value Create(
    napi_env env,
    napi_callback_info info)
{
    return register_rrd_func_v1(env, info, rrd_create);
}

napi_value Update(
    napi_env env,
    napi_callback_info info)
{
    return register_rrd_func_v1(env, info, rrd_update);
}

napi_value Fetch(
    napi_env env,
    napi_callback_info info)
{
    napi_status status;
    napi_value result;
    status = napi_get_boolean(env, false, &result);
    assert(status == napi_ok);
    ArgvInfo argv_info;
    if (!assign_argv_info(env, info, &argv_info))
        return result;

    time_t start, end;
    unsigned long step, ds_cnt;
    rrd_value_t *data, *datai;
    char **ds_namv;
    status = napi_get_boolean(env, rrd_fetch(argv_info.argc, argv_info.argv, &start, &end, &step, &ds_cnt, &ds_namv, &data) == 0, &result);
    print_rrd_error();
    free_argv_info_related_resources(argv_info);

    status = napi_create_object(env, &result);
    assert(status == napi_ok);
    napi_value start_value;
    convert_time_to_int(env, start, &start_value);
    status = napi_set_named_property(env, result, "start", start_value);
    assert(status == napi_ok);
    napi_value end_value;
    convert_time_to_int(env, end, &end_value);
    status = napi_set_named_property(env, result, "end", end_value);
    assert(status == napi_ok);
    napi_value step_value;
    napi_create_int64(env, step, &step_value);
    status = napi_set_named_property(env, result, "step", step_value);
    assert(status == napi_ok);
    napi_value ds_cnt_value;
    napi_create_int64(env, ds_cnt, &ds_cnt_value);
    status = napi_set_named_property(env, result, "ds_cnt", ds_cnt_value);
    assert(status == napi_ok);
    napi_value ds_namv_value;
    create_string_array(env, ds_cnt, ds_namv, &ds_namv_value);
    status = napi_set_named_property(env, result, "ds_namv", ds_namv_value);
    assert(status == napi_ok);

    napi_value timestamps;
    napi_value data_value;
    status = napi_create_array(env, &data_value);
    assert(status == napi_ok);
    status = napi_create_array(env, &timestamps);
    assert(status == napi_ok);
    datai = data;
    int count = 0;

    napi_value rows[ds_cnt];
    for (int i = 0; i < ds_cnt; i++)
    {
        napi_value row;
        status = napi_create_array(env, &row);
        assert(status == napi_ok);
        rows[i] = row;
    }

    for (time_t ti = start + step; ti <= end; ti += step)
    {
        for (int i = 0; i < ds_cnt; i++)
        {
            napi_value tmp_value;
            status = napi_create_double(env, *(datai++), &tmp_value);
            assert(status == napi_ok);
            status = napi_set_element(env, rows[i], count, tmp_value);
            assert(status == napi_ok);
        }
        napi_value timestamp;
        convert_time_to_int(env, ti, &timestamp);
        status = napi_set_element(env, timestamps, count, timestamp);
        assert(status == napi_ok);
        count++;
    }

    for (int i = 0; i < ds_cnt; i++)
    {
        status = napi_set_element(env, data_value, i, rows[i]);
        assert(status == napi_ok);
    }

    status = napi_set_named_property(env, result, "timestamps", timestamps);
    assert(status == napi_ok);
    status = napi_set_named_property(env, result, "data", data_value);
    assert(status == napi_ok);

    for (int i = 0; i < ds_cnt; i++)
        free(ds_namv[i]);
    free(ds_namv);
    free(data);
    return result;
}

//napi_value Graph(
//    napi_env env,
//    napi_callback_info info
//) {
//    napi_status status;
//    napi_value result;
//    status = napi_get_boolean(env, false, &result);
//    assert(status == napi_ok);
//    ArgvInfo argv_info;
//    if(!assign_argv_info(env, info, &argv_info)) return result;
//
//    int       xsize, ysize;
//    double    ymin, ymax;
//    char **calcpr;
//    status = napi_get_boolean(env, rrd_graph(
//          argv_info.argc,
//          argv_info.argv,
//          &calcpr,
//          &xsize,
//          &ysize,
//          &ymin,
//          &ymax
//        )==0, &result);
//    assert(status == napi_ok);
//    free_argv_info_related_resources(argv_info);
//    print_rrd_error();
//    return result;
//}

#define DECLARE_NAPI_METHOD(name, func)         \
    {                                           \
        name, 0, func, 0, 0, 0, napi_default, 0 \
    }

napi_value Init(napi_env env, napi_value exports)
{
    napi_status status;
    size_t descriptorNum = 3;
    napi_property_descriptor descriptors[descriptorNum];
    descriptors[0] = DECLARE_NAPI_METHOD("create", Create);
    descriptors[1] = DECLARE_NAPI_METHOD("update", Update);
    descriptors[2] = DECLARE_NAPI_METHOD("fetch", Fetch);
    status = napi_define_properties(env, exports, descriptorNum, descriptors);
    assert(status == napi_ok);
    return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)
