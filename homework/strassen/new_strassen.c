#include <stdlib.h>

#include "matrix.h"

void sum_matrix_blocks(float **C,
                       const size_t C_f_row,
                       const size_t C_f_col,
                       float ** A,
                       const size_t A_f_row,
                       const size_t A_f_col,
                       float ** B,
                       const size_t B_f_row,
                       const size_t B_f_col,
                       const size_t n)
{
  // for all the rows in the blocks
  for (size_t i=0; i<n; i++) {

    // for all the cols in the blocks
    for (size_t j=0; j<n; j++) {
      C[C_f_row+i][C_f_col+j] = A[A_f_row+i][A_f_col+j] +
                                B[B_f_row+i][B_f_col+j];
    }
  }
}

void sub_matrix_blocks(float **C,
                       const size_t C_f_row,
                       const size_t C_f_col,
                       float ** A,
                       const size_t A_f_row,
                       const size_t A_f_col,
                       float ** B,
                       const size_t B_f_row,
                       const size_t B_f_col,
                       const size_t n)
{
  // for all the rows in the blocks
  for (size_t i=0; i<n; i++) {

    // for all the cols in the blocks
    for (size_t j=0; j<n; j++) {
      C[C_f_row+i][C_f_col+j] = A[A_f_row+i][A_f_col+j] -
                                B[B_f_row+i][B_f_col+j];
    }
  }
}

void naive_aux(float **C, const size_t C_f_row, const size_t C_f_col,
               float **A, const size_t A_f_row, const size_t A_f_col,
               float **B, const size_t B_f_row, const size_t B_f_col,
               const size_t n)
{
   for (size_t i=0; i<n; i++) {
     for (size_t j=0; j<n; j++) {
       C[C_f_row+i][C_f_col+j] = 0.0;
       for (size_t k=0; k<n; k++) {
         C[C_f_row+i][C_f_col+j] += (A[A_f_row+i][A_f_col+k]*
                                     B[B_f_row+k][B_f_col+j]);
       }
     }

   }
}

void strassen_aux(float **C, const size_t C_f_row, const size_t C_f_col,
               float **A, const size_t A_f_row, const size_t A_f_col,
               float **B, const size_t B_f_row, const size_t B_f_col,
               float **D, const size_t D_f_row, const size_t D_f_col,
               const size_t n)
{
  if (n < (1<<6)) {  //bitwise : base case for n<2^5
    naive_aux(C, C_f_row, C_f_col,
              A, A_f_row, A_f_col,
              B, B_f_row, B_f_col,
              n);
    return;
  }

  const size_t n2=n/2;

  const size_t C1X = C_f_row;
  const size_t C2X = C_f_row + n2;
  const size_t CX1 = C_f_col;
  const size_t CX2 = C_f_col + n2;

  const size_t A1X = A_f_row;
  const size_t A2X = A_f_row + n2;
  const size_t AX1 = A_f_col;
  const size_t AX2 = A_f_col + n2;

  const size_t B1X = B_f_row;
  const size_t B2X = B_f_row + n2;
  const size_t BX1 = B_f_col;
  const size_t BX2 = B_f_col + n2;

  const size_t D1X = D_f_row;
  const size_t D2X = D_f_row + n2;
  const size_t DX1 = D_f_col;
  const size_t DX2 = D_f_col + n2;

  //until used, C it's allocated memory useful to store temporary data
  sub_matrix_blocks(C, C2X, CX2, //S7
        	          A,A1X,AX2,
        	          A,A2X,AX2,
        	          n2);

  	sum_matrix_blocks(C, C1X, CX2, //S8
        	            B,B2X,BX1,
        	            B,B2X,BX2,
        	            n2);

  	strassen_aux(D, D1X, DX1, //P6
                          C, C2X, CX2, //this is S7
                          C, C1X, CX2, //this S8
                          D, D2X, DX2,
                          n2);

  	// P2 = S2 x B22, so S2 first
 	 sum_matrix_blocks(C, C2X, CX2, //S2
 	                   A,A1X,AX1,
 	                   A,A1X,AX2,
 	                   n2);

 	 strassen_aux(C, C1X, CX2, //P2
                         C, C2X, CX2, //S2
                         B, B2X, BX2,
                         D, D2X, DX2,
                         n2);

  	// P5 = S5 x S6, so S5 and S6
  	sum_matrix_blocks(C, C2X, CX2, //S5
  	                  A,A1X,AX1,
  	                  A,A2X,AX2,
  	                  n2);

 
  	sum_matrix_blocks(C, C2X, CX1, //S6
        	            B,B1X,BX1,
        	            B,B2X,BX2,
        	            n2);

  	strassen_aux(D, D1X, DX2, // P5
                          C, C2X, CX2, //S5
                          C, C2X, CX1, //S6 
                          D,D2X,DX2,   
                          n2);

  	// P4 = A22 x S4, so S4
  	sub_matrix_blocks(C, C2X, CX2, //S4
        	            B,B2X,BX1,
        	            B,B1X,BX1,
        	            n2);

  	strassen_aux(D, D2X, DX1, // P4
        	                A, A2X, AX2,
        	                C, C2X, CX2, //S4
		                      D,D2X,DX2,
        	                n2);

  // P4 + P5
  sum_matrix_blocks(C, C1X, CX1,
                    D, D1X, DX2, //P5
                    D, D2X, DX1, //P4
                    n2);

  // (P4 + P5) - P2
  sub_matrix_blocks(C, C1X, CX1,
                    C, C1X, CX1,
                    C, C1X, CX2, //P2
                    n2);

  // ((P4 + P5) - P2) + P6
  sum_matrix_blocks(C, C1X, CX1,
                    C, C1X, CX1,
                    D, D1X, DX1, //P6
                    n2);
  //C11 done


  /// C12 = P1 + P2

 	 // P1 = A11 x S1, S1 not done yet
  	sub_matrix_blocks(C, C2X, CX1, //S1
                      B, B1X,BX2,
                      B, B2X,BX2,
                      n2);

	strassen_aux(C, C2X, CX2, //P1
                        A, A1X, AX1,
                        C, C2X, CX1, //S1
                        D, D2X, DX2,
                        n2);


  sum_matrix_blocks(C, C1X, CX2,
                    C, C2X, CX2, //P1
                    C, C1X, CX2, //P2
                    n2);


  // C21 = P3 + P4

 	 // P3 = S3 x B11, S3 not done yet
 	 sum_matrix_blocks(C, C2X, CX1, //S3
  	                 A, A2X, AX1,
  	                 A, A2X, AX2,
  	                 n2);

   strassen_aux(D, D1X, DX1, //P3
                         C, C2X, CX1, //S3
        	               B, B1X, BX1,
		                     D,D2X,DX2,
                  	     n2);


   sum_matrix_blocks(C, C2X, CX1,
                     D, D1X, DX1, //P3
                     D, D2X, DX1, //P4
                     n2);



  // C22 = P5 + P1 - P3 - P7

  // P1 + P5
  sum_matrix_blocks(C, C2X, CX2,
                    C, C2X, CX2, //P1
                    D, D1X, DX2, //P5
                    n2);

  // (P5 + P1) - P3
  sub_matrix_blocks(C, C2X, CX2,
                    C, C2X, CX2,
                    D, D1X, DX1, //P3
                    n2);

 	// P7 = S9 x S10, need S9 and S10
 	 sub_matrix_blocks( D, D1X, DX1, //S9
        	            A,A1X,AX1,
        	            A,A2X,AX1,
        	            n2);

 	 sum_matrix_blocks( D, D1X, DX2, //S10
        	            B,B1X,BX1,
        	            B,B1X,BX2,
        	            n2);

 	 strassen_aux(D, D2X, DX1, //P7: P4 NOT NEEDED
                         D, D1X, DX1, //S9
                         D, D1X, DX2, //S10
                         D,D2X,DX2,
                         n2);

  // ((P5 + P1) - P3) - P7
  sub_matrix_blocks(C, C2X, CX2,
                    C, C2X, CX2,
                    D, D2X, DX1, //P7
                    n2);
}

void strassen(float **C,
      float **A, float **B, const size_t n)
{
  float **D=allocate_matrix(n,n);
  strassen_aux(C, 0, 0, A, 0, 0, B, 0, 0, D, 0, 0, n);
  deallocate_matrix(D,n);
}
