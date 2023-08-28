cmake_minimum_required(VERSION 3.12)
project(cpp-docker-isolation-provider)

set( CMAKE_CXX_STANDARD 11 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )

add_definitions(-pipe -O -W -Wall -Wpointer-arith -Wno-unused-parameter -Werror -g)

INCLUDE_DIRECTORIES(
  "${CMAKE_SOURCE_DIR}/python"
)

# Find Boost package
find_package(Boost REQUIRED COMPONENTS python)

# Add the Boost include directory
include_directories(${Boost_INCLUDE_DIRS})

find_package(PythonLibs REQUIRED)

set(NGINX_SOURCE_PATH /home/deep-foundation/nginx/)

include_directories(
        ${NGINX_SOURCE_PATH}/src/core
        ${NGINX_SOURCE_PATH}/src/event
        ${NGINX_SOURCE_PATH}/src/event/modules
        ${NGINX_SOURCE_PATH}/src/event/quic
        ${NGINX_SOURCE_PATH}/src/os/unix
        ${NGINX_SOURCE_PATH}/objs
        ${NGINX_SOURCE_PATH}/src/http
        ${NGINX_SOURCE_PATH}/src/http/modules
)

set(CORE_DEPS
        ${NGINX_SOURCE_PATH}/src/core/nginx.h
        ${NGINX_SOURCE_PATH}/objs/ngx_auto_config.h
)

set(CORE_INCS
        -I ${NGINX_SOURCE_PATH}/src/core
        -I ${NGINX_SOURCE_PATH}/src/event
        -I ${NGINX_SOURCE_PATH}/src/event/modules
        -I ${NGINX_SOURCE_PATH}/src/event/quic
        -I ${NGINX_SOURCE_PATH}/src/os/unix
        -I ${NGINX_SOURCE_PATH}/objs
)

set(HTTP_DEPS
        ${NGINX_SOURCE_PATH}/src/http/ngx_http.h
        ${NGINX_SOURCE_PATH}/src/http/modules/ngx_http_ssi_filter_module.h
)

set(HTTP_INCS
        -I ${NGINX_SOURCE_PATH}/src/http
        -I ${NGINX_SOURCE_PATH}/src/http/modules
)

ADD_LIBRARY(cpp-docker-isolation-provider STATIC
        docker-isolation-provider.cpp
        ${CORE_DEPS}
        ${HTTP_DEPS}
)

# Link against Boost libraries
TARGET_LINK_LIBRARIES(cpp-docker-isolation-provider ${Boost_LIBRARIES} ${PYTHON_LIBRARIES} ${CMAKE_SOURCE_DIR}/nginx.o)

set_target_properties(cpp-docker-isolation-provider
  PROPERTIES
  ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
  LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
  PREFIX ""
)