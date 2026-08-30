/*-----------------------------------------------------------------------------
 * Umicom Education Studio Module
 * File: include/umicom/education/application.h
 *
 * PURPOSE:
 *   Expose the thin application composition over Framework-owned experience metadata and services.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#ifndef UMICOM_EDUCATION_APPLICATION_H
#define UMICOM_EDUCATION_APPLICATION_H

#include "umicom/application/experience.h"
#include "umicom/application/experience_status.h"

#ifdef __cplusplus
extern "C" {
#endif

#define UMI_EDUCATION_MODULE_API_VERSION 1U

const char *umi_education_application_id(void);

const UmiApplicationExperienceDefinition *
umi_education_application_experience(void);

UmiStatus umi_education_application_status(
    UmiApplicationExperienceStatus *out_status);

#ifdef __cplusplus
}
#endif

#endif
