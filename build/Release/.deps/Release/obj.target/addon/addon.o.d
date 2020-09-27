cmd_Release/obj.target/addon/addon.o := g++ '-DNODE_GYP_MODULE_NAME=addon' '-DUSING_UV_SHARED=1' '-DUSING_V8_SHARED=1' '-DV8_DEPRECATION_WARNINGS=1' '-D_LARGEFILE_SOURCE' '-D_FILE_OFFSET_BITS=64' '-DBUILDING_NODE_EXTENSION' -I/home/billy/.node-gyp/10.8.0/include/node -I/home/billy/.node-gyp/10.8.0/src -I/home/billy/.node-gyp/10.8.0/deps/openssl/config -I/home/billy/.node-gyp/10.8.0/deps/openssl/openssl/include -I/home/billy/.node-gyp/10.8.0/deps/uv/include -I/home/billy/.node-gyp/10.8.0/deps/zlib -I/home/billy/.node-gyp/10.8.0/deps/v8/include -I../. -I/opt/rrdtool-1.7.2/include  -fPIC -pthread -Wall -Wextra -Wno-unused-parameter -m64 -O3 -fno-omit-frame-pointer -fno-rtti -fno-exceptions -std=gnu++1y -MMD -MF ./Release/.deps/Release/obj.target/addon/addon.o.d.raw   -c -o Release/obj.target/addon/addon.o ../addon.cc
Release/obj.target/addon/addon.o: ../addon.cc \
 /home/billy/.node-gyp/10.8.0/include/node/node_api.h \
 /home/billy/.node-gyp/10.8.0/include/node/node_api_types.h \
 /opt/rrdtool-1.7.2/include/rrd.h
../addon.cc:
/home/billy/.node-gyp/10.8.0/include/node/node_api.h:
/home/billy/.node-gyp/10.8.0/include/node/node_api_types.h:
/opt/rrdtool-1.7.2/include/rrd.h:
