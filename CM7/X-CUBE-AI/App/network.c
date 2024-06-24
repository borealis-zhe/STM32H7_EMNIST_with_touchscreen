/**
  ******************************************************************************
  * @file    network.c
  * @author  AST Embedded Analytics Research Platform
  * @date    Mon Jun 24 00:33:21 2024
  * @brief   AI Tool Automatic Code Generator for Embedded NN computing
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  ******************************************************************************
  */


#include "network.h"
#include "network_data.h"

#include "ai_platform.h"
#include "ai_platform_interface.h"
#include "ai_math_helpers.h"

#include "core_common.h"
#include "core_convert.h"

#include "layers.h"



#undef AI_NET_OBJ_INSTANCE
#define AI_NET_OBJ_INSTANCE g_network
 
#undef AI_NETWORK_MODEL_SIGNATURE
#define AI_NETWORK_MODEL_SIGNATURE     "0x7ef82e19727609fa8148e0ec3940a863"

#ifndef AI_TOOLS_REVISION_ID
#define AI_TOOLS_REVISION_ID     ""
#endif

#undef AI_TOOLS_DATE_TIME
#define AI_TOOLS_DATE_TIME   "Mon Jun 24 00:33:21 2024"

#undef AI_TOOLS_COMPILE_TIME
#define AI_TOOLS_COMPILE_TIME    __DATE__ " " __TIME__

#undef AI_NETWORK_N_BATCHES
#define AI_NETWORK_N_BATCHES         (1)

static ai_ptr g_network_activations_map[1] = AI_C_ARRAY_INIT;
static ai_ptr g_network_weights_map[1] = AI_C_ARRAY_INIT;



/**  Array declarations section  **********************************************/
/* Array#0 */
AI_ARRAY_OBJ_DECLARE(
  serving_default_input_10_output_array, AI_ARRAY_FORMAT_U8|AI_FMT_FLAG_IS_IO,
  NULL, NULL, 784, AI_STATIC)

/* Array#1 */
AI_ARRAY_OBJ_DECLARE(
  conversion_0_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 784, AI_STATIC)

/* Array#2 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_1_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 3136, AI_STATIC)

/* Array#3 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_2_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 3136, AI_STATIC)

/* Array#4 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_3_pad_before_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 4096, AI_STATIC)

/* Array#5 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_3_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 6272, AI_STATIC)

/* Array#6 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_4_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 1568, AI_STATIC)

/* Array#7 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_5_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 64, AI_STATIC)

/* Array#8 */
AI_ARRAY_OBJ_DECLARE(
  gemm_7_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 36, AI_STATIC)

/* Array#9 */
AI_ARRAY_OBJ_DECLARE(
  nl_8_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 36, AI_STATIC)

/* Array#10 */
AI_ARRAY_OBJ_DECLARE(
  conversion_9_output_array, AI_ARRAY_FORMAT_FLOAT|AI_FMT_FLAG_IS_IO,
  NULL, NULL, 36, AI_STATIC)

/* Array#11 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_1_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 144, AI_STATIC)

/* Array#12 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_1_bias_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 16, AI_STATIC)

/* Array#13 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_2_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 144, AI_STATIC)

/* Array#14 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_2_bias_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 16, AI_STATIC)

/* Array#15 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_3_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 4608, AI_STATIC)

/* Array#16 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_3_bias_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 32, AI_STATIC)

/* Array#17 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_4_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 288, AI_STATIC)

/* Array#18 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_4_bias_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 32, AI_STATIC)

/* Array#19 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_5_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 2048, AI_STATIC)

/* Array#20 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_5_bias_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 64, AI_STATIC)

/* Array#21 */
AI_ARRAY_OBJ_DECLARE(
  gemm_7_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 2304, AI_STATIC)

/* Array#22 */
AI_ARRAY_OBJ_DECLARE(
  gemm_7_bias_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 36, AI_STATIC)

/* Array#23 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_1_scratch0_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 548, AI_STATIC)

/* Array#24 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_2_scratch0_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 593, AI_STATIC)

/* Array#25 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_3_scratch0_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 6144, AI_STATIC)

/* Array#26 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_4_scratch0_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 1185, AI_STATIC)

/* Array#27 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_5_scratch0_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 768, AI_STATIC)

/* Array#28 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_5_scratch1_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 3136, AI_STATIC)

/* Array#29 */
AI_ARRAY_OBJ_DECLARE(
  gemm_7_scratch0_array, AI_ARRAY_FORMAT_S16,
  NULL, NULL, 64, AI_STATIC)

/* Array#30 */
AI_ARRAY_OBJ_DECLARE(
  nl_8_scratch0_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 36, AI_STATIC)

/**  Array metadata declarations section  *************************************/
/* Int quant #0 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(serving_default_input_10_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_U8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.007843137718737125f),
    AI_PACK_UINTQ_ZP(127)))

/* Int quant #1 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conversion_0_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.007843137718737125f),
    AI_PACK_INTQ_ZP(-1)))

/* Int quant #2 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_1_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.2315894067287445f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #3 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_2_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.20124612748622894f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #4 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_3_pad_before_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.20124612748622894f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #5 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_3_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.5954235792160034f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #6 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_4_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.2706354856491089f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #7 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_5_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.00452814856544137f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #8 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(gemm_7_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.6511406302452087f),
    AI_PACK_INTQ_ZP(100)))

/* Int quant #9 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(nl_8_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.00390625f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #10 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_1_weights_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 16,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.010913748294115067f, 0.007515369914472103f, 0.05643252655863762f, 0.07166092097759247f, 0.020364774391055107f, 0.038866885006427765f, 0.07307113707065582f, 0.048153355717659f, 0.03998316079378128f, 0.018245361745357513f, 0.018963556736707687f, 0.10035378485918045f, 0.04035294055938721f, 0.03791853412985802f, 0.017414389178156853f, 0.017240822315216064f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #11 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_2_weights_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 16,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.01187876332551241f, 0.010638396255671978f, 0.025255270302295685f, 0.002073029289022088f, 0.005462064407765865f, 0.005678320769220591f, 0.003984816838055849f, 0.0033620730973780155f, 0.006073083728551865f, 0.0025521472562104464f, 0.006748361513018608f, 0.0012129906099289656f, 0.002566214185208082f, 0.006999763660132885f, 0.005988606251776218f, 0.008248265832662582f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #12 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_3_weights_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 32,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.003628318663686514f, 0.008568023331463337f, 0.003277118783444166f, 0.012500850483775139f, 0.005402531940490007f, 0.005841628182679415f, 0.0031775962561368942f, 0.004243186675012112f, 0.029917052015662193f, 0.003232063027098775f, 0.01945457234978676f, 0.002432919107377529f, 0.006564084440469742f, 0.004026584327220917f, 0.0049634650349617004f, 0.008090837858617306f, 0.003324376419186592f, 0.009470195509493351f, 0.01036139391362667f, 0.010535999201238155f, 0.003749435767531395f, 0.009482992812991142f, 0.004618030972778797f, 0.0054056537337601185f, 0.007079020142555237f, 0.0047551547177135944f, 0.0024839926045387983f, 0.005337994545698166f, 0.005191416945308447f, 0.004544260911643505f, 0.004724868573248386f, 0.0025958335027098656f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #13 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_4_weights_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 32,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.0074117607437074184f, 0.00286127463914454f, 0.0050133876502513885f, 0.006904717534780502f, 0.0014600575668737292f, 0.005988779943436384f, 0.004978247452527285f, 0.004186655394732952f, 0.00131516985129565f, 0.004151724278926849f, 0.0016398634761571884f, 0.0092009911313653f, 0.0030052585061639547f, 0.029588213190436363f, 0.004025998525321484f, 0.0026488553266972303f, 0.00566978519782424f, 0.0029698116704821587f, 0.0020166579633951187f, 0.0014198364224284887f, 0.004637028090655804f, 0.0026801570784300566f, 0.0026179125998169184f, 0.008677820675075054f, 0.00248922873288393f, 0.0055135139264166355f, 0.008720223791897297f, 0.003004499478265643f, 0.002531136618927121f, 0.014590218663215637f, 0.004299356136471033f, 0.005133527796715498f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #14 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_5_weights_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 64,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.002485421486198902f, 0.0025332109071314335f, 0.0026938333176076412f, 0.003120320150628686f, 0.0018382660346105695f, 0.002592504722997546f, 0.00253272638656199f, 0.002509583253413439f, 0.00294407713226974f, 0.0019711984787136316f, 0.002313461387529969f, 0.002692559966817498f, 0.002959569450467825f, 0.0015288927825167775f, 0.001693256781436503f, 0.002670370740815997f, 0.002993200905621052f, 0.0020885542035102844f, 0.0026888614520430565f, 0.001266577048227191f, 0.0020689412485808134f, 0.002703761449083686f, 0.0035390593111515045f, 0.0035288177896291018f, 0.002947440603747964f, 0.0014233520487323403f, 0.0033597785513848066f, 0.0022537449840456247f, 0.0033021774142980576f, 0.002281352411955595f, 0.004809788428246975f, 0.0051507288590073586f, 0.001668645883910358f, 0.002412050263956189f, 0.0036624616477638483f, 0.0024956448469311f, 0.0037594009190797806f, 0.0035618029069155455f, 0.0034159007482230663f, 0.0019238177919760346f, 0.0017543011344969273f, 0.0026272174436599016f, 0.002306942595168948f, 0.0021694882307201624f, 0.002728350693359971f, 0.002196838613599539f, 0.0022541398648172617f, 0.0033538031857460737f, 0.0030829731840640306f, 0.0019062949577346444f, 0.002703215926885605f, 0.0029742466285824776f, 0.0027702986262738705f, 0.0032170340418815613f, 0.0028394099790602922f, 0.0019441142212599516f, 0.004399371799081564f, 0.003139360575005412f, 0.0030708746053278446f, 0.0022440068423748016f, 0.0021362544503062963f, 0.0026086210273206234f, 0.003295918693765998f, 0.0024629465769976377f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #15 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(gemm_7_weights_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.37846001982688904f),
    AI_PACK_INTQ_ZP(0)))

/* Int quant #16 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_5_scratch1_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.058465417474508286f),
    AI_PACK_INTQ_ZP(-128)))

/**  Tensor declarations section  *********************************************/
/* Tensor #0 */
AI_TENSOR_OBJ_DECLARE(
  serving_default_input_10_output, AI_STATIC,
  0, 0x1,
  AI_SHAPE_INIT(4, 1, 1, 28, 28), AI_STRIDE_INIT(4, 1, 1, 1, 28),
  1, &serving_default_input_10_output_array, &serving_default_input_10_output_array_intq)

/* Tensor #1 */
AI_TENSOR_OBJ_DECLARE(
  conversion_0_output, AI_STATIC,
  1, 0x1,
  AI_SHAPE_INIT(4, 1, 1, 28, 28), AI_STRIDE_INIT(4, 1, 1, 1, 28),
  1, &conversion_0_output_array, &conversion_0_output_array_intq)

/* Tensor #2 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_1_output, AI_STATIC,
  2, 0x1,
  AI_SHAPE_INIT(4, 1, 16, 14, 14), AI_STRIDE_INIT(4, 1, 1, 16, 224),
  1, &conv2d_1_output_array, &conv2d_1_output_array_intq)

/* Tensor #3 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_2_output, AI_STATIC,
  3, 0x1,
  AI_SHAPE_INIT(4, 1, 16, 14, 14), AI_STRIDE_INIT(4, 1, 1, 16, 224),
  1, &conv2d_2_output_array, &conv2d_2_output_array_intq)

/* Tensor #4 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_3_pad_before_output, AI_STATIC,
  4, 0x1,
  AI_SHAPE_INIT(4, 1, 16, 16, 16), AI_STRIDE_INIT(4, 1, 1, 16, 256),
  1, &conv2d_3_pad_before_output_array, &conv2d_3_pad_before_output_array_intq)

/* Tensor #5 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_3_output, AI_STATIC,
  5, 0x1,
  AI_SHAPE_INIT(4, 1, 32, 14, 14), AI_STRIDE_INIT(4, 1, 1, 32, 448),
  1, &conv2d_3_output_array, &conv2d_3_output_array_intq)

/* Tensor #6 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_4_output, AI_STATIC,
  6, 0x1,
  AI_SHAPE_INIT(4, 1, 32, 7, 7), AI_STRIDE_INIT(4, 1, 1, 32, 224),
  1, &conv2d_4_output_array, &conv2d_4_output_array_intq)

/* Tensor #7 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_5_output, AI_STATIC,
  7, 0x1,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 1, 1, 64, 64),
  1, &conv2d_5_output_array, &conv2d_5_output_array_intq)

/* Tensor #8 */
AI_TENSOR_OBJ_DECLARE(
  gemm_7_output, AI_STATIC,
  8, 0x1,
  AI_SHAPE_INIT(4, 1, 36, 1, 1), AI_STRIDE_INIT(4, 1, 1, 36, 36),
  1, &gemm_7_output_array, &gemm_7_output_array_intq)

/* Tensor #9 */
AI_TENSOR_OBJ_DECLARE(
  nl_8_output, AI_STATIC,
  9, 0x1,
  AI_SHAPE_INIT(4, 1, 36, 1, 1), AI_STRIDE_INIT(4, 1, 1, 36, 36),
  1, &nl_8_output_array, &nl_8_output_array_intq)

/* Tensor #10 */
AI_TENSOR_OBJ_DECLARE(
  conversion_9_output, AI_STATIC,
  10, 0x0,
  AI_SHAPE_INIT(4, 1, 36, 1, 1), AI_STRIDE_INIT(4, 4, 4, 144, 144),
  1, &conversion_9_output_array, NULL)

/* Tensor #11 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_1_weights, AI_STATIC,
  11, 0x1,
  AI_SHAPE_INIT(4, 1, 3, 3, 16), AI_STRIDE_INIT(4, 1, 1, 16, 48),
  1, &conv2d_1_weights_array, &conv2d_1_weights_array_intq)

/* Tensor #12 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_1_bias, AI_STATIC,
  12, 0x0,
  AI_SHAPE_INIT(4, 1, 16, 1, 1), AI_STRIDE_INIT(4, 4, 4, 64, 64),
  1, &conv2d_1_bias_array, NULL)

/* Tensor #13 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_2_weights, AI_STATIC,
  13, 0x1,
  AI_SHAPE_INIT(4, 16, 3, 3, 1), AI_STRIDE_INIT(4, 1, 16, 16, 48),
  1, &conv2d_2_weights_array, &conv2d_2_weights_array_intq)

/* Tensor #14 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_2_bias, AI_STATIC,
  14, 0x0,
  AI_SHAPE_INIT(4, 1, 16, 1, 1), AI_STRIDE_INIT(4, 4, 4, 64, 64),
  1, &conv2d_2_bias_array, NULL)

/* Tensor #15 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_3_weights, AI_STATIC,
  15, 0x1,
  AI_SHAPE_INIT(4, 16, 3, 3, 32), AI_STRIDE_INIT(4, 1, 16, 512, 1536),
  1, &conv2d_3_weights_array, &conv2d_3_weights_array_intq)

/* Tensor #16 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_3_bias, AI_STATIC,
  16, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 1, 1), AI_STRIDE_INIT(4, 4, 4, 128, 128),
  1, &conv2d_3_bias_array, NULL)

/* Tensor #17 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_4_weights, AI_STATIC,
  17, 0x1,
  AI_SHAPE_INIT(4, 32, 3, 3, 1), AI_STRIDE_INIT(4, 1, 32, 32, 96),
  1, &conv2d_4_weights_array, &conv2d_4_weights_array_intq)

/* Tensor #18 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_4_bias, AI_STATIC,
  18, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 1, 1), AI_STRIDE_INIT(4, 4, 4, 128, 128),
  1, &conv2d_4_bias_array, NULL)

/* Tensor #19 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_5_weights, AI_STATIC,
  19, 0x1,
  AI_SHAPE_INIT(4, 32, 1, 1, 64), AI_STRIDE_INIT(4, 1, 32, 2048, 2048),
  1, &conv2d_5_weights_array, &conv2d_5_weights_array_intq)

/* Tensor #20 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_5_bias, AI_STATIC,
  20, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &conv2d_5_bias_array, NULL)

/* Tensor #21 */
AI_TENSOR_OBJ_DECLARE(
  gemm_7_weights, AI_STATIC,
  21, 0x1,
  AI_SHAPE_INIT(4, 64, 36, 1, 1), AI_STRIDE_INIT(4, 1, 64, 2304, 2304),
  1, &gemm_7_weights_array, &gemm_7_weights_array_intq)

/* Tensor #22 */
AI_TENSOR_OBJ_DECLARE(
  gemm_7_bias, AI_STATIC,
  22, 0x0,
  AI_SHAPE_INIT(4, 1, 36, 1, 1), AI_STRIDE_INIT(4, 4, 4, 144, 144),
  1, &gemm_7_bias_array, NULL)

/* Tensor #23 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_1_scratch0, AI_STATIC,
  23, 0x0,
  AI_SHAPE_INIT(4, 1, 548, 1, 1), AI_STRIDE_INIT(4, 1, 1, 548, 548),
  1, &conv2d_1_scratch0_array, NULL)

/* Tensor #24 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_2_scratch0, AI_STATIC,
  24, 0x0,
  AI_SHAPE_INIT(4, 1, 593, 1, 1), AI_STRIDE_INIT(4, 1, 1, 593, 593),
  1, &conv2d_2_scratch0_array, NULL)

/* Tensor #25 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_3_scratch0, AI_STATIC,
  25, 0x0,
  AI_SHAPE_INIT(4, 1, 6144, 1, 1), AI_STRIDE_INIT(4, 1, 1, 6144, 6144),
  1, &conv2d_3_scratch0_array, NULL)

/* Tensor #26 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_4_scratch0, AI_STATIC,
  26, 0x0,
  AI_SHAPE_INIT(4, 1, 1185, 1, 1), AI_STRIDE_INIT(4, 1, 1, 1185, 1185),
  1, &conv2d_4_scratch0_array, NULL)

/* Tensor #27 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_5_scratch0, AI_STATIC,
  27, 0x0,
  AI_SHAPE_INIT(4, 1, 768, 1, 1), AI_STRIDE_INIT(4, 1, 1, 768, 768),
  1, &conv2d_5_scratch0_array, NULL)

/* Tensor #28 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_5_scratch1, AI_STATIC,
  28, 0x1,
  AI_SHAPE_INIT(4, 1, 64, 7, 7), AI_STRIDE_INIT(4, 1, 1, 64, 448),
  1, &conv2d_5_scratch1_array, &conv2d_5_scratch1_array_intq)

/* Tensor #29 */
AI_TENSOR_OBJ_DECLARE(
  gemm_7_scratch0, AI_STATIC,
  29, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 2, 2, 128, 128),
  1, &gemm_7_scratch0_array, NULL)

/* Tensor #30 */
AI_TENSOR_OBJ_DECLARE(
  nl_8_scratch0, AI_STATIC,
  30, 0x0,
  AI_SHAPE_INIT(4, 1, 36, 1, 1), AI_STRIDE_INIT(4, 4, 4, 144, 144),
  1, &nl_8_scratch0_array, NULL)



/**  Layer declarations section  **********************************************/


AI_TENSOR_CHAIN_OBJ_DECLARE(
  conversion_9_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_8_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conversion_9_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  conversion_9_layer, 9,
  NL_TYPE, 0x0, NULL,
  nl, node_convert,
  &conversion_9_chain,
  NULL, &conversion_9_layer, AI_STATIC, 
)


AI_STATIC_CONST ai_i32 nl_8_nl_params_data[] = { 1398313856, 26, -31 };
AI_ARRAY_OBJ_DECLARE(
    nl_8_nl_params, AI_ARRAY_FORMAT_S32,
    nl_8_nl_params_data, nl_8_nl_params_data, 3, AI_STATIC_CONST)
AI_TENSOR_CHAIN_OBJ_DECLARE(
  nl_8_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &gemm_7_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_8_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_8_scratch0)
)

AI_LAYER_OBJ_DECLARE(
  nl_8_layer, 8,
  NL_TYPE, 0x0, NULL,
  nl, forward_sm_integer,
  &nl_8_chain,
  NULL, &conversion_9_layer, AI_STATIC, 
  .nl_params = &nl_8_nl_params, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  gemm_7_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_5_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &gemm_7_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &gemm_7_weights, &gemm_7_bias),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &gemm_7_scratch0)
)

AI_LAYER_OBJ_DECLARE(
  gemm_7_layer, 7,
  DENSE_TYPE, 0x0, NULL,
  dense, forward_dense_integer_SSSA,
  &gemm_7_chain,
  NULL, &nl_8_layer, AI_STATIC, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  conv2d_5_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_4_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_5_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_5_weights, &conv2d_5_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &conv2d_5_scratch0, &conv2d_5_scratch1)
)

AI_LAYER_OBJ_DECLARE(
  conv2d_5_layer, 6,
  OPTIMIZED_CONV2D_TYPE, 0x0, NULL,
  conv2d_nl_pool, forward_pw_sssa8_ch_nl_pool,
  &conv2d_5_chain,
  NULL, &gemm_7_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .pool_size = AI_SHAPE_2D_INIT(7, 7), 
  .pool_stride = AI_SHAPE_2D_INIT(7, 7), 
  .pool_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .pool_func = AI_HANDLE_PTR(pool_func_ap_array_integer_INT8), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  conv2d_4_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_3_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_4_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_4_weights, &conv2d_4_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_4_scratch0)
)

AI_LAYER_OBJ_DECLARE(
  conv2d_4_layer, 4,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_dw_sssa8_ch,
  &conv2d_4_chain,
  NULL, &conv2d_5_layer, AI_STATIC, 
  .groups = 32, 
  .filter_stride = AI_SHAPE_2D_INIT(2, 2), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 2, 2), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_SAME, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  conv2d_3_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_3_pad_before_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_3_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_3_weights, &conv2d_3_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_3_scratch0)
)

AI_LAYER_OBJ_DECLARE(
  conv2d_3_layer, 3,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_sssa8_ch,
  &conv2d_3_chain,
  NULL, &conv2d_4_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)


AI_STATIC_CONST ai_i8 conv2d_3_pad_before_value_data[] = { -128 };
AI_ARRAY_OBJ_DECLARE(
    conv2d_3_pad_before_value, AI_ARRAY_FORMAT_S8,
    conv2d_3_pad_before_value_data, conv2d_3_pad_before_value_data, 1, AI_STATIC_CONST)
AI_TENSOR_CHAIN_OBJ_DECLARE(
  conv2d_3_pad_before_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_2_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_3_pad_before_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  conv2d_3_pad_before_layer, 3,
  PAD_TYPE, 0x0, NULL,
  pad, forward_pad,
  &conv2d_3_pad_before_chain,
  NULL, &conv2d_3_layer, AI_STATIC, 
  .value = &conv2d_3_pad_before_value, 
  .mode = AI_PAD_CONSTANT, 
  .pads = AI_SHAPE_INIT(4, 1, 1, 1, 1), 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  conv2d_2_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_1_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_2_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_2_weights, &conv2d_2_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_2_scratch0)
)

AI_LAYER_OBJ_DECLARE(
  conv2d_2_layer, 2,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_dw_sssa8_ch,
  &conv2d_2_chain,
  NULL, &conv2d_3_pad_before_layer, AI_STATIC, 
  .groups = 16, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 1, 1, 1, 1), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_SAME, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  conv2d_1_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conversion_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_1_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_1_weights, &conv2d_1_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_1_scratch0)
)

AI_LAYER_OBJ_DECLARE(
  conv2d_1_layer, 1,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_sssa8_ch,
  &conv2d_1_chain,
  NULL, &conv2d_2_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(2, 2), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 2, 2), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_SAME, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  conversion_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &serving_default_input_10_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conversion_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  conversion_0_layer, 0,
  NL_TYPE, 0x0, NULL,
  nl, node_convert_integer,
  &conversion_0_chain,
  NULL, &conv2d_1_layer, AI_STATIC, 
)


#if (AI_TOOLS_API_VERSION < AI_TOOLS_API_VERSION_1_5)

AI_NETWORK_OBJ_DECLARE(
  AI_NET_OBJ_INSTANCE, AI_STATIC,
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 10320, 1, 1),
    10320, NULL, NULL),
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 13376, 1, 1),
    13376, NULL, NULL),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_NETWORK_IN_NUM, &serving_default_input_10_output),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_NETWORK_OUT_NUM, &conversion_9_output),
  &conversion_0_layer, 0xb4a12022, NULL)

#else

AI_NETWORK_OBJ_DECLARE(
  AI_NET_OBJ_INSTANCE, AI_STATIC,
  AI_BUFFER_ARRAY_OBJ_INIT_STATIC(
  	AI_FLAG_NONE, 1,
    AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
      AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 10320, 1, 1),
      10320, NULL, NULL)
  ),
  AI_BUFFER_ARRAY_OBJ_INIT_STATIC(
  	AI_FLAG_NONE, 1,
    AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
      AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 13376, 1, 1),
      13376, NULL, NULL)
  ),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_NETWORK_IN_NUM, &serving_default_input_10_output),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_NETWORK_OUT_NUM, &conversion_9_output),
  &conversion_0_layer, 0xb4a12022, NULL)

#endif	/*(AI_TOOLS_API_VERSION < AI_TOOLS_API_VERSION_1_5)*/



/******************************************************************************/
AI_DECLARE_STATIC
ai_bool network_configure_activations(
  ai_network* net_ctx, const ai_network_params* params)
{
  AI_ASSERT(net_ctx)

  if (ai_platform_get_activations_map(g_network_activations_map, 1, params)) {
    /* Updating activations (byte) offsets */
    
    serving_default_input_10_output_array.data = AI_PTR(g_network_activations_map[0] + 7168);
    serving_default_input_10_output_array.data_start = AI_PTR(g_network_activations_map[0] + 7168);
    conversion_0_output_array.data = AI_PTR(g_network_activations_map[0] + 7168);
    conversion_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 7168);
    conv2d_1_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 7952);
    conv2d_1_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 7952);
    conv2d_1_output_array.data = AI_PTR(g_network_activations_map[0] + 4576);
    conv2d_1_output_array.data_start = AI_PTR(g_network_activations_map[0] + 4576);
    conv2d_2_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 7712);
    conv2d_2_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 7712);
    conv2d_2_output_array.data = AI_PTR(g_network_activations_map[0] + 4096);
    conv2d_2_output_array.data_start = AI_PTR(g_network_activations_map[0] + 4096);
    conv2d_3_pad_before_output_array.data = AI_PTR(g_network_activations_map[0] + 3136);
    conv2d_3_pad_before_output_array.data_start = AI_PTR(g_network_activations_map[0] + 3136);
    conv2d_3_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 7232);
    conv2d_3_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 7232);
    conv2d_3_output_array.data = AI_PTR(g_network_activations_map[0] + 0);
    conv2d_3_output_array.data_start = AI_PTR(g_network_activations_map[0] + 0);
    conv2d_4_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 6272);
    conv2d_4_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 6272);
    conv2d_4_output_array.data = AI_PTR(g_network_activations_map[0] + 7460);
    conv2d_4_output_array.data_start = AI_PTR(g_network_activations_map[0] + 7460);
    conv2d_5_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 0);
    conv2d_5_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 0);
    conv2d_5_scratch1_array.data = AI_PTR(g_network_activations_map[0] + 768);
    conv2d_5_scratch1_array.data_start = AI_PTR(g_network_activations_map[0] + 768);
    conv2d_5_output_array.data = AI_PTR(g_network_activations_map[0] + 3904);
    conv2d_5_output_array.data_start = AI_PTR(g_network_activations_map[0] + 3904);
    gemm_7_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 0);
    gemm_7_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 0);
    gemm_7_output_array.data = AI_PTR(g_network_activations_map[0] + 128);
    gemm_7_output_array.data_start = AI_PTR(g_network_activations_map[0] + 128);
    nl_8_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 164);
    nl_8_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 164);
    nl_8_output_array.data = AI_PTR(g_network_activations_map[0] + 0);
    nl_8_output_array.data_start = AI_PTR(g_network_activations_map[0] + 0);
    conversion_9_output_array.data = AI_PTR(g_network_activations_map[0] + 36);
    conversion_9_output_array.data_start = AI_PTR(g_network_activations_map[0] + 36);
    return true;
  }
  AI_ERROR_TRAP(net_ctx, INIT_FAILED, NETWORK_ACTIVATIONS);
  return false;
}




/******************************************************************************/
AI_DECLARE_STATIC
ai_bool network_configure_weights(
  ai_network* net_ctx, const ai_network_params* params)
{
  AI_ASSERT(net_ctx)

  if (ai_platform_get_weights_map(g_network_weights_map, 1, params)) {
    /* Updating weights (byte) offsets */
    
    conv2d_1_weights_array.format |= AI_FMT_FLAG_CONST;
    conv2d_1_weights_array.data = AI_PTR(g_network_weights_map[0] + 0);
    conv2d_1_weights_array.data_start = AI_PTR(g_network_weights_map[0] + 0);
    conv2d_1_bias_array.format |= AI_FMT_FLAG_CONST;
    conv2d_1_bias_array.data = AI_PTR(g_network_weights_map[0] + 144);
    conv2d_1_bias_array.data_start = AI_PTR(g_network_weights_map[0] + 144);
    conv2d_2_weights_array.format |= AI_FMT_FLAG_CONST;
    conv2d_2_weights_array.data = AI_PTR(g_network_weights_map[0] + 208);
    conv2d_2_weights_array.data_start = AI_PTR(g_network_weights_map[0] + 208);
    conv2d_2_bias_array.format |= AI_FMT_FLAG_CONST;
    conv2d_2_bias_array.data = AI_PTR(g_network_weights_map[0] + 352);
    conv2d_2_bias_array.data_start = AI_PTR(g_network_weights_map[0] + 352);
    conv2d_3_weights_array.format |= AI_FMT_FLAG_CONST;
    conv2d_3_weights_array.data = AI_PTR(g_network_weights_map[0] + 416);
    conv2d_3_weights_array.data_start = AI_PTR(g_network_weights_map[0] + 416);
    conv2d_3_bias_array.format |= AI_FMT_FLAG_CONST;
    conv2d_3_bias_array.data = AI_PTR(g_network_weights_map[0] + 5024);
    conv2d_3_bias_array.data_start = AI_PTR(g_network_weights_map[0] + 5024);
    conv2d_4_weights_array.format |= AI_FMT_FLAG_CONST;
    conv2d_4_weights_array.data = AI_PTR(g_network_weights_map[0] + 5152);
    conv2d_4_weights_array.data_start = AI_PTR(g_network_weights_map[0] + 5152);
    conv2d_4_bias_array.format |= AI_FMT_FLAG_CONST;
    conv2d_4_bias_array.data = AI_PTR(g_network_weights_map[0] + 5440);
    conv2d_4_bias_array.data_start = AI_PTR(g_network_weights_map[0] + 5440);
    conv2d_5_weights_array.format |= AI_FMT_FLAG_CONST;
    conv2d_5_weights_array.data = AI_PTR(g_network_weights_map[0] + 5568);
    conv2d_5_weights_array.data_start = AI_PTR(g_network_weights_map[0] + 5568);
    conv2d_5_bias_array.format |= AI_FMT_FLAG_CONST;
    conv2d_5_bias_array.data = AI_PTR(g_network_weights_map[0] + 7616);
    conv2d_5_bias_array.data_start = AI_PTR(g_network_weights_map[0] + 7616);
    gemm_7_weights_array.format |= AI_FMT_FLAG_CONST;
    gemm_7_weights_array.data = AI_PTR(g_network_weights_map[0] + 7872);
    gemm_7_weights_array.data_start = AI_PTR(g_network_weights_map[0] + 7872);
    gemm_7_bias_array.format |= AI_FMT_FLAG_CONST;
    gemm_7_bias_array.data = AI_PTR(g_network_weights_map[0] + 10176);
    gemm_7_bias_array.data_start = AI_PTR(g_network_weights_map[0] + 10176);
    return true;
  }
  AI_ERROR_TRAP(net_ctx, INIT_FAILED, NETWORK_WEIGHTS);
  return false;
}


/**  PUBLIC APIs SECTION  *****************************************************/



AI_DEPRECATED
AI_API_ENTRY
ai_bool ai_network_get_info(
  ai_handle network, ai_network_report* report)
{
  ai_network* net_ctx = AI_NETWORK_ACQUIRE_CTX(network);

  if (report && net_ctx)
  {
    ai_network_report r = {
      .model_name        = AI_NETWORK_MODEL_NAME,
      .model_signature   = AI_NETWORK_MODEL_SIGNATURE,
      .model_datetime    = AI_TOOLS_DATE_TIME,
      
      .compile_datetime  = AI_TOOLS_COMPILE_TIME,
      
      .runtime_revision  = ai_platform_runtime_get_revision(),
      .runtime_version   = ai_platform_runtime_get_version(),

      .tool_revision     = AI_TOOLS_REVISION_ID,
      .tool_version      = {AI_TOOLS_VERSION_MAJOR, AI_TOOLS_VERSION_MINOR,
                            AI_TOOLS_VERSION_MICRO, 0x0},
      .tool_api_version  = AI_STRUCT_INIT,

      .api_version            = ai_platform_api_get_version(),
      .interface_api_version  = ai_platform_interface_api_get_version(),
      
      .n_macc            = 1081896,
      .n_inputs          = 0,
      .inputs            = NULL,
      .n_outputs         = 0,
      .outputs           = NULL,
      .params            = AI_STRUCT_INIT,
      .activations       = AI_STRUCT_INIT,
      .n_nodes           = 0,
      .signature         = 0xb4a12022,
    };

    if (!ai_platform_api_get_network_report(network, &r)) return false;

    *report = r;
    return true;
  }
  return false;
}



AI_API_ENTRY
ai_bool ai_network_get_report(
  ai_handle network, ai_network_report* report)
{
  ai_network* net_ctx = AI_NETWORK_ACQUIRE_CTX(network);

  if (report && net_ctx)
  {
    ai_network_report r = {
      .model_name        = AI_NETWORK_MODEL_NAME,
      .model_signature   = AI_NETWORK_MODEL_SIGNATURE,
      .model_datetime    = AI_TOOLS_DATE_TIME,
      
      .compile_datetime  = AI_TOOLS_COMPILE_TIME,
      
      .runtime_revision  = ai_platform_runtime_get_revision(),
      .runtime_version   = ai_platform_runtime_get_version(),

      .tool_revision     = AI_TOOLS_REVISION_ID,
      .tool_version      = {AI_TOOLS_VERSION_MAJOR, AI_TOOLS_VERSION_MINOR,
                            AI_TOOLS_VERSION_MICRO, 0x0},
      .tool_api_version  = AI_STRUCT_INIT,

      .api_version            = ai_platform_api_get_version(),
      .interface_api_version  = ai_platform_interface_api_get_version(),
      
      .n_macc            = 1081896,
      .n_inputs          = 0,
      .inputs            = NULL,
      .n_outputs         = 0,
      .outputs           = NULL,
      .map_signature     = AI_MAGIC_SIGNATURE,
      .map_weights       = AI_STRUCT_INIT,
      .map_activations   = AI_STRUCT_INIT,
      .n_nodes           = 0,
      .signature         = 0xb4a12022,
    };

    if (!ai_platform_api_get_network_report(network, &r)) return false;

    *report = r;
    return true;
  }
  return false;
}


AI_API_ENTRY
ai_error ai_network_get_error(ai_handle network)
{
  return ai_platform_network_get_error(network);
}


AI_API_ENTRY
ai_error ai_network_create(
  ai_handle* network, const ai_buffer* network_config)
{
  return ai_platform_network_create(
    network, network_config, 
    AI_CONTEXT_OBJ(&AI_NET_OBJ_INSTANCE),
    AI_TOOLS_API_VERSION_MAJOR, AI_TOOLS_API_VERSION_MINOR, AI_TOOLS_API_VERSION_MICRO);
}


AI_API_ENTRY
ai_error ai_network_create_and_init(
  ai_handle* network, const ai_handle activations[], const ai_handle weights[])
{
  ai_error err;
  ai_network_params params;

  err = ai_network_create(network, AI_NETWORK_DATA_CONFIG);
  if (err.type != AI_ERROR_NONE) {
    return err;
  }
  
  if (ai_network_data_params_get(&params) != true) {
    err = ai_network_get_error(*network);
    return err;
  }
#if defined(AI_NETWORK_DATA_ACTIVATIONS_COUNT)
  /* set the addresses of the activations buffers */
  for (ai_u16 idx=0; activations && idx<params.map_activations.size; idx++) {
    AI_BUFFER_ARRAY_ITEM_SET_ADDRESS(&params.map_activations, idx, activations[idx]);
  }
#endif
#if defined(AI_NETWORK_DATA_WEIGHTS_COUNT)
  /* set the addresses of the weight buffers */
  for (ai_u16 idx=0; weights && idx<params.map_weights.size; idx++) {
    AI_BUFFER_ARRAY_ITEM_SET_ADDRESS(&params.map_weights, idx, weights[idx]);
  }
#endif
  if (ai_network_init(*network, &params) != true) {
    err = ai_network_get_error(*network);
  }
  return err;
}


AI_API_ENTRY
ai_buffer* ai_network_inputs_get(ai_handle network, ai_u16 *n_buffer)
{
  if (network == AI_HANDLE_NULL) {
    network = (ai_handle)&AI_NET_OBJ_INSTANCE;
    AI_NETWORK_OBJ(network)->magic = AI_MAGIC_CONTEXT_TOKEN;
  }
  return ai_platform_inputs_get(network, n_buffer);
}


AI_API_ENTRY
ai_buffer* ai_network_outputs_get(ai_handle network, ai_u16 *n_buffer)
{
  if (network == AI_HANDLE_NULL) {
    network = (ai_handle)&AI_NET_OBJ_INSTANCE;
    AI_NETWORK_OBJ(network)->magic = AI_MAGIC_CONTEXT_TOKEN;
  }
  return ai_platform_outputs_get(network, n_buffer);
}


AI_API_ENTRY
ai_handle ai_network_destroy(ai_handle network)
{
  return ai_platform_network_destroy(network);
}


AI_API_ENTRY
ai_bool ai_network_init(
  ai_handle network, const ai_network_params* params)
{
  ai_network* net_ctx = AI_NETWORK_OBJ(ai_platform_network_init(network, params));
  ai_bool ok = true;

  if (!net_ctx) return false;
  ok &= network_configure_weights(net_ctx, params);
  ok &= network_configure_activations(net_ctx, params);

  ok &= ai_platform_network_post_init(network);

  return ok;
}


AI_API_ENTRY
ai_i32 ai_network_run(
  ai_handle network, const ai_buffer* input, ai_buffer* output)
{
  return ai_platform_network_process(network, input, output);
}


AI_API_ENTRY
ai_i32 ai_network_forward(ai_handle network, const ai_buffer* input)
{
  return ai_platform_network_process(network, input, NULL);
}



#undef AI_NETWORK_MODEL_SIGNATURE
#undef AI_NET_OBJ_INSTANCE
#undef AI_TOOLS_DATE_TIME
#undef AI_TOOLS_COMPILE_TIME

