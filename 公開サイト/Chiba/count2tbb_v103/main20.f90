program main
! count to tbb v1.02
! mod. Sep 01, 2020 / CEReS Chiba Univ.
implicit none
character*29::arg
character*8::filelist
real*4,dimension(17000)::tbb
integer*2,dimension(17000)::cnt
integer*2:: i, j, io, NoF, N
integer*2,parameter::pix=6000
integer*2,dimension(pix,pix)::data_all
real,dimension(pix,pix)::data_tbb
real,parameter :: undef=-999.

call getarg( 1, arg ) 
call getarg( 2, filelist)

! Open and Read data
Open(21,file=arg,access='direct',status='old',iostat=io, recl=6000*6000*2)
if(io==0)then
   read(21,rec=1)((data_all(i,j),i=1,pix),j=1,pix);close (21)
end if

! Read table file
NoF=17000
Open ( Unit=20, FILE=filelist,&
   STATUS='OLD',ACCESS='SEQUENTIAL',FORM='FORMATTED')
do N=1,NoF
READ (20, *, IOSTAT = io ) cnt(N),tbb(N)
if (io .ne. 0)exit
end do

! convert CTT to TBB
do i=1,pix
   do j=1,pix
      if( data_all(i,j) < 0 ) then
         data_tbb(i,j)=undef
      else
         data_tbb(i,j)=real(tbb(data_all(i,j)+1))
      end if
   end do
end do

Open ( Unit=10, File="grid20.dat", access='DIRECT',recl=6000*6000*4)
   Write ( 10,rec=1 )((data_tbb(i,j),i=1,6000),j=1,6000)
close(10)
end program main
