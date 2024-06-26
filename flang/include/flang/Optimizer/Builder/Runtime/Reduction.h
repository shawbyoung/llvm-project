//===-- Reduction.h -- generate calls to reduction runtime API --*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// The runtime routines generated in this file are generally storing the result
// in a descriptor (represented as a `box` in FIR). Some function might
// have a specialization where the value is returned as a scalar value, e.g.
// `genAll` is a specialization of `genAllDescriptor`.
//
//===----------------------------------------------------------------------===//

#ifndef FORTRAN_OPTIMIZER_BUILDER_RUNTIME_REDUCTION_H
#define FORTRAN_OPTIMIZER_BUILDER_RUNTIME_REDUCTION_H

#include "mlir/Dialect/Func/IR/FuncOps.h"

namespace fir {
class ExtendedValue;
class FirOpBuilder;
} // namespace fir

namespace fir::runtime {

/// Generate call to `AllDim` runtime routine.
/// This calls the descriptor based runtime call implementation of the `all`
/// intrinsic.
void genAllDescriptor(fir::FirOpBuilder &builder, mlir::Location loc,
                      mlir::Value resultBox, mlir::Value maskBox,
                      mlir::Value dim);

/// Generate call to `AnyDim` runtime routine.
/// This calls the descriptor based runtime call implementation of the `any`
/// intrinsic.
void genAnyDescriptor(fir::FirOpBuilder &builder, mlir::Location loc,
                      mlir::Value resultBox, mlir::Value maskBox,
                      mlir::Value dim);

/// Generate call to `ParityDim` runtime routine.
/// This calls the descriptor based runtime call implementation of the `parity`
/// intrinsic.
void genParityDescriptor(fir::FirOpBuilder &builder, mlir::Location loc,
                         mlir::Value resultBox, mlir::Value maskBox,
                         mlir::Value dim);

/// Generate call to `All` runtime routine. This version of `all` is specialized
/// for rank 1 mask arguments.
/// This calls the version that returns a scalar logical value.
mlir::Value genAll(fir::FirOpBuilder &builder, mlir::Location loc,
                   mlir::Value maskBox, mlir::Value dim);

/// Generate call to `Any` runtime routine. This version of `any` is specialized
/// for rank 1 mask arguments.
/// This calls the version that returns a scalar logical value.
mlir::Value genAny(fir::FirOpBuilder &builder, mlir::Location loc,
                   mlir::Value maskBox, mlir::Value dim);

/// Generate call to `Count` runtime routine. This routine is a specialized
/// version when mask is a rank one array or the dim argument is not
/// specified by the user.
mlir::Value genCount(fir::FirOpBuilder &builder, mlir::Location loc,
                     mlir::Value maskBox, mlir::Value dim);

/// Generate call to general `CountDim` runtime routine. This routine has a
/// descriptor result.
void genCountDim(fir::FirOpBuilder &builder, mlir::Location loc,
                 mlir::Value resultBox, mlir::Value maskBox, mlir::Value dim,
                 mlir::Value kind);

/// Generate call to `DotProduct` intrinsic runtime routine.
mlir::Value genDotProduct(fir::FirOpBuilder &builder, mlir::Location loc,
                          mlir::Value vectorABox, mlir::Value vectorBBox,
                          mlir::Value resultBox);

/// Generate call to `Findloc` intrinsic runtime routine. This is the version
/// that does not take a dim argument.
void genFindloc(fir::FirOpBuilder &builder, mlir::Location loc,
                mlir::Value resultBox, mlir::Value arrayBox, mlir::Value val,
                mlir::Value maskBox, mlir::Value kind, mlir::Value back);

/// Generate call to `FindlocDim` intrinsic runtime routine. This is the version
/// that takes a dim argument.
void genFindlocDim(fir::FirOpBuilder &builder, mlir::Location loc,
                   mlir::Value resultBox, mlir::Value arrayBox, mlir::Value val,
                   mlir::Value dim, mlir::Value maskBox, mlir::Value kind,
                   mlir::Value back);

/// Generate call to `Maxloc` intrinsic runtime routine. This is the version
/// that does not take a dim argument.
void genMaxloc(fir::FirOpBuilder &builder, mlir::Location loc,
               mlir::Value resultBox, mlir::Value arrayBox, mlir::Value maskBox,
               mlir::Value kind, mlir::Value back);

/// Generate call to `MaxlocDim` intrinsic runtime routine. This is the version
/// that takes a dim argument.
void genMaxlocDim(fir::FirOpBuilder &builder, mlir::Location loc,
                  mlir::Value resultBox, mlir::Value arrayBox, mlir::Value dim,
                  mlir::Value maskBox, mlir::Value kind, mlir::Value back);

/// Generate call to `Minloc` intrinsic runtime routine. This is the version
/// that does not take a dim argument.
void genMinloc(fir::FirOpBuilder &builder, mlir::Location loc,
               mlir::Value resultBox, mlir::Value arrayBox, mlir::Value maskBox,
               mlir::Value kind, mlir::Value back);

/// Generate call to `MinlocDim` intrinsic runtime routine. This is the version
/// that takes a dim argument.
void genMinlocDim(fir::FirOpBuilder &builder, mlir::Location loc,
                  mlir::Value resultBox, mlir::Value arrayBox, mlir::Value dim,
                  mlir::Value maskBox, mlir::Value kind, mlir::Value back);

/// Generate call to `Maxval` intrinsic runtime routine. This is the version
/// that does not take a dim argument.
mlir::Value genMaxval(fir::FirOpBuilder &builder, mlir::Location loc,
                      mlir::Value arrayBox, mlir::Value maskBox);

/// Generate call to `MaxvalCharacter` intrinsic runtime routine. This is the
/// version hat that handles 1 dimensional character arrays  with no DIM
/// argument.
void genMaxvalChar(fir::FirOpBuilder &builder, mlir::Location loc,
                   mlir::Value resultBox, mlir::Value arrayBox,
                   mlir::Value maskBox);

/// Generate call to `MaxvalDim` intrinsic runtime routine. This is the version
/// that takes arrays of any rank with a dim argument specified.
void genMaxvalDim(fir::FirOpBuilder &builder, mlir::Location loc,
                  mlir::Value resultBox, mlir::Value arrayBox, mlir::Value dim,
                  mlir::Value maskBox);

/// Generate call to `Minval` intrinsic runtime routine. This is the version
/// that does not take a dim argument.
mlir::Value genMinval(fir::FirOpBuilder &builder, mlir::Location loc,
                      mlir::Value arrayBox, mlir::Value maskBox);

/// Generate call to `MinvalCharacter` intrinsic runtime routine. This is the
/// version that handles 1 dimensional character arrays with no DIM
/// argument.
void genMinvalChar(fir::FirOpBuilder &builder, mlir::Location loc,
                   mlir::Value resultBox, mlir::Value arrayBox,
                   mlir::Value maskBox);

/// Generate call to `MinvalDim` intrinsic runtime routine. This is the version
/// that takes arrays of any rank with a dim argument specified.
void genMinvalDim(fir::FirOpBuilder &builder, mlir::Location loc,
                  mlir::Value resultBox, mlir::Value arrayBox, mlir::Value dim,
                  mlir::Value maskBox);

/// Generate call to `Norm2` intrinsic runtime routine. This is the version
/// that does not take a dim argument.
mlir::Value genNorm2(fir::FirOpBuilder &builder, mlir::Location loc,
                     mlir::Value arrayBox);

/// Generate call to `Norm2Dim` intrinsic runtime routine. This is the version
/// that takes a dim argument.
void genNorm2Dim(fir::FirOpBuilder &builder, mlir::Location loc,
                 mlir::Value resultBox, mlir::Value arrayBox, mlir::Value dim);

/// Generate call to `Parity` runtime routine. This version of `parity` is
/// specialized for rank 1 mask arguments.
/// This calls the version that returns a scalar logical value.
mlir::Value genParity(fir::FirOpBuilder &builder, mlir::Location loc,
                      mlir::Value maskBox, mlir::Value dim);

/// Generate call to `Product` intrinsic runtime routine. This is the version
/// that does not take a dim argument.
mlir::Value genProduct(fir::FirOpBuilder &builder, mlir::Location loc,
                       mlir::Value arrayBox, mlir::Value maskBox,
                       mlir::Value resultBox);

/// Generate call to `ProductDim` intrinsic runtime routine. This is the version
/// that takes arrays of any rank with a dim argument specified.
void genProductDim(fir::FirOpBuilder &builder, mlir::Location loc,
                   mlir::Value resultBox, mlir::Value arrayBox, mlir::Value dim,
                   mlir::Value maskBox);

/// Generate call to `Sum` intrinsic runtime routine. This is the version
/// that does not take a dim argument.
mlir::Value genSum(fir::FirOpBuilder &builder, mlir::Location loc,
                   mlir::Value arrayBox, mlir::Value maskBox,
                   mlir::Value resultBox);

/// Generate call to `SumDim` intrinsic runtime routine. This is the version
/// that takes arrays of any rank with a dim argument specified.
void genSumDim(fir::FirOpBuilder &builder, mlir::Location loc,
               mlir::Value resultBox, mlir::Value arrayBox, mlir::Value dim,
               mlir::Value maskBox);

/// Generate call to `IAll` intrinsic runtime routine. This is the version
/// that does not take a dim argument.
mlir::Value genIAll(fir::FirOpBuilder &builder, mlir::Location loc,
                    mlir::Value arrayBox, mlir::Value maskBox,
                    mlir::Value resultBox);

/// Generate call to `IAllDim` intrinsic runtime routine. This is the version
/// that takes arrays of any rank with a dim argument specified.
void genIAllDim(fir::FirOpBuilder &builder, mlir::Location loc,
                mlir::Value resultBox, mlir::Value arrayBox, mlir::Value dim,
                mlir::Value maskBox);

/// Generate call to `IAny` intrinsic runtime routine. This is the version
/// that does not take a dim argument.
mlir::Value genIAny(fir::FirOpBuilder &builder, mlir::Location loc,
                    mlir::Value arrayBox, mlir::Value maskBox,
                    mlir::Value resultBox);

/// Generate call to `IAnyDim` intrinsic runtime routine. This is the version
/// that takes arrays of any rank with a dim argument specified.
void genIAnyDim(fir::FirOpBuilder &builder, mlir::Location loc,
                mlir::Value resultBox, mlir::Value arrayBox, mlir::Value dim,
                mlir::Value maskBox);

/// Generate call to `IParity` intrinsic runtime routine. This is the version
/// that does not take a dim argument.
mlir::Value genIParity(fir::FirOpBuilder &builder, mlir::Location loc,
                       mlir::Value arrayBox, mlir::Value maskBox,
                       mlir::Value resultBox);

/// Generate call to `IParityDim` intrinsic runtime routine. This is the version
/// that takes arrays of any rank with a dim argument specified.
void genIParityDim(fir::FirOpBuilder &builder, mlir::Location loc,
                   mlir::Value resultBox, mlir::Value arrayBox, mlir::Value dim,
                   mlir::Value maskBox);

/// Generate call to `Reduce` intrinsic runtime routine. This is the version
/// that does not take a dim argument and store the result in the provided
/// result value. This is used for COMPLEX, CHARACTER and DERIVED TYPES.
void genReduce(fir::FirOpBuilder &builder, mlir::Location loc,
               mlir::Value arrayBox, mlir::Value operation, mlir::Value maskBox,
               mlir::Value identity, mlir::Value ordered,
               mlir::Value resultBox);

/// Generate call to `Reduce` intrinsic runtime routine. This is the version
/// that does not take a dim argument and return a scalare result. This is used
/// for REAL, INTEGER and LOGICAL TYPES.
mlir::Value genReduce(fir::FirOpBuilder &builder, mlir::Location loc,
                      mlir::Value arrayBox, mlir::Value operation,
                      mlir::Value maskBox, mlir::Value identity,
                      mlir::Value ordered);

} // namespace fir::runtime

#endif // FORTRAN_OPTIMIZER_BUILDER_RUNTIME_REDUCTION_H
