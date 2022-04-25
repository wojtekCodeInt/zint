#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <cstdint>
#include <iostream>
#include "common.h"
#include "gs1.h"
#include <unistd.h>
#include <cstring>
#include <file_input.h>
#include <fuzzer/FuzzedDataProvider.h>



const int BARCODES[] = {
BARCODE_CODE11,//          1
BARCODE_C25MATRIX,//       2
BARCODE_C25INTER,//        3
BARCODE_C25IATA,//         4
BARCODE_C25LOGIC,//        6
BARCODE_C25IND,//          7
BARCODE_CODE39,//          8
BARCODE_EXCODE39,//        9
BARCODE_EANX,//            13
BARCODE_EANX_CHK,//        14
BARCODE_EAN128,//          16
BARCODE_CODABAR,//         18
BARCODE_CODE128,//         20
BARCODE_DPLEIT,//          21
BARCODE_DPIDENT,//         22
BARCODE_CODE16K,//         23
BARCODE_CODE49,//          24
BARCODE_CODE93,//          25
BARCODE_FLAT,//            28
BARCODE_RSS14,//           29
BARCODE_RSS_LTD,//         30
BARCODE_RSS_EXP,//         31
BARCODE_TELEPEN,//         32
BARCODE_UPCA,//            34
BARCODE_UPCA_CHK,//        35
BARCODE_UPCE,//            37
BARCODE_UPCE_CHK,//        38
BARCODE_POSTNET,//         40
BARCODE_MSI_PLESSEY,//     47
BARCODE_FIM,//             49
BARCODE_LOGMARS,//         50
BARCODE_PHARMA,//          51
BARCODE_PZN,//             52
BARCODE_PHARMA_TWO,//      53
BARCODE_PDF417,//          55
BARCODE_PDF417TRUNC,//     56
BARCODE_MAXICODE,//        57
BARCODE_QRCODE,//          58
BARCODE_CODE128B,//        60
BARCODE_AUSPOST,//         63
BARCODE_AUSREPLY,//        66
BARCODE_AUSROUTE,//        67
BARCODE_AUSREDIRECT,//     68
BARCODE_ISBNX,//           69
BARCODE_RM4SCC,//          70
BARCODE_DATAMATRIX,//      71
BARCODE_EAN14,//           72
BARCODE_VIN,//             73
BARCODE_CODABLOCKF,//      74
BARCODE_NVE18,//           75
BARCODE_JAPANPOST,//       76
BARCODE_KOREAPOST,//       77
BARCODE_RSS14STACK,//      79
BARCODE_RSS14STACK_OMNI,// 80
BARCODE_RSS_EXPSTACK,//    81
BARCODE_PLANET,//          82
BARCODE_MICROPDF417,//     84
BARCODE_ONECODE,//         85
BARCODE_PLESSEY,//         86

    /* Tbarcode 8 codes */
BARCODE_TELEPEN_NUM,//     87
BARCODE_ITF14,//           89
BARCODE_KIX,//             90
BARCODE_AZTEC,//           92
BARCODE_DAFT,//            93
BARCODE_MICROQR,//         97

    /* Tbarcode 9 codes */
BARCODE_HIBC_128,//        98
BARCODE_HIBC_39,//         99
BARCODE_HIBC_DM,//         102
BARCODE_HIBC_QR,//         104
BARCODE_HIBC_PDF,//        106
BARCODE_HIBC_MICPDF,//     108
BARCODE_HIBC_BLOCKF,//     110
BARCODE_HIBC_AZTEC,//      112

    /* Tbarcode 10 codes */
BARCODE_DOTCODE,//         115
BARCODE_HANXIN,//          116

    /*Tbarcode 11 codes*/
BARCODE_MAILMARK,//        121

    /* Zint specific */
BARCODE_AZRUNE,//          128
BARCODE_CODE32,//          129
BARCODE_EANX_CC,//         130
BARCODE_EAN128_CC,//       131
BARCODE_RSS14_CC,//        132
BARCODE_RSS_LTD_CC,//      133
BARCODE_RSS_EXP_CC,//      134
BARCODE_UPCA_CC,//         135
BARCODE_UPCE_CC,//         136
BARCODE_RSS14STACK_CC,//   137
BARCODE_RSS14_OMNI_CC,//   138
BARCODE_RSS_EXPSTACK_CC,// 139
BARCODE_CHANNEL,//         140
BARCODE_CODEONE,//         141
BARCODE_GRIDMATRIX,//      142
BARCODE_UPNQR,//           143
BARCODE_ULTRA,//           144
BARCODE_RMQR,//            145
};

extern "C" int FUZZ(const unsigned char *Data, size_t Size)
{
  if (Size < 20 || Size > 1020)
    return 0;

  FuzzedDataProvider dp(Data, Size);

  int fuzzed_int = dp.ConsumeIntegral<int>();
  int fuzzed_int2 = dp.ConsumeIntegral<int>();
  int fuzzed_int3 = dp.ConsumeIntegral<int>(); // unused
  int fuzzed_symbology = dp.PickValueInArray(BARCODES);
  bool fuzzed_bool = dp.ConsumeBool();
  bool fuzzed_bool2 = dp.ConsumeBool();
  bool fuzzed_bool3 = dp.ConsumeBool(); //unused
  int rotate_angle = dp.ConsumeIntegral<int>();
  auto remaining = dp.ConsumeRemainingBytes<unsigned char>();


  struct zint_symbol *my_symbol = ZBarcode_Create();
  if (fuzzed_bool) {  
    my_symbol->symbology = fuzzed_symbology;
  } else {
      my_symbol->symbology = fuzzed_int;
  }
  if (fuzzed_bool2) {
      my_symbol->input_mode = fuzzed_int2;
  }
  auto ci_file_input = ci::input_file{remaining.data(), remaining.size()};
  char * filename = strdup(ci_file_input.name()); // needed because ZBarcode_Encode_File does not accept const char *
  ZBarcode_Encode_File(my_symbol, filename);
  free(filename);
  ZBarcode_Delete(my_symbol);

  return 0;
}
