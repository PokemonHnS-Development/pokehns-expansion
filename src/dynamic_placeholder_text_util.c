#include "global.h"
#include "text.h"
#include "dynamic_placeholder_text_util.h"
#include "string_util.h"

static EWRAM_DATA const u8 *sStringPointers[8] = {};

void DynamicPlaceholderTextUtil_Reset(void)
{
    const u8 **ptr;
    u8 *fillval;
    const u8 **ptr2;

    ptr = sStringPointers;
    fillval = NULL;
    ptr2 = ptr + (ARRAY_COUNT(sStringPointers) - 1);
    do
    {
        *ptr2-- = fillval;
    } while ((int)ptr2 >= (int)ptr);
}

void DynamicPlaceholderTextUtil_SetPlaceholderPtr(u8 idx, const u8 *ptr)
{
    if (idx < ARRAY_COUNT(sStringPointers))
    {
        sStringPointers[idx] = ptr;
    }
}

u8 *DynamicPlaceholderTextUtil_ExpandPlaceholders(u8 *dest, const u8 *src)
{
#if TEXT_RTL
    const u8 *template = src;
#endif
#if RTL_STRING_REPORT
    RtlStringReport(src);
#endif
    while (*src != EOS)
    {
        if (*src != CHAR_DYNAMIC)
        {
            *dest++ = *src++;
        }
        else
        {
            src++;
            if (sStringPointers[*src] != NULL)
            {
#if TEXT_RTL
                u8 *expansion = dest;

                dest = StringCopy(dest, sStringPointers[*src]);
                if (RtlNeedsPrefixMaqaf(template, src - 1, expansion))
                {
                    memmove(expansion + 1, expansion, dest - expansion);
                    *expansion = CHAR_HYPHEN;
                    dest++;
                }
#else
                dest = StringCopy(dest, sStringPointers[*src]);
#endif
            }
            src++;
        }
    }
    *dest = EOS;
    return dest;
}

const u8 *DynamicPlaceholderTextUtil_GetPlaceholderPtr(u8 idx)
{
    return sStringPointers[idx];
}
