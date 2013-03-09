#ifndef VIENNACL_LINALG_KERNELS_MATRIX_SOLVE_COL_COL_SOURCE_HPP_
#define VIENNACL_LINALG_KERNELS_MATRIX_SOLVE_COL_COL_SOURCE_HPP_
//Automatically generated file from auxiliary-directory, do not edit manually!
/** @file matrix_solve_col_col_source.h
 *  @brief OpenCL kernel source file, generated automatically from scripts in auxiliary/. */
namespace viennacl
{
 namespace linalg
 {
  namespace kernels
  {
const char * const matrix_solve_col_col_align1_trans_upper_solve = 
"// file automatically generated - do not edit!\n"
"// inplace solve A^T \\ B\n"
"// matrix layouts: A...col_major, B...col_major\n"
"__kernel void trans_upper_solve(\n"
"          __global const float * A,\n"
"          unsigned int A_start1, unsigned int A_start2,\n"
"          unsigned int A_inc1,   unsigned int A_inc2,\n"
"          unsigned int A_size1,  unsigned int A_size2,\n"
"          unsigned int A_internal_size1, unsigned int A_internal_size2,\n"
"          __global float * B,\n"
"          unsigned int B_start1, unsigned int B_start2,\n"
"          unsigned int B_inc1,   unsigned int B_inc2,\n"
"          unsigned int B_size1,  unsigned int B_size2,\n"
"          unsigned int B_internal_size1, unsigned int B_internal_size2)\n"
"{ \n"
"  float temp; \n"
"  for (unsigned int row_cnt = 0; row_cnt < A_size1; ++row_cnt) \n"
"  { \n"
"    unsigned int row = A_size1 - 1 - row_cnt;\n"
"    barrier(CLK_GLOBAL_MEM_FENCE); \n"
"    if (get_local_id(0) == 0) \n"
"      B[(row * B_inc1 + B_start1) + (get_group_id(0) * B_inc2 + B_start2) * B_internal_size1] /= A[(row * A_inc1 + A_start1) + (row * A_inc2 + A_start2)*A_internal_size1];\n"
"    barrier(CLK_GLOBAL_MEM_FENCE); \n"
"    temp = B[(row * B_inc1 + B_start1) + (get_group_id(0) * B_inc2 + B_start2) * B_internal_size1]; \n"
"    //eliminate column of op(A) with index 'row' in parallel: \n"
"    for  (unsigned int elim = get_local_id(0); elim < row; elim += get_local_size(0)) \n"
"      B[(elim * B_inc1 + B_start1) + (get_group_id(0) * B_inc2 + B_start2) * B_internal_size1] -= temp * A[(row * A_inc1 + A_start1) + (elim * A_inc2 + A_start2) * A_internal_size1];\n"
"   }\n"
"}\n"
; //matrix_solve_col_col_align1_trans_upper_solve

const char * const matrix_solve_col_col_align1_upper_trans_solve = 
"// file automatically generated - do not edit!\n"
"// inplace solve A \\ B^T\n"
"// matrix layouts: A...col_major, B...col_major\n"
"__kernel void upper_trans_solve(\n"
"          __global const float * A,\n"
"          unsigned int A_start1, unsigned int A_start2,\n"
"          unsigned int A_inc1,   unsigned int A_inc2,\n"
"          unsigned int A_size1,  unsigned int A_size2,\n"
"          unsigned int A_internal_size1, unsigned int A_internal_size2,\n"
"          __global float * B,\n"
"          unsigned int B_start1, unsigned int B_start2,\n"
"          unsigned int B_inc1,   unsigned int B_inc2,\n"
"          unsigned int B_size1,  unsigned int B_size2,\n"
"          unsigned int B_internal_size1, unsigned int B_internal_size2)\n"
"{ \n"
"  float temp; \n"
"  for (unsigned int row_cnt = 0; row_cnt < A_size1; ++row_cnt) \n"
"  { \n"
"    unsigned int row = A_size1 - 1 - row_cnt;\n"
"    barrier(CLK_GLOBAL_MEM_FENCE); \n"
"    if (get_local_id(0) == 0) \n"
"      B[(get_group_id(0) * B_inc1 + B_start1) + (row * B_inc2 + B_start2) * B_internal_size1] /= A[(row * A_inc1 + A_start1) + (row * A_inc2 + A_start2)*A_internal_size1];\n"
"    barrier(CLK_GLOBAL_MEM_FENCE); \n"
"    temp = B[(get_group_id(0) * B_inc1 + B_start1) + (row * B_inc2 + B_start2) * B_internal_size1]; \n"
"    //eliminate column of op(A) with index 'row' in parallel: \n"
"    for  (unsigned int elim = get_local_id(0); elim < row; elim += get_local_size(0)) \n"
"      B[(get_group_id(0) * B_inc1 + B_start1) + (elim * B_inc2 + B_start2) * B_internal_size1] -= temp * A[(elim * A_inc1 + A_start1) + (row * A_inc2 + A_start2) * A_internal_size1];\n"
"   }\n"
"}\n"
; //matrix_solve_col_col_align1_upper_trans_solve

const char * const matrix_solve_col_col_align1_unit_lower_trans_solve = 
"// file automatically generated - do not edit!\n"
"// inplace solve A \\ B^T\n"
"// matrix layouts: A...col_major, B...col_major\n"
"__kernel void unit_lower_trans_solve(\n"
"          __global const float * A,\n"
"          unsigned int A_start1, unsigned int A_start2,\n"
"          unsigned int A_inc1,   unsigned int A_inc2,\n"
"          unsigned int A_size1,  unsigned int A_size2,\n"
"          unsigned int A_internal_size1, unsigned int A_internal_size2,\n"
"          __global float * B,\n"
"          unsigned int B_start1, unsigned int B_start2,\n"
"          unsigned int B_inc1,   unsigned int B_inc2,\n"
"          unsigned int B_size1,  unsigned int B_size2,\n"
"          unsigned int B_internal_size1, unsigned int B_internal_size2)\n"
"{ \n"
"  float temp; \n"
"  for (unsigned int row = 0; row < A_size1; ++row) \n"
"  { \n"
"    barrier(CLK_GLOBAL_MEM_FENCE); \n"
"    temp = B[(get_group_id(0) * B_inc1 + B_start1) + (row * B_inc2 + B_start2) * B_internal_size1]; \n"
"    //eliminate column of op(A) with index 'row' in parallel: \n"
"    for  (unsigned int elim = row + get_local_id(0) + 1; elim < A_size1; elim += get_local_size(0)) \n"
"      B[(get_group_id(0) * B_inc1 + B_start1) + (elim * B_inc2 + B_start2) * B_internal_size1] -= temp * A[(elim * A_inc1 + A_start1) + (row * A_inc2 + A_start2) * A_internal_size1];\n"
"   }\n"
"}\n"
; //matrix_solve_col_col_align1_unit_lower_trans_solve

const char * const matrix_solve_col_col_align1_trans_unit_upper_trans_solve = 
"// file automatically generated - do not edit!\n"
"// inplace solve A^T \\ B^T\n"
"// matrix layouts: A...col_major, B...col_major\n"
"__kernel void trans_unit_upper_trans_solve(\n"
"          __global const float * A,\n"
"          unsigned int A_start1, unsigned int A_start2,\n"
"          unsigned int A_inc1,   unsigned int A_inc2,\n"
"          unsigned int A_size1,  unsigned int A_size2,\n"
"          unsigned int A_internal_size1, unsigned int A_internal_size2,\n"
"          __global float * B,\n"
"          unsigned int B_start1, unsigned int B_start2,\n"
"          unsigned int B_inc1,   unsigned int B_inc2,\n"
"          unsigned int B_size1,  unsigned int B_size2,\n"
"          unsigned int B_internal_size1, unsigned int B_internal_size2)\n"
"{ \n"
"  float temp; \n"
"  for (unsigned int row_cnt = 0; row_cnt < A_size1; ++row_cnt) \n"
"  { \n"
"    unsigned int row = A_size1 - 1 - row_cnt;\n"
"    barrier(CLK_GLOBAL_MEM_FENCE); \n"
"    temp = B[(get_group_id(0) * B_inc1 + B_start1) + (row * B_inc2 + B_start2) * B_internal_size1]; \n"
"    //eliminate column of op(A) with index 'row' in parallel: \n"
"    for  (unsigned int elim = get_local_id(0); elim < row; elim += get_local_size(0)) \n"
"      B[(get_group_id(0) * B_inc1 + B_start1) + (elim * B_inc2 + B_start2) * B_internal_size1] -= temp * A[(row * A_inc1 + A_start1) + (elim * A_inc2 + A_start2) * A_internal_size1];\n"
"   }\n"
"}\n"
; //matrix_solve_col_col_align1_trans_unit_upper_trans_solve

const char * const matrix_solve_col_col_align1_trans_unit_upper_solve = 
"// file automatically generated - do not edit!\n"
"// inplace solve A^T \\ B\n"
"// matrix layouts: A...col_major, B...col_major\n"
"__kernel void trans_unit_upper_solve(\n"
"          __global const float * A,\n"
"          unsigned int A_start1, unsigned int A_start2,\n"
"          unsigned int A_inc1,   unsigned int A_inc2,\n"
"          unsigned int A_size1,  unsigned int A_size2,\n"
"          unsigned int A_internal_size1, unsigned int A_internal_size2,\n"
"          __global float * B,\n"
"          unsigned int B_start1, unsigned int B_start2,\n"
"          unsigned int B_inc1,   unsigned int B_inc2,\n"
"          unsigned int B_size1,  unsigned int B_size2,\n"
"          unsigned int B_internal_size1, unsigned int B_internal_size2)\n"
"{ \n"
"  float temp; \n"
"  for (unsigned int row_cnt = 0; row_cnt < A_size1; ++row_cnt) \n"
"  { \n"
"    unsigned int row = A_size1 - 1 - row_cnt;\n"
"    barrier(CLK_GLOBAL_MEM_FENCE); \n"
"    temp = B[(row * B_inc1 + B_start1) + (get_group_id(0) * B_inc2 + B_start2) * B_internal_size1]; \n"
"    //eliminate column of op(A) with index 'row' in parallel: \n"
"    for  (unsigned int elim = get_local_id(0); elim < row; elim += get_local_size(0)) \n"
"      B[(elim * B_inc1 + B_start1) + (get_group_id(0) * B_inc2 + B_start2) * B_internal_size1] -= temp * A[(row * A_inc1 + A_start1) + (elim * A_inc2 + A_start2) * A_internal_size1];\n"
"   }\n"
"}\n"
; //matrix_solve_col_col_align1_trans_unit_upper_solve

const char * const matrix_solve_col_col_align1_trans_upper_trans_solve = 
"// file automatically generated - do not edit!\n"
"// inplace solve A^T \\ B^T\n"
"// matrix layouts: A...col_major, B...col_major\n"
"__kernel void trans_upper_trans_solve(\n"
"          __global const float * A,\n"
"          unsigned int A_start1, unsigned int A_start2,\n"
"          unsigned int A_inc1,   unsigned int A_inc2,\n"
"          unsigned int A_size1,  unsigned int A_size2,\n"
"          unsigned int A_internal_size1, unsigned int A_internal_size2,\n"
"          __global float * B,\n"
"          unsigned int B_start1, unsigned int B_start2,\n"
"          unsigned int B_inc1,   unsigned int B_inc2,\n"
"          unsigned int B_size1,  unsigned int B_size2,\n"
"          unsigned int B_internal_size1, unsigned int B_internal_size2)\n"
"{ \n"
"  float temp; \n"
"  for (unsigned int row_cnt = 0; row_cnt < A_size1; ++row_cnt) \n"
"  { \n"
"    unsigned int row = A_size1 - 1 - row_cnt;\n"
"    barrier(CLK_GLOBAL_MEM_FENCE); \n"
"    if (get_local_id(0) == 0) \n"
"      B[(get_group_id(0) * B_inc1 + B_start1) + (row * B_inc2 + B_start2) * B_internal_size1] /= A[(row * A_inc1 + A_start1) + (row * A_inc2 + A_start2)*A_internal_size1];\n"
"    barrier(CLK_GLOBAL_MEM_FENCE); \n"
"    temp = B[(get_group_id(0) * B_inc1 + B_start1) + (row * B_inc2 + B_start2) * B_internal_size1]; \n"
"    //eliminate column of op(A) with index 'row' in parallel: \n"
"    for  (unsigned int elim = get_local_id(0); elim < row; elim += get_local_size(0)) \n"
"      B[(get_group_id(0) * B_inc1 + B_start1) + (elim * B_inc2 + B_start2) * B_internal_size1] -= temp * A[(row * A_inc1 + A_start1) + (elim * A_inc2 + A_start2) * A_internal_size1];\n"
"   }\n"
"}\n"
; //matrix_solve_col_col_align1_trans_upper_trans_solve

const char * const matrix_solve_col_col_align1_trans_unit_lower_trans_solve = 
"// file automatically generated - do not edit!\n"
"// inplace solve A^T \\ B^T\n"
"// matrix layouts: A...col_major, B...col_major\n"
"__kernel void trans_unit_lower_trans_solve(\n"
"          __global const float * A,\n"
"          unsigned int A_start1, unsigned int A_start2,\n"
"          unsigned int A_inc1,   unsigned int A_inc2,\n"
"          unsigned int A_size1,  unsigned int A_size2,\n"
"          unsigned int A_internal_size1, unsigned int A_internal_size2,\n"
"          __global float * B,\n"
"          unsigned int B_start1, unsigned int B_start2,\n"
"          unsigned int B_inc1,   unsigned int B_inc2,\n"
"          unsigned int B_size1,  unsigned int B_size2,\n"
"          unsigned int B_internal_size1, unsigned int B_internal_size2)\n"
"{ \n"
"  float temp; \n"
"  for (unsigned int row = 0; row < A_size1; ++row) \n"
"  { \n"
"    barrier(CLK_GLOBAL_MEM_FENCE); \n"
"    temp = B[(get_group_id(0) * B_inc1 + B_start1) + (row * B_inc2 + B_start2) * B_internal_size1]; \n"
"    //eliminate column of op(A) with index 'row' in parallel: \n"
"    for  (unsigned int elim = row + get_local_id(0) + 1; elim < A_size1; elim += get_local_size(0)) \n"
"      B[(get_group_id(0) * B_inc1 + B_start1) + (elim * B_inc2 + B_start2) * B_internal_size1] -= temp * A[(row * A_inc1 + A_start1) + (elim * A_inc2 + A_start2) * A_internal_size1];\n"
"   }\n"
"}\n"
; //matrix_solve_col_col_align1_trans_unit_lower_trans_solve

const char * const matrix_solve_col_col_align1_trans_unit_lower_solve = 
"// file automatically generated - do not edit!\n"
"// inplace solve A^T \\ B\n"
"// matrix layouts: A...col_major, B...col_major\n"
"__kernel void trans_unit_lower_solve(\n"
"          __global const float * A,\n"
"          unsigned int A_start1, unsigned int A_start2,\n"
"          unsigned int A_inc1,   unsigned int A_inc2,\n"
"          unsigned int A_size1,  unsigned int A_size2,\n"
"          unsigned int A_internal_size1, unsigned int A_internal_size2,\n"
"          __global float * B,\n"
"          unsigned int B_start1, unsigned int B_start2,\n"
"          unsigned int B_inc1,   unsigned int B_inc2,\n"
"          unsigned int B_size1,  unsigned int B_size2,\n"
"          unsigned int B_internal_size1, unsigned int B_internal_size2)\n"
"{ \n"
"  float temp; \n"
"  for (unsigned int row = 0; row < A_size1; ++row) \n"
"  { \n"
"    barrier(CLK_GLOBAL_MEM_FENCE); \n"
"    temp = B[(row * B_inc1 + B_start1) + (get_group_id(0) * B_inc2 + B_start2) * B_internal_size1]; \n"
"    //eliminate column of op(A) with index 'row' in parallel: \n"
"    for  (unsigned int elim = row + get_local_id(0) + 1; elim < A_size1; elim += get_local_size(0)) \n"
"      B[(elim * B_inc1 + B_start1) + (get_group_id(0) * B_inc2 + B_start2) * B_internal_size1] -= temp * A[(row * A_inc1 + A_start1) + (elim * A_inc2 + A_start2) * A_internal_size1];\n"
"   }\n"
"}\n"
; //matrix_solve_col_col_align1_trans_unit_lower_solve

const char * const matrix_solve_col_col_align1_unit_upper_solve = 
"// file automatically generated - do not edit!\n"
"// inplace solve A \\ B\n"
"// matrix layouts: A...col_major, B...col_major\n"
"__kernel void unit_upper_solve(\n"
"          __global const float * A,\n"
"          unsigned int A_start1, unsigned int A_start2,\n"
"          unsigned int A_inc1,   unsigned int A_inc2,\n"
"          unsigned int A_size1,  unsigned int A_size2,\n"
"          unsigned int A_internal_size1, unsigned int A_internal_size2,\n"
"          __global float * B,\n"
"          unsigned int B_start1, unsigned int B_start2,\n"
"          unsigned int B_inc1,   unsigned int B_inc2,\n"
"          unsigned int B_size1,  unsigned int B_size2,\n"
"          unsigned int B_internal_size1, unsigned int B_internal_size2)\n"
"{ \n"
"  float temp; \n"
"  for (unsigned int row_cnt = 0; row_cnt < A_size1; ++row_cnt) \n"
"  { \n"
"    unsigned int row = A_size1 - 1 - row_cnt;\n"
"    barrier(CLK_GLOBAL_MEM_FENCE); \n"
"    temp = B[(row * B_inc1 + B_start1) + (get_group_id(0) * B_inc2 + B_start2) * B_internal_size1]; \n"
"    //eliminate column of op(A) with index 'row' in parallel: \n"
"    for  (unsigned int elim = get_local_id(0); elim < row; elim += get_local_size(0)) \n"
"      B[(elim * B_inc1 + B_start1) + (get_group_id(0) * B_inc2 + B_start2) * B_internal_size1] -= temp * A[(elim * A_inc1 + A_start1) + (row * A_inc2 + A_start2) * A_internal_size1];\n"
"   }\n"
"}\n"
; //matrix_solve_col_col_align1_unit_upper_solve

const char * const matrix_solve_col_col_align1_trans_lower_trans_solve = 
"// file automatically generated - do not edit!\n"
"// inplace solve A^T \\ B^T\n"
"// matrix layouts: A...col_major, B...col_major\n"
"__kernel void trans_lower_trans_solve(\n"
"          __global const float * A,\n"
"          unsigned int A_start1, unsigned int A_start2,\n"
"          unsigned int A_inc1,   unsigned int A_inc2,\n"
"          unsigned int A_size1,  unsigned int A_size2,\n"
"          unsigned int A_internal_size1, unsigned int A_internal_size2,\n"
"          __global float * B,\n"
"          unsigned int B_start1, unsigned int B_start2,\n"
"          unsigned int B_inc1,   unsigned int B_inc2,\n"
"          unsigned int B_size1,  unsigned int B_size2,\n"
"          unsigned int B_internal_size1, unsigned int B_internal_size2)\n"
"{ \n"
"  float temp; \n"
"  for (unsigned int row = 0; row < A_size1; ++row) \n"
"  { \n"
"    barrier(CLK_GLOBAL_MEM_FENCE); \n"
"    if (get_local_id(0) == 0) \n"
"      B[(get_group_id(0) * B_inc1 + B_start1) + (row * B_inc2 + B_start2) * B_internal_size1] /= A[(row * A_inc1 + A_start1) + (row * A_inc2 + A_start2)*A_internal_size1];\n"
"    barrier(CLK_GLOBAL_MEM_FENCE); \n"
"    temp = B[(get_group_id(0) * B_inc1 + B_start1) + (row * B_inc2 + B_start2) * B_internal_size1]; \n"
"    //eliminate column of op(A) with index 'row' in parallel: \n"
"    for  (unsigned int elim = row + get_local_id(0) + 1; elim < A_size1; elim += get_local_size(0)) \n"
"      B[(get_group_id(0) * B_inc1 + B_start1) + (elim * B_inc2 + B_start2) * B_internal_size1] -= temp * A[(row * A_inc1 + A_start1) + (elim * A_inc2 + A_start2) * A_internal_size1];\n"
"   }\n"
"}\n"
; //matrix_solve_col_col_align1_trans_lower_trans_solve

const char * const matrix_solve_col_col_align1_unit_lower_solve = 
"// file automatically generated - do not edit!\n"
"// inplace solve A \\ B\n"
"// matrix layouts: A...col_major, B...col_major\n"
"__kernel void unit_lower_solve(\n"
"          __global const float * A,\n"
"          unsigned int A_start1, unsigned int A_start2,\n"
"          unsigned int A_inc1,   unsigned int A_inc2,\n"
"          unsigned int A_size1,  unsigned int A_size2,\n"
"          unsigned int A_internal_size1, unsigned int A_internal_size2,\n"
"          __global float * B,\n"
"          unsigned int B_start1, unsigned int B_start2,\n"
"          unsigned int B_inc1,   unsigned int B_inc2,\n"
"          unsigned int B_size1,  unsigned int B_size2,\n"
"          unsigned int B_internal_size1, unsigned int B_internal_size2)\n"
"{ \n"
"  float temp; \n"
"  for (unsigned int row = 0; row < A_size1; ++row) \n"
"  { \n"
"    barrier(CLK_GLOBAL_MEM_FENCE); \n"
"    temp = B[(row * B_inc1 + B_start1) + (get_group_id(0) * B_inc2 + B_start2) * B_internal_size1]; \n"
"    //eliminate column of op(A) with index 'row' in parallel: \n"
"    for  (unsigned int elim = row + get_local_id(0) + 1; elim < A_size1; elim += get_local_size(0)) \n"
"      B[(elim * B_inc1 + B_start1) + (get_group_id(0) * B_inc2 + B_start2) * B_internal_size1] -= temp * A[(elim * A_inc1 + A_start1) + (row * A_inc2 + A_start2) * A_internal_size1];\n"
"   }\n"
"}\n"
; //matrix_solve_col_col_align1_unit_lower_solve

const char * const matrix_solve_col_col_align1_upper_solve = 
"// file automatically generated - do not edit!\n"
"// inplace solve A \\ B\n"
"// matrix layouts: A...col_major, B...col_major\n"
"__kernel void upper_solve(\n"
"          __global const float * A,\n"
"          unsigned int A_start1, unsigned int A_start2,\n"
"          unsigned int A_inc1,   unsigned int A_inc2,\n"
"          unsigned int A_size1,  unsigned int A_size2,\n"
"          unsigned int A_internal_size1, unsigned int A_internal_size2,\n"
"          __global float * B,\n"
"          unsigned int B_start1, unsigned int B_start2,\n"
"          unsigned int B_inc1,   unsigned int B_inc2,\n"
"          unsigned int B_size1,  unsigned int B_size2,\n"
"          unsigned int B_internal_size1, unsigned int B_internal_size2)\n"
"{ \n"
"  float temp; \n"
"  for (unsigned int row_cnt = 0; row_cnt < A_size1; ++row_cnt) \n"
"  { \n"
"    unsigned int row = A_size1 - 1 - row_cnt;\n"
"    barrier(CLK_GLOBAL_MEM_FENCE); \n"
"    if (get_local_id(0) == 0) \n"
"      B[(row * B_inc1 + B_start1) + (get_group_id(0) * B_inc2 + B_start2) * B_internal_size1] /= A[(row * A_inc1 + A_start1) + (row * A_inc2 + A_start2)*A_internal_size1];\n"
"    barrier(CLK_GLOBAL_MEM_FENCE); \n"
"    temp = B[(row * B_inc1 + B_start1) + (get_group_id(0) * B_inc2 + B_start2) * B_internal_size1]; \n"
"    //eliminate column of op(A) with index 'row' in parallel: \n"
"    for  (unsigned int elim = get_local_id(0); elim < row; elim += get_local_size(0)) \n"
"      B[(elim * B_inc1 + B_start1) + (get_group_id(0) * B_inc2 + B_start2) * B_internal_size1] -= temp * A[(elim * A_inc1 + A_start1) + (row * A_inc2 + A_start2) * A_internal_size1];\n"
"   }\n"
"}\n"
; //matrix_solve_col_col_align1_upper_solve

const char * const matrix_solve_col_col_align1_unit_upper_trans_solve = 
"// file automatically generated - do not edit!\n"
"// inplace solve A \\ B^T\n"
"// matrix layouts: A...col_major, B...col_major\n"
"__kernel void unit_upper_trans_solve(\n"
"          __global const float * A,\n"
"          unsigned int A_start1, unsigned int A_start2,\n"
"          unsigned int A_inc1,   unsigned int A_inc2,\n"
"          unsigned int A_size1,  unsigned int A_size2,\n"
"          unsigned int A_internal_size1, unsigned int A_internal_size2,\n"
"          __global float * B,\n"
"          unsigned int B_start1, unsigned int B_start2,\n"
"          unsigned int B_inc1,   unsigned int B_inc2,\n"
"          unsigned int B_size1,  unsigned int B_size2,\n"
"          unsigned int B_internal_size1, unsigned int B_internal_size2)\n"
"{ \n"
"  float temp; \n"
"  for (unsigned int row_cnt = 0; row_cnt < A_size1; ++row_cnt) \n"
"  { \n"
"    unsigned int row = A_size1 - 1 - row_cnt;\n"
"    barrier(CLK_GLOBAL_MEM_FENCE); \n"
"    temp = B[(get_group_id(0) * B_inc1 + B_start1) + (row * B_inc2 + B_start2) * B_internal_size1]; \n"
"    //eliminate column of op(A) with index 'row' in parallel: \n"
"    for  (unsigned int elim = get_local_id(0); elim < row; elim += get_local_size(0)) \n"
"      B[(get_group_id(0) * B_inc1 + B_start1) + (elim * B_inc2 + B_start2) * B_internal_size1] -= temp * A[(elim * A_inc1 + A_start1) + (row * A_inc2 + A_start2) * A_internal_size1];\n"
"   }\n"
"}\n"
; //matrix_solve_col_col_align1_unit_upper_trans_solve

const char * const matrix_solve_col_col_align1_lower_trans_solve = 
"// file automatically generated - do not edit!\n"
"// inplace solve A \\ B^T\n"
"// matrix layouts: A...col_major, B...col_major\n"
"__kernel void lower_trans_solve(\n"
"          __global const float * A,\n"
"          unsigned int A_start1, unsigned int A_start2,\n"
"          unsigned int A_inc1,   unsigned int A_inc2,\n"
"          unsigned int A_size1,  unsigned int A_size2,\n"
"          unsigned int A_internal_size1, unsigned int A_internal_size2,\n"
"          __global float * B,\n"
"          unsigned int B_start1, unsigned int B_start2,\n"
"          unsigned int B_inc1,   unsigned int B_inc2,\n"
"          unsigned int B_size1,  unsigned int B_size2,\n"
"          unsigned int B_internal_size1, unsigned int B_internal_size2)\n"
"{ \n"
"  float temp; \n"
"  for (unsigned int row = 0; row < A_size1; ++row) \n"
"  { \n"
"    barrier(CLK_GLOBAL_MEM_FENCE); \n"
"    if (get_local_id(0) == 0) \n"
"      B[(get_group_id(0) * B_inc1 + B_start1) + (row * B_inc2 + B_start2) * B_internal_size1] /= A[(row * A_inc1 + A_start1) + (row * A_inc2 + A_start2)*A_internal_size1];\n"
"    barrier(CLK_GLOBAL_MEM_FENCE); \n"
"    temp = B[(get_group_id(0) * B_inc1 + B_start1) + (row * B_inc2 + B_start2) * B_internal_size1]; \n"
"    //eliminate column of op(A) with index 'row' in parallel: \n"
"    for  (unsigned int elim = row + get_local_id(0) + 1; elim < A_size1; elim += get_local_size(0)) \n"
"      B[(get_group_id(0) * B_inc1 + B_start1) + (elim * B_inc2 + B_start2) * B_internal_size1] -= temp * A[(elim * A_inc1 + A_start1) + (row * A_inc2 + A_start2) * A_internal_size1];\n"
"   }\n"
"}\n"
; //matrix_solve_col_col_align1_lower_trans_solve

const char * const matrix_solve_col_col_align1_trans_lower_solve = 
"// file automatically generated - do not edit!\n"
"// inplace solve A^T \\ B\n"
"// matrix layouts: A...col_major, B...col_major\n"
"__kernel void trans_lower_solve(\n"
"          __global const float * A,\n"
"          unsigned int A_start1, unsigned int A_start2,\n"
"          unsigned int A_inc1,   unsigned int A_inc2,\n"
"          unsigned int A_size1,  unsigned int A_size2,\n"
"          unsigned int A_internal_size1, unsigned int A_internal_size2,\n"
"          __global float * B,\n"
"          unsigned int B_start1, unsigned int B_start2,\n"
"          unsigned int B_inc1,   unsigned int B_inc2,\n"
"          unsigned int B_size1,  unsigned int B_size2,\n"
"          unsigned int B_internal_size1, unsigned int B_internal_size2)\n"
"{ \n"
"  float temp; \n"
"  for (unsigned int row = 0; row < A_size1; ++row) \n"
"  { \n"
"    barrier(CLK_GLOBAL_MEM_FENCE); \n"
"    if (get_local_id(0) == 0) \n"
"      B[(row * B_inc1 + B_start1) + (get_group_id(0) * B_inc2 + B_start2) * B_internal_size1] /= A[(row * A_inc1 + A_start1) + (row * A_inc2 + A_start2)*A_internal_size1];\n"
"    barrier(CLK_GLOBAL_MEM_FENCE); \n"
"    temp = B[(row * B_inc1 + B_start1) + (get_group_id(0) * B_inc2 + B_start2) * B_internal_size1]; \n"
"    //eliminate column of op(A) with index 'row' in parallel: \n"
"    for  (unsigned int elim = row + get_local_id(0) + 1; elim < A_size1; elim += get_local_size(0)) \n"
"      B[(elim * B_inc1 + B_start1) + (get_group_id(0) * B_inc2 + B_start2) * B_internal_size1] -= temp * A[(row * A_inc1 + A_start1) + (elim * A_inc2 + A_start2) * A_internal_size1];\n"
"   }\n"
"}\n"
; //matrix_solve_col_col_align1_trans_lower_solve

const char * const matrix_solve_col_col_align1_lower_solve = 
"// file automatically generated - do not edit!\n"
"// inplace solve A \\ B\n"
"// matrix layouts: A...col_major, B...col_major\n"
"__kernel void lower_solve(\n"
"          __global const float * A,\n"
"          unsigned int A_start1, unsigned int A_start2,\n"
"          unsigned int A_inc1,   unsigned int A_inc2,\n"
"          unsigned int A_size1,  unsigned int A_size2,\n"
"          unsigned int A_internal_size1, unsigned int A_internal_size2,\n"
"          __global float * B,\n"
"          unsigned int B_start1, unsigned int B_start2,\n"
"          unsigned int B_inc1,   unsigned int B_inc2,\n"
"          unsigned int B_size1,  unsigned int B_size2,\n"
"          unsigned int B_internal_size1, unsigned int B_internal_size2)\n"
"{ \n"
"  float temp; \n"
"  for (unsigned int row = 0; row < A_size1; ++row) \n"
"  { \n"
"    barrier(CLK_GLOBAL_MEM_FENCE); \n"
"    if (get_local_id(0) == 0) \n"
"      B[(row * B_inc1 + B_start1) + (get_group_id(0) * B_inc2 + B_start2) * B_internal_size1] /= A[(row * A_inc1 + A_start1) + (row * A_inc2 + A_start2)*A_internal_size1];\n"
"    barrier(CLK_GLOBAL_MEM_FENCE); \n"
"    temp = B[(row * B_inc1 + B_start1) + (get_group_id(0) * B_inc2 + B_start2) * B_internal_size1]; \n"
"    //eliminate column of op(A) with index 'row' in parallel: \n"
"    for  (unsigned int elim = row + get_local_id(0) + 1; elim < A_size1; elim += get_local_size(0)) \n"
"      B[(elim * B_inc1 + B_start1) + (get_group_id(0) * B_inc2 + B_start2) * B_internal_size1] -= temp * A[(elim * A_inc1 + A_start1) + (row * A_inc2 + A_start2) * A_internal_size1];\n"
"   }\n"
"}\n"
; //matrix_solve_col_col_align1_lower_solve

  }  //namespace kernels
 }  //namespace linalg
}  //namespace viennacl
#endif

