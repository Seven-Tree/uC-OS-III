/*
*********************************************************************************************************
*                                             uC/FS V4
*                                     The Embedded File System
*
*                         (c) Copyright 2008-2014; Micrium, Inc.; Weston, FL
*
*                  All rights reserved.  Protected by international copyright laws.
*
*                  uC/FS is provided in source form to registered licensees ONLY.  It is
*                  illegal to distribute this source code to any third party unless you receive
*                  written permission by an authorized Micrium representative.  Knowledge of
*                  the source code may NOT be used to develop a similar product.
*
*                  Please help us continue to provide the Embedded community with the finest
*                  software available.  Your honesty is greatly appreciated.
*
*                  You can find our product's user manual, API reference, release notes and
*                  more information at: https://doc.micrium.com
*
*                  You can contact us at: http://www.micrium.com
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                          FILE SYSTEM TYPES
*
* Filename      : fs_type.h
* Version       : v4.07.00
* Programmer(s) : AHFAI
*                 BAN
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                               MODULE
*********************************************************************************************************
*/

#ifndef  FS_TYPE_H
#define  FS_TYPE_H


/*
*********************************************************************************************************
*                                          INCLUDE FILES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                               EXTERNS
*********************************************************************************************************
*/

#ifdef   FS_TYPE_MODULE
#define  FS_TYPE_EXT
#else
#define  FS_TYPE_EXT  extern
#endif


/*
*********************************************************************************************************
*                                          INCLUDE FILES
*********************************************************************************************************
*/

#include  <cpu.h>
#include  <lib_def.h>
#include  <lib_mem.h>
#include  "fs_cfg_fs.h"


/*
*********************************************************************************************************
*                                               DEFINES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                               MACRO'S
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             DATA TYPES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                        FORWARD DECLARATIONS
*********************************************************************************************************
*/

typedef  struct  fs_buf              FS_BUF;

typedef  struct  fs_dev              FS_DEV;

typedef  struct  fs_dev_api          FS_DEV_API;

typedef  struct  fs_dir              FS_DIR;

typedef  struct  fs_entry_info       FS_ENTRY_INFO;

typedef  struct  fs_file             FS_FILE;

typedef  struct  fs_partition_entry  FS_PARTITION_ENTRY;

typedef  struct  fs_sys_info         FS_SYS_INFO;

typedef  struct  fs_vol              FS_VOL;

typedef  struct  fs_vol_cache_api    FS_VOL_CACHE_API;


/*
*********************************************************************************************************
*                                          FILE SYSTEM TYPE
*
* Note(s) : (1) 'FS_TYPE' declared as 'CPU_INT32U' & all 'FS_TYPE's #define'd with large, non-trivial
*               values to trap & discard invalid/corrupted file system objects based on 'FS_TYPE'.
*
*           (2) 'FS_TYPE_CREATE()' macro forms 'CPU_INT32U' type value from three 'CPU_CHAR' characters.
*********************************************************************************************************
*/

typedef  CPU_INT32U  FS_TYPE;


#if     (CPU_CFG_ENDIAN_TYPE == CPU_ENDIAN_TYPE_BIG)
#define  FS_TYPE_CREATE(c1, c2, c3, c4)         ((CPU_INT32U)((c1) << (3u * DEF_OCTET_NBR_BITS)) | \
                                                 (CPU_INT32U)((c2) << (2u * DEF_OCTET_NBR_BITS)) | \
                                                 (CPU_INT32U)((c3) << (1u * DEF_OCTET_NBR_BITS)) | \
                                                 (CPU_INT32U)((c4) << (0u * DEF_OCTET_NBR_BITS)))
#else

#if     (CPU_CFG_DATA_SIZE   == CPU_WORD_SIZE_32)
#define  FS_TYPE_CREATE(c1, c2, c3, c4)         ((CPU_INT32U)((c1) << (0u * DEF_OCTET_NBR_BITS)) | \
                                                 (CPU_INT32U)((c2) << (1u * DEF_OCTET_NBR_BITS)) | \
                                                 (CPU_INT32U)((c3) << (2u * DEF_OCTET_NBR_BITS)) | \
                                                 (CPU_INT32U)((c4) << (3u * DEF_OCTET_NBR_BITS)))


#elif   (CPU_CFG_DATA_SIZE   == CPU_WORD_SIZE_16)
#define  FS_TYPE_CREATE(c1, c2, c3, c4)         ((CPU_INT32U)((c1) << (2u * DEF_OCTET_NBR_BITS)) | \
                                                 (CPU_INT32U)((c2) << (3u * DEF_OCTET_NBR_BITS)) | \
                                                 (CPU_INT32U)((c3) << (0u * DEF_OCTET_NBR_BITS)) | \
                                                 (CPU_INT32U)((c4) << (1u * DEF_OCTET_NBR_BITS)))

#else                                                           /* Dflt CPU_WORD_SIZE_08.                               */
#define  FS_TYPE_CREATE(c1, c2, c3, c4)         ((CPU_INT32U)((c1) << (3u * DEF_OCTET_NBR_BITS)) | \
                                                 (CPU_INT32U)((c2) << (2u * DEF_OCTET_NBR_BITS)) | \
                                                 (CPU_INT32U)((c3) << (1u * DEF_OCTET_NBR_BITS)) | \
                                                 (CPU_INT32U)((c4) << (0u * DEF_OCTET_NBR_BITS)))
#endif
#endif


/*
*********************************************************************************************************
*                                          FILE SYSTEM FLAGS
*********************************************************************************************************
*/

typedef  CPU_INT32U  FS_FLAGS;


/*
*********************************************************************************************************
*                                     FILE SYSTEM STATE DATA TYPE
*********************************************************************************************************
*/

typedef  CPU_INT16U  FS_STATE;


/*
*********************************************************************************************************
*                                 STRUCTURE / ITEM QUANTITY DATA TYPE
*********************************************************************************************************
*/

typedef  CPU_INT16U  FS_QTY;

#define  FS_QTY_NBR_MAX                         DEF_INT_16U_MAX_VAL


/*
*********************************************************************************************************
*                                    STRUCTURE / ITEM ID DATA TYPE
*********************************************************************************************************
*/

typedef  MEM_POOL_IX  FS_ID;

#define  FS_ID_INVALID                          DEF_GET_U_MAX_VAL(FS_ID)
#define  FS_ID_NBR_MAX                         (FS_ID_INVALID - 1u)


/*
*********************************************************************************************************
*                                      ENTRY NAME SIZE DATA TYPE
*********************************************************************************************************
*/

typedef  CPU_INT16U  FS_FILE_NAME_LEN;

#define  FS_FILE_NAME_LEN_MAX                    DEF_INT_16U_MAX_VAL


/*
*********************************************************************************************************
*                                   FILE / DIRECTORY SIZE DATA TYPE
*********************************************************************************************************
*/

#if (CPU_CFG_DATA_SIZE_MAX >= CPU_WORD_SIZE_64)
typedef  CPU_INT64S  FS_FILE_OFFSET;
#define  FS_FILE_OFFSET_MIN                     DEF_INT_64S_MIN_VAL
#define  FS_FILE_OFFSET_MAX                     DEF_INT_64S_MAX_VAL
typedef  CPU_INT64S  FS_FILE_OFFSET_SIZE;
#else
typedef  CPU_INT32S  FS_FILE_OFFSET;                            /* 2 GB limit for offset.                               */
#define  FS_FILE_OFFSET_MIN                     DEF_INT_32S_MIN_VAL
#define  FS_FILE_OFFSET_MAX                     DEF_INT_32S_MAX_VAL
typedef  CPU_INT32U  FS_FILE_OFFSET_SIZE;
#endif



/*
*********************************************************************************************************
*                                   FILE / DIRECTORY SIZE DATA TYPE
*********************************************************************************************************
*/

typedef  CPU_INT32U  FS_FILE_SIZE;

#define  FS_FILE_SIZE_MAX                        DEF_INT_32U_MAX_VAL


/*
*********************************************************************************************************
*                                   SEC QTY, NBR & SIZE DATA TYPES
*********************************************************************************************************
*/

#if (FS_CFG_64_BITS_LBA_EN == DEF_ENABLED)
typedef  CPU_INT64U  FS_SEC_QTY;

#else
typedef  CPU_INT32U  FS_SEC_QTY;
#endif


typedef  FS_SEC_QTY  FS_SEC_NBR;
typedef  CPU_INT32U  FS_SEC_SIZE;

typedef  CPU_INT16U  FS_PARTITION_NBR;

#define  FS_INVALID_PARTITION_NBR                DEF_INT_16U_MAX_VAL


/*
*********************************************************************************************************
*                                           BITFIELD TYPES
*********************************************************************************************************
*/

#if (defined(__GNUC__) && !defined(__STRICT_ANSI__))
typedef  CPU_INT08U  FS_BITFIELD08U;
typedef  CPU_INT16U  FS_BITFIELD16U;
typedef  CPU_INT32U  FS_BITFIELD32U;
typedef  CPU_INT64U  FS_BITFIELD64U;
#else
typedef  unsigned  int  FS_BITFIELD08U;
typedef  unsigned  int  FS_BITFIELD16U;
typedef  unsigned  int  FS_BITFIELD32U;
typedef  unsigned  int  FS_BITFIELD64U;
#endif


/*
*********************************************************************************************************
*                                          GLOBAL VARIABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                        CONFIGURATION ERRORS
*********************************************************************************************************
*/

                                                                /* ------------- FS_CFG_MAX_FILE_NAME_LEN ------------- */
#ifndef  FS_CFG_MAX_FILE_NAME_LEN
#error  "FS_CFG_MAX_FILE_NAME_LEN                     not #define'd in 'fs_cfg.h'               "

#elif   (FS_CFG_MAX_FILE_NAME_LEN < 1u)
#error  "FS_CFG_MAX_FILE_NAME_LEN               illegally #define'd in 'fs_cfg.h'               "
#error  "                                       [MUST be  >= 1]                                 "

#elif   (FS_CFG_MAX_FILE_NAME_LEN > FS_FILE_NAME_LEN_MAX)
#error  "FS_CFG_MAX_FILE_NAME_LEN               illegally #define'd in 'fs_cfg.h'               "
#error  "                                       [MUST be  <= FS_FILE_NAME_LEN_MAX]                                 "
#endif


                                                                /* ------------- FS_CFG_MAX_PATH_NAME_LEN ------------- */
#ifndef  FS_CFG_MAX_PATH_NAME_LEN
#error  "FS_CFG_MAX_PATH_NAME_LEN                     not #define'd in 'fs_cfg.h'               "
#error  "                                       [MUST be  >= 1]                                 "

#elif   (FS_CFG_MAX_PATH_NAME_LEN < 1u)
#error  "FS_CFG_MAX_PATH_NAME_LEN               illegally #define'd in 'fs_cfg.h'               "
#error  "                                       [MUST be  >= 1]                                 "

#elif   (FS_CFG_MAX_PATH_NAME_LEN <= FS_CFG_MAX_FILE_NAME_LEN)
#error  "FS_CFG_MAX_PATH_NAME_LEN               illegally #define'd in 'fs_cfg.h'               "
#error  "                                       [MUST be  >= FS_CFG_MAX_FILE_NAME_LEN]          "

#elif   (FS_CFG_MAX_PATH_NAME_LEN > FS_FILE_NAME_LEN_MAX)
#error  "FS_CFG_MAX_PATH_NAME_LEN               illegally #define'd in 'fs_cfg.h'               "
#error  "                                       [MUST be  >= 1]                                 "
#endif


                                                                /* ------------ FS_CFG_MAX_DEV_DRV_NAME_LEN ----------- */
#ifndef  FS_CFG_MAX_DEV_DRV_NAME_LEN
#error  "FS_CFG_MAX_DEV_DRV_NAME_LEN              not #define'd in 'fs_cfg.h'               "
#error  "                                   [MUST be  >= 1]                                 "

#elif   (FS_CFG_MAX_DEV_DRV_NAME_LEN < 1u)
#error  "FS_CFG_MAX_DEV_DRV_NAME_LEN        illegally #define'd in 'fs_cfg.h'               "
#error  "                                   [MUST be  >= 1]                                 "

#elif   (FS_CFG_MAX_DEV_DRV_NAME_LEN > FS_FILE_NAME_LEN_MAX)
#error  "FS_CFG_MAX_DEV_DRV_NAME_LEN        illegally #define'd in 'fs_cfg.h'               "
#error  "                                   [MUST be  >= 1]                                 "
#endif


                                                                /* -------------- FS_CFG_MAX_DEV_NAME_LEN ------------- */
#ifndef  FS_CFG_MAX_DEV_NAME_LEN
#error  "FS_CFG_MAX_DEV_NAME_LEN                      not #define'd in 'fs_cfg.h'               "
#error  "                                       [MUST be  >= 1]                                 "

#elif   (FS_CFG_MAX_DEV_NAME_LEN < 1u)
#error  "FS_CFG_MAX_DEV_NAME_LEN                illegally #define'd in 'fs_cfg.h'               "
#error  "                                       [MUST be  >= 1]                                 "

#elif   (FS_CFG_MAX_DEV_NAME_LEN < FS_CFG_MAX_DEV_DRV_NAME_LEN + 3u)
#error  "FS_CFG_MAX_DEV_NAME_LEN                illegally #define'd in 'fs_cfg.h'               "
#error  "                                       [MUST be  >= FS_CFG_MAX_DEV_DRV_NAME_LEN + 3]   "

#elif   (FS_CFG_MAX_DEV_NAME_LEN > FS_CFG_MAX_DEV_DRV_NAME_LEN + 5u)
#error  "FS_CFG_MAX_DEV_NAME_LEN                illegally #define'd in 'fs_cfg.h'               "
#error  "                                       [MUST be  <= FS_CFG_MAX_DEV_DRV_NAME_LEN + 5]   "

#elif   (FS_CFG_MAX_DEV_NAME_LEN > FS_FILE_NAME_LEN_MAX)
#error  "FS_CFG_MAX_DEV_NAME_LEN                illegally #define'd in 'fs_cfg.h'               "
#error  "                                       [MUST be  >= 1]                                 "
#endif


                                                                /* -------------- FS_CFG_MAX_VOL_NAME_LEN ------------- */
#ifndef  FS_CFG_MAX_VOL_NAME_LEN
#error  "FS_CFG_MAX_VOL_NAME_LEN                      not #define'd in 'fs_cfg.h'               "
#error  "                                       [MUST be  >= 1]                                 "

#elif   (FS_CFG_MAX_VOL_NAME_LEN < 1u)
#error  "FS_CFG_MAX_VOL_NAME_LEN                illegally #define'd in 'fs_cfg.h'               "
#error  "                                       [MUST be  >= 1]                                 "

#elif   (FS_CFG_MAX_VOL_NAME_LEN > FS_FILE_NAME_LEN_MAX)
#error  "FS_CFG_MAX_VOL_NAME_LEN                illegally #define'd in 'fs_cfg.h'               "
#error  "                                       [MUST be  >= 1]                                 "
#endif


/*
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*/

#endif
