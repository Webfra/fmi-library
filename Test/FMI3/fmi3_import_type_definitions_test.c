#include <stdio.h>
#include <float.h>

#include <fmilib.h>
#include "config_test.h"
#include "fmil_test.h"

static fmi3_import_t *parse_xml(const char *model_desc_path)
{
    jm_callbacks *cb = jm_get_default_callbacks();
    fmi_import_context_t *ctx = fmi_import_allocate_context(cb);
    fmi3_import_t *xml;

    if (ctx == NULL) {
        return NULL;
    }

    xml = fmi3_import_parse_xml(ctx, model_desc_path, NULL);

    fmi_import_free_context(ctx);
    return xml;
}

/* Parse small Float64 typedef */
static int test_type1(fmi3_import_t *xml)
{
    fmi3_import_variable_t *v = fmi3_import_get_variable_by_name(xml, "var.name1");
    fmi3_import_float64_variable_t *var;
    fmi3_import_variable_typedef_t *t;
    fmi3_import_float_typedef_t *type;

    ASSERT_MSG(v != NULL, "could not find variable to test");
    ASSERT_MSG(fmi3_import_get_variable_vr(v) == 1073741824, "bad vr");

    t = fmi3_import_get_variable_declared_type(v);
    ASSERT_MSG(t != NULL, "no declaredType found for enum variable");

    ASSERT_MSG(strcmp(fmi3_import_get_type_name(t), "Float64.name") == 0, "wrong type name");
    ASSERT_MSG(strcmp(fmi3_import_get_type_quantity(t), "typeQuantity") == 0, "wrong quantity in type definition");

    type = fmi3_import_get_type_as_float(t);
    ASSERT_MSG(type != NULL, "failed to convert to float type definition");
    ASSERT_MSG(fmi3_import_get_float64_type_max(type) == DBL_MAX, "wrong max for type"); /* from md */
    ASSERT_MSG(fmi3_import_get_float64_type_min(type) == 0.0, "wrong min for type"); /* default */
    ASSERT_MSG(fmi3_import_get_float64_type_nominal(type) == 1.0, "wrong nominal for type"); /* default */

    return TEST_OK;
}

int main(int argc, char **argv)
{
    fmi3_import_t *xml;
    int ret = 1;
    if (argc != 2) {
        printf("Usage: %s <path_to_dir_containing_float_modelDescription>\n", argv[0]);
        return CTEST_RETURN_FAIL;
    }

    printf("Running fmi3_import_variable_types_test\n");

    xml = parse_xml(argv[1]);
    if (xml == NULL) {
        return CTEST_RETURN_FAIL;
    }

    ret &= test_type1(xml);

    fmi3_import_free(xml);
    return ret == 0 ? CTEST_RETURN_FAIL : CTEST_RETURN_SUCCESS;
}
