/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2010 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id: header 297205 2010-03-30 21:09:07Z johannes $ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_cinvan.h"

/* If you declare any globals in php_cinvan.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(cinvan)
*/

/* True global resources - no need for thread safety here */
static int le_cinvan;

//cinvan 这个类结构
zend_class_entry *cinvan;
const zend_function_entry cinvan_methods[] = {
	PHP_ME(cinvan, hello, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(cinvan, get_refcount, NULL, ZEND_ACC_PUBLIC)
	{NULL, NULL, NULL}	/* Must be the last line in cinvan_functions[] */
};

/* {{{ cinvan_functions[]
 *
 * Every user visible function must have an entry in cinvan_functions[].
 */
const zend_function_entry cinvan_functions[] = {
	PHP_FE(confirm_cinvan_compiled,	NULL)		/* For testing, remove later. */
	PHP_FE(cinvan_hello, NULL)
	PHP_FE(create_foobar, NULL)
	PHP_FE(print_foobar, NULL)
	PHP_FE(cinvan_get_refcount, NULL)
	{NULL, NULL, NULL}	/* Must be the last line in cinvan_functions[] */
};
/* }}} */

/* {{{ cinvan_module_entry
 */
zend_module_entry cinvan_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"cinvan",
	cinvan_functions,
	PHP_MINIT(cinvan),
	PHP_MSHUTDOWN(cinvan),
	PHP_RINIT(cinvan),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(cinvan),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(cinvan),
#if ZEND_MODULE_API_NO >= 20010901
	"0.1", /* Replace with version number for your extension */
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_CINVAN
ZEND_GET_MODULE(cinvan)
#endif

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("cinvan.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_cinvan_globals, cinvan_globals)
    STD_PHP_INI_ENTRY("cinvan.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_cinvan_globals, cinvan_globals)
PHP_INI_END()
*/
/* }}} */

/* {{{ php_cinvan_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_cinvan_init_globals(zend_cinvan_globals *cinvan_globals)
{
	cinvan_globals->global_value = 0;
	cinvan_globals->global_string = NULL;
}
*/
/* }}} */

void cinvan_printf(char *string){
	php_printf("this is %s function\n\n", string);
}

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(cinvan)
{
	cinvan_printf("module init");
	/* If you have INI entries, uncomment these lines 
	REGISTER_INI_ENTRIES();
	*/
	zend_class_entry class_entry;

	//注册"cinvan"类
	//INIT_CLASS_ENTRY(class_entry, "cinvan", cinvan_functions);//可以直接使用function作为class的全部public方法
	INIT_CLASS_ENTRY(class_entry, "cinvan", cinvan_methods);
	cinvan = zend_register_internal_class(&class_entry TSRMLS_CC);

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(cinvan)
{
	FILE *fp=fopen("/tmp/cinvan.log","a+");
	fprintf(fp,"%s\n", "this is module shutdown function");
	fclose(fp);
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(cinvan)
{
	cinvan_printf("request init");
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(cinvan)
{
	cinvan_printf("request shutdown");
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(cinvan)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "cinvan support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */


/* Remove the following function when you have succesfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_cinvan_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_cinvan_compiled)
{
	char *arg = NULL;
	int arg_len, len;
	char *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
		RETURN_NULL();
	}

	len = spprintf(&strg, 0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "cinvan", arg);
	RETURN_STRINGL(strg, len, 0);
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and 
   unfold functions in source code. See the corresponding marks just before 
   function definition, where the functions purpose is also documented. Please 
   follow this convention for the convenience of others editing your code.
*/

PHP_FUNCTION(cinvan_hello)
{
	char *arg = NULL, *strg;
	int arg_len, len;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	len = spprintf(&strg, 0, "Hello %s, I'm Cinvan, come from cinvan module", arg);
	RETURN_STRINGL(strg, len, 0);
}

PHP_FUNCTION(create_foobar)
{
	zval *foobar;

	MAKE_STD_ZVAL(foobar);//初始化一个zval
	ZVAL_STRING(foobar, "foobarfoobar", 1);//给foobar这个zval赋值 foobarfoobar
	ZEND_SET_SYMBOL( EG(active_symbol_table) ,  "foobar" , foobar);//将foobar放到全局变量表中
	return;
}

PHP_FUNCTION(print_foobar)
{
    zval **foobar;

    if (zend_hash_find(
            EG(active_symbol_table), //在active_symbol_table表中去找这个值
            "foobar",
            sizeof("foobar"),
            (void**)&foobar
        ) == SUCCESS
    )
    {
    	zend_print_variable(*foobar);
    }
    else
    {
    	php_error_docref(NULL TSRMLS_CC, E_ERROR,"Undefined variable: %s", "foobar");
        php_printf("Undefined variable foobar\n");
    }
}

PHP_FUNCTION(cinvan_get_refcount)
{
	char *arg = NULL;
	int arg_len;
	zval **z_val;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	if (zend_hash_find(EG(active_symbol_table), arg, arg_len+1, (void **)&z_val) == SUCCESS) {
		php_printf("var %s's refcount__gc is %d", arg, Z_REFCOUNT_PP(z_val));

		Z_ADDREF_PP(z_val);//自动进行增加
	} else {
        php_printf("Undefined variable %s\n", arg);
	}
}

//======================class methods==================================

PHP_METHOD(cinvan, hello)
{
	char *arg = NULL, *strg;
	int arg_len, len;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	len = spprintf(&strg, 0, "Hello %s, I'm Cinvan, come from cinvan module", arg);
	RETURN_STRINGL(strg, len, 0);
}

PHP_METHOD(cinvan, get_refcount)
{
	char *arg = NULL;
	int arg_len;
	zval **z_val;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	if (zend_hash_find(EG(active_symbol_table), arg, arg_len+1, (void **)&z_val) == SUCCESS) {
		php_printf("var %s's refcount__gc is %d", arg, Z_REFCOUNT_PP(z_val));

		Z_ADDREF_PP(z_val);//自动进行增加
	} else {
		php_printf("Undefined variable %s\n", arg);
	}
}

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
