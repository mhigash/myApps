/**
 *  @file hs_api.h
 *
 *  Copyright (c) 2015, TOPCON TECHNOHOUSE Corp. All rights reserved.
 */

#ifndef _HS_API_H_
#define _HS_API_H_

#ifdef HS_API_EXPORTS
#define HS_API_API __declspec(dllexport)
#else
#define HS_API_API
#endif

#ifndef MAX_PATH
#define MAX_PATH 260
#endif

#ifdef __cplusplus
extern "C" {
#endif

/** Maximum number of characters for a product id */
const int HS_PRODUCT_ID_CHARACTERS_MAX = 32;
/** Maximum number of connections */
const int HS_DEVICE_COUNT_MAX = 8;
/** Maximum number of lens type for a device */
const int HS_DEVICE_LENS_TYPE_MAX = 10;
/** Maximum number of binning type for a device */
const int HS_DEVICE_BINNING_TYPE_MAX = 10;
/** Maximum number of gain type for a device */
const int HS_DEVICE_GAIN_TYPE_MAX = 10;

/** Maximum continuous measurement number */
const int HS_SEQUENTIAL_NO_MAX = 9999;
/** Minimal wavelength for spectral measurement */
const int HS_SPECTRAL_WAVELENGTH_MIN = 380;
/** Maximal visible wavelength for spectral measurement[for future development] */
const int HS_SPECTRAL_WAVELENGTH_MAX = 1100;
/** Maximum number of spectral wavelength range */
const int HS_SPECTRAL_DATA_SIZE = HS_SPECTRAL_WAVELENGTH_MAX - HS_SPECTRAL_WAVELENGTH_MIN + 1;
/** Minimal visible wavelength for spectral measurement */
const int HS_VISIBLE_SPECTRAL_WAVELENGTH_MIN = HS_SPECTRAL_WAVELENGTH_MIN;
/** Maximal visible wavelength for spectral measurement */
const int HS_VISIBLE_SPECTRAL_WAVELENGTH_MAX = 780;
/** Maximum number of visible light wavelength region */
const int HS_VISIBLE_SPECTRAL_DATA_SIZE = HS_VISIBLE_SPECTRAL_WAVELENGTH_MAX - HS_SPECTRAL_WAVELENGTH_MIN + 1;
/** Minimum number of contour */
const int HS_CONTOUR_COUNT_MIN = 2;
/** Default number of contour */
const int HS_CONTOUR_COUNT_DFT = 10;
/** Maximum number of contour */
const int HS_CONTOUR_COUNT_MAX = 20;
/** Number of thumbnail */
const int HS_THUMBNAILS_COUNT = 4;
/** Section line number of definition */
const int HS_SECTION_DATA_SETTING_COUNT_MAX = 10;

/** Live capture profile size */
const int HS_LIVE_PROFILE_SIZE = 2048;
/** Maximum data count of luminosity data */
const int HS_LUMINOSITY_DATA_COUNT_MAX = 10;
/** Maximum data count of luminosity factor data */
const int HS_LUMINOSITY_FACTOR_DATA_COUNT_MAX = 10;
/** Interval measurement condition setting count */
const int HS_INTERVAL_CONDITION_COUNT_MAX = 5;

/** Minimum vertical partition number of the image */
const int HS_IMAGE_PARTITION_VERTICAL_MIN = 1;
/** Maximum vertical partition number of the image(for area correction and matrix spot) */
const int HS_IMAGE_PARTITION_VERTICAL_MAX = 120;
/** Minimum horizontal partition number of the image */
const int HS_IMAGE_PARTITION_HORIZONTAL_MIN = 1;
/** Maximum horizontal partition number of the image(for area correction and matrix spot) */
const int HS_IMAGE_PARTITION_HORIZONTAL_MAX = 160;
/** Maximum number of admission decision area */
const int HS_JUDGMENT_AREA_COUNT_MAX = 10;
/** Maximum number of admission decision child area */
const int HS_JUDGMENT_CHILD_AREA_COUNT_MAX = 10;

/** Maximum number of spots */
const int HS_SPOT_MAX = HS_IMAGE_PARTITION_VERTICAL_MAX * HS_IMAGE_PARTITION_HORIZONTAL_MAX;
/** Maximum number of points in a polygon spot */
const int HS_SPOT_POLYGON_COUNT_MAX = 256;
/** Constant number of center reference evenly split for matrix spot */
const int HS_STD_SPOT_CENTER_EQUALITY_SPOT_DEF_MAX = 10;
/** Constant group of center reference evenly split for matrix spot */
const int HS_STD_SPOT_CENTER_EQUALITY_SPOT_COUNT[] = {3, 5, 7, 9, 11, 13, 15, 17, 19, 21};
/** Define the number of fixed standard number of spots for matrix spot */
const int HS_STD_SPOT_MEASUREMENT_SPOT_DEF_MAX = 4;
/** Fixed standard number of spots definition group for matrix spot */
const int HS_STD_SPOT_MEASUREMENT_SPOT_COUNT[] = {5, 9, 13, 25};

/** Date and time the maximum number of characters(yyyy/MM/dd hh:mm:ss.fff) */
const int HS_DATE_TIME_LENGTH = 24;
/** Comments maximum number of characters */
const int HS_COMMENT_LENGTH = 256;
/** 8U3 of bytes per pixel constant */
const int HS_BYTES_PER_PIXEL_8U3 = 3;
/** 32F of bytes per pixel constant */
const int HS_BYTES_PER_PIXEL_32F = 4;
/** Initial value of the list item index */
const int HS_NO_INDEX = -1;
/** Invalid value constant(FLT_MAX * -1) */
const float HS_INVALID_VALUE = 3.402823466e+38f * -1.0f;
/** Number of optimization results */
const int HS_OPTIMIZATION_RESULT_CNT = 4;

/** The heighest luminance */
const float HS_LUMINANCE_MAX = 5.0e+6f;
/** Maximal value of "L" of "L*a*b*" */
const float HS_LAB_L_MAX = 100.0f;
/** Maximal value of "a" and "b" of "L*a*b*" */
const float HS_LAB_AB_MAX = 150.0f;
/** Minimal value of "a" and "b" of "L*a*b*" */
const float HS_LAB_AB_MIN = -150.0f;

/**
 * @brief enumeration for error code.
 *
 * @version ver 1.5.0
 */
typedef enum _HsError {
  /** Success */
  HS_ERROR_NONE,
  /** Other process is already running */
  HS_ERROR_OTHER_PROCESS,
  /** Invalid argument */
  HS_ERROR_INVALID_PARAMETER,
  /** Image index error */
  HS_ERROR_INVALID_IMAGE_INDEX,
  /** Image size error */
  HS_ERROR_INVALID_IMAGE_SIZE,
  /** Image size mismatch */
  HS_ERROR_IMAGE_SIZE_MISMATCH,
  /** Wavelength mismatch */
  HS_ERROR_WAVELENGTH_MISMATCH,
  /** Failure to size adjustment */
  HS_ERROR_ADJUST_SIZE,
  /** Index error */
  HS_ERROR_INVALID_INDEX,
  /** Not supported */
  HS_ERROR_NOT_SUPPORTED,
  /** Cannot find path for calibration data */
  HS_ERROR_CALIBRATION_PATH_NOT_FOUND,
  /** Cannot find path */
  HS_ERROR_PATH_DOES_NOT_EXIST,
  /** Cannot find file */
  HS_ERROR_CANNOT_FIND_FILE,
  /** Cannot read file */
  HS_ERROR_CANNOT_LOAD_FILE,
  /** Canndot write file */
  HS_ERROR_CANNOT_SAVE_FILE,
  /** File already Loaded */
  HS_ERROR_ALREADY_LOADED,
  /** Cannot create folder */
  HS_ERROR_CANNOT_CREATE_DIR,
  /** Invalid file format */
  HS_ERROR_INVALID_FILE_FORMAT,
  /** Invalid operation */
  HS_ERROR_INVALID_OPERATION,
  /** System initializing error */
  HS_ERROR_SYSTEM_INITIALIZE,
  /** System initializing error */
  HS_ERROR_NOT_INITIALIZED,
  /** Device is not available */
  HS_ERROR_NO_CONNECTABLE_DEVICE,
  /** Device is not found */
  HS_ERROR_CANNOT_FIND_CONNECTED_DEVICE,
  /** Cannot connect to device */
  HS_ERROR_CANNOT_CONNECT_TO_DEVICE,
  /** Memory error */
  HS_ERROR_MEMORY,
  /** Saturation error */
  HS_ERROR_SATURATION,
  /** Failure in starting live */
  HS_ERROR_CANNOT_START_LIVE,
  /** Failure in stopping live */
  HS_ERROR_CANNOT_STOP_LIVE,
  /** Failure in retrieving live image */
  HS_ERROR_CANNOT_RETRIEVE_LIVE_IMAGE,
  /** Failure in starting scan */
  HS_ERROR_CANNOT_START_SCAN,
  /** Failure in finishing scan */
  HS_ERROR_CANNOT_STOP_SCAN,
  /** Measurement interruption */
  HS_ERROR_PROCESS_INTERRUPTED,
  /** Measurement time-out */
  HS_ERROR_PROCESS_TIMEOUT,
  /** Optimize error (too dark) */
  HS_ERROR_OPTIMIZE_TOO_DARK,
  /** Optimize error (too bright) */
  HS_ERROR_OPTIMIZE_TOO_BRIGHT,
} HsError;

/**
 * @brief Enumeration for device type
 *
 * @version Ver 1.5.0
 */
typedef enum _HsDeviceType {
  /** SR5000 */
  HS_DEVICE_SR5000,
  /** SR10[for future development] */
  HS_DEVICE_SR10,
  /** SR5000H */
  HS_DEVICE_SR5000H,
  /** Undefined */
  HS_DEVICE_UNKNOWN
} HsDeviceType;

/**
 * @brief Enumeration for binning type
 *
 * @version Ver 1.5.0
 */
typedef enum _HsBinningType {
  /** Binning 1x1 */
  HS_BINNING_TYPE1,
  /** Binning 2x2 */
  HS_BINNING_TYPE2,
  /** Binning 4x4 */
  HS_BINNING_TYPE4,
  /** Total number of binning types */
  HS_BINNING_TYPE_MAXCNT
} HsBinningType;

/**
 * @brief Enumeration for lens type
 *
 * @version Ver 1.5.0
 */
typedef enum _HsLensType {
  /** Wide(Standard) */
  HS_LENS_TYPE_WIDE,
  /** Standard */
  HS_LENS_TYPE_STANDARD,
  /** Telescopic */
  HS_LENS_TYPE_TELE,
  /** Macro */
  HS_LENS_TYPE_MACRO,
  /** Total number of lens types */
  HS_LENS_TYPE_MAXCNT
} HsLensType;

/**
 * @brief Enumeration for measurement timing type
 *
 * @version Ver 1.5.0
 */
typedef enum _HsMeasureTimingType {
  /** Serial measurement */
  HS_MEASURE_TYPE_SERIAL,
  /** Interval measurement */
  HS_MEASURE_TYPE_INTERVAL,
  /** Total number of measurement timing types */
  HS_MEASURE_TYPE_MAXCNT
} HsMeasureTimingType;

/**
 * @brief Enumeration for tristimulus
 *
 * @version Ver 1.5.0
 */
typedef enum _HsTristimulus {
  /** Tristimulus X */
  HS_TRISTIMULUS_X,
  /** Tristimulus Y */
  HS_TRISTIMULUS_Y,
  /** Tristimulus Z */
  HS_TRISTIMULUS_Z,
  /** Total number of tristimulus values */
  HS_TRISTIMULUS_MAXCNT
} HsTristimulus;

/**
 * @brief Enumeration for execution mode
 *
 * @version Ver 1.5.0
 */
typedef enum _HsExecModeType {
  /** Auto */
  HS_EXEC_MODE_TYPE_AUTO,
  /** Manual */
  HS_EXEC_MODE_TYPE_MANUAL,
  /** Total number of execution mode */
  HS_EXEC_MODE_TYPE_MAXCNT
} HsExecModeType;

/**
 * @brief Enumeration for sacn mode type
 *
 * @version Ver 1.5.0
 */
typedef enum _HsScanModeType {
  /** Normal */
  HS_SCAN_MODE_TYPE_NORMAL,
  /** High speed */
  HS_SCAN_MODE_TYPE_HIGH_SPEED,
  /** High precision */
  HS_SCAN_MODE_TYPE_HIGH_PRECISION,
  /** Total number of scan mode types */
  HS_SCAN_MODE_TYPE_MAXCNT
} HsScanModeType;

/**
 * @brief Enumeration for trigger mode type
 *
 * @version Ver 1.5.0
 */
typedef enum _HsTriggerModeType {
  /** Hard Trigger */
  HS_TRIGGER_MODE_TYPE_HARD,
  /** Soft Trigger */
  HS_TRIGGER_MODE_TYPE_SOFT,
  /** Total number of trigger mode types */
  HS_TRIGGER_MODE_TYPE_MAXCNT
} HsTriggerModeType;

/**
 * @brief Enumeration for trigger activation type
 *
 * @version Ver 1.5.0
 */
typedef enum _HsTriggerActivationType {
  /** Rising */
  HS_TRIGGER_ACTIVATION_RISING_EDGE,
  /** Falling */
  HS_TRIGGER_ACTIVATION_FALLING_EDGE,
  /** Total number of trigger activation types */
  HS_TRIGGER_ACTIVATION_MAXCNT
} HsTriggerActivationType;

/**
 * @brief Enumeration for measurement type
 *
 * @version Ver 1.5.0
 */
typedef enum _HsMeasurementType {
  /** Spectral measurement */
  HS_MEASUREMENT_TYPE_SPECTRAL,
  /** Filter measurement */
  HS_MEASUREMENT_TYPE_XYZ,
  /** Total number of measurement types */
  HS_MEASUREMENT_TYPE_MAXCNT
} HsMeasurementType;

/**
 * @brief Enumeration for filter type
 *
 * @version Ver 1.5.0
 */
typedef enum _HsFilterType {
  /** Spectroscopic filter */
  HS_FILTER_TYPE_SPECTRAL,
  /** X filter */
  HS_FILTER_TYPE_X,
  /** Y filter */
  HS_FILTER_TYPE_Y,
  /** Z filter */
  HS_FILTER_TYPE_Z,
  /** Total number of filter types */
  HS_FILTER_TYPE_MAXCNT
} HsFilterType;

/**
 * @brief Enumeration for gain type
 *
 * @version Ver 1.5.0
 */
typedef enum _HsGainType {
  /** Gain 1 */
  HS_GAIN_TYPE_01,
  /** Gain 4 */
  HS_GAIN_TYPE_04,
  /** Gain 8 */
  HS_GAIN_TYPE_08,
  /** Gain 16 */
  HS_GAIN_TYPE_16,
  /** Total number of gain types */
  HS_GAIN_TYPE_MAXCNT
} HsGainType;

/**
 * @brief Enumeration for data type
 *
 * @version Ver 1.5.0
 */
typedef enum _HsDataType {
  /** Tristimulus X */
  HS_DATA_TYPE_TRISTIMULUS_X,
  /** Tristimulus Y */
  HS_DATA_TYPE_TRISTIMULUS_Y,
  /** Tristimulus Z */
  HS_DATA_TYPE_TRISTIMULUS_Z,
  /** Chromaticity x */
  HS_DATA_TYPE_CHROMATICITY_X,
  /** Chromaticity y */
  HS_DATA_TYPE_CHROMATICITY_Y,
  /** Chromaticity u' */
  HS_DATA_TYPE_CHROMATICITY_U,
  /** Chromaticity v' */
  HS_DATA_TYPE_CHROMATICITY_V,
  /** Color temperature */
  HS_DATA_TYPE_COLOR_TEMPERATURE,
  /** Deviation */
  HS_DATA_TYPE_DEVIATION,
  /** Dominant wavelength */
  HS_DATA_TYPE_DOMINANT_WAVELENGTH,
  /** Exciatation purity */
  HS_DATA_TYPE_EXCITATION_PURITY,
  /** L*a*b*(L*) */
  HS_DATA_TYPE_LAB_L,
  /** L*a*b*(a*) */
  HS_DATA_TYPE_LAB_A,
  /** L*a*b*(b*) */
  HS_DATA_TYPE_LAB_B,
  /** L*C*h(C*) */
  HS_DATA_TYPE_LCH_C,
  /** L*C*h(h) */
  HS_DATA_TYPE_LCH_H,
  /** RGB(R) */
  HS_DATA_TYPE_RGB_R,
  /** RGB(G) */
  HS_DATA_TYPE_RGB_G,
  /** RGB(B) */
  HS_DATA_TYPE_RGB_B,
  /** HVC(H) */
  HS_DATA_TYPE_HVC_H,
  /** HVC(V) */
  HS_DATA_TYPE_HVC_V,
  /** HVC(C) */
  HS_DATA_TYPE_HVC_C,
  /** Total number of data types */
  HS_DATA_TYPE_MAXCNT
} HsDataType;

/**
 * @brief Enumeration for spot data type
 *
 * @version Ver 1.5.0
 */
typedef enum _HsSpotDataType {
  /** Random spot */
  HS_SPOT_DATA_TYPE_RANDOM,
  /** Standard spot */
  HS_SPOT_DATA_TYPE_STANDARD,
  /** Matrix spot */
  HS_SPOT_DATA_TYPE_MATRIX,
  /** Total number of spot types */
  HS_SPOT_DATA_TYPE_MAXCNT
} HsSpotDataType;

/**
 * @brief Enumeration for Spot/Area shape type
 *
 * @version Ver 1.5.0
 */
typedef enum _HsAreaShapeType {
  /** Circle */
  HS_AREA_SHAPE_TYPE_CIRCLE,
  /** Square */
  HS_AREA_SHAPE_TYPE_SQUARE,
  /** Polygon */
  HS_AREA_SHAPE_TYPE_POLYGON,
  /** Total number of shape types */
  HS_AREA_SHAPE_TYPE_MAXCNT
} HsAreaShapeType;

/**
 * @brief Enumeration for fixed standard type.
 *        This type is based on japanese domestic standard.
 *
 * @version Ver 1.5.0
 */
typedef enum _HsFixedStandardType {
  /** Standard A */
  HS_FIXED_STANDARD_TYPE_STANDARD_A,
  /** Standard B */
  HS_FIXED_STANDARD_TYPE_STANDARD_B,
  /** Equal size A */
  HS_FIXED_STANDARD_TYPE_EQUALITY_A,
  /** Equal size B */
  HS_FIXED_STANDARD_TYPE_EQUALITY_B,
  /** Equal distance from perimeter */
  HS_FIXED_STANDARD_TYPE_EQUALITY_OUTER,
  /** Total number of standard spot types */
  HS_FIXED_STANDARD_TYPE_MAXCNT
} HsFixedStandardType;

/**
 * @brief Enumeration for judgment area type[for future development]
 * @attention @b This definition is not working in this version. It may change in future version.
 *
 * @version Ver ?.?.?
 */
typedef enum _HsJudgmentAreaType {
  /** Chromaticity xy */
  HS_JUDGMENT_AREA_TYPE_XY,
  /** Chromaticity u'v' */
  HS_JUDGMENT_AREA_TYPE_UV,
  /** L*C*h(C*), L*C*h(h) */
  HS_JUDGMENT_AREA_TYPE_CH,
  /** Total number of judgment area types */
  HS_JUDGMENT_AREA_TYPE_MAXCNT
} HsJudgmentAreaType;

/**
 * @brief Enumeration for judgment group type[for future development]
 * @attention @b This definition is not working in this version. It may change in future version.
 *
 * @version Ver ?.?.?
 */
typedef enum _HsJudgmentGroupType {
  /** Judgment by light source(Tristimulus X, Tristimulus Y, Tristimulus Z, Chromaticity x, Chromaticity y, Chromaticity
     u', Chromaticity v') */
  HS_JUDGMENT_GROUP_TYPE_SOURCE,
  /** Judgment by material color(L*a*b*(L*), L*a*b*(a*), L*a*b*(b*), L*C*h(C*), L*C*h(h)) */
  HS_JUDGMENT_GROUP_TYPE_MATERIAL,
  /** Total number of judgment group types */
  HS_JUDGMENT_GROUP_TYPE_MAXCNT
} HsJudgmentGroupType;

/**
 * @brief Enumeration for judgment type[for future development]
 * @attention @b This definition is not working in this version. It may change in future version.
 *
 * @version Ver ?.?.?
 */
typedef enum _HsJudgmentType {
  /** Upper/Lower */
  HS_JUDGMENT_TYPE_MINMAX,
  /** Ratio to max */
  HS_JUDGMENT_TYPE_PERCENTAGE,
  /** Central-Diff */
  HS_JUDGMENT_TYPE_DISTANCE,
  /** Total number of judgment types */
  HS_JUDGMENT_TYPE_MAXCNT
} HsJudgmentType;

/**
 * @brief Enumeration for judgment result type[for future development]
 * @attention @b This definition is not working in this version. It may change in future version.
 *
 * @version Ver ?.?.?
 */
typedef enum _HsJudgmentResultType {
  /** No decision */
  HS_JUDGMENT_RESULT_DISABLED,
  /** No data */
  HS_JUDGMENT_RESULT_INVALID,
  /** Accepted */
  HS_JUDGMENT_RESULT_ACCEPTED,
  /** Rejected */
  HS_JUDGMENT_RESULT_REJECTED,
  /** Total number of judgment result types */
  HS_JUDGMENT_RESULT_MAXCNT
} HsJudgmentResultType;

/**
 * @brief Enumeration for CSV output type
 *
 * @version Ver 1.5.0
 */
typedef enum _HsCsvType {
  /** All pixel data */
  HS_CSV_TYPE_ALL_PIXEL,
  /** Time series(Unavailable for SDK) */
  HS_CSV_TYPE_TIME_SERIES,
  /** Random spot */
  HS_CSV_TYPE_RANDOM,
  /** Standard spot */
  HS_CSV_TYPE_STANDARD,
  /** Matrix spot */
  HS_CSV_TYPE_MATRIX,
  /** Section */
  HS_CSV_TYPE_SECTION,
  /** Total number of CSV output types */
  HS_CSV_TYPE_MAXCNT
} HsCsvType;

/**
 * @brief Enumeration for CSV output data type
 *
 * @version Ver 1.5.0
 */
typedef enum _HsOutputDataValuesType {
  /** Tristimulus X */
  HS_OUTPUT_DATA_VALUES_TYPE_TRISTIMULUS_X,
  /** Tristimulus Y */
  HS_OUTPUT_DATA_VALUES_TYPE_TRISTIMULUS_Y,
  /** Tristimulus Z */
  HS_OUTPUT_DATA_VALUES_TYPE_TRISTIMULUS_Z,
  /** Chromaticity xy */
  HS_OUTPUT_DATA_VALUES_TYPE_CHROMATICITY_XY,
  /** Chromaticity u'v' */
  HS_OUTPUT_DATA_VALUES_TYPE_CHROMATICITY_UV,
  /** Color temperature/Deviation */
  HS_OUTPUT_DATA_VALUES_TYPE_TEMPERATURE_DEVIATION,
  /** Dominant wavelength */
  HS_OUTPUT_DATA_VALUES_TYPE_WAVELENGH_PURITY,
  /** L*a*b* */
  HS_OUTPUT_DATA_VALUES_TYPE_LAB,
  /** L*C*h */
  HS_OUTPUT_DATA_VALUES_TYPE_LCH,
  /** RGB */
  HS_OUTPUT_DATA_VALUES_TYPE_RGB,
  /** Total number of CSV output data types */
  HS_OUTPUT_DATA_VALUES_TYPE_MAXCNT
} HsOutputDataValuesType;

/**
 * @brief Enumeration for CSV output admission decision attribute type[for future development]
 * @attention @b This definition is not working in this version. It may change in future version.
 *
 * @version Ver ?.?.?
 */
typedef enum _HsOutputJudgmentType {
  /** Total */
  HS_OUTPUT_JUDGMENT_TYPE_TOTAL_JUDGMENT,
  /** Tristimulus X */
  HS_OUTPUT_JUDGMENT_TYPE_TRISTIMULUS_X,
  /** Tristimulus Y */
  HS_OUTPUT_JUDGMENT_TYPE_TRISTIMULUS_Y,
  /** Tristimulus Z */
  HS_OUTPUT_JUDGMENT_TYPE_TRISTIMULUS_Z,
  /** Chromaticity xy */
  HS_OUTPUT_JUDGMENT_TYPE_CHROMATICITY_XY,
  /** Chromaticity u'v' */
  HS_OUTPUT_JUDGMENT_TYPE_CHROMATICITY_UV,
  /** L*a*b* */
  HS_OUTPUT_JUDGMENT_TYPE_LAB,
  /** L*C*h(C*)/L*C*h(h) */
  HS_OUTPUT_JUDGMENT_TYPE_LCH,
  /** Chromaticity xy area */
  HS_OUTPUT_JUDGMENT_TYPE_CHROMATICITY_XY_AREA,
  /** Chromaticity u'v' area */
  HS_OUTPUT_JUDGMENT_TYPE_CHROMATICITY_UV_AREA,
  /** L*C*h(C*)/L*C*h(h) area */
  HS_OUTPUT_JUDGMENT_TYPE_LCH_AREA,
  /** Total number of judgment CSV output types */
  HS_OUTPUT_JUDGMENT_TYPE_MAXCNT
} HsOutputJudgmentType;

/**
 * @brief Enumeration for standard white point type(Standard light type)
 *
 * @version Ver 1.5.0
 */
typedef enum _HsWhitePointType {
  /** Standard illuminant A */
  HS_WHITE_POINT_A,
  /** Standard illuminant B */
  HS_WHITE_POINT_B,
  /** Standard illuminant C */
  HS_WHITE_POINT_C,
  /** Standard illuminant D65 */
  HS_WHITE_POINT_D65,
  /** User defined */
  HS_WHITE_POINT_USER,
  /** Total number of standard white point types */
  HS_WHITE_POINT_MAXCNT
} HsWhitePointType;

/**
 * @brief Enumeration for section data type
 *
 * @version Ver 1.5.0
 */
typedef enum _HsSectionDataType {
  /** Cross */
  HS_SECTION_CROSS,
  /** Diagonal */
  HS_SECTION_DIAGONAL
} HsSectionDataType;

/**
 * @brief Enumeration for luminosity data type
 *
 * @version Ver 1.5.0
 */
typedef enum _HsLuminosityDataType {
  /** 1nm pitch */
  HS_LUMINOSITY_DATA_TYPE_1NM,
  /** 5nm pitch */
  HS_LUMINOSITY_DATA_TYPE_5NM
} HsLuminosityDataType;

/**
 * @brief Enumeration for luminosity factor type
 *
 * @version Ver 1.5.0
 */
typedef enum _HsLuminosityFactorType {
  /** Total coefficient of 1nm pitch */
  HS_LUMINOSITY_FACTOR_TYPE_1NM_ALL,
  /** Total coefficient of 5nm pitch */
  HS_LUMINOSITY_FACTOR_TYPE_5NM_ALL,
  /** XYZ individual coefficient of 1nm pitch */
  HS_LUMINOSITY_FACTOR_TYPE_1NM_XYZ,
  /** XYZ individual coefficient of 5nm pitch */
  HS_LUMINOSITY_FACTOR_TYPE_5NM_XYZ
} HsLuminosityFactorType;

/**
 * @brief Enumeration for image difference type
 *
 * @version Ver 1.5.0
 */
typedef enum _HsImageDifferenceType {
  /** Subtraction */
  HS_IMAGE_DIFFERENCE_TYPE_DIFF,
  /** Absolute value of subtraction */
  HS_IMAGE_DIFFERENCE_TYPE_DIFF_ABS,
  /** Ratio */
  HS_IMAGE_DIFFERENCE_TYPE_RATIO,
  /** Total number of image comparison types */
  HS_IMAGE_DIFFERENCE_TYPE_MAXCNT
} HsImageDifferenceType;

/**
 * @brief Enumeration of image type for the application software.
 *
 * @version Ver 1.5.0
 */
typedef enum _HsImageDataType {
  /** Tristimulus X */
  HS_IMAGE_DATA_TYPE_TRISTIMULUS_X,
  /** Tristimulus Y */
  HS_IMAGE_DATA_TYPE_TRISTIMULUS_Y,
  /** Tristimulus Z */
  HS_IMAGE_DATA_TYPE_TRISTIMULUS_Z,
  /** Chromaticity x */
  HS_IMAGE_DATA_TYPE_CHROMATICITY_X,
  /** Chromaticity y */
  HS_IMAGE_DATA_TYPE_CHROMATICITY_Y,
  /** Chromaticity u' */
  HS_IMAGE_DATA_TYPE_CHROMATICITY_U,
  /** Chromaticity v' */
  HS_IMAGE_DATA_TYPE_CHROMATICITY_V,
  /** Color temperature */
  HS_IMAGE_DATA_TYPE_COLOR_TEMPERATURE,
  /** L*a*b*(L*) */
  HS_IMAGE_DATA_TYPE_LAB_L,
  /** L*a*b*(a*) */
  HS_IMAGE_DATA_TYPE_LAB_A,
  /** L*a*b*(b*) */
  HS_IMAGE_DATA_TYPE_LAB_B,
  /** RGB */
  HS_IMAGE_DATA_TYPE_RGB,
  /** Spectral radiance */
  HS_IMAGE_DATA_TYPE_SPECTRAL_RADIANCE,
  /** Total number of image data types */
  HS_IMAGE_DATA_TYPE_MAXCNT
} HsImageDataType;

/**
 * @brief Enumeration of color type for the application software.
 *
 * @version Ver 1.5.0
 */
typedef enum _HsImageColorType {
  /** Pseudo color */
  HS_IMAGE_COLOR_TYPE_PSEUDO,
  /** Pseudo color(Contour) */
  HS_IMAGE_COLOR_TYPE_PSEUDO_CONTOUR,
  /** Grayscale */
  HS_IMAGE_COLOR_TYPE_GRAYSCALE,
  /** Grayscale(Contour) */
  HS_IMAGE_COLOR_TYPE_GRAYSCALE_CONTOUR,
  /** RGB */
  HS_IMAGE_COLOR_TYPE_RGB,
  /** Total number of image color types */
  HS_IMAGE_COLOR_TYPE_MAXCNT
} HsImageColorType;

/**
 * @brief Enumeration of pseudo color type for the application software.
 *
 * @version Ver 1.5.0
 */
typedef enum _HsPseudoColorSettingHex {
  /** Contour */
  HS_PSEUDO_CONTOUR = 0x00000001,
  /** Grayscale */
  HS_PSEUDO_GRAYSCALE = 0x00000002
} HsPseudoColorSettingHex;

/**
 * @brief Enumeration for processing status
 *
 * @version Ver 1.5.0
 */
typedef enum _HsRunningStatus {
  /** None */
  HS_STATUS_NONE,
  /** Loading data */
  HS_STATUS_LOADING_DATA,
  /** Creating spot data */
  HS_STATUS_CREATING_SPOT_DATA,
  /** Writing CSV data */
  HS_STATUS_WRITING_CSV,
  /** On optimization */
  HS_STATUS_OPTIMIZING,
  /** On scanning */
  HS_STATUS_SCANNING,
  /** On processing */
  HS_STATUS_PROCESSING,
  /** On searching spectrum */
  HS_STATUS_SEARCH_SPECTRUM,
  /** On simulation */
  HS_STATUS_SIMULATION
} HsRunningStatus;

/**
 * @brief Enumeration for saturation detection
 *
 * @version Ver 1.5.0
 */
typedef enum _HsSaturationDetectionType {
  /** None */
  HS_SATURATION_NONE,
  /** The measurement will be interrupted when saturation is detected */
  HS_SATURATION_INTERRUPT,
  /** Saturated pixels are recorded on the image */
  HS_SATURATION_OUTPUT,
} HsSaturationDetectionType;

/**
 * @brief Enumeration for white plate correction type
 *
 * @version Ver 1.5.0
 */
typedef enum _HsWhitePlateCorrectionType {
  /** Use measurement data file as white plate data */
  HS_WHITEPLATE_FILE,
  /** Use single white point data(Xn, Yn, Zn) */
  HS_WHITEPLATE_POINT,
} HsWhitePlateCorrectionType;

/**
 * @brief Enumeration for image rotation
 *
 * @version Ver 1.5.0
 */
typedef enum _HsImageRotationType {
  /** Rotation none */
  HS_IMAGE_ROTATION_NONE,
  /** Rotation 180 degree */
  HS_IMAGE_ROTATION_180,
} HsImageRotationType;

/**
 * @brief Structure for point
 *
 * @version Ver 1.5.0
 */
typedef struct _HsPoint {
  /** x */
  int x;
  /** y */
  int y;
} HsPoint;

/**
 * @brief Structure for point 64f
 *
 * @version Ver 1.5.0
 */
typedef struct _HsPoint64f {
  /** x */
  double x;
  /** y */
  double y;
} HsPoint64f;

/**
 * @brief Structure for size
 *
 * @version Ver 1.5.0
 */
typedef struct _HsSize {
  /** width */
  int width;
  /** height */
  int height;
} HsSize;

/**
 * @brief Structure for size 64f
 *
 * @version Ver 1.5.0
 */
typedef struct _HsSize64f {
  /** width */
  double width;
  /** height */
  double height;
} HsSize64f;

/**
 * @brief Structure for RECT
 *
 * @version Ver 1.5.0
 */
typedef struct _HsRect {
  /** x */
  int x;
  /** y */
  int y;
  /** width */
  int width;
  /** height */
  int height;
} HsRect;

/**
 * @brief Structure for RECT(64f)
 *
 * @version Ver 1.5.0
 */
typedef struct _HsRect64f {
  /** x */
  double x;
  /** y */
  double y;
  /** width */
  double width;
  /** height */
  double height;
} HsRect64f;

/**
 * @brief Structure for image(32f)
 * @details Value of each pixel is single floating point.
 *
 * @version Ver 1.5.0
 */
typedef struct _HsImage32f {
  /** width */
  int width;
  /** height */
  int height;
  /** Address of pixel array */
  float *pixels;
} HsImage32f;

/**
 * @brief Structure for image(8u3).
 * @details The value of each pixel is 0 to 255 that is consist of 3 channels(R, G, B).
 *
 * @version Ver 1.5.0
 */
typedef struct _HsImage8u3 {
  /** width */
  int width;
  /** height */
  int height;
  /** Address of pixel array */
  unsigned char *pixels;
} HsImage8u3;

/**
 * @brief Structure for configuration information
 *
 * @version Ver 1.5.0
 */
typedef struct _HsConfiguration {
  /** The number of devices which are installed */
  int num_installed;
  /** The number of devices which are connected */
  int num_connected;
  /** Character array of product ids that are installed */
  char installed_product_ids[HS_DEVICE_COUNT_MAX][HS_PRODUCT_ID_CHARACTERS_MAX];
  /** Character array of product ids that are connected */
  char connected_product_ids[HS_DEVICE_COUNT_MAX][HS_PRODUCT_ID_CHARACTERS_MAX];
} HsConfiguration;

/**
 * @brief Structure for device information
 *
 * @version Ver 1.5.0
 */
typedef struct _HsDeviceInfo {
  /** Device type */
  HsDeviceType device_type;
  /** Product id of devices */
  char product_id[HS_PRODUCT_ID_CHARACTERS_MAX];
  /** Mac address[for future development] */
  unsigned char mac_address[6];
  /** IP address[for future development] */
  unsigned char ip_address[4];
  /** Subnet mask[for future development] */
  unsigned char subnet_mask[4];
  /** Default gateway[for future development] */
  unsigned char default_gateway[4];
  /** Available lens types */
  HsLensType lens_types[HS_DEVICE_LENS_TYPE_MAX];
  /** Available binning types */
  HsBinningType binning_types[HS_DEVICE_BINNING_TYPE_MAX];
  /** Available gain types */
  HsGainType gain_types[HS_DEVICE_GAIN_TYPE_MAX];
  /** Maximum integration time */
  double max_integration_time[HS_FILTER_TYPE_MAXCNT];
  /** Minimum integration time */
  double min_integration_time[HS_FILTER_TYPE_MAXCNT];
} HsDeviceInfo;

/**
 * @brief Structure for trigger configuration
 *
 * @version Ver 1.5.0
 */
typedef struct _HsTriggerConfig {
  /** trigger type */
  HsTriggerModeType mode_type;
  /** trigger activation type */
  HsTriggerActivationType activation_type;
  /** trigger delay time */
  double delay_time;
} HsTriggerConfig;

/**
 * @brief Structure for live setting
 *
 * @version Ver 1.5.0
 */
typedef struct _HsLiveSetting {
  /** Binning type */
  HsBinningType binning_type;
  /** Gain */
  HsGainType gain;
  /** Integration time */
  double integration_time;
  /** ROI */
  HsRect roi;
  /** Trigger configuration */
  HsTriggerConfig trigger_config;
  /** Rotation degree of the image */
  HsImageRotationType image_rotation_type;
} HsLiveSetting;

/**
 * @brief Structure for spot
 *
 * @version Ver 1.5.0
 */
typedef struct _HsSpotArea {
  /** spot id */
  unsigned short id;
  /** enable/disable flag(for data sheet of app)@endif */
  bool enable;
  /** Spot/area shape flag */
  HsAreaShapeType shape;
  /** grid x(Matrix spot only) */
  int grid_x;
  /** grid y(Matrix spot only) */
  int grid_y;
  /** x coordinate of center of the spot(Not available when spot shape is polygon) */
  int x;
  /** y coordinate of center of the spot(Not available when spot shape is polygon) */
  int y;
  /** Width of spot [mm](Not available when spot shape is polygon) */
  double width;
  /** Height of spot [mm](Not available when spot shape is polygon) */
  double height;
  /** Point list size of vertex of polygon */
  unsigned short point_count;
  /** Pointer to data of vertex point of polygon */
  void *point_data;
  /** Threshold value of tristimulus value X in the spot */
  float threshold_x;
  /** Threshold value of tristimulus value Y in the spot */
  float threshold_y;
  /** Threshold value of tristimulus value Z in the spot */
  float threshold_z;
  /** Base spot flag */
  bool base_spot;
  /** Chromaticity xy area no of judgment[for future development] */
  int chrom_xy_ok_area_no;
  /** Chromaticity u'v' area no of judgment[for future development] */
  int chrom_uv_ok_area_no;
  /** L*C*h(C*)/L*C*h(h) area no of judgment[for future development] */
  int lch_ch_ok_area_no;
} HsSpotArea;

/**
 * @brief Structure for spot list
 *
 * @version Ver 1.5.0
 */
typedef struct _HsSpotAreaList {
  /** list item count */
  unsigned short count;
  /** spot/area list pointer */
  void *items;
} HsSpotAreaList;

/**
 * @brief Structure for random spot setting
 *
 * @version Ver 1.5.0
 */
typedef struct _HsRandomSpotSetting {
  /** Binning type */
  HsBinningType binning_type;
  /** measurement range of the image */
  HsRect measurement_roi;
  /** Trimming range of image */
  HsRect trimming;
  /** Spot default shape */
  HsAreaShapeType init_shape;
  /** Spot default size */
  HsSize64f init_size;
  /** Spot id re-numbering flag */
  bool renumbering;
  /** Apply flag of tristimumlus threshold */
  bool apply_threshold;
} HsRandomSpotSetting;

/**
 * @brief Structure for standard spot setting
 *
 * @version Ver 1.5.0
 */
typedef struct _HsStandardSpotSetting {
  /** Binning type */
  HsBinningType binning_type;
  /** measurement range of the image */
  HsRect measurement_roi;
  /** Trimming range of image */
  HsRect trimming;
  /** Spot default shape */
  HsAreaShapeType init_shape;
  /** Spot default size */
  HsSize64f init_size;
  /** enable/disable flag of equal size from center */
  bool center_equality_enable;
  /** Spot count of equal size from center(X axis) */
  int ce_spot_count_x;
  /** Spot count of equal size from center(Y axis) */
  int ce_spot_count_y;
  /** Spot interval of equal size from center */
  HsSize64f ce_interval;
  /** Type of fixed standard */
  HsFixedStandardType fs_type;
  /** Spot count of fixed standard */
  unsigned short fs_spot_count;
  /** Spot count of equal distance from perimeter(X axis) */
  int fs_outer_spot_count_x;
  /** Spot count of equal distance from perimeter(Y axis) */
  int fs_outer_spot_count_y;
  /** enable/disable flag of distance[mm] from the outer frame to spot */
  bool out_line_mm_enable;
  /** distance[mm] from the outer frame to spot */
  HsSize64f out_line_mm;
  /** enable/disable flag of distance[%] from the outer frame to spot */
  bool out_line_ratio_enable;
  /** distance[%] from the outer frame to spot */
  int out_line_ratio;
} HsStandardSpotSetting;

/**
 * @brief Structure for matrix spot setting
 *
 * @version Ver 1.5.0
 */
typedef struct _HsMatrixSpotSetting {
  /** Binning type */
  HsBinningType binning_type;
  /** measurement range of the image */
  HsRect measurement_roi;
  /** Lens type */
  HsLensType lens_type;
  /** Image Measurement distance[mm] */
  int measurement_distance;
  /** grid width */
  int grid_width;
  /** grid height */
  int grid_height;
  /** Trimming range of image */
  HsRect trimming;
} HsMatrixSpotSetting;

/**
 * @brief Structure for spot definition
 *
 * @version Ver 1.5.0
 */
typedef struct _HsSpotDef {
  /** Date and time of creation(yyyy/MM/dd hh:mm:ss.fff) */
  char datetime[HS_DATE_TIME_LENGTH];
  /** Comment */
  char comment[HS_COMMENT_LENGTH];
  /** Spot data type */
  HsSpotDataType type;
  /** Random spot setting (Random spot only) */
  HsRandomSpotSetting rdm_spot_setting;
  /** Random spot setting (Random spot only) */
  HsStandardSpotSetting std_spot_setting;
  /** Matrix spot setting (Matrix spot only) */
  HsMatrixSpotSetting mtx_spot_setting;
  /** spot list */
  HsSpotAreaList spot_list;
} HsSpotDef;

/**
 * @brief Structure for judgment area(For future development)
 * @attention @b This definition is not working in this version. It may change in future version.
 *
 * @version Ver ?.?.?
 */
typedef struct _HsJudgmentArea {
  /** id */
  unsigned short id;
  /** enable/disable flag */
  bool enable;
  /** area shape */
  HsAreaShapeType shape;
  /** center location of the area(Not available when area shape of a polygon) */
  HsRect64f pos;
  /** Point list size of vertex of polygon */
  unsigned short point_count;
  /** Pointer to data of vertex point of polygon */
  void *point_data;
} HsJudgmentArea;

/**
 * @brief Structure for judgment data area[for future development]
 * @attention @b This definition is not working in this version. It may change in future version.
 *
 * @version Ver ?.?.?
 */
typedef struct _HsJudgmentAreaData {
  /** Date and time of creation(yyyy/MM/dd hh:mm:ss.fff) */
  char datetime[HS_DATE_TIME_LENGTH];
  /** Comment */
  char comment[HS_COMMENT_LENGTH];
  /** Judgment area yype */
  HsJudgmentAreaType type;
  /** Judgment area type */
  HsJudgmentArea data_list[HS_JUDGMENT_AREA_COUNT_MAX][HS_JUDGMENT_CHILD_AREA_COUNT_MAX];
} HsJudgmentAreaData;

/**
 * @brief Structure for judgment criteria definition[for future development]
 * @attention @b This definition is not working in this version. It may change in future version.
 *
 * @version Ver ?.?.?
 */
typedef struct _HsJudgmentDef {
  /** Data type */
  HsDataType data_type;
  /** enable/disable flag */
  bool enable;
  /** Judgment type */
  HsJudgmentType judgment_type;
  /** Lower threshold */
  double lower_threshold;
  /** Upper threshold */
  double upper_threshold;
  /** Ratio to Maximum */
  double percent;
  /** Central-Diff */
  double distance;
} HsJudgmentDef;

/**
 * @brief Structure for judgment setting[for future development]
 * @attention @b This definition is not working in this version. It may change in future version.
 *
 * @version Ver ?.?.?
 */
typedef struct _HsJudgmentSettings {
  /** Date and time of creation(yyyy/MM/dd hh:mm:ss.fff) */
  char datetime[HS_DATE_TIME_LENGTH];
  /** Comment */
  char comment[HS_COMMENT_LENGTH];
  /** Judgment group type */
  HsJudgmentGroupType group_type;
  /** List of judgment criteria definition */
  HsJudgmentDef def[HS_DATA_TYPE_MAXCNT];
  /** enable/disable flag of judgment areas */
  bool area_enable[HS_JUDGMENT_AREA_TYPE_MAXCNT];
} HsJudgmentSettings;

/**
 * @brief Structure for statistics data
 *
 * @version Ver 1.5.0
 */
typedef struct _HsStatistics {
  /** Minimum value */
  double min;
  /** Maximum value */
  double max;
  /** Average value */
  double average;
  /** Center difference */
  double diff;
  /** Point of maximum value */
  HsPoint max_pixel;
  /** Point of minimum value */
  HsPoint min_pixel;
} HsStatistics;

/**
 * @brief Structure for spot data
 *
 * @version Ver 1.5.0
 */
typedef struct _HsSpotData {
  /** Spot id */
  int spot_id;
  /** Spot location */
  HsPoint location;
  /** Statistics */
  HsStatistics statistics[HS_DATA_TYPE_MAXCNT];
  /** Spectral statistics */
  HsStatistics spectral_statistics[HS_SPECTRAL_DATA_SIZE];
  /** Acceptance judgment result(By data type/for future develpment) */
  HsJudgmentResultType result_by_value[HS_DATA_TYPE_MAXCNT];
  /** Acceptance judgment result(By Area type/for future develpment) */
  HsJudgmentResultType result_by_area[HS_JUDGMENT_AREA_TYPE_MAXCNT];
  /** Admission decision area no (enclosed area no/for future develpment) */
  int result_area_no[HS_JUDGMENT_AREA_TYPE_MAXCNT];
  /** Total judgment result[for future development] */
  HsJudgmentResultType final_result;
} HsSpotData;

/**
 * @brief Structure for spot data list
 *
 * @version Ver 1.5.0
 */
typedef struct _HsSpotDataList {
  /** Spot data count */
  int count;
  /** Spot data list pointer */
  void *items;
} HsSpotDataList;

/**
 * @brief Structure for color setting of application software
 *
 * @version Ver 1.5.0
 */
typedef struct _HsColorSetting {
  /** Display maximum value */
  float level_max;
  /** Display minimum value */
  float level_min;
  /** Maximum color range[%] */
  float range_max;
  /** Minimum color range[%] */
  float range_min;
  /** Mask display flag */
  bool masked;
  /** Fixed display flag */
  bool locked;
  /** Mask Maximum value */
  float level_max_masked;
  /** Mask Minimum value */
  float level_min_masked;
} HsColorSetting;

/**
 * @brief Structure for measurement data
 *
 * @version Ver 1.5.0
 */
typedef struct _HsMeasurementData {
  /** Image width */
  int image_width;
  /** Image height */
  int image_height;
  /** Measurement start time(yyyy/MM/dd hh:mm:ss.fff) */
  char start_time[HS_DATE_TIME_LENGTH];
  /** Measurement end time(yyyy/MM/dd hh:mm:ss.fff) */
  char end_time[HS_DATE_TIME_LENGTH];
  /** Internal temperature(unused) */
  float internal_temperature;
  /** Statistics per measurement data type */
  HsStatistics statistics[HS_DATA_TYPE_MAXCNT];
  /** Statistics per each wavelength */
  HsStatistics spectral_statistics[HS_SPECTRAL_DATA_SIZE];
  /** Integration time[ms] at the measurement */
  double integration_time[HS_FILTER_TYPE_MAXCNT];
  /** Gain type at the measurement */
  HsGainType gain[HS_FILTER_TYPE_MAXCNT];
  /** Is saturated or not */
  bool is_saturated;
} HsMeasurementData;

/**
 * @brief Structure for measurement data file information
 *
 * @version Ver 1.5.0
 */
typedef struct _HsMeasurementDataFileInfo {
  /** Date and time of creation(yyyy/MM/dd hh:mm:ss.fff) */
  char datetime[HS_DATE_TIME_LENGTH];
  /** Comment */
  char comment[HS_COMMENT_LENGTH];
  /** File name */
  char filename[MAX_PATH];
} HsMeasurementDataFileInfo;

/**
 * @brief Structure for thumbnail setting
 *
 * @version Ver 1.5.0
 */
typedef struct _HsThumbnailSetting {
  /** Image data type */
  HsImageDataType image_data_type;
  /** Image color type */
  HsImageColorType image_color_type;
  /** Wavelength to show[nm] */
  int wavelength;
} HsThumbnailSetting;

/**
 * @brief Structure for RGB color setting
 *
 * @version Ver 1.5.0
 */
typedef struct _HsRGBColorSetting {
  /** RGB(R) adjustment value */
  int rgb_r_adjustment;
  /** RGB(G) adjustment value */
  int rgb_g_adjustment;
  /** RGB(B) adjustment value */
  int rgb_b_adjustment;
} HsRGBColorSetting;

/**
 * @brief Structure for setting to show the measument image
 *
 * @version Ver 1.5.0
 */
typedef struct _HsMeasurementDataImageSetting {
  /** Color setting(by Data type) */
  HsColorSetting color_setting[HS_DATA_TYPE_MAXCNT];
  /** Color setting(by Spectral wavelength) */
  HsColorSetting spectral_color_setting;
  /** Contour level */
  int contour_level;
  /** Display spectral wavelength */
  int current_wavelength;
  /** Trimming range of image */
  HsRect trimming_area;
  /** Thumbnail setting */
  HsThumbnailSetting thumbnail_settings[HS_THUMBNAILS_COUNT];
  /** RGB setting */
  HsRGBColorSetting rgb_color_setting;
} HsMeasurementDataImageSetting;

/**
 * @brief Structure for pseudo color setting
 *
 * @version Ver 1.5.0
 */
typedef struct _HsPseudoColorSetting {
  /** Color setting */
  HsColorSetting color_setting;
  /** Contour level */
  int contour_level;
  /** Color attribute type(Hex) */
  HsPseudoColorSettingHex flags;
} HsPseudoColorSetting;

/**
 * @brief Structure for interval condition setting
 *
 * @version Ver 1.5.0
 */
typedef struct _HsInterval {
  /** interval[s] */
  int interval_sec;
  /** times */
  int interval_count;
} HsInterval;

/**
 * @brief Structure for each filter condition
 *
 * @version Ver 1.5.0
 */
typedef struct _HsFilterCondition {
  /** Enable/Disable flag */
  bool enable;
  /** Integration time mode */
  HsExecModeType integration_time_type;
  /** Integration time */
  double integration_time;
  /** Gain mode */
  HsExecModeType gain_type;
  /** Gain type */
  HsGainType gain;
  /** Calculation flag from the frequency */
  bool frequency_calc_enable;
  /** Frequency value */
  int frequency_value;
  /** Average count */
  unsigned short averaging_count;
} HsFilterCondition;

/**
 * @brief Structure for measurement condition
 *
 * @version Ver 1.5.0
 */
typedef struct _HsMeasurementCondition {
  /** Device type */
  HsDeviceType device_type;
  /** Binning type */
  HsBinningType binning_type;
  /** Lens type */
  HsLensType lens_type;
  /** Measurement distance[mm] */
  int measure_distance;
  /** Measurement timing type */
  HsMeasureTimingType measure_timing;
  /** Continuous number of measurements */
  unsigned short serial_count;
  /** Time series measurement conditions */
  HsInterval intervals[HS_INTERVAL_CONDITION_COUNT_MAX];
  /** Flag for the first time only optimization */
  bool optimize_first_only;
  /** Interrupt flag at the interval time survey for time series measurement */
  bool interval_interrupt_enable;
  /** Layer flag */
  bool layer_mode;
  /** Layer count */
  unsigned short layer_count;
  /** Measurement type */
  HsMeasurementType measurement_type;
  /** Measurement conditions for each filter */
  HsFilterCondition filter_conditions[HS_FILTER_TYPE_MAXCNT];
  /** Saturation detection type */
  HsSaturationDetectionType saturation_detection_type;
  /** Scan mode type(for spectral measurement only) */
  HsScanModeType scan_type;
  /** trigger configuration */
  HsTriggerConfig trigger_config;
  /** Minimum wavelength of spectroscopic measurement(for spectral measurement only) */
  int measurement_wavelength_min;
  /** Maximum wavelength of spectroscopic measurement(for spectral measurement only) */
  int measurement_wavelength_max;
  /** Measurement wavelength step of spectroscopic measurement(for spectral measurement only) */
  int measurement_wavelength_step;
  /** Measurement area */
  HsRect measurement_range;
  /** Optimization area */
  HsRect optimization_area;
  /** Rotation degree of the image */
  HsImageRotationType image_rotation_type;
} HsMeasurementCondition;

/**
 * @brief Structure for diagonal correction
 *
 * @version Ver 1.5.0
 */
typedef struct _HsDiagonalCorrection {
  /** Date and time of creation(yyyy/MM/dd hh:mm:ss.fff) */
  char datetime[HS_DATE_TIME_LENGTH];
  /** Comment */
  char comment[HS_COMMENT_LENGTH];
  /** Image size */
  HsSize image_size;
  /** Coordinate before correction */
  HsPoint before_pos[4];
  /** Coordinate after correction */
  HsPoint after_pos[4];
} HsDiagonalCorrection;

/**
 * @brief Structure for diagonal correction list
 *
 * @version Ver 1.5.0
 */
typedef struct _HsDiagonalCorrectionList {
  /** Selected index */
  int selected_index;
  /** Count of diagonal correction */
  unsigned short count;
  /** Diagonal correction list */
  void *items;
} HsDiagonalCorrectionList;

/**
 * @brief Structure for color correction
 *
 * @version Ver 1.5.0
 */
typedef struct _HsColorCorrection {
  /** Date and time of creation(yyyy/MM/dd hh:mm:ss.fff) */
  char datetime[HS_DATE_TIME_LENGTH];
  /** Comment */
  char comment[HS_COMMENT_LENGTH];
  /** Selected flag */
  bool selected;
  /** The coefficient for tristimulus value X */
  float factor_x;
  /** The coefficient for tristimulus value Y */
  float factor_y;
  /** The coefficient for tristimulus value Z */
  float factor_z;
} HsColorCorrection;

/**
 * @brief Structure for color correction list
 *
 * @version Ver 1.5.0
 */
typedef struct _HsColorCorrectionList {
  /** Count of color correction */
  unsigned short count;
  /** Color correction list */
  void *items;
} HsColorCorrectionList;

/**
 * @brief Structure for luminosity data
 *
 * @version Ver 1.5.0
 */
typedef struct _HsLuminosityData {
  /** Date and time of creation(yyyy/MM/dd hh:mm:ss.fff) */
  char datetime[HS_DATE_TIME_LENGTH];
  /** Comment */
  char comment[HS_COMMENT_LENGTH];
  /** Luminosity data type */
  HsLuminosityDataType type;
  /** Factor */
  double factor[HS_VISIBLE_SPECTRAL_DATA_SIZE][HS_TRISTIMULUS_MAXCNT];
} HsLuminosityData;

/**
 * @brief Structure for luminosity data list
 *
 * @version Ver 1.5.0
 */
typedef struct _HsLuminosityDataList {
  /** Selected index */
  int selected_index;
  /** Count of luminosity data */
  unsigned short count;
  /** Luminosity data list */
  void *items;
} HsLuminosityDataList;

/**
 * @brief Structure for luminosity factor data
 *
 * @version Ver 1.5.0
 */
typedef struct _HsLuminosityFactorData {
  /** Date and time of creation(yyyy/MM/dd hh:mm:ss.fff) */
  char datetime[HS_DATE_TIME_LENGTH];
  /** Comment */
  char comment[HS_COMMENT_LENGTH];
  /** Selected flag */
  bool selected;
  /** Luminosity factor type */
  HsLuminosityFactorType type;
  /** Factor */
  double factor[HS_VISIBLE_SPECTRAL_DATA_SIZE][HS_TRISTIMULUS_MAXCNT];
} HsLuminosityFactorData;

/**
 * @brief Structure for luminosity factor data list
 *
 * @version Ver 1.5.0
 */
typedef struct _HsLuminosityFactorDataList {
  /** Count of luminosity factor data */
  unsigned short count;
  /** Luminosity factor data list */
  void *items;
} HsLuminosityFactorDataList;

/**
 * @brief Structure for area correction
 *
 * @version Ver 1.5.0
 */
typedef struct _HsAreaCorrection {
  /** Date and time of creation(yyyy/MM/dd hh:mm:ss.fff) */
  char datetime[HS_DATE_TIME_LENGTH];
  /** Comment */
  char comment[HS_COMMENT_LENGTH];
  /** Vertical division number */
  int rows;
  /** Horizontal division number */
  int cols;
  /** Coefficients of each area for tristimulus value X */
  float factor_x[HS_IMAGE_PARTITION_VERTICAL_MAX][HS_IMAGE_PARTITION_HORIZONTAL_MAX];
  /** Coefficients of each area for tristimulus value Y */
  float factor_y[HS_IMAGE_PARTITION_VERTICAL_MAX][HS_IMAGE_PARTITION_HORIZONTAL_MAX];
  /** Coefficients of each area for tristimulus value Z */
  float factor_z[HS_IMAGE_PARTITION_VERTICAL_MAX][HS_IMAGE_PARTITION_HORIZONTAL_MAX];
} HsAreaCorrection;

/**
 * @brief Structure for basic white point
 *
 * @version Ver 1.5.0
 */
typedef struct _HsBaseWhitePoint {
  /** Standard white point type(Standard light type) */
  HsWhitePointType type;
  /** User-defined white point (chromaticity xy) */
  HsPoint64f user_chrom_xy;
} HsBaseWhitePoint;

/**
 * @brief Structure for white plate correction
 *
 * @version Ver 1.5.0
 */
typedef struct _HsWhitePlateCorrection {
  /** The type of white plate correction */
  HsWhitePlateCorrectionType type;
  /** Tristimulus value of white point(Xn, Yn, Zn) */
  float tristimulus[HS_TRISTIMULUS_MAXCNT];
  /** file name of white plate correction */
  char filename[MAX_PATH];
} HsWhitePlateCorrection;

/**
 * @brief Structure for recipe data
 *
 * @version Ver 1.5.0
 */
typedef struct _HsRecipe {
  /** Date and time of creation(yyyy/MM/dd hh:mm:ss.fff) */
  char datetime[HS_DATE_TIME_LENGTH];
  /** Comment */
  char comment[HS_COMMENT_LENGTH];
  /** Basic white point */
  HsBaseWhitePoint base_point;
  /** Measurement condition */
  HsMeasurementCondition measurement;
  /** enable/disable flag of diagonal correction */
  bool diagonal_correction_enable;
  /** enable/disable flag of color correction */
  bool color_correction_enable;
  /** enable/disable flag of luminosity correction */
  bool luminosity_correction_enable;
  /** enable/disable flag of area correction */
  bool area_correction_enable;
  /** enable/disable flag of white plate correction */
  bool white_plate_correction_enable;
  /** Parameters for white plate correction */
  HsWhitePlateCorrection white_plate_correction;
} HsRecipe;

/**
 * @brief Enumeration for CSV output data item
 *
 * @version Ver 1.5.0
 */
typedef struct _HsOutputStatisticsDef {
  /** Average */
  bool average;
  /** Maximum */
  bool max;
  /** Mininum */
  bool min;
  /** Center difference */
  bool diff;
} HsOutputStatisticsDef;

/**
 * @brief Structure for CSV output setting
 *
 * @version Ver 1.5.0
 */
typedef struct _HsOutputCsvDef {
  /** CSV output type */
  HsCsvType type;
  /** Output flag of each output data */
  bool values[HS_OUTPUT_DATA_VALUES_TYPE_MAXCNT];
  /** Attribute flag of each output data */
  HsOutputStatisticsDef values_info[HS_OUTPUT_DATA_VALUES_TYPE_MAXCNT];
  /** Judgment information output flag */
  bool judgment;
  /** Output flag of each judgment condition */
  bool judgment_info[HS_OUTPUT_JUDGMENT_TYPE_MAXCNT];
  /** Spectroscopic information flag */
  bool spectral;
  /** Output wavelength list */
  int spectral_wavelength_list[HS_SPECTRAL_DATA_SIZE];
  /** Output wavelength count */
  int spectral_wavelength_list_count;
} HsOutputCsvDef;

/**
 * @brief Structure for section data
 *
 * @version Ver 1.5.0
 */
typedef struct _HsSectionData {
  /** Horizontal data count */
  int horizontal_data_count;
  /** Horizontal data pointer */
  float *horizontal_data;
  /** Vertical data count */
  int vertical_data_count;
  /** Vertical data pointer */
  float *vertical_data;
  /** Diagonal data count */
  int diagonal_data_count;
  /** Diagonal data pointer */
  float *diagonal_data;
} HsSectionData;

/**
 * @brief Structure for section data setting
 *
 * @version Ver 1.5.0
 */
typedef struct _HsSectionDataSetting {
  /** Start point */
  HsPoint start_point;
  /** End point */
  HsPoint end_point;
  /** enable/disable flag */
  bool enable;
  /** Section data type */
  HsSectionDataType section_data_type;
} HsSectionDataSetting;

/**
 * @brief Structure for section data setting list
 *
 * @version Ver 1.5.0
 */
typedef struct _HsSectionDataSettingList {
  /** Section data setting list */
  HsSectionDataSetting settings[HS_SECTION_DATA_SETTING_COUNT_MAX];
} HsSectionDataSettingList;

/**
 * @brief Structure for histogram data
 *
 * @version Ver 1.5.0
 */
typedef struct _HsHistogramData {
  /** Bins of histogram */
  int bins;
  /** Count of histogram for each bin. An array in same size as bins are allocated. */
  int *counts;
  /** Minimum value */
  float min_value;
  /** Maximum value */
  float max_value;
} HsHistogramData;

/**
 * @brief Structure for pixel measurement data
 *
 * @version Ver 1.5.0
 */
typedef struct _HsPixelData {
  /** Pixel location */
  HsPoint location;
  /** Measurement data for each data type */
  double datatype_values[HS_DATA_TYPE_MAXCNT];
  /** spectral data values */
  float spectral_values[HS_SPECTRAL_DATA_SIZE];
} HsPixelData;

/**
 * @brief Structure for Focus setting
 *
 * @version Ver 1.5.0
 */
typedef struct _HsFocusSetting {
  /** enable/disable flag */
  bool enabled;
  /** @if englis Focus area */
  HsRect focus_rect;
} HsFocusSetting;

/**
 * @brief Structure for Focus result
 *
 * @version Ver 1.5.0
 */
typedef struct _HsFocusResult {
  /** Ratio */
  float focus_ratio;
  /** Profile */
  unsigned short profile[HS_LIVE_PROFILE_SIZE];
  /** Maximum value */
  unsigned short max_value;
  /** Minimum value */
  unsigned short min_value;
} HsFocusResult;

/**
 * @brief Structure for Spectrum search settings
 *
 * @version Ver 1.5.0
 */
typedef struct _HsSearchSpectrumSetting {
  /** Wavelength count */
  int wavelength_count;
  /** First wavelength */
  int first_wavelength;
  /** Last wavelength */
  int last_wavelength;
  /** Spectral dat */
  float spectrum[HS_SPECTRAL_DATA_SIZE];
  /** Measurement data ID */
  int measurement_data_id;
  /** Matching rate[%] */
  float matching_rate;
} HsSearchSpectrumSetting;

/**
 * @brief Structure for simulation by spectrum settings
 *
 * @version Ver 1.5.0
 */
typedef struct _HsSimulationBySpectrumSetting {
  /** Measurement ID of measurement data that is used for simulation */
  int measurement_data_id;
  /** Spectrum of light source that was used on measurement */
  float spectrum_of_old_light[HS_SPECTRAL_DATA_SIZE];
  /** Spectrum of light source that will be used for simulation */
  float spectrum_of_new_light[HS_SPECTRAL_DATA_SIZE];
  /** Apply simulation result to measurement data or not */
  bool apply_to_measurement_data;
} HsSimulationBySpectrumSetting;

/**
 * @brief Structure for simulation by image settings
 *
 * @version Ver 1.5.0
 */
typedef struct _HsSimulationByImageSetting {
  /** Measurement ID of measurement data that is used for simulation */
  int measurement_data_id;
  /** Measurement ID of light source that was used on measurement */
  int measurement_data_id_of_old_light;
  /** Measurement ID of light source that will be used for simulation */
  int measurement_data_id_of_new_light;
  /** Apply simulation result to measurement data or not */
  bool apply_to_measurement_data;
} HsSimulationByImageSetting;

/**
 * @brief Structure for backlight simulation settings
 *
 * @version Ver 1.5.0
 */
typedef struct _HsBacklightSimulationSetting {
  /** Measurement ID of measurement data that is used for simulation */
  int measurement_data_id;
  /** Measurement ID of backlight */
  int measurement_data_id_of_backlight;
  /** Spectrum of ideal backlight */
  float spectrum_of_ideal_backlight[HS_SPECTRAL_DATA_SIZE];
  /** Apply simulation result to measurement data or not */
  bool apply_to_measurement_data;
} HsBacklightSimulationSetting;

/**
 * @brief Structure for optimization result
 *
 * @version Ver 1.5.0
 */
typedef struct _HsOptimizationResult {
  /** Integration time */
  double integration_time;
  /** gain */
  HsGainType gain;
} HsOptimizationResult;

/**
 * @brief Running status callback function.
 * @param[in] status Processing execution status
 * @param[in] progress Progress bar of value
 * @return void
 *
 * @version Ver 1.5.0
 */
typedef void(__stdcall *HsProgressCallback)(HsRunningStatus status, float progress);

/**
 * @brief Initializes whole system.
 * @details Please call this function before calling any other functions.
 * @param[in] calibration_directory Reference directory path of the calibration data
 * @param[in] config Configuration information
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsInitialize(const char *calibration_directory, HsConfiguration *config);

/**
 * @brief Gets the system version.
 * @details Please use 8 bytes or more for the buffer.
 * @param[in] buffer_size Buffer size
 * @param[in,out] version Buffer to get the version
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsGetVersion(unsigned int buffer_size, char *version);

/**
 * @brief Gets the error string.
 * @details Please use 256 bytes or more for the buffer.
 * @param[in] error_no Error code
 * @param[in] buffer_size Buffer size
 * @param[in,out] error_string Error string buffer
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsGetErrorString(HsError error_no, unsigned int buffer_size, char *error_string);

/**
 * @brief Finalizes the system.
 * @details Please call this funtion on the terminating phase.
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsFinalize();

/**
 * @brief Opens the device and establish the connection.
 * @param[in] product_id Product ID of the target device.
 * @param[in,out] device Device information
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsOpenDevice(const char *product_id, HsDeviceInfo *device);

/**
 * @brief Closes the device.
 * @param[in] product_id Product ID of the target device.
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsCloseDevice(const char *product_id);

/**
 * @brief Gets the device type.
 * @param[in] product_id Product ID of the target device.
 * @param[in,out] device_type Device type
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsGetDeviceType(const char *product_id, HsDeviceType *device_type);

/**
 * @brief Adjusts image size in order to be suitable for hardware restriction.
 * @details Devices have the restriction for its image size that can handle(ex; The width of image should be even number
 *or multiple number of 4). This function adjusts given image area size to fit the restriction.
 * @param[in] device_type device type
 * @param[in] binning_type Binning type
 * @param[in,out] image_rect image area
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsAdjustImageRectForDevice(HsDeviceType device_type, HsBinningType binning_type, HsRect *image_rect);

/**
 * @brief Gets the live setting.
 * @param[in] product_id Product ID of the target device.
 * @param[in,out] live_setting Live setting
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsGetLiveSetting(const char *product_id, HsLiveSetting *live_setting);

/**
 * @brief Sets the live setting.
 * @param[in] product_id Product ID of the target device.
 * @param[in] live_setting Live setting
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsSetLiveSetting(const char *product_id, HsLiveSetting *live_setting);

/**
 * @brief Creates spot definition.
 * @attention Please don't forget to dispose created object when it is not necessary.
 * @param[in,out] spot_def Reference pointer of spot definition pointer
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsCreateSpotDef(HsSpotDef *spot_def);

/**
 * @brief Disposes the spot definition.
 * @param[in,out] spot_def Reference pointer of spot definition
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsDestroySpotDef(HsSpotDef *spot_def);

/**
 * @brief Loads the spot definition.
 * @attention Please don't forget to dispose loaded object when it is not necessary.
 * @param[in] filepath Spot definition file path
 * @param[in,out] spot_def Reference pointer of spot definition
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsLoadSpotDef(const char *filepath, HsSpotDef *spot_def);

/**
 * @brief Saves the spot definition.
 * @param[in] filepath Spot definition file path
 * @param[in] spot_def Spot definition pointer
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsSaveSpotDef(const char *filepath, const HsSpotDef *spot_def);

/**
 * @brief Creates a standard spot.
 * @param[in,out] spot_def Standard spot definition
 * @param[in] device_type Device type
 * @param[in] lens_type Lens type
 * @param[in] measurement_distance Measurement distance[mm]
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError
hsCreateStandardSpotArea(HsSpotDef *spot_def, HsDeviceType device_type, HsLensType lens_type, int measurement_distance);

/**
 * @brief Creates a matrix spot.
 * @param[in,out] spot_def Matrix spot definition
 * @param[in] device_type Device type
 * @param[in] lens_type Lens type
 * @param[in] measurement_distance Measurement distance[mm]
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError
hsCreateMatrixSpotArea(HsSpotDef *spot_def, HsDeviceType device_type, HsLensType lens_type, int measurement_distance);

/**
 * @brief Creates the measurement data.
 * @details If this function succeeds, a measurement id is generated. By using this ID, user can retrieve measurement
 *values, settings in data and images.
 * @param[in] recipe Recipe data
 * @param[in,out] measurement_data_id ID of the measurement data created
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsCreateMeasurementData(const HsRecipe *recipe, int *measurement_data_id);

/**
 * @brief Disposes the measurement_data.
 * @param[in,out] measurement_data_id Measurement data id
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsDestroyMeasurementData(int measurement_data_id);

/**
 * @brief Starts the measurement.
 * @param[in] product_id Product ID of the target device.
 * @param[in] measurement_data_id Measurement data id
 * @param[in] sequential_no Sequential number
 * @param[in,out] progress_callback Running status callback function
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsStartMeasurement(const char *product_id, int measurement_data_id, int sequential_no,
                                      HsProgressCallback progress_callback);

/**
 * @brief Stop the measurement.
 * @param[in] product_id Product ID of the target device.
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsStopMeasurement(const char *product_id);

/**
 * @brief Updates the measurement data.
 * @details Please call this funtion after changing settings in measurement data related with correction.
 * @param[in] measurement_data_id Measurement data id
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsUpdateMeasurementData(int measurement_data_id);

/**
 * @brief Gets the measurement data image.
 * @param[in] measurement_data_id Measurement data id
 * @param[in] data_type Data type
 * @param[in,out] image32f Measurement data image
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsGetMeasurementImage(int measurement_data_id, HsDataType data_type, HsImage32f *image32f);

/**
 * @brief Gets the measurement spectral image.
 * @param[in] measurement_data_id Measurement data id
 * @param[in] current_wavelength Wavelength[nm]
 * @param[in,out] image32f Measurement spectral image
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsGetSpectralImage(int measurement_data_id, int current_wavelength, HsImage32f *image32f);

/**
 * @brief Gets a pseudo color image.
 * @param[in] setting Pseudo color setting
 * @param[in] source_image Measurement data image
 * @param[in] mask_image Mask image
 * @param[in,out] destination_image Pseudo color image
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsToPseudoColor(HsPseudoColorSetting setting, HsImage32f *source_image, HsImage8u3 *mask_image,
                                   HsImage8u3 *destination_image);

/**
 * @brief Gets a pseudo color image.
 * @param[in] source_image Measurement spectral image
 * @param[in] current_wavelength Wavelength[nm]
 * @param[in] mask_image Mask image
 * @param[in,out] destination_image Pseudo color image
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsToSpectralColor(HsImage32f *source_image, int current_wavelength, HsImage8u3 *mask_image,
                                     HsImage8u3 *destination_image);

/**
 * @brief Gets a rgb color image.
 * @param[in] measurement_data_id Measurement data id
 * @param[in] setting RGB color setting
 * @param[in,out] image8u3 RGB color image
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsGetRGBColorImage(int measurement_data_id, HsRGBColorSetting setting, HsImage8u3 *image8u3);

/**
 * @brief Gets the measurment value of each pixel.
 * @param[in] measurement_data_id Measurement data id
 * @param[in] location Pixel location
 * @param[in,out] pixel_data pixel data
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsGetPixelData(int measurement_data_id, HsPoint location, HsPixelData *pixel_data);

/**
 * @brief Creates a mask image.
 * @attention Please don't forget to dispose created object when it is not necessary.
 * @param[in] measurement_data_id Measurement data id
 * @param[in] image_data_type Data type
 * @param[in,out] image Refarence pointer of mask image
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsCreateMaskImage(int measurement_data_id, HsImageDataType image_data_type, HsImage8u3 *image);

/**
 * @brief Check if measurement data is changed or not.
 * @details After createing measurement data or loading data and changing it, the changed flag was set to TRUE
 *internally. In this case, the user needs to save this data.
 * @param[in] measurement_data_id Measurement data id
 * @param[in,out] is_dirty change flag
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsIsMeasurementDataDirty(int measurement_data_id, bool *is_dirty);

/**
 * @brief Get the measurement data.
 * @details Get the data in the measurement data that cannot be changed externally. There is no corresponding "Set"
 *function to this function.
 * @param[in] measurement_data_id Measurement data id
 * @param[in,out] measurement_data measurement data
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsGetMeasurementData(int measurement_data_id, HsMeasurementData *measurement_data);

/**
 * @brief Loads the measurement data.
 * @details If this function succeeds, a measurement id is generated. By using this ID, user can retrieve measurement
 *values, settings in data and images.
 * @attention Please don't forget to dispose loaded object when it is not necessary.
 * @param[in] filepath File path of the measurement data
 * @param[in,out] progress_callback Running status callback function
 * @param[in,out] measurement_data_id Measurement data id
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError
hsLoadMeasurementData(const char *filepath, HsProgressCallback progress_callback, int *measurement_data_id);

/**
 * @brief Saves the measurement data.
 * @param[in] filepath File path of the measurement data
 * @param[in] measurement_data_id Measurement data id
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsSaveMeasurementData(const char *filepath, const int measurement_data_id);

/**
 * @brief Creates a spot data list.
 * @attention Please don't forget to dispose created object when it is not necessary.
 * @param[in] measurement_data_id Measurement data id
 * @param[in] spot_data_type Spot data type
 * @param[in,out] progress_callback Running status callback function
 * @param[in,out] spot_data_list Reference pointer of spot data list
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsCreateSpotDataList(int measurement_data_id, HsSpotDataType spot_data_type,
                                        HsProgressCallback progress_callback, HsSpotDataList *spot_data_list);

/**
 * @brief Disposes the spot data list.
 * @param[in,out] spot_data_list Reference pointer of spot data list
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsDestroySpotDataList(HsSpotDataList *spot_data_list);

/**
 * @brief Gets the already read measurement data count.
 * @param[in,out] measurement_data_count measurement data count
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsGetMeasurementDataCount(int *measurement_data_count);

/**
 * @brief Gets the measurement data id from loading index of measurement data.
 * @param[in] index measurement Loading index of measurement data
 * @param[in,out] measurement_data_id measurement data id
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsGetMeasurementDataID(int index, int *measurement_data_id);

/**
 * @brief Gets the file information of the measurement data.
 * @param[in] measurement_data_id Measurement data id
 * @param[in,out] measurement_data_file_info Measurement data file information
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError
hsGetMeasurementDataFileInfo(int measurement_data_id, HsMeasurementDataFileInfo *measurement_data_file_info);

/**
 * @brief Sets the file information of the measurement data.
 * @param[in] measurement_data_id Measurement data id
 * @param[in] measurement_data_file_info Measurement data file information
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError
hsSetMeasurementDataFileInfo(int measurement_data_id, HsMeasurementDataFileInfo *measurement_data_file_info);

/**
 * @brief Gets the measurement data image setting of measurement data.
 * @param[in] measurement_data_id Measurement data id
 * @param[in,out] image_setting Measurement data image setting
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError
hsGetMeasurementDataImageSetting(int measurement_data_id, HsMeasurementDataImageSetting *image_setting);

/**
 * @brief Sets the measurement data image setting of measurement data.
 * @param[in] measurement_data_id Measurement data id
 * @param[in] image_setting Measurement data image setting
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError
hsSetMeasurementDataImageSetting(int measurement_data_id, HsMeasurementDataImageSetting *image_setting);

/**
 * @brief Gets the section data setting list of the measurement data.
 * @param[in] measurement_data_id Measurement data id
 * @param[in,out] list Section data setting list
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsGetMeasurementDataSectionSetting(int measurement_data_id, HsSectionDataSettingList *list);

/**
 * @brief Sets the section data setting list of the measurement data.
 * @param[in] measurement_data_id Measurement data id
 * @param[in] list Section data setting list
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsSetMeasurementDataSectionSetting(int measurement_data_id, HsSectionDataSettingList *list);

/**
 * @brief Disposes the diagonal correction list.
 * @param[in,out] list Reference pointer of diagonal correction list
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsDestroyDiagonalCorrectionList(HsDiagonalCorrectionList *list);

/**
 * @brief Loads the diagonal correction list.
 * @attention Please don't forget to dispose loaded object when it is not necessary.
 * @param[in] filepath diagonal correction list file path
 * @param[in,out] list Reference pointer of diagonal correction list
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsLoadDiagonalCorrectionList(const char *filepath, HsDiagonalCorrectionList *list);

/**
 * @brief Saves the diagonal correction list.
 * @param[in] filepath diagonal correction list file path
 * @param[in] list diagonal correction list
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsSaveDiagonalCorrectionList(const char *filepath, const HsDiagonalCorrectionList *list);

/**
 * @brief Disposes the color correction list.
 * @param[in,out] list Reference pointer of color correction list
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsDestroyColorCorrectionList(HsColorCorrectionList *list);

/**
 * @brief Loads the color correction list.
 * @attention Please don't forget to dispose loaded object when it is not necessary.
 * @param[in] filepath color correction list file path
 * @param[in,out] list Reference pointer of color correction list
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsLoadColorCorrectionList(const char *filepath, HsColorCorrectionList *list);

/**
 * @brief Saves the color correction list.
 * @param[in] filepath color correction list file path
 * @param[in] list color correction list
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsSaveColorCorrectionList(const char *filepath, const HsColorCorrectionList *list);

/**
 * @brief Disposes the cluminosity data.
 * @param[in,out] data Reference pointer of luminosity data
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsDestroyLuminosityData(HsLuminosityData *data);

/**
 * @brief Loads the luminosity data CSV file.
 * @param[in] filepath luminosity data CSV file path
 * @param[in,out] data Reference pointer of luminosity data
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsLoadLuminosityDataCsv(const char *filepath, HsLuminosityData *data);

/**
 * @brief Saves the luminosity data CSV file.
 * @param[in] filepath Luminosity data CSV file path
 * @param[in] data Luminosity data
 * @param[in] decimal_place Number of decimal places
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsSaveLuminosityDataCsv(const char *filepath, const HsLuminosityData *data, int decimal_place);

/**
 * @brief Disposes the cluminosity data list.
 * @param[in,out] list Reference pointer of luminosity data list
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsDestroyLuminosityDataList(HsLuminosityDataList *list);

/**
 * @brief Loads the luminosity data list.
 * @attention Please don't forget to dispose loaded object when it is not necessary.
 * @param[in] filepath Luminosity data list file path
 * @param[in,out] list Reference pointer of luminosity data list
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsLoadLuminosityDataList(const char *filepath, HsLuminosityDataList *list);

/**
 * @brief Saves the luminosity data list.
 * @param[in] filepath Luminosity data list file path
 * @param[in] list Luminosity data list
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsSaveLuminosityDataList(const char *filepath, const HsLuminosityDataList *list);

/**
 * @brief Disposes the cluminosity factor data.
 * @param[in,out] data Reference pointer of luminosity factor data
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsDestroyLuminosityFactorData(HsLuminosityFactorData *data);

/**
 * @brief Loads the luminosity factor data CSV file.
 * @param[in] filepath Luminosity factor data CSV file path
 * @param[in,out] data Reference pointer of luminosity factor data
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsLoadLuminosityFactorDataCsv(const char *filepath, HsLuminosityFactorData *data);

/**
 * @brief Saves the luminosity factor data CSV file.
 * @param[in] filepath Luminosity factor data CSV file path
 * @param[in] data Luminosity factor data
 * @param[in] decimal_place Number of decimal places
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError
hsSaveLuminosityFactorDataCsv(const char *filepath, const HsLuminosityFactorData *data, int decimal_place);

/**
 * @brief Disposes the cluminosity factor data list.
 * @param[in,out] list Reference pointer of luminosity factor data list
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsDestroyLuminosityFactorDataList(HsLuminosityFactorDataList *list);

/**
 * @brief Loads the luminosity factor data list.
 * @attention Please don't forget to dispose loaded object when it is not necessary.
 * @param[in] filepath Luminosity factor data list file path
 * @param[in,out] list Reference pointer of luminosity factor data list
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsLoadLuminosityFactorDataList(const char *filepath, HsLuminosityFactorDataList *list);

/**
 * @brief Saves the luminosity factor data list.
 * @param[in] filepath Luminosity factor data list file path
 * @param[in] list Luminosity factor data list
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsSaveLuminosityFactorDataList(const char *filepath, const HsLuminosityFactorDataList *list);

/**
 * @brief Disposes the area correction.
 * @param[in,out] data Reference pointer of area correction
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsDestroyAreaCorrection(HsAreaCorrection *data);

/**
 * @brief Loads the area correction.
 * @param[in] filepath area correction file path
 * @param[in,out] data Reference pointer of area correction
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsLoadAreaCorrection(const char *filepath, HsAreaCorrection *data);

/**
 * @brief Saves the area correction.
 * @param[in] filepath area correction file path
 * @param[in] data Area correction
 * @param[in] decimal_place Number of decimal places
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsSaveAreaCorrection(const char *filepath, const HsAreaCorrection *data, int decimal_place);

/**
 * @brief Creates recipe data.
 * @attention Please don't forget to dispose created object when it is not necessary.
 * @param[in,out] recipe Reference pointer of recipe data
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsCreateRecipe(HsRecipe *recipe);

/**
 * @brief Disposes the recipe data.
 * @param[in,out] recipe Reference pointer of recipe data
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsDestroyRecipe(HsRecipe *recipe);

/**
 * @brief Loads the recipe data.
 * @attention Please don't forget to dispose loaded object when it is not necessary.
 * @param[in] filepath recipe data file path
 * @param[in,out] recipe Reference pointer of recipe data
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsLoadRecipe(const char *filepath, HsRecipe *recipe);

/**
 * @brief Saves the recipe data.
 * @param[in] filepath recipe data file path
 * @param[in] recipe Recipe data
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsSaveRecipe(const char *filepath, const HsRecipe *recipe);

/**
 * @brief Gets the measurement recipe data.
 * @param[in] measurement_data_id Measurement data id
 * @param[in,out] recipe Measurement recipe data
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsGetMeasurementRecipe(int measurement_data_id, HsRecipe *recipe);

/**
 * @brief Sets the measurement recipe data.
 * @param[in] measurement_data_id Measurement data id
 * @param[in] recipe Measurement recipe data
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsSetMeasurementRecipe(int measurement_data_id, const HsRecipe *recipe);

/**
 * @brief Gets the Random spot definition of measurement data.
 * @param[in] measurement_data_id Measurement data id
 * @param[in,out] spot_def Random spot definition
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsGetMeasurementRandomSpotDef(int measurement_data_id, HsSpotDef *spot_def);

/**
 * @brief Sets the Random spot definition of measurement data.
 * @param[in] measurement_data_id Measurement data id
 * @param[in] spot_def Random spot definition
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsSetMeasurementRandomSpotDef(int measurement_data_id, const HsSpotDef *spot_def);

/**
 * @brief Gets the Standard spot definition of measurement data.
 * @param[in] measurement_data_id Measurement data id
 * @param[in,out] spot_def Standard spot definition
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsGetMeasurementStandardSpotDef(int measurement_data_id, HsSpotDef *spot_def);

/**
 * @brief Sets the Standard spot definition of measurement data.
 * @param[in] measurement_data_id Measurement data id
 * @param[in] spot_def Standard spot definition
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsSetMeasurementStandardSpotDef(int measurement_data_id, const HsSpotDef *spot_def);

/**
 * @brief Gets the Matrix spot definition of measurement data.
 * @param[in] measurement_data_id Measurement data id
 * @param[in,out] spot_def Matrix spot definition
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsGetMeasurementMatrixSpotDef(int measurement_data_id, HsSpotDef *spot_def);

/**
 * @brief Sets the Matrix spot definition of measurement data.
 * @param[in] measurement_data_id Measurement data id
 * @param[in] spot_def Matrix spot definition
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsSetMeasurementMatrixSpotDef(int measurement_data_id, const HsSpotDef *spot_def);

/**
 * @brief Gets the diagonal correction list of measurement data.
 * @param[in] measurement_data_id Measurement data id
 * @param[in,out] list Diagonal correction list pointer
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsGetMeasurementDiagonalCorrectionList(int measurement_data_id, HsDiagonalCorrectionList *list);

/**
 * @brief Sets the diagonal correction list of measurement data.
 * @param[in] measurement_data_id Measurement data id
 * @param[in] list Reference pointer of diagonal correction list
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError
hsSetMeasurementDiagonalCorrectionList(int measurement_data_id, const HsDiagonalCorrectionList *list);

/**
 * @brief Gets the color correction list of measurement data.
 * @param[in] measurement_data_id Measurement data id
 * @param[in,out] list Reference pointer of Color correction list
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsGetMeasurementColorCorrectionList(int measurement_data_id, HsColorCorrectionList *list);

/**
 * @brief Sets the color correction list of measurement data.
 * @param[in] measurement_data_id Measurement data id
 * @param[in] list Color correction list pointer
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsSetMeasurementColorCorrectionList(int measurement_data_id, const HsColorCorrectionList *list);

/**
 * @brief Gets the area correction of measurement data.
 * @param[in] measurement_data_id Measurement data id
 * @param[in,out] data Reference pointer of area correction
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsGetMeasurementAreaCorrection(int measurement_data_id, HsAreaCorrection *data);

/**
 * @brief Sets the area correction of measurement data.
 * @param[in] measurement_data_id Measurement data id
 * @param[in] data Area correction pointer
 * @param[in] decimal_place Number of decimal places
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError
hsSetMeasurementAreaCorrection(int measurement_data_id, const HsAreaCorrection *data, int decimal_place);

/**
 * @brief Gets the luminosity data list of measurement data.
 * @param[in] measurement_data_id Measurement data id
 * @param[in,out] list Reference pointer of luminosity data list
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsGetMeasurementLuminosityDataList(int measurement_data_id, HsLuminosityDataList *list);

/**
 * @brief Sets the luminosity data list of measurement data.
 * @param[in] measurement_data_id Measurement data id
 * @param[in] list Luminosity data list pointer
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsSetMeasurementLuminosityDataList(int measurement_data_id, const HsLuminosityDataList *list);

/**
 * @brief Gets the luminosity factor data list of measurement data.
 * @param[in] measurement_data_id Measurement data id
 * @param[in,out] list Reference pointer of luminosity factor data list
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsGetMeasurementLuminosityFactorDataList(int measurement_data_id, HsLuminosityFactorDataList *list);

/**
 * @brief Sets the luminosity factor data list of measurement data.
 * @param[in] measurement_data_id Measurement data id
 * @param[in] list Luminosity factor data list pointer
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError
hsSetMeasurementLuminosityFactorDataList(int measurement_data_id, const HsLuminosityFactorDataList *list);

/**
 * @brief Gets the comparison result of the measurement image.
 * @param[in] image_a Measurement image A
 * @param[in] image_b Measurement image B
 * @param[in] diff_type Image comparison type
 * @param[in,out] image_c Comparison of Measurement image A and Measurement image B
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError
hsGetImageDifference(HsImage32f *image_a, HsImage32f *image_b, HsImageDifferenceType diff_type, HsImage32f *image_c);

/**
 * @brief Gets the Delta Eab of the measurement image.
 * @param[in] measurement_id1 Measurement id1
 * @param[in] measurement_id2 Measurement id2
 * @param[in,out] image_delta_eab DeltaEab image of measurement id1 image and measurement id2 image
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsGetDeltaEabImage(int measurement_id1, int measurement_id2, HsImage32f *image_delta_eab);

/**
 * @brief Starts image capture.
 * @param[in] product_id Product ID of the target device.
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsStartCapture(const char *product_id);

/**
 * @brief Terminates image capture.
 * @param[in] product_id Product ID of the target device.
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsStopCapture(const char *product_id);

/**
 * @brief Captures live image.
 * @param[in] product_id Product ID of the target device.
 * @param[in] focus_setting Focus setting
 * @param[in,out] live_image Live image
 * @param[in,out] focus_result Focus result
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsCaptureLiveImage(const char *product_id, HsFocusSetting *focus_setting, HsImage8u3 *live_image,
                                      HsFocusResult *focus_result);

/**
 * @brief Optimizes the integration time for the live image.
 * @param[in] product_id Product ID of the target device.
 * @param[in,out] optimization_result Optimization result for every filter
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsOptimizeThroughLive(const char *product_id, HsOptimizationResult *optimization_result);

/**
 * @brief Optimizes the integration time for the measurement.
 * @param[in] product_id Product ID of the target device.
 * @param[in] recipe Measurement recipe data
 * @param[in,out] optimization_result Optimization result for each filter.
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsOptimizeMeasurement(const char *product_id, const HsRecipe *recipe,
                                         HsOptimizationResult optimization_result[HS_FILTER_TYPE_MAXCNT]);

/**
 * @brief Gets the measurement image size.
 * @details Get the maximum image size per device and binning type.
 * @param[in] device_type Device type
 * @param[in] binning_type Binning_type
 * @param[in,out] image_size Image size
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsGetImageSize(HsDeviceType device_type, HsBinningType binning_type, HsSize *image_size);

/**
 * @brief Gets the resolution [mm].
 * @param[in] device_type Device type
 * @param[in] lens_type Lens type
 * @param[in] measurement_distance Measurement distance
 * @param[in] binning_type Binning type
 * @param[in,out] size Resolution[mm]
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsGetOpticalResolutionMm(HsDeviceType device_type, HsLensType lens_type, int measurement_distance,
                                            HsBinningType binning_type, HsSize64f *size);

/**
 * @brief Gets the measurement range[mm].
 * @param[in] device_type Device type
 * @param[in] image_size ROI[pixel]
 * @param[in] lens_type Lens type
 * @param[in] measurement_distance Measurement distance
 * @param[in] binning_type Binning type
 * @param[in,out] size measurement range[mm]
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsGetMeasurementRange(HsDeviceType device_type, HsSize *image_size, HsLensType lens_type,
                                         int measurement_distance, HsBinningType binning_type, HsSize64f *size);

/**
 * @brief Creates the image.
 * @attention Please don't forget to dispose created object when it is not necessary.
 * @param[in] width Width
 * @param[in] height Height
 * @param[in,out] image Reference pointer of image
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsCreateImage32f(int width, int height, HsImage32f *image);

/**
 * @brief Disposes the image.
 * @param[in,out] image Reference pointer of image
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsDestroyImage32f(HsImage32f *image);

/**
 * @brief Creates the image.
 * @attention Please don't forget to dispose created object when it is not necessary.
 * @param[in] width Width
 * @param[in] height Height
 * @param[in,out] image Reference pointer of image
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsCreateImage8u3(int width, int height, HsImage8u3 *image);

/**
 * @brief Disposes the image.
 * @param[in,out] image Reference pointer of image
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsDestroyImage8u3(HsImage8u3 *image);

/**
 * @brief Creates a histogram from the measured data.
 * @attention Please don't forget to dispose created object when it is not necessary.
 * @param[in] image Measuremnet image
 * @param[in] trimming_area Trimming area
 * @param[in] bins Histogram data bins
 * @param[in,out] histogram Reference pointer of histogram data list pointer
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError
hsCreateHistogram(HsImage32f *image, const HsRect *trimming_area, int bins, HsHistogramData *histogram);

/**
 * @brief Disposes the histogram.
 * @param[in,out] histogram Reference pointer of histogram data list pointer
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsDestroyHistogram(HsHistogramData *histogram);

/**
 * @brief Creates a section data list.
 * @attention Please don't forget to dispose created object when it is not necessary.
 * @param[in] image Measurement image
 * @param[in] section_setting Section data setting
 * @param[in,out] section_data Reference pointer of section data list pointer
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError
hsCreateSectionData(HsImage32f *image, const HsSectionDataSetting *section_setting, HsSectionData *section_data);

/**
 * @brief Disposes the section data list.
 * @param[in,out] section_data Reference pointer of section data list pointer
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsDestroySectionData(HsSectionData *section_data);

/**
 * @brief Outputs measurement data of all the pixels to a CSV file.
 * @param[in] filepath Output CSV file path
 * @param[in] measurement_data_id Measurement data id
 * @param[in] csv_def CSV output configuration definition
 * @param[in] decimal_place Number of decimal places
 * @param[in,out] progress_callback Running status callback function
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsOutputCsv(const char *filepath, int measurement_data_id, HsOutputCsvDef *csv_def,
                               char decimal_place[HS_DATA_TYPE_MAXCNT], HsProgressCallback progress_callback);

/**
 * @brief Outputs the measurement data of the measurement spot to CSV file.
 * @param[in] filepath Output CSV file path
 * @param[in] measurement_data_id Measurement data id
 * @param[in] csv_def CSV output configuration definition
 * @param[in] decimal_place Number of decimal places
 * @param[in,out] progress_callback Running status callback function
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsOutputSpotCsv(const char *filepath, int measurement_data_id, HsOutputCsvDef *csv_def,
                                   char decimal_place[HS_DATA_TYPE_MAXCNT], HsProgressCallback progress_callback);

/**
 * @brief Outputs the measurement data for each section data to a CSV file.
 * @param[in] filepath Output CSV file path
 * @param[in] measurement_data_id Measurement data id
 * @param[in] csv_def CSV output configuration definition
 * @param[in] decimal_place Number of decimal places
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsOutputSectionDataCsv(const char *filepath, int measurement_data_id, HsOutputCsvDef *csv_def,
                                          char decimal_place[HS_DATA_TYPE_MAXCNT]);

/**
 * @brief Object color simulation by using spectrum
 * @param[in] setting Settings for simulation
 * @param[in,out] progress_callback Running status callback function
 * @param[in,out] result_image simulation result image in RGB
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsSimulationBySpectrum(HsSimulationBySpectrumSetting *setting, HsProgressCallback progress_callback,
                                          HsImage8u3 *result_image);

/**
 * @brief Object color simulation by using image
 * @param[in] setting Settings for simulation
 * @param[in,out] progress_callback Running status callback function
 * @param[in,out] result_image simulation result image in RGB
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsSimulationByImage(HsSimulationByImageSetting *setting, HsProgressCallback progress_callback,
                                       HsImage8u3 *result_image);

/**
 * @brief Color simulation by using ideal backlight spectrum
 * @param[in] setting Settings for simulation
 * @param[in,out] progress_callback Running status callback function
 * @param[in,out] result_image simulation result image in RGB
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsBacklightSimulation(HsBacklightSimulationSetting *setting, HsProgressCallback progress_callback,
                                         HsImage8u3 *result_image);

/**
 * @brief Applies the diagonal correction to the image.
 * @param[in] original_image Original image
 * @param[in] correction_parameter Diagonal correction
 * @param[in,out] corrected_image Image of applying the diagonal correction
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsApplyDiagonalCorrection(const HsImage8u3 *original_image,
                                             const HsDiagonalCorrection *correction_parameter,
                                             HsImage8u3 *corrected_image);

/**
 * @brief Gets the image of searching the spectrum.
 * @param[in] setting Search spectrum setting
 * @param[in,out] progress_callback Running status callback function
 * @param[in,out] result_image Image of searching the spectrum
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsSearchSpectrum(const HsSearchSpectrumSetting *setting, HsProgressCallback progress_callback,
                                    HsImage32f *result_image);

/**
 * @brief If the processing execution status is not HS_STATUS_NONE, to suspend the execution process.
 * @return Error code
 *
 * @version Ver 1.5.0
 */
HS_API_API HsError hsStopProcessing();

#ifdef __cplusplus
}  // extern "C"
#endif

#endif
