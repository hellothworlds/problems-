!  lasso.f90 
!
!  Subroutine:
!  lasso - Takes the three Legacy Fortran codes and wraps them togther so the C code can call them later
!

!****************************************************************************
!
!  SUBROUTINE: lasso
!
!  PURPOSE: Takes the three Legacy Fortran codes and wraps them togther so the C code can call them later
!
!****************************************************************************
    !Declaration of subroutine Lasso, and associated variables
    subroutine  lasso(JF,JMAG,ALATI,ALONG,IYYYY,MMDD,DHOUR,HEIBEG,HEIEND,HEISTP,OUTF,OARR)

    implicit none
    
    logical jf(50)
    integer jmag,iyyyy,mmdd,i
    real*4 alati,along,dhour,heibeg,heiend,heistp
    real*4 outf(20,1000),oarr(100)

    !Calling two legacy Fortran files that must be called for IRI-SUB to compile
    call read_ig_rz
    call readapf107
      

    
    !This is the defined call of IRS-SUB which produces Ion data, as well as other information stored in OUTF
    call IRI_SUB(JF,JMAG,ALATI,ALONG,IYYYY,MMDD,DHOUR,HEIBEG,HEIEND,HEISTP,OUTF,OARR)

    return

    end

