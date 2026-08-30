/*-----------------------------------------------------------------------------
 * Umicom Education Studio Module
 * File: include/umicom/education/readiness.h
 *
 * PURPOSE:
 *   Expose Framework-owned readiness and ownership evidence through the thin product boundary.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


#ifndef UMICOM_EDUCATION_READINESS_H
#define UMICOM_EDUCATION_READINESS_H

#include "umicom/application/runtime/readiness.h"

#ifdef __cplusplus
extern "C" {
#endif

UmiStatus umi_education_readiness_report(
    UmiApplicationReadinessReport *out_report);
const UmiExperienceFeatureDefinition *umi_education_readiness_next_feature(void);

#ifdef __cplusplus
}
#endif

#endif
