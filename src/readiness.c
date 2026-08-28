/*-----------------------------------------------------------------------------
 * Umicom Education Studio Module
 * File: src/readiness.c
 *
 * PURPOSE:
 *   Project the canonical Framework feature backlog without product-local roadmap duplication.
 *
 * Created by: Sammy Hegab
 * Organisation: Umicom Foundation
 * Licence: MIT
 *---------------------------------------------------------------------------*/


#include "umicom/education/readiness.h"

#include "umicom/education/runtime.h"
#include "umicom/application/experience_plan.h"

UmiStatus umi_education_readiness_report(
    UmiApplicationReadinessReport *out_report)
{
    const UmiApplicationExperienceDefinition *experience =
        umi_education_runtime_experience();
    if (experience == NULL) return UMI_STATUS_NOT_FOUND;
    return umi_application_readiness_report(experience, out_report);
}

const UmiExperienceFeatureDefinition *umi_education_readiness_next_feature(void)
{
    return umi_application_experience_next_feature(
        umi_education_runtime_experience());
}
