/* Include files */

#include <stddef.h>
#include "blas.h"
#include "JointSpaceControl_sfun.h"
#include "c22_JointSpaceControl.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "JointSpaceControl_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static const char * c22_debug_family_names[7] = { "nargin", "nargout", "J_a",
  "dJ_a", "ddX", "dq", "ddq" };

/* Function Declarations */
static void initialize_c22_JointSpaceControl
  (SFc22_JointSpaceControlInstanceStruct *chartInstance);
static void initialize_params_c22_JointSpaceControl
  (SFc22_JointSpaceControlInstanceStruct *chartInstance);
static void enable_c22_JointSpaceControl(SFc22_JointSpaceControlInstanceStruct
  *chartInstance);
static void disable_c22_JointSpaceControl(SFc22_JointSpaceControlInstanceStruct *
  chartInstance);
static void c22_update_debugger_state_c22_JointSpaceControl
  (SFc22_JointSpaceControlInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c22_JointSpaceControl
  (SFc22_JointSpaceControlInstanceStruct *chartInstance);
static void set_sim_state_c22_JointSpaceControl
  (SFc22_JointSpaceControlInstanceStruct *chartInstance, const mxArray *c22_st);
static void finalize_c22_JointSpaceControl(SFc22_JointSpaceControlInstanceStruct
  *chartInstance);
static void sf_c22_JointSpaceControl(SFc22_JointSpaceControlInstanceStruct
  *chartInstance);
static void c22_chartstep_c22_JointSpaceControl
  (SFc22_JointSpaceControlInstanceStruct *chartInstance);
static void initSimStructsc22_JointSpaceControl
  (SFc22_JointSpaceControlInstanceStruct *chartInstance);
static void registerMessagesc22_JointSpaceControl
  (SFc22_JointSpaceControlInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c22_machineNumber, uint32_T
  c22_chartNumber);
static const mxArray *c22_sf_marshallOut(void *chartInstanceVoid, void
  *c22_inData);
static void c22_emlrt_marshallIn(SFc22_JointSpaceControlInstanceStruct
  *chartInstance, const mxArray *c22_ddq, const char_T *c22_identifier, real_T
  c22_y[6]);
static void c22_b_emlrt_marshallIn(SFc22_JointSpaceControlInstanceStruct
  *chartInstance, const mxArray *c22_u, const emlrtMsgIdentifier *c22_parentId,
  real_T c22_y[6]);
static void c22_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c22_mxArrayInData, const char_T *c22_varName, void *c22_outData);
static const mxArray *c22_b_sf_marshallOut(void *chartInstanceVoid, void
  *c22_inData);
static const mxArray *c22_c_sf_marshallOut(void *chartInstanceVoid, void
  *c22_inData);
static real_T c22_c_emlrt_marshallIn(SFc22_JointSpaceControlInstanceStruct
  *chartInstance, const mxArray *c22_u, const emlrtMsgIdentifier *c22_parentId);
static void c22_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c22_mxArrayInData, const char_T *c22_varName, void *c22_outData);
static void c22_info_helper(c22_ResolvedFunctionInfo c22_info[130]);
static void c22_b_info_helper(c22_ResolvedFunctionInfo c22_info[130]);
static void c22_c_info_helper(c22_ResolvedFunctionInfo c22_info[130]);
static void c22_inv(SFc22_JointSpaceControlInstanceStruct *chartInstance, real_T
                    c22_x[36], real_T c22_y[36]);
static void c22_invNxN(SFc22_JointSpaceControlInstanceStruct *chartInstance,
  real_T c22_x[36], real_T c22_y[36]);
static void c22_realmin(SFc22_JointSpaceControlInstanceStruct *chartInstance);
static void c22_eps(SFc22_JointSpaceControlInstanceStruct *chartInstance);
static void c22_eml_matlab_zgetrf(SFc22_JointSpaceControlInstanceStruct
  *chartInstance, real_T c22_A[36], real_T c22_b_A[36], int32_T c22_ipiv[6],
  int32_T *c22_info);
static void c22_check_forloop_overflow_error
  (SFc22_JointSpaceControlInstanceStruct *chartInstance, boolean_T c22_overflow);
static void c22_eml_xger(SFc22_JointSpaceControlInstanceStruct *chartInstance,
  int32_T c22_m, int32_T c22_n, real_T c22_alpha1, int32_T c22_ix0, int32_T
  c22_iy0, real_T c22_A[36], int32_T c22_ia0, real_T c22_b_A[36]);
static void c22_eml_xtrsm(SFc22_JointSpaceControlInstanceStruct *chartInstance,
  real_T c22_A[36], real_T c22_B[36], real_T c22_b_B[36]);
static real_T c22_norm(SFc22_JointSpaceControlInstanceStruct *chartInstance,
  real_T c22_x[36]);
static void c22_eml_warning(SFc22_JointSpaceControlInstanceStruct *chartInstance);
static void c22_b_eml_warning(SFc22_JointSpaceControlInstanceStruct
  *chartInstance, char_T c22_varargin_2[14]);
static void c22_eml_scalar_eg(SFc22_JointSpaceControlInstanceStruct
  *chartInstance);
static void c22_d_emlrt_marshallIn(SFc22_JointSpaceControlInstanceStruct
  *chartInstance, const mxArray *c22_sprintf, const char_T *c22_identifier,
  char_T c22_y[14]);
static void c22_e_emlrt_marshallIn(SFc22_JointSpaceControlInstanceStruct
  *chartInstance, const mxArray *c22_u, const emlrtMsgIdentifier *c22_parentId,
  char_T c22_y[14]);
static const mxArray *c22_d_sf_marshallOut(void *chartInstanceVoid, void
  *c22_inData);
static int32_T c22_f_emlrt_marshallIn(SFc22_JointSpaceControlInstanceStruct
  *chartInstance, const mxArray *c22_u, const emlrtMsgIdentifier *c22_parentId);
static void c22_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c22_mxArrayInData, const char_T *c22_varName, void *c22_outData);
static uint8_T c22_g_emlrt_marshallIn(SFc22_JointSpaceControlInstanceStruct
  *chartInstance, const mxArray *c22_b_is_active_c22_JointSpaceControl, const
  char_T *c22_identifier);
static uint8_T c22_h_emlrt_marshallIn(SFc22_JointSpaceControlInstanceStruct
  *chartInstance, const mxArray *c22_u, const emlrtMsgIdentifier *c22_parentId);
static void c22_b_eml_matlab_zgetrf(SFc22_JointSpaceControlInstanceStruct
  *chartInstance, real_T c22_A[36], int32_T c22_ipiv[6], int32_T *c22_info);
static void c22_b_eml_xger(SFc22_JointSpaceControlInstanceStruct *chartInstance,
  int32_T c22_m, int32_T c22_n, real_T c22_alpha1, int32_T c22_ix0, int32_T
  c22_iy0, real_T c22_A[36], int32_T c22_ia0);
static void c22_b_eml_xtrsm(SFc22_JointSpaceControlInstanceStruct *chartInstance,
  real_T c22_A[36], real_T c22_B[36]);
static void init_dsm_address_info(SFc22_JointSpaceControlInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c22_JointSpaceControl
  (SFc22_JointSpaceControlInstanceStruct *chartInstance)
{
  chartInstance->c22_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c22_is_active_c22_JointSpaceControl = 0U;
}

static void initialize_params_c22_JointSpaceControl
  (SFc22_JointSpaceControlInstanceStruct *chartInstance)
{
}

static void enable_c22_JointSpaceControl(SFc22_JointSpaceControlInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c22_JointSpaceControl(SFc22_JointSpaceControlInstanceStruct *
  chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c22_update_debugger_state_c22_JointSpaceControl
  (SFc22_JointSpaceControlInstanceStruct *chartInstance)
{
}

static const mxArray *get_sim_state_c22_JointSpaceControl
  (SFc22_JointSpaceControlInstanceStruct *chartInstance)
{
  const mxArray *c22_st;
  const mxArray *c22_y = NULL;
  int32_T c22_i0;
  real_T c22_u[6];
  const mxArray *c22_b_y = NULL;
  uint8_T c22_hoistedGlobal;
  uint8_T c22_b_u;
  const mxArray *c22_c_y = NULL;
  real_T (*c22_ddq)[6];
  c22_ddq = (real_T (*)[6])ssGetOutputPortSignal(chartInstance->S, 1);
  c22_st = NULL;
  c22_st = NULL;
  c22_y = NULL;
  sf_mex_assign(&c22_y, sf_mex_createcellarray(2), FALSE);
  for (c22_i0 = 0; c22_i0 < 6; c22_i0++) {
    c22_u[c22_i0] = (*c22_ddq)[c22_i0];
  }

  c22_b_y = NULL;
  sf_mex_assign(&c22_b_y, sf_mex_create("y", c22_u, 0, 0U, 1U, 0U, 1, 6), FALSE);
  sf_mex_setcell(c22_y, 0, c22_b_y);
  c22_hoistedGlobal = chartInstance->c22_is_active_c22_JointSpaceControl;
  c22_b_u = c22_hoistedGlobal;
  c22_c_y = NULL;
  sf_mex_assign(&c22_c_y, sf_mex_create("y", &c22_b_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c22_y, 1, c22_c_y);
  sf_mex_assign(&c22_st, c22_y, FALSE);
  return c22_st;
}

static void set_sim_state_c22_JointSpaceControl
  (SFc22_JointSpaceControlInstanceStruct *chartInstance, const mxArray *c22_st)
{
  const mxArray *c22_u;
  real_T c22_dv0[6];
  int32_T c22_i1;
  real_T (*c22_ddq)[6];
  c22_ddq = (real_T (*)[6])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c22_doneDoubleBufferReInit = TRUE;
  c22_u = sf_mex_dup(c22_st);
  c22_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c22_u, 0)),
                       "ddq", c22_dv0);
  for (c22_i1 = 0; c22_i1 < 6; c22_i1++) {
    (*c22_ddq)[c22_i1] = c22_dv0[c22_i1];
  }

  chartInstance->c22_is_active_c22_JointSpaceControl = c22_g_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c22_u, 1)),
     "is_active_c22_JointSpaceControl");
  sf_mex_destroy(&c22_u);
  c22_update_debugger_state_c22_JointSpaceControl(chartInstance);
  sf_mex_destroy(&c22_st);
}

static void finalize_c22_JointSpaceControl(SFc22_JointSpaceControlInstanceStruct
  *chartInstance)
{
}

static void sf_c22_JointSpaceControl(SFc22_JointSpaceControlInstanceStruct
  *chartInstance)
{
  int32_T c22_i2;
  int32_T c22_i3;
  int32_T c22_i4;
  int32_T c22_i5;
  int32_T c22_i6;
  real_T (*c22_ddq)[6];
  real_T (*c22_dq)[6];
  real_T (*c22_ddX)[6];
  real_T (*c22_dJ_a)[36];
  real_T (*c22_J_a)[36];
  c22_ddq = (real_T (*)[6])ssGetOutputPortSignal(chartInstance->S, 1);
  c22_dq = (real_T (*)[6])ssGetInputPortSignal(chartInstance->S, 3);
  c22_ddX = (real_T (*)[6])ssGetInputPortSignal(chartInstance->S, 2);
  c22_dJ_a = (real_T (*)[36])ssGetInputPortSignal(chartInstance->S, 1);
  c22_J_a = (real_T (*)[36])ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 19U, chartInstance->c22_sfEvent);
  for (c22_i2 = 0; c22_i2 < 36; c22_i2++) {
    _SFD_DATA_RANGE_CHECK((*c22_J_a)[c22_i2], 0U);
  }

  for (c22_i3 = 0; c22_i3 < 36; c22_i3++) {
    _SFD_DATA_RANGE_CHECK((*c22_dJ_a)[c22_i3], 1U);
  }

  for (c22_i4 = 0; c22_i4 < 6; c22_i4++) {
    _SFD_DATA_RANGE_CHECK((*c22_ddX)[c22_i4], 2U);
  }

  for (c22_i5 = 0; c22_i5 < 6; c22_i5++) {
    _SFD_DATA_RANGE_CHECK((*c22_dq)[c22_i5], 3U);
  }

  for (c22_i6 = 0; c22_i6 < 6; c22_i6++) {
    _SFD_DATA_RANGE_CHECK((*c22_ddq)[c22_i6], 4U);
  }

  chartInstance->c22_sfEvent = CALL_EVENT;
  c22_chartstep_c22_JointSpaceControl(chartInstance);
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_JointSpaceControlMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void c22_chartstep_c22_JointSpaceControl
  (SFc22_JointSpaceControlInstanceStruct *chartInstance)
{
  int32_T c22_i7;
  real_T c22_J_a[36];
  int32_T c22_i8;
  real_T c22_dJ_a[36];
  int32_T c22_i9;
  real_T c22_ddX[6];
  int32_T c22_i10;
  real_T c22_dq[6];
  uint32_T c22_debug_family_var_map[7];
  real_T c22_nargin = 4.0;
  real_T c22_nargout = 1.0;
  real_T c22_ddq[6];
  int32_T c22_i11;
  real_T c22_a[36];
  int32_T c22_i12;
  real_T c22_b[6];
  int32_T c22_i13;
  real_T c22_y[6];
  int32_T c22_i14;
  int32_T c22_i15;
  int32_T c22_i16;
  real_T c22_b_J_a[36];
  int32_T c22_i17;
  int32_T c22_i18;
  int32_T c22_i19;
  int32_T c22_i20;
  int32_T c22_i21;
  int32_T c22_i22;
  int32_T c22_i23;
  int32_T c22_i24;
  int32_T c22_i25;
  int32_T c22_i26;
  int32_T c22_i27;
  real_T (*c22_b_ddq)[6];
  real_T (*c22_b_dq)[6];
  real_T (*c22_b_ddX)[6];
  real_T (*c22_b_dJ_a)[36];
  real_T (*c22_c_J_a)[36];
  c22_b_ddq = (real_T (*)[6])ssGetOutputPortSignal(chartInstance->S, 1);
  c22_b_dq = (real_T (*)[6])ssGetInputPortSignal(chartInstance->S, 3);
  c22_b_ddX = (real_T (*)[6])ssGetInputPortSignal(chartInstance->S, 2);
  c22_b_dJ_a = (real_T (*)[36])ssGetInputPortSignal(chartInstance->S, 1);
  c22_c_J_a = (real_T (*)[36])ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 19U, chartInstance->c22_sfEvent);
  for (c22_i7 = 0; c22_i7 < 36; c22_i7++) {
    c22_J_a[c22_i7] = (*c22_c_J_a)[c22_i7];
  }

  for (c22_i8 = 0; c22_i8 < 36; c22_i8++) {
    c22_dJ_a[c22_i8] = (*c22_b_dJ_a)[c22_i8];
  }

  for (c22_i9 = 0; c22_i9 < 6; c22_i9++) {
    c22_ddX[c22_i9] = (*c22_b_ddX)[c22_i9];
  }

  for (c22_i10 = 0; c22_i10 < 6; c22_i10++) {
    c22_dq[c22_i10] = (*c22_b_dq)[c22_i10];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 7U, 7U, c22_debug_family_names,
    c22_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c22_nargin, 0U, c22_c_sf_marshallOut,
    c22_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c22_nargout, 1U, c22_c_sf_marshallOut,
    c22_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c22_J_a, 2U, c22_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c22_dJ_a, 3U, c22_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c22_ddX, 4U, c22_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c22_dq, 5U, c22_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c22_ddq, 6U, c22_sf_marshallOut,
    c22_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c22_sfEvent, 6);
  for (c22_i11 = 0; c22_i11 < 36; c22_i11++) {
    c22_a[c22_i11] = c22_dJ_a[c22_i11];
  }

  for (c22_i12 = 0; c22_i12 < 6; c22_i12++) {
    c22_b[c22_i12] = c22_dq[c22_i12];
  }

  c22_eml_scalar_eg(chartInstance);
  c22_eml_scalar_eg(chartInstance);
  for (c22_i13 = 0; c22_i13 < 6; c22_i13++) {
    c22_y[c22_i13] = 0.0;
    c22_i14 = 0;
    for (c22_i15 = 0; c22_i15 < 6; c22_i15++) {
      c22_y[c22_i13] += c22_a[c22_i14 + c22_i13] * c22_b[c22_i15];
      c22_i14 += 6;
    }
  }

  for (c22_i16 = 0; c22_i16 < 36; c22_i16++) {
    c22_b_J_a[c22_i16] = c22_J_a[c22_i16];
  }

  c22_inv(chartInstance, c22_b_J_a, c22_a);
  for (c22_i17 = 0; c22_i17 < 6; c22_i17++) {
    c22_y[c22_i17] = c22_ddX[c22_i17] - c22_y[c22_i17];
  }

  c22_eml_scalar_eg(chartInstance);
  c22_eml_scalar_eg(chartInstance);
  for (c22_i18 = 0; c22_i18 < 6; c22_i18++) {
    c22_ddq[c22_i18] = 0.0;
  }

  for (c22_i19 = 0; c22_i19 < 6; c22_i19++) {
    c22_ddq[c22_i19] = 0.0;
  }

  for (c22_i20 = 0; c22_i20 < 6; c22_i20++) {
    c22_b[c22_i20] = c22_ddq[c22_i20];
  }

  for (c22_i21 = 0; c22_i21 < 6; c22_i21++) {
    c22_ddq[c22_i21] = c22_b[c22_i21];
  }

  for (c22_i22 = 0; c22_i22 < 6; c22_i22++) {
    c22_b[c22_i22] = c22_ddq[c22_i22];
  }

  for (c22_i23 = 0; c22_i23 < 6; c22_i23++) {
    c22_ddq[c22_i23] = c22_b[c22_i23];
  }

  for (c22_i24 = 0; c22_i24 < 6; c22_i24++) {
    c22_ddq[c22_i24] = 0.0;
    c22_i25 = 0;
    for (c22_i26 = 0; c22_i26 < 6; c22_i26++) {
      c22_ddq[c22_i24] += c22_a[c22_i25 + c22_i24] * c22_y[c22_i26];
      c22_i25 += 6;
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c22_sfEvent, -6);
  _SFD_SYMBOL_SCOPE_POP();
  for (c22_i27 = 0; c22_i27 < 6; c22_i27++) {
    (*c22_b_ddq)[c22_i27] = c22_ddq[c22_i27];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 19U, chartInstance->c22_sfEvent);
}

static void initSimStructsc22_JointSpaceControl
  (SFc22_JointSpaceControlInstanceStruct *chartInstance)
{
}

static void registerMessagesc22_JointSpaceControl
  (SFc22_JointSpaceControlInstanceStruct *chartInstance)
{
}

static void init_script_number_translation(uint32_T c22_machineNumber, uint32_T
  c22_chartNumber)
{
}

static const mxArray *c22_sf_marshallOut(void *chartInstanceVoid, void
  *c22_inData)
{
  const mxArray *c22_mxArrayOutData = NULL;
  int32_T c22_i28;
  real_T c22_b_inData[6];
  int32_T c22_i29;
  real_T c22_u[6];
  const mxArray *c22_y = NULL;
  SFc22_JointSpaceControlInstanceStruct *chartInstance;
  chartInstance = (SFc22_JointSpaceControlInstanceStruct *)chartInstanceVoid;
  c22_mxArrayOutData = NULL;
  for (c22_i28 = 0; c22_i28 < 6; c22_i28++) {
    c22_b_inData[c22_i28] = (*(real_T (*)[6])c22_inData)[c22_i28];
  }

  for (c22_i29 = 0; c22_i29 < 6; c22_i29++) {
    c22_u[c22_i29] = c22_b_inData[c22_i29];
  }

  c22_y = NULL;
  sf_mex_assign(&c22_y, sf_mex_create("y", c22_u, 0, 0U, 1U, 0U, 1, 6), FALSE);
  sf_mex_assign(&c22_mxArrayOutData, c22_y, FALSE);
  return c22_mxArrayOutData;
}

static void c22_emlrt_marshallIn(SFc22_JointSpaceControlInstanceStruct
  *chartInstance, const mxArray *c22_ddq, const char_T *c22_identifier, real_T
  c22_y[6])
{
  emlrtMsgIdentifier c22_thisId;
  c22_thisId.fIdentifier = c22_identifier;
  c22_thisId.fParent = NULL;
  c22_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c22_ddq), &c22_thisId, c22_y);
  sf_mex_destroy(&c22_ddq);
}

static void c22_b_emlrt_marshallIn(SFc22_JointSpaceControlInstanceStruct
  *chartInstance, const mxArray *c22_u, const emlrtMsgIdentifier *c22_parentId,
  real_T c22_y[6])
{
  real_T c22_dv1[6];
  int32_T c22_i30;
  sf_mex_import(c22_parentId, sf_mex_dup(c22_u), c22_dv1, 1, 0, 0U, 1, 0U, 1, 6);
  for (c22_i30 = 0; c22_i30 < 6; c22_i30++) {
    c22_y[c22_i30] = c22_dv1[c22_i30];
  }

  sf_mex_destroy(&c22_u);
}

static void c22_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c22_mxArrayInData, const char_T *c22_varName, void *c22_outData)
{
  const mxArray *c22_ddq;
  const char_T *c22_identifier;
  emlrtMsgIdentifier c22_thisId;
  real_T c22_y[6];
  int32_T c22_i31;
  SFc22_JointSpaceControlInstanceStruct *chartInstance;
  chartInstance = (SFc22_JointSpaceControlInstanceStruct *)chartInstanceVoid;
  c22_ddq = sf_mex_dup(c22_mxArrayInData);
  c22_identifier = c22_varName;
  c22_thisId.fIdentifier = c22_identifier;
  c22_thisId.fParent = NULL;
  c22_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c22_ddq), &c22_thisId, c22_y);
  sf_mex_destroy(&c22_ddq);
  for (c22_i31 = 0; c22_i31 < 6; c22_i31++) {
    (*(real_T (*)[6])c22_outData)[c22_i31] = c22_y[c22_i31];
  }

  sf_mex_destroy(&c22_mxArrayInData);
}

static const mxArray *c22_b_sf_marshallOut(void *chartInstanceVoid, void
  *c22_inData)
{
  const mxArray *c22_mxArrayOutData = NULL;
  int32_T c22_i32;
  int32_T c22_i33;
  int32_T c22_i34;
  real_T c22_b_inData[36];
  int32_T c22_i35;
  int32_T c22_i36;
  int32_T c22_i37;
  real_T c22_u[36];
  const mxArray *c22_y = NULL;
  SFc22_JointSpaceControlInstanceStruct *chartInstance;
  chartInstance = (SFc22_JointSpaceControlInstanceStruct *)chartInstanceVoid;
  c22_mxArrayOutData = NULL;
  c22_i32 = 0;
  for (c22_i33 = 0; c22_i33 < 6; c22_i33++) {
    for (c22_i34 = 0; c22_i34 < 6; c22_i34++) {
      c22_b_inData[c22_i34 + c22_i32] = (*(real_T (*)[36])c22_inData)[c22_i34 +
        c22_i32];
    }

    c22_i32 += 6;
  }

  c22_i35 = 0;
  for (c22_i36 = 0; c22_i36 < 6; c22_i36++) {
    for (c22_i37 = 0; c22_i37 < 6; c22_i37++) {
      c22_u[c22_i37 + c22_i35] = c22_b_inData[c22_i37 + c22_i35];
    }

    c22_i35 += 6;
  }

  c22_y = NULL;
  sf_mex_assign(&c22_y, sf_mex_create("y", c22_u, 0, 0U, 1U, 0U, 2, 6, 6), FALSE);
  sf_mex_assign(&c22_mxArrayOutData, c22_y, FALSE);
  return c22_mxArrayOutData;
}

static const mxArray *c22_c_sf_marshallOut(void *chartInstanceVoid, void
  *c22_inData)
{
  const mxArray *c22_mxArrayOutData = NULL;
  real_T c22_u;
  const mxArray *c22_y = NULL;
  SFc22_JointSpaceControlInstanceStruct *chartInstance;
  chartInstance = (SFc22_JointSpaceControlInstanceStruct *)chartInstanceVoid;
  c22_mxArrayOutData = NULL;
  c22_u = *(real_T *)c22_inData;
  c22_y = NULL;
  sf_mex_assign(&c22_y, sf_mex_create("y", &c22_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c22_mxArrayOutData, c22_y, FALSE);
  return c22_mxArrayOutData;
}

static real_T c22_c_emlrt_marshallIn(SFc22_JointSpaceControlInstanceStruct
  *chartInstance, const mxArray *c22_u, const emlrtMsgIdentifier *c22_parentId)
{
  real_T c22_y;
  real_T c22_d0;
  sf_mex_import(c22_parentId, sf_mex_dup(c22_u), &c22_d0, 1, 0, 0U, 0, 0U, 0);
  c22_y = c22_d0;
  sf_mex_destroy(&c22_u);
  return c22_y;
}

static void c22_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c22_mxArrayInData, const char_T *c22_varName, void *c22_outData)
{
  const mxArray *c22_nargout;
  const char_T *c22_identifier;
  emlrtMsgIdentifier c22_thisId;
  real_T c22_y;
  SFc22_JointSpaceControlInstanceStruct *chartInstance;
  chartInstance = (SFc22_JointSpaceControlInstanceStruct *)chartInstanceVoid;
  c22_nargout = sf_mex_dup(c22_mxArrayInData);
  c22_identifier = c22_varName;
  c22_thisId.fIdentifier = c22_identifier;
  c22_thisId.fParent = NULL;
  c22_y = c22_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c22_nargout),
    &c22_thisId);
  sf_mex_destroy(&c22_nargout);
  *(real_T *)c22_outData = c22_y;
  sf_mex_destroy(&c22_mxArrayInData);
}

const mxArray *sf_c22_JointSpaceControl_get_eml_resolved_functions_info(void)
{
  const mxArray *c22_nameCaptureInfo;
  c22_ResolvedFunctionInfo c22_info[130];
  const mxArray *c22_m0 = NULL;
  int32_T c22_i38;
  c22_ResolvedFunctionInfo *c22_r0;
  c22_nameCaptureInfo = NULL;
  c22_nameCaptureInfo = NULL;
  c22_info_helper(c22_info);
  c22_b_info_helper(c22_info);
  c22_c_info_helper(c22_info);
  sf_mex_assign(&c22_m0, sf_mex_createstruct("nameCaptureInfo", 1, 130), FALSE);
  for (c22_i38 = 0; c22_i38 < 130; c22_i38++) {
    c22_r0 = &c22_info[c22_i38];
    sf_mex_addfield(c22_m0, sf_mex_create("nameCaptureInfo", c22_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c22_r0->context)), "context", "nameCaptureInfo",
                    c22_i38);
    sf_mex_addfield(c22_m0, sf_mex_create("nameCaptureInfo", c22_r0->name, 15,
      0U, 0U, 0U, 2, 1, strlen(c22_r0->name)), "name", "nameCaptureInfo",
                    c22_i38);
    sf_mex_addfield(c22_m0, sf_mex_create("nameCaptureInfo",
      c22_r0->dominantType, 15, 0U, 0U, 0U, 2, 1, strlen(c22_r0->dominantType)),
                    "dominantType", "nameCaptureInfo", c22_i38);
    sf_mex_addfield(c22_m0, sf_mex_create("nameCaptureInfo", c22_r0->resolved,
      15, 0U, 0U, 0U, 2, 1, strlen(c22_r0->resolved)), "resolved",
                    "nameCaptureInfo", c22_i38);
    sf_mex_addfield(c22_m0, sf_mex_create("nameCaptureInfo", &c22_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c22_i38);
    sf_mex_addfield(c22_m0, sf_mex_create("nameCaptureInfo", &c22_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c22_i38);
    sf_mex_addfield(c22_m0, sf_mex_create("nameCaptureInfo",
      &c22_r0->mFileTimeLo, 7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo",
                    c22_i38);
    sf_mex_addfield(c22_m0, sf_mex_create("nameCaptureInfo",
      &c22_r0->mFileTimeHi, 7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo",
                    c22_i38);
  }

  sf_mex_assign(&c22_nameCaptureInfo, c22_m0, FALSE);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c22_nameCaptureInfo);
  return c22_nameCaptureInfo;
}

static void c22_info_helper(c22_ResolvedFunctionInfo c22_info[130])
{
  c22_info[0].context = "";
  c22_info[0].name = "inv";
  c22_info[0].dominantType = "double";
  c22_info[0].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m";
  c22_info[0].fileTimeLo = 1305339600U;
  c22_info[0].fileTimeHi = 0U;
  c22_info[0].mFileTimeLo = 0U;
  c22_info[0].mFileTimeHi = 0U;
  c22_info[1].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!invNxN";
  c22_info[1].name = "eml_index_class";
  c22_info[1].dominantType = "";
  c22_info[1].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c22_info[1].fileTimeLo = 1323192178U;
  c22_info[1].fileTimeHi = 0U;
  c22_info[1].mFileTimeLo = 0U;
  c22_info[1].mFileTimeHi = 0U;
  c22_info[2].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!invNxN";
  c22_info[2].name = "eml_xgetrf";
  c22_info[2].dominantType = "double";
  c22_info[2].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/eml_xgetrf.m";
  c22_info[2].fileTimeLo = 1286840406U;
  c22_info[2].fileTimeHi = 0U;
  c22_info[2].mFileTimeLo = 0U;
  c22_info[2].mFileTimeHi = 0U;
  c22_info[3].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/eml_xgetrf.m";
  c22_info[3].name = "eml_lapack_xgetrf";
  c22_info[3].dominantType = "double";
  c22_info[3].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/internal/eml_lapack_xgetrf.m";
  c22_info[3].fileTimeLo = 1286840410U;
  c22_info[3].fileTimeHi = 0U;
  c22_info[3].mFileTimeLo = 0U;
  c22_info[3].mFileTimeHi = 0U;
  c22_info[4].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/internal/eml_lapack_xgetrf.m";
  c22_info[4].name = "eml_matlab_zgetrf";
  c22_info[4].dominantType = "double";
  c22_info[4].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c22_info[4].fileTimeLo = 1302710594U;
  c22_info[4].fileTimeHi = 0U;
  c22_info[4].mFileTimeLo = 0U;
  c22_info[4].mFileTimeHi = 0U;
  c22_info[5].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c22_info[5].name = "realmin";
  c22_info[5].dominantType = "char";
  c22_info[5].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/realmin.m";
  c22_info[5].fileTimeLo = 1307672842U;
  c22_info[5].fileTimeHi = 0U;
  c22_info[5].mFileTimeLo = 0U;
  c22_info[5].mFileTimeHi = 0U;
  c22_info[6].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/realmin.m";
  c22_info[6].name = "eml_realmin";
  c22_info[6].dominantType = "char";
  c22_info[6].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_realmin.m";
  c22_info[6].fileTimeLo = 1307672844U;
  c22_info[6].fileTimeHi = 0U;
  c22_info[6].mFileTimeLo = 0U;
  c22_info[6].mFileTimeHi = 0U;
  c22_info[7].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_realmin.m";
  c22_info[7].name = "eml_float_model";
  c22_info[7].dominantType = "char";
  c22_info[7].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_float_model.m";
  c22_info[7].fileTimeLo = 1326749596U;
  c22_info[7].fileTimeHi = 0U;
  c22_info[7].mFileTimeLo = 0U;
  c22_info[7].mFileTimeHi = 0U;
  c22_info[8].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c22_info[8].name = "eps";
  c22_info[8].dominantType = "char";
  c22_info[8].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m";
  c22_info[8].fileTimeLo = 1326749596U;
  c22_info[8].fileTimeHi = 0U;
  c22_info[8].mFileTimeLo = 0U;
  c22_info[8].mFileTimeHi = 0U;
  c22_info[9].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m";
  c22_info[9].name = "eml_is_float_class";
  c22_info[9].dominantType = "char";
  c22_info[9].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_is_float_class.m";
  c22_info[9].fileTimeLo = 1286840382U;
  c22_info[9].fileTimeHi = 0U;
  c22_info[9].mFileTimeLo = 0U;
  c22_info[9].mFileTimeHi = 0U;
  c22_info[10].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m";
  c22_info[10].name = "eml_eps";
  c22_info[10].dominantType = "char";
  c22_info[10].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_eps.m";
  c22_info[10].fileTimeLo = 1326749596U;
  c22_info[10].fileTimeHi = 0U;
  c22_info[10].mFileTimeLo = 0U;
  c22_info[10].mFileTimeHi = 0U;
  c22_info[11].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_eps.m";
  c22_info[11].name = "eml_float_model";
  c22_info[11].dominantType = "char";
  c22_info[11].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_float_model.m";
  c22_info[11].fileTimeLo = 1326749596U;
  c22_info[11].fileTimeHi = 0U;
  c22_info[11].mFileTimeLo = 0U;
  c22_info[11].mFileTimeHi = 0U;
  c22_info[12].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c22_info[12].name = "min";
  c22_info[12].dominantType = "coder.internal.indexInt";
  c22_info[12].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m";
  c22_info[12].fileTimeLo = 1311276918U;
  c22_info[12].fileTimeHi = 0U;
  c22_info[12].mFileTimeLo = 0U;
  c22_info[12].mFileTimeHi = 0U;
  c22_info[13].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m";
  c22_info[13].name = "eml_min_or_max";
  c22_info[13].dominantType = "char";
  c22_info[13].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m";
  c22_info[13].fileTimeLo = 1334093090U;
  c22_info[13].fileTimeHi = 0U;
  c22_info[13].mFileTimeLo = 0U;
  c22_info[13].mFileTimeHi = 0U;
  c22_info[14].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum";
  c22_info[14].name = "eml_scalar_eg";
  c22_info[14].dominantType = "coder.internal.indexInt";
  c22_info[14].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c22_info[14].fileTimeLo = 1286840396U;
  c22_info[14].fileTimeHi = 0U;
  c22_info[14].mFileTimeLo = 0U;
  c22_info[14].mFileTimeHi = 0U;
  c22_info[15].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum";
  c22_info[15].name = "eml_scalexp_alloc";
  c22_info[15].dominantType = "coder.internal.indexInt";
  c22_info[15].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m";
  c22_info[15].fileTimeLo = 1352446460U;
  c22_info[15].fileTimeHi = 0U;
  c22_info[15].mFileTimeLo = 0U;
  c22_info[15].mFileTimeHi = 0U;
  c22_info[16].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum";
  c22_info[16].name = "eml_index_class";
  c22_info[16].dominantType = "";
  c22_info[16].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c22_info[16].fileTimeLo = 1323192178U;
  c22_info[16].fileTimeHi = 0U;
  c22_info[16].mFileTimeLo = 0U;
  c22_info[16].mFileTimeHi = 0U;
  c22_info[17].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_scalar_bin_extremum";
  c22_info[17].name = "eml_scalar_eg";
  c22_info[17].dominantType = "coder.internal.indexInt";
  c22_info[17].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c22_info[17].fileTimeLo = 1286840396U;
  c22_info[17].fileTimeHi = 0U;
  c22_info[17].mFileTimeLo = 0U;
  c22_info[17].mFileTimeHi = 0U;
  c22_info[18].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c22_info[18].name = "colon";
  c22_info[18].dominantType = "double";
  c22_info[18].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m";
  c22_info[18].fileTimeLo = 1348213528U;
  c22_info[18].fileTimeHi = 0U;
  c22_info[18].mFileTimeLo = 0U;
  c22_info[18].mFileTimeHi = 0U;
  c22_info[19].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m";
  c22_info[19].name = "colon";
  c22_info[19].dominantType = "double";
  c22_info[19].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m";
  c22_info[19].fileTimeLo = 1348213528U;
  c22_info[19].fileTimeHi = 0U;
  c22_info[19].mFileTimeLo = 0U;
  c22_info[19].mFileTimeHi = 0U;
  c22_info[20].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m";
  c22_info[20].name = "floor";
  c22_info[20].dominantType = "double";
  c22_info[20].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m";
  c22_info[20].fileTimeLo = 1343851980U;
  c22_info[20].fileTimeHi = 0U;
  c22_info[20].mFileTimeLo = 0U;
  c22_info[20].mFileTimeHi = 0U;
  c22_info[21].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m";
  c22_info[21].name = "eml_scalar_floor";
  c22_info[21].dominantType = "double";
  c22_info[21].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_floor.m";
  c22_info[21].fileTimeLo = 1286840326U;
  c22_info[21].fileTimeHi = 0U;
  c22_info[21].mFileTimeLo = 0U;
  c22_info[21].mFileTimeHi = 0U;
  c22_info[22].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!checkrange";
  c22_info[22].name = "intmin";
  c22_info[22].dominantType = "char";
  c22_info[22].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmin.m";
  c22_info[22].fileTimeLo = 1311276918U;
  c22_info[22].fileTimeHi = 0U;
  c22_info[22].mFileTimeLo = 0U;
  c22_info[22].mFileTimeHi = 0U;
  c22_info[23].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!checkrange";
  c22_info[23].name = "intmax";
  c22_info[23].dominantType = "char";
  c22_info[23].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m";
  c22_info[23].fileTimeLo = 1311276916U;
  c22_info[23].fileTimeHi = 0U;
  c22_info[23].mFileTimeLo = 0U;
  c22_info[23].mFileTimeHi = 0U;
  c22_info[24].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!eml_integer_colon_dispatcher";
  c22_info[24].name = "intmin";
  c22_info[24].dominantType = "char";
  c22_info[24].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmin.m";
  c22_info[24].fileTimeLo = 1311276918U;
  c22_info[24].fileTimeHi = 0U;
  c22_info[24].mFileTimeLo = 0U;
  c22_info[24].mFileTimeHi = 0U;
  c22_info[25].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!eml_integer_colon_dispatcher";
  c22_info[25].name = "intmax";
  c22_info[25].dominantType = "char";
  c22_info[25].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m";
  c22_info[25].fileTimeLo = 1311276916U;
  c22_info[25].fileTimeHi = 0U;
  c22_info[25].mFileTimeLo = 0U;
  c22_info[25].mFileTimeHi = 0U;
  c22_info[26].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!eml_integer_colon_dispatcher";
  c22_info[26].name = "eml_isa_uint";
  c22_info[26].dominantType = "coder.internal.indexInt";
  c22_info[26].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isa_uint.m";
  c22_info[26].fileTimeLo = 1286840384U;
  c22_info[26].fileTimeHi = 0U;
  c22_info[26].mFileTimeLo = 0U;
  c22_info[26].mFileTimeHi = 0U;
  c22_info[27].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!integer_colon_length_nonnegd";
  c22_info[27].name = "eml_unsigned_class";
  c22_info[27].dominantType = "char";
  c22_info[27].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_unsigned_class.m";
  c22_info[27].fileTimeLo = 1323192180U;
  c22_info[27].fileTimeHi = 0U;
  c22_info[27].mFileTimeLo = 0U;
  c22_info[27].mFileTimeHi = 0U;
  c22_info[28].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_unsigned_class.m";
  c22_info[28].name = "eml_index_class";
  c22_info[28].dominantType = "";
  c22_info[28].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c22_info[28].fileTimeLo = 1323192178U;
  c22_info[28].fileTimeHi = 0U;
  c22_info[28].mFileTimeLo = 0U;
  c22_info[28].mFileTimeHi = 0U;
  c22_info[29].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!integer_colon_length_nonnegd";
  c22_info[29].name = "eml_index_class";
  c22_info[29].dominantType = "";
  c22_info[29].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c22_info[29].fileTimeLo = 1323192178U;
  c22_info[29].fileTimeHi = 0U;
  c22_info[29].mFileTimeLo = 0U;
  c22_info[29].mFileTimeHi = 0U;
  c22_info[30].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!integer_colon_length_nonnegd";
  c22_info[30].name = "intmax";
  c22_info[30].dominantType = "char";
  c22_info[30].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m";
  c22_info[30].fileTimeLo = 1311276916U;
  c22_info[30].fileTimeHi = 0U;
  c22_info[30].mFileTimeLo = 0U;
  c22_info[30].mFileTimeHi = 0U;
  c22_info[31].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!integer_colon_length_nonnegd";
  c22_info[31].name = "eml_isa_uint";
  c22_info[31].dominantType = "coder.internal.indexInt";
  c22_info[31].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isa_uint.m";
  c22_info[31].fileTimeLo = 1286840384U;
  c22_info[31].fileTimeHi = 0U;
  c22_info[31].mFileTimeLo = 0U;
  c22_info[31].mFileTimeHi = 0U;
  c22_info[32].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!integer_colon_length_nonnegd";
  c22_info[32].name = "eml_index_plus";
  c22_info[32].dominantType = "double";
  c22_info[32].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c22_info[32].fileTimeLo = 1286840378U;
  c22_info[32].fileTimeHi = 0U;
  c22_info[32].mFileTimeLo = 0U;
  c22_info[32].mFileTimeHi = 0U;
  c22_info[33].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c22_info[33].name = "eml_index_class";
  c22_info[33].dominantType = "";
  c22_info[33].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c22_info[33].fileTimeLo = 1323192178U;
  c22_info[33].fileTimeHi = 0U;
  c22_info[33].mFileTimeLo = 0U;
  c22_info[33].mFileTimeHi = 0U;
  c22_info[34].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!eml_signed_integer_colon";
  c22_info[34].name = "eml_int_forloop_overflow_check";
  c22_info[34].dominantType = "";
  c22_info[34].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m";
  c22_info[34].fileTimeLo = 1346531940U;
  c22_info[34].fileTimeHi = 0U;
  c22_info[34].mFileTimeLo = 0U;
  c22_info[34].mFileTimeHi = 0U;
  c22_info[35].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m!eml_int_forloop_overflow_check_helper";
  c22_info[35].name = "intmax";
  c22_info[35].dominantType = "char";
  c22_info[35].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m";
  c22_info[35].fileTimeLo = 1311276916U;
  c22_info[35].fileTimeHi = 0U;
  c22_info[35].mFileTimeLo = 0U;
  c22_info[35].mFileTimeHi = 0U;
  c22_info[36].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c22_info[36].name = "eml_index_class";
  c22_info[36].dominantType = "";
  c22_info[36].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c22_info[36].fileTimeLo = 1323192178U;
  c22_info[36].fileTimeHi = 0U;
  c22_info[36].mFileTimeLo = 0U;
  c22_info[36].mFileTimeHi = 0U;
  c22_info[37].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c22_info[37].name = "eml_index_plus";
  c22_info[37].dominantType = "double";
  c22_info[37].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c22_info[37].fileTimeLo = 1286840378U;
  c22_info[37].fileTimeHi = 0U;
  c22_info[37].mFileTimeLo = 0U;
  c22_info[37].mFileTimeHi = 0U;
  c22_info[38].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c22_info[38].name = "eml_int_forloop_overflow_check";
  c22_info[38].dominantType = "";
  c22_info[38].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m";
  c22_info[38].fileTimeLo = 1346531940U;
  c22_info[38].fileTimeHi = 0U;
  c22_info[38].mFileTimeLo = 0U;
  c22_info[38].mFileTimeHi = 0U;
  c22_info[39].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c22_info[39].name = "eml_index_minus";
  c22_info[39].dominantType = "double";
  c22_info[39].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m";
  c22_info[39].fileTimeLo = 1286840378U;
  c22_info[39].fileTimeHi = 0U;
  c22_info[39].mFileTimeLo = 0U;
  c22_info[39].mFileTimeHi = 0U;
  c22_info[40].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m";
  c22_info[40].name = "eml_index_class";
  c22_info[40].dominantType = "";
  c22_info[40].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c22_info[40].fileTimeLo = 1323192178U;
  c22_info[40].fileTimeHi = 0U;
  c22_info[40].mFileTimeLo = 0U;
  c22_info[40].mFileTimeHi = 0U;
  c22_info[41].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c22_info[41].name = "eml_index_minus";
  c22_info[41].dominantType = "coder.internal.indexInt";
  c22_info[41].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m";
  c22_info[41].fileTimeLo = 1286840378U;
  c22_info[41].fileTimeHi = 0U;
  c22_info[41].mFileTimeLo = 0U;
  c22_info[41].mFileTimeHi = 0U;
  c22_info[42].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c22_info[42].name = "eml_index_times";
  c22_info[42].dominantType = "coder.internal.indexInt";
  c22_info[42].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_times.m";
  c22_info[42].fileTimeLo = 1286840380U;
  c22_info[42].fileTimeHi = 0U;
  c22_info[42].mFileTimeLo = 0U;
  c22_info[42].mFileTimeHi = 0U;
  c22_info[43].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_times.m";
  c22_info[43].name = "eml_index_class";
  c22_info[43].dominantType = "";
  c22_info[43].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c22_info[43].fileTimeLo = 1323192178U;
  c22_info[43].fileTimeHi = 0U;
  c22_info[43].mFileTimeLo = 0U;
  c22_info[43].mFileTimeHi = 0U;
  c22_info[44].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c22_info[44].name = "eml_index_plus";
  c22_info[44].dominantType = "coder.internal.indexInt";
  c22_info[44].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c22_info[44].fileTimeLo = 1286840378U;
  c22_info[44].fileTimeHi = 0U;
  c22_info[44].mFileTimeLo = 0U;
  c22_info[44].mFileTimeHi = 0U;
  c22_info[45].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c22_info[45].name = "eml_ixamax";
  c22_info[45].dominantType = "double";
  c22_info[45].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_ixamax.m";
  c22_info[45].fileTimeLo = 1299098370U;
  c22_info[45].fileTimeHi = 0U;
  c22_info[45].mFileTimeLo = 0U;
  c22_info[45].mFileTimeHi = 0U;
  c22_info[46].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_ixamax.m";
  c22_info[46].name = "eml_blas_inline";
  c22_info[46].dominantType = "";
  c22_info[46].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_blas_inline.m";
  c22_info[46].fileTimeLo = 1299098368U;
  c22_info[46].fileTimeHi = 0U;
  c22_info[46].mFileTimeLo = 0U;
  c22_info[46].mFileTimeHi = 0U;
  c22_info[47].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_ixamax.m!below_threshold";
  c22_info[47].name = "length";
  c22_info[47].dominantType = "double";
  c22_info[47].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/length.m";
  c22_info[47].fileTimeLo = 1303167806U;
  c22_info[47].fileTimeHi = 0U;
  c22_info[47].mFileTimeLo = 0U;
  c22_info[47].mFileTimeHi = 0U;
  c22_info[48].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/length.m!intlength";
  c22_info[48].name = "eml_index_class";
  c22_info[48].dominantType = "";
  c22_info[48].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c22_info[48].fileTimeLo = 1323192178U;
  c22_info[48].fileTimeHi = 0U;
  c22_info[48].mFileTimeLo = 0U;
  c22_info[48].mFileTimeHi = 0U;
  c22_info[49].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_ixamax.m";
  c22_info[49].name = "eml_index_class";
  c22_info[49].dominantType = "";
  c22_info[49].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c22_info[49].fileTimeLo = 1323192178U;
  c22_info[49].fileTimeHi = 0U;
  c22_info[49].mFileTimeLo = 0U;
  c22_info[49].mFileTimeHi = 0U;
  c22_info[50].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_ixamax.m";
  c22_info[50].name = "eml_refblas_ixamax";
  c22_info[50].dominantType = "double";
  c22_info[50].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_ixamax.m";
  c22_info[50].fileTimeLo = 1299098370U;
  c22_info[50].fileTimeHi = 0U;
  c22_info[50].mFileTimeLo = 0U;
  c22_info[50].mFileTimeHi = 0U;
  c22_info[51].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_ixamax.m";
  c22_info[51].name = "eml_index_class";
  c22_info[51].dominantType = "";
  c22_info[51].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c22_info[51].fileTimeLo = 1323192178U;
  c22_info[51].fileTimeHi = 0U;
  c22_info[51].mFileTimeLo = 0U;
  c22_info[51].mFileTimeHi = 0U;
  c22_info[52].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_ixamax.m";
  c22_info[52].name = "eml_xcabs1";
  c22_info[52].dominantType = "double";
  c22_info[52].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xcabs1.m";
  c22_info[52].fileTimeLo = 1286840306U;
  c22_info[52].fileTimeHi = 0U;
  c22_info[52].mFileTimeLo = 0U;
  c22_info[52].mFileTimeHi = 0U;
  c22_info[53].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xcabs1.m";
  c22_info[53].name = "abs";
  c22_info[53].dominantType = "double";
  c22_info[53].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c22_info[53].fileTimeLo = 1343851966U;
  c22_info[53].fileTimeHi = 0U;
  c22_info[53].mFileTimeLo = 0U;
  c22_info[53].mFileTimeHi = 0U;
  c22_info[54].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c22_info[54].name = "eml_scalar_abs";
  c22_info[54].dominantType = "double";
  c22_info[54].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_abs.m";
  c22_info[54].fileTimeLo = 1286840312U;
  c22_info[54].fileTimeHi = 0U;
  c22_info[54].mFileTimeLo = 0U;
  c22_info[54].mFileTimeHi = 0U;
  c22_info[55].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_ixamax.m";
  c22_info[55].name = "eml_int_forloop_overflow_check";
  c22_info[55].dominantType = "";
  c22_info[55].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m";
  c22_info[55].fileTimeLo = 1346531940U;
  c22_info[55].fileTimeHi = 0U;
  c22_info[55].mFileTimeLo = 0U;
  c22_info[55].mFileTimeHi = 0U;
  c22_info[56].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_ixamax.m";
  c22_info[56].name = "eml_index_plus";
  c22_info[56].dominantType = "coder.internal.indexInt";
  c22_info[56].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c22_info[56].fileTimeLo = 1286840378U;
  c22_info[56].fileTimeHi = 0U;
  c22_info[56].mFileTimeLo = 0U;
  c22_info[56].mFileTimeHi = 0U;
  c22_info[57].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c22_info[57].name = "eml_xswap";
  c22_info[57].dominantType = "double";
  c22_info[57].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xswap.m";
  c22_info[57].fileTimeLo = 1299098378U;
  c22_info[57].fileTimeHi = 0U;
  c22_info[57].mFileTimeLo = 0U;
  c22_info[57].mFileTimeHi = 0U;
  c22_info[58].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xswap.m";
  c22_info[58].name = "eml_blas_inline";
  c22_info[58].dominantType = "";
  c22_info[58].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_blas_inline.m";
  c22_info[58].fileTimeLo = 1299098368U;
  c22_info[58].fileTimeHi = 0U;
  c22_info[58].mFileTimeLo = 0U;
  c22_info[58].mFileTimeHi = 0U;
  c22_info[59].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xswap.m";
  c22_info[59].name = "eml_index_class";
  c22_info[59].dominantType = "";
  c22_info[59].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c22_info[59].fileTimeLo = 1323192178U;
  c22_info[59].fileTimeHi = 0U;
  c22_info[59].mFileTimeLo = 0U;
  c22_info[59].mFileTimeHi = 0U;
  c22_info[60].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xswap.m";
  c22_info[60].name = "eml_refblas_xswap";
  c22_info[60].dominantType = "double";
  c22_info[60].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xswap.m";
  c22_info[60].fileTimeLo = 1299098386U;
  c22_info[60].fileTimeHi = 0U;
  c22_info[60].mFileTimeLo = 0U;
  c22_info[60].mFileTimeHi = 0U;
  c22_info[61].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xswap.m";
  c22_info[61].name = "eml_index_class";
  c22_info[61].dominantType = "";
  c22_info[61].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c22_info[61].fileTimeLo = 1323192178U;
  c22_info[61].fileTimeHi = 0U;
  c22_info[61].mFileTimeLo = 0U;
  c22_info[61].mFileTimeHi = 0U;
  c22_info[62].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xswap.m";
  c22_info[62].name = "abs";
  c22_info[62].dominantType = "coder.internal.indexInt";
  c22_info[62].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c22_info[62].fileTimeLo = 1343851966U;
  c22_info[62].fileTimeHi = 0U;
  c22_info[62].mFileTimeLo = 0U;
  c22_info[62].mFileTimeHi = 0U;
  c22_info[63].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c22_info[63].name = "eml_scalar_abs";
  c22_info[63].dominantType = "coder.internal.indexInt";
  c22_info[63].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_abs.m";
  c22_info[63].fileTimeLo = 1286840312U;
  c22_info[63].fileTimeHi = 0U;
  c22_info[63].mFileTimeLo = 0U;
  c22_info[63].mFileTimeHi = 0U;
}

static void c22_b_info_helper(c22_ResolvedFunctionInfo c22_info[130])
{
  c22_info[64].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xswap.m";
  c22_info[64].name = "eml_int_forloop_overflow_check";
  c22_info[64].dominantType = "";
  c22_info[64].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m";
  c22_info[64].fileTimeLo = 1346531940U;
  c22_info[64].fileTimeHi = 0U;
  c22_info[64].mFileTimeLo = 0U;
  c22_info[64].mFileTimeHi = 0U;
  c22_info[65].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xswap.m";
  c22_info[65].name = "eml_index_plus";
  c22_info[65].dominantType = "coder.internal.indexInt";
  c22_info[65].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c22_info[65].fileTimeLo = 1286840378U;
  c22_info[65].fileTimeHi = 0U;
  c22_info[65].mFileTimeLo = 0U;
  c22_info[65].mFileTimeHi = 0U;
  c22_info[66].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c22_info[66].name = "eml_div";
  c22_info[66].dominantType = "double";
  c22_info[66].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m";
  c22_info[66].fileTimeLo = 1313369410U;
  c22_info[66].fileTimeHi = 0U;
  c22_info[66].mFileTimeLo = 0U;
  c22_info[66].mFileTimeHi = 0U;
  c22_info[67].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c22_info[67].name = "eml_xgeru";
  c22_info[67].dominantType = "double";
  c22_info[67].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgeru.m";
  c22_info[67].fileTimeLo = 1299098374U;
  c22_info[67].fileTimeHi = 0U;
  c22_info[67].mFileTimeLo = 0U;
  c22_info[67].mFileTimeHi = 0U;
  c22_info[68].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgeru.m";
  c22_info[68].name = "eml_blas_inline";
  c22_info[68].dominantType = "";
  c22_info[68].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_blas_inline.m";
  c22_info[68].fileTimeLo = 1299098368U;
  c22_info[68].fileTimeHi = 0U;
  c22_info[68].mFileTimeLo = 0U;
  c22_info[68].mFileTimeHi = 0U;
  c22_info[69].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgeru.m";
  c22_info[69].name = "eml_xger";
  c22_info[69].dominantType = "double";
  c22_info[69].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xger.m";
  c22_info[69].fileTimeLo = 1299098374U;
  c22_info[69].fileTimeHi = 0U;
  c22_info[69].mFileTimeLo = 0U;
  c22_info[69].mFileTimeHi = 0U;
  c22_info[70].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xger.m";
  c22_info[70].name = "eml_blas_inline";
  c22_info[70].dominantType = "";
  c22_info[70].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_blas_inline.m";
  c22_info[70].fileTimeLo = 1299098368U;
  c22_info[70].fileTimeHi = 0U;
  c22_info[70].mFileTimeLo = 0U;
  c22_info[70].mFileTimeHi = 0U;
  c22_info[71].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xger.m!below_threshold";
  c22_info[71].name = "intmax";
  c22_info[71].dominantType = "char";
  c22_info[71].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m";
  c22_info[71].fileTimeLo = 1311276916U;
  c22_info[71].fileTimeHi = 0U;
  c22_info[71].mFileTimeLo = 0U;
  c22_info[71].mFileTimeHi = 0U;
  c22_info[72].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xger.m!below_threshold";
  c22_info[72].name = "min";
  c22_info[72].dominantType = "double";
  c22_info[72].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m";
  c22_info[72].fileTimeLo = 1311276918U;
  c22_info[72].fileTimeHi = 0U;
  c22_info[72].mFileTimeLo = 0U;
  c22_info[72].mFileTimeHi = 0U;
  c22_info[73].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum";
  c22_info[73].name = "eml_scalar_eg";
  c22_info[73].dominantType = "double";
  c22_info[73].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c22_info[73].fileTimeLo = 1286840396U;
  c22_info[73].fileTimeHi = 0U;
  c22_info[73].mFileTimeLo = 0U;
  c22_info[73].mFileTimeHi = 0U;
  c22_info[74].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum";
  c22_info[74].name = "eml_scalexp_alloc";
  c22_info[74].dominantType = "double";
  c22_info[74].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m";
  c22_info[74].fileTimeLo = 1352446460U;
  c22_info[74].fileTimeHi = 0U;
  c22_info[74].mFileTimeLo = 0U;
  c22_info[74].mFileTimeHi = 0U;
  c22_info[75].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_scalar_bin_extremum";
  c22_info[75].name = "eml_scalar_eg";
  c22_info[75].dominantType = "double";
  c22_info[75].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c22_info[75].fileTimeLo = 1286840396U;
  c22_info[75].fileTimeHi = 0U;
  c22_info[75].mFileTimeLo = 0U;
  c22_info[75].mFileTimeHi = 0U;
  c22_info[76].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xger.m!below_threshold";
  c22_info[76].name = "mtimes";
  c22_info[76].dominantType = "double";
  c22_info[76].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c22_info[76].fileTimeLo = 1289541292U;
  c22_info[76].fileTimeHi = 0U;
  c22_info[76].mFileTimeLo = 0U;
  c22_info[76].mFileTimeHi = 0U;
  c22_info[77].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xger.m";
  c22_info[77].name = "eml_index_class";
  c22_info[77].dominantType = "";
  c22_info[77].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c22_info[77].fileTimeLo = 1323192178U;
  c22_info[77].fileTimeHi = 0U;
  c22_info[77].mFileTimeLo = 0U;
  c22_info[77].mFileTimeHi = 0U;
  c22_info[78].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xger.m";
  c22_info[78].name = "eml_refblas_xger";
  c22_info[78].dominantType = "double";
  c22_info[78].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xger.m";
  c22_info[78].fileTimeLo = 1299098376U;
  c22_info[78].fileTimeHi = 0U;
  c22_info[78].mFileTimeLo = 0U;
  c22_info[78].mFileTimeHi = 0U;
  c22_info[79].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xger.m";
  c22_info[79].name = "eml_refblas_xgerx";
  c22_info[79].dominantType = "char";
  c22_info[79].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgerx.m";
  c22_info[79].fileTimeLo = 1299098378U;
  c22_info[79].fileTimeHi = 0U;
  c22_info[79].mFileTimeLo = 0U;
  c22_info[79].mFileTimeHi = 0U;
  c22_info[80].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgerx.m";
  c22_info[80].name = "eml_index_class";
  c22_info[80].dominantType = "";
  c22_info[80].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c22_info[80].fileTimeLo = 1323192178U;
  c22_info[80].fileTimeHi = 0U;
  c22_info[80].mFileTimeLo = 0U;
  c22_info[80].mFileTimeHi = 0U;
  c22_info[81].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgerx.m";
  c22_info[81].name = "abs";
  c22_info[81].dominantType = "coder.internal.indexInt";
  c22_info[81].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c22_info[81].fileTimeLo = 1343851966U;
  c22_info[81].fileTimeHi = 0U;
  c22_info[81].mFileTimeLo = 0U;
  c22_info[81].mFileTimeHi = 0U;
  c22_info[82].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgerx.m";
  c22_info[82].name = "eml_index_minus";
  c22_info[82].dominantType = "double";
  c22_info[82].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m";
  c22_info[82].fileTimeLo = 1286840378U;
  c22_info[82].fileTimeHi = 0U;
  c22_info[82].mFileTimeLo = 0U;
  c22_info[82].mFileTimeHi = 0U;
  c22_info[83].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgerx.m";
  c22_info[83].name = "eml_int_forloop_overflow_check";
  c22_info[83].dominantType = "";
  c22_info[83].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m";
  c22_info[83].fileTimeLo = 1346531940U;
  c22_info[83].fileTimeHi = 0U;
  c22_info[83].mFileTimeLo = 0U;
  c22_info[83].mFileTimeHi = 0U;
  c22_info[84].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgerx.m";
  c22_info[84].name = "eml_index_plus";
  c22_info[84].dominantType = "double";
  c22_info[84].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c22_info[84].fileTimeLo = 1286840378U;
  c22_info[84].fileTimeHi = 0U;
  c22_info[84].mFileTimeLo = 0U;
  c22_info[84].mFileTimeHi = 0U;
  c22_info[85].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgerx.m";
  c22_info[85].name = "eml_index_plus";
  c22_info[85].dominantType = "coder.internal.indexInt";
  c22_info[85].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c22_info[85].fileTimeLo = 1286840378U;
  c22_info[85].fileTimeHi = 0U;
  c22_info[85].mFileTimeLo = 0U;
  c22_info[85].mFileTimeHi = 0U;
  c22_info[86].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!invNxN";
  c22_info[86].name = "eml_ipiv2perm";
  c22_info[86].dominantType = "coder.internal.indexInt";
  c22_info[86].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_ipiv2perm.m";
  c22_info[86].fileTimeLo = 1286840382U;
  c22_info[86].fileTimeHi = 0U;
  c22_info[86].mFileTimeLo = 0U;
  c22_info[86].mFileTimeHi = 0U;
  c22_info[87].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_ipiv2perm.m";
  c22_info[87].name = "colon";
  c22_info[87].dominantType = "double";
  c22_info[87].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m";
  c22_info[87].fileTimeLo = 1348213528U;
  c22_info[87].fileTimeHi = 0U;
  c22_info[87].mFileTimeLo = 0U;
  c22_info[87].mFileTimeHi = 0U;
  c22_info[88].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_ipiv2perm.m";
  c22_info[88].name = "eml_index_class";
  c22_info[88].dominantType = "";
  c22_info[88].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c22_info[88].fileTimeLo = 1323192178U;
  c22_info[88].fileTimeHi = 0U;
  c22_info[88].mFileTimeLo = 0U;
  c22_info[88].mFileTimeHi = 0U;
  c22_info[89].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_ipiv2perm.m";
  c22_info[89].name = "coder.internal.indexIntRelop";
  c22_info[89].dominantType = "";
  c22_info[89].resolved =
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexIntRelop.m";
  c22_info[89].fileTimeLo = 1326749922U;
  c22_info[89].fileTimeHi = 0U;
  c22_info[89].mFileTimeLo = 0U;
  c22_info[89].mFileTimeHi = 0U;
  c22_info[90].context =
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexIntRelop.m!float_class_contains_indexIntClass";
  c22_info[90].name = "eml_float_model";
  c22_info[90].dominantType = "char";
  c22_info[90].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_float_model.m";
  c22_info[90].fileTimeLo = 1326749596U;
  c22_info[90].fileTimeHi = 0U;
  c22_info[90].mFileTimeLo = 0U;
  c22_info[90].mFileTimeHi = 0U;
  c22_info[91].context =
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexIntRelop.m!is_signed_indexIntClass";
  c22_info[91].name = "intmin";
  c22_info[91].dominantType = "char";
  c22_info[91].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmin.m";
  c22_info[91].fileTimeLo = 1311276918U;
  c22_info[91].fileTimeHi = 0U;
  c22_info[91].mFileTimeLo = 0U;
  c22_info[91].mFileTimeHi = 0U;
  c22_info[92].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!invNxN";
  c22_info[92].name = "eml_int_forloop_overflow_check";
  c22_info[92].dominantType = "";
  c22_info[92].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m";
  c22_info[92].fileTimeLo = 1346531940U;
  c22_info[92].fileTimeHi = 0U;
  c22_info[92].mFileTimeLo = 0U;
  c22_info[92].mFileTimeHi = 0U;
  c22_info[93].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!invNxN";
  c22_info[93].name = "eml_index_plus";
  c22_info[93].dominantType = "double";
  c22_info[93].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c22_info[93].fileTimeLo = 1286840378U;
  c22_info[93].fileTimeHi = 0U;
  c22_info[93].mFileTimeLo = 0U;
  c22_info[93].mFileTimeHi = 0U;
  c22_info[94].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!invNxN";
  c22_info[94].name = "mtimes";
  c22_info[94].dominantType = "double";
  c22_info[94].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c22_info[94].fileTimeLo = 1289541292U;
  c22_info[94].fileTimeHi = 0U;
  c22_info[94].mFileTimeLo = 0U;
  c22_info[94].mFileTimeHi = 0U;
  c22_info[95].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!invNxN";
  c22_info[95].name = "eml_scalar_eg";
  c22_info[95].dominantType = "double";
  c22_info[95].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c22_info[95].fileTimeLo = 1286840396U;
  c22_info[95].fileTimeHi = 0U;
  c22_info[95].mFileTimeLo = 0U;
  c22_info[95].mFileTimeHi = 0U;
  c22_info[96].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!invNxN";
  c22_info[96].name = "eml_xtrsm";
  c22_info[96].dominantType = "char";
  c22_info[96].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xtrsm.m";
  c22_info[96].fileTimeLo = 1299098378U;
  c22_info[96].fileTimeHi = 0U;
  c22_info[96].mFileTimeLo = 0U;
  c22_info[96].mFileTimeHi = 0U;
  c22_info[97].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xtrsm.m";
  c22_info[97].name = "eml_blas_inline";
  c22_info[97].dominantType = "";
  c22_info[97].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_blas_inline.m";
  c22_info[97].fileTimeLo = 1299098368U;
  c22_info[97].fileTimeHi = 0U;
  c22_info[97].mFileTimeLo = 0U;
  c22_info[97].mFileTimeHi = 0U;
  c22_info[98].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xtrsm.m!below_threshold";
  c22_info[98].name = "mtimes";
  c22_info[98].dominantType = "double";
  c22_info[98].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c22_info[98].fileTimeLo = 1289541292U;
  c22_info[98].fileTimeHi = 0U;
  c22_info[98].mFileTimeLo = 0U;
  c22_info[98].mFileTimeHi = 0U;
  c22_info[99].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xtrsm.m";
  c22_info[99].name = "eml_index_class";
  c22_info[99].dominantType = "";
  c22_info[99].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c22_info[99].fileTimeLo = 1323192178U;
  c22_info[99].fileTimeHi = 0U;
  c22_info[99].mFileTimeLo = 0U;
  c22_info[99].mFileTimeHi = 0U;
  c22_info[100].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xtrsm.m";
  c22_info[100].name = "eml_scalar_eg";
  c22_info[100].dominantType = "double";
  c22_info[100].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c22_info[100].fileTimeLo = 1286840396U;
  c22_info[100].fileTimeHi = 0U;
  c22_info[100].mFileTimeLo = 0U;
  c22_info[100].mFileTimeHi = 0U;
  c22_info[101].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xtrsm.m";
  c22_info[101].name = "eml_refblas_xtrsm";
  c22_info[101].dominantType = "char";
  c22_info[101].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xtrsm.m";
  c22_info[101].fileTimeLo = 1299098386U;
  c22_info[101].fileTimeHi = 0U;
  c22_info[101].mFileTimeLo = 0U;
  c22_info[101].mFileTimeHi = 0U;
  c22_info[102].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xtrsm.m";
  c22_info[102].name = "eml_scalar_eg";
  c22_info[102].dominantType = "double";
  c22_info[102].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c22_info[102].fileTimeLo = 1286840396U;
  c22_info[102].fileTimeHi = 0U;
  c22_info[102].mFileTimeLo = 0U;
  c22_info[102].mFileTimeHi = 0U;
  c22_info[103].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xtrsm.m";
  c22_info[103].name = "eml_index_minus";
  c22_info[103].dominantType = "double";
  c22_info[103].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m";
  c22_info[103].fileTimeLo = 1286840378U;
  c22_info[103].fileTimeHi = 0U;
  c22_info[103].mFileTimeLo = 0U;
  c22_info[103].mFileTimeHi = 0U;
  c22_info[104].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xtrsm.m";
  c22_info[104].name = "eml_index_class";
  c22_info[104].dominantType = "";
  c22_info[104].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c22_info[104].fileTimeLo = 1323192178U;
  c22_info[104].fileTimeHi = 0U;
  c22_info[104].mFileTimeLo = 0U;
  c22_info[104].mFileTimeHi = 0U;
  c22_info[105].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xtrsm.m";
  c22_info[105].name = "eml_int_forloop_overflow_check";
  c22_info[105].dominantType = "";
  c22_info[105].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m";
  c22_info[105].fileTimeLo = 1346531940U;
  c22_info[105].fileTimeHi = 0U;
  c22_info[105].mFileTimeLo = 0U;
  c22_info[105].mFileTimeHi = 0U;
  c22_info[106].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xtrsm.m";
  c22_info[106].name = "eml_index_times";
  c22_info[106].dominantType = "coder.internal.indexInt";
  c22_info[106].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_times.m";
  c22_info[106].fileTimeLo = 1286840380U;
  c22_info[106].fileTimeHi = 0U;
  c22_info[106].mFileTimeLo = 0U;
  c22_info[106].mFileTimeHi = 0U;
  c22_info[107].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xtrsm.m";
  c22_info[107].name = "eml_index_plus";
  c22_info[107].dominantType = "coder.internal.indexInt";
  c22_info[107].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c22_info[107].fileTimeLo = 1286840378U;
  c22_info[107].fileTimeHi = 0U;
  c22_info[107].mFileTimeLo = 0U;
  c22_info[107].mFileTimeHi = 0U;
  c22_info[108].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m!eml_int_forloop_overflow_check_helper";
  c22_info[108].name = "intmin";
  c22_info[108].dominantType = "char";
  c22_info[108].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmin.m";
  c22_info[108].fileTimeLo = 1311276918U;
  c22_info[108].fileTimeHi = 0U;
  c22_info[108].mFileTimeLo = 0U;
  c22_info[108].mFileTimeHi = 0U;
  c22_info[109].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xtrsm.m";
  c22_info[109].name = "eml_div";
  c22_info[109].dominantType = "double";
  c22_info[109].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m";
  c22_info[109].fileTimeLo = 1313369410U;
  c22_info[109].fileTimeHi = 0U;
  c22_info[109].mFileTimeLo = 0U;
  c22_info[109].mFileTimeHi = 0U;
  c22_info[110].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!checkcond";
  c22_info[110].name = "norm";
  c22_info[110].dominantType = "double";
  c22_info[110].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m";
  c22_info[110].fileTimeLo = 1336543694U;
  c22_info[110].fileTimeHi = 0U;
  c22_info[110].mFileTimeLo = 0U;
  c22_info[110].mFileTimeHi = 0U;
  c22_info[111].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m!mat1norm";
  c22_info[111].name = "abs";
  c22_info[111].dominantType = "double";
  c22_info[111].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c22_info[111].fileTimeLo = 1343851966U;
  c22_info[111].fileTimeHi = 0U;
  c22_info[111].mFileTimeLo = 0U;
  c22_info[111].mFileTimeHi = 0U;
  c22_info[112].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m!mat1norm";
  c22_info[112].name = "isnan";
  c22_info[112].dominantType = "double";
  c22_info[112].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isnan.m";
  c22_info[112].fileTimeLo = 1286840360U;
  c22_info[112].fileTimeHi = 0U;
  c22_info[112].mFileTimeLo = 0U;
  c22_info[112].mFileTimeHi = 0U;
  c22_info[113].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m!mat1norm";
  c22_info[113].name = "eml_guarded_nan";
  c22_info[113].dominantType = "char";
  c22_info[113].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_guarded_nan.m";
  c22_info[113].fileTimeLo = 1286840376U;
  c22_info[113].fileTimeHi = 0U;
  c22_info[113].mFileTimeLo = 0U;
  c22_info[113].mFileTimeHi = 0U;
  c22_info[114].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_guarded_nan.m";
  c22_info[114].name = "eml_is_float_class";
  c22_info[114].dominantType = "char";
  c22_info[114].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_is_float_class.m";
  c22_info[114].fileTimeLo = 1286840382U;
  c22_info[114].fileTimeHi = 0U;
  c22_info[114].mFileTimeLo = 0U;
  c22_info[114].mFileTimeHi = 0U;
  c22_info[115].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!checkcond";
  c22_info[115].name = "mtimes";
  c22_info[115].dominantType = "double";
  c22_info[115].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c22_info[115].fileTimeLo = 1289541292U;
  c22_info[115].fileTimeHi = 0U;
  c22_info[115].mFileTimeLo = 0U;
  c22_info[115].mFileTimeHi = 0U;
  c22_info[116].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!checkcond";
  c22_info[116].name = "eml_warning";
  c22_info[116].dominantType = "char";
  c22_info[116].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_warning.m";
  c22_info[116].fileTimeLo = 1286840402U;
  c22_info[116].fileTimeHi = 0U;
  c22_info[116].mFileTimeLo = 0U;
  c22_info[116].mFileTimeHi = 0U;
  c22_info[117].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!checkcond";
  c22_info[117].name = "isnan";
  c22_info[117].dominantType = "double";
  c22_info[117].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isnan.m";
  c22_info[117].fileTimeLo = 1286840360U;
  c22_info[117].fileTimeHi = 0U;
  c22_info[117].mFileTimeLo = 0U;
  c22_info[117].mFileTimeHi = 0U;
  c22_info[118].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!checkcond";
  c22_info[118].name = "eps";
  c22_info[118].dominantType = "char";
  c22_info[118].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m";
  c22_info[118].fileTimeLo = 1326749596U;
  c22_info[118].fileTimeHi = 0U;
  c22_info[118].mFileTimeLo = 0U;
  c22_info[118].mFileTimeHi = 0U;
  c22_info[119].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!checkcond";
  c22_info[119].name = "eml_flt2str";
  c22_info[119].dominantType = "double";
  c22_info[119].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_flt2str.m";
  c22_info[119].fileTimeLo = 1309472796U;
  c22_info[119].fileTimeHi = 0U;
  c22_info[119].mFileTimeLo = 0U;
  c22_info[119].mFileTimeHi = 0U;
  c22_info[120].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_flt2str.m";
  c22_info[120].name = "char";
  c22_info[120].dominantType = "double";
  c22_info[120].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/char.m";
  c22_info[120].fileTimeLo = 1319751568U;
  c22_info[120].fileTimeHi = 0U;
  c22_info[120].mFileTimeLo = 0U;
  c22_info[120].mFileTimeHi = 0U;
  c22_info[121].context = "";
  c22_info[121].name = "mtimes";
  c22_info[121].dominantType = "double";
  c22_info[121].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c22_info[121].fileTimeLo = 1289541292U;
  c22_info[121].fileTimeHi = 0U;
  c22_info[121].mFileTimeLo = 0U;
  c22_info[121].mFileTimeHi = 0U;
  c22_info[122].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c22_info[122].name = "eml_index_class";
  c22_info[122].dominantType = "";
  c22_info[122].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c22_info[122].fileTimeLo = 1323192178U;
  c22_info[122].fileTimeHi = 0U;
  c22_info[122].mFileTimeLo = 0U;
  c22_info[122].mFileTimeHi = 0U;
  c22_info[123].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c22_info[123].name = "eml_scalar_eg";
  c22_info[123].dominantType = "double";
  c22_info[123].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c22_info[123].fileTimeLo = 1286840396U;
  c22_info[123].fileTimeHi = 0U;
  c22_info[123].mFileTimeLo = 0U;
  c22_info[123].mFileTimeHi = 0U;
  c22_info[124].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c22_info[124].name = "eml_xgemm";
  c22_info[124].dominantType = "char";
  c22_info[124].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m";
  c22_info[124].fileTimeLo = 1299098372U;
  c22_info[124].fileTimeHi = 0U;
  c22_info[124].mFileTimeLo = 0U;
  c22_info[124].mFileTimeHi = 0U;
  c22_info[125].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m";
  c22_info[125].name = "eml_blas_inline";
  c22_info[125].dominantType = "";
  c22_info[125].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_blas_inline.m";
  c22_info[125].fileTimeLo = 1299098368U;
  c22_info[125].fileTimeHi = 0U;
  c22_info[125].mFileTimeLo = 0U;
  c22_info[125].mFileTimeHi = 0U;
  c22_info[126].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m!below_threshold";
  c22_info[126].name = "mtimes";
  c22_info[126].dominantType = "double";
  c22_info[126].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c22_info[126].fileTimeLo = 1289541292U;
  c22_info[126].fileTimeHi = 0U;
  c22_info[126].mFileTimeLo = 0U;
  c22_info[126].mFileTimeHi = 0U;
  c22_info[127].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c22_info[127].name = "eml_index_class";
  c22_info[127].dominantType = "";
  c22_info[127].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c22_info[127].fileTimeLo = 1323192178U;
  c22_info[127].fileTimeHi = 0U;
  c22_info[127].mFileTimeLo = 0U;
  c22_info[127].mFileTimeHi = 0U;
}

static void c22_c_info_helper(c22_ResolvedFunctionInfo c22_info[130])
{
  c22_info[128].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c22_info[128].name = "eml_scalar_eg";
  c22_info[128].dominantType = "double";
  c22_info[128].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c22_info[128].fileTimeLo = 1286840396U;
  c22_info[128].fileTimeHi = 0U;
  c22_info[128].mFileTimeLo = 0U;
  c22_info[128].mFileTimeHi = 0U;
  c22_info[129].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c22_info[129].name = "eml_refblas_xgemm";
  c22_info[129].dominantType = "char";
  c22_info[129].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgemm.m";
  c22_info[129].fileTimeLo = 1299098374U;
  c22_info[129].fileTimeHi = 0U;
  c22_info[129].mFileTimeLo = 0U;
  c22_info[129].mFileTimeHi = 0U;
}

static void c22_inv(SFc22_JointSpaceControlInstanceStruct *chartInstance, real_T
                    c22_x[36], real_T c22_y[36])
{
  int32_T c22_i39;
  real_T c22_b_x[36];
  int32_T c22_i40;
  real_T c22_c_x[36];
  real_T c22_n1x;
  int32_T c22_i41;
  real_T c22_b_y[36];
  real_T c22_n1xinv;
  real_T c22_a;
  real_T c22_b;
  real_T c22_c_y;
  real_T c22_rc;
  real_T c22_d_x;
  boolean_T c22_b_b;
  real_T c22_e_x;
  int32_T c22_i42;
  static char_T c22_cv0[8] = { '%', '%', '%', 'd', '.', '%', 'd', 'e' };

  char_T c22_u[8];
  const mxArray *c22_d_y = NULL;
  real_T c22_b_u;
  const mxArray *c22_e_y = NULL;
  real_T c22_c_u;
  const mxArray *c22_f_y = NULL;
  real_T c22_d_u;
  const mxArray *c22_g_y = NULL;
  char_T c22_str[14];
  int32_T c22_i43;
  char_T c22_b_str[14];
  boolean_T guard1 = FALSE;
  boolean_T guard2 = FALSE;
  boolean_T guard3 = FALSE;
  for (c22_i39 = 0; c22_i39 < 36; c22_i39++) {
    c22_b_x[c22_i39] = c22_x[c22_i39];
  }

  c22_invNxN(chartInstance, c22_b_x, c22_y);
  for (c22_i40 = 0; c22_i40 < 36; c22_i40++) {
    c22_c_x[c22_i40] = c22_x[c22_i40];
  }

  c22_n1x = c22_norm(chartInstance, c22_c_x);
  for (c22_i41 = 0; c22_i41 < 36; c22_i41++) {
    c22_b_y[c22_i41] = c22_y[c22_i41];
  }

  c22_n1xinv = c22_norm(chartInstance, c22_b_y);
  c22_a = c22_n1x;
  c22_b = c22_n1xinv;
  c22_c_y = c22_a * c22_b;
  c22_rc = 1.0 / c22_c_y;
  guard1 = FALSE;
  guard2 = FALSE;
  if (c22_n1x == 0.0) {
    guard2 = TRUE;
  } else if (c22_n1xinv == 0.0) {
    guard2 = TRUE;
  } else if (c22_rc == 0.0) {
    guard1 = TRUE;
  } else {
    c22_d_x = c22_rc;
    c22_b_b = muDoubleScalarIsNaN(c22_d_x);
    guard3 = FALSE;
    if (c22_b_b) {
      guard3 = TRUE;
    } else {
      c22_eps(chartInstance);
      if (c22_rc < 2.2204460492503131E-16) {
        guard3 = TRUE;
      }
    }

    if (guard3 == TRUE) {
      c22_e_x = c22_rc;
      for (c22_i42 = 0; c22_i42 < 8; c22_i42++) {
        c22_u[c22_i42] = c22_cv0[c22_i42];
      }

      c22_d_y = NULL;
      sf_mex_assign(&c22_d_y, sf_mex_create("y", c22_u, 10, 0U, 1U, 0U, 2, 1, 8),
                    FALSE);
      c22_b_u = 14.0;
      c22_e_y = NULL;
      sf_mex_assign(&c22_e_y, sf_mex_create("y", &c22_b_u, 0, 0U, 0U, 0U, 0),
                    FALSE);
      c22_c_u = 6.0;
      c22_f_y = NULL;
      sf_mex_assign(&c22_f_y, sf_mex_create("y", &c22_c_u, 0, 0U, 0U, 0U, 0),
                    FALSE);
      c22_d_u = c22_e_x;
      c22_g_y = NULL;
      sf_mex_assign(&c22_g_y, sf_mex_create("y", &c22_d_u, 0, 0U, 0U, 0U, 0),
                    FALSE);
      c22_d_emlrt_marshallIn(chartInstance, sf_mex_call_debug("sprintf", 1U, 2U,
        14, sf_mex_call_debug("sprintf", 1U, 3U, 14, c22_d_y, 14, c22_e_y, 14,
        c22_f_y), 14, c22_g_y), "sprintf", c22_str);
      for (c22_i43 = 0; c22_i43 < 14; c22_i43++) {
        c22_b_str[c22_i43] = c22_str[c22_i43];
      }

      c22_b_eml_warning(chartInstance, c22_b_str);
    }
  }

  if (guard2 == TRUE) {
    guard1 = TRUE;
  }

  if (guard1 == TRUE) {
    c22_eml_warning(chartInstance);
  }
}

static void c22_invNxN(SFc22_JointSpaceControlInstanceStruct *chartInstance,
  real_T c22_x[36], real_T c22_y[36])
{
  int32_T c22_i44;
  int32_T c22_info;
  int32_T c22_ipiv[6];
  int32_T c22_i45;
  int32_T c22_p[6];
  int32_T c22_k;
  real_T c22_b_k;
  int32_T c22_ipk;
  int32_T c22_a;
  real_T c22_b;
  int32_T c22_b_a;
  real_T c22_b_b;
  int32_T c22_idx;
  real_T c22_flt;
  boolean_T c22_b_p;
  int32_T c22_pipk;
  int32_T c22_c_k;
  int32_T c22_d_k;
  int32_T c22_c;
  int32_T c22_e_k;
  boolean_T c22_overflow;
  int32_T c22_j;
  int32_T c22_b_j;
  int32_T c22_c_a;
  int32_T c22_i46;
  boolean_T c22_b_overflow;
  int32_T c22_i;
  int32_T c22_b_i;
  real_T c22_d_a;
  real_T c22_c_b;
  real_T c22_b_y;
  int32_T c22_i47;
  real_T c22_b_x[36];
  for (c22_i44 = 0; c22_i44 < 36; c22_i44++) {
    c22_y[c22_i44] = 0.0;
  }

  c22_b_eml_matlab_zgetrf(chartInstance, c22_x, c22_ipiv, &c22_info);
  for (c22_i45 = 0; c22_i45 < 6; c22_i45++) {
    c22_p[c22_i45] = 1 + c22_i45;
  }

  for (c22_k = 0; c22_k < 5; c22_k++) {
    c22_b_k = 1.0 + (real_T)c22_k;
    c22_ipk = c22_ipiv[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
      _SFD_INTEGER_CHECK("", c22_b_k), 1, 6, 1, 0) - 1];
    c22_a = c22_ipk;
    c22_b = c22_b_k;
    c22_b_a = c22_a;
    c22_b_b = c22_b;
    c22_idx = c22_b_a;
    c22_flt = c22_b_b;
    c22_b_p = ((real_T)c22_idx > c22_flt);
    if (c22_b_p) {
      c22_pipk = c22_p[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
        _SFD_INTEGER_CHECK("", (real_T)c22_ipk), 1, 6, 1, 0) - 1];
      c22_p[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
        (real_T)c22_ipk), 1, 6, 1, 0) - 1] = c22_p[(int32_T)(real_T)
        _SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", c22_b_k),
        1, 6, 1, 0) - 1];
      c22_p[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
        _SFD_INTEGER_CHECK("", c22_b_k), 1, 6, 1, 0) - 1] = c22_pipk;
    }
  }

  for (c22_c_k = 1; c22_c_k < 7; c22_c_k++) {
    c22_d_k = c22_c_k;
    c22_c = c22_p[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
      (real_T)c22_d_k), 1, 6, 1, 0) - 1];
    c22_y[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
             (real_T)c22_d_k), 1, 6, 1, 0) + 6 * (_SFD_EML_ARRAY_BOUNDS_CHECK("",
             (int32_T)_SFD_INTEGER_CHECK("", (real_T)c22_c), 1, 6, 2, 0) - 1)) -
      1] = 1.0;
    c22_e_k = c22_d_k;
    c22_overflow = FALSE;
    if (c22_overflow) {
      c22_check_forloop_overflow_error(chartInstance, c22_overflow);
    }

    for (c22_j = c22_e_k; c22_j < 7; c22_j++) {
      c22_b_j = c22_j;
      if (c22_y[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
             (real_T)c22_b_j), 1, 6, 1, 0) + 6 * (_SFD_EML_ARRAY_BOUNDS_CHECK("",
             (int32_T)_SFD_INTEGER_CHECK("", (real_T)c22_c), 1, 6, 2, 0) - 1)) -
          1] != 0.0) {
        c22_c_a = c22_b_j;
        c22_i46 = c22_c_a;
        c22_b_overflow = FALSE;
        if (c22_b_overflow) {
          c22_check_forloop_overflow_error(chartInstance, c22_b_overflow);
        }

        for (c22_i = c22_i46 + 1; c22_i < 7; c22_i++) {
          c22_b_i = c22_i;
          c22_d_a = c22_y[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", (real_T)c22_b_j), 1, 6, 1, 0) + 6 *
                           (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", (real_T)c22_c), 1, 6, 2, 0) - 1)) - 1];
          c22_c_b = c22_x[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", (real_T)c22_b_i), 1, 6, 1, 0) + 6 *
                           (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", (real_T)c22_b_j), 1, 6, 2, 0) - 1)) - 1];
          c22_b_y = c22_d_a * c22_c_b;
          c22_y[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                   (real_T)c22_b_i), 1, 6, 1, 0) + 6 *
                 (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                    (real_T)c22_c), 1, 6, 2, 0) - 1)) - 1] = c22_y
            [(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                (real_T)c22_b_i), 1, 6, 1, 0) + 6 * (_SFD_EML_ARRAY_BOUNDS_CHECK
               ("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)c22_c), 1, 6, 2, 0)
               - 1)) - 1] - c22_b_y;
        }
      }
    }
  }

  for (c22_i47 = 0; c22_i47 < 36; c22_i47++) {
    c22_b_x[c22_i47] = c22_x[c22_i47];
  }

  c22_b_eml_xtrsm(chartInstance, c22_b_x, c22_y);
}

static void c22_realmin(SFc22_JointSpaceControlInstanceStruct *chartInstance)
{
}

static void c22_eps(SFc22_JointSpaceControlInstanceStruct *chartInstance)
{
}

static void c22_eml_matlab_zgetrf(SFc22_JointSpaceControlInstanceStruct
  *chartInstance, real_T c22_A[36], real_T c22_b_A[36], int32_T c22_ipiv[6],
  int32_T *c22_info)
{
  int32_T c22_i48;
  for (c22_i48 = 0; c22_i48 < 36; c22_i48++) {
    c22_b_A[c22_i48] = c22_A[c22_i48];
  }

  c22_b_eml_matlab_zgetrf(chartInstance, c22_b_A, c22_ipiv, c22_info);
}

static void c22_check_forloop_overflow_error
  (SFc22_JointSpaceControlInstanceStruct *chartInstance, boolean_T c22_overflow)
{
  int32_T c22_i49;
  static char_T c22_cv1[34] = { 'C', 'o', 'd', 'e', 'r', ':', 't', 'o', 'o', 'l',
    'b', 'o', 'x', ':', 'i', 'n', 't', '_', 'f', 'o', 'r', 'l', 'o', 'o', 'p',
    '_', 'o', 'v', 'e', 'r', 'f', 'l', 'o', 'w' };

  char_T c22_u[34];
  const mxArray *c22_y = NULL;
  int32_T c22_i50;
  static char_T c22_cv2[23] = { 'c', 'o', 'd', 'e', 'r', '.', 'i', 'n', 't', 'e',
    'r', 'n', 'a', 'l', '.', 'i', 'n', 'd', 'e', 'x', 'I', 'n', 't' };

  char_T c22_b_u[23];
  const mxArray *c22_b_y = NULL;
  if (!c22_overflow) {
  } else {
    for (c22_i49 = 0; c22_i49 < 34; c22_i49++) {
      c22_u[c22_i49] = c22_cv1[c22_i49];
    }

    c22_y = NULL;
    sf_mex_assign(&c22_y, sf_mex_create("y", c22_u, 10, 0U, 1U, 0U, 2, 1, 34),
                  FALSE);
    for (c22_i50 = 0; c22_i50 < 23; c22_i50++) {
      c22_b_u[c22_i50] = c22_cv2[c22_i50];
    }

    c22_b_y = NULL;
    sf_mex_assign(&c22_b_y, sf_mex_create("y", c22_b_u, 10, 0U, 1U, 0U, 2, 1, 23),
                  FALSE);
    sf_mex_call_debug("error", 0U, 1U, 14, sf_mex_call_debug("message", 1U, 2U,
      14, c22_y, 14, c22_b_y));
  }
}

static void c22_eml_xger(SFc22_JointSpaceControlInstanceStruct *chartInstance,
  int32_T c22_m, int32_T c22_n, real_T c22_alpha1, int32_T c22_ix0, int32_T
  c22_iy0, real_T c22_A[36], int32_T c22_ia0, real_T c22_b_A[36])
{
  int32_T c22_i51;
  for (c22_i51 = 0; c22_i51 < 36; c22_i51++) {
    c22_b_A[c22_i51] = c22_A[c22_i51];
  }

  c22_b_eml_xger(chartInstance, c22_m, c22_n, c22_alpha1, c22_ix0, c22_iy0,
                 c22_b_A, c22_ia0);
}

static void c22_eml_xtrsm(SFc22_JointSpaceControlInstanceStruct *chartInstance,
  real_T c22_A[36], real_T c22_B[36], real_T c22_b_B[36])
{
  int32_T c22_i52;
  int32_T c22_i53;
  real_T c22_b_A[36];
  for (c22_i52 = 0; c22_i52 < 36; c22_i52++) {
    c22_b_B[c22_i52] = c22_B[c22_i52];
  }

  for (c22_i53 = 0; c22_i53 < 36; c22_i53++) {
    c22_b_A[c22_i53] = c22_A[c22_i53];
  }

  c22_b_eml_xtrsm(chartInstance, c22_b_A, c22_b_B);
}

static real_T c22_norm(SFc22_JointSpaceControlInstanceStruct *chartInstance,
  real_T c22_x[36])
{
  real_T c22_y;
  int32_T c22_j;
  real_T c22_b_j;
  real_T c22_s;
  int32_T c22_i;
  real_T c22_b_i;
  real_T c22_b_x;
  real_T c22_c_x;
  real_T c22_b_y;
  real_T c22_d_x;
  boolean_T c22_b;
  boolean_T exitg1;
  c22_y = 0.0;
  c22_j = 0;
  exitg1 = FALSE;
  while ((exitg1 == FALSE) && (c22_j < 6)) {
    c22_b_j = 1.0 + (real_T)c22_j;
    c22_s = 0.0;
    for (c22_i = 0; c22_i < 6; c22_i++) {
      c22_b_i = 1.0 + (real_T)c22_i;
      c22_b_x = c22_x[((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
        _SFD_INTEGER_CHECK("", c22_b_i), 1, 6, 1, 0) + 6 * ((int32_T)(real_T)
        _SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", c22_b_j),
        1, 6, 2, 0) - 1)) - 1];
      c22_c_x = c22_b_x;
      c22_b_y = muDoubleScalarAbs(c22_c_x);
      c22_s += c22_b_y;
    }

    c22_d_x = c22_s;
    c22_b = muDoubleScalarIsNaN(c22_d_x);
    if (c22_b) {
      c22_y = rtNaN;
      exitg1 = TRUE;
    } else {
      if (c22_s > c22_y) {
        c22_y = c22_s;
      }

      c22_j++;
    }
  }

  return c22_y;
}

static void c22_eml_warning(SFc22_JointSpaceControlInstanceStruct *chartInstance)
{
  int32_T c22_i54;
  static char_T c22_varargin_1[27] = { 'C', 'o', 'd', 'e', 'r', ':', 'M', 'A',
    'T', 'L', 'A', 'B', ':', 's', 'i', 'n', 'g', 'u', 'l', 'a', 'r', 'M', 'a',
    't', 'r', 'i', 'x' };

  char_T c22_u[27];
  const mxArray *c22_y = NULL;
  for (c22_i54 = 0; c22_i54 < 27; c22_i54++) {
    c22_u[c22_i54] = c22_varargin_1[c22_i54];
  }

  c22_y = NULL;
  sf_mex_assign(&c22_y, sf_mex_create("y", c22_u, 10, 0U, 1U, 0U, 2, 1, 27),
                FALSE);
  sf_mex_call_debug("warning", 0U, 1U, 14, sf_mex_call_debug("message", 1U, 1U,
    14, c22_y));
}

static void c22_b_eml_warning(SFc22_JointSpaceControlInstanceStruct
  *chartInstance, char_T c22_varargin_2[14])
{
  int32_T c22_i55;
  static char_T c22_varargin_1[33] = { 'C', 'o', 'd', 'e', 'r', ':', 'M', 'A',
    'T', 'L', 'A', 'B', ':', 'i', 'l', 'l', 'C', 'o', 'n', 'd', 'i', 't', 'i',
    'o', 'n', 'e', 'd', 'M', 'a', 't', 'r', 'i', 'x' };

  char_T c22_u[33];
  const mxArray *c22_y = NULL;
  int32_T c22_i56;
  char_T c22_b_u[14];
  const mxArray *c22_b_y = NULL;
  for (c22_i55 = 0; c22_i55 < 33; c22_i55++) {
    c22_u[c22_i55] = c22_varargin_1[c22_i55];
  }

  c22_y = NULL;
  sf_mex_assign(&c22_y, sf_mex_create("y", c22_u, 10, 0U, 1U, 0U, 2, 1, 33),
                FALSE);
  for (c22_i56 = 0; c22_i56 < 14; c22_i56++) {
    c22_b_u[c22_i56] = c22_varargin_2[c22_i56];
  }

  c22_b_y = NULL;
  sf_mex_assign(&c22_b_y, sf_mex_create("y", c22_b_u, 10, 0U, 1U, 0U, 2, 1, 14),
                FALSE);
  sf_mex_call_debug("warning", 0U, 1U, 14, sf_mex_call_debug("message", 1U, 2U,
    14, c22_y, 14, c22_b_y));
}

static void c22_eml_scalar_eg(SFc22_JointSpaceControlInstanceStruct
  *chartInstance)
{
}

static void c22_d_emlrt_marshallIn(SFc22_JointSpaceControlInstanceStruct
  *chartInstance, const mxArray *c22_sprintf, const char_T *c22_identifier,
  char_T c22_y[14])
{
  emlrtMsgIdentifier c22_thisId;
  c22_thisId.fIdentifier = c22_identifier;
  c22_thisId.fParent = NULL;
  c22_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c22_sprintf), &c22_thisId,
    c22_y);
  sf_mex_destroy(&c22_sprintf);
}

static void c22_e_emlrt_marshallIn(SFc22_JointSpaceControlInstanceStruct
  *chartInstance, const mxArray *c22_u, const emlrtMsgIdentifier *c22_parentId,
  char_T c22_y[14])
{
  char_T c22_cv3[14];
  int32_T c22_i57;
  sf_mex_import(c22_parentId, sf_mex_dup(c22_u), c22_cv3, 1, 10, 0U, 1, 0U, 2, 1,
                14);
  for (c22_i57 = 0; c22_i57 < 14; c22_i57++) {
    c22_y[c22_i57] = c22_cv3[c22_i57];
  }

  sf_mex_destroy(&c22_u);
}

static const mxArray *c22_d_sf_marshallOut(void *chartInstanceVoid, void
  *c22_inData)
{
  const mxArray *c22_mxArrayOutData = NULL;
  int32_T c22_u;
  const mxArray *c22_y = NULL;
  SFc22_JointSpaceControlInstanceStruct *chartInstance;
  chartInstance = (SFc22_JointSpaceControlInstanceStruct *)chartInstanceVoid;
  c22_mxArrayOutData = NULL;
  c22_u = *(int32_T *)c22_inData;
  c22_y = NULL;
  sf_mex_assign(&c22_y, sf_mex_create("y", &c22_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c22_mxArrayOutData, c22_y, FALSE);
  return c22_mxArrayOutData;
}

static int32_T c22_f_emlrt_marshallIn(SFc22_JointSpaceControlInstanceStruct
  *chartInstance, const mxArray *c22_u, const emlrtMsgIdentifier *c22_parentId)
{
  int32_T c22_y;
  int32_T c22_i58;
  sf_mex_import(c22_parentId, sf_mex_dup(c22_u), &c22_i58, 1, 6, 0U, 0, 0U, 0);
  c22_y = c22_i58;
  sf_mex_destroy(&c22_u);
  return c22_y;
}

static void c22_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c22_mxArrayInData, const char_T *c22_varName, void *c22_outData)
{
  const mxArray *c22_b_sfEvent;
  const char_T *c22_identifier;
  emlrtMsgIdentifier c22_thisId;
  int32_T c22_y;
  SFc22_JointSpaceControlInstanceStruct *chartInstance;
  chartInstance = (SFc22_JointSpaceControlInstanceStruct *)chartInstanceVoid;
  c22_b_sfEvent = sf_mex_dup(c22_mxArrayInData);
  c22_identifier = c22_varName;
  c22_thisId.fIdentifier = c22_identifier;
  c22_thisId.fParent = NULL;
  c22_y = c22_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c22_b_sfEvent),
    &c22_thisId);
  sf_mex_destroy(&c22_b_sfEvent);
  *(int32_T *)c22_outData = c22_y;
  sf_mex_destroy(&c22_mxArrayInData);
}

static uint8_T c22_g_emlrt_marshallIn(SFc22_JointSpaceControlInstanceStruct
  *chartInstance, const mxArray *c22_b_is_active_c22_JointSpaceControl, const
  char_T *c22_identifier)
{
  uint8_T c22_y;
  emlrtMsgIdentifier c22_thisId;
  c22_thisId.fIdentifier = c22_identifier;
  c22_thisId.fParent = NULL;
  c22_y = c22_h_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c22_b_is_active_c22_JointSpaceControl), &c22_thisId);
  sf_mex_destroy(&c22_b_is_active_c22_JointSpaceControl);
  return c22_y;
}

static uint8_T c22_h_emlrt_marshallIn(SFc22_JointSpaceControlInstanceStruct
  *chartInstance, const mxArray *c22_u, const emlrtMsgIdentifier *c22_parentId)
{
  uint8_T c22_y;
  uint8_T c22_u0;
  sf_mex_import(c22_parentId, sf_mex_dup(c22_u), &c22_u0, 1, 3, 0U, 0, 0U, 0);
  c22_y = c22_u0;
  sf_mex_destroy(&c22_u);
  return c22_y;
}

static void c22_b_eml_matlab_zgetrf(SFc22_JointSpaceControlInstanceStruct
  *chartInstance, real_T c22_A[36], int32_T c22_ipiv[6], int32_T *c22_info)
{
  int32_T c22_i59;
  int32_T c22_j;
  int32_T c22_b_j;
  int32_T c22_a;
  int32_T c22_jm1;
  int32_T c22_b;
  int32_T c22_mmj;
  int32_T c22_b_a;
  int32_T c22_c;
  int32_T c22_b_b;
  int32_T c22_jj;
  int32_T c22_c_a;
  int32_T c22_jp1j;
  int32_T c22_d_a;
  int32_T c22_b_c;
  int32_T c22_n;
  int32_T c22_ix0;
  int32_T c22_b_n;
  int32_T c22_b_ix0;
  int32_T c22_c_n;
  int32_T c22_c_ix0;
  int32_T c22_idxmax;
  int32_T c22_ix;
  real_T c22_x;
  real_T c22_b_x;
  real_T c22_c_x;
  real_T c22_y;
  real_T c22_d_x;
  real_T c22_e_x;
  real_T c22_b_y;
  real_T c22_smax;
  int32_T c22_d_n;
  int32_T c22_c_b;
  int32_T c22_d_b;
  boolean_T c22_overflow;
  int32_T c22_k;
  int32_T c22_b_k;
  int32_T c22_e_a;
  real_T c22_f_x;
  real_T c22_g_x;
  real_T c22_h_x;
  real_T c22_c_y;
  real_T c22_i_x;
  real_T c22_j_x;
  real_T c22_d_y;
  real_T c22_s;
  int32_T c22_f_a;
  int32_T c22_jpiv_offset;
  int32_T c22_g_a;
  int32_T c22_e_b;
  int32_T c22_jpiv;
  int32_T c22_h_a;
  int32_T c22_f_b;
  int32_T c22_c_c;
  int32_T c22_g_b;
  int32_T c22_jrow;
  int32_T c22_i_a;
  int32_T c22_h_b;
  int32_T c22_jprow;
  int32_T c22_d_ix0;
  int32_T c22_iy0;
  int32_T c22_e_ix0;
  int32_T c22_b_iy0;
  int32_T c22_f_ix0;
  int32_T c22_c_iy0;
  int32_T c22_b_ix;
  int32_T c22_iy;
  int32_T c22_c_k;
  real_T c22_temp;
  int32_T c22_j_a;
  int32_T c22_k_a;
  int32_T c22_b_jp1j;
  int32_T c22_l_a;
  int32_T c22_d_c;
  int32_T c22_m_a;
  int32_T c22_i_b;
  int32_T c22_i60;
  int32_T c22_n_a;
  int32_T c22_j_b;
  int32_T c22_o_a;
  int32_T c22_k_b;
  boolean_T c22_b_overflow;
  int32_T c22_i;
  int32_T c22_b_i;
  real_T c22_k_x;
  real_T c22_e_y;
  real_T c22_z;
  int32_T c22_l_b;
  int32_T c22_e_c;
  int32_T c22_p_a;
  int32_T c22_f_c;
  int32_T c22_q_a;
  int32_T c22_g_c;
  int32_T c22_m;
  int32_T c22_e_n;
  int32_T c22_g_ix0;
  int32_T c22_d_iy0;
  int32_T c22_ia0;
  real_T c22_d1;
  c22_realmin(chartInstance);
  c22_eps(chartInstance);
  for (c22_i59 = 0; c22_i59 < 6; c22_i59++) {
    c22_ipiv[c22_i59] = 1 + c22_i59;
  }

  *c22_info = 0;
  for (c22_j = 1; c22_j < 6; c22_j++) {
    c22_b_j = c22_j;
    c22_a = c22_b_j - 1;
    c22_jm1 = c22_a;
    c22_b = c22_b_j;
    c22_mmj = 6 - c22_b;
    c22_b_a = c22_jm1;
    c22_c = c22_b_a * 7;
    c22_b_b = c22_c + 1;
    c22_jj = c22_b_b;
    c22_c_a = c22_jj + 1;
    c22_jp1j = c22_c_a;
    c22_d_a = c22_mmj;
    c22_b_c = c22_d_a;
    c22_n = c22_b_c + 1;
    c22_ix0 = c22_jj;
    c22_b_n = c22_n;
    c22_b_ix0 = c22_ix0;
    c22_c_n = c22_b_n;
    c22_c_ix0 = c22_b_ix0;
    if (c22_c_n < 1) {
      c22_idxmax = 0;
    } else {
      c22_idxmax = 1;
      if (c22_c_n > 1) {
        c22_ix = c22_c_ix0;
        c22_x = c22_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c22_ix), 1, 36, 1, 0) - 1];
        c22_b_x = c22_x;
        c22_c_x = c22_b_x;
        c22_y = muDoubleScalarAbs(c22_c_x);
        c22_d_x = 0.0;
        c22_e_x = c22_d_x;
        c22_b_y = muDoubleScalarAbs(c22_e_x);
        c22_smax = c22_y + c22_b_y;
        c22_d_n = c22_c_n;
        c22_c_b = c22_d_n;
        c22_d_b = c22_c_b;
        if (2 > c22_d_b) {
          c22_overflow = FALSE;
        } else {
          c22_overflow = (c22_d_b > 2147483646);
        }

        if (c22_overflow) {
          c22_check_forloop_overflow_error(chartInstance, c22_overflow);
        }

        for (c22_k = 2; c22_k <= c22_d_n; c22_k++) {
          c22_b_k = c22_k;
          c22_e_a = c22_ix + 1;
          c22_ix = c22_e_a;
          c22_f_x = c22_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", (real_T)c22_ix), 1, 36, 1, 0) - 1];
          c22_g_x = c22_f_x;
          c22_h_x = c22_g_x;
          c22_c_y = muDoubleScalarAbs(c22_h_x);
          c22_i_x = 0.0;
          c22_j_x = c22_i_x;
          c22_d_y = muDoubleScalarAbs(c22_j_x);
          c22_s = c22_c_y + c22_d_y;
          if (c22_s > c22_smax) {
            c22_idxmax = c22_b_k;
            c22_smax = c22_s;
          }
        }
      }
    }

    c22_f_a = c22_idxmax - 1;
    c22_jpiv_offset = c22_f_a;
    c22_g_a = c22_jj;
    c22_e_b = c22_jpiv_offset;
    c22_jpiv = c22_g_a + c22_e_b;
    if (c22_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (real_T)c22_jpiv), 1, 36, 1, 0) - 1] != 0.0) {
      if (c22_jpiv_offset != 0) {
        c22_h_a = c22_b_j;
        c22_f_b = c22_jpiv_offset;
        c22_c_c = c22_h_a + c22_f_b;
        c22_ipiv[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (real_T)c22_b_j), 1, 6, 1, 0) - 1] = c22_c_c;
        c22_g_b = c22_jm1 + 1;
        c22_jrow = c22_g_b;
        c22_i_a = c22_jrow;
        c22_h_b = c22_jpiv_offset;
        c22_jprow = c22_i_a + c22_h_b;
        c22_d_ix0 = c22_jrow;
        c22_iy0 = c22_jprow;
        c22_e_ix0 = c22_d_ix0;
        c22_b_iy0 = c22_iy0;
        c22_f_ix0 = c22_e_ix0;
        c22_c_iy0 = c22_b_iy0;
        c22_b_ix = c22_f_ix0;
        c22_iy = c22_c_iy0;
        for (c22_c_k = 1; c22_c_k < 7; c22_c_k++) {
          c22_temp = c22_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", (real_T)c22_b_ix), 1, 36, 1, 0) - 1];
          c22_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c22_b_ix), 1, 36, 1, 0) - 1] =
            c22_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c22_iy), 1, 36, 1, 0) - 1];
          c22_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c22_iy), 1, 36, 1, 0) - 1] = c22_temp;
          c22_j_a = c22_b_ix + 6;
          c22_b_ix = c22_j_a;
          c22_k_a = c22_iy + 6;
          c22_iy = c22_k_a;
        }
      }

      c22_b_jp1j = c22_jp1j;
      c22_l_a = c22_mmj;
      c22_d_c = c22_l_a;
      c22_m_a = c22_jp1j;
      c22_i_b = c22_d_c - 1;
      c22_i60 = c22_m_a + c22_i_b;
      c22_n_a = c22_b_jp1j;
      c22_j_b = c22_i60;
      c22_o_a = c22_n_a;
      c22_k_b = c22_j_b;
      if (c22_o_a > c22_k_b) {
        c22_b_overflow = FALSE;
      } else {
        c22_b_overflow = (c22_k_b > 2147483646);
      }

      if (c22_b_overflow) {
        c22_check_forloop_overflow_error(chartInstance, c22_b_overflow);
      }

      for (c22_i = c22_b_jp1j; c22_i <= c22_i60; c22_i++) {
        c22_b_i = c22_i;
        c22_k_x = c22_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c22_b_i), 1, 36, 1, 0) - 1];
        c22_e_y = c22_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c22_jj), 1, 36, 1, 0) - 1];
        c22_z = c22_k_x / c22_e_y;
        c22_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (real_T)c22_b_i), 1, 36, 1, 0) - 1] = c22_z;
      }
    } else {
      *c22_info = c22_b_j;
    }

    c22_l_b = c22_b_j;
    c22_e_c = 6 - c22_l_b;
    c22_p_a = c22_jj;
    c22_f_c = c22_p_a;
    c22_q_a = c22_jj;
    c22_g_c = c22_q_a;
    c22_m = c22_mmj;
    c22_e_n = c22_e_c;
    c22_g_ix0 = c22_jp1j;
    c22_d_iy0 = c22_f_c + 6;
    c22_ia0 = c22_g_c + 7;
    c22_d1 = -1.0;
    c22_b_eml_xger(chartInstance, c22_m, c22_e_n, c22_d1, c22_g_ix0, c22_d_iy0,
                   c22_A, c22_ia0);
  }

  if (*c22_info == 0) {
    if (!(c22_A[35] != 0.0)) {
      *c22_info = 6;
    }
  }
}

static void c22_b_eml_xger(SFc22_JointSpaceControlInstanceStruct *chartInstance,
  int32_T c22_m, int32_T c22_n, real_T c22_alpha1, int32_T c22_ix0, int32_T
  c22_iy0, real_T c22_A[36], int32_T c22_ia0)
{
  int32_T c22_b_m;
  int32_T c22_b_n;
  real_T c22_b_alpha1;
  int32_T c22_b_ix0;
  int32_T c22_b_iy0;
  int32_T c22_b_ia0;
  int32_T c22_c_m;
  int32_T c22_c_n;
  real_T c22_c_alpha1;
  int32_T c22_c_ix0;
  int32_T c22_c_iy0;
  int32_T c22_c_ia0;
  int32_T c22_d_m;
  int32_T c22_d_n;
  real_T c22_d_alpha1;
  int32_T c22_d_ix0;
  int32_T c22_d_iy0;
  int32_T c22_d_ia0;
  int32_T c22_ixstart;
  int32_T c22_a;
  int32_T c22_jA;
  int32_T c22_jy;
  int32_T c22_e_n;
  int32_T c22_b;
  int32_T c22_b_b;
  boolean_T c22_overflow;
  int32_T c22_j;
  real_T c22_yjy;
  real_T c22_temp;
  int32_T c22_ix;
  int32_T c22_c_b;
  int32_T c22_i61;
  int32_T c22_b_a;
  int32_T c22_d_b;
  int32_T c22_i62;
  int32_T c22_c_a;
  int32_T c22_e_b;
  int32_T c22_d_a;
  int32_T c22_f_b;
  boolean_T c22_b_overflow;
  int32_T c22_ijA;
  int32_T c22_b_ijA;
  int32_T c22_e_a;
  int32_T c22_f_a;
  int32_T c22_g_a;
  c22_b_m = c22_m;
  c22_b_n = c22_n;
  c22_b_alpha1 = c22_alpha1;
  c22_b_ix0 = c22_ix0;
  c22_b_iy0 = c22_iy0;
  c22_b_ia0 = c22_ia0;
  c22_c_m = c22_b_m;
  c22_c_n = c22_b_n;
  c22_c_alpha1 = c22_b_alpha1;
  c22_c_ix0 = c22_b_ix0;
  c22_c_iy0 = c22_b_iy0;
  c22_c_ia0 = c22_b_ia0;
  c22_d_m = c22_c_m;
  c22_d_n = c22_c_n;
  c22_d_alpha1 = c22_c_alpha1;
  c22_d_ix0 = c22_c_ix0;
  c22_d_iy0 = c22_c_iy0;
  c22_d_ia0 = c22_c_ia0;
  if (c22_d_alpha1 == 0.0) {
  } else {
    c22_ixstart = c22_d_ix0;
    c22_a = c22_d_ia0 - 1;
    c22_jA = c22_a;
    c22_jy = c22_d_iy0;
    c22_e_n = c22_d_n;
    c22_b = c22_e_n;
    c22_b_b = c22_b;
    if (1 > c22_b_b) {
      c22_overflow = FALSE;
    } else {
      c22_overflow = (c22_b_b > 2147483646);
    }

    if (c22_overflow) {
      c22_check_forloop_overflow_error(chartInstance, c22_overflow);
    }

    for (c22_j = 1; c22_j <= c22_e_n; c22_j++) {
      c22_yjy = c22_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
        _SFD_INTEGER_CHECK("", (real_T)c22_jy), 1, 36, 1, 0) - 1];
      if (c22_yjy != 0.0) {
        c22_temp = c22_yjy * c22_d_alpha1;
        c22_ix = c22_ixstart;
        c22_c_b = c22_jA + 1;
        c22_i61 = c22_c_b;
        c22_b_a = c22_d_m;
        c22_d_b = c22_jA;
        c22_i62 = c22_b_a + c22_d_b;
        c22_c_a = c22_i61;
        c22_e_b = c22_i62;
        c22_d_a = c22_c_a;
        c22_f_b = c22_e_b;
        if (c22_d_a > c22_f_b) {
          c22_b_overflow = FALSE;
        } else {
          c22_b_overflow = (c22_f_b > 2147483646);
        }

        if (c22_b_overflow) {
          c22_check_forloop_overflow_error(chartInstance, c22_b_overflow);
        }

        for (c22_ijA = c22_i61; c22_ijA <= c22_i62; c22_ijA++) {
          c22_b_ijA = c22_ijA;
          c22_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c22_b_ijA), 1, 36, 1, 0) - 1] =
            c22_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c22_b_ijA), 1, 36, 1, 0) - 1] +
            c22_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c22_ix), 1, 36, 1, 0) - 1] * c22_temp;
          c22_e_a = c22_ix + 1;
          c22_ix = c22_e_a;
        }
      }

      c22_f_a = c22_jy + 6;
      c22_jy = c22_f_a;
      c22_g_a = c22_jA + 6;
      c22_jA = c22_g_a;
    }
  }
}

static void c22_b_eml_xtrsm(SFc22_JointSpaceControlInstanceStruct *chartInstance,
  real_T c22_A[36], real_T c22_B[36])
{
  int32_T c22_j;
  int32_T c22_b_j;
  int32_T c22_a;
  int32_T c22_c;
  int32_T c22_b;
  int32_T c22_b_c;
  int32_T c22_b_b;
  int32_T c22_jBcol;
  int32_T c22_k;
  int32_T c22_b_k;
  int32_T c22_b_a;
  int32_T c22_c_c;
  int32_T c22_c_b;
  int32_T c22_d_c;
  int32_T c22_d_b;
  int32_T c22_kAcol;
  int32_T c22_c_a;
  int32_T c22_e_b;
  int32_T c22_e_c;
  int32_T c22_d_a;
  int32_T c22_f_b;
  int32_T c22_f_c;
  int32_T c22_e_a;
  int32_T c22_g_b;
  int32_T c22_g_c;
  int32_T c22_f_a;
  int32_T c22_h_b;
  int32_T c22_h_c;
  real_T c22_x;
  real_T c22_y;
  real_T c22_z;
  int32_T c22_g_a;
  int32_T c22_i63;
  int32_T c22_i_b;
  int32_T c22_j_b;
  boolean_T c22_overflow;
  int32_T c22_i;
  int32_T c22_b_i;
  int32_T c22_h_a;
  int32_T c22_k_b;
  int32_T c22_i_c;
  int32_T c22_i_a;
  int32_T c22_l_b;
  int32_T c22_j_c;
  int32_T c22_j_a;
  int32_T c22_m_b;
  int32_T c22_k_c;
  int32_T c22_k_a;
  int32_T c22_n_b;
  int32_T c22_l_c;
  for (c22_j = 1; c22_j < 7; c22_j++) {
    c22_b_j = c22_j;
    c22_a = c22_b_j;
    c22_c = c22_a;
    c22_b = c22_c - 1;
    c22_b_c = 6 * c22_b;
    c22_b_b = c22_b_c;
    c22_jBcol = c22_b_b;
    for (c22_k = 6; c22_k > 0; c22_k--) {
      c22_b_k = c22_k;
      c22_b_a = c22_b_k;
      c22_c_c = c22_b_a;
      c22_c_b = c22_c_c - 1;
      c22_d_c = 6 * c22_c_b;
      c22_d_b = c22_d_c;
      c22_kAcol = c22_d_b;
      c22_c_a = c22_b_k;
      c22_e_b = c22_jBcol;
      c22_e_c = c22_c_a + c22_e_b;
      if (c22_B[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c22_e_c), 1, 36, 1, 0) - 1] != 0.0) {
        c22_d_a = c22_b_k;
        c22_f_b = c22_jBcol;
        c22_f_c = c22_d_a + c22_f_b;
        c22_e_a = c22_b_k;
        c22_g_b = c22_jBcol;
        c22_g_c = c22_e_a + c22_g_b;
        c22_f_a = c22_b_k;
        c22_h_b = c22_kAcol;
        c22_h_c = c22_f_a + c22_h_b;
        c22_x = c22_B[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c22_g_c), 1, 36, 1, 0) - 1];
        c22_y = c22_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c22_h_c), 1, 36, 1, 0) - 1];
        c22_z = c22_x / c22_y;
        c22_B[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (real_T)c22_f_c), 1, 36, 1, 0) - 1] = c22_z;
        c22_g_a = c22_b_k - 1;
        c22_i63 = c22_g_a;
        c22_i_b = c22_i63;
        c22_j_b = c22_i_b;
        if (1 > c22_j_b) {
          c22_overflow = FALSE;
        } else {
          c22_overflow = (c22_j_b > 2147483646);
        }

        if (c22_overflow) {
          c22_check_forloop_overflow_error(chartInstance, c22_overflow);
        }

        for (c22_i = 1; c22_i <= c22_i63; c22_i++) {
          c22_b_i = c22_i;
          c22_h_a = c22_b_i;
          c22_k_b = c22_jBcol;
          c22_i_c = c22_h_a + c22_k_b;
          c22_i_a = c22_b_i;
          c22_l_b = c22_jBcol;
          c22_j_c = c22_i_a + c22_l_b;
          c22_j_a = c22_b_k;
          c22_m_b = c22_jBcol;
          c22_k_c = c22_j_a + c22_m_b;
          c22_k_a = c22_b_i;
          c22_n_b = c22_kAcol;
          c22_l_c = c22_k_a + c22_n_b;
          c22_B[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c22_i_c), 1, 36, 1, 0) - 1] =
            c22_B[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c22_j_c), 1, 36, 1, 0) - 1] -
            c22_B[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c22_k_c), 1, 36, 1, 0) - 1] *
            c22_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c22_l_c), 1, 36, 1, 0) - 1];
        }
      }
    }
  }
}

static void init_dsm_address_info(SFc22_JointSpaceControlInstanceStruct
  *chartInstance)
{
}

/* SFunction Glue Code */
#ifdef utFree
#undef utFree
#endif

#ifdef utMalloc
#undef utMalloc
#endif

#ifdef __cplusplus

extern "C" void *utMalloc(size_t size);
extern "C" void utFree(void*);

#else

extern void *utMalloc(size_t size);
extern void utFree(void*);

#endif

void sf_c22_JointSpaceControl_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(2396601831U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(502047863U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(593859288U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3856566254U);
}

mxArray *sf_c22_JointSpaceControl_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("6J92kSNwndO5cn6LgrzZiH");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,4,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(6);
      pr[1] = (double)(6);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(6);
      pr[1] = (double)(6);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(6);
      pr[1] = (double)(1);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(6);
      pr[1] = (double)(1);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(6);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c22_JointSpaceControl_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

static const mxArray *sf_get_sim_state_info_c22_JointSpaceControl(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x2'type','srcId','name','auxInfo'{{M[1],M[14],T\"ddq\",},{M[8],M[0],T\"is_active_c22_JointSpaceControl\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 2, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c22_JointSpaceControl_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc22_JointSpaceControlInstanceStruct *chartInstance;
    chartInstance = (SFc22_JointSpaceControlInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _JointSpaceControlMachineNumber_,
           22,
           1,
           1,
           5,
           0,
           0,
           0,
           0,
           0,
           &(chartInstance->chartNumber),
           &(chartInstance->instanceNumber),
           ssGetPath(S),
           (void *)S);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          init_script_number_translation(_JointSpaceControlMachineNumber_,
            chartInstance->chartNumber);
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_JointSpaceControlMachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _JointSpaceControlMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"J_a");
          _SFD_SET_DATA_PROPS(1,1,1,0,"dJ_a");
          _SFD_SET_DATA_PROPS(2,1,1,0,"ddX");
          _SFD_SET_DATA_PROPS(3,1,1,0,"dq");
          _SFD_SET_DATA_PROPS(4,2,0,1,"ddq");
          _SFD_STATE_INFO(0,0,2);
          _SFD_CH_SUBSTATE_COUNT(0);
          _SFD_CH_SUBSTATE_DECOMP(0);
        }

        _SFD_CV_INIT_CHART(0,0,0,0);

        {
          _SFD_CV_INIT_STATE(0,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);

        /* Initialization of MATLAB Function Model Coverage */
        _SFD_CV_INIT_EML(0,1,1,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,225);
        _SFD_TRANS_COV_WTS(0,0,0,1,0);
        if (chartAlreadyPresent==0) {
          _SFD_TRANS_COV_MAPS(0,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              1,NULL,NULL,
                              0,NULL,NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 6;
          dimVector[1]= 6;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c22_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 6;
          dimVector[1]= 6;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c22_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 6;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c22_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 6;
          _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c22_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 6;
          _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c22_sf_marshallOut,(MexInFcnForType)
            c22_sf_marshallIn);
        }

        {
          real_T (*c22_J_a)[36];
          real_T (*c22_dJ_a)[36];
          real_T (*c22_ddX)[6];
          real_T (*c22_dq)[6];
          real_T (*c22_ddq)[6];
          c22_ddq = (real_T (*)[6])ssGetOutputPortSignal(chartInstance->S, 1);
          c22_dq = (real_T (*)[6])ssGetInputPortSignal(chartInstance->S, 3);
          c22_ddX = (real_T (*)[6])ssGetInputPortSignal(chartInstance->S, 2);
          c22_dJ_a = (real_T (*)[36])ssGetInputPortSignal(chartInstance->S, 1);
          c22_J_a = (real_T (*)[36])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c22_J_a);
          _SFD_SET_DATA_VALUE_PTR(1U, *c22_dJ_a);
          _SFD_SET_DATA_VALUE_PTR(2U, *c22_ddX);
          _SFD_SET_DATA_VALUE_PTR(3U, *c22_dq);
          _SFD_SET_DATA_VALUE_PTR(4U, *c22_ddq);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _JointSpaceControlMachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "iiQfQmGrrx4DFynkmkjH3G";
}

static void sf_opaque_initialize_c22_JointSpaceControl(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc22_JointSpaceControlInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c22_JointSpaceControl((SFc22_JointSpaceControlInstanceStruct*)
    chartInstanceVar);
  initialize_c22_JointSpaceControl((SFc22_JointSpaceControlInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c22_JointSpaceControl(void *chartInstanceVar)
{
  enable_c22_JointSpaceControl((SFc22_JointSpaceControlInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_disable_c22_JointSpaceControl(void *chartInstanceVar)
{
  disable_c22_JointSpaceControl((SFc22_JointSpaceControlInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c22_JointSpaceControl(void *chartInstanceVar)
{
  sf_c22_JointSpaceControl((SFc22_JointSpaceControlInstanceStruct*)
    chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c22_JointSpaceControl(SimStruct*
  S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c22_JointSpaceControl
    ((SFc22_JointSpaceControlInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c22_JointSpaceControl();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_raw2high'.\n");
  }

  return plhs[0];
}

extern void sf_internal_set_sim_state_c22_JointSpaceControl(SimStruct* S, const
  mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c22_JointSpaceControl();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c22_JointSpaceControl((SFc22_JointSpaceControlInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c22_JointSpaceControl(SimStruct* S)
{
  return sf_internal_get_sim_state_c22_JointSpaceControl(S);
}

static void sf_opaque_set_sim_state_c22_JointSpaceControl(SimStruct* S, const
  mxArray *st)
{
  sf_internal_set_sim_state_c22_JointSpaceControl(S, st);
}

static void sf_opaque_terminate_c22_JointSpaceControl(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc22_JointSpaceControlInstanceStruct*) chartInstanceVar)
      ->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_JointSpaceControl_optimization_info();
    }

    finalize_c22_JointSpaceControl((SFc22_JointSpaceControlInstanceStruct*)
      chartInstanceVar);
    utFree((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc22_JointSpaceControl((SFc22_JointSpaceControlInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c22_JointSpaceControl(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c22_JointSpaceControl
      ((SFc22_JointSpaceControlInstanceStruct*)(((ChartInfoStruct *)
         ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c22_JointSpaceControl(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_JointSpaceControl_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,sf_get_instance_specialization(),infoStruct,
      22);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,sf_get_instance_specialization(),
                infoStruct,22,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,
      sf_get_instance_specialization(),infoStruct,22,
      "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(S,sf_get_instance_specialization(),infoStruct,22);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,22,4);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,22,1);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=1; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 4; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,22);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(1657249955U));
  ssSetChecksum1(S,(2168194104U));
  ssSetChecksum2(S,(808641353U));
  ssSetChecksum3(S,(1248625489U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c22_JointSpaceControl(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c22_JointSpaceControl(SimStruct *S)
{
  SFc22_JointSpaceControlInstanceStruct *chartInstance;
  chartInstance = (SFc22_JointSpaceControlInstanceStruct *)utMalloc(sizeof
    (SFc22_JointSpaceControlInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc22_JointSpaceControlInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c22_JointSpaceControl;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c22_JointSpaceControl;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c22_JointSpaceControl;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c22_JointSpaceControl;
  chartInstance->chartInfo.disableChart =
    sf_opaque_disable_c22_JointSpaceControl;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c22_JointSpaceControl;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c22_JointSpaceControl;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c22_JointSpaceControl;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c22_JointSpaceControl;
  chartInstance->chartInfo.mdlStart = mdlStart_c22_JointSpaceControl;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c22_JointSpaceControl;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->S = S;
  ssSetUserData(S,(void *)(&(chartInstance->chartInfo)));/* register the chart instance with simstruct */
  init_dsm_address_info(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  sf_opaque_init_subchart_simstructs(chartInstance->chartInfo.chartInstance);
  chart_debug_initialization(S,1);
}

void c22_JointSpaceControl_method_dispatcher(SimStruct *S, int_T method, void
  *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c22_JointSpaceControl(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c22_JointSpaceControl(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c22_JointSpaceControl(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c22_JointSpaceControl_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
