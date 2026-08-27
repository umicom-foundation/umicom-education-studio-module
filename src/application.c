/*-----------------------------------------------------------------------------
 * Umicom Education Studio Module
 * File: src/application.c
 *
 * PURPOSE:
 *   Bind the product identity to the canonical Framework application-experience catalogue.
 *
 * Created by: Sammy Hegab
 * Organisation: Umicom Foundation
 * Licence: MIT
 *---------------------------------------------------------------------------*/

#include "umicom/education/application.h"

#include "umicom/application/experience_catalogue.h"

const char *umi_education_application_id(void)
{
    return "org.umicom.education";
}

const UmiApplicationExperienceDefinition *
umi_education_application_experience(void)
{
    return umi_application_experience_catalogue_find(
        umi_education_application_id());
}

UmiStatus umi_education_application_status(
    UmiApplicationExperienceStatus *out_status)
{
    const UmiApplicationExperienceDefinition *definition =
        umi_education_application_experience();
    if (definition == NULL) return UMI_STATUS_NOT_FOUND;
    return umi_application_experience_status(definition, out_status);
}
