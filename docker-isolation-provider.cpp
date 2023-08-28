#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>


static ngx_int_t ngx_http_module_init(ngx_conf_t *cf);
static char *ngx_http_directive(ngx_conf_t *cf, ngx_command_t *cmd, void *conf);


static ngx_command_t ngx_http_commands[] = {
        { ngx_string("directive"),
          NGX_HTTP_LOC_CONF|NGX_CONF_TAKE1,
          ngx_http_directive,
          NGX_HTTP_LOC_CONF_OFFSET,
          0,
          NULL },

        ngx_null_command
};


typedef struct {
    ngx_str_t some_value;
} ngx_http_conf_t;


static ngx_http_module_t ngx_http_module_ctx = {
        NULL,                                   /* preconfiguration */
        ngx_http_module_init,               /* postconfiguration */

        NULL,                                   /* create main configuration */
        NULL,                                   /* init main configuration */

        NULL,                                   /* create server configuration */
        NULL,                                   /* merge server configuration */

        NULL,                                   /* create location configuration */
        NULL                                    /* merge location configuration */
};


ngx_module_t ngx_http_module = {
        NGX_MODULE_V1,
        &ngx_http_module_ctx,               /* module context */
        ngx_http_commands,                  /* module directives */
        NGX_HTTP_MODULE,                         /* module type */
        NULL,                                   /* init master */
        NULL,                                   /* init module */
        NULL,                                   /* init process */
        NULL,                                   /* init thread */
        NULL,                                   /* exit thread */
        NULL,                                   /* exit process */
        NULL,                                   /* exit master */
        NGX_MODULE_V1_PADDING
};


static char *ngx_http_directive(ngx_conf_t *cf, ngx_command_t *cmd, void *conf) {
    ngx_http_core_loc_conf_t *clcf;

    clcf = ngx_http_conf_get_module_loc_conf(cf, ngx_http_core_module);
    clcf->handler = ngx_http_handler;

    ngx_conf_set_str_slot(cf, cmd, conf);

    return NGX_CONF_OK;
}


static ngx_int_t ngx_http_handler(ngx_http_request_t *r) {
    ngx_log_error(NGX_LOG_NOTICE, r->connection->log, 0, "Handling your request");

    return NGX_HTTP_OK;
}


static ngx_int_t ngx_http_module_init(ngx_conf_t *cf) {
    ngx_http_core_main_conf_t *cmcf;
    cmcf = ngx_http_conf_get_module_main_conf(cf, ngx_http_core_module);

    ngx_http_handler_pt *h = ngx_array_push(&cmcf->phases[NGX_HTTP_CONTENT_PHASE].handlers);
    if (h == NULL) {
        return NGX_ERROR;
    }

    *h = ngx_http_handler;

    return NGX_OK;
}
