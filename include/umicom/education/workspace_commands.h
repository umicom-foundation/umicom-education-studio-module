/*-----------------------------------------------------------------------------
 * Umicom Education Studio Module
 * File: include/umicom/education/workspace_commands.h
 *
 * PURPOSE:
 *   Expose product-facing layout, panel and context commands implemented by the Framework runtime.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


#ifndef UMICOM_EDUCATION_WORKSPACE_COMMANDS_H
#define UMICOM_EDUCATION_WORKSPACE_COMMANDS_H

#include "umicom/education/runtime.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Provide the education workspace select layout operation used by this module and its
 * client applications.
 */
UmiStatus umi_education_workspace_select_layout(
    UmiApplicationWorkspaceRuntime *runtime,
    const char *layout_id);
/**
 * Provide the education workspace activate panel operation used by this module and its
 * client applications.
 */
UmiStatus umi_education_workspace_activate_panel(
    UmiApplicationWorkspaceRuntime *runtime,
    const char *panel_id);
/**
 * Provide the education workspace set context operation used by this module and its client
 * applications.
 */
UmiStatus umi_education_workspace_set_context(
    UmiApplicationWorkspaceRuntime *runtime,
    const char *group_id,
    const char *value);
/**
 * Provide the education workspace commands operation used by this module and its client
 * applications.
 */
const UmiApplicationCommandSurface *umi_education_workspace_commands(
    const UmiApplicationWorkspaceRuntime *runtime);

#ifdef __cplusplus
}
#endif

#endif
