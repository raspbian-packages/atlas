/* ---------------------------------------------------------------------
 *
 * -- Automatically Tuned Linear Algebra Software (ATLAS)
 *    (C) Copyright 2000 All Rights Reserved
 *
 * -- ATLAS routine -- Version 3.9.24 -- December 25, 2000
 *
 * Author         : Antoine P. Petitet
 * Originally developed at the University of Tennessee,
 * Innovative Computing Laboratory, Knoxville TN, 37996-1301, USA.
 *
 * ---------------------------------------------------------------------
 *
 * -- Copyright notice and Licensing terms:
 *
 *  Redistribution  and  use in  source and binary forms, with or without
 *  modification, are  permitted provided  that the following  conditions
 *  are met:
 *
 * 1. Redistributions  of  source  code  must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce  the above copyright
 *    notice,  this list of conditions, and the  following disclaimer in
 *    the documentation and/or other materials provided with the distri-
 *    bution.
 * 3. The name of the University,  the ATLAS group,  or the names of its
 *    contributors  may not be used to endorse or promote products deri-
 *    ved from this software without specific written permission.
 *
 * -- Disclaimer:
 *
 * THIS  SOFTWARE  IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES,  INCLUDING,  BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE UNIVERSITY
 * OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,  INDIRECT, INCIDENTAL, SPE-
 * CIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO,  PROCUREMENT  OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEO-
 * RY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT  (IN-
 * CLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * ---------------------------------------------------------------------
 */
/*
 * Include files
 */
#include "atlas_refmisc.h"
#include "atlas_reflvl3.h"
#include "atlas_reflevel3.h"

void ATL_zreftrmmRUCN
(
   const int                  M,
   const int                  N,
   const double               * ALPHA,
   const double               * A,
   const int                  LDA,
   double                     * B,
   const int                  LDB
)
{
/*
 * Purpose
 * =======
 *
 * ATL_zreftrmmRUCN( ... )
 *
 * <=>
 *
 * ATL_zreftrmm
 * ( AtlasRight, AtlasUpper, AtlasConjTrans, AtlasNonUnit, ... )
 *
 * See ATL_zreftrmm for details.
 *
 * ---------------------------------------------------------------------
 */
/*
 * .. Local Variables ..
 */
   double                     t0_i, t0_r;
   int                        i, iajk, ibij, ibik, j, jak, jbj, jbk, k,
                              lda2 = ( LDA << 1 ), ldb2 = ( LDB << 1 );
/* ..
 * .. Executable Statements ..
 *
 */
   for( k = 0, jak = 0, jbk = 0; k < N; k++, jak += lda2, jbk += ldb2 )
   {
      for( j = 0, iajk  = jak, jbj  = 0; j < k; j++, iajk += 2,   jbj += ldb2 )
      {
         Mmul( ALPHA[0], ALPHA[1], A[iajk], -A[iajk+1], t0_r, t0_i );
         for( i = 0,      ibij  = jbj, ibik  = jbk;
              i < M; i++, ibij += 2,   ibik += 2 )
         { Mmla( t0_r, t0_i, B[ibik], B[ibik+1], B[ibij], B[ibij+1] ); }
      }
      Mset( ALPHA[0], ALPHA[1], t0_r, t0_i );
      i = ( k << 1 ) + jak; Mdscl( A[i], -A[i+1], t0_r, t0_i );
      for( i = 0, ibik = jbk; i < M; i++, ibik += 2 )
      { Mdscl( t0_r, t0_i, B[ibik], B[ibik+1] ); }
   }
/*
 * End of ATL_zreftrmmRUCN
 */
}
