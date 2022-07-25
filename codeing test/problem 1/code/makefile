color:
	echo "color"
	gfortran -fpic -c -std=legacy cira.for igrf.for iridreg.for iriflip.for irifun.for irisub.for iritec.for 
	gfortran -fpic -c lasso.f90
	gfortran -shared -o ionslib.so cira.o igrf.o iridreg.o iriflip.o irifun.o irisub.o iritec.o lasso.o


doit:
	echo "just do it"
	gfortran ge1.f90 ford.so

writeexe:
	echo "compile and run exe"
	gcc ctest1.c -c
	gfortran ctest1.o ionslib.so