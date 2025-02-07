/**
  ******************************************************************************
  * @file    ov5640.c
  * @author  MCD Application Team
  * @brief   This file provides the OV5640 camera driver
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2018 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "ov5640.h"

/** @addtogroup BSP
  * @{
  */

/** @addtogroup Components
  * @{
  */

/** @addtogroup OV5640
  * @brief     This file provides a set of functions needed to drive the
  *            OV5640 Camera module.
  * @{
  */
const uint16_t RGB565_Init[][2]=

{

    //15fps VGA RGB565 output

    // 24MHz input clock, 24MHz PCLK

    {0x3103, 0x11}, // system clock from pad, bit[1]

    {0x3008, 0x82}, // software reset, bit[7]

    // delay 5ms

    {0x3008, 0x42}, // software power down, bit[6]

    {0x3103, 0x03}, // system clock from PLL, bit[1]

    {0x3017, 0xff}, // FREX, Vsync, HREF, PCLK, D[9:6] output enable

    {0x3018, 0xff}, // D[5:0], GPIO[1:0] output enable

    {0x3034, 0x1a}, // MIPI 10-bit

    {0x3037, 0x13}, // PLL root divider, bit[4], PLL pre-divider, bit[3:0]

    {0x3108, 0x01}, // PCLK root divider, bit[5:4], SCLK2x root divider, bit[3:2]

    // SCLK root divider, bit[1:0]

    {0x3630, 0x36},

    {0x3631, 0x0e},

    {0x3632, 0xe2},

    {0x3633, 0x12},

    {0x3621, 0xe0},

    {0x3704, 0xa0},

    {0x3703, 0x5a},

    {0x3715, 0x78},

    {0x3717, 0x01},

    {0x370b, 0x60},

    {0x3705, 0x1a},

    {0x3905, 0x02},

    {0x3906, 0x10},

    {0x3901, 0x0a},

    {0x3731, 0x12},

    {0x3600, 0x08}, // VCM control

    {0x3601, 0x33}, // VCM control

    {0x302d, 0x60}, // system control

    {0x3620, 0x52},

    {0x371b, 0x20},

    {0x471c, 0x50},

    {0x3a13, 0x43}, // pre-gain = 1.047x

    {0x3a18, 0x00}, // gain ceiling

    {0x3a19, 0xf8}, // gain ceiling = 15.5x

    {0x3635, 0x13},

    {0x3636, 0x03},

    {0x3634, 0x40},

    {0x3622, 0x01},

    // 50/60Hz detection 50/60Hz µÆ¹âÌõÎÆ¹ýÂË

    {0x3c01, 0x34}, // Band auto, bit[7]

    {0x3c04, 0x28}, // threshold low sum

    {0x3c05, 0x98}, // threshold high sum

    {0x3c06, 0x00}, // light meter 1 threshold[15:8]

    {0x3c07, 0x08}, // light meter 1 threshold[7:0]

    {0x3c08, 0x00}, // light meter 2 threshold[15:8]

    {0x3c09, 0x1c}, // light meter 2 threshold[7:0]

    {0x3c0a, 0x9c}, // sample number[15:8]

    {0x3c0b, 0x40}, // sample number[7:0]

    {0x3810, 0x00}, // Timing Hoffset[11:8]

    {0x3811, 0x10}, // Timing Hoffset[7:0]

    {0x3812, 0x00}, // Timing Voffset[10:8]

    {0x3708, 0x64},

    {0x4001, 0x02}, // BLC start from line 2

    {0x4005, 0x1a}, // BLC always update

    {0x3000, 0x00}, // enable blocks

    {0x3004, 0xff}, // enable clocks

    {0x300e, 0x58}, // MIPI power down, DVP enable

    {0x302e, 0x00},



    {0x4300, 0x6f}, // RGB565

    {0x501f, 0x01}, // RGB565



    {0x440e, 0x00},

    {0x5000, 0xa7}, // Lenc on, raw gamma on, BPC on, WPC on, CIP on

    // AEC target ×Ô¶¯ÆØ¹â¿ØÖÆ

    {0x3a0f, 0x30}, // stable range in high

    {0x3a10, 0x28}, // stable range in low

    {0x3a1b, 0x30}, // stable range out high

    {0x3a1e, 0x26}, // stable range out low

    {0x3a11, 0x60}, // fast zone high

    {0x3a1f, 0x14}, // fast zone low

    // Lens correction for ? ¾µÍ·²¹³¥

    {0x5800, 0x23},

    {0x5801, 0x14},

    {0x5802, 0x0f},

    {0x5803, 0x0f},

    {0x5804, 0x12},

    {0x5805, 0x26},

    {0x5806, 0x0c},

    {0x5807, 0x08},

    {0x5808, 0x05},

    {0x5809, 0x05},

    {0x580a, 0x08},

    {0x580b, 0x0d},

    {0x580c, 0x08},

    {0x580d, 0x03},

    {0x580e, 0x00},

    {0x580f, 0x00},

    {0x5810, 0x03},

    {0x5811, 0x09},

    {0x5812, 0x07},

    {0x5813, 0x03},

    {0x5814, 0x00},

    {0x5815, 0x01},

    {0x5816, 0x03},

    {0x5817, 0x08},

    {0x5818, 0x0d},

    {0x5819, 0x08},

    {0x581a, 0x05},

    {0x581b, 0x06},

    {0x581c, 0x08},

    {0x581d, 0x0e},

    {0x581e, 0x29},

    {0x581f, 0x17},

    {0x5820, 0x11},

    {0x5821, 0x11},

    {0x5822, 0x15},

    {0x5823, 0x28},

    {0x5824, 0x46},

    {0x5825, 0x26},

    {0x5826, 0x08},

    {0x5827, 0x26},

    {0x5828, 0x64},

    {0x5829, 0x26},

    {0x582a, 0x24},

    {0x582b, 0x22},

    {0x582c, 0x24},

    {0x582d, 0x24},

    {0x582e, 0x06},

    {0x582f, 0x22},

    {0x5830, 0x40},

    {0x5831, 0x42},

    {0x5832, 0x24},

    {0x5833, 0x26},

    {0x5834, 0x24},

    {0x5835, 0x22},

    {0x5836, 0x22},

    {0x5837, 0x26},

    {0x5838, 0x44},

    {0x5839, 0x24},

    {0x583a, 0x26},

    {0x583b, 0x28},

    {0x583c, 0x42},

    {0x583d, 0xce}, // lenc BR offset

    // AWB ×Ô¶¯°×Æ½ºâ

    {0x5180, 0xff}, // AWB B block

    {0x5181, 0xf2}, // AWB control

    {0x5182, 0x00}, // [7:4] max local counter, [3:0] max fast counter

    {0x5183, 0x14}, // AWB advanced

    {0x5184, 0x25},

    {0x5185, 0x24},

    {0x5186, 0x09},

    {0x5187, 0x09},

    {0x5188, 0x09},

    {0x5189, 0x75},

    {0x518a, 0x54},

    {0x518b, 0xe0},

    {0x518c, 0xb2},

    {0x518d, 0x42},

    {0x518e, 0x3d},

    {0x518f, 0x56},

    {0x5190, 0x46},

    {0x5191, 0xf8}, // AWB top limit

    {0x5192, 0x04}, // AWB bottom limit

    {0x5193, 0x70}, // red limit

    {0x5194, 0xf0}, // green limit

    {0x5195, 0xf0}, // blue limit

    {0x5196, 0x03}, // AWB control

    {0x5197, 0x01}, // local limit

    {0x5198, 0x04},

    {0x5199, 0x12},

    {0x519a, 0x04},

    {0x519b, 0x00},

    {0x519c, 0x06},

    {0x519d, 0x82},

    {0x519e, 0x38}, // AWB control

    // Gamma Ù¤ÂêÇúÏß

    {0x5480, 0x01}, // Gamma bias plus on, bit[0]

    {0x5481, 0x08},

    {0x5482, 0x14},

    {0x5483, 0x28},

    {0x5484, 0x51},

    {0x5485, 0x65},

    {0x5486, 0x71},

    {0x5487, 0x7d},

    {0x5488, 0x87},

    {0x5489, 0x91},

    {0x548a, 0x9a},

    {0x548b, 0xaa},

    {0x548c, 0xb8},

    {0x548d, 0xcd},

    {0x548e, 0xdd},

    {0x548f, 0xea},

    {0x5490, 0x1d},

    // color matrix É«²Ê¾ØÕó

    {0x5381, 0x1e}, // CMX1 for Y

    {0x5382, 0x5b}, // CMX2 for Y

    {0x5383, 0x08}, // CMX3 for Y

    {0x5384, 0x0a}, // CMX4 for U

    {0x5385, 0x7e}, // CMX5 for U

    {0x5386, 0x88}, // CMX6 for U

    {0x5387, 0x7c}, // CMX7 for V

    {0x5388, 0x6c}, // CMX8 for V

    {0x5389, 0x10}, // CMX9 for V

    {0x538a, 0x01}, // sign[9]

    {0x538b, 0x98}, // sign[8:1]

    // UV adjust UV É«²Ê±¥ºÍ¶Èµ÷Õû

    {0x5580, 0x06}, // saturation on, bit[1]

    {0x5583, 0x40},

    {0x5584, 0x10},

    {0x5589, 0x10},

    {0x558a, 0x00},

    {0x558b, 0xf8},

    {0x501d, 0x40}, // enable manual offset of contrast

    // CIP Èñ»¯ºÍ½µÔë

    {0x5300, 0x08}, // CIP sharpen MT threshold 1

    {0x5301, 0x30}, // CIP sharpen MT threshold 2

    {0x5302, 0x10}, // CIP sharpen MT offset 1

    {0x5303, 0x00}, // CIP sharpen MT offset 2

    {0x5304, 0x08}, // CIP DNS threshold 1

    {0x5305, 0x30}, // CIP DNS threshold 2

    {0x5306, 0x08}, // CIP DNS offset 1

    {0x5307, 0x16}, // CIP DNS offset 2

    {0x5309, 0x08}, // CIP sharpen TH threshold 1

    {0x530a, 0x30}, // CIP sharpen TH threshold 2

    {0x530b, 0x04}, // CIP sharpen TH offset 1

    {0x530c, 0x06}, // CIP sharpen TH offset 2

    {0x5025, 0x00},

    {0x3008, 0x02}, // wake up from standby, bit[6]

   

    //{0x503d, 0x80},//²âÊÔ²ÊÌõ

    //{0x4741, 0x00},
};
const uint16_t RGB565_QVGA[][2]=

{

    // input clock 24Mhz, PCLK 45.6Mhz

    {0x3035, 0x41}, // PLL

    {0x3036, 0x72}, // PLL

    {0x3c07, 0x08}, // light meter 1 threshold[7:0]

    {0x3820, 0x42}, // flip

    {0x3821, 0x00}, // mirror

    {0x3814, 0x31}, // timing X inc

    {0x3815, 0x31}, // timing Y inc

    {0x3800, 0x00}, // HS

    {0x3801, 0x00}, // HS

    {0x3802, 0x00}, // VS

    {0x3803, 0xbe}, // VS

    {0x3804, 0x0a}, // HW (HE)

    {0x3805, 0x3f}, // HW (HE)

    {0x3806, 0x06}, // VH (VE)

    {0x3807, 0xe4}, // VH (VE)



    {0x3808, 0x01}, // DVPHO = 320

    {0x3809, 0x40}, // DVP HO

    {0x380a, 0x00}, // DVPVO = 240

    {0x380b, 0xf0}, // DVPVO

    {0x3810, 0x00}, // H offset = 16

    {0x3811, 0x10}, // H offset

    {0x3812, 0x00}, // V offset = 4

    {0x3813, 0x04}, // V offset

    

    {0x380c, 0x07}, // HTS

    {0x380d, 0x69}, // HTS

    {0x380e, 0x03}, // VTS

    {0x380f, 0x21}, // VTS



    {0x3618, 0x00},

    {0x3612, 0x29},

    {0x3709, 0x52},

    {0x370c, 0x03},

    {0x3a02, 0x09}, // 60Hz max exposure, night mode 5fps

    {0x3a03, 0x63}, // 60Hz max exposure



    {0x3a14, 0x09}, // 50Hz max exposure, night mode 5fps

    {0x3a15, 0x63}, // 50Hz max exposure

    {0x4004, 0x02}, // BLC line number

    {0x3002, 0x1c}, // reset JFIFO, SFIFO, JPG

    {0x3006, 0xc3}, // disable clock of JPEG2x, JPEG

    {0x4713, 0x03}, // JPEG mode 3

    {0x4407, 0x04}, // Quantization sacle

    {0x460b, 0x35},

    {0x460c, 0x22},

    {0x4837, 0x22}, // MIPI global timing

    {0x3824, 0x02}, // PCLK manual divider

    {0x5001, 0xa3}, // SDE on, CMX on, AWB on

    {0x3503, 0x00}, // AEC/AGC on//	  /* Initialize OV5640 */

};
/** @defgroup OV5640_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */
/** @defgroup OV5640_Private_Variables
  * @{
  */

OV5640_CAMERA_Drv_t   OV5640_CAMERA_Driver =
{
  OV5640_Init,
  OV5640_DeInit,
  OV5640_ReadID,
  OV5640_GetCapabilities,
  OV5640_SetLightMode,
  OV5640_SetColorEffect,
  OV5640_SetBrightness,
  OV5640_SetSaturation,
  OV5640_SetContrast,
  OV5640_SetHueDegree,
  OV5640_MirrorFlipConfig,
  OV5640_ZoomConfig,
  OV5640_SetResolution,
  OV5640_GetResolution,
  OV5640_SetPixelFormat,
  OV5640_GetPixelFormat,
  OV5640_NightModeConfig
};

/**
  * @}
  */

/** @defgroup OV5640_Private_Functions_Prototypes Private Functions Prototypes
  * @{
  */
static int32_t OV5640_ReadRegWrap(void *handle, uint16_t Reg, uint8_t* Data, uint16_t Length);
static int32_t OV5640_WriteRegWrap(void *handle, uint16_t Reg, uint8_t* Data, uint16_t Length);
static int32_t OV5640_Delay(OV5640_Object_t *pObj, uint32_t Delay);

/**
  * @}
  */

/** @defgroup OV5640_Exported_Functions OV5640 Exported Functions
  * @{
  */
/**
  * @brief  Register component IO bus
  * @param  Component object pointer
  * @retval Component status
  */
int32_t OV5640_RegisterBusIO (OV5640_Object_t *pObj, OV5640_IO_t *pIO)
{
  int32_t ret;

  if (pObj == NULL)
  {
    ret = OV5640_ERROR;
  }
  else
  {
    pObj->IO.Init      = pIO->Init;
    pObj->IO.DeInit    = pIO->DeInit;
    pObj->IO.Address   = pIO->Address;
    pObj->IO.WriteReg  = pIO->WriteReg;
    pObj->IO.ReadReg   = pIO->ReadReg;
    pObj->IO.GetTick   = pIO->GetTick;

    pObj->Ctx.ReadReg  = OV5640_ReadRegWrap;
    pObj->Ctx.WriteReg = OV5640_WriteRegWrap;
    pObj->Ctx.handle   = pObj;

    if(pObj->IO.Init != NULL)
    {
      ret = pObj->IO.Init();
    }
    else
    {
      ret = OV5640_ERROR;
    }
  }

  return ret;
}

/**
  * @brief  Initializes the OV5640 CAMERA component.
  * @param  pObj  pointer to component object
  * @param  Resolution  Camera resolution
  * @param  PixelFormat pixel format to be configured
  * @retval Component status
  */
int32_t OV5640_Init(OV5640_Object_t *pObj, uint32_t Resolution, uint32_t PixelFormat)
{
  //uint32_t index;
  int32_t ret = OV5640_OK;

  /* Initialization sequence for OV5640 */
  /*
  static const uint16_t OV5640_Common[][2] =
  {
    {OV5640_SCCB_SYSTEM_CTRL1, 0x11},
    {OV5640_SYSTEM_CTROL0, 0x82},
    {OV5640_SCCB_SYSTEM_CTRL1, 0x03},
    {OV5640_PAD_OUTPUT_ENABLE01, 0xFF},
    {OV5640_PAD_OUTPUT_ENABLE02, 0xf3},
    {OV5640_SC_PLL_CONTRL0, 0x18},
    {OV5640_SYSTEM_CTROL0, 0x02},
    {OV5640_SC_PLL_CONTRL1, 0x41},
    {OV5640_SC_PLL_CONTRL2, 0x72},        //modified by @LS.org
    {OV5640_SC_PLL_CONTRL3, 0x13},
    {OV5640_SYSTEM_ROOT_DIVIDER, 0x01},
    {0x3630, 0x36},
    {0x3631, 0x0e},
    {0x3632, 0xe2},
    {0x3633, 0x12},
    {0x3621, 0xe0},
    {0x3704, 0xa0},
    {0x3703, 0x5a},
    {0x3715, 0x78},
    {0x3717, 0x01},
    {0x370b, 0x60},
    {0x3705, 0x1a},
    {0x3905, 0x02},
    {0x3906, 0x10},
    {0x3901, 0x0a},
    {0x3731, 0x12},
    {0x3600, 0x08},
    {0x3601, 0x33},
    {0x302d, 0x60},
    {0x3620, 0x52},
    {0x371b, 0x20},
    {0x471c, 0x50},
    {OV5640_AEC_CTRL13, 0x43},
    {OV5640_AEC_GAIN_CEILING_HIGH, 0x00},
    {OV5640_AEC_GAIN_CEILING_LOW, 0xf8},
    {0x3635, 0x13},
    {0x3636, 0x03},
    {0x3634, 0x40},
    {0x3622, 0x01},
    {OV5640_5060HZ_CTRL01, 0x34},
    {OV5640_5060HZ_CTRL04, 0x28},
    {OV5640_5060HZ_CTRL05, 0x98},
    {OV5640_LIGHTMETER1_TH_HIGH, 0x00},
    {OV5640_LIGHTMETER1_TH_LOW, 0x00},
    {OV5640_LIGHTMETER2_TH_HIGH, 0x01},
    {OV5640_LIGHTMETER2_TH_LOW, 0x2c},
    {OV5640_SAMPLE_NUMBER_HIGH, 0x9c},
    {OV5640_SAMPLE_NUMBER_LOW, 0x40},
    {OV5640_TIMING_TC_REG20, 0x06},
    {OV5640_TIMING_TC_REG21, 0x00},
    {OV5640_TIMING_X_INC, 0x31},
    {OV5640_TIMING_Y_INC, 0x31},
    {OV5640_TIMING_HS_HIGH, 0x00},
    {OV5640_TIMING_HS_LOW, 0x00},
    {OV5640_TIMING_VS_HIGH, 0x00},
    {OV5640_TIMING_VS_LOW, 0x04},
    {OV5640_TIMING_HW_HIGH, 0x0a},
    {OV5640_TIMING_HW_LOW, 0x3f},
    {OV5640_TIMING_VH_HIGH, 0x07},
    {OV5640_TIMING_VH_LOW, 0x9b},
    {OV5640_TIMING_DVPHO_HIGH, 0x01},
    {OV5640_TIMING_DVPHO_LOW, 0x40},
    {OV5640_TIMING_DVPVO_HIGH, 0x00},
    {OV5640_TIMING_DVPVO_LOW, 0xF0},
    {OV5640_TIMING_HTS_HIGH, 0x07},
    {OV5640_TIMING_HTS_LOW, 0x68},
    {OV5640_TIMING_VTS_HIGH, 0x03},
    {OV5640_TIMING_VTS_LOW, 0xd8},
    {OV5640_TIMING_HOFFSET_HIGH, 0x00},
    {OV5640_TIMING_HOFFSET_LOW, 0x10},
    {OV5640_TIMING_VOFFSET_HIGH, 0x00},
    {OV5640_TIMING_VOFFSET_LOW, 0x06},
    {0x3618, 0x00},
    {0x3612, 0x29},
    {0x3708, 0x64},
    {0x3709, 0x52},
    {0x370c, 0x03},
    {OV5640_AEC_CTRL02, 0x03},
    {OV5640_AEC_CTRL03, 0xd8},
    {OV5640_AEC_B50_STEP_HIGH, 0x01},
    {OV5640_AEC_B50_STEP_LOW, 0x27},
    {OV5640_AEC_B60_STEP_HIGH, 0x00},
    {OV5640_AEC_B60_STEP_LOW, 0xf6},
    {OV5640_AEC_CTRL0E, 0x03},
    {OV5640_AEC_CTRL0D, 0x04},
    {OV5640_AEC_MAX_EXPO_HIGH, 0x03},
    {OV5640_AEC_MAX_EXPO_LOW, 0xd8},
    {OV5640_BLC_CTRL01, 0x02},
    {OV5640_BLC_CTRL04, 0x02},
    {OV5640_SYSREM_RESET00, 0x00},
    {OV5640_SYSREM_RESET02, 0x1c},
    {OV5640_CLOCK_ENABLE00, 0xff},
    {OV5640_CLOCK_ENABLE02, 0xc3},
    {OV5640_MIPI_CONTROL00, 0x58},
    {0x302e, 0x00},
    {OV5640_POLARITY_CTRL, 0x22},
    {OV5640_FORMAT_CTRL00, 0x6F},
    {OV5640_FORMAT_MUX_CTRL, 0x01},
    {OV5640_JPG_MODE_SELECT, 0x03},
    {OV5640_JPEG_CTRL07, 0x04},
    {0x440e, 0x00},
    {0x460b, 0x35},
    {0x460c, 0x23},
    {OV5640_PCLK_PERIOD, 0x22},
    {0x3824, 0x02},
    {OV5640_ISP_CONTROL00, 0xa7},
    {OV5640_ISP_CONTROL01, 0xa3},
    {OV5640_AWB_CTRL00, 0xff},
    {OV5640_AWB_CTRL01, 0xf2},
    {OV5640_AWB_CTRL02, 0x00},
    {OV5640_AWB_CTRL03, 0x14},
    {OV5640_AWB_CTRL04, 0x25},
    {OV5640_AWB_CTRL05, 0x24},
    {OV5640_AWB_CTRL06, 0x09},
    {OV5640_AWB_CTRL07, 0x09},
    {OV5640_AWB_CTRL08, 0x09},
    {OV5640_AWB_CTRL09, 0x75},
    {OV5640_AWB_CTRL10, 0x54},
    {OV5640_AWB_CTRL11, 0xe0},
    {OV5640_AWB_CTRL12, 0xb2},
    {OV5640_AWB_CTRL13, 0x42},
    {OV5640_AWB_CTRL14, 0x3d},
    {OV5640_AWB_CTRL15, 0x56},
    {OV5640_AWB_CTRL16, 0x46},
    {OV5640_AWB_CTRL17, 0xf8},
    {OV5640_AWB_CTRL18, 0x04},
    {OV5640_AWB_CTRL19, 0x70},
    {OV5640_AWB_CTRL20, 0xf0},
    {OV5640_AWB_CTRL21, 0xf0},
    {OV5640_AWB_CTRL22, 0x03},
    {OV5640_AWB_CTRL23, 0x01},
    {OV5640_AWB_CTRL24, 0x04},
    {OV5640_AWB_CTRL25, 0x12},
    {OV5640_AWB_CTRL26, 0x04},
    {OV5640_AWB_CTRL27, 0x00},
    {OV5640_AWB_CTRL28, 0x06},
    {OV5640_AWB_CTRL29, 0x82},
    {OV5640_AWB_CTRL30, 0x38},
    {OV5640_CMX1        , 0x1e},
    {OV5640_CMX2        , 0x5b},
    {OV5640_CMX3        , 0x08},
    {OV5640_CMX4        , 0x0a},
    {OV5640_CMX5        , 0x7e},
    {OV5640_CMX6        , 0x88},
    {OV5640_CMX7        , 0x7c},
    {OV5640_CMX8        , 0x6c},
    {OV5640_CMX9        , 0x10},
    {OV5640_CMXSIGN_HIGH, 0x01},
    {OV5640_CMXSIGN_LOW , 0x98},
    {OV5640_CIP_SHARPENMT_TH1    , 0x08},
    {OV5640_CIP_SHARPENMT_TH2    , 0x30},
    {OV5640_CIP_SHARPENMT_OFFSET1, 0x10},
    {OV5640_CIP_SHARPENMT_OFFSET2, 0x00},
    {OV5640_CIP_DNS_TH1          , 0x08},
    {OV5640_CIP_DNS_TH2          , 0x30},
    {OV5640_CIP_DNS_OFFSET1      , 0x08},
    {OV5640_CIP_DNS_OFFSET2      , 0x16},
    {OV5640_CIP_CTRL             , 0x08},
    {OV5640_CIP_SHARPENTH_TH1    , 0x30},
    {OV5640_CIP_SHARPENTH_TH2    , 0x04},
    {OV5640_CIP_SHARPENTH_OFFSET1, 0x06},
    {OV5640_GAMMA_CTRL00, 0x01},
    {OV5640_GAMMA_YST00, 0x08},
    {OV5640_GAMMA_YST01, 0x14},
    {OV5640_GAMMA_YST02, 0x28},
    {OV5640_GAMMA_YST03, 0x51},
    {OV5640_GAMMA_YST04, 0x65},
    {OV5640_GAMMA_YST05, 0x71},
    {OV5640_GAMMA_YST06, 0x7d},
    {OV5640_GAMMA_YST07, 0x87},
    {OV5640_GAMMA_YST08, 0x91},
    {OV5640_GAMMA_YST09, 0x9a},
    {OV5640_GAMMA_YST0A, 0xaa},
    {OV5640_GAMMA_YST0B, 0xb8},
    {OV5640_GAMMA_YST0C, 0xcd},
    {OV5640_GAMMA_YST0D, 0xdd},
    {OV5640_GAMMA_YST0E, 0xea},
    {OV5640_GAMMA_YST0F, 0x1d},
    {OV5640_SDE_CTRL0, 0x02},
    {OV5640_SDE_CTRL3, 0x40},
    {OV5640_SDE_CTRL4, 0x10},
    {OV5640_SDE_CTRL9, 0x10},
    {OV5640_SDE_CTRL10, 0x00},
    {OV5640_SDE_CTRL11, 0xf8},
    {OV5640_GMTRX00       , 0x23},
    {OV5640_GMTRX01       , 0x14},
    {OV5640_GMTRX02       , 0x0f},
    {OV5640_GMTRX03       , 0x0f},
    {OV5640_GMTRX04       , 0x12},
    {OV5640_GMTRX05       , 0x26},
    {OV5640_GMTRX10       , 0x0c},
    {OV5640_GMTRX11       , 0x08},
    {OV5640_GMTRX12       , 0x05},
    {OV5640_GMTRX13       , 0x05},
    {OV5640_GMTRX14       , 0x08},
    {OV5640_GMTRX15       , 0x0d},
    {OV5640_GMTRX20       , 0x08},
    {OV5640_GMTRX21       , 0x03},
    {OV5640_GMTRX22       , 0x00},
    {OV5640_GMTRX23       , 0x00},
    {OV5640_GMTRX24       , 0x03},
    {OV5640_GMTRX25       , 0x09},
    {OV5640_GMTRX30       , 0x07},
    {OV5640_GMTRX31       , 0x03},
    {OV5640_GMTRX32       , 0x00},
    {OV5640_GMTRX33       , 0x01},
    {OV5640_GMTRX34       , 0x03},
    {OV5640_GMTRX35       , 0x08},
    {OV5640_GMTRX40       , 0x0d},
    {OV5640_GMTRX41       , 0x08},
    {OV5640_GMTRX42       , 0x05},
    {OV5640_GMTRX43       , 0x06},
    {OV5640_GMTRX44       , 0x08},
    {OV5640_GMTRX45       , 0x0e},
    {OV5640_GMTRX50       , 0x29},
    {OV5640_GMTRX51       , 0x17},
    {OV5640_GMTRX52       , 0x11},
    {OV5640_GMTRX53       , 0x11},
    {OV5640_GMTRX54       , 0x15},
    {OV5640_GMTRX55       , 0x28},
    {OV5640_BRMATRX00     , 0x46},
    {OV5640_BRMATRX01     , 0x26},
    {OV5640_BRMATRX02     , 0x08},
    {OV5640_BRMATRX03     , 0x26},
    {OV5640_BRMATRX04     , 0x64},
    {OV5640_BRMATRX05     , 0x26},
    {OV5640_BRMATRX06     , 0x24},
    {OV5640_BRMATRX07     , 0x22},
    {OV5640_BRMATRX08     , 0x24},
    {OV5640_BRMATRX09     , 0x24},
    {OV5640_BRMATRX20     , 0x06},
    {OV5640_BRMATRX21     , 0x22},
    {OV5640_BRMATRX22     , 0x40},
    {OV5640_BRMATRX23     , 0x42},
    {OV5640_BRMATRX24     , 0x24},
    {OV5640_BRMATRX30     , 0x26},
    {OV5640_BRMATRX31     , 0x24},
    {OV5640_BRMATRX32     , 0x22},
    {OV5640_BRMATRX33     , 0x22},
    {OV5640_BRMATRX34     , 0x26},
    {OV5640_BRMATRX40     , 0x44},
    {OV5640_BRMATRX41     , 0x24},
    {OV5640_BRMATRX42     , 0x26},
    {OV5640_BRMATRX43     , 0x28},
    {OV5640_BRMATRX44     , 0x42},
    {OV5640_LENC_BR_OFFSET, 0xce},
    {0x5025, 0x00},
    {OV5640_AEC_CTRL0F, 0x30},
    {OV5640_AEC_CTRL10, 0x28},
    {OV5640_AEC_CTRL1B, 0x30},
    {OV5640_AEC_CTRL1E, 0x26},
    {OV5640_AEC_CTRL11, 0x60},
    {OV5640_AEC_CTRL1F, 0x14},
    {OV5640_SYSTEM_CTROL0, 0x02},
  }; 
  uint8_t tmp;

  if(pObj->IsInitialized == 0U)
  {
    // Check if resolution is supported
    if((Resolution > OV5640_R800x480) || ((PixelFormat != OV5640_RGB565) && (PixelFormat != OV5640_YUV422)))
    {
      ret = OV5640_ERROR;
    }
    else
    {
      // Set common parameters for all resolutions 
      for(index=0; index< (sizeof(OV5640_Common)/4U) ; index++)
      {
        if(ret != OV5640_ERROR)
        {
          tmp = (uint8_t)OV5640_Common[index][1];

          if(ov5640_write_reg(&pObj->Ctx, OV5640_Common[index][0], &tmp, 1) != OV5640_OK)
          {
            ret = OV5640_ERROR;
          }
        }
      }

      if(ret == OV5640_OK)
      {
        // Set specific parameters for each resolution 
        if(OV5640_SetResolution(pObj, Resolution)!= OV5640_OK)
        {
          ret = OV5640_ERROR;
        }// Set specific parameters for each pixel format 
        else if(OV5640_SetPixelFormat(pObj, PixelFormat)!= OV5640_OK)
        {
          ret = OV5640_ERROR;
        }
        else
        {
          pObj->IsInitialized = 1U;
        }
      }
    } 
   }
  */

   static const uint16_t OV5640_Common[][2] =

  {

    {OV5640_SCCB_SYSTEM_CTRL1, 0x11},

    {OV5640_SYSTEM_CTROL0, 0x82},

    {OV5640_SCCB_SYSTEM_CTRL1, 0x03},

    {OV5640_PAD_OUTPUT_ENABLE01, 0xFF},

    {OV5640_PAD_OUTPUT_ENABLE02, 0xf3},

    {OV5640_SC_PLL_CONTRL0, 0x18},

    {OV5640_SYSTEM_CTROL0, 0x02},

    {OV5640_SC_PLL_CONTRL1, 0x41},

    {OV5640_SC_PLL_CONTRL2, 0x72},        //modified by @LS.org

    {OV5640_SC_PLL_CONTRL3, 0x13},

    {OV5640_SYSTEM_ROOT_DIVIDER, 0x01},

    {0x3630, 0x36},

    {0x3631, 0x0e},

    {0x3632, 0xe2},

    {0x3633, 0x12},

    {0x3621, 0xe0},

    {0x3704, 0xa0},

    {0x3703, 0x5a},

    {0x3715, 0x78},

    {0x3717, 0x01},

    {0x370b, 0x60},

    {0x3705, 0x1a},

    {0x3905, 0x02},

    {0x3906, 0x10},

    {0x3901, 0x0a},

    {0x3731, 0x12},

    {0x3600, 0x08},

    {0x3601, 0x33},

    {0x302d, 0x60},

    {0x3620, 0x52},

    {0x371b, 0x20},

    {0x471c, 0x50},

    {OV5640_AEC_CTRL13, 0x43},

    {OV5640_AEC_GAIN_CEILING_HIGH, 0x00},

    {OV5640_AEC_GAIN_CEILING_LOW, 0xf8},

    {0x3635, 0x13},

    {0x3636, 0x03},

    {0x3634, 0x40},

    {0x3622, 0x01},

    {OV5640_5060HZ_CTRL01, 0x34},

    {OV5640_5060HZ_CTRL04, 0x28},

    {OV5640_5060HZ_CTRL05, 0x98},

    {OV5640_LIGHTMETER1_TH_HIGH, 0x00},

    {OV5640_LIGHTMETER1_TH_LOW, 0x00},

    {OV5640_LIGHTMETER2_TH_HIGH, 0x01},

    {OV5640_LIGHTMETER2_TH_LOW, 0x2c},

    {OV5640_SAMPLE_NUMBER_HIGH, 0x9c},

    {OV5640_SAMPLE_NUMBER_LOW, 0x40},

    {OV5640_TIMING_TC_REG20, 0x06},

    {OV5640_TIMING_TC_REG21, 0x00},

    {OV5640_TIMING_X_INC, 0x31},

    {OV5640_TIMING_Y_INC, 0x31},

    {OV5640_TIMING_HS_HIGH, 0x00},

    {OV5640_TIMING_HS_LOW, 0x00},

    {OV5640_TIMING_VS_HIGH, 0x00},

    {OV5640_TIMING_VS_LOW, 0x04},

    {OV5640_TIMING_HW_HIGH, 0x0a},

    {OV5640_TIMING_HW_LOW, 0x3f},

    {OV5640_TIMING_VH_HIGH, 0x07},

    {OV5640_TIMING_VH_LOW, 0x9b},

    {OV5640_TIMING_DVPHO_HIGH, 0x01},

    {OV5640_TIMING_DVPHO_LOW, 0x40},

    {OV5640_TIMING_DVPVO_HIGH, 0x00},

    {OV5640_TIMING_DVPVO_LOW, 0xF0},

    {OV5640_TIMING_HTS_HIGH, 0x07},

    {OV5640_TIMING_HTS_LOW, 0x68},

    {OV5640_TIMING_VTS_HIGH, 0x03},

    {OV5640_TIMING_VTS_LOW, 0xd8},

    {OV5640_TIMING_HOFFSET_HIGH, 0x00},

    {OV5640_TIMING_HOFFSET_LOW, 0x10},

    {OV5640_TIMING_VOFFSET_HIGH, 0x00},

    {OV5640_TIMING_VOFFSET_LOW, 0x06},

    {0x3618, 0x00},

    {0x3612, 0x29},

    {0x3708, 0x64},

    {0x3709, 0x52},

    {0x370c, 0x03},

    {OV5640_AEC_CTRL02, 0x03},

    {OV5640_AEC_CTRL03, 0xd8},

    {OV5640_AEC_B50_STEP_HIGH, 0x01},

    {OV5640_AEC_B50_STEP_LOW, 0x27},

    {OV5640_AEC_B60_STEP_HIGH, 0x00},

    {OV5640_AEC_B60_STEP_LOW, 0xf6},

    {OV5640_AEC_CTRL0E, 0x03},

    {OV5640_AEC_CTRL0D, 0x04},

    {OV5640_AEC_MAX_EXPO_HIGH, 0x03},

    {OV5640_AEC_MAX_EXPO_LOW, 0xd8},

    {OV5640_BLC_CTRL01, 0x02},

    {OV5640_BLC_CTRL04, 0x02},

    {OV5640_SYSREM_RESET00, 0x00},

    {OV5640_SYSREM_RESET02, 0x1c},

    {OV5640_CLOCK_ENABLE00, 0xff},

    {OV5640_CLOCK_ENABLE02, 0xc3},

    {OV5640_MIPI_CONTROL00, 0x58},

    {0x302e, 0x00},

    {OV5640_POLARITY_CTRL, 0x22},

    {OV5640_FORMAT_CTRL00, 0x6F},

    {OV5640_FORMAT_MUX_CTRL, 0x01},

    {OV5640_JPG_MODE_SELECT, 0x03},

    {OV5640_JPEG_CTRL07, 0x04},

    {0x440e, 0x00},

    {0x460b, 0x35},

    {0x460c, 0x23},

    {OV5640_PCLK_PERIOD, 0x22},

    {0x3824, 0x02},

    {OV5640_ISP_CONTROL00, 0xa7},

    {OV5640_ISP_CONTROL01, 0xa3},

    {OV5640_AWB_CTRL00, 0xff},

    {OV5640_AWB_CTRL01, 0xf2},

    {OV5640_AWB_CTRL02, 0x00},

    {OV5640_AWB_CTRL03, 0x14},

    {OV5640_AWB_CTRL04, 0x25},

    {OV5640_AWB_CTRL05, 0x24},

    {OV5640_AWB_CTRL06, 0x09},

    {OV5640_AWB_CTRL07, 0x09},

    {OV5640_AWB_CTRL08, 0x09},

    {OV5640_AWB_CTRL09, 0x75},

    {OV5640_AWB_CTRL10, 0x54},

    {OV5640_AWB_CTRL11, 0xe0},

    {OV5640_AWB_CTRL12, 0xb2},

    {OV5640_AWB_CTRL13, 0x42},

    {OV5640_AWB_CTRL14, 0x3d},

    {OV5640_AWB_CTRL15, 0x56},

    {OV5640_AWB_CTRL16, 0x46},

    {OV5640_AWB_CTRL17, 0xf8},

    {OV5640_AWB_CTRL18, 0x04},

    {OV5640_AWB_CTRL19, 0x70},

    {OV5640_AWB_CTRL20, 0xf0},

    {OV5640_AWB_CTRL21, 0xf0},

    {OV5640_AWB_CTRL22, 0x03},

    {OV5640_AWB_CTRL23, 0x01},

    {OV5640_AWB_CTRL24, 0x04},

    {OV5640_AWB_CTRL25, 0x12},

    {OV5640_AWB_CTRL26, 0x04},

    {OV5640_AWB_CTRL27, 0x00},

    {OV5640_AWB_CTRL28, 0x06},

    {OV5640_AWB_CTRL29, 0x82},

    {OV5640_AWB_CTRL30, 0x38},

    {OV5640_CMX1        , 0x1e},

    {OV5640_CMX2        , 0x5b},

    {OV5640_CMX3        , 0x08},

    {OV5640_CMX4        , 0x0a},

    {OV5640_CMX5        , 0x7e},

    {OV5640_CMX6        , 0x88},

    {OV5640_CMX7        , 0x7c},

    {OV5640_CMX8        , 0x6c},

    {OV5640_CMX9        , 0x10},

    {OV5640_CMXSIGN_HIGH, 0x01},

    {OV5640_CMXSIGN_LOW , 0x98},

    {OV5640_CIP_SHARPENMT_TH1    , 0x08},

    {OV5640_CIP_SHARPENMT_TH2    , 0x30},

    {OV5640_CIP_SHARPENMT_OFFSET1, 0x10},

    {OV5640_CIP_SHARPENMT_OFFSET2, 0x00},

    {OV5640_CIP_DNS_TH1          , 0x08},

    {OV5640_CIP_DNS_TH2          , 0x30},

    {OV5640_CIP_DNS_OFFSET1      , 0x08},

    {OV5640_CIP_DNS_OFFSET2      , 0x16},

    {OV5640_CIP_CTRL             , 0x08},

    {OV5640_CIP_SHARPENTH_TH1    , 0x30},

    {OV5640_CIP_SHARPENTH_TH2    , 0x04},

    {OV5640_CIP_SHARPENTH_OFFSET1, 0x06},

    {OV5640_GAMMA_CTRL00, 0x01},

    {OV5640_GAMMA_YST00, 0x08},

    {OV5640_GAMMA_YST01, 0x14},

    {OV5640_GAMMA_YST02, 0x28},

    {OV5640_GAMMA_YST03, 0x51},

    {OV5640_GAMMA_YST04, 0x65},

    {OV5640_GAMMA_YST05, 0x71},

    {OV5640_GAMMA_YST06, 0x7d},

    {OV5640_GAMMA_YST07, 0x87},

    {OV5640_GAMMA_YST08, 0x91},

    {OV5640_GAMMA_YST09, 0x9a},

    {OV5640_GAMMA_YST0A, 0xaa},

    {OV5640_GAMMA_YST0B, 0xb8},

    {OV5640_GAMMA_YST0C, 0xcd},

    {OV5640_GAMMA_YST0D, 0xdd},

    {OV5640_GAMMA_YST0E, 0xea},

    {OV5640_GAMMA_YST0F, 0x1d},

    {OV5640_SDE_CTRL0, 0x02},

    {OV5640_SDE_CTRL3, 0x40},

    {OV5640_SDE_CTRL4, 0x10},

    {OV5640_SDE_CTRL9, 0x10},

    {OV5640_SDE_CTRL10, 0x00},

    {OV5640_SDE_CTRL11, 0xf8},

    {OV5640_GMTRX00       , 0x23},

    {OV5640_GMTRX01       , 0x14},

    {OV5640_GMTRX02       , 0x0f},

    {OV5640_GMTRX03       , 0x0f},

    {OV5640_GMTRX04       , 0x12},

    {OV5640_GMTRX05       , 0x26},

    {OV5640_GMTRX10       , 0x0c},

    {OV5640_GMTRX11       , 0x08},

    {OV5640_GMTRX12       , 0x05},

    {OV5640_GMTRX13       , 0x05},

    {OV5640_GMTRX14       , 0x08},

    {OV5640_GMTRX15       , 0x0d},

    {OV5640_GMTRX20       , 0x08},

    {OV5640_GMTRX21       , 0x03},

    {OV5640_GMTRX22       , 0x00},

    {OV5640_GMTRX23       , 0x00},

    {OV5640_GMTRX24       , 0x03},

    {OV5640_GMTRX25       , 0x09},

    {OV5640_GMTRX30       , 0x07},

    {OV5640_GMTRX31       , 0x03},

    {OV5640_GMTRX32       , 0x00},

    {OV5640_GMTRX33       , 0x01},

    {OV5640_GMTRX34       , 0x03},

    {OV5640_GMTRX35       , 0x08},

    {OV5640_GMTRX40       , 0x0d},

    {OV5640_GMTRX41       , 0x08},

    {OV5640_GMTRX42       , 0x05},

    {OV5640_GMTRX43       , 0x06},

    {OV5640_GMTRX44       , 0x08},

    {OV5640_GMTRX45       , 0x0e},

    {OV5640_GMTRX50       , 0x29},

    {OV5640_GMTRX51       , 0x17},

    {OV5640_GMTRX52       , 0x11},

    {OV5640_GMTRX53       , 0x11},

    {OV5640_GMTRX54       , 0x15},

    {OV5640_GMTRX55       , 0x28},

    {OV5640_BRMATRX00     , 0x46},

    {OV5640_BRMATRX01     , 0x26},

    {OV5640_BRMATRX02     , 0x08},

    {OV5640_BRMATRX03     , 0x26},

    {OV5640_BRMATRX04     , 0x64},

    {OV5640_BRMATRX05     , 0x26},

    {OV5640_BRMATRX06     , 0x24},

    {OV5640_BRMATRX07     , 0x22},

    {OV5640_BRMATRX08     , 0x24},

    {OV5640_BRMATRX09     , 0x24},

    {OV5640_BRMATRX20     , 0x06},

    {OV5640_BRMATRX21     , 0x22},

    {OV5640_BRMATRX22     , 0x40},

    {OV5640_BRMATRX23     , 0x42},

    {OV5640_BRMATRX24     , 0x24},

    {OV5640_BRMATRX30     , 0x26},

    {OV5640_BRMATRX31     , 0x24},

    {OV5640_BRMATRX32     , 0x22},

    {OV5640_BRMATRX33     , 0x22},

    {OV5640_BRMATRX34     , 0x26},

    {OV5640_BRMATRX40     , 0x44},

    {OV5640_BRMATRX41     , 0x24},

    {OV5640_BRMATRX42     , 0x26},

    {OV5640_BRMATRX43     , 0x28},

    {OV5640_BRMATRX44     , 0x42},

    {OV5640_LENC_BR_OFFSET, 0xce},

    {0x5025, 0x00},

    {OV5640_AEC_CTRL0F, 0x30},

    {OV5640_AEC_CTRL10, 0x28},

    {OV5640_AEC_CTRL1B, 0x30},

    {OV5640_AEC_CTRL1E, 0x26},

    {OV5640_AEC_CTRL11, 0x60},

    {OV5640_AEC_CTRL1F, 0x14},

    {OV5640_SYSTEM_CTROL0, 0x02},

  };

	uint16_t index;
	uint8_t tmp;
  for(index=0; index<(sizeof(OV5640_Common)/4U); index++)
  {
     tmp = (uint8_t)OV5640_Common[index][1];
     ov5640_write_reg(&pObj->Ctx, OV5640_Common[index][0], &tmp, 1);
	}						

  OV5640_RGB565_Mode(pObj);
    
  return ret;
}

void OV5640_RGB565_Mode(OV5640_Object_t *pObj)
{
  uint16_t index;
  uint8_t tmp;

  for(index = 0;index < (sizeof(RGB565_Init) / 4); index++)
	{
		//OV5640_WR_Reg(ov5640_rgb565_reg_tbl[i][0],ov5640_rgb565_reg_tbl[i][1]); 
		  tmp = (uint8_t)RGB565_Init[index][1];
    //OV5640_WR_Reg(RGB565_Init[i][0], RGB565_Init[i][1]); 
      ov5640_write_reg(&pObj->Ctx, RGB565_Init[index][0], &tmp, 1);
	  } 
	
  for(index = 0; index < (sizeof(RGB565_QVGA) / 4); index ++)
  {
    //OV5640_WR_Reg(RGB565_QVGA[i][0], RGB565_QVGA[i][1]);
    	tmp = (uint8_t)RGB565_QVGA[index][1];
    //OV5640_WR_Reg(RGB565_Init[i][0], RGB565_Init[i][1]); 
      ov5640_write_reg(&pObj->Ctx, RGB565_QVGA[index][0], &tmp, 1);
    }



}
/**
  * @brief  De-initializes the camera sensor.
  * @param  pObj  pointer to component object
  * @retval Component status
  */
int32_t OV5640_DeInit(OV5640_Object_t *pObj)
{
  if(pObj->IsInitialized == 1U)
  {
    /* De-initialize camera sensor interface */
    pObj->IsInitialized = 0U;
  }

  return OV5640_OK;
}

/**
  * @brief  Set OV5640 camera Pixel Format.
  * @param  pObj  pointer to component object
  * @param  PixelFormat pixel format to be configured
  * @retval Component status
  */
int32_t OV5640_SetPixelFormat(OV5640_Object_t *pObj, uint32_t PixelFormat)
{
  int32_t ret = OV5640_OK;
  uint32_t index;
  uint8_t tmp;

  /* Initialization sequence for RGB565 pixel format */
  static const uint16_t OV5640_PF_RGB565[][2]=
  {
    /*  SET PIXEL FORMAT: RGB565 */
    {OV5640_FORMAT_CTRL00, 0x6F},
    {OV5640_POLARITY_CTRL, 0x22},
    {OV5640_FORMAT_MUX_CTRL, 0x01},
  };

  /* Initialization sequence for YUV422 pixel format */
  static const uint16_t OV5640_PF_YUV422[][2]=
  {
    /*  SET PIXEL FORMAT: YUV422 */
    {OV5640_FORMAT_CTRL00, 0x3F},
    {OV5640_POLARITY_CTRL, 0x22},
    {OV5640_FORMAT_MUX_CTRL, 0x00},
  };

  /* Check if PixelFormat is supported */
  if((PixelFormat != OV5640_RGB565) && (PixelFormat != OV5640_YUV422))
  {
    /* Pixel format not supported */
    ret = OV5640_ERROR;
  }
  else
  {
    /* Set specific parameters for each PixelFormat */
    switch (PixelFormat)
    {
    case OV5640_YUV422:
      for(index=0; index<(sizeof(OV5640_PF_YUV422)/4U); index++)
      {
        if(ret != OV5640_ERROR)
        {
          tmp = (uint8_t)OV5640_PF_YUV422[index][1];
          if(ov5640_write_reg(&pObj->Ctx, OV5640_PF_YUV422[index][0], &tmp, 1) != OV5640_OK)
          {
            ret = OV5640_ERROR;
          }
          else
          {
            (void)OV5640_Delay(pObj, 1);
          }
        }
      }
      break;

    case OV5640_RGB565:
    default:
      for(index=0; index<(sizeof(OV5640_PF_RGB565)/4U); index++)
      {
        if(ret != OV5640_ERROR)
        {
          tmp = (uint8_t)OV5640_PF_RGB565[index][1];
          if(ov5640_write_reg(&pObj->Ctx, OV5640_PF_RGB565[index][0], &tmp, 1) != OV5640_OK)
          {
            ret = OV5640_ERROR;
          }
          else
          {
            (void)OV5640_Delay(pObj, 1);
          }
        }
      }
      break;
    }
  }

  return ret;
}

/**
  * @brief  Set OV5640 camera Pixel Format.
  * @param  pObj  pointer to component object
  * @param  PixelFormat pixel format to be configured
  * @retval Component status
  */
int32_t OV5640_GetPixelFormat(OV5640_Object_t *pObj, uint32_t *PixelFormat)
{
  (void)(pObj);
  (void)(PixelFormat);

  return OV5640_ERROR;
}

/**
  * @brief  Get OV5640 camera resolution.
  * @param  pObj  pointer to component object
  * @param  Resolution  Camera resolution
  * @retval Component status
  */
int32_t OV5640_SetResolution(OV5640_Object_t *pObj, uint32_t Resolution)
{
  int32_t ret = OV5640_OK;
  uint32_t index;
  uint8_t tmp;

  /* Initialization sequence for WVGA resolution (800x480)*/
  static const uint16_t OV5640_WVGA[][2]=
  {
    {OV5640_TIMING_DVPHO_HIGH, 0x03},
    {OV5640_TIMING_DVPHO_LOW, 0x20},
    {OV5640_TIMING_DVPVO_HIGH, 0x01},
    {OV5640_TIMING_DVPVO_LOW, 0xE0},
  };

  /* Initialization sequence for VGA resolution (640x480)*/
  static const uint16_t OV5640_VGA[][2]=
  {
    {OV5640_TIMING_DVPHO_HIGH, 0x02},
    {OV5640_TIMING_DVPHO_LOW, 0x80},
    {OV5640_TIMING_DVPVO_HIGH, 0x01},
    {OV5640_TIMING_DVPVO_LOW, 0xE0},
  };

  /* Initialization sequence for 480x272 resolution */
  static const uint16_t OV5640_480x272[][2]=
  {
    {OV5640_TIMING_DVPHO_HIGH, 0x01},
    {OV5640_TIMING_DVPHO_LOW, 0xE0},
    {OV5640_TIMING_DVPVO_HIGH, 0x01},
    {OV5640_TIMING_DVPVO_LOW, 0x10},
  };

  /* Initialization sequence for QVGA resolution (320x240) */
  static const uint16_t OV5640_QVGA[][2] =
  {
    {OV5640_TIMING_DVPHO_HIGH, 0x01},
    {OV5640_TIMING_DVPHO_LOW, 0x40},
    {OV5640_TIMING_DVPVO_HIGH, 0x00},
    {OV5640_TIMING_DVPVO_LOW, 0xF0},
  };

  /* Initialization sequence for QQVGA resolution (160x120) */
  static const uint16_t OV5640_QQVGA[][2]=
  {
    {OV5640_TIMING_DVPHO_HIGH, 0x00},
    {OV5640_TIMING_DVPHO_LOW, 0xA0},
    {OV5640_TIMING_DVPVO_HIGH, 0x00},
    {OV5640_TIMING_DVPVO_LOW, 0x78},
  };

  /* Check if resolution is supported */
  if (Resolution > OV5640_R800x480)
  {
    ret = OV5640_ERROR;
  }
  else
  {
    /* Initialize OV5640 */
    switch (Resolution)
    {
    case OV5640_R160x120:
      for(index=0; index<(sizeof(OV5640_QQVGA)/4U); index++)
      {
        if(ret != OV5640_ERROR)
        {
          tmp = (uint8_t)OV5640_QQVGA[index][1];
          if(ov5640_write_reg(&pObj->Ctx, OV5640_QQVGA[index][0], &tmp, 1) != OV5640_OK)
          {
            ret = OV5640_ERROR;
          }
        }
      }
      break;
    case OV5640_R320x240:
      for(index=0; index< (sizeof(OV5640_QVGA)/4U); index++)
      {
        if(ret != OV5640_ERROR)
        {
          tmp = (uint8_t)OV5640_QVGA[index][1];
          if(ov5640_write_reg(&pObj->Ctx, OV5640_QVGA[index][0], &tmp, 1) != OV5640_OK)
          {
            ret = OV5640_ERROR;
          }
        }
      }
      break;
    case OV5640_R480x272:
      for(index=0; index<(sizeof(OV5640_480x272)/4U); index++)
      {
        if(ret != OV5640_ERROR)
        {
          tmp = (uint8_t)OV5640_480x272[index][1];
          if(ov5640_write_reg(&pObj->Ctx, OV5640_480x272[index][0], &tmp, 1) != OV5640_OK)
          {
            ret = OV5640_ERROR;
          }
        }
      }
      break;
    case OV5640_R640x480:
      for(index=0; index<(sizeof(OV5640_VGA)/4U); index++)
      {
        if(ret != OV5640_ERROR)
        {
          tmp = (uint8_t)OV5640_VGA[index][1];
          if(ov5640_write_reg(&pObj->Ctx, OV5640_VGA[index][0], &tmp, 1) != OV5640_OK)
          {
            ret = OV5640_ERROR;
          }
        }
      }
      break;
    case OV5640_R800x480:
      for(index=0; index<(sizeof(OV5640_WVGA)/4U); index++)
      {
        if(ret != OV5640_ERROR)
        {
          tmp = (uint8_t)OV5640_WVGA[index][1];
          if(ov5640_write_reg(&pObj->Ctx, OV5640_WVGA[index][0], &tmp, 1) != OV5640_OK)
          {
            ret = OV5640_ERROR;
          }
        }
      }
      break;
    default:
      ret = OV5640_ERROR;
      break;
    }
  }

  return ret;
}

/**
  * @brief  Get OV5640 camera resolution.
  * @param  pObj  pointer to component object
  * @param  Resolution  Camera resolution
  * @retval Component status
  */
int32_t OV5640_GetResolution(OV5640_Object_t *pObj, uint32_t *Resolution)
{
  int32_t ret;
  uint16_t x_size, y_size;
  uint8_t tmp;

  if(ov5640_read_reg(&pObj->Ctx, OV5640_TIMING_DVPHO_HIGH, &tmp, 1) != OV5640_OK)
  {
    ret = OV5640_ERROR;
  }
  else
  {
    x_size = (uint16_t)tmp << 8U;

    if(ov5640_read_reg(&pObj->Ctx, OV5640_TIMING_DVPHO_LOW, &tmp, 1) != OV5640_OK)
    {
      ret = OV5640_ERROR;
    }
    else
    {
      x_size |= tmp;

      if(ov5640_read_reg(&pObj->Ctx, OV5640_TIMING_DVPVO_HIGH, &tmp, 1) != OV5640_OK)
      {
        ret = OV5640_ERROR;
      }
      else
      {
        y_size = (uint16_t)tmp << 8U;
        if(ov5640_read_reg(&pObj->Ctx, OV5640_TIMING_DVPVO_LOW, &tmp, 1) != OV5640_OK)
        {
          ret = OV5640_ERROR;
        }
        else
        {
          y_size |= tmp;

          if((x_size == 800U) && (y_size == 480U))
          {
            *Resolution = OV5640_R800x480;
            ret = OV5640_OK;
          }
          else if((x_size == 640U) && (y_size == 480U))
          {
            *Resolution = OV5640_R640x480;
            ret = OV5640_OK;
          }
          else if((x_size == 480U) && (y_size == 272U))
          {
            *Resolution = OV5640_R480x272;
            ret = OV5640_OK;
          }
          else if((x_size == 320U) && (y_size == 240U))
          {
            *Resolution = OV5640_R320x240;
            ret = OV5640_OK;
          }
          else if((x_size == 160U) && (y_size == 120U))
          {
            *Resolution = OV5640_R160x120;
            ret = OV5640_OK;
          }
          else
          {
            ret = OV5640_ERROR;
          }
        }
      }
    }
  }

  return ret;
}

/**
  * @brief  Read the OV5640 Camera identity.
  * @param  pObj  pointer to component object
  * @param  Id    pointer to component ID
  * @retval Component status
  */
int32_t OV5640_ReadID(OV5640_Object_t *pObj, uint32_t *Id)
{
  int32_t ret;
  uint8_t tmp;

  /* Initialize I2C */
  pObj->IO.Init();

  /* Prepare the camera to be configured */
  tmp = 0x80;
  if(ov5640_write_reg(&pObj->Ctx, OV5640_SYSTEM_CTROL0, &tmp, 1) != OV5640_OK)
  {
    ret = OV5640_ERROR;
  }
  else
  {
    (void)OV5640_Delay(pObj, 500);

    if(ov5640_read_reg(&pObj->Ctx, OV5640_CHIP_ID_HIGH_BYTE, &tmp, 1)!= OV5640_OK)
    {
      ret = OV5640_ERROR;
    }
    else
    {
      *Id = (uint32_t)tmp << 8U;
      if(ov5640_read_reg(&pObj->Ctx, OV5640_CHIP_ID_LOW_BYTE, &tmp, 1)!= OV5640_OK)
      {
        ret = OV5640_ERROR;
      }
      else
      {
        *Id |= tmp;
        ret = OV5640_OK;
      }
    }
  }

  /* Component status */
  return ret;
}

/**
  * @brief  Read the OV5640 Camera Capabilities.
  * @param  pObj          pointer to component object
  * @param  Capabilities  pointer to component Capabilities
  * @retval Component status
  */
int32_t OV5640_GetCapabilities(OV5640_Object_t *pObj, OV5640_Capabilities_t *Capabilities)
{
  int32_t ret;

  if(pObj == NULL)
  {
    ret = OV5640_ERROR;
  }
  else
  {
    Capabilities->Config_Brightness    = 1;
    Capabilities->Config_Contrast      = 1;
    Capabilities->Config_HueDegree     = 1;
    Capabilities->Config_LightMode     = 1;
    Capabilities->Config_MirrorFlip    = 1;
    Capabilities->Config_NightMode     = 1;
    Capabilities->Config_Resolution    = 1;
    Capabilities->Config_Saturation    = 1;
    Capabilities->Config_SpecialEffect = 1;
    Capabilities->Config_Zoom          = 1;

    ret = OV5640_OK;
  }

  return ret;
}

/**
  * @brief  Set the OV5640 camera Light Mode.
  * @param  pObj  pointer to component object
  * @param  Effect  Effect to be configured
  * @retval Component status
  */
int32_t OV5640_SetLightMode(OV5640_Object_t *pObj, uint32_t LightMode)
{
  int32_t ret;
  uint32_t index;
  uint8_t tmp;

  /* OV5640 Light Mode setting */
  static const uint16_t OV5640_LightModeAuto[][2]=
  {
    {OV5640_AWB_MANUAL_CONTROL, 0x00},
    {OV5640_AWB_R_GAIN_MSB, 0x04},
    {OV5640_AWB_R_GAIN_LSB, 0x00},
    {OV5640_AWB_G_GAIN_MSB, 0x04},
    {OV5640_AWB_G_GAIN_LSB, 0x00},
    {OV5640_AWB_B_GAIN_MSB, 0x04},
    {OV5640_AWB_B_GAIN_LSB, 0x00},
  };

  static const uint16_t OV5640_LightModeCloudy[][2]=
  {
    {OV5640_AWB_MANUAL_CONTROL, 0x01},
    {OV5640_AWB_R_GAIN_MSB, 0x06},
    {OV5640_AWB_R_GAIN_LSB, 0x48},
    {OV5640_AWB_G_GAIN_MSB, 0x04},
    {OV5640_AWB_G_GAIN_LSB, 0x00},
    {OV5640_AWB_B_GAIN_MSB, 0x04},
    {OV5640_AWB_B_GAIN_LSB, 0xD3},
  };

  static const uint16_t OV5640_LightModeOffice[][2]=
  {
    {OV5640_AWB_MANUAL_CONTROL, 0x01},
    {OV5640_AWB_R_GAIN_MSB, 0x05},
    {OV5640_AWB_R_GAIN_LSB, 0x48},
    {OV5640_AWB_G_GAIN_MSB, 0x04},
    {OV5640_AWB_G_GAIN_LSB, 0x00},
    {OV5640_AWB_B_GAIN_MSB, 0x07},
    {OV5640_AWB_B_GAIN_LSB, 0xCF},
  };

  static const uint16_t OV5640_LightModeHome[][2]=
  {
    {OV5640_AWB_MANUAL_CONTROL, 0x01},
    {OV5640_AWB_R_GAIN_MSB, 0x04},
    {OV5640_AWB_R_GAIN_LSB, 0x10},
    {OV5640_AWB_G_GAIN_MSB, 0x04},
    {OV5640_AWB_G_GAIN_LSB, 0x00},
    {OV5640_AWB_B_GAIN_MSB, 0x08},
    {OV5640_AWB_B_GAIN_LSB, 0xB6},
  };

  static const uint16_t OV5640_LightModeSunny[][2]=
  {
    {OV5640_AWB_MANUAL_CONTROL, 0x01},
    {OV5640_AWB_R_GAIN_MSB, 0x06},
    {OV5640_AWB_R_GAIN_LSB, 0x1C},
    {OV5640_AWB_G_GAIN_MSB, 0x04},
    {OV5640_AWB_G_GAIN_LSB, 0x00},
    {OV5640_AWB_B_GAIN_MSB, 0x04},
    {OV5640_AWB_B_GAIN_LSB, 0xF3},
  };

  tmp = 0x00;
  ret = ov5640_write_reg(&pObj->Ctx, OV5640_AWB_MANUAL_CONTROL, &tmp, 1);
  if(ret == OV5640_OK)
  {
    tmp = 0x46;
    ret = ov5640_write_reg(&pObj->Ctx, OV5640_AWB_CTRL16, &tmp, 1);
  }

  if(ret == OV5640_OK)
  {
    tmp = 0xF8;
    ret = ov5640_write_reg(&pObj->Ctx, OV5640_AWB_CTRL17, &tmp, 1);
  }

  if(ret == OV5640_OK)
  {
    tmp = 0x04;
    ret = ov5640_write_reg(&pObj->Ctx, OV5640_AWB_CTRL18, &tmp, 1);
  }

  if(ret == OV5640_OK)
  {
    switch(LightMode)
    {
    case OV5640_LIGHT_SUNNY:
      for(index=0; index< (sizeof(OV5640_LightModeSunny)/4U) ; index++)
      {
        if(ret != OV5640_ERROR)
        {
          tmp = (uint8_t)OV5640_LightModeSunny[index][1];
          if(ov5640_write_reg(&pObj->Ctx, OV5640_LightModeSunny[index][0], &tmp, 1) != OV5640_OK)
          {
            ret = OV5640_ERROR;
          }
        }
      }
      break;
    case OV5640_LIGHT_OFFICE:
      for(index=0; index< (sizeof(OV5640_LightModeOffice)/4U) ; index++)
      {
        if(ret != OV5640_ERROR)
        {
          tmp = (uint8_t)OV5640_LightModeOffice[index][1];
          if(ov5640_write_reg(&pObj->Ctx, OV5640_LightModeOffice[index][0], &tmp, 1) != OV5640_OK)
          {
            ret = OV5640_ERROR;
          }
        }
      }
      break;
    case OV5640_LIGHT_CLOUDY:
      for(index=0; index< (sizeof(OV5640_LightModeCloudy)/4U) ; index++)
      {
        if(ret != OV5640_ERROR)
        {
          tmp = (uint8_t)OV5640_LightModeCloudy[index][1];
          if(ov5640_write_reg(&pObj->Ctx, OV5640_LightModeCloudy[index][0], &tmp, 1) != OV5640_OK)
          {
            ret = OV5640_ERROR;
          }
        }
      }
      break;
    case OV5640_LIGHT_HOME:
      for(index=0; index< (sizeof(OV5640_LightModeHome)/4U) ; index++)
      {
        if(ret != OV5640_ERROR)
        {
          tmp = (uint8_t)OV5640_LightModeHome[index][1];
          if(ov5640_write_reg(&pObj->Ctx, OV5640_LightModeHome[index][0], &tmp, 1) != OV5640_OK)
          {
            ret = OV5640_ERROR;
          }
        }
      }
      break;
    case OV5640_LIGHT_AUTO:
    default :
      for(index=0; index< (sizeof(OV5640_LightModeAuto)/4U) ; index++)
      {
        if(ret != OV5640_ERROR)
        {
          tmp = (uint8_t)OV5640_LightModeAuto[index][1];
          if(ov5640_write_reg(&pObj->Ctx, OV5640_LightModeAuto[index][0], &tmp, 1) != OV5640_OK)
          {
            ret = OV5640_ERROR;
          }
        }
      }
      break;
    }
  }
  return ret;
}

/**
  * @brief  Set the OV5640 camera Special Effect.
  * @param  pObj  pointer to component object
  * @param  Effect  Effect to be configured
  * @retval Component status
  */
int32_t OV5640_SetColorEffect(OV5640_Object_t *pObj, uint32_t Effect)
{
  int32_t ret;
  uint8_t tmp;

  switch(Effect)
  {
  case OV5640_COLOR_EFFECT_BLUE:
    tmp = 0xFF;
    ret = ov5640_write_reg(&pObj->Ctx, OV5640_ISP_CONTROL01, &tmp, 1);

    if(ret == OV5640_OK)
    {
      tmp = 0x18;
      ret = ov5640_write_reg(&pObj->Ctx, OV5640_SDE_CTRL0, &tmp, 1);
    }
    if(ret == OV5640_OK)
    {
      tmp = 0xA0;
      ret = ov5640_write_reg(&pObj->Ctx, OV5640_SDE_CTRL3, &tmp, 1);
    }
    if(ret == OV5640_OK)
    {
      tmp = 0x40;
      ret = ov5640_write_reg(&pObj->Ctx, OV5640_SDE_CTRL4, &tmp, 1);
    }

    if(ret != OV5640_OK)
    {
      ret = OV5640_ERROR;
    }
    break;

  case OV5640_COLOR_EFFECT_RED:
    tmp = 0xFF;
    ret = ov5640_write_reg(&pObj->Ctx, OV5640_ISP_CONTROL01, &tmp, 1);

    if(ret == OV5640_OK)
    {
      tmp = 0x18;
      ret = ov5640_write_reg(&pObj->Ctx, OV5640_SDE_CTRL0, &tmp, 1);
    }
    if(ret == OV5640_OK)
    {
      tmp = 0x80;
      ret = ov5640_write_reg(&pObj->Ctx, OV5640_SDE_CTRL3, &tmp, 1);
    }
    if(ret == OV5640_OK)
    {
      tmp = 0xC0;
      ret = ov5640_write_reg(&pObj->Ctx, OV5640_SDE_CTRL4, &tmp, 1);
    }

    if(ret != OV5640_OK)
    {
      ret = OV5640_ERROR;
    }
    break;

  case OV5640_COLOR_EFFECT_GREEN:
    tmp = 0xFF;
    ret = ov5640_write_reg(&pObj->Ctx, OV5640_ISP_CONTROL01, &tmp, 1);

    if(ret == OV5640_OK)
    {
      tmp = 0x18;
      ret = ov5640_write_reg(&pObj->Ctx, OV5640_SDE_CTRL0, &tmp, 1);
    }
    if(ret == OV5640_OK)
    {
      tmp = 0x60;
      ret = ov5640_write_reg(&pObj->Ctx, OV5640_SDE_CTRL3, &tmp, 1);
    }
    if(ret == OV5640_OK)
    {
      tmp = 0x60;
      ret = ov5640_write_reg(&pObj->Ctx, OV5640_SDE_CTRL4, &tmp, 1);
    }

    if(ret != OV5640_OK)
    {
      ret = OV5640_ERROR;
    }
    break;

  case OV5640_COLOR_EFFECT_BW:
    tmp = 0xFF;
    ret = ov5640_write_reg(&pObj->Ctx, OV5640_ISP_CONTROL01, &tmp, 1);

    if(ret == OV5640_OK)
    {
      tmp = 0x18;
      ret = ov5640_write_reg(&pObj->Ctx, OV5640_SDE_CTRL0, &tmp, 1);
    }
    if(ret == OV5640_OK)
    {
      tmp = 0x80;
      ret = ov5640_write_reg(&pObj->Ctx, OV5640_SDE_CTRL3, &tmp, 1);
    }
    if(ret == OV5640_OK)
    {
      tmp = 0x80;
      ret = ov5640_write_reg(&pObj->Ctx, OV5640_SDE_CTRL4, &tmp, 1);
    }

    if(ret != OV5640_OK)
    {
      ret = OV5640_ERROR;
    }
    break;

  case OV5640_COLOR_EFFECT_SEPIA:
    tmp = 0xFF;
    ret = ov5640_write_reg(&pObj->Ctx, OV5640_ISP_CONTROL01, &tmp, 1);

    if(ret == OV5640_OK)
    {
      tmp = 0x18;
      ret = ov5640_write_reg(&pObj->Ctx, OV5640_SDE_CTRL0, &tmp, 1);
    }
    if(ret == OV5640_OK)
    {
      tmp = 0x40;
      ret = ov5640_write_reg(&pObj->Ctx, OV5640_SDE_CTRL3, &tmp, 1);
    }
    if(ret == OV5640_OK)
    {
      tmp = 0xA0;
      ret = ov5640_write_reg(&pObj->Ctx, OV5640_SDE_CTRL4, &tmp, 1);
    }

    if(ret != OV5640_OK)
    {
      ret = OV5640_ERROR;
    }
    break;

  case OV5640_COLOR_EFFECT_NEGATIVE:
    tmp = 0xFF;
    ret = ov5640_write_reg(&pObj->Ctx, OV5640_ISP_CONTROL01, &tmp, 1);

    if(ret == OV5640_OK)
    {
      tmp = 0x40;
      ret = ov5640_write_reg(&pObj->Ctx, OV5640_SDE_CTRL0, &tmp, 1);
    }
    if(ret != OV5640_OK)
    {
      ret = OV5640_ERROR;
    }
    break;

  case OV5640_COLOR_EFFECT_NONE:
  default :
    tmp = 0x7F;
    ret = ov5640_write_reg(&pObj->Ctx, OV5640_ISP_CONTROL01, &tmp, 1);

    if(ret == OV5640_OK)
    {
      tmp = 0x00;
      ret = ov5640_write_reg(&pObj->Ctx, OV5640_SDE_CTRL0, &tmp, 1);
    }

    if(ret != OV5640_OK)
    {
      ret = OV5640_ERROR;
    }

    break;
  }

  return ret;
}

/**
  * @brief  Set the OV5640 camera Brightness Level.
  * @note   The brightness of OV5640 could be adjusted. Higher brightness will
  *         make the picture more bright. The side effect of higher brightness
  *         is the picture looks foggy.
  * @param  pObj  pointer to component object
  * @param  Level Value to be configured
  * @retval Component status
  */
int32_t OV5640_SetBrightness(OV5640_Object_t *pObj, int32_t Level)
{
  int32_t ret;
  const uint8_t brightness_level[] = {0x40U, 0x30U, 0x20U, 0x10U, 0x00U, 0x10U, 0x20U, 0x30U, 0x40U};
  uint8_t tmp;

  tmp = 0xFF;
  ret = ov5640_write_reg(&pObj->Ctx, OV5640_ISP_CONTROL01, &tmp, 1);

  if(ret == OV5640_OK)
  {
   tmp = brightness_level[Level + 4];
   ret = ov5640_write_reg(&pObj->Ctx, OV5640_SDE_CTRL7, &tmp, 1);
  }
  if(ret == OV5640_OK)
  {
    tmp = 0x04;
    ret = ov5640_write_reg(&pObj->Ctx, OV5640_SDE_CTRL0, &tmp, 1);
  }

  if(ret == OV5640_OK)
  {
    if(Level < 0)
    {
      tmp = 0x01;
      if(ov5640_write_reg(&pObj->Ctx, OV5640_SDE_CTRL8, &tmp, 1) != OV5640_OK)
      {
        ret = OV5640_ERROR;
      }
    }
    else
    {
      tmp = 0x09;
      if(ov5640_write_reg(&pObj->Ctx, OV5640_SDE_CTRL8, &tmp, 1) != OV5640_OK)
      {
        ret = OV5640_ERROR;
      }
    }
  }

  return ret;
}

/**
  * @brief  Set the OV5640 camera Saturation Level.
  * @note   The color saturation of OV5640 could be adjusted. High color saturation
  *         would make the picture looks more vivid, but the side effect is the
  *         bigger noise and not accurate skin color.
  * @param  pObj  pointer to component object
  * @param  Level Value to be configured
  * @retval Component status
  */
int32_t OV5640_SetSaturation(OV5640_Object_t *pObj, int32_t Level)
{
  int32_t ret;
  const uint8_t saturation_level[] = {0x00U, 0x10U, 0x20U, 0x30U, 0x80U, 0x70U, 0x60U, 0x50U, 0x40U};
  uint8_t tmp;

  tmp = 0xFF;
  ret = ov5640_write_reg(&pObj->Ctx, OV5640_ISP_CONTROL01, &tmp, 1);

  if(ret == OV5640_OK)
  {
    tmp = saturation_level[Level + 4];
    ret = ov5640_write_reg(&pObj->Ctx, OV5640_SDE_CTRL3, &tmp, 1);
  }
  if(ret == OV5640_OK)
  {
    ret = ov5640_write_reg(&pObj->Ctx, OV5640_SDE_CTRL4, &tmp, 1);
  }
  if(ret == OV5640_OK)
  {
    tmp = 0x02;
    ret = ov5640_write_reg(&pObj->Ctx, OV5640_SDE_CTRL0, &tmp, 1);
  }

  if(ret == OV5640_OK)
  {
    tmp = 0x41;
    ret = ov5640_write_reg(&pObj->Ctx, OV5640_SDE_CTRL8, &tmp, 1);
  }

  if(ret != OV5640_OK)
  {
    ret = OV5640_ERROR;
  }

  return ret;
}

/**
  * @brief  Set the OV5640 camera Contrast Level.
  * @note   The contrast of OV5640 could be adjusted. Higher contrast will make
  *         the picture sharp. But the side effect is loosing dynamic range.
  * @param  pObj  pointer to component object
  * @param  Level Value to be configured
  * @retval Component status
  */
int32_t OV5640_SetContrast(OV5640_Object_t *pObj, int32_t Level)
{
  int32_t ret;
  const uint8_t contrast_level[] = {0x10U, 0x14U, 0x18U, 0x1CU, 0x20U, 0x24U, 0x28U, 0x2CU, 0x30U};
  uint8_t tmp;

  tmp = 0xFF;
  ret = ov5640_write_reg(&pObj->Ctx, OV5640_ISP_CONTROL01, &tmp, 1);

  if(ret == OV5640_OK)
  {
    tmp = 0x04;
    ret = ov5640_write_reg(&pObj->Ctx, OV5640_SDE_CTRL0, &tmp, 1);
  }
  if(ret == OV5640_OK)
  {
    tmp = contrast_level[Level + 4];
    ret = ov5640_write_reg(&pObj->Ctx, OV5640_SDE_CTRL6, &tmp, 1);
  }
  if(ret == OV5640_OK)
  {
    ret = ov5640_write_reg(&pObj->Ctx, OV5640_SDE_CTRL5, &tmp, 1);
  }
  if(ret == OV5640_OK)
  {
    tmp = 0x41;
    ret = ov5640_write_reg(&pObj->Ctx, OV5640_SDE_CTRL8, &tmp, 1);
  }

  if(ret != OV5640_OK)
  {
    ret = OV5640_ERROR;
  }

  return ret;
}

/**
  * @brief  Set the OV5640 camera Hue degree.
  * @param  pObj  pointer to component object
  * @param  Level Value to be configured
  * @retval Component status
  */
int32_t OV5640_SetHueDegree(OV5640_Object_t *pObj, int32_t Degree)
{
  int32_t ret;
  const uint8_t hue_degree_ctrl1[] = {0x80U, 0x6FU, 0x40U, 0x00U, 0x40U, 0x6FU, 0x80U, 0x6FU, 0x40U, 0x00U, 0x40U, 0x6FU};
  const uint8_t hue_degree_ctrl2[] = {0x00U, 0x40U, 0x6FU, 0x80U, 0x6FU, 0x40U, 0x00U, 0x40U, 0x6FU, 0x80U, 0x6FU, 0x40U};
  const uint8_t hue_degree_ctrl8[] = {0x32U, 0x32U, 0x32U, 0x02U, 0x02U, 0x02U, 0x01U, 0x01U, 0x01U, 0x31U, 0x31U, 0x31U};
  uint8_t tmp;

  tmp = 0xFF;
  ret = ov5640_write_reg(&pObj->Ctx, OV5640_ISP_CONTROL01, &tmp, 1);

  if(ret == OV5640_OK)
  {
    tmp = 0x01;
    ret = ov5640_write_reg(&pObj->Ctx, OV5640_SDE_CTRL0, &tmp, 1);
  }
  if(ret == OV5640_OK)
  {
    tmp = hue_degree_ctrl1[Degree + 6];
    ret = ov5640_write_reg(&pObj->Ctx, OV5640_SDE_CTRL1, &tmp, 1);
  }
  if(ret == OV5640_OK)
  {
    tmp = hue_degree_ctrl2[Degree + 6];
    ret = ov5640_write_reg(&pObj->Ctx, OV5640_SDE_CTRL2, &tmp, 1);
  }
  if(ret == OV5640_OK)
  {
    tmp = hue_degree_ctrl8[Degree + 6];
    ret = ov5640_write_reg(&pObj->Ctx, OV5640_SDE_CTRL8, &tmp, 1);
  }

  if(ret != OV5640_OK)
  {
    ret = OV5640_ERROR;
  }

  return ret;
}

/**
  * @brief  Control OV5640 camera mirror/vflip.
  * @param  pObj  pointer to component object
  * @param  Config To configure mirror, flip, both or none
  * @retval Component status
  */
int32_t OV5640_MirrorFlipConfig(OV5640_Object_t *pObj, uint32_t Config)
{
  int32_t ret;
  uint8_t tmp3820 = 0, tmp3821;

  if(ov5640_read_reg(&pObj->Ctx, OV5640_TIMING_TC_REG20, &tmp3820, 1) != OV5640_OK)
  {
    ret = OV5640_ERROR;
  }
  else
  {
    tmp3820 &= 0xF9U;

    if(ov5640_read_reg(&pObj->Ctx, OV5640_TIMING_TC_REG21, &tmp3821, 1) != OV5640_OK)
    {
      ret = OV5640_ERROR;
    }
    else
    {
      ret = OV5640_OK;
      tmp3821 &= 0xF9U;

      switch (Config)
      {
      case OV5640_MIRROR:
        if(ov5640_write_reg(&pObj->Ctx, OV5640_TIMING_TC_REG20, &tmp3820, 1) != OV5640_OK)
        {
          ret = OV5640_ERROR;
        }
        else
        {
          tmp3821 |= 0x06U;
          if(ov5640_write_reg(&pObj->Ctx, OV5640_TIMING_TC_REG21, &tmp3821, 1) != OV5640_OK)
          {
            ret = OV5640_ERROR;
          }
        }
        break;
      case OV5640_FLIP:
        tmp3820 |= 0x06U;
        if(ov5640_write_reg(&pObj->Ctx, OV5640_TIMING_TC_REG20, &tmp3820, 1) != OV5640_OK)
        {
          ret = OV5640_ERROR;
        }
        else
        {
          if(ov5640_write_reg(&pObj->Ctx, OV5640_TIMING_TC_REG21, &tmp3821, 1) != OV5640_OK)
          {
            ret = OV5640_ERROR;
          }
        }
        break;
      case OV5640_MIRROR_FLIP:
        tmp3820 |= 0x06U;
        if(ov5640_write_reg(&pObj->Ctx, OV5640_TIMING_TC_REG20, &tmp3820, 1) != OV5640_OK)
        {
          ret = OV5640_ERROR;
        }
        else
        {
          tmp3821 |= 0x06U;
          if(ov5640_write_reg(&pObj->Ctx, OV5640_TIMING_TC_REG21, &tmp3821, 1) != OV5640_OK)
          {
            ret = OV5640_ERROR;
          }
        }
        break;

      case OV5640_MIRROR_FLIP_NONE:
      default:
        if(ov5640_write_reg(&pObj->Ctx, OV5640_TIMING_TC_REG20, &tmp3820, 1) != OV5640_OK)
        {
          ret = OV5640_ERROR;
        }
        else
        {
          if(ov5640_write_reg(&pObj->Ctx, OV5640_TIMING_TC_REG21, &tmp3821, 1) != OV5640_OK)
          {
            ret = OV5640_ERROR;
          }
        }
        break;
      }
    }
  }

  return ret;
}

/**
  * @brief  Control OV5640 camera zooming.
  * @param  pObj  pointer to component object
  * @param  Zoom  Zoom to be configured
  * @retval Component status
  */
int32_t OV5640_ZoomConfig(OV5640_Object_t *pObj, uint32_t Zoom)
{
  int32_t ret = OV5640_OK;
  uint32_t res;
  uint32_t zoom;
  uint8_t tmp;

  /* Get camera resolution */
  if(OV5640_GetResolution(pObj, &res) != OV5640_OK)
  {
    ret = OV5640_ERROR;
  }
  else
  {
    zoom = Zoom;

    if(zoom == OV5640_ZOOM_x1)
    {
      tmp = 0x10;
      if(ov5640_write_reg(&pObj->Ctx, OV5640_SCALE_CTRL0, &tmp, 1) != OV5640_OK)
      {
        ret = OV5640_ERROR;
      }
    }
    else
    {
      switch (res)
      {
      case OV5640_R320x240:
      case OV5640_R480x272:
        zoom = zoom >> 1U;
        break;
      case OV5640_R640x480:
        zoom = zoom >> 2U;
        break;
      default:
        break;
      }

      tmp = 0x00;
      if(ov5640_write_reg(&pObj->Ctx, OV5640_SCALE_CTRL0, &tmp, 1) != OV5640_OK)
      {
        ret = OV5640_ERROR;
      }
      else
      {
        tmp = (uint8_t)zoom;
        if(ov5640_write_reg(&pObj->Ctx, OV5640_SCALE_CTRL1, &tmp, 1) != OV5640_OK)
        {
          ret = OV5640_ERROR;
        }
      }
    }
  }

  return ret;
}

/**
  * @brief  Enable/disable the OV5640 camera night mode.
  * @param  pObj  pointer to component object
  * @param  Cmd   Enable disable night mode
  * @retval Component status
  */
int32_t OV5640_NightModeConfig(OV5640_Object_t *pObj, uint32_t Cmd)
{
  int32_t ret;
  uint8_t tmp = 0;

  if(Cmd == NIGHT_MODE_ENABLE)
  {
    /* Auto Frame Rate: 15fps ~ 3.75fps night mode for 60/50Hz light environment,
    24Mhz clock input,24Mhz PCLK*/
    ret = ov5640_write_reg(&pObj->Ctx, OV5640_SC_PLL_CONTRL4 ,&tmp, 1);
    if(ret == OV5640_OK)
    {
      ret = ov5640_write_reg(&pObj->Ctx, OV5640_SC_PLL_CONTRL5 ,&tmp, 1);
    }
    if(ret == OV5640_OK)
    {
      tmp = 0x7C;
      ret = ov5640_write_reg(&pObj->Ctx, OV5640_AEC_CTRL00 ,&tmp, 1);
    }
    if(ret == OV5640_OK)
    {
      tmp = 0x01;
      ret = ov5640_write_reg(&pObj->Ctx, OV5640_AEC_B50_STEP_HIGH ,&tmp, 1);
    }
    if(ret == OV5640_OK)
    {
      tmp = 0x27;
      ret = ov5640_write_reg(&pObj->Ctx, OV5640_AEC_B50_STEP_LOW ,&tmp, 1);
    }
    if(ret == OV5640_OK)
    {
      tmp = 0x00;
      ret = ov5640_write_reg(&pObj->Ctx, OV5640_AEC_B60_STEP_HIGH ,&tmp, 1);
    }
    if(ret == OV5640_OK)
    {
      tmp = 0xF6;
      ret = ov5640_write_reg(&pObj->Ctx, OV5640_AEC_B60_STEP_LOW ,&tmp, 1);
    }
    if(ret == OV5640_OK)
    {
      tmp = 0x04;
      ret = ov5640_write_reg(&pObj->Ctx, OV5640_AEC_CTRL0D ,&tmp, 1);
    }
    if(ret == OV5640_OK)
    {
      ret = ov5640_write_reg(&pObj->Ctx, OV5640_AEC_CTRL0E ,&tmp, 1);
    }
    if(ret == OV5640_OK)
    {
      tmp = 0x0B;
      ret = ov5640_write_reg(&pObj->Ctx, OV5640_AEC_CTRL02 ,&tmp, 1);
    }
    if(ret == OV5640_OK)
    {
      tmp = 0x88;
      ret = ov5640_write_reg(&pObj->Ctx, OV5640_AEC_CTRL03 ,&tmp, 1);
    }
    if(ret == OV5640_OK)
    {
      tmp = 0x0B;
      ret = ov5640_write_reg(&pObj->Ctx, OV5640_AEC_MAX_EXPO_HIGH ,&tmp, 1);
    }
    if(ret == OV5640_OK)
    {
      tmp = 0x88;
      ret = ov5640_write_reg(&pObj->Ctx, OV5640_AEC_MAX_EXPO_LOW ,&tmp, 1);
    }
    if(ret != OV5640_OK)
    {
      ret = OV5640_ERROR;
    }
  }
  else
  {
    if(ov5640_read_reg(&pObj->Ctx, OV5640_AEC_CTRL00, &tmp, 1) != OV5640_OK)
    {
      ret = OV5640_ERROR;
    }
    else
    {
      ret = OV5640_OK;
      tmp &= 0xFBU;
      /* Set Bit 2 to 0 */
      if(ov5640_write_reg(&pObj->Ctx, OV5640_AEC_CTRL00, &tmp, 1) != OV5640_OK)
      {
        ret = OV5640_ERROR;
      }
    }
  }

  return ret;
}

/**
  * @}
  */

/** @defgroup OV5640_Private_Functions Private Functions
  * @{
  */
/**
  * @brief This function provides accurate delay (in milliseconds)
  * @param pObj   pointer to component object
  * @param Delay  specifies the delay time length, in milliseconds
  * @retval OV5640_OK
  */
static int32_t OV5640_Delay(OV5640_Object_t *pObj, uint32_t Delay)
{
  uint32_t tickstart;
  tickstart = pObj->IO.GetTick();
  while((pObj->IO.GetTick() - tickstart) < Delay)
  {
  }
  return OV5640_OK;
}

/**
  * @brief  Wrap component ReadReg to Bus Read function
  * @param  handle  Component object handle
  * @param  Reg  The target register address to write
  * @param  pData  The target register value to be written
  * @param  Length  buffer size to be written
  * @retval error status
  */
static int32_t OV5640_ReadRegWrap(void *handle, uint16_t Reg, uint8_t* pData, uint16_t Length)
{
  OV5640_Object_t *pObj = (OV5640_Object_t *)handle;

  return pObj->IO.ReadReg(pObj->IO.Address, Reg, pData, Length);
}

/**
  * @brief  Wrap component WriteReg to Bus Write function
  * @param  handle  Component object handle
  * @param  Reg  The target register address to write
  * @param  pData  The target register value to be written
  * @param  Length  buffer size to be written
  * @retval error status
  */
static int32_t OV5640_WriteRegWrap(void *handle, uint16_t Reg, uint8_t* pData, uint16_t Length)
{
  OV5640_Object_t *pObj = (OV5640_Object_t *)handle;

  return pObj->IO.WriteReg(pObj->IO.Address, Reg, pData, Length);
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
