/*-----------------------------------------------------------------------------
 * Umicom Education Studio Module
 * File: include/umicom/education/workspace.h
 *
 * PURPOSE:
 *   Expose product workspace lookups without duplicating Framework workbench or layout logic.
 *
 * Created by: Sammy Hegab
 * Organisation: Umicom Foundation
 * Licence: MIT
 *---------------------------------------------------------------------------*/

#ifndef UMICOM_EDUCATION_WORKSPACE_H
#define UMICOM_EDUCATION_WORKSPACE_H

#include <stddef.h>

#include "umicom/application/experience.h"

#ifdef __cplusplus
extern "C" {
#endif

size_t umi_education_workspace_layout_count(void);

const UmiExperienceLayoutDefinition *umi_education_workspace_layout_at(
    size_t index);

const UmiExperienceLayoutDefinition *umi_education_workspace_default(void);

const UmiExperienceFeatureDefinition *umi_education_workspace_next_feature(
    void);

#ifdef __cplusplus
}
#endif

#endif
