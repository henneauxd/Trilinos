/*
// @HEADER
// ***********************************************************************
//
//            Domi: Multidimensional Datastructures Package
//                 Copyright (2013) Sandia Corporation
//
// Under terms of Contract DE-AC04-94AL85000, there is a non-exclusive
// license for use of this work by or on behalf of the U.S. Government.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
// 1. Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
//
// 3. Neither the name of the Corporation nor the names of the
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY SANDIA CORPORATION "AS IS" AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL SANDIA CORPORATION OR THE
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Questions? Contact William F. Spotz (wfspotz@sandia.gov)
//
// ***********************************************************************
// @HEADER
*/

#include "MDArray_UnitTest_helpers.hpp"

namespace
{

using Teuchos::tuple;
using Teuchos::Array;
using Domi::MDArray;
using Domi::MDArrayView;
using Domi::Slice;
using Teuchos::RangeError;
using MDArrayUnitTestHelpers::nrows;
using MDArrayUnitTestHelpers::ncols;
using MDArrayUnitTestHelpers::generateMDArray;

//template< typename T >

TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( MDArrayView, defaultConstructor, T )
{
  MDArrayView< T > av;
  TEST_EQUALITY_CONST(av.num_dims(), 1);
  TEST_EQUALITY_CONST(av.dimension(0), 0);
  TEST_EQUALITY_CONST(av.size(), 0);
  TEST_EQUALITY_CONST(av.strides()[0], 1);
}

TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( MDArrayView, arrayViewDimsConstructor, T )
{
  typedef typename MDArrayView< T >::size_type size_type;
  Array< T > a(314);
  MDArrayView< T > av(a, tuple< size_type >(12,25));
  TEST_EQUALITY_CONST(av.num_dims(),     2);
  TEST_EQUALITY_CONST(av.dimension(0),  12);
  TEST_EQUALITY_CONST(av.dimension(1),  25);
  TEST_EQUALITY_CONST(av.size(),       300);
}

TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( MDArrayView, arrayViewDimsConstructorBad, T )
{
  typedef typename MDArrayView< T >::size_type size_type;
  Array< T > a(100);
  TEST_THROW(MDArrayView< T > av(a, tuple< size_type >(15,12)), RangeError);
}

TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( MDArrayView, copyConstructor, T )
{
  MDArray< T > a = generateMDArray< T >(3,4);
  MDArrayView< T > av = a.mdArrayView();
  MDArrayView< T > avc(av);
  TEST_EQUALITY_CONST(avc.num_dims(), av.num_dims());
  TEST_EQUALITY_CONST(avc.dimension(0), av.dimension(0));
  TEST_EQUALITY_CONST(avc.dimension(1), av.dimension(1));
  TEST_EQUALITY_CONST(avc(0,0), av(0,0));
  TEST_EQUALITY_CONST(avc(1,0), av(1,0));
  TEST_EQUALITY_CONST(avc(2,0), av(2,0));
  TEST_EQUALITY_CONST(avc(0,1), av(0,1));
  TEST_EQUALITY_CONST(avc(1,1), av(1,1));
  TEST_EQUALITY_CONST(avc(2,1), av(2,1));
  TEST_EQUALITY_CONST(avc(0,2), av(0,2));
  TEST_EQUALITY_CONST(avc(1,2), av(1,2));
  TEST_EQUALITY_CONST(avc(2,2), av(2,2));
  TEST_EQUALITY_CONST(avc(0,3), av(0,3));
  TEST_EQUALITY_CONST(avc(1,3), av(1,3));
  TEST_EQUALITY_CONST(avc(2,3), av(2,3));
}


TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( MDArrayView, indexing4D, T )
{
  typedef Domi::Ordinal ord;
  using Teuchos::tuple;
  ord ni = 2;
  ord nj = 2;
  ord nk = 3;
  ord nm = 3;
  MDArray< T > mda(tuple(ni,nj,nk,nm));
  MDArrayView< T > mdav = mda();
  for (ord m=0; m < nm; m++)
    for (ord k=0; k < nk; k++)
      for (ord j=0; j < nj; j++)
        for (ord i=0; i < ni; i++)
        {
          mdav(i,j,k,m) = 3;
          TEST_EQUALITY(mdav(i,j,k,m), 3);
        }
}

TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( MDArrayView, indexing5D, T )
{
  typedef Domi::Ordinal ord;
  using Teuchos::tuple;
  ord ni = 2;
  ord nj = 2;
  ord nk = 3;
  ord nm = 3;
  ord nn = 4;
  MDArray< T > mda(tuple(ni,nj,nk,nm,nn));
  MDArrayView< T > mdav = mda();
  for (ord n=0; n < nn; n++)
    for (ord m=0; m < nm; m++)
      for (ord k=0; k < nk; k++)
        for (ord j=0; j < nj; j++)
          for (ord i=0; i < ni; i++)
          {
            mdav(i,j,k,m,n) = 4;
            TEST_EQUALITY(mdav(i,j,k,m,n), 4);
          }
}

TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( MDArrayView, indexing6D, T )
{
  typedef Domi::Ordinal ord;
  using Teuchos::tuple;
  ord ni = 2;
  ord nj = 2;
  ord nk = 3;
  ord nm = 3;
  ord nn = 4;
  ord np = 4;
  MDArray< T > mda(tuple(ni,nj,nk,nm,nn,np));
  MDArrayView< T > mdav = mda();
  for (ord p=0; p < np; p++)
    for (ord n=0; n < nn; n++)
      for (ord m=0; m < nm; m++)
        for (ord k=0; k < nk; k++)
          for (ord j=0; j < nj; j++)
            for (ord i=0; i < ni; i++)
            {
              mdav(i,j,k,m,n,p) = 5;
              TEST_EQUALITY(mdav(i,j,k,m,n,p), 5);
            }
}

TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( MDArrayView, indexing7D, T )
{
  // Note: this unit test exercises the variadic argument of the last
  // overloaded operator()
  typedef Domi::Ordinal ord;
  using Teuchos::tuple;
  ord ni = 2;
  ord nj = 2;
  ord nk = 3;
  ord nm = 3;
  ord nn = 4;
  ord np = 4;
  ord nq = 3;
  MDArray< T > mda(tuple(ni,nj,nk,nm,nn,np,nq));
  MDArrayView< T > mdav = mda();
  for (ord q=0; q < nq; q++)
    for (ord p=0; p < np; p++)
      for (ord n=0; n < nn; n++)
        for (ord m=0; m < nm; m++)
          for (ord k=0; k < nk; k++)
            for (ord j=0; j < nj; j++)
              for (ord i=0; i < ni; i++)
              {
                mdav(i,j,k,m,n,p,q) = 6;
                TEST_EQUALITY(mdav(i,j,k,m,n,p,q), 6);
              }
}

TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( MDArrayView, squareBracketOrdinal, T )
{
  MDArray< T > a = generateMDArray< T >(3,4);
  MDArrayView< T > av(a);
  MDArrayView< T > view = av[0][Slice()];
  TEST_EQUALITY_CONST(view(0), 0);
  TEST_EQUALITY_CONST(view(1), 3);
  TEST_EQUALITY_CONST(view(2), 6);
  TEST_EQUALITY_CONST(view(3), 9);

  view = av[1][Slice()];
  TEST_EQUALITY_CONST(view(0),  1);
  TEST_EQUALITY_CONST(view(1),  4);
  TEST_EQUALITY_CONST(view(2),  7);
  TEST_EQUALITY_CONST(view(3), 10);

  view = av[2][Slice()];
  TEST_EQUALITY_CONST(view(0),  2);
  TEST_EQUALITY_CONST(view(1),  5);
  TEST_EQUALITY_CONST(view(2),  8);
  TEST_EQUALITY_CONST(view(3), 11);

  view = av[1][1];
  TEST_EQUALITY_CONST(view(0), 4);
}

TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( MDArrayView, squareBracketOrdinalCOrder, T )
{
  MDArray< T > a = generateMDArray< T >(3,4, Domi::C_ORDER);
  MDArrayView< T > av(a);
  MDArrayView< T > view = av[0][Slice()];
  TEST_EQUALITY_CONST(view(0), 0);
  TEST_EQUALITY_CONST(view(1), 3);
  TEST_EQUALITY_CONST(view(2), 6);
  TEST_EQUALITY_CONST(view(3), 9);

  view = av[1][Slice()];
  TEST_EQUALITY_CONST(view(0),  1);
  TEST_EQUALITY_CONST(view(1),  4);
  TEST_EQUALITY_CONST(view(2),  7);
  TEST_EQUALITY_CONST(view(3), 10);

  view = av[2][Slice()];
  TEST_EQUALITY_CONST(view(0),  2);
  TEST_EQUALITY_CONST(view(1),  5);
  TEST_EQUALITY_CONST(view(2),  8);
  TEST_EQUALITY_CONST(view(3), 11);

  view = av[1][1];
  TEST_EQUALITY_CONST(view(0), 4);
}

TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( MDArrayView, squareBracketSlice1, T )
{
  MDArray< T > a = generateMDArray< T >(4,5);
  MDArrayView< T > av(a);
  MDArrayView< T > view = av[Slice(1,-1)][Slice(1,-1)];
  TEST_EQUALITY_CONST(view(0,0),  5);
  TEST_EQUALITY_CONST(view(0,1),  9);
  TEST_EQUALITY_CONST(view(0,2), 13);
  TEST_EQUALITY_CONST(view(1,0),  6);
  TEST_EQUALITY_CONST(view(1,1), 10);
  TEST_EQUALITY_CONST(view(1,2), 14);
}

TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( MDArrayView, squareBracketSlice2, T )
{
  MDArray< T > a = generateMDArray< T >(4,3);
  MDArrayView< T > av(a);
  MDArrayView< T > view = av[Slice(1,-1)][Slice()];
  TEST_EQUALITY_CONST(view(0,0),  1);
  TEST_EQUALITY_CONST(view(0,1),  5);
  TEST_EQUALITY_CONST(view(0,2),  9);
  TEST_EQUALITY_CONST(view(1,0),  2);
  TEST_EQUALITY_CONST(view(1,1),  6);
  TEST_EQUALITY_CONST(view(1,2), 10);
}

TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( MDArrayView, rangeError, T )
{
  MDArray< T > a = generateMDArray< T >(3,4);
#ifdef HAVE_DOMI_ARRAY_BOUNDSCHECK
  TEST_THROW(a(3,3), RangeError);
  TEST_THROW(a(0,4), RangeError);
#else
  a(0,0);  // Prevent unused variable warning
#endif
}

TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( MDArrayView, rangeErrorCOrder, T )
{
  MDArray< T > a = generateMDArray< T >(3,4,Domi::C_ORDER);
#ifdef HAVE_DOMI_ARRAY_BOUNDSCHECK
  TEST_THROW(a(3,3), RangeError);
  TEST_THROW(a(0,4), RangeError);
#else
  a(0,0);  // Prevent unused variable warning
#endif
}

TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( MDArrayView, legalAt, T )
{
  MDArray< T > a = generateMDArray< T >(2,3);
  TEST_EQUALITY_CONST(a.at(0,0), 0);
  TEST_EQUALITY_CONST(a.at(1,0), 1);
  TEST_EQUALITY_CONST(a.at(0,1), 2);
  TEST_EQUALITY_CONST(a.at(1,1), 3);
  TEST_EQUALITY_CONST(a.at(0,2), 4);
  TEST_EQUALITY_CONST(a.at(1,2), 5);
}

TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( MDArrayView, illegalAt, T )
{
  MDArray< T > a = generateMDArray< T >(2,3);
  TEST_THROW(a.at(2,0), RangeError);
  TEST_THROW(a.at(0,3), RangeError);
}

TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( MDArrayView, toStringNull, T )
{
  MDArrayView< T > av;
  TEST_EQUALITY_CONST(av.toString(), "[]");
}

TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( MDArrayView, toString1D, T )
{
  typedef typename MDArray< T >::size_type size_type;
  T val = 3;
  MDArray< T > a(tuple< size_type >(3), val);
  MDArrayView< T > av(a);
  TEST_EQUALITY_CONST(av.toString(), "[3, 3, 3]");
}

TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( MDArrayView, toString2D, T )
{
  MDArray< T > a = generateMDArray< T >(2,3);
  MDArrayView< T > av(a);
  TEST_EQUALITY_CONST(av.toString(), "[[0, 2, 4],\n [1, 3, 5]]");
}

TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( MDArrayView, toString3D, T )
{
  MDArray< T > a = generateMDArray< T >(2,3,2);
  MDArrayView< T > av(a);
  TEST_EQUALITY_CONST(av.toString(), "[[[0, 1],\n  [2, 3],\n  [4, 5]],\n [[6, 7],\n  [8, 9],\n  [10, 11]]]");
}

//
// Instantiations
//
#ifdef HAVE_DOMI_ARRAY_BOUNDSCHECK
#  define DEBUG_UNIT_TEST_GROUP( T )
#else // HAVE_DOMI_ARRAY_BOUNDSCHECK
#  define DEBUG_UNIT_TEST_GROUP( T )
#endif // HAVE_DOMI_ARRAY_BOUNDSCHECK

#define UNIT_TEST_GROUP( T ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( MDArrayView, defaultConstructor, T ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( MDArrayView, arrayViewDimsConstructor, T ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( MDArrayView, arrayViewDimsConstructorBad, T ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( MDArrayView, copyConstructor, T ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( MDArrayView, indexing4D, T ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( MDArrayView, indexing5D, T ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( MDArrayView, indexing6D, T ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( MDArrayView, indexing7D, T ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( MDArrayView, squareBracketOrdinal, T ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( MDArrayView, squareBracketOrdinalCOrder, T ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( MDArrayView, squareBracketSlice1, T ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( MDArrayView, squareBracketSlice2, T ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( MDArrayView, rangeError, T) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( MDArrayView, rangeErrorCOrder, T) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( MDArrayView, legalAt, T) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( MDArrayView, illegalAt, T) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( MDArrayView, toStringNull, T) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( MDArrayView, toString1D, T) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( MDArrayView, toString2D, T) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( MDArrayView, toString3D, T) \
  DEBUG_UNIT_TEST_GROUP( T )

UNIT_TEST_GROUP(int)
#if 1
UNIT_TEST_GROUP(long)
UNIT_TEST_GROUP(float)
UNIT_TEST_GROUP(double)
#endif

}  // namespace
