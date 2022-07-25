!  Iris.f90 
!
!  FUNCTIONS:
!  Iris - Entry point of console application.
!

!****************************************************************************
!
!  PROGRAM: Iris
!
!  PURPOSE:  Entry point for the console application.
!
!****************************************************************************

    subroutine  Iris(JF,JMAG,ALATI,ALONG,IYYYY,MMDD,DHOUR,HEIBEG,HEIEND,HEISTP,OUTF,OARR)

    implicit none
    
    logical jf(50)
    integer jmag,iyyyy,mmdd,i
    real*4 alati,along,dhour,heibeg,heiend,heistp
    real*4 outf(20,1000),oarr(100)

    ! Variables

    ! Body of Iris
    print *, 'Hello World'

    call read_ig_rz
    call readapf107

    heiend = 1500
    heibeg = 100
    heistp = 50.0 

    do 10 i = 1,50
      jf(i) = .true. 
10  continue 

    jf(4) = .false.
    jf(5) = .false.
    jf(6) = .false.
    jf(21) = .false.
    jf(23) = .false.
    jf(28) = .false.
    jf(29) = .false.
    jf(30) = .false.
    jf(33) = .false.
    jf(35) = .false.
    jf(39) = .false.
    jf(40) = .false.
    jf(47) = .false.

    IYYYY = 2021
    JMAG = 0 
    MMDD = 0303
    DHOUR = 11.00

    ALATI = 37.8 
    ALONG = 75.4         
     


    
    
    call IRI_SUB(JF,JMAG,ALATI,ALONG,IYYYY,MMDD,DHOUR,HEIBEG,HEIEND,HEISTP,OUTF,OARR)

    write(6,*) ' outf(1,1) =',OUTF(1,1)

    end program Iris

