program trace 
   
   !use omp_lib
   implicit none
   real,dimension(6) :: proc,t
   integer :: i,n1
   real :: speedup 
   
   !n1=omp_get_num_threads()
   open(1,file="temps.dat")
   open(10,file="speedup.dat")
   open(9,file="efficacité.dat")
   
   read(1,*) proc(1),t(1)
   write(9,*) proc(1),1
   
   do i=2,6
   
     read(1,*) proc(i),t(i)
     speedup=t(1)/t(i)
     write(10,*) proc(i),speedup
     write(9,*)  proc(i),speedup/proc(i)
   
   end do
   
   close(1)
   close(10)
   close(9)







end program trace
