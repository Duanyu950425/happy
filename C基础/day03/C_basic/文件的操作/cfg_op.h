#pragma once
#ifndef _INC_CFG_OP_H
#define _INC_CFG_OP_H

#ifdef  __cplusplus
extern "C" {
#endif

    int GetCfgItem(char *pFileName /*in*/, char *pKey /*in*/, char *pValue /*in out*/, int *pValueLen /*out*/);
    int WriteCfgItem(char *pFileName /*in*/, char *pItemName /*in*/, char *pItemValue/*in*/, int *pItemValueLen /*in*/);

#ifdef __cplusplus
}
#endif

#endif
